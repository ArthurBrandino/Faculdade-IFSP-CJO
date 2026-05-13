import { Worm } from "../entities/Worm.js";

export class CollisionManager {
    constructor(scene) {
        this.scene = scene;
        this.setupCollisions();
    }

    setupCollisions() {
        // Colisão com as Defesas e com o Processador
        this.scene.physics.add.overlap(
            this.scene.inimigos, 
            [this.scene.defesas, this.scene.processador], 
            this.tratarColisao, 
            null, 
            this
        );
    }

    tratarColisao(obj1, obj2) {
        let inimigo, alvo;

        // Identifica quem é o inimigo e quem é o alvo
        if (obj1 instanceof Worm || obj1.velocidade !== undefined) {
            inimigo = obj1;
            alvo = obj2;
        } else {
            inimigo = obj2;
            alvo = obj1;
        }

        if (!inimigo.active || !alvo.active) return;

        if (inimigo instanceof Worm) {
            if (!inimigo.ehSegmento) {
                inimigo.aoColidir(alvo); 
            }
        } else {
            // Vírus comum
            if (alvo.receberDano) {
                alvo.receberDano(inimigo.dano || 10, inimigo); 
            }
            if (inimigo.morrer) inimigo.morrer();
        }
    }
}