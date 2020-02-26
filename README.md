# gloomy ![appveyor](https://img.shields.io/appveyor/build/bittersweetshimmer/gloomy?style=flat-square)
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
