#include <raylib.h>
#include <string>
#include <iostream>

Texture2D prlxBG;
Texture2D prlxFG1;
Texture2D prlxFG2;
Texture2D prlxFG3;

Texture2D prlxFG1_copy;
Texture2D prlxFG2_copy;
Texture2D prlxFG3_copy;

float prlxFG1_vel = 0.2f;
float prlxFG2_vel = 0.4f;
float prlxFG3_vel = 0.6f;

float FG1_curPos = 0.0f;
float FG2_curPos = 0.0f;
float FG3_curPos = 0.0f;

float FG1_copy_curPos = 1600.0f;
float FG2_copy_curPos = 1600.0f;
float FG3_copy_curPos = 1600.0f;

void Parallax(){

    //pohyb textur foreground layerov pozadia
    FG1_curPos -= prlxFG1_vel;
    FG1_copy_curPos -= prlxFG1_vel;
    DrawTexture(prlxFG1,FG1_curPos,-250,WHITE);
    DrawTexture(prlxFG1_copy,FG1_copy_curPos,-250, WHITE);

    FG2_curPos -= prlxFG2_vel;
    FG2_copy_curPos -= prlxFG2_vel;
    DrawTexture(prlxFG2,FG2_curPos,-250,WHITE);
    DrawTexture(prlxFG2_copy,FG2_copy_curPos,-250, WHITE);

    FG3_curPos -= prlxFG3_vel;
    FG3_copy_curPos -= prlxFG3_vel;
    DrawTexture(prlxFG3,FG3_curPos,-250,WHITE);
    DrawTexture(prlxFG3_copy,FG3_copy_curPos,-250, WHITE);
    
    //cyklacia textur 
    if (FG1_curPos <= -(prlxFG1.width)){
        FG1_curPos = prlxFG1.width;
    }
    if (FG1_copy_curPos <= -(prlxFG1_copy.width)){
        FG1_copy_curPos = prlxFG1_copy.width;
    }

    if (FG2_curPos <= -(prlxFG2.width)){
        FG2_curPos = prlxFG2.width;
    }
    if (FG2_copy_curPos <= -(prlxFG2_copy.width)){
        FG2_copy_curPos = prlxFG2_copy.width;
    }

    if (FG3_curPos <= -(prlxFG3.width)){
        FG3_curPos = prlxFG3.width;
    }
    if (FG3_copy_curPos <= -(prlxFG3_copy.width)){
        FG3_copy_curPos = prlxFG3_copy.width;
    }

    if (IsKeyDown(KEY_SPACE)){
        prlxFG1_vel = 0.0f;
        prlxFG2_vel = 0.0f;
        prlxFG3_vel = 0.0f;
    }else{
        prlxFG1_vel = 0.2f;
        prlxFG2_vel = 0.4f;
        prlxFG3_vel = 0.6f;
    }
}

void TextureManager(){
    //loadovanie textur parallax pozadia 2-krát -> 2 instances, jedno zajde za kameru druhe je na kamere
    prlxBG = LoadTexture("textury/parallax/prlx_bg.png");

    prlxFG1 = LoadTexture("textury/parallax/prlx_fg1.png");
    prlxFG2 = LoadTexture("textury/parallax/prlx_fg2.png");
    prlxFG3 = LoadTexture("textury/parallax/prlx_fg3.png");

    prlxFG1_copy = LoadTexture("textury/parallax/prlx_fg1_copy.png");
    prlxFG2_copy = LoadTexture("textury/parallax/prlx_fg2_copy.png");
    prlxFG3_copy = LoadTexture("textury/parallax/prlx_fg3_copy.png");
}

int main(){
    InitWindow(800,500,"Parallax");
    SetTargetFPS(240);

    TextureManager();    

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        //vykreslovanie textury pozadia
        DrawTexture(prlxBG,0,-250,WHITE);

        Parallax();

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)){
            TakeScreenshot("screenshot.png");
        }
    }

    CloseWindow();
    return 0;
}