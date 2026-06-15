#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// Estados possíveis do Player
enum PlayerState {
    P_IDLE,
    P_RUN,
    P_ATTACK
};

// Direções cardinais para mapeamento da Spritesheet
enum PlayerDirection {
    DIR_DOWN,
    DIR_SIDE,
    DIR_UP
};

class Player {
private:
    // Texturas individuais (Spritesheets)
    Texture2D idleSheet;
    Texture2D runSheet;
    Texture2D attackSheet;

    // --- CONTROLE DE PISCAR AO LEVAR DANO ---
    float damageTintTimer; 
    float damageDuration;  

    // Transformações físicas e vetoriais
    Vector2 position;
    float speed;
    int hp;
    int maxHp;
    float radius;

    // --- MÁQUINA DE ANIMAÇÃO ---
    PlayerState currentState;
    PlayerDirection currentDir;
    
    int currentFrame;
    float frameTimer;
    float frameLength; // Tempo de exibição de cada frame (1.0f / frameRate)
    int maxFrames;     // Quantidade de frames na animação atual
    float flipX;       // 1.0f normal, -1.0f espelhado para a esquerda

    // Controle de prioridade (Bloqueia movimentação durante o ataque)
    bool isAttacking;

    Sound attackSound;
    Sound damageSound;

public:
    Player(Vector2 startPos);
    ~Player();

    void Update(float deltaTime);
    void Draw();

    // Getters vitais para o Gameplay.cpp
    Vector2 GetPosition() const { return position; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    float GetRadius() const { return radius; }
    bool IsDead() const { return hp <= 0; }
    
    void TakeDamage(int damage);
    void IncreaseSpeed(float amount);
    void TriggerAttack(); // Função para disparar a animação de ataque
};

#endif