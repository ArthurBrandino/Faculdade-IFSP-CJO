import Phaser from 'phaser';

export class BadEnding extends Phaser.Scene {
    constructor() {
        super({ key: 'BadEnding' });
    }

    create() {
        // 1. Adiciona a imagem única do quadrinho do final ruim centralizada na tela
        // Certifique-se de carregar a chave 'bad_ending_cutscene' no seu Preloader
        this.comic = this.add.image(this.cameras.main.centerX, this.cameras.main.centerY, 'bad_ending_cutscene');
        this.comic.setOrigin(0.5);

        // Ajusta o tamanho da imagem para cobrir a tela inteira do usuário
        this.comic.setDisplaySize(this.cameras.main.width, this.cameras.main.height);

        // 2. Adiciona o texto piscando na parte inferior
        this.clickText = this.add.text(
            this.cameras.main.centerX, 
            this.cameras.main.height - 50, 
            "CLIQUE EM QUALQUER LUGAR PARA VOLTAR AO MENU", 
            {
                fontFamily: 'monospace',
                fontSize: '20px',
                fill: '#ffffff',
                stroke: '#000000',
                strokeThickness: 4
            }
        );
        this.clickText.setOrigin(0.5);

        // 3. Efeito de piscar do texto
        this.tweens.add({
            targets: this.clickText,
            alpha: 0,
            duration: 800,
            yoyo: true,
            loop: -1
        });

        // 4. Escutadores para avançar de volta para o Menu Principal
        this.input.on('pointerdown', () => this.returnToMenu());
        this.input.keyboard.on('keydown', () => this.returnToMenu());

        // Entrada suave da cena
        this.cameras.main.fadeIn(1000, 0, 0, 0);
    }

    returnToMenu() {
        if (this.cameras.main.fadeEffect.isRunning) return;

        // Saída suave escurecendo a tela
        this.cameras.main.fadeOut(1000, 0, 0, 0);

        this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
            // Volta para a tela inicial de Login (MainMenu)
            this.scene.start('MainMenu');
        });
    }
}