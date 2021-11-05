# Welcome to libSwitchWarningsOff

This small CMake based C++ package provides two macros `SWITCH_WARNINGS_OFF` and `SWITCH_WARNINGS_ON`.
The macros are supposed to be used to suppress warnings from external headers that often occur when compiling
with high warning levels.

Targets that link to *libSwitchWarningsOff* will automatically force include the header file that provides the macros, so no
manual includes are required in order to use the macro.

## Example ##

```cpp
// file MySource.cpp
#include "MySource.h"

SWITCH_WARNINGS_ON
// external headers that cause warnings during compilation
#include <gtest/gtest.h>
#include <QString>
SWITCH_WARNINGS_OFF

#include "MyOtherSource.h"

...
your code that should compile without warnings
...


```

## Usage ##

The macro is known to work with VS, Gcc and Clang. Add the repository as git submodule to your CMake project
and add it with `add_subdirectory()`. Then you should get a *libSwitchWarningsOff* target that you can
link to your targets.
