import { Defesa } from './Defesa.js';

const COR_CLICKER = 0xeeeeee;

export class Clicker extends Defesa {
    static get CUSTO() { return 50; }
    static get RANGE() { return 300; }
    static get LARGURA() { return 100; }
    static get ALTURA() { return 100; }
    static get VIDA() { return 1; }
    static get TAXA_TIRO() { return 2000; }
    static get DANO() { return 1; }

    constructor(scene, x, y) {
        super(
            scene, 
            x, 
            y, 
            Clicker.LARGURA, 
            Clicker.ALTURA, 
            Clicker.VIDA, 
            Clicker.TAXA_TIRO, 
            Clicker.DANO, 
            Clicker.RANGE, 
            Clicker.CUSTO
        );
        this.setFillStyle(COR_CLICKER);
        this.proximoTiro = 0;
    }

    update(time, delta) {
        if (time > this.proximoTiro) {
            this.atirarNoMaisProximo(time);
        }
    }

    atirarNoMaisProximo(time) {
        const alvo = this.procurarAlvo();

        if (alvo) {
            alvo.receberDano(this.dano); 
            this.proximoTiro = time + this.speed;
            
            // Feedback visual
            this.scene.tweens.add({
                targets: this,
                scale: 0.8,
                duration: 50,
                yoyo: true
            });
        }
    }
}