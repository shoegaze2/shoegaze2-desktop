# shoegaze2-desktop
*This project is in early development stage*\
Cross-platform audio-processing app for desktop operating systems

# Demo Application
![DemoApp](/imgs/demoapp.gif?raw=true)

# Build Instructions
- Clone the repository:
```
git clone --recursive https://github.com/shoegaze2/shoegaze2-desktop.git
cd shoegaze2-desktop
```
- Run CMake:
```
mkdir build && cd build

cmake ..
# OR
cmake -G "<generator>"
```

- Build: *use selected build tool*
- Before launch: *download Montserrat fonts and place them in executable dir in folder 'fonts'*

# Dependencies
- [glfw](https://github.com/glfw/glfw)
- [glad](https://github.com/Dav1dde/glad)
- [nanovg](https://github.com/shoegaze2/nanovg)
- [portaudio](https://github.com/PortAudio/portaudio)
- [shoegaze2](https://github.com/shoegaze2/shoegaze2)
