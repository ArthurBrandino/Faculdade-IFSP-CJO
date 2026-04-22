import { Inimigo } from "./Virus";
import { Worm } from "./Worm";

const COR_TROJAN = 0x8C5C51;

export class Trojan extends Inimigo {
    constructor(scene, x, y){
        const velocidade = 30;
        const vida = 40;
        const dano = 10;
        const largura = 32; 
        const altura = 32;
        const frequencia = 0;
        const amplitude = 0;

        super(scene, x, y, largura, altura, vida, velocidade, dano, frequencia, amplitude);
        this.setFillStyle(COR_TROJAN);
    }

    preUpdate(time, delta){
        super.preUpdate(time, delta);
    }

    morrer() {
        let quantidade = Phaser.Math.Between(2, 4);
        for (let i = 0; i < quantidade; i++) {
            const wormFilho = new Worm(this.scene, this.x, this.y);
        
            if (this.scene.inimigos) {
                this.scene.inimigos.add(wormFilho);
            }
        }
        super.morrer();
    }
}