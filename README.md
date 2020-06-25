# Esdiel

Programming study project repository that contains engine and game made in it.

### Building

Clone this repository and follow steps below to generate project files and build executable.
Then just run executable in `example` folder.

##### Windows

Visual Studio
```bash
tools/premake5.exe vs2019
# open Visual Studio solution and build
```

MinGW with git-bash
```bash
./tools/premake5.exe gmake2
make # config=release
```

##### Linux

```bash
sudo apt install g++ libsdl2-dev
./tools/premake5 gmake2
make # config=release
```

### Issues

Application may not work properly on some hardware configurations, especially with integrated graphics cards.
