#include "Worm.h"
#include "raymath.h"

Worm::Worm(Vector2 startPosition, int initialSegments, int playerLevel)
{
    position = startPosition;

    radius = 14.0f;
    speed = 150.0f;
    historySpacing = 6;
    active = true;

    maxHp = initialSegments * playerLevel; 
    hp = maxHp;

    segmentCount = hp - 1; 

    for (int i = 0; i < segmentCount; i++)
    {
        segments.push_back(position);
    }
}

void Worm::Update(float deltaTime, Vector2 playerPosition)
{
    if (!active) return;

    Vector2 direction = Vector2Subtract(playerPosition, position);

    if (Vector2Length(direction) > 0.0f)
    {
        direction = Vector2Normalize(direction);
    }

    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;

    positionHistory.insert(positionHistory.begin(), position);

    int currentSegmentsCount = static_cast<int>(segments.size());
    int maxHistorySize = (currentSegmentsCount + 1) * historySpacing + 20;

    if (static_cast<int>(positionHistory.size()) > maxHistorySize)
    {
        positionHistory.pop_back();
    }

    for (int i = 0; i < currentSegmentsCount; i++)
    {
        int historyIndex = (i + 1) * historySpacing;

        if (historyIndex < static_cast<int>(positionHistory.size()))
        {
            segments[i] = positionHistory[historyIndex];
        }
    }
}

void Worm::Draw(const Texture2D& texture) const
{
    if (!active || texture.id <= 0)
    {
        for (size_t i = 0; i < segments.size(); i++) {
            DrawCircleV(segments[i], radius, Color{ 120, 40, 160, 255 });
        }
        DrawCircleV(position, radius + 2.0f, Color{ 210, 60, 230, 255 });
        return;
    }

    float pieceWidth = (float)texture.width / 4.0f;
    float pieceHeight = (float)texture.height;

    float desiredWidth = radius * 2.5f; 
    float desiredHeight = radius * 2.5f;

    int currentSegmentsCount = static_cast<int>(segments.size());
    for (int i = 0; i < currentSegmentsCount; i++)
    {
        int frameIndex = 2; 

        if (currentSegmentsCount > 1) {
            if (i == currentSegmentsCount - 2) {
                frameIndex = 1; 
            }
            if (i == currentSegmentsCount - 1) {
                frameIndex = 0; 
            }
        } else if (currentSegmentsCount == 1) {
            frameIndex = 0; 
        }

        Rectangle sourceRec = { frameIndex * pieceWidth, 0.0f, pieceWidth, pieceHeight };
        Rectangle destRec = { segments[i].x, segments[i].y, desiredWidth, desiredHeight };

        DrawTexturePro(texture, sourceRec, destRec, Vector2{ desiredWidth / 2.0f, desiredHeight / 2.0f }, 0.0f, WHITE);
    }

    Rectangle sourceHead = { 3.0f * pieceWidth, 0.0f, pieceWidth, pieceHeight };
    Rectangle destHead = { position.x, position.y, desiredWidth , desiredHeight  }; 

    DrawTexturePro(texture, sourceHead, destHead, Vector2{ desiredWidth / 2.0f, desiredHeight / 2.0f }, 0.0f, WHITE);

    DrawText(TextFormat("%d/%d", hp, maxHp), static_cast<int>(position.x - 14), static_cast<int>(position.y - 32), 14, WHITE);
}

void Worm::TakeDamage(int amount)
{
    if (!active) return;

    hp -= amount;

    for (int i = 0; i < amount; i++) {
        if (!segments.empty()) {
            segments.pop_back();
        }
    }

    if (hp <= 0)
    {
        hp = 0;
        Kill();
    }
}

bool Worm::CheckCollisionWithPlayer(Vector2 playerPosition, float playerRadius) const
{
    if (!active) return false;
    return CheckCollisionCircles(position, radius + 2.0f, playerPosition, playerRadius);
}

int Worm::GetDamage() const
{
    return 1 + static_cast<int>(segments.size());
}

bool Worm::IsActive() const { return active; }
void Worm::Kill() { active = false; }
Vector2 Worm::GetPosition() const { return position; }
float Worm::GetRadius() const { return radius; }
bool Worm::IsDead() const { return hp <= 0 || !active; }
int Worm::GetHp() const { return hp; }
int Worm::GetMaxHp() const { return maxHp; }