#include "raylib.h"
#include "Menu.h"
#include "Gameplay.h"
#include "GameOver.h"
#include "Cutscene.h" 
#include "BadEnding.h"

int main() {
    InitWindow(1280, 720, "Cyber Defense - IFSP CJO");
    InitAudioDevice();
    SetTargetFPS(60);

    // O tipo GameState agora é lido diretamente do "Menu.h"
    GameState currentState = STATE_MENU; 
    Menu* gameMenu = new Menu();
    Cutscene* introCutscene = nullptr; 
    Gameplay* gamePlay = nullptr;
    GameOver* gameOverScreen = nullptr;
    BadEnding* badEndingCutscene = nullptr; 

    // Variáveis de áudio persistentes na Main
    Sound startupSound = { 0 };
    startupSound.stream.buffer = nullptr; 

    Music gamePlaylist = { 0 };
    gamePlaylist.ctxData = nullptr; 
    
    // Flags de controle para a transição perfeita
    bool esperandoStartup = false;
    bool trilhaIniciada = false;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        // --- SISTEMA DE TIMING DA TRILHA SONORA ---
        // 1. Se estamos esperando o startup acabar e ele FINISHED de tocar:
        if (esperandoStartup && !IsSoundPlaying(startupSound)) {
            gamePlaylist = LoadMusicStream("resources/audios/GameSoundtrack.mp3");
            gamePlaylist.looping = true;
            PlayMusicStream(gamePlaylist);
            
            trilhaIniciada = true;
            esperandoStartup = false; // Transição concluída
        }

        // 2. Se a trilha já está ativa, mantém o streaming do MP3 vivo
        if (trilhaIniciada) {
            UpdateMusicStream(gamePlaylist);
        }

        // --- ATUALIZAÇÃO DA LÓGICA ---
        if (currentState == STATE_MENU) {
            gameMenu->Update(mousePos);
            if (gameMenu->DeveIniciarJogo()) {
                delete gameMenu;
                gameMenu = nullptr;
                
                introCutscene = new Cutscene();
                currentState = STATE_INTRO_CUTSCENE;
            }
        } 
        else if (currentState == STATE_INTRO_CUTSCENE) {
            if (introCutscene != nullptr) {
                introCutscene->Update(deltaTime);
                
                if (introCutscene->ShouldAdvance()) {
                    delete introCutscene;
                    introCutscene = nullptr;
                    
                    // Dispara o som de Startup
                    startupSound = LoadSound("resources/audios/Startup.wav");
                    PlaySound(startupSound);
                    
                    // Liga o sensor: "Fique de olho até esse som terminar"
                    esperandoStartup = true; 
                    
                    // Entra na gameplay, mas a trilha vai segurar até o som de boot morrer
                    gamePlay = new Gameplay();
                    currentState = STATE_GAMEPLAY;
                }
            }
        }
        else if (currentState == STATE_GAMEPLAY) {
            gamePlay->Update(deltaTime);
            
            if (gamePlay->IsPlayerDead()) { 
                delete gamePlay;
                gamePlay = nullptr;
                
                // Limpeza da trilha sonora ao morrer
                if (trilhaIniciada) {
                    StopMusicStream(gamePlaylist);
                    UnloadMusicStream(gamePlaylist);
                    gamePlaylist.ctxData = nullptr;
                    trilhaIniciada = false;
                }
                esperandoStartup = false; // Garante reset se morrer no meio do som
                
                gameOverScreen = new GameOver(2500, 32, 84.5f);
                currentState = STATE_GAMEOVER;
            }
        } 
        else if (currentState == STATE_GAMEOVER) {
            gameOverScreen->Update(deltaTime);

            if (gameOverScreen->ShouldAdvance()) {
                delete gameOverScreen;
                gameOverScreen = nullptr;
                
                badEndingCutscene = new BadEnding(); 
                currentState = STATE_BAD_ENDING;     
            }
        }
        else if (currentState == STATE_BAD_ENDING) { 
            if (badEndingCutscene != nullptr) {
                badEndingCutscene->Update(deltaTime);
                
                if (badEndingCutscene->ShouldReturn()) {
                    delete badEndingCutscene;
                    badEndingCutscene = nullptr;
                    
                    gameMenu = new Menu();
                    currentState = STATE_MENU;
                }
            }
        }

        // --- RENDERIZAÇÃO ---
        BeginDrawing();
            if (currentState == STATE_MENU && gameMenu != nullptr) {
                gameMenu->Draw(mousePos);
            } 
            else if (currentState == STATE_INTRO_CUTSCENE && introCutscene != nullptr) {
                introCutscene->Draw(); 
            }
            else if (currentState == STATE_GAMEPLAY && gamePlay != nullptr) {
                gamePlay->Draw();
            } 
            else if (currentState == STATE_GAMEOVER && gameOverScreen != nullptr) {
                gameOverScreen->Draw();
            }
            else if (currentState == STATE_BAD_ENDING && badEndingCutscene != nullptr) {
                badEndingCutscene->Draw(); 
            }
        EndDrawing();
    }

    // Liberação de segurança ao fechar a janela
    if (gameMenu != nullptr) delete gameMenu;
    if (introCutscene != nullptr) delete introCutscene; 
    if (gamePlay != nullptr) delete gamePlay;
    if (gameOverScreen != nullptr) delete gameOverScreen;
    if (badEndingCutscene != nullptr) delete badEndingCutscene; 

    if (startupSound.stream.buffer != nullptr) {
        UnloadSound(startupSound);
    }
    if (gamePlaylist.ctxData != nullptr) {
        UnloadMusicStream(gamePlaylist);
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}