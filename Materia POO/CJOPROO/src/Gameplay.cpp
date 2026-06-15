#include "GameOver.h"
#include "Gameplay.h"
#include <algorithm>
#include <cmath>

Gameplay::Gameplay() : player({ 3000.0f / 2.0f, 3000.0f / 2.0f }) {
    // Carrega sprites do Gameplay
    backgroundTex = LoadTexture("resources/mapa/BackgroundGame.gif");
    playerTex     = LoadTexture("resources/player.png");
    wormTex       = LoadTexture("resources/inimigos/Worm_Sprite.png");
    projectileTex = LoadTexture("resources/defesas/projectile.png");
    XpTex         = LoadTexture("resources/mapa/Folder_Sprite.png");
    lifeTex       = LoadTexture("resources/mapa/processador.png");

    // --- CARREGAMENTO CENTRALIZADO DE ÁUDIO DOS INIMIGOS ---
    enemyHitSound  = LoadSound("resources/audios/hitEnemy.wav");
    enemyDeadSound = LoadSound("resources/audios/EnemyDestroy.mp3");

    // --- NOVO: CARREGAMENTO DOS ÁUDIOS DE PROGRESSÃO DO PLAYER ---
    xpPickupSound  = LoadSound("resources/audios/key.wav");
    levelUpSound   = LoadSound("resources/audios/LevelUp.wav");

    // Inicializa variáveis do estado original
    maxWormsOnScreen = 1;
    spawnTimer = 0.0f;
    spawnCooldown = 3.0f;
    
    // Configurações de progressão
    currentXp = 0;
    xpNeededForLevelUp = 30;
    playerLevel = 1;
    wormsKilled = 0; 
    attackTimer = 0.0f;
    attackCooldown = 1.0f;

    // Configuração da Câmera
    camera = { 0 };
    camera.target = player.GetPosition();
    camera.offset = { 1280 / 2.0f, 720 / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

Gameplay::~Gameplay() {
    UnloadTexture(backgroundTex);
    UnloadTexture(playerTex);
    UnloadTexture(wormTex);
    UnloadTexture(projectileTex);
    UnloadTexture(XpTex);
    UnloadTexture(lifeTex);

    // --- DESALOCAÇÃO SEGURA DOS ÁUDIOS DO INIMIGO ---
    UnloadSound(enemyHitSound);
    UnloadSound(enemyDeadSound);

    // --- NOVO: DESALOCAÇÃO SEGURA DOS ÁUDIOS DO PLAYER ---
    UnloadSound(xpPickupSound);
    UnloadSound(levelUpSound);
}

void Gameplay::Update(float deltaTime) {
    // Se o player estiver morto, para a atualização imediatamente
    if (player.IsDead()) return;

    player.Update(deltaTime);
    maxWormsOnScreen = playerLevel; 

    // Lógica de Spawn das Worms
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnCooldown && worms.size() < static_cast<size_t>(maxWormsOnScreen)) {
        spawnTimer = 0.0f;
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float distance = 700.0f; 
        Vector2 spawnPos = {
            player.GetPosition().x + cosf(angle) * distance,
            player.GetPosition().y + sinf(angle) * distance
        };
        worms.push_back(Worm(spawnPos, 4, playerLevel));
    }

    for (Worm& w : worms) {
        if (w.IsActive()) w.Update(deltaTime, player.GetPosition());
    }

    // Input de ataque manual
    if (IsKeyPressed(KEY_SPACE)) {
        projectiles.push_back(CursorProjectile(player.GetPosition(), { player.GetPosition().x + 500.0f, player.GetPosition().y }));
    }

    // Ataque automático sincronizado com a animação do player
    attackTimer += deltaTime;
    if (attackTimer >= attackCooldown && !worms.empty()) {
        attackTimer = 0.0f;
        for (Worm& w : worms) {
            if (w.IsActive()) {
                projectiles.push_back(CursorProjectile(player.GetPosition(), w.GetPosition()));
                
                // Dispara a animação do player automaticamente junto com o projétil
                player.TriggerAttack(); 
                break; 
            }
        }
    }

    // Colisões de projéteis e Sistema de Drop Dinâmico de XP
    for (CursorProjectile& projectile : projectiles) {
        if (projectile.IsActive()) {
            projectile.Update(deltaTime);
            for (Worm& w : worms) {
                if (w.IsActive() && CheckCollisionCircles(projectile.GetPosition(), 10.0f, w.GetPosition(), w.GetRadius() + 2.0f)) {
                    
                    w.TakeDamage(projectile.GetDamage());
                    projectile.Deactivate();
                    
                    // Checa se o ataque matou a Worm
                    if (w.IsDead()) {
                        PlaySound(enemyDeadSound); 
                        wormsKilled++; 
                        
                        XpGem novoXp = { w.GetPosition(), 15, true, 450.0f, 150.0f };
                        xpGems.push_back(novoXp);
                    }
                    else {
                        PlaySound(enemyHitSound); 
                    }
                }
            }
        }
    }

    // --- LOGICA DE ATRAÇÃO E COLETA DE MÚLTIPLOS XPS + SONS ---
    for (XpGem& gem : xpGems) {
        if (gem.active) {
            float dx = player.GetPosition().x - gem.position.x;
            float dy = player.GetPosition().y - gem.position.y;
            float distance = sqrtf(dx * dx + dy * dy);

            if (distance <= gem.attractionRadius && distance > 0.0f) {
                gem.position.x += (dx / distance) * gem.speed * deltaTime;
                gem.position.y += (dy / distance) * gem.speed * deltaTime;
            }

            // Colisão com o jogador para coletar o XP
            if (CheckCollisionCircles(player.GetPosition(), player.GetRadius(), gem.position, 12.0f)) {
                gem.active = false; 
                currentXp += gem.xpValue;
                
                // NOVO: Toca o som de coleta do XP
                PlaySound(xpPickupSound);
                
                // Checa se subiu de nível
                if (currentXp >= xpNeededForLevelUp) {
                    currentXp -= xpNeededForLevelUp;
                    playerLevel++;
                    xpNeededForLevelUp += 15;
                    player.IncreaseSpeed(15.0f);
                    attackCooldown -= 0.1f;
                    
                    // NOVO: Toca o som épico de Level Up
                    PlaySound(levelUpSound);
                }
            }
        }
    }

    // Dano das Worms no Player
    for (Worm& w : worms) {
        if (w.IsActive() && w.CheckCollisionWithPlayer(player.GetPosition(), player.GetRadius())) {
            player.TakeDamage(w.GetDamage());
            
            PlaySound(enemyDeadSound); 
            w.Kill();
            wormsKilled++; 
            
            XpGem novoXp = { w.GetPosition(), 15, true, 450.0f, 150.0f };
            xpGems.push_back(novoXp);
        }
    }

    // Limpeza de vetores
    worms.erase(std::remove_if(worms.begin(), worms.end(), [](const Worm& w) { return !w.IsActive(); }), worms.end());
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const CursorProjectile& p) { 
        return !p.IsActive() || p.GetPosition().x < 0 || p.GetPosition().x > 3000.0f || p.GetPosition().y < 0 || p.GetPosition().y > 3000.0f; 
    }), projectiles.end());
    
    xpGems.erase(std::remove_if(xpGems.begin(), xpGems.end(), [](const XpGem& g) { return !g.active; }), xpGems.end());

    // --- TRAVAR A CÂMERA NOS LIMITES DO MUNDO (Camera Clamping) ---
    float minX = 1280 / 2.0f;
    float maxX = 3000.0f - (1280 / 2.0f);
    float minY = 720 / 2.0f;
    float maxY = 3000.0f - (720 / 2.0f);

    camera.target.x = std::clamp(player.GetPosition().x, minX, maxX);
    camera.target.y = std::clamp(player.GetPosition().y, minY, maxY);
}

