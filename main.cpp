#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color green_1 {173, 203, 96, 255};
Color green_2 {43, 51, 24, 255};

int cellsize = 50;
int cellcount = 15;

class Grass {
public: 
deque<Vector2> grassspace = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9},
                             Vector2{6,10}, Vector2{5,10} ,Vector2{4,10},
                             Vector2{6,11}, Vector2{5,11}, Vector2{4,11}};

void Draw() {
    for(unsigned int i = 0; i < grassspace.size(); i++) {
        float x = grassspace[i].x;
        float y = grassspace[i].y;
        DrawRectangle(x*cellsize, y*cellsize, (float)cellsize, (float)cellsize, green_2);
    }
}
};

class Player {
    public:
    Vector2 startpos = {3,3};
    Vector2 position = startpos;
    Vector2 direction = {0, 0};
    
    void Draw() {
        position = Vector2Add(position, direction);
        DrawRectangle(position.x * cellsize, position.y * cellsize, cellsize, cellsize, WHITE);
        direction = {0, 0};
    }

    void Update() {
        if(IsKeyPressed(KEY_UP)) {
            direction = {0, -1};
        }
        if(IsKeyPressed(KEY_DOWN)) {
            direction = {0, 1};
        }
        if(IsKeyPressed(KEY_RIGHT)) {
            direction = {1, 0};
        }
        if(IsKeyPressed(KEY_LEFT)) {
            direction = {-1, 0};
        }
    }
};

class Game {
public:
Player player = Player();
Grass grass = Grass();

bool touching_grass_prev;

void Draw() {
    grass.Draw();
    player.Draw();
    
}

void Update() {
    player.Update();
}

void CollisionWithGrass() {
    bool is_touching_grass = false;

    Rectangle playerRect = {
        player.position.x * cellsize,
        player.position.y * cellsize,
        (float)cellsize,
        (float)cellsize
    };
    
    for (unsigned int i = 0; i < grass.grassspace.size(); i++) {
        Vector2 grassCell = grass.grassspace[i];

        Rectangle grassRect;
        grassRect.x = grassCell.x * cellsize;
        grassRect.y = grassCell.y * cellsize;
        grassRect.width = (float)cellsize;
        grassRect.height = (float)cellsize;

        
        if (CheckCollisionRecs(playerRect, grassRect)) {
            is_touching_grass = true;
            break; 
        }
    }

          

    if(is_touching_grass && !touching_grass_prev) {
        cout << "grass touched" << endl;
        touching_grass_prev = true;
    }

    if(!is_touching_grass) {
        touching_grass_prev = false;
    }
}
};

int main() 
{
    InitWindow(cellsize*cellcount, cellsize*cellcount, "POKEMON");
    SetTargetFPS(24);

    Game game;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        
        ClearBackground(green_1);
        game.Draw();
        game.Draw();

        game.Update();
        game.CollisionWithGrass();


        EndDrawing();
    }
    
    CloseWindow(); 
}