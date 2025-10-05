## 📘 Overview

**Cub3D** is part of the **42 Common Core** and serves as your introduction to **graphics programming**, **raycasting**, and **game development** using the **MiniLibX** library.  

This project involves rendering a 3D-like environment from a 2D map using **raycasting**, allowing a player to navigate inside a maze with real-time perspective and movement.

The **bonus part** extends the base project by adding:
- 🖱️ **Mouse rotation** for smooth view control  
- 🚪 **Doors** that open and close  
- 💫 **Animations** for a more dynamic experience  
- 🧍 **Wall collisions** for realistic player movement

---

## 🧠 Key Concepts

- **Raycasting**: calculating ray intersections with walls to simulate 3D depth.
- **MiniLibX**: a simple graphical library used for window management and pixel drawing.
- **2D to 3D projection**: transforming a 2D map into a 3D perspective.
- **Textures mapping**: applying wall and object textures dynamically.
- **Player movement**: handling movement and rotation via keyboard and mouse inputs.
- **Collision detection**: preventing the player from passing through walls.
- **Interactive elements**: such as animated sprites and opening doors in the bonus part.

---

## 🎮 Controls

| Key | Action |
|-----|---------|
| **W** | Move forward |
| **S** | Move backward |
| **A** | Move left |
| **D** | Move right |
| **← / →** | Rotate view left / right |
| **Mouse movement** | Rotate view (bonus) |
| **ESC** | Exit the game |

---

## ⚙️ Usage

### 🔧 Compilation

Use the provided Makefile to build the project:

```bash
make
```

To compile the **bonus version**, use:
```bash
make bonus
```
### ▶️ Execution
for **mandatory part**, use:
```bash
./cub3D maps/<choose_a_mandatory_map>
```

for **bonus part**, use:
```bash
./cub3d_bonus maps/<choose_a_bonus_map>
```

---

## 🗺️ Map Format (.cub)
Each map defines:

- Textures for walls (N, S, E, W)

- Floor and ceiling colors (RGB)

- Player starting position and orientation

- Map layout using `1` for walls, `0` for empty space, and `D` for doors (bonus)

Example:
```bash
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
1000D1
10N001
111111
```
---

## 📁 Project Structure
```bash
cub3d/
├── includes/
│   ├── cub3d.h              # Header file for the mandatory part
│   └── cub3d_bonus.h        # Header file for the bonus part
│
├── libraries/
│   ├── get_next_line/       # Used for reading map files line by line
│   ├── libft/               # Utility functions library
│   └── minilibx-linux/      # Manages windows, rendering, and input events
│
├── maps/
│   └── *.cub                # Example map configuration files
│
├── srcs/
│   ├── mandatory/           # Source files for the mandatory part
│   │   └── *.c
│   └── bonus/               # Source files for the bonus part (doors, animations, mouse, collisions)
│       └── *.c
│
├── tests/
│   ├── mandatory/           # Tests for mandatory features
│   └── bonus/               # Tests for bonus features
│
├── textures/
│   └── *.xpm                # Textures for walls, doors, and sprites
│
├── Makefile                 # Build rules for mandatory and bonus versions
└── README.md                # Project documentation
```
---

## 📜 License
This project is part of the **42 Common Core** curriculum and created for educational purposes.








