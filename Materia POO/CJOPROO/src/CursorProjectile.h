#ifndef CURSOR_PROJECTILE_H
#define CURSOR_PROJECTILE_H

#include "raylib.h"

class CursorProjectile {
private:
    Vector2 position;
    Vector2 direction;
    float speed;
    float radius;
    int damage;
    bool active;
    float rotation; // <-- Guarda o ângulo de rotação em graus

public:
    CursorProjectile(Vector2 startPosition, Vector2 targetPosition);
    
    void Update(float deltaTime);
    // Agora o Draw recebe a textura para podermos rotacioná-la na tela
    void Draw(Texture2D texture) const; 

    Vector2 GetPosition() const;
    float GetRadius() const;
    int GetDamage() const;
    bool IsActive() const;
    void Deactivate();
};

#endif