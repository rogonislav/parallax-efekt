#include <raylib.h>
#include <string>
#include <iostream>
#include <vector>
#include <format>

// '* 240' -> nasobime target FPS, aby sme docielili rovnaku rychlost pri kazdom fps (nie len pri 240)
constexpr float FG1_VEL = 48;   // 0.2f * 240
constexpr float FG2_VEL = 96;   // 0.4f * 240
constexpr float FG3_VEL = 144;  // 0.6f * 240

class TextureManager {
private:
    std::vector<Texture2D> textures;
public:
    Texture2D Load(const std::string& path) {
        Texture2D tex = LoadTexture(path.c_str());
        textures.push_back(tex);
        return tex;
    }

    ~TextureManager() {
        for(auto& tex : textures) {
            UnloadTexture(tex);
        }
    }
};

class ParalaxProp {
private:
    Texture2D tex;
    Vector2 pos1, pos2;
    float vel; // TODO: zovseobecnit -> spravit cez Vector2 -> podpora pre vsetky osi, nielen os x; 
public:
    ParalaxProp(Texture2D _tex, float _vel, Vector2 _pos1): tex(_tex), vel(_vel), pos1(_pos1) {
        // pri zovseobcnovani venovat pozornost
        pos2 = { pos1.x + tex.width, pos1.y };
    }

    void Update(float delta) {
        // 'vel.x' je zakomentovane, pretoze by to bolo FPS-dependent -> pri vyssich FPSkach by sa to pohybovalo rychlejsie
        pos1.x -= vel * delta; //vel.x;
        pos2.x -= vel * delta; //vel.x;

        // PRIPRAVENE PRE ZOVSEOBECNENIE:
        /*
        pos1.y -= vel.y;
        pos2.y -= vel.y;
        */

        if(pos1.x < -tex.width) {
            pos1.x = pos2.x + tex.width;
        }
        if(pos2.x < -tex.width) {
            pos2.x = pos1.x + tex.width;
        }
    }

    void Draw() {
        DrawTexture(tex, pos1.x, pos1.y, WHITE);
        DrawTexture(tex, pos2.x, pos2.y, WHITE);
    }
};

void ParallaxUaD(std::vector<ParalaxProp>& paralaxProps, float delta) {
    for(auto& pair : paralaxProps) {
        if(!IsKeyDown(KEY_SPACE))
            pair.Update(delta);
        pair.Draw();
    }
}

int main() {
    InitWindow(800, 500, "Parallax");
    int targetFPSindex = 0;

    // DOSTUPNE FPS -> 24, 30, 60, 120, 144, 240
    auto fpsVals = std::to_array({24, 30, 60, 120, 144, 240});
    SetTargetFPS(fpsVals[targetFPSindex]);

    TextureManager texMgr;
    std::vector<ParalaxProp> paralaxProps;
    paralaxProps.emplace_back(texMgr.Load("textury/parallax/prlx_bg.png"), 0.0f, Vector2{0.0f, -250.0f});
    paralaxProps.emplace_back(texMgr.Load("textury/parallax/prlx_fg1.png"), FG1_VEL, Vector2{0.0f, -250.0f});
    paralaxProps.emplace_back(texMgr.Load("textury/parallax/prlx_fg2.png"), FG2_VEL, Vector2{0.0f, -250.0f});
    paralaxProps.emplace_back(texMgr.Load("textury/parallax/prlx_fg3.png"), FG3_VEL, Vector2{0.0f, -250.0f});

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ENTER)) {
            TakeScreenshot("screenshot.png");
        }

        // RYCHLOST OBJEKTOV JE NEZAVISLY OD FPS, PRETOZE POUZIVAME DELTU
        if(IsKeyPressed(KEY_RIGHT)) {
            targetFPSindex++;
            if(targetFPSindex >= fpsVals.size())
                targetFPSindex = fpsVals.size() - 1;
            SetTargetFPS(fpsVals[targetFPSindex]);
        }
        if(IsKeyPressed(KEY_LEFT)) {
            targetFPSindex--;
            if(targetFPSindex < 0)
                targetFPSindex = 0;
            SetTargetFPS(fpsVals[targetFPSindex]);
        }

        BeginDrawing();

        ClearBackground(WHITE);

        ParallaxUaD(paralaxProps, GetFrameTime());
        
        DrawText(std::format("MAX: {}", fpsVals[targetFPSindex]).c_str(), 4, 4, 20, RED);
        DrawText(std::format("FPS: {}", GetFPS()).c_str(), 4, 25, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}