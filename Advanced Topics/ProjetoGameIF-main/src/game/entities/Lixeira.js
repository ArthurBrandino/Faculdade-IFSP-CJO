import { Defesa } from './Defesa.js';
import { Worm } from "../entities/Worm.js";

const COR_LIXEIRA = 0x999999;

export class Lixeira extends Defesa {
    static get CUSTO() { return 200; }
    static get RANGE() { return 300; }
    static get LARGURA() { return 100; }
    static get ALTURA() { return 100; }
    static get VIDA() { return 100; }
    static get TAXA_TIRO() { return 5000; }
    static get DANO() { return 1; }

    constructor(scene, x, y) {
        super(
            scene, 
            x, 
            y, 
            Lixeira.LARGURA, 
            Lixeira.ALTURA, 
            Lixeira.VIDA, 
            Lixeira.TAXA_TIRO, 
            Lixeira.DANO, 
            Lixeira.RANGE, 
            Lixeira.CUSTO
        );
        this.alvoPreso = null;
        this.ocupado = false;
        this.cronometro = 0;
        
        this.setFillStyle(COR_LIXEIRA);
    }

    update(time, delta) {
        if (!this.ocupado) {
            this.capturar(time);
            return;
        }else{
            this.cronometro += delta;

            if (!this.alvoPreso || !this.alvoPreso.active) {
                this.resetarLixeira(); 
                return;
            }

            this.dano = this.alvoPreso.hp/Lixeira.TAXA_TIRO
            this.alvoPreso.receberDano(this.dano);

            if(this.cronometro >= Lixeira.TAXA_TIRO || this.alvoPreso.hp <= 0)
            {
                this.alvoPreso.morrer(false);
                this.finalizarFeedback()
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

            console.log("iNIMIGO CAPTURADO:", this.alvoPreso);
            this.capturarFeedback();
        }
    }

    receberDano(quantidade) {
        super.receberDano(quantidade);
        if (this.hp <= 0) {
            if(this.ocupado)
            {   
                this.alvoPreso.setPosition(this.x, this.y);
                this.alvoPreso.visible = true;
                this.alvoPreso.body.enable = true;
            }
            this.destruir();
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
        this.setAngle(0);
        this.setFillStyle(COR_LIXEIRA);
    }

    //============================================================Visual===========================================

    capturarFeedback() {
        this.tweenProcessando = this.scene.tweens.add({
            targets: this,
            angle: { from: -2, to: 2 },
            duration: 100,
            repeat: -1,
            yoyo: true
        });

        this.scene.tweens.add({
            targets: this,
            scaleX: 1.3,
            scaleY: 0.7,
            duration: 100,
            yoyo: true,
            ease: 'Back.easeOut',
            onComplete: () => {
                this.setFillStyle(0xffa500); 
            }
        });
    }

    finalizarFeedback() {
        // Para o balanço e reseta o ângulo
        if (this.tweenProcessando) {
            this.tweenProcessando.stop();
            this.tweenProcessando = null;
        }
        this.setAngle(0);

        // Efeito de "explosão" de limpeza
        this.scene.tweens.add({
            targets: this,
            scale: 1.5,
            alpha: 0.8,
            duration: 150,
            yoyo: true,
            onComplete: () => {
                this.setFillStyle(COR_LIXEIRA); // Volta para cinza
                this.setScale(1); 
                this.setAlpha(1);
            }
        });
    }
}