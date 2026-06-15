#include "Menu.h"

Menu::Menu() {
    // Carrega os recursos do menu
    logoXpTex   = LoadTexture("resources/mapa/Logo_winxp.png");
    avatarTex   = LoadTexture("resources/mapa/avatar.png");
    onButtonTex = LoadTexture("resources/mapa/On_Sprite.png");

    // Configurando os arquivos de áudio exatamente como você especificou
    turnOnSound = LoadSound("resources/audios/TurnOn.mp3"); // Se falhar na leitura, converta para .wav
    

    Reset();
}

Menu::~Menu() {
    // Garante que nenhum som fique órfão tocando ao destruir o menu
    StopSound(turnOnSound);
    StopSound(startSound);

    // Descarrega a memória
    UnloadTexture(logoXpTex);
    UnloadTexture(avatarTex);
    UnloadTexture(onButtonTex);
    UnloadSound(turnOnSound);
    UnloadSound(startSound);
}

void Menu::Reset() {
    tocarMusicaMenu = true;
    mostrarPopUpCreditos = false;
    escalaCreditos = 1.0f;
    deveIniciarJogo = false;
}

void Menu::Update(Vector2 mousePos) {
    // --- GESTÃO DO LOOP DE ÁUDIO (TurnOn) ---
    // Toca o áudio pela primeira vez assim que o menu abre
    if (tocarMusicaMenu) {
        PlaySound(turnOnSound);
        tocarMusicaMenu = false;
    }
    
    // Se o som terminou de rodar E o jogador ainda não clicou em jogar, reinicia (Loop)
    if (!IsSoundPlaying(turnOnSound) && !deveIniciarJogo && !mostrarPopUpCreditos) {
        PlaySound(turnOnSound);
    }

    if (!mostrarPopUpCreditos) {
        // Clique no Administrador
        Rectangle areaUsuario = { 1280 * 0.55f - 40, 720 * 0.48f - 40, 300, 80 };
        if (CheckCollisionPointRec(mousePos, areaUsuario) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            
            // --- TRANSIÇÃO DOS ÁUDIOS ---
            StopSound(turnOnSound);  // Para o áudio de fundo imediatamente
            
            deveIniciarJogo = true;
        }

        // Hover e Clique nos Créditos
        Rectangle areaCreditos = { 45, 720 - 65, 220, 40 };
        if (CheckCollisionPointRec(mousePos, areaCreditos)) {
            escalaCreditos = 1.05f;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mostrarPopUpCreditos = true;
                StopSound(turnOnSound); // Para o som quando abrir os créditos
            }
        } else {
            escalaCreditos = 1.0f;
        }
    } else {
        // Botão Fechar do Pop-up (X)
        Rectangle areaFecharX = { (float)(1280 / 2 + 180), (float)(720 / 2 - 134), 22, 22 };
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, areaFecharX)) {
            mostrarPopUpCreditos = false;
        }
    }
}

