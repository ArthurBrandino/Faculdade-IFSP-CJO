#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "raylib.h"
#include <string>

class GameOver {
private:
    Sound deathSound;
    Sound shutdownSound;
    std::string cabecalho;
    std::string corpoTexto;
    std::string infoTecnica;
    
    // --- NOVAS VARIÁVEIS PARA O SCOREBOARD ---
    int playerScore;
    int malwaresDestruidos;
    float tempoSobrevivido;
    std::string blocoScoreboard;

    bool sonsTocados;
    float blinkTimer;
    bool mostrarTextoClique;

public:
    // Atualizado para receber os parâmetros da gameplay
    GameOver(int score, int malwares, float tempo);
    ~GameOver();

    void Reset();
    void Update(float deltaTime);
    void Draw();
    bool ShouldAdvance();
};

#endif