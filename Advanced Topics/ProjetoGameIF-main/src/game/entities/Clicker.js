import { Defesa } from './Defesa.js';

const COR_CLICKER = 0xeeeeee;

export class Clicker extends Defesa {
    constructor(scene, x, y) {
        const vida = 100;     // HP
        const taxaTiro = 200; // SPEED (intervalo entre tiros)
        const dano = 1;       // DANO
        const alcance = 300;  // RANGE
        const custo = 50;     // CUSTO

        super(scene, x, y, vida, taxaTiro, dano, alcance, custo);
        this.setFillStyle(COR_CLICKER);
        this.proximoTiro = 0;
    }

    update(time, delta) {
        if (time > this.proximoTiro) {
            this.atirarNoMaisProximo(time);
        }
    }

    atirarNoMaisProximo(time) {
        // Usamos this.range que já foi definido no super da Defesa.js
        const inimigo = this.scene.inimigos.getChildren().find(i => 
            i.active && Phaser.Math.Distance.Between(this.x, this.y, i.x, i.y) <= this.range
        );

        if (inimigo) {
            inimigo.receberDano(this.dano); 
            this.proximoTiro = time + this.speed; // Usamos this.speed definido no super
            
            // Feedback visual de clique
            this.scene.tweens.add({
                targets: this,
                scale: 0.7,
                duration: 50,
                yoyo: true
            });
        }
    }
}