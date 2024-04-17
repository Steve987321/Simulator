Simulator
=========

Gravity simulator.

An old project made for school.

## How to setup in Visual Studio 
1.   Clone the repo
2.   Run `premake5.exe vs2022`
3.   Open `simulator.sln` and build

## How to setup on Mac
1.  Clone the repo
2.  Run `premake5 gmake2`
3.  Run `make` to build in **Debug** configuration
4.  Copy the .dylib files in `vendor/SFML/SFML-2.6.1/lib/` to the output directory
5.  Run `bin/<output path>/Simulator`

You might experience errors saying: **no RLPATH's found**.
Set the rlpath by running `install_name_tool -add_rpath @executable_path/. <output path>/Simulator`.

![image](https://github.com/Steve987321/Simulator/assets/88980055/c37f54fa-aaee-4068-87f4-3d787da4a9ea)
