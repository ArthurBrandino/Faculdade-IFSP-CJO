import { Inimigo } from "./Virus";

const COR_WORM = 0x00ff00;

export class Worm extends Inimigo {
    constructor(scene, x, y, ehSegmento = false) {
        // Atributos base
        const velocidade = 150;
        const vida = 1;
        const dano = 1; 
        const largura = 18;
        const altura = 18;
        const frequencia = 0.01;
        const amplitude = 2.5;

        super(scene, x, y, largura, altura, vida, velocidade, dano, frequencia, amplitude);

        this.setFillStyle(COR_WORM);
        this.cauda = []; 
        this.ehSegmento = ehSegmento; 

        this.historicoPosicoes = [];
        if (this.ehSegmento) {
            this.tornarImortal();
        }
        else{
            this.adicionarSegmentos(4);
        }
    }

    tornarImortal() {
        this.disableInteractive(); // Não aceita cliques
        if (this.body) {
            this.body.enable = false; // Desativa física (não colide com nada)
        }
        this.setAlpha(0.6); // Feedback visual: cauda é mais transparente
    }

    tornarVulneravel() {
        this.setInteractive(); // Volta a aceitar cliques
        if (this.body) {
            this.body.enable = true; // Ativa física (pode bater no processador)
        }
        this.setAlpha(1); // Fica sólido
    }

    adicionarSegmentos(quantidade) {
        for (let i = 0; i < quantidade; i++) {
            const novoSegmento = new Worm(this.scene, this.x, this.y, true);
            
            this.scene.inimigos.add(novoSegmento);
            this.cauda.push(novoSegmento);
        }
    }

    preUpdate(time, delta) {
        // Apenas a cabeça processa a lógica de movimento do Virus.js
        if (!this.ehSegmento) {
            super.preUpdate(time, delta);

            // Guarda a posição atual
            this.historicoPosicoes.unshift({ x: this.x, y: this.y });

            // Limpa o histórico antigo para não pesar (tamanho da cauda * delay)
            if (this.historicoPosicoes.length > 100) {
                this.historicoPosicoes.pop();
            }

            // Faz a cauda seguir o rastro com um "delay" de frames
            const espacamento = 6; // Quantos frames de atraso entre cada bloco
            this.cauda.forEach((seg, index) => {
                const indiceNoHistorico = (index + 1) * espacamento;
                const posAntiga = this.historicoPosicoes[indiceNoHistorico];

                if (posAntiga) {
                    seg.x = posAntiga.x;
                    seg.y = posAntiga.y;
                }
            });
        }
    }

    aoColidir(alvo) {
        // 1. Causa dano ao alvo (seja Processador ou Defesa)
        if (alvo.receberDano) {
            alvo.receberDano(this.dano);
        }

        // 2. Se o alvo for destruído pelo meu impacto, eu me multiplico!
        // Checamos se o HP do alvo chegou a 0 após o meu hit
        if (alvo.hp <= 0) {
            console.log("Worm consumiu a construção e cresceu!");
            this.adicionarSegmentos(5); // Ganha +5 quadradinhos
        }

        // 3. A cabeça atual morre e passa o bastão para o próximo segmento
        this.morrer();
    }

    morrer() {
        if (this.cauda.length > 0) {
            const novaCabeca = this.cauda.shift();
            
            if (novaCabeca && novaCabeca.active) {
                novaCabeca.cauda = this.cauda;
                novaCabeca.ehSegmento = false; 
                novaCabeca.historicoPosicoes = this.historicoPosicoes;
                novaCabeca.tornarVulneravel();

                this.scene.tweens.add({
                    targets: novaCabeca,
                    scale: 1.2,
                    duration: 100,
                    yoyo: true
                });
            }
        }

        this.cauda = [];
        super.morrer();
    }
}