import Phaser from 'phaser';

export class Defesa extends Phaser.GameObjects.Rectangle {
    constructor(scene, x, y, largura, altura, hp, speed, dano, range, custo) {
        // Agora largura e altura vêm do filho (Clicker, Firewall, etc)
        super(scene, x, y, largura, altura, 0xeeeeee);
        
        scene.add.existing(this);
        // static: true garante que o corpo físico não se mova
        scene.physics.add.existing(this, true); 
        
        this.hp = hp;
        this.maxHp = hp;
        this.speed = speed;
        this.dano = dano;
        this.range = range;
        this.custo = custo;

        // Criamos o objeto gráfico da barra de vida
        this.barraVida = scene.add.graphics();
        this.atualizarBarraVida();
    }

    receberDano(quantidade) {
        this.hp -= quantidade;
        this.atualizarBarraVida(); // Atualiza o desenho da barra
        
        // Feedback visual de piscar
        this.scene.tweens.add({
            targets: this,
            fillAlpha: 0.5,
            duration: 100,
            yoyo: true
        });

        if (this.hp <= 0) {
            this.destruir();
        }
    }

    atualizarBarraVida() {
        this.barraVida.clear();
        
        // Só desenha a barra se a defesa estiver danificada (opcional)
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
        // MUITO IMPORTANTE: Destruir a barra de vida também, 
        // senão ela fica "flutuando" no mapa sozinha
        if (this.barraVida) {
            this.barraVida.destroy();
        }
        this.destroy();
    }
}