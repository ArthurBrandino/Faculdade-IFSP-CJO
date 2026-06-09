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
        this.indiceAtual = 0; 
    
        this.proximaOnda();
        this.currentWave = 0;
    }

    proximaOnda() {
        if (!this.configOndas || this.configOndas.length === 0) return;

        // Dentro do seu WaveManager.js, no método proximaOnda()
        if (this.indiceAtual >= this.configOndas.length) {
            console.log("SISTEMA LIMPO!");
            this.scene.events.emit('update-timer', "WIN");

            // Para todos os eventos/timers da gameplay
            this.scene.time.removeAllEvents();
            
            // === NOVO: PARA TODOS OS ÁUDIOS DA GAMEPLAY ===
            this.scene.sound.stopAll(); 
            
            this.scene.cameras.main.fadeOut(1000, 0, 0, 0);
            this.scene.cameras.main.once(Phaser.Cameras.Scene2D.Events.FADE_OUT_COMPLETE, () => {
                // Passamos a quantidade de Bits atual para a tela de vitória usar na barra de tarefas
                // Mude "this.scene.bits" se a sua variável de dinheiro no jogo tiver outro nome
                const bitsAtuais = this.scene.bits || 0; 
                this.scene.scene.start('WinScreen', { bits: bitsAtuais }); 
            });
            return;
        }
        const dadosOnda = this.configOndas[this.indiceAtual];
        
        this.scene.events.emit('update-wave', dadosOnda.id);

        // --- SAFE ZONE ---
        this.emDangerZone = false;
        this.scene.cameras.main.flash(500, 0, 100, 255);
        this.scene.cameras.main.setBackgroundColor(0x001133); 
        
        if (this.scene.backgroundCyber) {
            this.scene.backgroundCyber.clearTint();
        }
        
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
        
        if (this.scene && typeof this.scene.mudarMatrizBackground === 'function') {
            this.scene.mudarMatrizBackground();
        }
        
        this.iniciarContagemRegressiva(dadosOnda.dangerTime / 1000, "DANGER");

        // === NOVO: CRIAR UMA FILA MISTURADA DE INIMIGOS ===
        let filaInimigos = [];

        // 1. Desembrulha a configuração jogando Strings puras para dentro do array
        // Se tem 15 Worms e 2 Trojans, o array terá 17 itens: ['Worm', 'Worm'..., 'Trojan', 'Trojan']
        dadosOnda.inimigos.forEach(config => {
            for (let i = 0; i < config.quantidade; i++) {
                filaInimigos.push(config.classe);
            }
        });

        // 2. Algoritmo de Embaralhamento (Fisher-Yates Shuffle)
        // Mistura a fila completamente para que fiquem totalmente intercalados
        for (let i = filaInimigos.length - 1; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
            [filaInimigos[i], filaInimigos[j]] = [filaInimigos[j], filaInimigos[i]];
        }

        // 3. Calcula um intervalo dinâmico baseado no DangerTime disponível
        // Assim, todos os monstros nascem distribuídos uniformemente ao longo do tempo da wave
        const tempoTotalDisponivel = dadosOnda.dangerTime - 2000; // Margem de 2s para não nascer bicho no último segundo
        const intervaloSpawn = Math.max(200, tempoTotalDisponivel / filaInimigos.length);

        // 4. Um ÚNICO timer cadenciado consumindo a nossa fila misturada
        if (filaInimigos.length > 0) {
            this.timerGeradorDeWave = this.scene.time.addEvent({
                delay: intervaloSpawn,
                repeat: filaInimigos.length - 1,
                callback: () => {
                    if (filaInimigos.length > 0) {
                        const proximoInimigo = filaInimigos.shift(); // Remove e pega o primeiro bicho da fila
                        this.scene.spawnInimigo(proximoInimigo);
                    }
                }
            });
        }

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