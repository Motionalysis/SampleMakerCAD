#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

const std::vector<char> Key = { 0x1A, 0xB3, 0xCA, 0x19, 0x08, 0x22, 0x57, 0x72, 0x33 };

long ReadAllBytes(const char* filename, char** buf)
{
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    *buf = new char[pos];
    ifs.seekg(0, std::ios::beg);
    ifs.read(*buf, pos);
    ifs.close();
    return pos;
}

void Decrypt(char* buf, long size) 
{
    auto keyIterator = Key.begin();
    for (long i = 0; i < size; i++)
    {
        buf[i] ^= *keyIterator;
        if (++keyIterator == Key.end())
            keyIterator = Key.begin();
    }
}

long ConvertToSmak(const char* filename, char** buf)
{
    long size = ReadAllBytes(filename, buf);
    Decrypt(*buf, size);
    return size;
}


void main() 
{
    std::string filename = "design.moa";
    char* buf;
    long size = ConvertToSmak(filename.c_str(), &buf);
    // at this stage buf should contain .smak file content, which can be passed to our lib by calling OpenFromBuffer(buf, size)
}
