#ifndef MENU_H
#define MENU_H

#include "raylib.h"

// ================= ESTADOS GLOBAIS DO JOGO =================
enum GameState {
    STATE_MENU,
    STATE_INTRO_CUTSCENE,
    STATE_GAMEPLAY,
    STATE_GAMEOVER,
    STATE_BAD_ENDING // <-- ADICIONE ESSA LINHA AQUI (lembre da vírgula na linha anterior!)
};

class Menu {
private:
    // Texturas do Windows XP Logon
    Texture2D logoXpTex;
    Texture2D avatarTex;
    Texture2D onButtonTex;

    // Sons
    Sound turnOnSound;
    Sound startSound;

    // Estados internos da interface
    bool tocarMusicaMenu;
    bool mostrarPopUpCreditos;
    float escalaCreditos;
    bool deveIniciarJogo;

public:
    Menu();
    ~Menu();
    
    // Atualiza a lógica (cliques, hover)
    void Update(Vector2 mousePos);
    
    // Desenha a interface (Layout XP, botões, pop-up)
    void Draw(Vector2 mousePos);
    
    // Retorna true se o jogador clicou para iniciar
    bool DeveIniciarJogo() const { return deveIniciarJogo; }
    
    // Reinicializa o estado do menu (para quando o jogo volta para cá)
    void Reset(); 
};

#endif