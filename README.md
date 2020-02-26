# gloomy
Some kind of safer OpenGL wrappers and convenience namespace.

### Build
```sh
> mkdir build
> cd build
> cmake .. # just a static library
> make -j8 # or msbuild yadda yadda if you're using Visual Studio.
```

### Examples
All examples can be found [here](https://github.com/bittersweetshimmer/gloomy-learnopengl).
```sh
> git submodule update --init --recursive
> mkdir build
> cd build
> cmake .. -D GLOOMY_DEBUG:BOOL=TRUE -D GLOOMY_EXAMPLES:BOOL=TRUE # examples and error checking
> make -j8
```

### Acknowledgments
- [LearnOpenGL](https://learnopengl.com/) - great tutorials on modern OpenGL.
