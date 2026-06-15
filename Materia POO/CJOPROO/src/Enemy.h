#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

class Enemy {
public:
    Enemy(Vector2 startPosition);
    ~Enemy(); // Adicionar destrutor para descarregar o áudio individual se carregar na classe

    void Update(float deltaTime, Vector2 playerPosition);
    void Draw() const;

    Vector2 GetPosition() const;
    float GetRadius() const;
    int GetDamage() const;
    
    // --- NOVOS MÉTODOS ---
    void TakeDamage(int amount);
    bool IsDead() const;

private:
    Vector2 position;
    float radius;
    float speed;
    int hp;
    int damage;

    // --- NOVOS RECURSOS DE ÁUDIO ---
    Sound hitSound;
    Music dieMusic; // Usando Music para garantir a reprodução estável do .mp3
};

#endif