import { Defesa } from './Defesa.js';
import { Worm } from "../entities/Worm.js";

const COR_CLICKER = 0xeeeeee;

export class Clicker extends Defesa {
    static get CUSTO() { return 50; }
    static get RANGE() { return 300; }
    static get LARGURA() { return 100; }
    static get ALTURA() { return 100; }
    static get VIDA() { return 100; }
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
        // Filtramos os inimigos no alcance
        const alvo = this.scene.inimigos.getChildren().find(inimigo => {
            // 1. Deve estar ativo
            if (!inimigo.active) return false;

            // 2. Deve estar no alcance (range)
            const distancia = Phaser.Math.Distance.Between(this.x, this.y, inimigo.x, inimigo.y);
            if (distancia > this.range) return false;

            // 3. REGRA DO WORM: Se for Worm, só foca se NÃO for segmento (ou seja, se for a cabeça)
            if (inimigo instanceof Worm && inimigo.ehSegmento) {
                return false;
            }

            return true; // Se passou por tudo, é um alvo válido (ILY, Trojan ou Cabeça de Worm)
        });

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