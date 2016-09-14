# <center>Cmake教程
&emsp;&emsp;CMake是一个跨平台的安装(编译)工具,可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件,能测试编译器所支持的C++特性,类似UNIX下的automake。所有的Cmake编译规则定义在`CMakeLists.txt`文件中。

&emsp;&emsp;本教程通过实例来说明如何使用Cmake构建一个工程。其中每一步都有一个具体的实例，来展示如何编写Cmake规则。

## 由源文件生产可执行文件

&emsp;&emsp;最基础的项目是由源文件生产可执行文件，我们通过在`CMakeLists.txt`文件中定义下面的两行规格就能满足需求。
``` cmake
cmake_minimum_required (VERSION 2.6) #声明需要cmake的最低版本
project (Tutorial) #工程名称，同时也是在CMakeFiles目录下创建存放生成中间文件的目录依赖名Tutorial.dir
add_executable(Tutorial tutorial.cxx) #生成可执行文件名称，以及编译依赖文件
```
&emsp;&emsp;这里使用的是小写字母来完成规则的编写，在Cmake文件中对字母的大小写并不敏感我们可以任意使用大写小写或者混合编写。`tutorial.cxx`文件定义如下：
``` cpp
// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main (int argc, char *argv[])
{
  if (argc < 2)
    {
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }
  double inputValue = atof(argv[1]);
  double outputValue = sqrt(inputValue);
  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
  return 0;
}
```

## 添加版本信息和配置文件

&emsp;&emsp;通过`set`命令为生成的可执行文件添加版本信息，然后通过`configure_file`命令添加配置文件，在`CMakeLists.txt`文件中具体实现如下：
``` cmake
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
# 设置软件版本信息
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# 指定配置文件
# 生成头文件
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# 指定在生成文件目录查找头文件TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# 指定生成文件以及依赖文件
add_executable(Tutorial tutorial.cxx)
```
&emsp;&emsp;配置文件`TutorialConfig.h.in`内容如下：
``` cpp
// the configured options and settings for Tutorial
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```
&emsp;&emsp;C++源码如下：
``` cpp
// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TutorialConfig.h"

int main (int argc, char *argv[])
{
  if (argc < 2)
    {
    fprintf(stdout,"%s Version %d.%d\n",
            argv[0],
            Tutorial_VERSION_MAJOR,
            Tutorial_VERSION_MINOR);
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }
  double inputValue = atof(argv[1]);
  double outputValue = sqrt(inputValue);
  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
  return 0;
}
```
## 为工程添加库文件

&emsp;&emsp;现在我们为我们的工程，添加一个包含计算一个数的平方根的函数的库文件。假定将库的实现放在MathFunctions子目录中，我们需要在该子目录中创建一个CMakeLists.txt文件，包含下面一行代码：
``` cmake
add_library(MathFunctions mysqrt.cxx)
```
&emsp;&emsp;在``mysqrt.cxx``文件中定义了一个mysqrt函数；如果要使用库文件，我们需要在工程顶层目录的CMakeLists.txt文件中添加add_subdirectory调用，然后需要指定头文件路径以便查找到库文件的头文件。顶层CMakeLists.txt文件最后几行代码如下:
``` cmake
include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
add_subdirectory (MathFunctions)

# add the executable
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial MathFunctions)
```
&emsp;&emsp;如果我们想实现MathFunctions库为可选择的，那么我们需要在顶层CMakeLists.txt文件中添加如下代码：
``` cmake
# should we use our own math functions?
option (USE_MYMATH "Use tutorial provided math implementation" ON)
```
&emsp;&emsp;修改顶层的CMakeLists.txt文件内容如下，通过变量`USE_MYMATH`来选择是否使用MathFunctions库文件：
``` cmake
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# should we use our own math functions?
#option (USE_MYMATH "Use tutorial provided math implementation" OFF)
option (USE_MYMATH "Use tutorial provided math implementation" ON)

if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

#include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
#add_subdirectory (MathFunctions)

# add the executable
add_executable(Tutorial tutorial.cxx)
#target_link_libraries (Tutorial MathFunctions)
target_link_libraries (Tutorial  ${EXTRA_LIBS})
```
&emsp;&emsp;同时需要在`TutorialConfig.h.in`配置文件中添加一个定义，以便生成`USE_MYMATH`宏定义，在源文件中使用：
``` cpp
#cmakedefine USE_MYMATH
```
&emsp;&emsp;源文件代码实现如下（库文件的实现见代码）：
``` cpp
// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "mysqrt.h"
#endif

int main (int argc, char *argv[])
{
  if (argc < 2)
    {
    fprintf(stdout,"%s Version %d.%d\n", argv[0],
            Tutorial_VERSION_MAJOR,
            Tutorial_VERSION_MINOR);
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }

  double inputValue = atof(argv[1]);

#ifdef USE_MYMATH
  double outputValue = mysqrt(inputValue);
#else
  double outputValue = sqrt(inputValue);
#endif

  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
  return 0;
}
```
## 安装和测试

&emsp;&emsp;通过添加下面的规则，来给工程添加安装的功能。对于MathFunctions库，通过修改子目录下的`CMakeLists.txt`文件来实现，修改如下：
``` cmake
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
```
&emsp;&emsp;对于应用程序以下行被添加到顶层的`CMakeLists.txt`文件来安装可执行文件和配置的头文件：
``` cmake
# add the install targets
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
         DESTINATION include)
```
&emsp;&emsp;在执行`cmake`之后生成的Makefile文件中，生成了install目标，执行`make install`安装文件；
可以通过变量`CMAKE_INSTALL_PREFIX`来指定安装的路径。

&emsp;&emsp;编译出可执行文件后，我们可以添加测试命令，
``` cmake
include(CTest)
# does the application run
add_test (TutorialRuns Tutorial 25)
# does it sqrt of 25
add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")
# does it handle negative numbers
add_test (TutorialNegative Tutorial -25)
set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is -nan")

# does it handle small numbers
add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
# does the usage message work?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")
```
