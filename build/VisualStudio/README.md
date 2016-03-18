# User Manual for the Windows Version of the QX-Simulator Project
Author: Xiang Fu

Email: gtaifu@gmail.com

## Introduction
The QX-Simulator was first developed in Linux OS with G++ compiler by [Nader Khammassi](nader.khammassi@gmail.com). Xiang Fu ported the QX-Simulator into Windows OS with Microsoft Visual C++ compiler. MinGW compiler is not supported. This Windows version is targeted to be cross-platform. However, no test in Linux is done yet.


## File Structure
This project contains the following folder /files:
- /bin/: The binary generated will be put in this folder. Linux/Mac/Windows version will be put in corresponding folders.
- /build/: The folder contains all project file required in Windows. Makefile and configure file used in Linux/Mac will be move to this folder in the future, too.
- /doc/: documentation.
- /src/: This folder contains all the source files (*.cpp, *.h) and some dll/lib files. Only part of the files are used in the project. Folder clean is required in the future.
  - /src/xpu-0.15/: The folder contains the xpu platform, which is for bottom layer memory management and parallel execution speedup.
  - /src/core/: This folder contains files that implement the basic functions required for the simulator.
  - /src/tools/: simulator.cc contains the **main** function for the windows version.
  - /src/qcode/: quantum_code_loader.h and strings.h are used for reading qasm fie.
  - /src/qasm/: not used in Windows version till now.
  - /src/circuit/: contains many testing circuits that can be read and executed by the simulator executable.
- **NOTE**: All network-related functions are not enabled in the Windows version now. More time is required to debug it.

## Preparation
To use /develop the windows version of the simulator, the following work is required:
1. Install Visual Studio 2015 (VS2015)
- Go to: https://www.visualstudio.com/downloads/download-visual-studio-vs
- Download Community Free. Community Free version is enough for our purpose. Enterprise version would be better, only if you have the license.
- VS 2015 is suggested, since the project is built with 2015. With earlier version of VS, e.g. VS2012, the project configuration is not ensured.
2. Prepare **pthread_win**
- copy "\src\xpu-0.1.5\pthread\dll\pthreadVC2.dll" into the folder C:\Windows\
- copy "\src\xpu-0.1.5\pthread\lib\pthreadVC2.lib" into the Visual Studio installation folder: e.g. "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib".If older version of VS is used, then the folder name would be with another number instead of **14.0**.
- Configure pthread in Visual Studio
  - In Visual Studio, open the project qx_simulator.sln, right click on the project (not the solution) and choose properties -> Linker -> input group -> Additional Dependencies, in the dialog, input *pthreadVC2.lib* and click OK.
3. Install **Boost**
- Download boost: http://www.boost.org/users/history/version_1_60_0.html
- By extracting the file, you will get the folder "boost_1_60_0\", copy or move it to  "C:\Program Files\boost\boost_1_60_0\"
- Configure boost in Visual Studio:
  - In Configuration Properties > C/C++ > General > Additional Include Directories, enter the path to the Boost root directory "C:\Program Files\boost\boost_1_60_0"
  - In Configuration Properties > C/C++ > Precompiled Headers, change Use Precompiled Header (/Yu) to Not Using Precompiled Headers.
4. Add compiler option
- **NOTE**: If everything works properly, the configuration should already be set in the  qx_simulator.sln file you get from the repository. So you only need to check the following configurations.
- In Configuration Properties > C/C++ > Command Line> Additional Options, add the following line (Preprocessor Definition):
  - /D_SCL_SECURE_NO_WARNINGS
- In Configuration Properties > C/C++ > Code Generation -> Enable Enhanced Instruction Set: set to Streaming SIMD Extension 2.
  - Based on the target CPU, it can change to other instructions.

After the above four steps, you should be able to run the project.

More information: gtaifu@gmail.com
