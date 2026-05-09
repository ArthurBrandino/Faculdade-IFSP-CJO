import Phaser from 'phaser';

export class Inimigo extends Phaser.GameObjects.Sprite {
    constructor(scene, x, y, largura, altura, spriteKey, hp, speed, dano, freq = 0, amp = 0) {
        super(scene, x, y, spriteKey);
        
        this.setDisplaySize(largura, altura);

        scene.add.existing(this);
        scene.physics.add.existing(this);
        //this.body.setSize(largura, altura);


        this.hp = hp;
        this.speed = speed;
        this.dano = dano;
        this.frequencia = freq; 
        this.amplitude = amp;
        this.alvo = scene.processador; // Todos focam no processador por padrão

        
    }

    preUpdate(time, delta) {
        if (this.alvo && this.alvo.active) {
            this.scene.physics.moveToObject(this, this.alvo, this.speed);

            // Se tiver oscilação, aplica a lógica matemática
            if (this.amplitude > 0) {
                const angulo = Phaser.Math.Angle.Between(this.x, this.y, this.alvo.x, this.alvo.y);
                const oscilacao = Math.sin(time * this.frequencia) * this.amplitude;

                this.x += Math.cos(angulo + Math.PI/2) * oscilacao;
                this.y += Math.sin(angulo + Math.PI/2) * oscilacao;
            }
        }
    }

    

    receberDano(quantidade) {
        this.hp -= quantidade;

        this.scene.tweens.add({
            targets: this,
            alpha: 0.5,
            duration: 50,
            yoyo: true
        });
        
        if (this.hp <= 0) {
            this.morrer();
        }
    }

    morrer(gerarFilhos = true) {
        if (this.scene.adicionarBits) { 
            let bits = Phaser.Math.Between(1, 5);
            this.scene.adicionarBits(bits);
        }
        this.destroy();
    }
}