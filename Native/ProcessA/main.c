#include <stdio.h>
#include <string.h>
#include "mmf.h"
//-----------------------------------------------------------------------------
static const int BufferSize = 256;
static const char message[] = "Process A says 'Hi to all' :-)\n";

#if __unix__
    static const char mapName[] = "/tmp/MyFileMappingObject";
#else
    static const char mapName[] = "MyFileMappingObject";
#endif
//-----------------------------------------------------------------------------
int main()
{
    struct MemoryMappedFile* mmf = memory_mapped_file_create(mapName, BufferSize);

    memcpy(mmf->data, message, strlen(message));

    printf("Message written (%ld bytes), hit any key to exit\n", strlen(message));
    getchar();

    memory_mapped_file_close(mmf);
}
