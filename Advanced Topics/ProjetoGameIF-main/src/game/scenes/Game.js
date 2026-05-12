import { Scene } from 'phaser';
import { Player } from '../entities/Player.js';
import { Pastas } from '../entities/Pastas.js'; // IMPORTANTE
import { Processador } from '../entities/Processador.js'; // IMPORTANTE
import { Worm } from "../entities/Worm.js";
import { Trojan } from "../entities/Trojan.js";
import { ILY } from "../entities/ILY.js";
import { WaveManager } from '../logic/WaveManager.js';
import { WAVES } from '../logic/WaveData.js';
import { BuildManager } from '../logic/BuildManager.js';
import { InputManager } from '../logic/InputManager.js';
import { Clicker } from '../entities/Clicker.js';
import { Lixeira } from '../entities/Lixeira.js';
import { Firewall } from '../entities/Firewall.js';

export class Game extends Scene {
    constructor() {
        super('Game'); 
    }
    create() {
            // 1. CONFIGURAÇÃO DO MUNDO E JOGO
        this.physics.world.setBounds(0, 0, 2000, 2000);
        this.enzinho = new Player(this, 1100, 1100);
        this.processador = new Processador(this, 1000, 1000);
        this.physics.add.collider(this.enzinho, this.processador);
        this.inimigos = this.physics.add.group({runChildUpdate: true });
        this.inputManager = new InputManager(this);
        
        //Preview
        this.previewRange = this.add.graphics();
        this.previewRange.setDepth(99).setVisible(false);

        this.previewPreco = this.add.text(0, 0, '', {
            fontSize: '16px',
            fill: '#ffffff',
            stroke: '#000000',
            strokeThickness: 3,
            fontWeight: 'bold'
        });
        this.previewPreco.setOrigin(0.5, 2.5).setDepth(101).setVisible(false);
          this.buildManager = new BuildManager(this);

        // 2. ELEMENTOS DE INTERFACE (HUD)
        this.bits = 0;
        this.textoBits = this.add.text(850, 16, 'Bits: 0', { fontSize: '32px', fill: '#fff' });
        this.textoBits.setScrollFactor(0);

        // 3. CONFIGURAÇÃO DA CÂMERA PRINCIPAL (JOGO)
        this.cameras.main.startFollow(this.enzinho, true);
        this.cameras.main.setViewport(450, 100, 1000, 700);
        this.cameras.main.setBackgroundColor('#000b00');
        this.cameras.main.ignore([
            this.textoBits, 
            this.processador.barraVida, 
            this.processador.textoHUD
        ]);

        // 4. CONFIGURAÇÃO DA CÂMERA HUD
        this.hudCamera = this.cameras.add(50, 50, 250, 75).setName('HUD');
        this.hudCamera.setBackgroundColor('#000b00');
        this.hudCamera.ignore([
            this.enzinho, 
            this.processador, 
            this.inimigos,
            this.buildManager.preview,
            this.previewRange,
            this.previewPreco
        ]);


        this.hotbarCamera = this.cameras.add(450, 825, 1000, 100).setName('HUD');
        this.hotbarCamera.setBackgroundColor('#014901');
        this.hotbarCamera.ignore([this.enzinho, this.processador, this.inimigos]);
        this.hotbarCamera.ignore([
            this.enzinho, 
            this.processador, 
            this.inimigos,
            this.textoBits, 
            this.processador.barraVida, 
            this.processador.textoHUD,
            this.buildManager.preview,
            this.previewRange,
            this.previewPreco
        ]);

        //Gerenciamento de Ondas
        //this.gerenciadorOndas = new WaveManager(this, WAVES);
        //this.gerenciadorOndas.iniciarSistema();

        this.defesas = this.add.group({ runChildUpdate: true });

        this.dadosDefesas = {
            1: { nome: 'Combate', modo: 'acao' },
            2: { 
                nome: 'Clicker', 
                largura: Clicker.LARGURA, 
                altura: Clicker.ALTURA, 
                cor: Clicker.COR, 
                custo: Clicker.CUSTO, 
                range: Clicker.RANGE, 
                modo: 'construcao',
                classe: Clicker 
            },
           3: { 
                nome: 'Lixeira', 
                largura: Lixeira.LARGURA, 
                altura: Lixeira.ALTURA, 
                cor: Lixeira.COR, 
                custo: Lixeira.CUSTO, 
                range: Lixeira.RANGE, 
                modo: 'construcao',
                classe: Lixeira 
            },
             4: { 
                nome: 'Firewall', 
                largura: Firewall.LARGURA, 
                altura: Firewall.ALTURA, 
                cor: Firewall.COR, 
                custo: Firewall.CUSTO, 
                modo: 'construcao',
                classe: Firewall 
            }
        };

        this.selecionada = 1;

        const tratarColisao = (obj1, obj2) => {
            let inimigo, alvo;

            if (obj1 instanceof Worm || obj1.constructor.name === 'Virus' || obj1.velocidade !== undefined) {
                inimigo = obj1;
                alvo = obj2;
            } else {
                inimigo = obj2;
                alvo = obj1;
            }

            if (!inimigo.active || !alvo.active) return;

            if (inimigo instanceof Worm) {
                if (!inimigo.ehSegmento) {
                    inimigo.aoColidir(alvo); 
                }
            } else {
                // Vírus comum
                if (alvo.receberDano) {
                    alvo.receberDano(inimigo.dano || 10, inimigo); 
                }
                if (inimigo.morrer) inimigo.morrer();
            }
        };
        // 1. Colisão com as Defesas (Torres)
        this.physics.add.overlap(
            this.inimigos, 
            this.defesas, 
            tratarColisao, 
            null, 
            this
        );

        // 2. Colisão com o Processador
        this.physics.add.overlap(
            this.inimigos, 
            this.processador, 
            tratarColisao, 
            null, 
            this
        );
    }

