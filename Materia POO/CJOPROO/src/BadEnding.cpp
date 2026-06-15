#include "BadEnding.h"
#include <iostream>
#include <cmath>

BadEnding::BadEnding() {
    // Carrega a imagem do final ruim (coloque este arquivo na pasta resources/player/)
    texture = LoadTexture("resources/cutscenes/Bad_ending_cutscene.png");
   
    
    if (texture.id == 0) {
        std::cout << "[ERRO] A Raylib nao encontrou a imagem em: resources/player/BadEnding_cutscene.png" << std::endl;
    }

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    displayTimer = 0.0f;
    canContinue = false;
}

BadEnding::~BadEnding() {
    UnloadTexture(texture);
}

void BadEnding::Update(float deltaTime) {
    displayTimer += deltaTime;

    // Aguarda 1 segundo antes de liberar o botão (dá tempo do jogador processar a derrota)
    if (displayTimer > 1.0f) {
        canContinue = true;
    }
}

void BadEnding::Draw() {
    // Desenha a imagem de fim de jogo em tela cheia
    DrawTexturePro(
        texture,
        Rectangle{ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
        Rectangle{ 0.0f, 0.0f, 1280.0f, 720.0f },
        Vector2{ 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    // --- LÓGICA DA COR DINÂMICA (EFEITO TERMOCROMÁTICO VERMELHO/SANGUE) ---
    float tempo = GetTime() * 4.0f; // Um pouco mais rápido para passar sensação de perigo/erro
    
    // Focado em tons de Vermelho (R alto fixo) com variações agressivas nos outros canais
    unsigned char r = (unsigned char)((sinf(tempo) * 0.2f + 0.8f) * 255); // Oscila apenas entre vermelho vivo e escuro
    unsigned char g = (unsigned char)((sinf(tempo + 1.0f) * 0.1f + 0.1f) * 255); 
    unsigned char b = (unsigned char)((sinf(tempo + 2.0f) * 0.1f + 0.1f) * 255);
    
    Color corDerrotaDinamica = { r, g, b, 255 };

    // --- RENDERIZAÇÃO DO TEXTO ---
    if (canContinue) {
        const char* textoPrompt = "APERTE ENTER PARA VOLTAR AO MENU";
        
        DrawText(
            textoPrompt, 
            640 - MeasureText(textoPrompt, 24) / 2, 
            620, 
            24, 
            corDerrotaDinamica
        );
    }
}

bool BadEnding::ShouldReturn() {
    if (!canContinue) return false;

    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || 
            IsKeyPressed(KEY_SPACE) || 
            IsKeyPressed(KEY_ENTER));
}