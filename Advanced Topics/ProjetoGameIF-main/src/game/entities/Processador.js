import Phaser from 'phaser';

export class Processador extends Phaser.Physics.Arcade.Sprite {   
    constructor(scene, x, y) {
        // 1. Inicializa o sprite com a textura
        super(scene, x, y, 'processador');
        
        scene.add.existing(this);
        // 2. Adiciona a física estática
        scene.physics.add.existing(this, true);

        // 3. Aplica a escala primeiro!
        this.setScale(3);
        this.setPixelArt = true;

        // 4. CORREÇÃO DA HITBOX: 
        // Usamos as propriedades nativas de tamanho da própria imagem (width e height).
        // Assim o Phaser ajusta a colisão proporcionalmente ao tamanho do sprite.
        this.body.setSize(this.width, this.height);
        this.body.setOffset(0, 0);

        // 5. CRUCIAL PARA CORPOS ESTÁTICOS:
        // Força a física a atualizar a posição da hitbox baseada no novo tamanho/escala centralizado
        this.body.updateFromGameObject();

        // 6. Resto das configurações normais
        this.podeTocarSomHit = true;
        this.somHit = scene.sound.add('hit_processador');

        this.vidaMaxima = 100;
        this.vidaAtual = this.vidaMaxima;  
    }

    receberDano(quantidade) {
        // CORREÇÃO: Usando o nome correto da variável (quantidade)
        this.vidaAtual = Phaser.Math.Clamp(this.vidaAtual - quantidade, 0, this.vidaMaxima);
        this.scene.events.emit('update-hp', this.vidaAtual, this.vidaMaxima);

        // Se o processador morrer, chama o Game Over (Tela Azul) na hora
        if (this.vidaAtual <= 0) {
            this.destruirEGameOver();
            return;
        }

        // --- INTERVALO (SOM + VISUAL) ---
        if (this.podeTocarSomHit) {
            this.podeTocarSomHit = false; 

            // Som do Processador sendo atacado
            if (this.somHit) this.somHit.play();

            // Ativa o Feedback Visual (Piscada Vermelha Neon)
            this.setTint(0xff3333);
            this.setAlpha(0.8); 

            // Restaurar a aparência original do processador após 150ms
            this.scene.time.delayedCall(150, () => {
                this.clearTint();            
                this.setAlpha(1);             
                this.podeTocarSomHit = true;
            });
        }
    }
    destruirEGameOver() {
        if (this.somHit) {
            this.somHit.stop();
            this.somHit.destroy();
        }
        
        // Para todas as músicas e efeitos da cena atual antes de ir para a Tela Azul
        if (this.scene.bgmOnda) {
            this.scene.bgmOnda.stop();
        }
        
        this.scene.scene.start('GameOver'); 
    }
}