# PraxisarbeitIPSO

A simple terminal-based treasure hunting game written in C.

## Architecture

The game uses a 2D array (`GRID_SIZE x GRID_SIZE`) to represent the playing field. Key components:

- **Grid Generation**: Randomly places obstacles, player, and treasure on the field
- **Reachability Check**: Uses BFS (Breadth-First Search) to verify the treasure is reachable from the player's starting position
- **Game Loop**: Processes WASD input and updates player position until treasure is found
- **Collision Detection**: Prevents invalid moves (obstacles, boundaries)

Configuration: Change `GRID_SIZE` constant to adjust grid dimensions (default: 12x12).

## Compile & Run

```bash
cd src/
gcc -o treasure_game main.c
./treasure_game
```

## How to Play

**Objective**: Navigate the player (P) to the treasure (T).

**Controls**:
- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right
- Press `Enter` after each move

**Field Legend**:
- `.` - Empty space
- `O` - Obstacle (cannot pass)
- `P` - Player (you)
- `T` - Treasure (goal)

Win by moving the player onto the treasure tile.
