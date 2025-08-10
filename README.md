# fractol

A real-time fractal explorer with interactive navigation and dynamic coloring, developed as part of the 42 School curriculum.

## Overview

This project renders beautiful mathematical fractals in real-time using the MLX42 graphics library. It features three different fractal types, multiple color schemes, smooth zooming capabilities, and interactive navigation with optimized rendering performance.

## Features

### Supported Fractals
- **Mandelbrot Set** - The classic fractal with cardioid and bulb optimizations
- **Julia Set** - Configurable with custom complex parameters
- **Phoenix Fractal** - Unique fractal with feedback mechanism

### Interactive Navigation
- **Real-time Movement** - Arrow keys for smooth panning
- **Zoom Controls** - Keyboard (W/S) and mouse scroll wheel
- **Mouse Zoom** - Zoom directly at cursor position
- **View Reset** - Return to default view with R key

### Dynamic Coloring
- **4 Color Modes** - Smooth, Psychedelic, Fire, and Ocean themes
- **Color Shifting** - Manual and automatic color animation
- **Real-time Updates** - Instant color mode switching

### Performance Optimizations
- **Fast Pixel Writing** - Direct memory access for maximum speed
- **Compiler Optimizations** - O3, loop unrolling, and vectorization
- **Safety Checks** - Prevents infinite precision issues
- **Cross-platform** - Linux and macOS support

## Project Structure

```
.
├── Makefile
├── includes/
│   └── fractol.h              # Main header file
├── srcs/
│   ├── main.c                 # Program initialization and main loop
│   ├── mandelbrot.c           # Mandelbrot set implementation
│   ├── julia.c                # Julia set implementation
│   ├── phoenix.c              # Phoenix fractal implementation
│   ├── render.c               # Rendering engine
│   ├── zoom.c                 # Zoom and mouse controls
│   ├── keyboard_utils.c       # Keyboard input handling
│   ├── colors.c               # Color scheme implementations
│   └── parsing.c              # Command-line argument parsing
├── libft/                     # Required libft library (dependency)
└── MLX42/                     # Graphics library (auto-downloaded)
```

## Compilation

### Prerequisites
- A `libft` library in the `./libft/` directory
- CMake (for MLX42 compilation)
- OpenGL development libraries
- GLFW library

### Build Commands
```bash
make            # Compile the program (auto-downloads MLX42)
make clean      # Remove object files
make fclean     # Remove object files, program, and MLX42
make re         # Rebuild from scratch
```

The Makefile automatically detects your operating system and configures the appropriate linking flags.

## Usage

### Command Line Arguments
```bash
# Mandelbrot set
./fractol mandelbrot

# Julia set with custom parameters
./fractol julia [real_part] [imaginary_part]

# Phoenix fractal
./fractol phoenix

# Color mode option (0=smooth, 1=psychedelic, 2=fire, 3=ocean)
./fractol mandelbrot -c 1
```

### Examples
```bash
./fractol mandelbrot
./fractol julia -0.7 0.27015
./fractol julia -0.8 0.156
./fractol phoenix -c 2
```

### Controls
- **Arrow Keys** - Move around the fractal
- **W / S** - Zoom in / Zoom out
- **Mouse Scroll** - Zoom at cursor position
- **1 / 2 / 3 / 4** - Switch between color modes
- **SPACE** - Toggle automatic color shifting
- **R** - Reset to default view
- **ESC** - Exit program

## Implementation Details

- **Mathematical Precision** - Uses double-precision floating-point arithmetic
- **Escape-time Algorithm** - Optimized iteration counting with early termination
- **Memory Safety** - Proper error handling and resource cleanup
- **Numerical Stability** - Prevents overflow and precision loss at extreme zoom levels
- **Standards Compliance** - Follows 42 School coding standards (Norminette)

## Color Schemes

1. **Smooth (0)** - Gradient-based coloring with smooth transitions
2. **Psychedelic (1)** - RGB sine wave patterns for vibrant effects
3. **Fire (2)** - Red-orange-yellow gradient simulating flames
4. **Ocean (3)** - Blue-cyan gradient resembling water depths

## Performance Features

- **Compiler Optimizations** - Advanced GCC flags for maximum performance
- **Direct Pixel Access** - Bypasses MLX42 overhead for faster rendering
- **Cardioid/Bulb Detection** - Skips expensive calculations for known regions
- **Finite Value Checking** - Prevents rendering artifacts from mathematical edge cases

## Author

**nweber** - 42 Heilbronn Student
