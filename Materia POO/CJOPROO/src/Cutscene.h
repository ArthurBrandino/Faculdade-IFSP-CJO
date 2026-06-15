#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "raylib.h"

class Cutscene {
private:
    Texture2D texture;
    float displayTimer;
    bool canContinue;
    float textAlpha;

public:
    Cutscene();  // Construtor padrão focado na introdução
    ~Cutscene();

    void Update(float deltaTime);
    void Draw();
    bool ShouldAdvance(); // Retorna true quando o jogador clica para iniciar o jogo
};

#endif