void Menu::Draw(Vector2 mousePos) {
    // Cores e Layout de Fundo do Windows XP
    DrawRectangle(0, 0, 1280, 720, Color{ 90, 126, 220, 255 }); 
    DrawRectangle(0, 0, 1280, 160, Color{ 0, 51, 153, 255 });            
    DrawRectangle(0, 720 - 160, 1280, 160, Color{ 0, 51, 153, 255 }); 
    
    DrawRectangle(0, 160, 1280, 2, Color{ 255, 255, 255, 76 });
    DrawRectangle(0, 720 - 160, 1280, 2, Color{ 255, 255, 255, 76 });

    // --- POSICIONAMENTO DA LOGO (Mantido conforme o seu código) ---
    if (logoXpTex.id > 0) {
        float logoEscala = 0.45f;
        float logoX = 1280 * 0.2f; 
        float logoY = 190.0f; 
        
        DrawTextureEx(logoXpTex, Vector2{ logoX, logoY }, 0.0f, logoEscala, WHITE);
    }
    
    DrawText("Para começar, clique no seu nome de usuário.", (int)(1280 * 0.12f), (int)(720 * 0.58f), 18, WHITE);
    DrawRectangle(1280 * 0.48f, 720 / 2 - 150, 2, 300, Color{ 255, 255, 255, 40 });

    // Painel do Usuário Administrador
    float userX = 1280 * 0.55f;
    float userY = 720 * 0.48f;
    Rectangle areaUsuario = { userX - 40, userY - 40, 300, 80 };
    bool mouseNoUsuario = CheckCollisionPointRec(mousePos, areaUsuario);

    if (mouseNoUsuario) {
        DrawRectangleLinesEx(Rectangle{ userX - 42, userY - 42, 84, 84 }, 2, Color{ 255, 204, 0, 230 });
    }

    if (avatarTex.id > 0) {
        DrawTextureEx(avatarTex, Vector2{ userX - 40, userY - 40 }, 0.0f, 0.08f, WHITE);
    }

    Color corTextoUser = mouseNoUsuario ? Color{ 255, 204, 0, 255 } : WHITE;
    DrawText("ADMINISTRADOR", (int)(userX + 55), (int)(userY - 14), 22, corTextoUser);
    DrawText("Clique aqui para logar", (int)(userX + 55), (int)(userY + 14), 14, Color{ 180, 197, 237, 255 });

    // Botão de Desligar / Créditos
    float btnX = 45;
    float btnY = 720 - 45;
    if (onButtonTex.id > 0) {
        DrawTextureEx(onButtonTex, Vector2{ btnX, btnY - (onButtonTex.height * escalaCreditos) / 2.0f }, 0.0f, escalaCreditos, WHITE);
    }
    Color corTextoCreditos = (escalaCreditos > 1.0f) ? Color{ 255, 204, 0, 255 } : WHITE;
    DrawText("Créditos do Sistema", (int)(btnX + 35), (int)(btnY - 8), 16, corTextoCreditos);

    // Pop-up Janela do Windows (Luna)
    if (mostrarPopUpCreditos) {
        DrawRectangle(0, 0, 1280, 720, Color{ 0, 0, 0, 150 });

        int winW = 420; int winH = 280;
        int winX = 1280 / 2 - winW / 2; int winY = 720 / 2 - winH / 2;

        DrawRectangle(winX, winY, winW, winH, Color{ 236, 233, 216, 255 });
        DrawRectangleLinesEx(Rectangle{ (float)winX, (float)winY, (float)winW, (float)winH }, 3, Color{ 0, 83, 225, 255 });
        DrawRectangle(winX, winY, winW, 32, Color{ 0, 83, 225, 255 });
        DrawText("Propriedades do Sistema", winX + 15, winY + 8, 14, WHITE);

        int xBtnX = winX + winW - 28; int xBtnY = winY + 5;
        bool mouseNoX = CheckCollisionPointRec(mousePos, Rectangle{ (float)xBtnX, (float)xBtnY, 22, 22 });
        DrawRectangle(xBtnX, xBtnY, 22, 22, mouseNoX ? Color{ 242, 92, 92, 255 } : Color{ 224, 67, 67, 255 });
        DrawRectangleLines(xBtnX, xBtnY, 22, 22, WHITE);
        DrawText("x", xBtnX + 7, xBtnY + 2, 16, WHITE);

        DrawText("TROJAN.ENZINHO.EXE", winX + 110, winY + 60, 18, BLACK);
        DrawText("-------------------------------------------------", winX + 25, winY + 90, 16, DARKGRAY);
        DrawText("Desenvolvido por: Arthur Brandino", winX + 40, winY + 120, 16, BLACK);
        DrawText("Design de Arte: Nicholas Koedel", winX + 40, winY + 150, 16, BLACK);
        DrawText("Motor Grafico: Raylib (C++)", winX + 40, winY + 180, 16, BLACK);
        DrawText("-------------------------------------------------", winX + 25, winY + 210, 16, DARKGRAY);
        DrawText("© 2026 - Todos os vírus reservados.", winX + 70, winY + 240, 14, GRAY);
    }
}