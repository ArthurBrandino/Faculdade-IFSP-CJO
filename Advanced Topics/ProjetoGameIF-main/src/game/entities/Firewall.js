import { Defesa } from './Defesa.js';
import { Worm } from "../entities/Worm.js";

const COR_FIREWALL = 0xe74c3c;

export class Firewall extends Defesa {
    static get CUSTO() { return 10; }
    static get LARGURA() { return 50; }
    static get ALTURA() { return 50; }
    static get VIDA() { return 200; }

    constructor(scene, x, y) {
        super(
            scene, 
            x, 
            y, 
            Firewall.LARGURA, 
            Firewall.ALTURA, 
            Firewall.VIDA,  
            Firewall.CUSTO
        );
        this.danoCritico = 10;
        this.setFillStyle(COR_FIREWALL);
    }

    receberDano(quantidade, atacante){
        let danoFinal = quantidade;

        if(atacante instanceof Worm){
            danoFinal = quantidade * 10;
            console.log("Dano crítico = ", danoFinal, " Worm corroendo o Firewall.");
        }

        super.receberDano(danoFinal);
    }
}