# CG

Install cmake and cmake-qt gui
– sudo apt-get install cmake
– sudo apt-get install cmake-qt-gui

• Install freeglut
– sudo apt-get install freeglut3-dev

Note: IF fail to compile freeglut try:
cd /usr/include/X11/extensions
sudo ln –s XI.h XInput.h

• Check OpenGL version
– glxinfo | grep "OpenGL“
– (sudo apt-get install mesa-utils)



How to run in Linux:

1- Open CMake from a terminal window : cmake-gui &
2- In the CMake window:
  -"Where is the source code": input de project folder
  -"Where to build the sources":a new subfolder
3- Press "Configure" and "Configurate"  
4- Open a terminal in the build folder and type: make
5- To run the app : ./generator <args> or ./engine <args>