void Gameplay::Draw() {
    BeginMode2D(camera);
        // Desenha o mapa quadriculado
        float tileWidth = 512.0f; float tileHeight = 512.0f;
        for (float x = 0; x < 3000.0f; x += tileWidth) {
            for (float y = 0; y < 3000.0f; y += tileHeight) {
                DrawTexturePro(backgroundTex, Rectangle{ 0, 0, (float)backgroundTex.width, (float)backgroundTex.height }, Rectangle{ x, y, tileWidth, tileHeight }, Vector2{ 0, 0 }, 0.0f, WHITE);
            }
        }

        for (const XpGem& gem : xpGems) {
            if (gem.active) {
                if (XpTex.id > 0) {
                    float gemW = (float)XpTex.width / 2.0f;
                    DrawTexturePro(XpTex, Rectangle{ gemW, 0.0f, gemW, (float)XpTex.height }, Rectangle{ gem.position.x, gem.position.y, 28.0f, 28.0f }, Vector2{ 14.0f, 14.0f }, 0.0f, WHITE);
                } else {
                    DrawCircleV(gem.position, 8.0f, GREEN);
                }
            }
        }

        for (const Worm& w : worms) w.Draw(wormTex);

        for (const CursorProjectile& p : projectiles) {
            p.Draw(projectileTex);
        }

        player.Draw();
    EndMode2D();

    // HUD do Jogo (Fixo na Tela)
    DrawRectangle(0, 0, 1280, 65, Color{ 15, 15, 22, 220 });
    DrawRectangleLines(0, 0, 1280, 65, Color{ 45, 45, 65, 255 });

    if (XpTex.id > 0) {
        DrawTexturePro(XpTex, Rectangle{ 0.0f, 0.0f, (float)XpTex.width / 2.0f, (float)XpTex.height }, Rectangle{ 20.0f, 15.0f, 32.0f, 32.0f }, Vector2{ 0, 0 }, 0.0f, WHITE);
    }
    DrawText(TextFormat("NÍVEL %d", playerLevel), 65, 20, 22, GREEN);
    DrawText(TextFormat("XP: %d / %d", currentXp, xpNeededForLevelUp), 175, 24, 16, LIGHTGRAY);

    if (lifeTex.id > 0) {
        DrawTexturePro(lifeTex, Rectangle{ 0.0f, 0.0f, (float)lifeTex.width, (float)lifeTex.height }, Rectangle{ 445.0f, 16.0f, 32.0f, 32.0f }, Vector2{ 0, 0 }, 0.0f, WHITE);
    }
    
    int barWidth = 200, barHeight = 20, barX = 490, barY = 22;
    float hpPercentage = (player.GetMaxHp() > 0) ? (float)player.GetHp() / (float)player.GetMaxHp() : 0.0f;
    DrawRectangle(barX, barY, barWidth, barHeight, DARKGRAY);
    DrawRectangle(barX, barY, static_cast<int>(barWidth * fmaxf(hpPercentage, 0.0f)), barHeight, MAROON);
    DrawRectangleLines(barX, barY, barWidth, barHeight, WHITE);
    DrawText(TextFormat("%d / %d", player.GetHp(), player.GetMaxHp()), barX + 15, barY + 3, 14, WHITE);

    DrawCircle(850, 32, 10, Color{ 210, 60, 230, 255 });
    DrawText(TextFormat("Worms: %d (Máx: %d)", static_cast<int>(worms.size()), maxWormsOnScreen), 870, 22, 18, PURPLE);
}

bool Gameplay::IsPlayerDead() {
    return player.IsDead(); 
}