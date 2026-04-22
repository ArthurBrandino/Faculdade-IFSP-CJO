export class Processador extends Phaser.GameObjects.Rectangle {    
    constructor(scene, x, y) {
        const largura = 100; 
        const altura = 100;

        super(scene, x, y, largura, altura, 0x00ff00);
        scene.add.existing(this);
        scene.physics.add.existing(this, true);

        this.vidaMaxima = 100;
        this.vidaAtual = this.vidaMaxima;

        this.barraVida = scene.add.graphics();
        this.atualizarBarra();
        this.barraVida.setScrollFactor(0);

        this.textoHUD = scene.add.text(20, 45, 'CPU_STABILITY: OK', {
            fontSize: '14px',
            fill: '#00ff00',
            fontFamily: 'monospace'
        }).setScrollFactor(0);
    }

    receberDano(quantidade) {
        this.vidaAtual -= quantidade;
        this.vidaAtual = Phaser.Math.Clamp(this.vidaAtual, 0, this.vidaMaxima);
        this.atualizarBarra();

        if (this.vidaAtual <= 0) {
            
            this.scene.physics.pause();
            
            this.scene.scene.start('GameOver'); 
        }
    }

    atualizarBarra() {
        this.barraVida.clear();

        const xHUD = 20; // Posição X no canto da tela
        const yHUD = 20; // Posição Y no canto da tela
        const larguraTotal = 200; // Barra maior para o HUD
        this.barraVida.fillStyle(0x000000, 0.5); 
        this.barraVida.fillRect(xHUD, yHUD, larguraTotal, 20);

        const larguraVida = (this.vidaAtual / this.vidaMaxima) * larguraTotal;
        this.barraVida.fillStyle(0x00ff00);
        this.barraVida.fillRect(xHUD, yHUD, larguraVida, 20);
        
        this.barraVida.lineStyle(2, 0xffffff);
        this.barraVida.strokeRect(xHUD, yHUD, larguraTotal, 20);
    }
}