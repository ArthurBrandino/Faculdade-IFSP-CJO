export class Processador extends Phaser.GameObjects.Rectangle {    
    constructor(scene, x, y) {
        super(scene, x, y, 100, 100, 0x00ff00);
        scene.add.existing(this);
        scene.physics.add.existing(this, true);

        this.vidaMaxima = 100;
        this.vidaAtual = this.vidaMaxima;  
    }

   receberDano(quantidade) {
        this.vidaAtual = Phaser.Math.Clamp(this.vidaAtual - quantidade, 0, this.vidaMaxima);
        this.scene.events.emit('update-hp', this.vidaAtual, this.vidaMaxima);

        // --- PISCAR RÁPIDO E TRANSPARENTE ---
        const overlay = this.scene.flashOverlay;
        if (overlay && this.scene.sys.isActive()) {
            
            this.scene.tweens.killTweensOf(overlay);

            overlay.setAlpha(0.3); 

            // Some em 60 milissegundos (muito rápido)
            this.scene.tweens.add({
                targets: overlay,
                alpha: 0,
                duration: 60,
                ease: 'Linear'
            });
        }

        if (this.vidaAtual <= 0) {
            this.scene.physics.pause();
            this.scene.scene.start('GameOver'); 
        }
    }
}