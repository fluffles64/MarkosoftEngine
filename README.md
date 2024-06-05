# Markosoft Engine

Markosoft Engine is a versatile custom engine developed using C++ and SDL2. It offers a robust framework to develop simple games.

Although originally designed for cellular automata games, it can be utilized to create many types of games. It comes pre-loaded with a sample game - a *falling sand* sandbox type of game, where users can mess around with diverse materials each with different physics properties. The falling sand algorithm is based in *[Conway's Game of Life](https://conwaylife.com/)*.

Developed as part of a university assignment for the *Game Engines* class, this project actually earned me a 10!

## Media

<div style="display:flex; justify-content:center;">
    <img src="https://github.com/fluffles64/MarkosoftEngine/assets/61605339/ce765652-e5b6-42c4-ab14-02a4916c0371" alt="Gif" style="width: 100%;"/>
</div>

## Features

- **Robust Design**: Splits tasks into different managers, using the *singleton* design pattern: Physics, Rendering, Input...
- **Multithreading Capabilities**: Features multithreading to render thousands of concurrent objects with support of up to 4 threads.
- **SDL2 API**: Uses SDL2 for rendering graphics and handling user input.
- **Sample Game**: Includes a demonstration game to illustrate the engine's capabilities and functionalities.

## Changelog

- **v1.0.0**:
  - Addressed a known issue that caused FPS to drop when rendering too many textures at once.

## Requirements

- **C++**: 17 or later
- **SDL2**: [v2.0.16](https://github.com/libsdl-org/SDL/releases)
- **SDL2_image**: [v2.0.5](https://github.com/libsdl-org/SDL_image/releases)
- **SDL2_ttf**: [v2.0.15](https://github.com/libsdl-org/SDL_ttf/releases)

## Installation and Running

### Option 1: Pre-Packaged Zip (Includes Libraries)

1. Download the latest zip file from the [releases page](https://github.com/fluffles64/MarkosoftEngine/releases).
2. Extract the zip file to your desired location.
3. Navigate to the location of the executable: `Project > Debug > Debug`.
4. Run *Game.exe*.

### Option 2: Build from Source

1. Clone the repository:
    ```bash
    git clone https://github.com/fluffles64/MarkosoftEngine.git
    cd MarkosoftEngine
    ```

2. Install the required dependencies:
    - Ensure you have C++17 or later installed.
    - Install SDL2, SDL2_image, and SDL2_ttf from the links provided in the Requirements section, or install them directly using [vcpkg](https://vcpkg.link/ports/sdl2).

3. Build the project:

   **If you are using Visual Studio**:
   
   - Add the SDL2, SDL2_image, and SDL2_ttf */include* folders into `Configuration Properties > VC++ Directories > Include Libraries`.
   - Similarly, add the SDL2, SDL2_image, and SDL2_ttf *.lib* files into `Linker > Input > Additional Dependencies`.
   - Add the SDL2, SDL2_image, and SDL2_ttf */lib/x64* folders into `Configuration Properties > VC++ Directories > Library Directories`.
   - Finally, make sure you copy and paste the SDL2, SDL2_image, and SDL2_ttf *.dll* files into the same directory the game executable is at.
   - It is recommended to create two separate solutions, one for the engine and one for the game. You can add the *MarkosoftEngine* solution as a dependency in `Build Dependencies > Project Dependencies`.

    **If you are using CMake or vcpkg**:

   Create the appropriate *CMakeLists.txt* file and set up *environment variables* or a *CMakePresets.json* file. You can refer to examples and best practices in the following resources:
   [CMake](https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/) and
   [vcpkg](https://github.com/njakob/vcpkg-sdl2-example).

    - Build the project:
        ```bash
        mkdir build
        cd build
        cmake ..
        make
        ```
        
    - Run the game:
        ```bash
        ./game
        ```

## Contributing

1. **Fork the repository**.

2. **Create a new branch**:

    ```bash
    git checkout -b feature/YourFeature
    ```

3. **Commit your changes**:

    ```bash
    git commit -m 'Add some feature'
    ```

4. **Push to the branch**:

    ```bash
    git push origin feature/YourFeature
    ```

5. **Open a pull request**.

## License

This project is licensed under the [MIT License](LICENSE.md).
