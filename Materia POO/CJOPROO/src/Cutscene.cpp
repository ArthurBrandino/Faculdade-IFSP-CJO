#include "Cutscene.h"
#include <iostream>
#include <cmath>

Cutscene::Cutscene() {
    // Usando o caminho da pasta player onde o seu teste funcionou!
    texture = LoadTexture("resources/cutscenes/Introducao_cutscene.png");
    
    if (texture.id == 0) {
        std::cout << "[ERRO] A Raylib nao encontrou a imagem em: resources/player/Introducao_cutscene.png" << std::endl;
    }

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    displayTimer = 0.0f;
    textAlpha = 0.0f;
    canContinue = false;
}

Cutscene::~Cutscene() {
    UnloadTexture(texture);
}

void Cutscene::Update(float deltaTime) {
    displayTimer += deltaTime;

    // Proteção de 0.5s para evitar pulos acidentais ao sair do menu
    if (displayTimer > 0.5f) {
        canContinue = true;
    }

    if (canContinue && textAlpha < 1.0f) {
        textAlpha += deltaTime * 2.0f;
        if (textAlpha > 1.0f) textAlpha = 1.0f;
    }
}

void Cutscene::Draw() {
    // Renderiza a imagem na tela cheia (1280x720)
    DrawTexturePro(
        texture,
        Rectangle{ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
        Rectangle{ 0.0f, 0.0f, 1280.0f, 720.0f },
        Vector2{ 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    // --- LÓGICA DA COR DINÂMICA (EFEITO CYBERPUNK) ---
    float tempo = GetTime() * 3.0f; // Controla a velocidade da transição de cores
    
    // Ondas senoidais defasadas para misturar os canais R, G e B suavemente entre 0 e 255
    unsigned char r = (unsigned char)((sinf(tempo) * 0.5f + 0.5f) * 255);
    unsigned char g = (unsigned char)((sinf(tempo + 2.0f) * 0.5f + 0.5f) * 255);
    unsigned char b = (unsigned char)((sinf(tempo + 4.0f) * 0.5f + 0.5f) * 255);
    
    Color corDinamica = { r, g, b, 255 };

    // --- RENDERIZAÇÃO DO TEXTO ---
    if (canContinue) {
        const char* textoPrompt = "APERTE ENTER PARA CONTINUAR";
        
        // Desenha o texto centralizado na parte inferior da tela com o efeito RGB
        DrawText(
            textoPrompt, 
            640 - MeasureText(textoPrompt, 24) / 2, 
            620, 
            24, 
            corDinamica
        );
    }
}

bool Cutscene::ShouldAdvance() {
    if (!canContinue) return false;

    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || 
            IsKeyPressed(KEY_SPACE) || 
            IsKeyPressed(KEY_ENTER));
}