    executarAcaoCombate(worldPoint) {
        // 1. Verificar se clicou em uma Pasta
        const pastasNoClique = this.physics.overlapCirc(worldPoint.x, worldPoint.y, 10);
        let interagiuComPasta = false;

        pastasNoClique.forEach(corpo => {
            const objeto = corpo.gameObject;
            if (objeto instanceof Pastas) {
                objeto.interagir(); // Supondo que você tenha esse método na classe Pastas
                interagiuComPasta = true;
            }
        });

        // 2. Se não clicou em pasta, verificar se tem inimigo perto para bater
        if (!interagiuComPasta) {
            // Aqui você pode disparar a animação de ataque do Enzinho
            //this.enzinho.atacar(); 
            
            const inimigosNoRaio = this.inimigos.getChildren().filter(inimigo => {
                const distancia = Phaser.Math.Distance.Between(worldPoint.x, worldPoint.y, inimigo.x, inimigo.y);
                
                const alvoValido = inimigo instanceof Worm ? !inimigo.ehSegmento : true;

                return distancia < 50 && inimigo.active && alvoValido;
            });

            inimigosNoRaio.sort((a, b) => {
                const distA = Phaser.Math.Distance.Between(worldPoint.x, worldPoint.y, a.x, a.y);
                const distB = Phaser.Math.Distance.Between(worldPoint.x, worldPoint.y, b.x, b.y);
                return distA - distB;
            });

            const alvoUnico = inimigosNoRaio[0];

            if (alvoUnico && alvoUnico.receberDano) {
                alvoUnico.receberDano(this.enzinho.danoAtaque);
            }
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
        // Update do Player 
        if (this.enzinho && typeof this.enzinho.update === 'function') {
            this.enzinho.update();
        }

        this.buildManager.atualizarPreview(this.input.activePointer, this.dadosDefesas[this.selecionada]);
        
    }
}