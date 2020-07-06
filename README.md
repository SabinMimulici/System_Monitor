# System_Monitor
System monitor based on htop. It is an interactive process viewer for Unix Systems.

The project uses ncurses.
- ncurses is a library that facilitates text-based graphical output in the terminal. 

This project uses Make. 

- build: compiles the source code and generates an executable (make build)
- debug: compiles the source code and generates an executable, including debugging symbols (make debug)
- clean: deletes the build/ directory, including all of the build artifacts (make clean)

Install ncurses: 
sudo apt install libncurses5-dev libncursesw5-dev

Build the project : make build
Run the program: ./build/monitor


