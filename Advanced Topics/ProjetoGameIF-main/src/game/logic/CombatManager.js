import { Pastas } from '../entities/Pastas.js';
import { Worm } from "../entities/Worm.js";

export class CombatManager {
    constructor(scene) {
        this.scene = scene;
    }

    executarAcao(worldPoint) {
        // 1. Verificar se clicou em uma Pasta
        const pastasNoClique = this.scene.physics.overlapCirc(worldPoint.x, worldPoint.y, 10);
        let interagiuComPasta = false;

        pastasNoClique.forEach(corpo => {
            const objeto = corpo.gameObject;
            if (objeto instanceof Pastas) {
                objeto.interagir();
                interagiuComPasta = true;
            }
        });

        // 2. Se não clicou em pasta, verificar se tem inimigo perto para bater
        if (!interagiuComPasta) {
            const inimigosNoRaio = this.scene.inimigos.getChildren().filter(inimigo => {
                const distancia = Phaser.Math.Distance.Between(worldPoint.x, worldPoint.y, inimigo.x, inimigo.y);
                const alvoValido = inimigo instanceof Worm ? !inimigo.ehSegmento : true;
                return distancia < 50 && inimigo.active && alvoValido;
            });

            inimigosNoRaio.sort((a, b) => {
                const distA = Phaser.Math.Distance.Between(worldPoint.x, worldPoint.y, a.x, a.y);
                const distB = Phaser.Math.Distance.Between(worldPoint.x, worldPoint.y, b.x, b.y);
                return distA - distB;
            });

            const alvoUnico = inimigosNoRaio[0];
            if (alvoUnico && alvoUnico.receberDano) {
                alvoUnico.receberDano(this.scene.enzinho.danoAtaque);
            }
        }
    }
}