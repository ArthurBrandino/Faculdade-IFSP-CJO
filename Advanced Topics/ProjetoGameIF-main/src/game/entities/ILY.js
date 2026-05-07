import { Inimigo } from "./Virus";


export class ILY extends Inimigo {
    constructor(scene, x, y){
        const velocidade = 80;
        const vida = 1;
        const dano = 20;
        const largura = 60; 
        const altura = 50;
        const frequencia = 0.005;
        const amplitude = 4;

        //super(scene, x, y, 'ily_texture', vida, velocidade);
        super(scene, x, y, largura, altura, 'spr_letter', vida, velocidade, dano, frequencia, amplitude);

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