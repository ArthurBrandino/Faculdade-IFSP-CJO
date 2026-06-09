import { Worm } from "../entities/Worm.js";
import { Trojan } from "../entities/Trojan.js";
import { ILY } from "../entities/ILY.js";
import { Pastas } from "../entities/Pastas.js";

export class InputManager {
    constructor(scene) {
        this.scene = scene;
        
        // O Modo Dev começa DESATIVADO por segurança (Ative/Desative com F2)
        this.modoDev = false; 

        this.setupKeys();
        this.setupMouse();
    }

    setupKeys() {
        // --- ATALHOS DE JOGABILIDADE PADRÃO (1, 2, 3, 4) ---
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

        // --- INTERRUPTOR DO MODO DEV (F2) ---
        this.scene.input.keyboard.on('keydown-F2', () => {
            this.modoDev = !this.modoDev;
            console.log(`[DEV MODE] -> ${this.modoDev ? "ATIVADO 🔓" : "DESATIVADO 🔒"}`);
        });

        // --- CHEATS DE CONTROLE DE WAVE E BITS ---
        this.scene.input.keyboard.on('keydown-T', () => {
            if (!this.modoDev) return;
            this.scene.adicionarBits(100);
        });

        this.scene.input.keyboard.on('keydown-Q', () => {
            if (!this.modoDev) return;
            console.log("Cheat: Forçando Avanço de Wave!");
            const wm = this.scene.waveManager;
            if (wm) {
                if (wm.timerGeradorDeWave) wm.timerGeradorDeWave.destroy();
                if (wm.eventoTimer) wm.eventoTimer.destroy();
                this.scene.time.removeAllEvents();
                if (this.scene.inimigos) this.scene.inimigos.clear(true, true);
                wm.indiceAtual++;
                wm.proximaOnda();
            }
        });

        this.scene.input.keyboard.on('keydown-H', () => {
            if (!this.modoDev) return;
            this.limparAudiosDaCena();
            this.scene.time.removeAllEvents();
            this.scene.scene.start('WinScreen', { bits: this.scene.bits || 0 }); 
        });

        this.scene.input.keyboard.on('keydown-K', () => {
            if (!this.modoDev) return;
            this.limparAudiosDaCena();
            this.scene.time.removeAllEvents();
            this.scene.scene.start('GameOver');
        });

        // =====================================================================
        // --- NOVO: SPAWNS DIRETOS POR EVENTO DE TECLA (ESTILO GAME.JS) ---
        // =====================================================================
        
        // Tecla Y -> Spawna Worm no ponteiro atual do mouse
        this.scene.input.keyboard.on('keydown-Y', () => {
            if (!this.modoDev) return;
            const pointer = this.scene.input.activePointer;
            const worldPoint = pointer.positionToCamera(this.scene.cameras.main);
            
            this.scene.inimigos.add(new Worm(this.scene, worldPoint.x, worldPoint.y));
            console.log(`[DEV] Worm spawnado em X: ${Math.round(worldPoint.x)}, Y: ${Math.round(worldPoint.y)}`);
        });

        // Tecla E -> Spawna Trojan no ponteiro atual do mouse
        this.scene.input.keyboard.on('keydown-E', () => {
            if (!this.modoDev) return;
            const pointer = this.scene.input.activePointer;
            const worldPoint = pointer.positionToCamera(this.scene.cameras.main);
            
            this.scene.inimigos.add(new Trojan(this.scene, worldPoint.x, worldPoint.y));
            console.log(`[DEV] Trojan spawnado em X: ${Math.round(worldPoint.x)}, Y: ${Math.round(worldPoint.y)}`);
        });

        // Tecla R -> Spawna ILY no ponteiro atual do mouse
        this.scene.input.keyboard.on('keydown-R', () => {
            if (!this.modoDev) return;
            const pointer = this.scene.input.activePointer;
            const worldPoint = pointer.positionToCamera(this.scene.cameras.main);
            
            this.scene.inimigos.add(new ILY(this.scene, worldPoint.x, worldPoint.y));
            console.log(`[DEV] ILY spawnado em X: ${Math.round(worldPoint.x)}, Y: ${Math.round(worldPoint.y)}`);
        });

        // Tecla P -> Spawna Pasta no ponteiro atual do mouse
        this.scene.input.keyboard.on('keydown-P', () => {
            if (!this.modoDev) return;
            const pointer = this.scene.input.activePointer;
            const worldPoint = pointer.positionToCamera(this.scene.cameras.main);
            
            new Pastas(this.scene, worldPoint.x, worldPoint.y);
            console.log(`[DEV] Pasta spawnada em X: ${Math.round(worldPoint.x)}, Y: ${Math.round(worldPoint.y)}`);
        });
    }

    setupMouse() {
        this.scene.input.on('pointerdown', (pointer) => {
            const worldPoint = pointer.positionToCamera(this.scene.cameras.main);
            const dadosAtuais = this.scene.dadosDefesas[this.scene.selecionada];

            // MODO CONSTRUÇÃO (Slots 2, 3 e 4)
            if (dadosAtuais && dadosAtuais.modo === 'construcao') {
                this.scene.buildManager.tentarConstruir(worldPoint.x, worldPoint.y);
            } 
            // MODO SELEÇÃO 1 (Combate / Interação Manual com Pastas)
            else if (this.scene.selecionada === 1) {
                
                // 1. Dispara a animação/lógica visual do player
                if (this.scene.enzinho && typeof this.scene.enzinho.atacar === 'function') {
                    this.scene.enzinho.atacar(worldPoint, this.scene.inimigos, this.scene.defesas);
                }

                // 2. Passa o clique para o seu CombatManager processar o dano/mineração
                if (this.scene.combatManager && typeof this.scene.combatManager.executarAcao === 'function') {
                    this.scene.combatManager.executarAcao(worldPoint);
                }
            }
        });
    }

    limparAudiosDaCena() {
        if (this.scene.bgmOnda) this.scene.bgmOnda.stop();
        if (this.scene.sound) this.scene.sound.stopAll(); 
    }
}