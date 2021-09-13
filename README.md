# gfx_extensions
This application provides the default display's extension list of EGL and GLES.

## How to build

```
$ mkdir build && cd build
$ conan install ..
$ cmake .. -DCMAKE_MODULE_PATH=`pwd`
$ make
```

