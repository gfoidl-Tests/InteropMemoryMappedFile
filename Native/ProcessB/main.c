#include <stdio.h>
#include "mmf.h"
//-----------------------------------------------------------------------------
static const int BufferSize = 256;

#if __unix__
    static const char mapName[] = "/tmp/MyFileMappingObject";
#else
    static const char mapName[] = "MyFileMappingObject";
#endif
//-----------------------------------------------------------------------------
int main()
{
    struct MemoryMappedFile* mmf = memory_mapped_file_open(mapName, BufferSize);

    printf("Message: %s\n", mmf->data);

    memory_mapped_file_close(mmf);
}
