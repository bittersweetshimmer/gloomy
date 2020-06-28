# gloomy
Some kind of safer OpenGL wrappers and convenience namespace.

### Build
```sh
> git submodule update --init --recursive # pull the dependencies
> mkdir build
> cd build
> cmake .. # just a static library
> cmake --build .
```
If you're using Visual Studio then it's `msbuild yadda yadda`. This works fine [on my machine](https://i.imgur.com/f5uGQ.jpg).
```cmd
msbuild gloomy.sln /m
```

### Examples
Check [this](https://github.com/bittersweetshimmer/gloomy-learnopengl) repo.

### 3rd party code
- [bitmask](https://github.com/oliora/bitmask) - Type safe bitmask - `BSL-1.0`
- [glad](https://glad.dav1d.de/) - GL loader-generator

### Acknowledgments
- [LearnOpenGL](https://learnopengl.com/) - great tutorials on modern OpenGL.
