#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define GRID_SIZE 12
#define EMPTY '.'
#define OBSTACLE 'O'
#define TREASURE 'T'
#define PLAYER 'P'

typedef struct {
    int x;
    int y;
} Position;

char grid[GRID_SIZE][GRID_SIZE];
Position player;
Position treasure;

void initGrid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = EMPTY;
        }
    }
}

void printGrid() {
    printf("\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isValidPosition(int x, int y) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
}

bool isReachable(Position start, Position end) {
    bool visited[GRID_SIZE][GRID_SIZE] = {false};
    Position queue[GRID_SIZE * GRID_SIZE];
    int front = 0, rear = 0;
    
    queue[rear++] = start;
    visited[start.y][start.x] = true;
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    while (front < rear) {
        Position current = queue[front++];
        
        if (current.x == end.x && current.y == end.y) {
            return true;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (isValidPosition(nx, ny) && !visited[ny][nx] && grid[ny][nx] != OBSTACLE) {
                visited[ny][nx] = true;
                queue[rear++] = (Position){nx, ny};
            }
        }
    }
    
    return false;
}

void generateGrid() {
    do {
        initGrid();
        
        // Place obstacles (20% of grid)
        int obstacleCount = (GRID_SIZE * GRID_SIZE) / 5;
        for (int i = 0; i < obstacleCount; i++) {
            int x, y;
            do {
                x = rand() % GRID_SIZE;
                y = rand() % GRID_SIZE;
            } while (grid[y][x] != EMPTY);
            grid[y][x] = OBSTACLE;
        }
        
        // Place player
        do {
            player.x = rand() % GRID_SIZE;
            player.y = rand() % GRID_SIZE;
        } while (grid[player.y][player.x] != EMPTY);
        grid[player.y][player.x] = PLAYER;
        
        // Place treasure
        do {
            treasure.x = rand() % GRID_SIZE;
            treasure.y = rand() % GRID_SIZE;
        } while (grid[treasure.y][treasure.x] != EMPTY);
        grid[treasure.y][treasure.x] = TREASURE;
        
    } while (!isReachable(player, treasure));
}

bool movePlayer(int dx, int dy) {
    int newX = player.x + dx;
    int newY = player.y + dy;
    
    if (!isValidPosition(newX, newY)) {
        printf("Can't move there - out of bounds!\n");
        return false;
    }
    
    if (grid[newY][newX] == OBSTACLE) {
        printf("Can't move there - obstacle in the way!\n");
        return false;
    }
    
    grid[player.y][player.x] = EMPTY;
    player.x = newX;
    player.y = newY;
    
    if (grid[player.y][player.x] == TREASURE) {
        return true;
    }
    
    grid[player.y][player.x] = PLAYER;
    return false;
}

int main() {
    srand(time(NULL));
    
    printf("=== TREASURE HUNT ===\n");
    printf("Navigate to the treasure (T) using WASD + Enter\n");
    printf("W = Up, S = Down, A = Left, D = Right\n");
    
    generateGrid();
    printGrid();
    
    char move;
    bool won = false;
    
    while (!won) {
        printf("Enter move (WASD): ");
        scanf(" %c", &move);
        
        switch (move) {
            case 'w':
            case 'W':
                won = movePlayer(0, -1);
                break;
            case 's':
            case 'S':
                won = movePlayer(0, 1);
                break;
            case 'a':
            case 'A':
                won = movePlayer(-1, 0);
                break;
            case 'd':
            case 'D':
                won = movePlayer(1, 0);
                break;
            default:
                printf("Invalid move! Use W, A, S, or D.\n");
                continue;
        }
        
        if (!won) {
            printGrid();
        }
    }
    
    grid[player.y][player.x] = PLAYER;
    printGrid();
    printf("Congratulations! You found the treasure!\n");
    
    return 0;
}