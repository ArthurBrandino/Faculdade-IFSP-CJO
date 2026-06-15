#ifndef BADENDING_H
#define BADENDING_H

#include "raylib.h"

class BadEnding {
private:
    Texture2D texture;
    float displayTimer;
    bool canContinue;

public:
    BadEnding();
    ~BadEnding();

    void Update(float deltaTime);
    void Draw();
    bool ShouldReturn(); // Retorna true quando o jogador decide voltar ao menu
};

#endif