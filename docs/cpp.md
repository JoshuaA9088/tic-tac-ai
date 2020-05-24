# Compiling CPP

Cmake is the primary build system for this project.

## Dependencies

-   `ncurses`

-   `cmake`

-   `make`

-   `gcc 9`

Install with:

    sudo apt install cmake libncurses5-dev gcc

## Building (Release)

Create a build directory and `cd` into it:

    mkdir src/cpp/build

    cd src/cpp/build

Generate build scripts with cmake:

    cmake ..

    # Alternatively, create build scripts with debug symbols:

    cmake -DCMAKE_BUILD_TYPE=Debug ..

Compile with `make`:

    make

The binary should be build to `src/cpp/build/bin/tic-tac-cpp.o`

## VSCode Debugging

Here are some helpful tips for setting up a debugger on VSCode.

Ensure `gdb` is installed:

    sudo apt install gdb

1.  Open the **root** of the repository with VSCode.

2.  Create a `launch.json` debug file with the following contents:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/src/cpp/build/bin/tic-tac-cpp.o",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

3.  Add breakpoints wherever you like, and start the debugger with `F5`

> You must still manually compile your projects. Ensure you enable debug symbols when you generate the `cmake`!
