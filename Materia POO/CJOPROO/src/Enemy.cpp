#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 startPosition)
{
    position = startPosition;
    radius = 16.0f;
    speed = 120.0f;
    hp = 20;
    damage = 10;
}

Enemy::~Enemy()
{
    // Não precisa desalocar nada aqui, a Gameplay cuida disso
}

void Enemy::Update(float deltaTime, Vector2 playerPosition)
{
    Vector2 direction = Vector2Subtract(playerPosition, position);

    if (Vector2Length(direction) > 0.0f)
    {
        direction = Vector2Normalize(direction);
    }

    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;
}

void Enemy::TakeDamage(int amount)
{
    hp -= amount;
}

bool Enemy::IsDead() const
{
    return hp <= 0;
}

void Enemy::Draw() const
{
    DrawCircleV(position, radius, RED);
    DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), radius, MAROON);
}

Vector2 Enemy::GetPosition() const
{
    return position;
}

float Enemy::GetRadius() const
{
    return radius;
}

int Enemy::GetDamage() const
{
    return damage;
}