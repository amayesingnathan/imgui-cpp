# imgui-cpp

A modern C++ wrapper around Dear ImGui widgets.

## Description

This is a wrapper around Dear ImGui widgets written using C++20. Not only does it use C++20 modules, resulting in faster build times, but also provides
more type safe abstractions around certain widgets using templates and concepts. 

imgui-cpp uses the master branch of imgui, but does not export it as part of the main imcpp module. This means it is required to link your own version, but means that different branches
should be possible to use as imgui-cpp does not depend on anything other than core ImGui features.

## Getting Started

### Dependencies

* Dear ImGui - Internal dependency but is not exported so is required in your own project as the API used ImGui types and typedefs.
* Python3 - Used for setup scripts
* premake5 - Will be downloaded and extracted as a binary when the setup script is run if it is not found.

### Installing

* Clone the repo recursively and run `setup.bat` for Windows or `setup.sh` for Linux.

## License

This project is licensed under the MIT License - see the LICENSE.md file for details