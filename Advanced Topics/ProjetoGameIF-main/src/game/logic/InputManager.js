import { Worm } from "../entities/Worm.js";
import { Trojan } from "../entities/Trojan.js";
import { ILY } from "../entities/ILY.js";
import { Pastas } from "../entities/Pastas.js";

export class InputManager {
    constructor(scene) {
        this.scene = scene;
        this.setupKeys();
        this.setupMouse();
    }
    setupKeys() {
        // Atalhos de seleção (1, 2, 3, 4)
        const chaves = ['ONE', 'TWO', 'THREE', 'FOUR'];
        chaves.forEach((key, index) => {
            this.scene.input.keyboard.on(`keydown-${key}`, () => {
                this.scene.selecionada = index + 1;
                this.scene.buildManager.atualizarPreview(
                    this.scene.input.activePointer, 
                    this.scene.dadosDefesas[this.scene.selecionada]
                );
            });
        });

        // Atalhos de Debug/Teste
        this.scene.input.keyboard.on('keydown-Q', () => this.debugSpawn(Worm));
        this.scene.input.keyboard.on('keydown-E', () => this.debugSpawn(Trojan));
        this.scene.input.keyboard.on('keydown-R', () => this.debugSpawn(ILY));
        this.scene.input.keyboard.on('keydown-P', () => this.debugSpawn(Pastas));
        this.scene.input.keyboard.on('keydown-T', () => this.scene.adicionarBits(100));
    }

    setupMouse() {
        this.scene.input.on('pointerdown', (pointer) => {
            const dadosAtuais = this.scene.dadosDefesas[this.scene.selecionada];
            
            // Usando getWorldPoint para garantir que o clique ignore o deslocamento da câmera
            const worldPoint = this.scene.cameras.main.getWorldPoint(pointer.x, pointer.y);

            if (dadosAtuais.modo === 'construcao') {
                this.scene.buildManager.tentarConstruir(worldPoint.x, worldPoint.y);
            } else {
                if (this.scene.combatManager) {
                    this.scene.combatManager.executarAcao(worldPoint); 
                }
            }
        });
    }

    debugSpawn(classeInimigo) {
        const pointer = this.scene.input.activePointer;
        const worldPoint = this.scene.cameras.main.getWorldPoint(pointer.x, pointer.y);
        const inimigo = new classeInimigo(this.scene, worldPoint.x, worldPoint.y);
        this.scene.inimigos.add(inimigo);
    }
}