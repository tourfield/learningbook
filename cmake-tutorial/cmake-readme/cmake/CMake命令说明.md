# CMake命令说明

**命令名称**

&emsp;&emsp;cmake - 跨平台Makefile生成工具。

**用法**

> cmake [选项] <源码路径>
> cmake [选项] <现有构建路径>

**描述**

&emsp;&emsp;cmake可执行程序是CMake的命令行界面。它可以用脚本对工程进行配置。工程配置设置可以在命令行中使用-D选项指定。使用-i选项，cmake将通过提示交互式地完成该设置。

&emsp;&emsp;CMake是一个跨平台的构建系统生成工具。它使用平台无关的CMake清单文件CMakeLists.txt，指定工程的构建过程；源码树的每个路径下都有这个文件。CMake产生一个适用于具体平台的构建系统，用户使用这个系统构建自己的工程。

**选项**

* `-C <initial-cache>`: 预加载一个脚本填充缓存文件。当cmake在一个空的构建树上第一次运行时，它会创建一个CMakeCache.txt文件，然后向其中写入可定制的项目设置数据。-C选项可以用来指定一个文件，在第一次解析这个工程的cmake清单文件时，从这个文件加载缓存的条目(cache entries)信息。被加载的缓存条目比项目默认的值有更高的优先权。参数中给定的那个文件应该是一个CMake脚本，其中包含有使用CACHE选项的SET命令；而不是一个缓存格式的文件。

* `-D <var>:<type>=<value>`: 创建一个CMake的缓存条目。当cmake第一次运行于一个空的构建数时，它会创建一个CMakeCache.txt文件，并且使用可定制的工程设置来填充这个文件。这个选项可以用来指定优先级高于工程的默认值的工程设置值。这个参数可以被重复多次，用来填充所需要数量的缓存条目(cache entries)。

* `-U <globbing_expr>`: 从CMake的缓存文件中删除一条匹配的条目。该选项可以用来删除CMakeCache.txt文件中的一或多个变量。文件名匹配表达式(globbing expression)支持通配符*和?的使用。该选项可以重复多次以删除期望数量的缓存条目。使用它时要小心，你可能因此让自己的CMakeCache.txt罢工。

* `-G <generator-name>`: 指定一个makefile生成工具。在具体的平台上，CMake可以支持多个原生的构建系统。makefile生成工具的职责是生成特定的构建系统。可能的生成工具的名称将在生成工具一节给出。

* `-Wno-dev`: 抑制开发者警告。抑制那些为CMakeLists.txt文件的作者准备的警告信息。

* `-Wdev`: 使能开发者警告信息输出功能。允许那些为CMakeLists.txt文件的作者准备的警告信息。

* `-E`: CMake命令行模式。为了真正做到与平台无关，CMake提供了一系列可以用于所有系统上的的命令。以-E参数运行CMake会帮助你获得这些命令的用法。可以使用的命令有：chdir, copy, copy_if_different copy_directory, compare_files, echo, echo_append, environment, make_directory, md5sum, remove_directory, remove, tar, time, touch, touch_nocreate, write_regv, delete_regv, comspec, create_symlink。

* `-i`: 以向导模式运行CMake。向导模式是在没有GUI时，交互式地运行cmake的模式。cmake会弹出一系列的提示，要求用户回答关于工程配置的一行问题。这些答复会被用来设置cmake的缓存值。

* `-L[A][H]`: 列出缓存的变量中的非高级的变量。-L选项会列出缓存变量会运行CMake，并列出所有CMake的内有被标记为INTERNAL或者ADVANCED的缓存变量。这会显示当前的CMake配置信息，然后你可以用-D选项改变这些选项。修改一些变量可能会引起更多的变量被创建出来。如果指定了A选项，那么命令也会显示高级变量。如果指定了H选项，那么命令会显示每个变量的帮助信息。

* `--build <dir>`: 构建由CMake生成的工程的二进制树。（这个选项的含义我不是很清楚—译注。该选项用以下的选项概括了内置构建工具的命令行界面,运行不带选项的cmake --build来获取快速帮助信息。
```
<dir>            待创建的工程二进制路径。
--target <tgt>   构建<tgt>，而不是默认目标。
--config <cfg>   对于多重配置工具，选择配置<cfg>。
--clean-first    首先构建目标的clean伪目标，然后再构建。
                (如果仅仅要clean掉，使用--target 'clean'选项。）
--               向内置工具（native tools）传递剩余的选项。
```

* `-N`: 查看模式。仅仅加载缓存信息，并不实际运行配置和生成步骤。

* `-P <file>`: 处理脚本模式。
　　将给定的cmake文件按照CMake语言编写的脚本进行处理。不执行配置和生成步骤，不修改缓存信息。如果要使用-D选项定义变量，-D选项必须在-P选项之前。

