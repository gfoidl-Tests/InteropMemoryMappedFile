#include "mmf.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
//-----------------------------------------------------------------------------
struct MemoryMappedFileInternal
{
    struct MemoryMappedFile mmf;
    const char*             mapName;
};
//-----------------------------------------------------------------------------
static struct MemoryMappedFile* create(const char* mapName, size_t length, void* viewAccessor)
{
    struct MemoryMappedFileInternal* mmf = malloc(sizeof(*mmf));
    if (mmf == NULL)
    {
        exit(EXIT_FAILURE);
    }

    mmf->mapName    = mapName;
    mmf->mmf.length = length;
    mmf->mmf.data   = viewAccessor;

    return &mmf->mmf;
}
//-----------------------------------------------------------------------------
struct MemoryMappedFile* memory_mapped_file_create(const char* mapName, size_t bufferSize)
{
    return memory_mapped_file_open(mapName, bufferSize);
}
//-----------------------------------------------------------------------------
struct MemoryMappedFile* memory_mapped_file_open(const char* mapName, size_t bufferSize)
{
    //char dummyFileName[] = "/tmp/mmfXXXXXX";
    //mkstemp(dummyFileName);

    // mode must be specified, for access rights.
    int fd = open(mapName, O_RDWR | O_CREAT, S_IRWXU);
    if (fd == -1)
    {
        printf("Could not create file mapping object (%d).\n", errno);
        exit(EXIT_MAP_CREATE_FAILED);
    }

    // If the file didn't exist it's created as empty file, so we need to set
    // the size, otherwise there's nothing to read and a bus-error will be created.
    ftruncate(fd, bufferSize);

    void* map = mmap(NULL, bufferSize, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        printf("Could not open file mapping object (%d).\n", errno);
        exit(EXIT_MAP_VIEW_GET_FAILED);
    }

    // Close the dummy-file here, the kernel will release it when the mmf is closed.
    // Also remove the file.
    close(fd);

    return create(mapName, bufferSize, map);
}
//-----------------------------------------------------------------------------
void memory_mapped_file_close(struct MemoryMappedFile* handle)
{
    struct MemoryMappedFileInternal* mmf = (struct MemoryMappedFileInternal*)handle;

    int res = munmap(mmf->mmf.data, mmf->mmf.length);
    if (res == -1)
    {
        exit(EXIT_FAILURE);
    }

    remove(mmf->mapName);

    free(mmf);
}
