import Phaser from 'phaser';

export class IntroCutscene extends Phaser.Scene {
    constructor() {
        super({ key: 'IntroCutscene' });
    }

    create() {
        // 1. Adiciona a imagem única do seu quadrinho centralizada na tela
        this.comic = this.add.image(this.cameras.main.centerX, this.cameras.main.centerY, 'introducao_cutscene');
        this.comic.setOrigin(0.5);

        // Ajusta o tamanho da imagem para cobrir a tela inteira se necessário
        this.comic.setDisplaySize(this.cameras.main.width, this.cameras.main.height);

        // 2. Adiciona o texto piscando na parte inferior da tela
        // Ele fica posicionado horizontalmente no centro e 50 pixels acima da borda inferior (height - 50)
        this.clickText = this.add.text(
            this.cameras.main.centerX, 
            this.cameras.main.height - 50, 
            "CLIQUE EM QUALQUER LUGAR PARA CONTINUAR", 
            {
                fontFamily: 'monospace', // Mantém o estilo de sistema operacional do Windows XP
                fontSize: '20px',
                fill: '#ffffff', // Cor branca
                stroke: '#000000', // Contorno preto para garantir leitura sobre qualquer fundo
                strokeThickness: 4
            }
        );
        this.clickText.setOrigin(0.5); // Centraliza o próprio ponto pivô do texto

        // 3. Cria o efeito de piscar (Tween de Opacidade)
        this.tweens.add({
            targets: this.clickText,
            alpha: 0,             // Vai diminuir a opacidade até ficar invisível
            duration: 800,        // Tempo da transição (800 milissegundos)
            yoyo: true,           // Faz o caminho reverso (volta a ficar visível)
            loop: -1              // Loop infinito (-1)
        });

        // 4. Cria os escutadores para aguardar a ação do jogador
        this.input.on('pointerdown', () => this.startGame());
        this.input.keyboard.on('keydown', () => this.startGame());

        // Efeito visual suave de entrada na cena
        this.cameras.main.fadeIn(1000, 0, 0, 0);
    }

    startGame() {
        // Evita múltiplos cliques bugarem a transição
        if (this.cameras.main.fadeEffect.isRunning) return;

        // Efeito visual de saída
        this.cameras.main.fadeOut(1000, 0, 0, 0);

        this.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
            this.scene.start('Game'); 
        });
    }
}