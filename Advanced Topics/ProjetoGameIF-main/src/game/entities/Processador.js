export class Processador extends Phaser.GameObjects.Rectangle {    
    constructor(scene, x, y) {
        super(scene, x, y, 100, 100, 0x00ff00);
        scene.add.existing(this);
        scene.physics.add.existing(this, true);

        this.podeTocarSomHit = true;
        this.somHit = scene.sound.add('hit_processador');

        this.vidaMaxima = 100;
        this.vidaAtual = this.vidaMaxima;  
    }

  
    receberDano(quantidade) {
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

            //Som do Processador sendo atacado
            if (this.somHit) this.somHit.play();

            //Feedback Visual
            //this.setTint(0xff0000);
            //this.alpha = 0.7; 

            // Restaurar o processador 
            this.scene.time.delayedCall(150, () => {
                //this.clearTint();            
                //this.alpha = 1;             
                this.podeTocarSomHit = true;
            });
        }
    }

    destruirEGameOver() {
        if (this.somHit) {
            this.somHit.stop();
            this.somHit.destroy();
        }
        this.scene.scene.start('GameOver'); 
    }
}