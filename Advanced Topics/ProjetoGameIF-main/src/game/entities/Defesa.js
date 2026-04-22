import Phaser from 'phaser';

export class Defesa extends Phaser.GameObjects.Rectangle {
    constructor(scene, x, y, hp, speed, dano, range, custo) {
        const largura = 100;
        const altura = 100;
        super(scene, x, y, largura, altura);
        
        scene.add.existing(this);
        scene.physics.add.existing(this, true);
        
        this.hp = hp;
        this.maxHp = hp;
        this.speed = speed;
        this.dano = dano;
        this.range = range
        this.custo = custo;
    }

    receberDano(quantidade) {
        this.hp -= quantidade;
        
        
        this.scene.tweens.add({
            targets: this,
            tint: 0xff0000,
            duration: 100,
            yoyo: true,
            onComplete: () => this.clearTint()
        });

        if (this.hp <= 0) {
            this.destruir();
        }
    }

    destruir() {
        this.destroy();
    }
}