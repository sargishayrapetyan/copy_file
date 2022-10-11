Requirements
---
* compiler version -  gcc 9.4.0(C++17) or higher

* libraries - Standard Template Library(STL)

* OS - Linux(tested on Ubuntu)

Build and Usage
---
Steps to build and run the application:

    make

After "make" command executable with name "app" will be created in build/bin directory as well as symbolic link in
current directory with the same name.

    To run tests
    ./app test

    To run with custom files you need to specify input and output files
    ./app 'path/to/input/file' 'path/to/output/file'


Note:
The input files should contain only characters which could be represented in ASCII.
