import { Inimigo } from "./Virus";

export class ILY extends Inimigo {
    constructor(scene, x, y){
        const velocidade = 70;
        const vida = 15; 
        const dano = 20;
        const largura = 50; 
        const altura = 35;
        const frequencia = 0.005;
        const amplitude = 4;

        super(scene, x, y, largura, altura, 'spr_letter', vida, velocidade, dano, frequencia, amplitude);
        
     
        this.alvejavel = false; // Indica para o sistema de mira que este monstro deve ser ignorado
    }

    // Mantemos a segurança: se algo ainda conseguir bater nele por erro, ele não toma dano
    receberDano(quantidade) {
        return; 
    }

    explodir(alvo, dano) {
        alvo.receberDano(dano); // Hitkill na construção que ele tocou
        this.destroy(); 
    }
}