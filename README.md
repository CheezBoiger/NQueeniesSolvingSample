CS420 - Project 2
Author: Mario Garcia
Date: 5/3/2017
Expected Due Date: 5/15/2017
Instructor: Dr. Fang Tang
Language: C++11



# How to build
CMake is used to build this project, however there are already premade executables for this
program, so there is no need to build from scratch.

In the unlikely event that you are not running this program on Windows 10 x64, you can build 
this project easily with cmake. 

If you have cmake installed, simply:
  1. Go into your command prompt, navigate to the directory of
      where this project is.
  2. Type in the prompt "cmake .", this will trigger cmake to build the 
      solution project for this program using your default compiler. 
  3. Navigate to the solution file (which should be called "N-QueenSolving.sln") 
      and open it.
  4. Select the build type to be in Release mode instead of Debug mode on the top of the 
      tools bar of your Visual Studio IDE. then build the project.
  5. Once done, go to your Solution Explorer tab and right click on NQueenApplication.
      Select "Set as StartUp Project". Then Click to Run the project (which will either be 
      called "Local Windows Debugger" on the top of your Visual Studio IDE or something else 
      along those lines.)

However, if you do have Windows 10 installed, you have a better chance of running a 64 bit version of it
and therefore should have no issue with running the prebuilt program. 

# Running

To Run, simply just run. The board is randomly generated, and the algorithms are automatically run for said board.
If nothing pops up on the console window of the program, chances are it must be taking a ton of time, to which you
may need to close the program by clicking the x icon to close.
