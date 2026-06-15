#include "Player.h"
#include <cmath>

Player::Player(Vector2 startPos) {
    position = startPos;
    speed = 250.0f;
    hp = 100;
    maxHp = 100;
    
    // Raio físico condizente com o tamanho visual maior (escala 3x)
    radius = 24.0f; 

    // Carrega as 3 spritesheets do projeto original
    idleSheet   = LoadTexture("resources/player/idle.png");
    runSheet    = LoadTexture("resources/player/run.png");
    attackSheet = LoadTexture("resources/player/attack.png");

    // --- NOVO: CARREGAMENTO DOS ÁUDIOS DO PLAYER ---
    attackSound = LoadSound("resources/audios/hitHurt.wav");
    damageSound = LoadSound("resources/audios/Error.mp3");

    // --- FILTRO DE PIXELS (Evita que o sprite fique borrado ao escalar) ---
    SetTextureFilter(idleSheet, TEXTURE_FILTER_POINT);
    SetTextureFilter(runSheet, TEXTURE_FILTER_POINT);
    SetTextureFilter(attackSheet, TEXTURE_FILTER_POINT);

    // Inicialização do Estado Inicial
    currentState = P_IDLE;
    currentDir = DIR_DOWN;
    currentFrame = 0;
    frameTimer = 0.0f;
    frameLength = 1.0f / 6.0f; // 6 FPS (Idle)
    maxFrames = 4;
    flipX = 1.0f;
    isAttacking = false;

    // --- INICIALIZAÇÃO DO TEMPORIZADOR DE DANO ---
    damageTintTimer = 0.0f;
    damageDuration = 0.25f; // Duração do efeito visual de flash (em segundos)
}

Player::~Player() {
    UnloadTexture(idleSheet);
    UnloadTexture(runSheet);
    UnloadTexture(attackSheet);

    // --- NOVO: DESALOCAÇÃO SEGURA DOS ÁUDIOS DO PLAYER ---
    UnloadSound(attackSound);
    UnloadSound(damageSound);
}

void Player::TriggerAttack() {
    if (!isAttacking) {
        isAttacking = true;
        currentState = P_ATTACK;
        currentFrame = 0;
        frameTimer = 0.0f;
        frameLength = 1.0f / 14.0f; // 14 FPS
        maxFrames = 6;              // Ataques possuem 6 frames

        // NOVO: Toca o som ao iniciar o ataque
        PlaySound(attackSound);
    }
}

void Player::TakeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
    
    // Dispara o início do efeito de flash
    damageTintTimer = damageDuration;

    // NOVO: Toca o som de dano recebido
    PlaySound(damageSound);
}

void Player::Update(float deltaTime) {
    if (IsDead()) return;

    // --- ATUALIZA O TEMPORIZADOR DE PISCAR POR DANO ---
    if (damageTintTimer > 0.0f) {
        damageTintTimer -= deltaTime;
    }

    // --- LEITURA VETORIAL DE INPUTS (Sempre ativa para permitir andar) ---
    float moveX = 0;
    float moveY = 0;

    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) moveX = -1;
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) moveX = 1;

    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) moveY = -1;
    else if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) moveY = 1;

    // Aplica a movimentação física no mundo independente do estado da animação
    if (moveX != 0 || moveY != 0) {
        position.x += moveX * speed * deltaTime;
        position.y += moveY * speed * deltaTime;
    }

    // --- MÁQUINA DE ANIMAÇÃO: GERENCIAMENTO DE ESTADOS ---
    if (isAttacking) {
        // Se estiver atacando, atualizamos o timer e os frames do ataque
        frameTimer += deltaTime;
        if (frameTimer >= frameLength) {
            frameTimer = 0.0f;
            currentFrame++;
            if (currentFrame >= maxFrames) {
                // Fim do ataque: devolve o estado para a movimentação atual
                isAttacking = false;
                currentFrame = 0;
                
                // Se ainda estiver segurando teclas, volta direto para RUN, senão IDLE
                if (moveX != 0 || moveY != 0) {
                    currentState = P_RUN;
                    frameLength = 1.0f / 12.0f;
                    maxFrames = 6;
                } else {
                    currentState = P_IDLE;
                    frameLength = 1.0f / 6.0f;
                    maxFrames = 4;
                }
            }
        }

        // Se o jogador mudar de direção ENQUANTO anda e ataca, atualizamos a direção do sprite
        if (moveY == 1)       currentDir = DIR_DOWN;
        else if (moveY == -1) currentDir = DIR_UP;
        else if (moveX != 0) {
            currentDir = DIR_SIDE;
            flipX = (moveX == -1) ? -1.0f : 1.0f;
        }

        // Retorna antes de processar as animações de Run/Idle comuns para não cortar o ataque no meio
        return; 
    }

    // --- ANIMAÇÕES NORMAIS DE CORRIDA E REPOUSO (Apenas se NÃO estiver atacando) ---
    if (moveX != 0 || moveY != 0) {
        currentState = P_RUN;
        frameLength = 1.0f / 12.0f;
        maxFrames = 6;

        if (moveY == 1) {
            currentDir = DIR_DOWN;
        } 
        else if (moveY == -1) {
            currentDir = DIR_UP;
        } 
        else if (moveX != 0) {
            currentDir = DIR_SIDE;
            flipX = (moveX == -1) ? -1.0f : 1.0f;
        }
    } 
    else {
        currentState = P_IDLE;
        frameLength = 1.0f / 6.0f;
        maxFrames = 4;
    }

    // Patamar normal dos frames (Run / Idle)
    frameTimer += deltaTime;
    if (frameTimer >= frameLength) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % maxFrames;
    }
}

void Player::Draw() {
    Texture2D currentSheet;
    int offsetLinhaXp = 0;

    switch (currentState) {
        case P_IDLE:
            currentSheet = idleSheet;
            if (currentDir == DIR_DOWN) offsetLinhaXp = 0;
            if (currentDir == DIR_SIDE) offsetLinhaXp = 2;
            if (currentDir == DIR_UP)   offsetLinhaXp = 4;
            break;

        case P_RUN:
            currentSheet = runSheet;
            if (currentDir == DIR_DOWN) offsetLinhaXp = 0;
            if (currentDir == DIR_SIDE) offsetLinhaXp = 2;
            if (currentDir == DIR_UP)   offsetLinhaXp = 4;
            break;

        case P_ATTACK:
            currentSheet = attackSheet;
            if (currentDir == DIR_DOWN) offsetLinhaXp = 0;
            if (currentDir == DIR_SIDE) offsetLinhaXp = 2;
            if (currentDir == DIR_UP)   offsetLinhaXp = 4;
            break;
    }

    float frameWidth = 24.0f;
    float frameHeight = 24.0f;

    Rectangle sourceRec = {
        currentFrame * frameWidth,
        offsetLinhaXp * frameHeight,
        frameWidth * flipX, 
        frameHeight
    };

    float escala = 3.0f;

    Rectangle destRec = {
        position.x,
        position.y,
        frameWidth * escala,
        frameHeight * escala
    };

    Vector2 origin = { (frameWidth * escala) / 2.0f, (frameHeight * escala) / 2.0f };

    Color corDoSprite = WHITE;
    if (damageTintTimer > 0.0f) {
        if ((int)(damageTintTimer * 25) % 2 == 0) {
            corDoSprite = RED;
        }
    }

    DrawTexturePro(currentSheet, sourceRec, destRec, origin, 0.0f, corDoSprite);
}

void Player::IncreaseSpeed(float amount) {
    speed += amount;
}