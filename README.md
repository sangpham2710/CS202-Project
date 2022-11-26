# CS202-Project

## Setup

#### You should have `Git Bash` and `CMake` already configured for this to work.

```bash
git clone https://github.com/sangpham2710/CS202-Project.git
cd CS202-Project
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -S .. -B .
```

Go into the `build/` folder and open `CS202-Project.sln` using Visual Studio.

Set `CS202-Project` as the Startup project.

Finally, try to build and run the program using Visual Studio.

## Project Structure

```
CS202-Project/
├─ src/                 // contains source code, header files, implementation files
│  ├─ main.cpp
├─ assets/              // contains assets
│  ├─ music/            // contains music
│  ├─ sounds/           // contains sounds
│  ├─ textures/         // contains textures
├─ CMakeLists.txt
├─ .gitignore
├─ README.md
```
