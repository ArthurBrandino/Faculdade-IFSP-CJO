import { Defesa } from './Defesa.js';
import { Worm } from "../entities/Worm.js";

export class Lixeira extends Defesa {
    static get CUSTO() { return 200; }
    static get RANGE() { return 300; }
    static get LARGURA() { return 100; }
    static get ALTURA() { return 100; }
    static get VIDA() { return 2; }
    static get TAXA_TIRO() { return 10000; }
    static get DANO() { return 1; }

    constructor(scene, x, y) {
        super(
            scene, 
            x, 
            y, 
            Lixeira.LARGURA, 
            Lixeira.ALTURA, 
            'spr_lixeira',
            Lixeira.VIDA, 
            Lixeira.TAXA_TIRO, 
            Lixeira.DANO, 
            Lixeira.RANGE, 
            Lixeira.CUSTO
        );
        this.alvoPreso = null;
        this.ocupado = false;
        this.cronometro = 0;
        
        // Guarda as escalas originais para os Tweens de impacto não quebrarem o tamanho do sprite
        this.escalaOriginalX = this.scaleX;
        this.escalaOriginalY = this.scaleY;

        // --- AUDIO CONFIG ---
        // Instancia o som de processamento com loop para o caso do tempo de taxa de tiro ser longo
        this.somProcessando = this.scene.sound.add('TrashProcessing', { loop: true, volume: 0.3 });
    }

    update(time, delta) {
        if (!this.ocupado) {
            this.capturar(time);
            return;
        } else {
            this.cronometro += delta;

            if (!this.alvoPreso || !this.alvoPreso.active) {
                this.resetarLixeira(); 
                return;
            }

            this.dano = this.alvoPreso.hp / Lixeira.TAXA_TIRO;
            this.alvoPreso.receberDano(this.dano);

            if (this.cronometro >= Lixeira.TAXA_TIRO || this.alvoPreso.hp <= 0) {
                this.alvoPreso.morrer(false);
                this.finalizarFeedback(); // Aqui para o som de processamento e toca o complete
                this.resetarLixeira();
            }
        }
    }

    capturar(time) {
        const alvo = this.procurarAlvo();
        if (alvo) {
            this.alvoPreso = alvo; 
            this.alvoPreso.estaPreso = true;

            if (typeof this.alvoPreso.promoverProximoSegmento === 'function') {
                console.log("Promovendo novo líder para o Worm...");
                this.alvoPreso.promoverProximoSegmento(); 
            }

            this.alvoPreso.visible = false;
            this.alvoPreso.body.enable = false;
            this.ocupado = true; 

            console.log("INIMIGO CAPTURADO:", this.alvoPreso);
            this.capturarFeedback();
        }
    }

    receberDano(quantidade) {
        // Aplica o dano usando a lógica da classe pai (Defesa)
        super.receberDano(quantidade);
        
        // Se a lixeira zerar os pontos de vida (hp ou vida, dependendo de como está na classe pai)
        if (this.hp <= 0) {
            
            // Se ela continha um monstro preso, cospe o bicho de volta no mapa antes de sumir
            if (this.ocupado && this.alvoPreso && this.alvoPreso.active) {   
                this.alvoPreso.setPosition(this.x, this.y);
                this.alvoPreso.visible = true;
                if (this.alvoPreso.body) {
                    this.alvoPreso.body.enable = true;
                }
                this.alvoPreso.estaPreso = false;
            }
            
            // Para o áudio imediatamente para não ficar tocando em loop no limbo
            if (this.somProcessando) {
                if (this.somProcessando.isPlaying) {
                    this.somProcessando.stop();
                }
                this.somProcessando.destroy(); // Remove o áudio da memória do gerenciador de som
            }

            if (this.tweenProcessando) {
                this.tweenProcessando.stop();
            }
            
            // ATENÇÃO: Usa o método padrão do Phaser para deletar o objeto de vez
            this.destroy();
        }
    }

    resetarLixeira() {
        this.alvoPreso = null;
        this.cronometro = 0;
        this.ocupado = false;
    
        if (this.tweenProcessando) {
            this.tweenProcessando.stop();
            this.tweenProcessando = null;
        }

        // Garante que o som pare caso o inimigo saia ou quebre por outro motivo externo
        if (this.somProcessando && this.somProcessando.isPlaying) {
            this.somProcessando.stop();
        }

        this.setAngle(0);
        this.setScale(this.escalaOriginalX, this.escalaOriginalY); 
    }

    //============================================================ Visual e Sonoro ===========================================

    capturarFeedback() {
        // --- ÁUDIO: Inicia o som de trituração/deletando ---
        if (this.somProcessando && !this.somProcessando.isPlaying) {
            this.somProcessando.play();
        }

        // 1. Efeito de Tremor mecânico enquanto deleta
        this.tweenProcessando = this.scene.tweens.add({
            targets: this,
            angle: { from: -6, to: 6 }, 
            duration: 60, 
            repeat: -1,
            yoyo: true
        });

        // 2. Efeito de "Squeeze" (Esmagar de leve ao engolir o vírus)
        this.scene.tweens.add({
            targets: this,
            scaleX: this.escalaOriginalX * 1.3, 
            scaleY: this.escalaOriginalY * 0.7,
            duration: 100,
            yoyo: true,
            ease: 'Back.easeOut'
        });
    }

    finalizarFeedback() {
        // --- ÁUDIO: Para a trituração e toca o aviso de concluído (Lixeira Esvaziada) ---
        if (this.somProcessando && this.somProcessando.isPlaying) {
            this.somProcessando.stop();
        }
        this.scene.sound.play('TrashComplete', { volume: 2 });

        if (this.tweenProcessando) {
            this.tweenProcessando.stop();
            this.tweenProcessando = null;
        }
        this.setAngle(0);

        // 3. Efeito Pop (Sinalizando que terminou de esvaziar/deletar)
        this.scene.tweens.add({
            targets: this,
            scaleX: this.escalaOriginalX * 1.4,
            scaleY: this.escalaOriginalY * 1.4,
            alpha: 0.7,
            duration: 120,
            yoyo: true,
            onComplete: () => {
                this.setScale(this.escalaOriginalX, this.escalaOriginalY); 
                this.setAlpha(1);
            }
        });
    }
}