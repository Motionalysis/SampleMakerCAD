/*-----------------------------------------------------------------------------
 * Data structures and prototypes for slvs.lib, a geometric constraint solver.
 *
 * See the comments in this file, the accompanying sample code that uses
 * this library, and the accompanying documentation (DOC.txt).
 *
 * Copyright 2009-2013 Jonathan Westhues.
 *---------------------------------------------------------------------------*/

#ifndef __SLVSPLUG_H
#define __SLVSPLUG_H

#define DLL

#ifdef _MSC_VER
typedef unsigned __int32 uint32_t;
#else
#include <stdint.h>
#endif

extern "C" {

DLL void Init();

DLL int OpenFromFile(const char* inFilename);
DLL int OpenFromBuffer(const char* buffer, size_t size);
DLL int ImportFromFile(const char* filename, char** message);
DLL void SetVar(const char* name, double val);
DLL void ResetVars();
DLL bool GetVariablesFromBuffer(const char* buf, size_t size,
    char names[32][256], char values[32][256], int* matchCount);
DLL bool GetVariablesFromFile(const char* filename,
    char names[32][256], char values[32][256], int* matchCount);

DLL bool ResolveFile(char** message);
DLL void GenerateXml(char** outString);
DLL void FreeStr(char* str);

DLL void DrawPreview(int x, int y, int w, int h);
DLL void ExportToFile(const char* filename);

}

#endif
