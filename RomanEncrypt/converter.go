package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"
)

const smakExtension = ".smak"
const moaExtension = ".moa"

var encryptionKey = [...]byte{0x1A, 0x3B, 0x2C, 0x19, 0x08, 0x22, 0x57, 0x72, 0x33}

func isDir(path string) bool {
	fi, err := os.Stat(path)
	if err != nil {
		panic("Got non-valid path.")
	}
	return fi.Mode().IsDir()
}

func buildOutPath(path string) string {
	ext := filepath.Ext(path)
	basePath := strings.TrimSuffix(path, ext)
	switch strings.ToLower(ext) {
	case smakExtension:
		return fmt.Sprintf("%s%s", basePath, moaExtension)
	case moaExtension:
		return fmt.Sprintf("%s%s", basePath, smakExtension)
	}
	panic(fmt.Sprintf("Unknown file extension: %s", path))
}

func convert(inPath string) {
	// building out path
	outPath := buildOutPath(inPath)

	// reading file
	data, err := ioutil.ReadFile(inPath)
	if err != nil {
		panic("Can't open a file given: " + inPath)
	}

	// encrypting file
	keySize := len(encryptionKey)
	for i := 0; i < len(data); i++ {
		data[i] ^= encryptionKey[i%keySize]
	}

	// saving file
	fmt.Println(fmt.Sprintf("Creating - %s", outPath))
	ioutil.WriteFile(outPath, data, os.ModePerm)
}

func main() {
	args := os.Args[1:]
	if len(args) != 1 {
		panic("Unknown arguments given. Expected file/dir path.")
	}

	path := args[0]

	var files []string
	if isDir(path) {
		dir, err := ioutil.ReadDir(path)
		if err != nil {
			panic("Can't enumerate files in a dir given: " + path)
		}

		for _, f := range dir {
			if f.IsDir() {
				continue
			}

			name := f.Name()
			ext := strings.ToLower(filepath.Ext(name))
			if ext != smakExtension && ext != moaExtension {
				continue
			}

			files = append(files, filepath.Join(path, name))
		}
	} else {
		files = append(files, path)
	}

	if len(files) < 1 {
		panic("No designs found.")
	}

	for _, f := range files {
		convert(f)
	}

	fmt.Println(fmt.Sprintf("Conversion completed - %d designs converted.", len(files)))
}
