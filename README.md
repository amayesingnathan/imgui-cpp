# imgui-cpp

A modern C++ wrapper around Dear ImGui widgets.

## Description

This is a wrapper around Dear ImGui widgets written using C++20. Not only does it use C++20 modules, resulting in faster build times, but also provides
more type safe abstractions around certain widgets using templates and concepts. 

imgui-cpp packages Dear ImGui and GLFW, but expects the user to provide their own handling of a GLFWwindow. When creating an ImHandler, which manages ImGui initialisation and shutdown 
using RAII, the user must provide two callbacks. One which returns the GLFWwindow for ImGui to use, and another which returns the size of said window.

## Getting Started

### Dependencies

* Python3 - Used for setup scripts
* premake5 - Will be downloaded and extracted as a binary when the setup script is run if it is not found.

### Installing

* Clone the repo recursively and run `setup.bat` for Windows or `setup.sh` for Linux.

## License

This project is licensed under the MIT License - see the LICENSE.md file for details