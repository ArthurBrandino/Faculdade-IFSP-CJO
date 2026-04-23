import { Defesa } from './Defesa.js';
import { Worm } from "../entities/Worm.js";

const COR_CLICKER = 0xeeeeee;

export class Clicker extends Defesa {
    constructor(scene, x, y) {
        const largura = 100;
        const altura = 100;
        const vida = 100;     // HP
        const taxaTiro = 20000; // SPEED (intervalo entre tiros)
        const dano = 1;       // DANO
        const alcance = 300;  // RANGE
        const custo = 50;     // CUSTO

        super(scene, x, y, largura, altura, vida, taxaTiro, dano, alcance, custo);
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