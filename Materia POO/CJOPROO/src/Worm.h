#ifndef WORM_H
#define WORM_H

#include "raylib.h"
#include <vector>

class Worm
{
private:
    Vector2 position;
    std::vector<Vector2> segments;
    std::vector<Vector2> positionHistory;
    float radius;
    float speed;
    int segmentCount;
    int historySpacing;
    bool active;
    int hp;
    int maxHp;

public:
    Worm(Vector2 startPosition, int initialSegments, int playerLevel);

    // Mantenha o resto dos métodos públicos exatamente como estavam
    void Update(float deltaTime, Vector2 playerPosition);
    void Draw(const Texture2D& texture) const;
    bool CheckCollisionWithPlayer(Vector2 playerPosition, float playerRadius) const;
    int GetDamage() const;
    bool IsActive() const;
    void Kill();
    void TakeDamage(int amount);
    bool IsDead() const;
    int GetHp() const;
    int GetMaxHp() const;
    Vector2 GetPosition() const;
    float GetRadius() const;
};

#endif