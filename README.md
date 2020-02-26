# gloomy
Some kind of safer OpenGL wrappers and convenience namespace.

### Build
```sh
> mkdir build
> cd build
> cmake .. # just a static library
> make -j8 # or msbuild yadda yadda if you're using Visual Studio.
```

##### Examples
All examples are in a separate repo [here](https://github.com/bittersweetshimmer/gloomy-learnopengl).
On Windows you may want to set the proper path to the GLFW static library in `learnopengl/CMakeLists.txt`. Precompiled binaries can be found [here](https://www.glfw.org/download.html).
Most Linux distros have it in their repositories.
```sh
> pacman -S glfw # on Arch Linux
```
Building:
```sh
> git submodule update --init --recursive
> mkdir build
> cd build
> cmake .. -D GLOOMY_DEBUG:BOOL=TRUE -D GLOOMY_EXAMPLES:BOOL=TRUE # examples and error checking
> make -j8
```

### 3rd party code
- [bitmask](https://github.com/oliora/bitmask) - Type safe bitmask - `BSL-1.0`
- [glad](https://glad.dav1d.de/) - GL loader-generator

### Acknowledgments
- [LearnOpenGL](https://learnopengl.com/) - great tutorials on modern OpenGL.
