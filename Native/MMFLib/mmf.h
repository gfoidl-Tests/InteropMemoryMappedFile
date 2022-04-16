#pragma once
//-----------------------------------------------------------------------------
#include <stddef.h>
//-----------------------------------------------------------------------------
#define EXIT_MAP_CREATE_FAILED   2
#define EXIT_MAP_OPEN_FAILED     3
#define EXIT_MAP_VIEW_GET_FAILED 4
//-----------------------------------------------------------------------------
struct MemoryMappedFile
{
    char*  data;
    size_t length;
};
//-----------------------------------------------------------------------------
struct MemoryMappedFile* memory_mapped_file_create(const char* mapName, size_t bufferSize);
struct MemoryMappedFile* memory_mapped_file_open(const char* mapName, size_t bufferSize);
void memory_mapped_file_close(struct MemoryMappedFile* memoryMappedFile);
