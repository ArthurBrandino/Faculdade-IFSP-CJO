#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"
#include "Player.h"
#include "Worm.h"
#include "CursorProjectile.h"
#include <vector>

// Estrutura para as pastas de XP (Gems) se você tiver ela declarada aqui
struct XpGem {
    Vector2 position;
    int xpValue;
    bool active;
    float speed;
    float attractionRadius;
};

class Gameplay {
public:
    Gameplay();
    ~Gameplay();

    void Update(float deltaTime);
    void Draw();
    bool IsPlayerDead();

private:
    // --- TEXTURAS E ENTIDADES EXISTENTES ---
    Texture2D backgroundTex;
    Texture2D playerTex;
    Texture2D wormTex;
    Texture2D projectileTex;
    Texture2D XpTex;
    Texture2D lifeTex;

    Player player;
    std::vector<Worm> worms;
    std::vector<CursorProjectile> projectiles;
    std::vector<XpGem> xpGems;

    Camera2D camera;

    // --- VARIÁVEIS DE CONTROLE EXISTENTES ---
    int maxWormsOnScreen;
    float spawnTimer;
    float spawnCooldown;
    int currentXp;
    int xpNeededForLevelUp;
    int playerLevel;
    int wormsKilled;
    float attackTimer;
    float attackCooldown;

    // =========================================================
    // Sons
    // =========================================================
    Sound enemyHitSound;
    Sound enemyDeadSound;

    Sound xpPickupSound;
    Sound levelUpSound;
};

#endif // GAMEPLAY_H