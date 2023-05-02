# file_embedder
a program for easily allowing files to be embedded into a C/C++ application


## Usage

### Windows
For windows, simply grab the binary and run it from the terminal.
If you would like to make changes to the source, simply clone the repo and open the *binaryembedder.sln* in Visual Studio, then compile.


### Linux
For Linux, grab the *embedder.c* and *Makefile* files. Ensure you have *make* installed and run ***make all***, then run the output binary.

### Using the output file
 Create a header file and include the functions below. Name the header file the same as your .c file and place both in the build path of your project, then include the .h file in the code you wish to use the embedded file in.
 #### ex.
 __Content of header__
```C
#pragma once
const char* grab_file(const char* name, size_t* size);
int rebuild_file(const char* d, size_t size);
```
