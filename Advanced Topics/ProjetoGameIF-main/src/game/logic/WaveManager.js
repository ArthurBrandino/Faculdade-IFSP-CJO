import { Pastas } from '../entities/Pastas.js';
export class WaveManager {
    constructor(scene, configOndas) {
        this.scene = scene;
        this.configOndas = configOndas;
        this.indiceAtual = 0;
        this.emDangerZone = false;
        this.eventoTimer = null;
    }

    iniciarSistema() {
        this.proximaOnda();
    }

    proximaOnda() {
        if (!this.configOndas || this.configOndas.length === 0) return;

        if (this.indiceAtual >= this.configOndas.length) {
            console.log("SISTEMA LIMPO!");
            this.scene.events.emit('update-timer', "WIN");
            return;
        }

        const dadosOnda = this.configOndas[this.indiceAtual];
        
        // Atualiza o número da Wave na UI
        this.scene.events.emit('update-wave', dadosOnda.id);

        // --- SAFE ZONE ---
        this.emDangerZone = false;
        this.scene.cameras.main.flash(500, 0, 100, 255);
        this.scene.cameras.main.setBackgroundColor(0x001133); 
        
        // Envia para o relógio da Hotbar
        this.iniciarContagemRegressiva(dadosOnda.safeTime / 1000, "SAFE");

        if (dadosOnda.pastasParaCriar) {
            Pastas.gerarGrupo(this.scene, dadosOnda.pastasParaCriar);
        }

        this.scene.time.delayedCall(dadosOnda.safeTime, () => {
            this.iniciarDangerZone(dadosOnda);
        });
    }

    iniciarDangerZone(dadosOnda) {
        this.emDangerZone = true;
        this.scene.cameras.main.flash(500, 255, 0, 0);
        this.scene.cameras.main.setBackgroundColor(0x330000);
        
        this.iniciarContagemRegressiva(dadosOnda.dangerTime / 1000, "DANGER");

        dadosOnda.inimigos.forEach(config => {
            this.scene.time.addEvent({
                delay: config.intervalo,
                repeat: config.quantidade - 1,
                callback: () => {
                    this.scene.spawnInimigo(config.classe);
                    
                }
            });
        });

        this.scene.time.delayedCall(dadosOnda.dangerTime, () => {
            this.verificarFimDeOnda();
        });
    }

    iniciarContagemRegressiva(segundos, status) {
        let tempoRestante = segundos;
        if (this.eventoTimer) this.eventoTimer.remove();

        this.eventoTimer = this.scene.time.addEvent({
            delay: 1000,
            callback: () => {
                tempoRestante--;
                
                // CRITICAL: Isso envia o dado para fora do WaveManager
                this.scene.events.emit('update-timer', `${status}: ${tempoRestante}s`);
                
                if (tempoRestante <= 0) {
                    this.eventoTimer.remove();
                }
            },
            loop: true
        });
    }

    verificarFimDeOnda() {
        this.scene.events.emit('update-timer', "CLEANING...");
        
        const check = this.scene.time.addEvent({
            delay: 1000,
            callback: () => {
                // Se não houver mais inimigos ativos no grupo da cena
                if (this.scene.inimigos.countActive() === 0) {
                    check.remove();
                    this.indiceAtual++;
                    this.proximaOnda();
                }
            },
            loop: true
        });
    }
}