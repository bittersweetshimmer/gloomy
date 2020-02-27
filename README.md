# gloomy ![appveyor](https://img.shields.io/appveyor/build/bittersweetshimmer/gloomy?style=flat-square)
Some kind of safer OpenGL wrappers and convenience namespace.

### Build
```sh
> mkdir build
> cd build
> cmake .. # just a static library
> make -j8 # on Linux/or if you're using make generator
```
If you're using Visual Studio then it's `msbuild yadda yadda`. This works fine [on my machine](https://i.imgur.com/f5uGQ.jpg).
```cmd
msbuild gloomy_all.sln /m
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
