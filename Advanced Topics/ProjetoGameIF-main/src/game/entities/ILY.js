import { Inimigo } from "./Virus";

const COR_ILY = 0xFF0000;

export class ILY extends Inimigo {
    constructor(scene, x, y){
        const velocidade = 80;
        const vida = 1;
        const dano = 20;
        const largura = 25; 
        const altura = 25;
        const frequencia = 0.005;
        const amplitude = 4;

        //super(scene, x, y, 'ily_texture', vida, velocidade);
        super(scene, x, y, largura, altura, vida, velocidade, dano, frequencia, amplitude);

        this.setFillStyle(COR_ILY);
    }

    preUpdate(time, delta) {
        super.preUpdate(time, delta);
    }

    explodir(alvo) {
        // Causa dano alto e se destrói
        alvo.receberDano(50); 
        this.destroy();
    }
}