#include "GameOver.h"
#include <iostream>
#include <string>

GameOver::GameOver(int score, int malwares, float tempo) {
    shutdownSound = LoadSound("resources/audios/Shutdown.mp3");
    
    cabecalho = "--- GAME OVER ---";
    
    corpoTexto = 
        "A problem has been detected and Cyber_Defense.exe has been terminated to prevent damage\n"
        "to your current system architecture.\n\n"
        "SYSTEM_STATUS: CORRUPTED_BY_MALWARE\n\n"
        "Check to make sure any new hardware or software (like your FIREWALL, CLICKER or LIXEIRA)\n"
        "is properly installed. If problems continue, remove any newly installed software.";

    playerScore = score;
    malwaresDestruidos = malwares;
    tempoSobrevivido = tempo;

    blocoScoreboard = 
        "RESULT_DATA_EDITION:\n"
        "  * TOTAL_CORE_SCORE  : " + std::to_string(playerScore) + " PTS\n"
        "  * THREATS_DESTROYED : " + std::to_string(malwaresDestruidos) + " MALWARES\n"
        "  * SYSTEM_UPTIME     : " + std::to_string((int)tempoSobrevivido) + " SECONDS";

    infoTecnica = 
        "Technical information:\n"
        "*** STOP: 0x000000D1 (0x0000" + std::to_string(playerScore) + ", 0x000000" + std::to_string(malwaresDestruidos) + ", 0x00000000, 0xF86B5A89)\n"
        "*** cyber_defense.sys - Address F86B5A89 base at F86B0000";

    Reset();
}

GameOver::~GameOver() {
    // FIX: Checagem universal compatível com qualquer versão da Raylib
    if (shutdownSound.stream.buffer != nullptr) {
        UnloadSound(shutdownSound);
    }
}

void GameOver::Reset() {
    sonsTocados = false;
    blinkTimer = 0.0f;
    mostrarTextoClique = true;
}

void GameOver::Update(float deltaTime) {
    if (!sonsTocados) {
        // FIX: Garante que só toca se o ponteiro do buffer de áudio for válido
        if (shutdownSound.stream.buffer != nullptr) {
            PlaySound(shutdownSound);
        }
        sonsTocados = true;
    }

    blinkTimer += deltaTime;
    if (blinkTimer >= 0.6f) {
        mostrarTextoClique = !mostrarTextoClique;
        blinkTimer = 0.0f;
    }
}

void GameOver::Draw() {
    ClearBackground(Color{ 0, 0, 170, 255 }); 

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int margemX = 60; 

    int barraY = 40;
    int barraH = 35;
    DrawRectangle(margemX, barraY, screenWidth - (margemX * 2), barraH, WHITE);

    int tamanhoTextoCabecalho = MeasureText(cabecalho.c_str(), 20);
    DrawText(cabecalho.c_str(), (screenWidth / 2) - (tamanhoTextoCabecalho / 2), barraY + 8, 20, Color{ 0, 0, 170, 255 });

    DrawText(corpoTexto.c_str(), margemX, 110, 18, WHITE);

    int scoreboardY = 290; 
    DrawRectangle(margemX, scoreboardY - 10, screenWidth - (margemX * 2), 2, WHITE);
    DrawText(blocoScoreboard.c_str(), margemX, scoreboardY, 18, WHITE);
    DrawRectangle(margemX, scoreboardY + 90, screenWidth - (margemX * 2), 2, WHITE);

    DrawText(infoTecnica.c_str(), margemX, 420, 18, WHITE);

    if (mostrarTextoClique) {
        const char* textoPrompt = "Press any key or CLICK ANYWHERE to continue";
        int tamanhoPrompt = MeasureText(textoPrompt, 20);
        DrawText(textoPrompt, (screenWidth / 2) - (tamanhoPrompt / 2), screenHeight - 80, 20, WHITE);
    }
}

bool GameOver::ShouldAdvance() {
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetKeyPressed() != 0);
}