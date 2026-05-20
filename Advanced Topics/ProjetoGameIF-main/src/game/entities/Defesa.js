import Phaser from 'phaser';
import { Worm } from "../entities/Worm.js";

export class Defesa extends Phaser.GameObjects.Sprite {
    constructor(scene, x, y, largura, altura, spriteKey, hp, speed, dano, range, custo) {
        // Agora largura e altura vêm do filho (Clicker, Firewall, etc)
        super(scene, x, y, spriteKey);
        
        scene.add.existing(this);
        // static: true garante que o corpo físico não se mova
        scene.physics.add.existing(this, true);
        this.body.setSize(largura, altura);
        
        this.setDisplaySize(largura, altura);
        
        this.hp = hp;
        this.maxHp = hp;
        this.speed = speed;
        this.dano = dano;
        this.range = range;
        this.custo = custo;

        this.somHit = scene.sound.add('DefenseHit');
        this.podeTocarSomHit = true;

        // Criamos o objeto gráfico da barra de vida
        this.barraVida = scene.add.graphics();
        this.atualizarBarraVida();
    }

    receberDano(quantidade) {
        this.hp -= quantidade;

        if (this.hp <= 0) {
            this.destruir();
            return;
        }

        this.atualizarBarraVida(); // Atualiza o desenho da barra
        
        // Feedback visual e Sonoro
        if (this.podeTocarSomHit) {
            this.podeTocarSomHit = false;

            if (this.somHit) this.somHit.play();

            this.setTint(0xff0000);
            this.alpha = 0.6; 

            //Timer para evitar spam
            this.scene.time.delayedCall(120, () => {
                this.clearTint();          
                this.alpha = 1;            
                this.podeTocarSomHit = true; 
            });
        }
    }

    procurarAlvo() {
        //Pega todos os inimigos do grupo
        const listaInimigos = this.scene.inimigos.getChildren();

        return listaInimigos.find(inimigo => {
            // 2. Filtro de Atividade
            if (!inimigo || !inimigo.active || !inimigo.body || inimigo.estaPreso) return false;


            // 3. Filtro de Distância
            const distancia = Phaser.Math.Distance.Between(this.x, this.y, inimigo.x, inimigo.y);
            if (distancia > this.range) return false;

            // 4. Filtro de Segmento (Worm)
            // Usamos uma verificação mais simples: se tem a propriedade 'ehSegmento' e ela é true, ignora
            if (inimigo.ehSegmento === true) {
                return false;
            }

            // 5. Se passou por tudo acima, este é um alvo válido!
            return true; 
        });
    }

    atualizarBarraVida() {
        this.barraVida.clear();
        this.barraVida.setDepth(101);
        // Só desenha a barra se a defesa estiver danificada
        if (this.hp < this.maxHp && this.hp > 0) {
            const larguraTotal = this.width * 0.8;
            const alturaBarra = 6;
            const x = this.x - larguraTotal / 2;
            const y = this.y - (this.height / 2) - 15;

            // Fundo (Preto)
            this.barraVida.fillStyle(0x000000, 0.7);
            this.barraVida.fillRect(x, y, larguraTotal, alturaBarra);

            // Vida (Verde ou Vermelho se estiver baixa)
            const percentual = this.hp / this.maxHp;
            const cor = percentual > 0.3 ? 0x00ff00 : 0xff0000;
            
            this.barraVida.fillStyle(cor, 1);
            this.barraVida.fillRect(x, y, larguraTotal * percentual, alturaBarra);
        }
    }

    destruir() {
        if (this.somHit) {
            this.somHit.stop();       
            this.somHit.destroy();   
        }

        if (this.barraVida) {
            this.scene.sound.play('DefenseDestroy'); // Solta o som de explosão/limpeza
            this.barraVida.destroy();
        }
        this.destroy();
    }
}