# Trigonometry Solver will solve for your missing sides or angles of a triangle

### Usage
The user must enter a valid solvable triangle conforming to at least one of the following conformations: Side-Side-Side, Side-Angle-Side, Side-Side-Angle, Angle-Side-Angle, and Angle-Angle-Side.

### Prerequisites
Before you begin, make sure you have:

C++ Compiler (GCC, Clang, or MSVC)
CMake (recommended for cross-platform builds)
wxWidgets Library (installed manually or built from source)
Git (to clone the repository)

git clone <your-repository-url>
cd <your-project-folder>

### Steps
1. Install MSYS2
Download and install MSYS2 from:
🔗 https://www.msys2.org/

After installation, open MSYS2 MSYS from the Start menu and update the system:

2. Install Required Packages
```pacman -S mingw-w64-x86_64-wxWidgets```

3. Clone the Repository
```
cd ~/projects  # Change to your preferred directory
git clone <your-repository-url>
cd <your-project-folder>
```

4. Build the wxWidgets library
Refer to the following documentation for how to build on your system:
https://docs.wxwidgets.org/3.2/plat_msw_install.html

Run:
```where wx-config```
To confirm the installation. 

5. Compile and Run the Application:
```g++ -o TrigSolver.exe TrigSolver.cpp Triangle.cpp TrigFunctions.cpp Globals.cpp (wx-config --cxxflags --libs)```

```./TrigSolver.exe```
