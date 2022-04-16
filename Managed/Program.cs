using System.IO.MemoryMappedFiles;

string mapName = OperatingSystem.IsLinux()
    ? "/tmp/MyFileMappingObject"
    : "MyFileMappingObject";

using MemoryMappedFile memoryMappedFile = OperatingSystem.IsWindows()
    ? MemoryMappedFile.OpenExisting("mapName")
    : MemoryMappedFile.CreateFromFile(mapName);

using MemoryMappedViewStream stream = memoryMappedFile.CreateViewStream();
using StreamReader reader           = new(stream, leaveOpen: true);
string? message                     = reader.ReadLine();

Console.WriteLine($"Message:     {message}");
Console.WriteLine($"Message len: {message?.Length}");
