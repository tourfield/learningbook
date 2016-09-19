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
install (FILES mysqrt.h DESTINATION include)
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

&emsp;&emsp;编译出可执行文件后，我们可以添加测试命令，编译完成后执行`make test`进行测试，在`CMakeLists.txt`文件中添加`PASS_REGULAR_EXPRESSION`属性，通过检测输出结果中包含的字符来判断代码执行的是否正确。
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

&emsp;&emsp;另外我们可以在`CMakeLists.txt`文件中定义一个函数，简化书写测试命令，具体实现如下：
``` cmake
#define a macro to simplify adding tests, then use it
macro (do_test arg result)
  add_test (TutorialComp${arg} Tutorial ${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# do a bunch of result based tests
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")
```

## 为工程添加日志功能

&emsp;&emsp;接下来为我们的工程添加日志功能的宏控制，在顶层的`CMakeLists.txt`文件中增加下面代码：
```
# does this system provide the log and exp functions?
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)
```
&emsp;&emsp;然后在TutorialConfig.h.in文件中增加定义`HAVE_LOG`和`HAVE_EXP`宏定义。
```
// does the platform provide exp and log functions?
#cmakedefine HAVE_LOG
#cmakedefine HAVE_EXP
```
&emsp;&emsp;在mysqrt.cxx文件中，根据宏定义定义代码段，如下：
```
#if defined(HAVE_LOG) && defined(HAVE_EXP)
  return sqrt(d);
#else
  return exp(log(d) * 0.5);
#endif
```

## 添加一个生成器和生成文件

&emsp;&emsp;本节中将为工程添加一个生成源文件。在下面的例子中，我们将创建预先计算平方分的表作为工程的输入。要做到这一点，我们需要先创建一个程序用于生成表。在MathFunctions子目录中新建一个`MakeTable.cxx`文件，其内容如下：
``` cpp
// A simple program that builds a sqrt table
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{
  int i;
  double result;

  // make sure we have enough arguments
  if (argc < 2)
    {
    return 1;
    }

  // open the output file
  FILE *fout = fopen(argv[1],"w");
  if (!fout)
    {
    return 1;
    }

  // create a source file with a table of square roots
  fprintf(fout,"double sqrtTable[] = {\n");
  for (i = 0; i < 10; ++i)
    {
    result = sqrt(static_cast<double>(i));
    fprintf(fout,"%g,\n",result);
    }

  // close the table with a zero
  fprintf(fout,"0};\n");
  fclose(fout);
  return 0;
}
```
&emsp;&emsp;注意：生成的表格作为有效的C++代码并作为输出文件传递参数。接下来修改MathFunctions子目录下的`CMakeLists.txt`文件，用于创建`MakeTable`可执行文件，修改代码如下：
```
# first we add the executable that generates the table
add_executable(MakeTable MakeTable.cxx)

# add the command to generate the source code
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )

# add the binary tree directory to the search path for
# include files
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

# add the main library
add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

install (TARGETS MathFunctions DESTINATION bin)
install (FILES mysqrt.h DESTINATION include)
```
&emsp;&emsp;首先需要将可执行文件`MakeTable`加到工程中，然后指定运行该文件以生成`Table.h`文件。接下来通过将生成的`Table.h`文件加到生成的MathFunctions库文件中以通知cmake `mysqrt.cxx`依赖于`Table.h`文件。同时我们还需要添加当前的库文件目录以便编译时可以找到`Table.h`文件。当编译生成`MakeTable`文件后，会执行该文件以生成`Table.h`文件。顶层的`CMakeLists.txt`文件如下：
```
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
include(CTest)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# does this system provide the log and exp functions?
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)

check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# should we use our own math functions
option(USE_MYMATH
  "Use tutorial provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories ("${PROJECT_BINARY_DIR}")

# add the MathFunctions library?
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# add the executable
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial  ${EXTRA_LIBS})

# add the install targets
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
         DESTINATION include)

# does the application run
add_test (TutorialRuns Tutorial 25)

# does the usage message work?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage
  PROPERTIES
  PASS_REGULAR_EXPRESSION "Usage:.*number"
  )


#define a macro to simplify adding tests
macro (do_test arg result)
  add_test (TutorialComp${arg} Tutorial ${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endmacro (do_test)

# do a bunch of result based tests
do_test (4 "4 is 2")
do_test (9 "9 is 3")
do_test (5 "5 is 2.236")
do_test (7 "7 is 2.645")
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")
do_test (0.0001 "0.0001 is 0.01")
```
&emsp;&emsp;配置文件TutorialConfig.h.in定义如下：
```

// the configured options and settings for Tutorial
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
#cmakedefine USE_MYMATH

// does the platform provide exp and log functions?
#cmakedefine HAVE_LOG
#cmakedefine HAVE_EXP
```

## 生成安装包
&emsp;&emsp;通常我们发型软件时通过两种方式进行发行，第一种是通过发布可执行文件，另一种是通过发行源文件；我们要发行我们的软件也很简单，只需要在顶层的`CMakeLists.txt`文件结尾添加一下几行代码：
```
# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include (CPack)
```
&emsp;&emsp;创建二进制安装包，执行下面的命令：
``` sh
cpack --config CPackConfig.cmake
```
&emsp;&emsp;创建源文件安装包，执行下面的命令：
```
cpack --config CPackSourceConfig.cmake
```

## 上传测试结果
&emsp;&emsp;将我们的测试结果提交到[展示网站](https://open.cdash.org/index.php?project=PublicDashboard)，方法很简单，在顶层的`CMakeLists.txt`文件中允许CTest如下：
```
# enable dashboard scripting
include (CTest)
```
&emsp;&emsp;然后我们可以创建一个`CTestConfig.cmake`文件来指定项目的名称如下。CTest运行时将会读取这个文件。在执行`cmake`之后，进入编译生成文件目录，执行`ctest -D`，然后测试结果将会上传到展示网站上。
