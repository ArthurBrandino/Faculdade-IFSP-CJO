import { Pastas } from '../entities/Pastas.js';

export class WaveManager {
    constructor(scene, configOndas) {
        this.scene = scene;
        this.configOndas = configOndas;
        this.indiceAtual = 0;
        this.emDangerZone = false;

        const larguraTela = this.scene.cameras.main.width;
        const alturaTela = this.scene.cameras.main.height;

        this.textoTimer = this.scene.add.text(larguraTela - 150, alturaTela - 20, '', {
            fontSize: '48px',
            fill: '#ffffff',
            fontFamily: 'monospace',
            stroke: '#000',
            strokeThickness: 6
        }).setOrigin(0.5).setScrollFactor(0);
    }

    iniciarSistema() {
        this.proximaOnda();
    }

    proximaOnda() {
        const dadosOnda = this.configOndas[this.indiceAtual];
        
        if (!dadosOnda) return;

        // --- SAFE ZONE ---
        this.emDangerZone = false;
        this.scene.cameras.main.flash(500, 0, 100, 255);
        this.scene.cameras.main.setBackgroundColor(0x001133); 
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

        // Para cada tipo de inimigo definido na sub-rotina daquela wave
        dadosOnda.inimigos.forEach(config => {
            this.scene.time.addEvent({
                delay: config.intervalo,
                repeat: config.quantidade - 1,
                callback: () => {
                    this.scene.spawnInimigo(config.classe);
                }
            });
        });

        // O tempo de perigo acaba, mas a onda só termina quando os inimigos morrerem
        this.scene.time.delayedCall(dadosOnda.dangerTime, () => {
            this.verificarFimDeOnda();
        });
    }

    iniciarContagemRegressiva(segundos, status) {
        let tempoRestante = segundos;
        
        // Se já existir um evento de timer, removemos para não encavalar
        if (this.eventoTimer) this.eventoTimer.remove();

        this.eventoTimer = this.scene.time.addEvent({
            delay: 1000,
            callback: () => {
                tempoRestante--;
                this.textoTimer.setText(`${status}: ${tempoRestante}s`);
                
                if (tempoRestante <= 0) {
                    this.textoTimer.setText("");
                    this.eventoTimer.remove();
                }
            },
            loop: true
        });
    }

    verificarFimDeOnda() {
        // Checa a cada segundo se a tela está limpa
        const check = this.scene.time.addEvent({
            delay: 1000,
            callback: () => {
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