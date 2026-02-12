# HTTP LED

This project was designed to integrate my already existing web development skills
with the hardware development skills I am working on. This spins up a simple webserver
using `cpp-httplib` to serve requests that can:

1. Get the "status" of the LED (the GPIO level)
2. Turn the light on
3. Turn the light off

As well, this was the first of the hardware projects I've worked on where I built
it on MacOS during development, pushed it to git, and then pulled and built it on
the target device (the Raspberry Pi 3B+). I started learning about `cmake`, as well
as building out stubs for the `pigpio` library since it isn't buildable on MacOS.

I reused the `GpioPin` class from the `flashing-led` project since it made setting
up GPIO much easier!

## Learnings

- Stubbing hardware dependencies for local compilation/testing
- Basic web servers in C++
- CMake basics
    - CMakeLists.txt
    - CMakePresets.json
    - `cmake --profile default && cmake --build build`
- C++ lambda functions