* `--graphviz=[file]`: 生成依赖的graphviz图。
　　生成一个graphviz软件的输入文件，其中包括了项目中所有库和可执行文件之间的依赖关系。

* `--system-information [file]`: 输出与该系统相关的信息。输出范围比较广的、与当前使用的系统有关的信息。如果在一个CMake工程的二进制构建树的顶端运行该命令，它还会打印一些附加信息，例如缓存，日志文件等等。

* `--debug-trycompile`: 不删除“尝试编译”路径。不删除那些为try_compile调用生成的路径。这在调试失败的try_compile文件时比较有用。不过，因为上一次“尝试编译”生成的旧的垃圾输出文件也许会导致一次不正确通过/不通过，且该结果与上次测试的结果不同，所以该选项可能会改变“尝试编译”的结果。对于某一次“尝试编译”，该选项最好只用一次；并且仅仅在调试时使用。

* `--debug-output`: 将cmake设置为调试模式。在cmake运行时，打印额外的信息；比如使用message(send_error)调用得到的栈跟踪信息。

* `--help-command cmd [file]`: 打印单个命令cmd的帮助信息，然后退出。显示给定的命令的完整的文档。如果指定了[file]参数，该文档会写入该文件，其输出格式由该文件的后缀名确定。支持的文件类型有：man page，HTML，DocBook以及纯文本。

* `--help-command-list [file]`: 列出所有可用命令的清单，然后退出。该选项列出的信息含有所有命令的名字；其中，每个命令的帮助信息可以使用--help-command选项后跟一个命令名字得到。如果指定了[file]参数，帮助信息会写到file中，输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-commands [file]`: 打印所有命令的帮助文件，然后退出。显示所有关于兼容性命令的完整文档。如果指定了[file]参数，帮助信息会写到file中，输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-module module [file]`: 打印某单一模块的帮助信息，然后退出。打印关于给定模块的完整信息。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-module-list [file]`: 列出所有可用模块名，然后退出。列出的清单包括所有模块的名字；其中，每个模块的帮助信息可以使用--help-module选项，后跟模块名的方式得到。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-modules [file]`: 打印所有模块的帮助信息，然后退出。显示关于所有模块的完整文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-custom-modules [file]`: 打印所有自定义模块名，然后退出。显示所有自定义模块的完整文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-policy cmp [file]`: 打印单个策略的帮助信息，然后退出。显示给定的策略的完整文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-policies [file]`: 打印所有策略的帮助信息，然后退出。显示所有策略的完整文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-property prop [file]`: 打印单个属性的帮助信息，然后退出。显示指定属性的完整文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-property-list [file]`: 列出所有可用的属性，然后退出。该命令列出的清单包括所有属性的名字；其中，每个属性的帮助信息都可以通过--help-property选项后跟一个属性名的方式获得。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-properties [file]`: 打印所有属性的帮助信息，然后退出。显示所有属性的完整文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-variable var [file]`: 打印单个变量的帮助信息，然后退出。显示指定变量的完整文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-variable-list [file]`: 列出文档中有记录的变量，然后退出。该命令列出的清单包括所有变量的名字；其中，每个变量的帮助信息都可以通过--help-variable选项后跟一个变量名的方式获得。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--help-variables [file]`: 打印所有变量的帮助信息，然后退出。显示所有变量的完整帮助文档。如果指定了[file]参数，帮助信息会写到file中，且输出格式依赖于文件名后缀。支持的文件格式包括：man page，HTML，DocBook以及纯文本。

* `--copyright [file]`: 打印CMake的版权信息，然后退出。如果指定了[file]参数，版权信息会写到这个文件中。

* `--help`: 打印用法信息，然后退出。用法信息描述了基本的命令行界面及其选项。

* `--help-full [file]`: 打印完整的帮助信息，然后退出。显示大多数UNIX man page提供的帮助信息。该选项是为非UNIX平台提供的；但是如果man手册页没有安装，它也能提供便利。如果制定了[file]参数，帮助信息会写到这个文件中。

* `--help-html [file]`: 以HTML格式打印完整的帮助信息，然后退出。CMake的作者使用该选来帮助生成web页面。如果指定了[file]参数，帮助信息会写到这个文件中。

* `--help-man [file]`: 以UNIX的man手册页格式打印完整的帮助信息，然后退出。cmake使用该选生成UNIX的man手册页。如果指定了[file]参数，帮助信息会写到这个文件中。

* `--version [file]`: 显示程序名/版本信息行，然后退出。如果指定了[file]参数，版本信息会写到这个文件中。

_注：对于CMake的语言要素，比如命令，属性和变量，帮助命令选项也是很有规律的，一般是用--help-xxx-list查看所有值的名字，找出感兴趣的项，然后用--help-xxx name查看该名字的详细信息；也可以用--help-xxxs获得相关语言要素的完整帮助信息。_
