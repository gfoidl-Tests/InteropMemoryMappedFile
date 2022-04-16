#include "mmf.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
//-----------------------------------------------------------------------------
struct MemoryMappedFileInternal
{
    struct MemoryMappedFile mmf;
    void*                   viewHandle;
};
//-----------------------------------------------------------------------------
static void* view_accessor_get(void* mapFile, size_t bytesToMap);
static void view_accessor_close(void* viewAccessor);
//-----------------------------------------------------------------------------
static struct MemoryMappedFile* create(void* mapFile, void* viewAccessor, size_t length)
{
    struct MemoryMappedFileInternal* mmf = malloc(sizeof(*mmf));
    if (mmf == NULL)
    {
        exit(EXIT_FAILURE);
    }

    mmf->viewHandle = mapFile;
    mmf->mmf.length = length;
    mmf->mmf.data   = viewAccessor;

    return &mmf->mmf;
}
//-----------------------------------------------------------------------------
struct MemoryMappedFile* memory_mapped_file_create(const char* mapName, size_t bufferSize)
{
    void* mapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        (DWORD)bufferSize,
        mapName);

    if (mapFile == NULL)
    {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        exit(EXIT_MAP_CREATE_FAILED);
    }

    void* viewAccessor = view_accessor_get(mapFile, bufferSize);

    return create(mapFile, viewAccessor, bufferSize);
}
//-----------------------------------------------------------------------------
struct MemoryMappedFile* memory_mapped_file_open(const char* mapName, size_t bufferSize)
{
    void* mapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        mapName);

    if (mapFile == NULL)
    {
        printf("Could not open file mapping object (%d).\n", GetLastError());
        exit(EXIT_MAP_OPEN_FAILED);
    }

    void* viewAccessor = view_accessor_get(mapFile, bufferSize);

    return create(mapFile, viewAccessor, bufferSize);
}
//-----------------------------------------------------------------------------
void memory_mapped_file_close(struct MemoryMappedFile* handle)
{
    struct MemoryMappedFileInternal* mmf = (struct MemoryMappedFileInternal*)handle;

    view_accessor_close(mmf->mmf.data);
    CloseHandle(mmf->viewHandle);

    free(mmf);
}
//-----------------------------------------------------------------------------
static void* view_accessor_get(void* mapFile, size_t bytesToMap)
{
    void* viewAccessor = MapViewOfFile(mapFile, FILE_MAP_ALL_ACCESS, 0, 0, bytesToMap);

    if (viewAccessor == NULL)
    {
        printf("Could not map view of file (%d).\n", GetLastError());
        memory_mapped_file_close(mapFile);
        exit(EXIT_MAP_VIEW_GET_FAILED);
    }

    return viewAccessor;
}
//-----------------------------------------------------------------------------
static void view_accessor_close(void* viewAccessor)
{
    UnmapViewOfFile(viewAccessor);
}
