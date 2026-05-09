import { Inimigo } from "./Virus";

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

        super(scene, x, y, largura, altura, 'spr_worm', vida, velocidade, dano, frequencia, amplitude);

        
        this.cauda = []; 
        this.ehSegmento = ehSegmento; 

        if (!ehSegmento) {
            this.setFrame(3);
            this.historicoPosicoes = [];
            this.adicionarSegmentos(4);
        }
        else{
            this.setFrame(2);
            this.tornarImortal();
        }

        this.setDisplaySize(altura, largura);
    }


    tornarImortal() {
        this.disableInteractive(); // Não aceita cliques
        if (this.body) {
            this.body.enable = false; // Desativa física (não colide com nada)
        }
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

    promoverProximoSegmento(alvo = null) {
        if (this.estaMorrendo) return;
        this.estaMorrendo = true;

        if (this.cauda && this.cauda.length > 0) {
            const novaCabeca = this.cauda.shift();

            if (novaCabeca && novaCabeca.active) {
                novaCabeca.setFrame(3);
                novaCabeca.cauda = this.cauda;
                novaCabeca.historicoPosicoes = this.historicoPosicoes;
                novaCabeca.ehSegmento = false;
                novaCabeca.tornarVulneravel();

                // Se o alvo for o processador, a nova cabeça assume a posição da antiga
                if (alvo === this.scene.processador) {
                    novaCabeca.x = this.x;
                    novaCabeca.y = this.y;
                }
            }
        }
        this.cauda = [];
    }

   aoColidir(alvo) {
        if (this.estaMorrendo) return;

        if (alvo && alvo.receberDano) {
            const hpAntes = alvo.hp;
            
            alvo.receberDano(this.dano, this);

            if (alvo.hp <= 0 && alvo !== this.scene.processador) {
                console.log("Worm devorou a defesa e cresceu!");
                
                if (this.cauda.length > 0) {
                    this.adicionarSegmentos(5); 
                }
            }
        }

        this.promoverProximoSegmento(alvo);
        this.morrer();
    }

    receberDano(quantidade) {
        this.hp -= quantidade;
        
        if (this.hp <= 0 && !this.estaMorrendo) {
            // Se morreu por tiro, tentamos promover a cauda ANTES de destruir
            this.promoverProximoSegmento(); 
            this.morrer();
        }
    }

    morrer() {
       if (this.cauda.length === 0 && this.ehSegmento === false) {
            console.log("Worm totalmente eliminado!");
        }
        
        // Deletamos a cabeça atual, mas o objeto 'novaCabeca' 
        // já recebeu a referência da lista 'cauda' no aoColidir ou aqui
        super.morrer();
    }
}