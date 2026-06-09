import { Worm } from "../entities/Worm.js";
import { Trojan } from "../entities/Trojan.js";
import { ILY } from "../entities/ILY.js";
import { Pastas } from "../entities/Pastas.js";

export class InputManager {
    constructor(scene) {
        this.scene = scene;
        
        // O Modo Dev começa DESATIVADO por segurança
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

        // =====================================================================
        // --- INTERRUPTOR DO MODO DEV (F2) ---
        // =====================================================================
        this.scene.input.keyboard.on('keydown-F2', () => {
            this.modoDev = !this.modoDev;
            console.log(`[DEV MODE] -> ${this.modoDev ? "ATIVADO 🔓" : "DESATIVADO 🔒"}`);
        });

        // =====================================================================
        // --- CHEATS DE TESTE (SÓ FUNCIONAM SE MODO DEV FOR TRUE) ---
        // =====================================================================

        // T: Adicionar Dinheiro / Bits (+100 BITS)
        this.scene.input.keyboard.on('keydown-T', () => {
            if (!this.modoDev) return;
            this.scene.adicionarBits(100);
        });

        // W: Forçar Avanço de Wave instantaneamente (Conectado perfeitamente ao seu WaveManager)
        this.scene.input.keyboard.on('keydown-Q', () => {
            if (!this.modoDev) return;
            console.log("Cheat: Forçando Avanço de Wave!");

            const wm = this.scene.waveManager;

            if (wm) {
                // 1. Limpa os timers pendentes no Phaser para parar os loops de contagem e spawn antigos
                if (wm.timerGeradorDeWave) wm.timerGeradorDeWave.destroy();
                if (wm.eventoTimer) wm.eventoTimer.destroy();
                
                // Remove todos os delayedCalls e eventos de tempo ativos na cena
                this.scene.time.removeAllEvents();

                // 2. Remove todos os vírus vivos na tela para limpar o mapa imediatamente
                if (this.scene.inimigos) {
                    this.scene.inimigos.clear(true, true);
                }

                // 3. Avança o índice do gerenciador para a próxima configuração
                wm.indiceAtual++;

                // 4. Dispara a lógica de criação da nova horda
                wm.proximaOnda();
            } else {
                console.warn("WaveManager não encontrado em 'this.scene.waveManager'");
            }
        });

        // H: Forçar Pulo para GAME WIN (Puxando a cena 'WinScreen' configurada no seu WaveManager)
        this.scene.input.keyboard.on('keydown-H', () => {
            if (!this.modoDev) return;
            console.log("Cheat: Forçando Game Win!");
            this.limparAudiosDaCena();
            this.scene.time.removeAllEvents();
            
            const bitsAtuais = this.scene.bits || 0;
            this.scene.scene.start('WinScreen', { bits: bitsAtuais }); 
        });

        // K: Forçar Pulo para GAME OVER (Puxando a cena 'GameOver')
        this.scene.input.keyboard.on('keydown-K', () => {
            if (!this.modoDev) return;
            console.log("Cheat: Forçando Game Over!");
            this.limparAudiosDaCena();
            this.scene.time.removeAllEvents();
            this.scene.scene.start('GameOver');
        });

        // --- SPAWNERS DE INIMIGOS ADAPTADOS PARA O SEU MÉTODO STRING spawnInimigo() ---
        this.scene.input.keyboard.on('keydown-Y', () => { if (this.modoDev) this.scene.spawnInimigo('Worm'); });
        this.scene.input.keyboard.on('keydown-E', () => { if (this.modoDev) this.scene.spawnInimigo('Trojan'); });
        this.scene.input.keyboard.on('keydown-R', () => { if (this.modoDev) this.scene.spawnInimigo('ILY'); });
        
        // As pastas usam o clique do mouse para teste
        this.scene.input.keyboard.on('keydown-P', () => { 
            if (this.modoDev) this.debugSpawnNoMouse(Pastas); 
        });
    }

    setupMouse() {
        this.scene.input.on('pointerdown', (pointer) => {
            const dadosAtuais = this.scene.dadosDefesas[this.scene.selecionada];
            const worldPoint = pointer.positionToCamera(this.scene.cameras.main);

            if (dadosAtuais.modo === 'construcao') {
                this.scene.buildManager.tentarConstruir(worldPoint.x, worldPoint.y);
            }
        });
    }

    // Método auxiliar usado apenas para o spawn especial de pastas na mira do mouse
    debugSpawnNoMouse(classeInimigo) {
        const pointer = this.scene.input.activePointer;
        const worldPoint = pointer.positionToCamera(this.scene.cameras.main);
        const inimigo = new classeInimigo(this.scene, worldPoint.x, worldPoint.y);
        this.scene.inimigos.add(inimigo);
    }

    limparAudiosDaCena() {
        if (this.scene.bgmOnda) this.scene.bgmOnda.stop();
        this.scene.sound.stopAll(); 
    }
}