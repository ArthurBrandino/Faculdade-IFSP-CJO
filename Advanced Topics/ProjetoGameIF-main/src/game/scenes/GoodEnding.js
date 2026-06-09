import Phaser from 'phaser';

export class GoodEnding extends Phaser.Scene {
    constructor() {
        super({ key: 'GoodEnding' });
    }

    create() {
        // 1. Adiciona a imagem única do quadrinho do final bom
        // Certifique-se de carregar a chave 'good_ending_cutscene' no seu Preloader
        this.comic = this.add.image(this.cameras.main.centerX, this.cameras.main.centerY, 'good_ending_cutscene');
        this.comic.setOrigin(0.5);
        this.comic.setDisplaySize(this.cameras.main.width, this.cameras.main.height);

        // 2. Texto interativo inferior
        this.clickText = this.add.text(
            this.cameras.main.centerX, 
            this.cameras.main.height - 50, 
            "CLIQUE EM QUALQUER LUGAR PARA CONCLUIR", 
            {
                fontFamily: 'monospace',
                fontSize: '20px',
                fill: '#ffffff',
                stroke: '#000000',
                strokeThickness: 4
            }
        ).setOrigin(0.5);

        this.tweens.add({
            targets: this.clickText,
            alpha: 0,
            duration: 800,
            yoyo: true,
            loop: -1
        });

        // 3. Escutadores para finalizar o loop e voltar pro menu de Login
        this.input.on('pointerdown', () => this.finishGame());
        this.input.keyboard.on('keydown', () => this.finishGame());

        this.cameras.main.fadeIn(1000, 0, 0, 0);
    }

    finishGame() {
        if (this.cameras.main.fadeEffect.isRunning) return;

        this.cameras.main.fadeOut(1000, 0, 0, 0);
        this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
            this.scene.start('MainMenu'); // Retorna ao Desktop / Tela de login principal
        });
    }
}