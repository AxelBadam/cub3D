# cub3d

cub3D is a school project that emulates the raycasting techniques used in classic first-person shooter games like Wolfenstein 3D. It creates a 3D perspective from a 2D map and allows you to navigate through maze-like environments. Made with https://github.com/eetukoljonen

![cubegif](https://github.com/AxelBadam/cub3D/assets/110740560/d5b90686-49cc-4ae3-85b3-b5721c58a3ea)



## Features

- Raycasting rendering engine
- Textured walls and sprites
- Player movement with keyboard and mouse input
- Collision detection
- Map parsing from a configuration file
- Adjustable resolution and textures
- Mini-map display

## Installation

1. Check dependencies for the MLX42 graphics library (depends on your OS)

https://github.com/codam-coding-college/MLX42#installing-the-dependencies

2. Clone the cub3D repository:

```$ git clone https://github.com/AxelBadam/cub3d.git```

```$ cd cub3d```

3. Run `make`

If you have 42 homebrew replace this line in the makefile:

```libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"```

-installs and builds the MLX42 and the program

## Usage
   
```
$ ./cub3D test_maps/working_maps/simple_map.cub
```

-use the WASD keys to move forward, backward, and sideways. Right and left arrow to turn.

-press M to toggle mouse turn

-press ESC to exit the game.

-create your own maps or modify the existing ones in the test_maps/working_maps directory with the provided textures.

