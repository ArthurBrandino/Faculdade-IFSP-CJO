import { Scene } from 'phaser';
import { Player } from '../entities/Player.js';
import { Processador } from '../entities/Processador.js';
import { Worm } from "../entities/Worm.js";
import { Trojan } from "../entities/Trojan.js";
import { ILY } from "../entities/ILY.js";
import { Clicker } from '../entities/Clicker.js';
import { Lixeira } from '../entities/Lixeira.js';
import { Firewall } from '../entities/Firewall.js';

// Importação dos Gerenciadores de Lógica
import { WaveManager } from '../logic/WaveManager.js';
import { WAVES } from '../logic/wavedata.js';
import { BuildManager } from '../logic/BuildManager.js';
import { InputManager } from '../logic/InputManager.js';
import { CollisionManager } from '../logic/CollisionManager.js';
import { CombatManager } from '../logic/CombatManager.js';
import { UIManager } from '../logic/UIManager.js';

export class Game extends Scene {
    constructor() {
        super('Game'); 
    }

    create() {
        // 1. ESTADO INICIAL
        this.bits = 0;
        this.selecionada = 1;
        this.dadosDefesas = this.configurarDadosDefesas();

        // 2. CONFIGURAÇÃO DO MUNDO FÍSICO
        this.physics.world.setBounds(0, 0, 2000, 2000);
        
        // 3. GRUPOS
        this.inimigos = this.physics.add.group({ runChildUpdate: true });
        this.defesas = this.add.group({ runChildUpdate: true });

        // 4. ENTIDADES PRINCIPAIS
        this.enzinho = new Player(this, 1100, 1100);
        this.processador = new Processador(this, 1000, 1000);
        this.physics.add.collider(this.enzinho, this.processador);

        // 5. PREVIEW DE CONSTRUÇÃO (Gráficos)
        this.previewRange = this.add.graphics().setDepth(99).setVisible(false);
        this.previewPreco = this.add.text(0, 0, '', {
            fontSize: '16px', fill: '#ffffff', stroke: '#000000', strokeThickness: 3, fontWeight: 'bold'
        }).setOrigin(0.5, 2.5).setDepth(101).setVisible(false);

        // 6. INICIALIZAÇÃO DOS GERENCIADORES
        // Nota: A ordem importa. Build e UI primeiro, Input por último.
        this.combatManager = new CombatManager(this);
        this.buildManager = new BuildManager(this);
        this.uiManager = new UIManager(this); 
        this.collisionManager = new CollisionManager(this);
        this.inputManager = new InputManager(this);
        this.waveManager = new WaveManager(this, WAVES); 
        this.waveManager.iniciarSistema();

        // 7. CÂMERA SEGUIR JOGADOR
        this.cameras.main.startFollow(this.enzinho, true);

        this.input.keyboard.on('keydown', (event) => {
            const num = parseInt(event.key);
            if (num >= 1 && num <= 4) {
                // Chama a função do UIManager para trocar o slot visualmente e a lógica
                this.uiManager.selecionarSlot(num);
            }
        });
    }


    // Centraliza os dados das torres para não poluir o create
    configurarDadosDefesas() {
        return {
            1: { nome: 'Combate', modo: 'acao' },
            2: { nome: 'Clicker', largura: Clicker.LARGURA, altura: Clicker.ALTURA, cor: Clicker.COR, custo: Clicker.CUSTO, range: Clicker.RANGE, modo: 'construcao', classe: Clicker },
            3: { nome: 'Lixeira', largura: Lixeira.LARGURA, altura: Lixeira.ALTURA, cor: Lixeira.COR, custo: Lixeira.CUSTO, range: Lixeira.RANGE, modo: 'construcao', classe: Lixeira },
            4: { nome: 'Firewall', largura: Firewall.LARGURA, altura: Firewall.ALTURA, cor: Firewall.COR, custo: Firewall.CUSTO, modo: 'construcao', classe: Firewall }
        };
    }

    adicionarBits(valor) {
        this.bits += valor;
        this.uiManager.atualizarBits(this.bits);
    }

    spawnInimigo(classe) { 
        const margem = 100;
        const lado = Phaser.Math.Between(0, 3);
        let x, y;

        if (lado === 0) { x = Phaser.Math.Between(0, 2000); y = -margem; }
        else if (lado === 1) { x = Phaser.Math.Between(0, 2000); y = 2000 + margem; }
        else if (lado === 2) { x = -margem; y = Phaser.Math.Between(0, 2000); }
        else { x = 2000 + margem; y = Phaser.Math.Between(0, 2000); }

        const classes = { 'Worm': Worm, 'ILY': ILY, 'Trojan': Trojan };
        const InimigoClasse = classes[classe];

        if (InimigoClasse) {
            this.inimigos.add(new InimigoClasse(this, x, y));
        }
    }

    update() {
        if (this.enzinho?.update) this.enzinho.update();
        
        this.buildManager.atualizarPreview(
            this.input.activePointer, 
            this.dadosDefesas[this.selecionada]
        );
    }
}