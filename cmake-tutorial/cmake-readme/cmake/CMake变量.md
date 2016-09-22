# CMake变量
&emsp;&emsp;CMake变量按功能分有主要有四种不同的类型：
1. 提供信息的变量[共53个]；
2. 改变行为的变量[共23个]；
3. 描述系统的变量[共24个]；
4. 控制构建过程的变量[共22个]。
&emsp;&emsp;此外还有一些变量因编译使用的语言不同而不同，将它们归为第五类[共29个]。由于变量比较多，这里只给出变量的大概描述；具体作用可使用`cmake --help-variable variable_name`命令查看。

**提供信息的变量**

* CMAKE_AR   静态库的归档工具名字。
* CMAKE_BINARY_DIR  构建树的顶层路径。
* CMAKE_BUILD_TOOL  实际构建过程中使用的工具。
* CMAKE_CACHEFILE_DIR  文件CMakeCache.txt所在的路径。
* CMAKE_CACHE_MAJOR_VERSION  用于创建CMakeCache.txt文件的CMake的主版本号。
* VCMAKE_CACHE_MINOR_VERSION  用于创建CMakeCache.txt文件的CMake的子版本号。
* CMAKE_CACHE_PATCH_VERSION  用于创建CMakeCache.txt文件的CMake的补丁号。
* CMAKE_CFG_INTDIR 构建时，与构建配置相对应的输出子路径（只读）。
* CMAKE_COMMAND 指向CMake可执行文件的完整路径。
* CMAKE_CROSSCOMPILING  指出CMake是否正在交叉编译。
* CMAKE_CTEST_COMMAND  与cmake一起安装的ctest命令的完整路径。
* CMAKE_CURRENT_BINARY_DIR 当前正在被处理的二进制目录的路径。
* CMAKE_CURRENT_LIST_DIR  当前正在处理的listfile的完整目录。
* CMAKE_CURRENT_LIST_FILE  当前正在处理的listfile的完整路径。
* CMAKE_CURRENT_LIST_LINE  当前正在处理的listfile的行号。
* CMAKE_CURRENT_SOURCE_DIR  指向正在被处理的源码目录的路径。
* CMAKE_DL_LIBS  包含dlopen和dlclose函数的库的名称。
* CMAKE_EDIT_COMMAND  指向cmake-gui或ccmake的完整路径。
* CMAKE_EXECUTABLE_SUFFIX(_<LANG>) 本平台上可执行文件的后缀。
* CMAKE_EXTRA_GENERATOR  构建本工程所需要的额外生成器。
* CMAKE_EXTRA_SHARED_LIBRARY_SUFFIXES 附加的共享库后缀（除CMAKE_SHARED_LIBRARY_SUFFIX以外，其他可以识别的共享库的后缀名。）
* CMAKE_GENERATOR  用于构建该工程的生成器。
* CMAKE_HOME_DIRECTORY 指向源码树顶层的路径。
* CMAKE_IMPORT_LIBRARY_PREFIX(_<LANG>)  需要链接的导入库的前缀。
* CMAKE_IMPORT_LIBRARY_SUFFIX(_<LANG>)  需要链接的导入库的后缀。
* CMAKE_LINK_LIBRARY_SUFFIX  需要链接的库的后缀。
* CMAKE_MAJOR_VERSION  cmake的主版本号（例如2.X.X中的2）。
* CMAKE_MAKE_PROGRAM  参见CMAKE_BUILD_TOOL。
* CMAKE_MINOR_VERSION  cmake的次版本号（例如X.4.X中的4）。
* CMAKE_PARENT_LIST_FILE  当前正在被处理listfile的父listfile的全路径。
* CMAKE_PATCH_VERSION  cmake的补丁号(例如X.X.3中的3)。
* CMAKE_PROJECT_NAME  当前工程的工程名。
* CMAKE_RANLIB  静态库的随机化工具的名字（比如linux下的ranlib）。
* CMAKE_ROOT  CMake的安装路径。
* CMAKE_SHARED_LIBRARY_PREFIX(`_<LANG>`)  被链接的共享库的前缀。
* CMAKE_SHARED_LIBRARY_SUFFIX(`_<LANG>`)  被链接的共享库的后缀。
* CMAKE_SHARED_MODULE_PREFIX(`_<LANG>`)  被链接的可加载模块的前缀。
* CMAKE_SHARED_MODULE_SUFFIX(`_<LANG>`)  被链接的共享库的后缀。
* CMAKE_SIZEOF_VOID_P void指针的长度。
* CMAKE_SKIP_RPATH  如果变量为真，不为编译出的可执行文件添加运行时的路径信息。默认添加。
* CMAKE_SOURCE_DIR  源码树的顶层路径。
* CMAKE_STANDARD_LIBRARIES  链接到所有可执行文件和共享库上的库。这是一个list。
* CMAKE_STATIC_LIBRARY_PREFIX(`_<LANG>`)  被链接的静态库的前缀。
* CMAKE_STATIC_LIBRARY_SUFFIX(`_<LANG>`)  被链接的静态库的后缀。
* CMAKE_TWEAK_VERSION  cmake的tweak版本号(例如X.X.X.1中的1)。
* CMAKE_USING_VC_FREE_TOOLS  如果用到了免费的visual studio工具，设置为真。
* CMAKE_VERBOSE_MAKEFILE  设置该变量为真将创建完整版本的makefile。
* CMAKE_VERSION  cmake的完整版本号；格式为major.minor.patch[.tweak[-id]]。
* PROJECT_BINARY_DIR  指向工程构建目录的全路径。
* PROJECT_NAME  向project命令传递的工程名参数。
* PROJECT_SOURCE_DIR  当前工程的源码路径。
* [Project name]_BINARY_DIR  给定工程的二进制文件顶层路径。
* [Project name]_SOURCE_DIR  给定工程的源码顶层路径。
