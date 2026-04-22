import { Scene } from 'phaser';
import { Player } from '../entities/Player.js';
import { Pastas } from '../entities/Pastas.js'; // IMPORTANTE
import { Processador } from '../entities/Processador.js'; // IMPORTANTE
import { Worm } from "../entities/Worm.js";
import { Trojan } from "../entities/Trojan.js";
import { ILY } from "../entities/ILY.js";
import { WaveManager } from '../logic/WaveManager.js';
import { WAVES } from '../logic/WaveData.js';
import { Clicker } from '../entities/Clicker.js';

export class Game extends Scene {
    constructor() {
        super('Game'); 
    }
    create() {
        //Mapa
        this.physics.world.setBounds(0, 0, 2000, 2000);

        //Player
        this.enzinho = new Player(this, 1000, 1000);

        //Gerar as Pastas do pastas.js
        //Pastas.gerarGrupo(this, 15);

        //Processador
        this.processador = new Processador(this, 800, 800);

        this.physics.add.collider(this.enzinho, this.processador);

        this.cameras.main.startFollow(this.enzinho, true); // O 'true' ativa o arredondamento de pixels
        this.cameras.main.centerOn(1000, 1000); // Força a câmera a olhar para o centro no início

        this.bits = 0;
        this.textoBits = this.add.text(850, 16, 'Bits: 0', { fontSize: '32px', fill: '#fff' });
        
        this.textoBits.setScrollFactor(0);

        this.inimigos = this.physics.add.group({runChildUpdate: true });

        this.gerenciadorOndas = new WaveManager(this, WAVES);
        this.gerenciadorOndas.iniciarSistema();

        this.defesas = this.add.group({ runChildUpdate: true });

        // Atalhos para selecionar a defesa
        this.selecionada = 1; // 1: Clicker, 2: Lixeira, 3: Firewall
        this.input.keyboard.on('keydown-ONE', () => { this.selecionada = 1; console.log("Clicker Selecionado"); });
        this.input.keyboard.on('keydown-TWO', () => { this.selecionada = 2; console.log("Lixeira Selecionada"); });
        this.input.keyboard.on('keydown-THREE', () => { this.selecionada = 3; console.log("Firewall Selecionado"); });

        // Clique para construir
        this.input.on('pointerdown', (pointer) => {
            // Converte a posição do clique na tela para a posição no mapa (mundo)
            const worldPoint = pointer.positionToCamera(this.cameras.main);
            this.tentarConstruir(worldPoint.x, worldPoint.y);
        });

        const tratarColisao = (alvo, inimigo) => {
            if (!inimigo.active) return;

            if (inimigo instanceof Worm) {
                if (!inimigo.ehSegmento) {
                    inimigo.aoColidir(alvo);
                }
            } else {
                if (alvo.receberDano) alvo.receberDano(inimigo.dano);
                if (inimigo.morrer) inimigo.morrer();
            }
        };

        this.physics.add.overlap(this.inimigos, this.processador, (proc, inimigo) => tratarColisao(proc, inimigo));
        this.physics.add.collider(this.inimigos, this.defesas, (inimigo, defesa) => tratarColisao(defesa, inimigo));
    }

    tentarConstruir(x, y) {
        //Grid 50x50
        const snapX = Math.floor(x / 50) * 50 + 25;
        const snapY = Math.floor(y / 50) * 50 + 25;

        const jaOcupado = this.defesas.getChildren().some(d => d.x === snapX && d.y === snapY);
        if (jaOcupado) {
            console.log("Slot ocupado!");
            return; 
        }

        let novaDefesa;
        let custo = 0;

        if (this.selecionada === 1) {
            custo = 50;
            if (this.bits >= custo) {
                novaDefesa = new Clicker(this, snapX, snapY);
            }
        } else if (this.selecionada === 2) {
            custo = 150;
            if (this.bits >= custo) {
                novaDefesa = new Lixeira(this, snapX, snapY);
            }
        } else if (this.selecionada === 3) {
            custo = 20;
            if (this.bits >= custo) {
                novaDefesa = new Firewall(this, snapX, snapY);
            }
        }

        if (novaDefesa) {
            this.bits -= custo;
            this.textoBits.setText('Bits: ' + this.bits);
            this.defesas.add(novaDefesa);
        } else if (this.bits < custo) {
            console.log("Bits insuficientes!");
        }
    }

    adicionarBits(valor) {
        this.bits += valor;
        this.textoBits.setText('Bits: ' + this.bits);
        console.log("Bits adicionados:", valor);
    }

    spawnInimigo(classe) { 
        const margem = 100;
        let x, y;
        const lado = Phaser.Math.Between(0, 3);

        if (lado === 0) { x = Phaser.Math.Between(0, 2000); y = -margem; }
        else if (lado === 1) { x = Phaser.Math.Between(0, 2000); y = 2000 + margem; }
        else if (lado === 2) { x = -margem; y = Phaser.Math.Between(0, 2000); }
        else { x = 2000 + margem; y = Phaser.Math.Between(0, 2000); }

        let novoInimigo;

        if (classe === 'Worm') {
            novoInimigo = new Worm(this, x, y);
        } else if (classe === 'ILY') {
            novoInimigo = new ILY(this, x, y);
        } else if (classe === 'Trojan') {
            novoInimigo = new Trojan(this, x, y);
        }

        if (novoInimigo) {
            this.inimigos.add(novoInimigo);
        }
    }

    update() {
       this.enzinho.update();
    }
}