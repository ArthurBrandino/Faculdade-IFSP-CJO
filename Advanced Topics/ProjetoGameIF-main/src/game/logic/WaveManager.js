import { Pastas } from '../entities/Pastas.js';
export class WaveManager {
    constructor(scene, configOndas) {
        this.scene = scene;
        this.configOndas = configOndas;
        this.indiceAtual = 0;
        this.emDangerZone = false;
        this.eventoTimer = null;

        this.scene.events.once('GameOver', () => {
            // Procura por qualquer timer que você tenha criado
            if (this.timerGeradorDeWave) {
                this.timerGeradorDeWave.remove();
            }
            // Se você usa o clock do phaser diretamente:
            this.scene.time.removeAllEvents(); 
        });
    }

    iniciarSistema() {
        this.proximaOnda();
        this.currentWave = 0;
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
        this.scene.sound.play('EvilLaugh');
        this.currentWave++; 
        this.scene.events.emit('proxima-wave', this.currentWave);
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
        if (this.eventoTimer) this.eventoTimer.destroy(); // Use destroy em vez de remove para ser mais agressivo

        this.eventoTimer = this.scene.time.addEvent({
            delay: 1000,
            callback: () => {
                // SE A CENA MORREU, PARA O TIMER IMEDIATAMENTE
                if (!this.scene || !this.scene.sys.isActive()) {
                    if (this.eventoTimer) this.eventoTimer.destroy();
                    return;
                }

                tempoRestante--;
                
                this.scene.events.emit('update-timer', `${status}: ${tempoRestante}s`);
                
                if (tempoRestante <= 0) {
                    this.eventoTimer.destroy();
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
                    this.scene.sound.play('WaveClear');
                    this.proximaOnda();
                }
            },
            loop: true
        });
    }
}