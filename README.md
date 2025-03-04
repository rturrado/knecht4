# knecht4

A Connect 4 game implementation. And a tribute to Lakers number 4 Dalton Knecht.

## Requirements

- `CMake` >= 3.22
- `git`
- `Python` 3.x plus `pip`, with the following pacakge:
  - `conan` >= 2.0 

## Build

This version of knecht4 can only be compiled via the Conan package manager.
You will need to create a default profile before using it for the first time.
The installation of dependencies, as well as the compilation, can be done in one go.

```
git clone https://github.com/rturrado/knecht4.git
cd knecht4
conan profile detect
conan build . -pr:a=conan/profiles/tests-debug-gcc-linux-x64 -b missing
```

## Run

```
./build/Debug/src/knecht4
```

## Test

```
./build/Debug/test/knecht4-test
```

## Docker

Alternatively, if you have `docker` installed, you can build the application directly
(without installing any required dependency):

```
rm -fr build
docker build -t knecht4 .
docker run -it knecht4
```

And then execute it, together with the tests:

```
$ ./build/Debug/src/knecht4
$ ./build/Debug/test/knecht4-test
```
