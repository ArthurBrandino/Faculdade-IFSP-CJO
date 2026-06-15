#include "CursorProjectile.h"
#include <cmath> // Para sqrtf e atan2f

CursorProjectile::CursorProjectile(Vector2 startPosition, Vector2 targetPosition)
{
    position = startPosition;

    // Cálculo manual para evitar bugs de link com raymath
    direction.x = targetPosition.x - startPosition.x;
    direction.y = targetPosition.y - startPosition.y;

    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.0f)
    {
        direction.x /= length;
        direction.y /= length;
    }
    else
    {
        direction = { 1.0f, 0.0f };
    }

    // --- CÁLCULO DA ROTAÇÃO EM GRAUS ---
    // atan2f nos dá o ângulo em radianos. Multiplicamos por RAD2DEG para converter para graus.
    // Se o seu sprite original do cursor estiver apontando para a direita, o ajuste é 0.
    rotation = atan2f(direction.y, direction.x) * RAD2DEG;

    speed = 600.0f;
    radius = 10.0f; // Sincronizado com o tamanho do desenho
    damage = 1;
    active = true;
}

void CursorProjectile::Update(float deltaTime)
{
    if (!active) return;

    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;
}

void CursorProjectile::Draw(Texture2D texture) const
{
    // Se a textura for válida (carregada), desenha rotacionada com DrawTexturePro
    if (texture.id > 0)
    {
        // Parte da imagem que vamos usar (inteira)
        Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
        
        // Onde e qual tamanho vai ser desenhado no mapa
        Rectangle destRec = { position.x, position.y, 24.0f, 24.0f };
        
        // Define o centro de rotação bem no meio do projétil
        Vector2 origin = { 12.0f, 12.0f };
        
        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);
    }
    else
    {
        // Fallback robusto em círculos caso a imagem falhe ao carregar
        DrawCircleV(position, radius, YELLOW);
        DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), radius, ORANGE);
    }
}

Vector2 CursorProjectile::GetPosition() const { return position; }
float CursorProjectile::GetRadius() const { return radius; }
int CursorProjectile::GetDamage() const { return damage; }
bool CursorProjectile::IsActive() const { return active; }
void CursorProjectile::Deactivate() { active = false; }