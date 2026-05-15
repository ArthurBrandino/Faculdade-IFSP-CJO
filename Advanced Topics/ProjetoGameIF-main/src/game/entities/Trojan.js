import { Inimigo } from "./Virus";
import { Worm } from "./Worm";

export class Trojan extends Inimigo {
    constructor(scene, x, y){
        const velocidade = 30;
        const vida = 40;
        const dano = 10;
        const largura = 50; 
        const altura = 50;
        const frequencia = 0;
        const amplitude = 0;

        super(scene, x, y, largura, altura, 'spr_trojan', vida, velocidade, dano, frequencia, amplitude);
        
    }

    preUpdate(time, delta) {
        super.preUpdate(time, delta);

        // Verifica a velocidade no corpo físico
        if (this.body) {
            if (this.body.velocity.x > 0) {
                // Se a velocidade X é positiva, ele vai para a direita
                this.setFlipX(false); 
            } else if (this.body.velocity.x < 0) {
                // Se a velocidade X é negativa, ele vai para a esquerda (Inverte o sprite)
                this.setFlipX(true); 
            }
        }
    }

    morrer(gerarFilhos = true) {
        if(gerarFilhos)
        {
            let quantidade = Phaser.Math.Between(2, 4);
            for (let i = 0; i < quantidade; i++) {
                
                const offsetX = Phaser.Math.Between(-30, 30);
                const offsetY = Phaser.Math.Between(-30, 30);

                const wormFilho = new Worm(
                    this.scene, 
                    this.x + offsetX, 
                    this.y + offsetY
                );
            
                if (this.scene.inimigos) {
                    this.scene.inimigos.add(wormFilho);

                    
                }
            }
        }
        super.morrer(gerarFilhos);
    }
}