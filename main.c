#include<stdlib.h>
#include<time.h>

#include"raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define COLS 10
#define ROWS 10

const int screenWidth = 400;
const int screenHeight = 400;

const int cellWidth = screenWidth / COLS;
const int cellHeight = screenHeight / ROWS;

// const char* WindowBox000Text = "Algorithm";
const char* ToogleGroup001Text = "BFS; Dijkstra; A Star";
// Vector2 anchor01 = {600, 264};

int ToggleGroup001Active = 0;
// Rectangle layOutRecs[1] = {
//     (Rectangle){anchor01.x + -600, anchor01.y + -264}
// };

typedef struct {
    int x;
    int y;
    bool IS_containWall;
    bool IS_source;
    bool IS_dest;
} cell_t;

cell_t grid[COLS][ROWS];

void CELL_Draw(cell_t cell);
bool INDEX_IsValid(int x, int y);



int main(){
    srand(time(0));

    InitWindow(screenWidth, screenHeight, "Algorithm");

    for (int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++) {
            grid[i][j] = (cell_t){
                .x = i, 
                .y = j,
                .IS_containWall = false,
                .IS_source = false,
                .IS_dest = false,
            };
        }
    }
    
    bool isDrawingWalls = false;
    bool hasSource = false;
    bool hasDest = false;
    int sourceX, sourceY, destX, destY;

    while(!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isDrawingWalls = true;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDrawingWalls = false;
        }

        if(isDrawingWalls) {
            Vector2 mPos = GetMousePosition();
            int inX = mPos.x / cellWidth;
            int inY = mPos.y / cellHeight;
            Rectangle bound;
            bound.x = grid[inX][inY].x * cellWidth;
            bound.y = grid[inX][inY].y * cellHeight;
            bound.width = cellWidth;
            bound.height = cellHeight;
            if(INDEX_IsValid(inX, inY) && CheckCollisionPointRec(mPos, bound)) {
                grid[inX][inY].IS_containWall = true;
            }
        }
        else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Vector2 mPos2 = GetMousePosition();
            int inX = mPos2.x / cellWidth;
            int inY = mPos2.y / cellHeight;

            if (INDEX_IsValid(inX, inY)) {
                if (!hasSource) {
                    hasSource = true;
                    sourceX = inX;
                    sourceY = inY;
                    grid[inX][inY].IS_source = true;
                } else if (!hasDest) {
                    hasDest = true;
                    destX = inX;
                    destY = inY;
                    grid[inX][inY].IS_dest = true;
                } else {
                    // Clear previous source and destination
                    grid[sourceX][sourceY].IS_source = false;
                    grid[destX][destY].IS_dest = false;
                    hasSource = false;
                    hasDest = false;
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        GuiToggleGroup((Rectangle){-10, -10 , 40, 24}, "BFS; Dijkstra; A Star", &ToggleGroup001Active);

        for(int i = 0; i < COLS; i++){
            for(int j = 0; j < ROWS; j++){
                CELL_Draw(grid[i][j]);
            }
        }

        EndDrawing();
    }

    CloseWindow();


    return 0;
}

void CELL_Draw(cell_t cell){
    if(cell.IS_containWall){
        DrawRectangle(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, YELLOW);
    }
    else if(cell.IS_source){
        DrawRectangle(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, RED);
    }
    else if(cell.IS_dest){
        DrawRectangle(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, BLUE);
    }
    
    DrawRectangleLines(cell.x * cellWidth, cell.y * cellHeight, cellWidth, cellHeight, BLACK);

}

bool INDEX_IsValid(int x, int y) {
    return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}

