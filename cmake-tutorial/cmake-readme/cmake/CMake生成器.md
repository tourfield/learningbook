# CMake生成器

&emsp;&emsp;在CMake 2.8.3平台上，CMake支持下列生成器：

* Borland Makefiles: 生成Borland makefile。
* MSYS Makefiles: 生成MSYS makefile。
生成的makefile用use /bin/sh作为它的shell。在运行CMake的机器上需要安装msys。

* MinGW Makefiles: 生成供mingw32-make使用的make file。
生成的makefile使用cmd.exe作为它的shell。生成它们不需要msys或者unix shell。

* NMake Makefiles: 生成NMake makefile。
* NMake Makefiles JOM: 生成JOM makefile。
* Unix Makefiles: 生成标准的UNIX makefile。
在构建树上生成分层的UNIX makefile。任何标准的UNIX风格的make程序都可以通过默认的make目标构建工程。生成的makefile也提供了install目标。

* Visual Studio 10: 生成Visual Studio 10 工程文件。
* Visual Studio 10 Win64: 生成Visual Studio 10 Win64 工程文件。
* Visual Studio 6: 生成Visual Studio 6 工程文件。
* Visual Studio 7: 生成Visual Studio .NET 2002 工程文件。
* Visual Studio 7 .NET 2003: 生成Visual Studio .NET 2003工程文件。
* Visual Studio 8 2005: 生成Visual Studio .NET 2005 工程文件。
* Visual Studio 8 2005 Win64: 生成Visual Studio .NET 2005 Win64工程文件。
* Visual Studio 9 2008: 生成Visual Studio 9 2008 工程文件。
* Visual Studio 9 2008 Win64: 生成Visual Studio 9 2008 Win64工程文件。
* Watcom WMake: 生成Watcom WMake makefiles。
* CodeBlocks - MinGW Makefiles: 生成CodeBlock工程文件。
在顶层目录以及每层子目录下为CodeBlocks生成工程文件，生成的CMakeList.txt的特点是都包含一个PROJECT()调用。除此之外还会在构建树上生成一套层次性的makefile。通过默认的make目标，正确的make程序可以构建这个工程。makefile还提供了install目标。

* CodeBlocks - NMake Makefiles: 生成CodeBlocks工程文件。
在顶层目录以及每层子目录下为CodeBlocks生成工程文件，生成的CMakeList.txt的特点是都包含一个PROJECT()调用。除此之外还会在构建树上生成一套层次性的makefile。通过默认的make目标，正确的make程序可以构建这个工程。makefile还提供了install目标。

* CodeBlocks - Unix Makefiles: 生成CodeBlocks工程文件。
在顶层目录以及每层子目录下为CodeBlocks生成工程文件，生成的CMakeList.txt的特点是都包含一个PROJECT()调用。除此之外还会在构建树上生成一套层次性的makefile。通过默认的make目标，正确的make程序可以构建这个工程。makefile还提供了install目标。

* Eclipse CDT4 - MinGW Makefiles: 生成Eclipse CDT 4.0 工程文件。
在顶层目录下为Eclipse生成工程文件。在运行源码外构建时，一个连接到顶层源码路径的资源文件会被创建。除此之外还会在构建树上生成一套层次性的makefile。通过默认的make目标，正确的make程序可以构建这个工程。makefile还提供了install目标。

* Eclipse CDT4 - NMake Makefiles: 生成Eclipse CDT 4.0 工程文件。
在顶层目录下为Eclipse生成工程文件。在运行源码外构建时，一个连接到顶层源码路径的资源文件会被创建。除此之外还会在构建树上生成一套层次性的makefile。通过默认的make目标，正确的make程序可以构建这个工程。makefile还提供了install目标。

* Eclipse CDT4 - Unix Makefiles: 生成Eclipse CDT 4.0 工程文件。
在顶层目录下为Eclipse生成工程文件。在运行源码外构建时，一个连接到顶层源码路径的资源文件会被创建。除此之外还会在构建树上生成一套层次性的makefile。通过默认的make目标，正确的make程序可以构建这个工程。makefile还提供了install目标。
