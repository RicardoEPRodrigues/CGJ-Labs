# [3Engine](https://ricardoeprodrigues.github.io/3Engine/)

[![GitHub tag](https://img.shields.io/github/tag/RicardoEPRodrigues/3Engine.svg?style=flat-square)](https://github.com/RicardoEPRodrigues/3Engine/releases) [![Travis](https://img.shields.io/travis/RicardoEPRodrigues/3Engine.svg?style=flat-square)](https://travis-ci.org/RicardoEPRodrigues/3Engine) [![AppVeyor](https://ci.appveyor.com/api/projects/status/3kcxkyeddhu9qhuq?svg=true)](https://ci.appveyor.com/project/RicardoEPRodrigues/3engine)

Game Engine **3Engine** using OpenGL made for a class on *Computer Graphics for Games*.

Fun feature: uses JSON files for configuration with realtime change detection.

This project depends on OpenGL, GLEW and SDL2. While the first is normally installed by default in most systems the latter libraries are not.

You might want to visit the [Release page](https://github.com/RicardoEPRodrigues/3Engine/releases) and check out pre-built versions of the engine.

**CONTRIBUTIONS: Help make the library more usable. Mainly regarding using pre-built versions.**

---

## How to Run in Linux?

### Setup

To add all the necessary dependencies you need to run the ```Setup.sh``` file. It will install some dependencies on Ubuntu/Debian Oses and download and prepare GLEW and SDL2 libraries.

```
./Setup.sh
```

#### Non-Ubuntu OSes Dependencies

If you don't use a Ubuntu/Debian OS, please install the following dependencies.

* g++
* libxmu-dev
* libxi-dev
* cmake
* libgl1-mesa-dev
* libjpeg-dev
* libtiff-dev
* libwebp-dev
* libfreetype6-dev

### Compiling

In Linux we created a CMake project and currently use CLion IDE. To open a project open the `CMakeLists.txt` file with CLion.

You can use any other IDE that supports CMake (CodeLite, Kdevelop, etc.).

If you wish to compile it using the terminal follow this steps:

```bash
cd project-folder
mkdir -p intermediate
cd intermediate
cmake .. -DCMAKE_BUILD_TYPE=Debug
make LightScene # This is a specific example scene using BRDF
```

The JSON config files are copied from `config` folder to a same named folder on the build folder.

### Run

Either press Play in Clion or using the terminal follow these steps:

```bash
cd bin/debug/
./LightScene
```

### AppImage (Testing)

An AppImage allows me to build an executable and distribute it more easily. Therefore you may see Releases using AppImage. If you wish to compile the Engine into an AppImage follow the compiling steps, but replace the last one with `make AppImage`:

```bash
cd project-folder
mkdir -p intermediate
cd intermediate
cmake .. -DCMAKE_BUILD_TYPE=Debug
make AppImage
```

To run in just double-click on the `3Engine.AppImage` file in the `bin/AppImage` folder.

## How to Run in Windows?

### Dependencies

The inclusion of the said libraries are needed, yet dependencies are ignored to reduce the size of the project. To get the project to run follow the steps.

1. Download precompiled builds for MSVC (or compile it yourself) 
        
    * [SDL2](https://github.com/RicardoEPRodrigues/Dependencies/raw/master/SDL2-msvc.zip)
    * [SDL2-image](https://github.com/RicardoEPRodrigues/Dependencies/raw/master/SDL2-image-msvc.zip)
    * [GLEW](https://github.com/RicardoEPRodrigues/Dependencies/raw/master/glew-msvc.zip)

1. Create a folder named `dependencies` and place inside the libraries. Rename them as shown:

    * SDL2-msvc
    * SDL2-image-msvc
    * glew-msvc

### Compiling

In Windows we created a Visual Studio Project. We recommend Visual Studio 2017 Community edition. To open the project just double-click the `3Engine.sln`.

Set the configuration to `Debug` or `Release`, and the platform to `x64`. Then just press Play to run.

The default build folder is in 'bin' folder. `.dll` files from *SDL2* and *GLEW* are copied to the build folder.

The JSON config files are copied from `config` folder to a same named folder on the build folder.

### Run

Either press Play in Visual Studio or double-click the compiled executable in the `bin` folder.


## How to Run in Mac OS X?

### Dependencies

The inclusion of the said libraries are needed, yet dependencies are ignored to reduce the size of the project. To get the project to run follow the steps.

1. [Install SDL2 Development Libraries](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php)

1. Following similar steps, install [SDL-image Development Libraries](https://www.libsdl.org/projects/SDL_image/).

1. Using [Homebrew](https://brew.sh), install GLEW:

    ```bash
    brew install glew
    ```

### Compiling

Follow the Linux instructions.

### Run

Follow the Linux instructions.
