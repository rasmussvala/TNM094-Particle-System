# TNM094 - Particle System

This particle system is a part of the course [TNM094 Media Technology - Bachelor Project](https://studieinfo.liu.se/en/kurs/TNM094/vt-2023) at Linköping University 2023. It is a minimal particle system with a small graphical interface that allows for visually editing parameters. The source code can be found on the [GitLab Repository](https://gitlab.liu.se/tnm094-labs/particlesystem) if permitted.

## Setup instructions
Dependencies:
 - [CMake](https://cmake.org/download/) For cross-platform compiler project generation.
 - [Vcpkg](https://github.com/microsoft/vcpkg) For dependency management
 - C++20 Required, e.g. [Visual Studio](https://visualstudio.microsoft.com/downloads/)


1)  Make a project folder for example 'tnm094'

2)  In the project folder:
    * git clone https://github.com/microsoft/vcpkg 
    * git clone https://github.com/rasmussvala/TNM094-Particle-System.git

2)  Open CMake (we recommend using the GUI here), enter the source path to the particlesystem git repo
    and select one of the "presets" ("MSVC 2022", "Xcode", "Ninja", "Unix Makefiles")
    and hit configure. This will build and the dependencies using vcpkg and make them available to 
    the project. Then the will be configured 

3)  Hit Generate and then Open Project to open the project in your IDE.

4)  Build and run the 'application' executable.

## Application Preview

![particle-system](https://github.com/user-attachments/assets/0ca36f3c-1b84-4f57-a106-e7a4d626ae54)
