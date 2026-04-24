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
        this.enzinho = new Player(this, 1100, 1100);

        //Gerar as Pastas do pastas.js
        //Pastas.gerarGrupo(this, 15);

        //Processador
        this.processador = new Processador(this, 1000, 1000);

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

        // Preview de construção
        this.dadosDefesas = {
            1: { nome: 'Clicker', largura: 100, altura: 100, cor: 0xeeeeee, custo: 50 },
            2: { nome: 'Lixeira', largura: 30, altura: 40, cor: 0x0055ff, custo: 150 },
            3: { nome: 'Firewall', largura: 60, altura: 20, cor: 0xff4400, custo: 20 }
        };

        this.selecionada = 1;

        // 2. Criar o Fantasma (Preview)
        this.previewConstrucao = this.add.rectangle(0, 0, 25, 25, 0xffffff, 0.5);
        this.previewConstrucao.setOrigin(0.5);
        this.previewConstrucao.setDepth(100);
        this.previewConstrucao.setVisible(false);

        // 3. Atualizar seleção (Teclado)
        this.input.keyboard.on('keydown-ONE', () => { this.selecionada = 1; this.atualizarPreview(); });
        this.input.keyboard.on('keydown-TWO', () => { this.selecionada = 2; this.atualizarPreview(); });
        this.input.keyboard.on('keydown-THREE', () => { this.selecionada = 3; this.atualizarPreview(); });

        // Clique para construir
        this.input.on('pointerdown', (pointer) => {
            // Converte a posição do clique na tela para a posição no mapa (mundo)
            const worldPoint = pointer.positionToCamera(this.cameras.main);
            this.tentarConstruir(worldPoint.x, worldPoint.y);
        });

        const tratarColisao = (objetoInimigo, objetoDefesa) => {
            // Agora o código sabe quem é quem
            const inimigo = objetoInimigo;
            const alvo = objetoDefesa;

            if (!inimigo.active || !alvo.active) return;

            console.log("Colisão com:", alvo.constructor.name); // Veja se aparece "Clicker" ou "Defesa"

            if (inimigo instanceof Worm) {
                if (!inimigo.ehSegmento) inimigo.aoColidir(alvo);
            } else {
                if (alvo.receberDano) {
                    alvo.receberDano(inimigo.dano || 10);
                }
                if (inimigo.morrer) inimigo.morrer();
            }
        };

        this.physics.add.overlap(this.inimigos, this.processador, (proc, inimigo) => {
            // 1. O Processador leva dano (se você quiser)
            if (proc.receberDano) proc.receberDano(inimigo.dano);

            // 2. O Inimigo MORRE ao tocar o Processador
            if (inimigo.morrer) {
                inimigo.morrer();
            } else if (inimigo instanceof Worm) {
                inimigo.aoColidir(proc); // Worm tem lógica própria de morte
            }
        }, null, this);
        this.physics.add.overlap(this.inimigos, this.defesas, (inimigo, defesa) => {
            tratarColisao(defesa, inimigo);
        }, null, this);


        //testes
        
        const debugSpawn = (classeInimigo) => {
        const worldPoint = this.input.activePointer.positionToCamera(this.cameras.main);
        const inimigo = new classeInimigo(this, worldPoint.x, worldPoint.y);
            this.inimigos.add(inimigo);
        };

        this.input.keyboard.on('keydown-Q', () => debugSpawn(Worm));
        this.input.keyboard.on('keydown-E', () => debugSpawn(Trojan));
        this.input.keyboard.on('keydown-R', () => debugSpawn(ILY));
        }

    tentarConstruir(x, y) {
        if (!this.dadosDefesas || !this.dadosDefesas[this.selecionada]) return;

        const dados = this.dadosDefesas[this.selecionada];
        
        // 1. Calcula o Snap (Centro do bloco de 50x50)
        const snapX = Math.floor(x / 50) * 50;
        const snapY = Math.floor(y / 50) * 50;

        // 2. Criamos um retângulo virtual que representa a nova construção
        // Subtraímos metade da largura/altura do snap para pegar o canto superior esquerdo

        const novaArea = new Phaser.Geom.Rectangle(
            snapX - dados.largura / 2 + 1, // +1 pixel de folga
            snapY - dados.altura / 2 + 1, // +1 pixel de folga
            dados.largura - 2,             // -2 pixels no total
            dados.altura - 2              // -2 pixels no total
        );

        // 3. Verificamos se essa área encosta em QUALQUER defesa já existente
        const ocupado = this.defesas.getChildren().some(defesa => {
            // Pegamos a área real da defesa que já está no mapa
            const bounds = defesa.getBounds();
            // Verificamos se há intersecção entre os dois retângulos
            return Phaser.Geom.Intersects.RectangleToRectangle(novaArea, bounds);
        });

        if (ocupado) {
            console.log("Espaço insuficiente! Há uma construção no caminho.");
            return; // Sai da função e não gasta bits nem cria a torre
        }

        // 4. Se chegou aqui, o espaço está livre!
        if (this.bits >= dados.custo) {
            let novaDefesa;
            if (this.selecionada === 1) novaDefesa = new Clicker(this, snapX, snapY);
            else if (this.selecionada === 2) novaDefesa = new Lixeira(this, snapX, snapY);
            else if (this.selecionada === 3) novaDefesa = new Firewall(this, snapX, snapY);

            if (novaDefesa) {
                this.bits -= dados.custo;
                this.textoBits.setText('Bits: ' + this.bits);
                this.defesas.add(novaDefesa);
            }
        } else {
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
        // 1. Update do Player primeiro (sempre!)
        if (this.enzinho && typeof this.enzinho.update === 'function') {
            this.enzinho.update();
        }

        // 2. Trava de segurança para o resto do código
        if (!this.dadosDefesas || !this.previewConstrucao) return;

        try {
            const pointer = this.input.activePointer;
            const worldPoint = pointer.positionToCamera(this.cameras.main);

            const snapX = Math.floor(worldPoint.x / 50) * 50;
            const snapY = Math.floor(worldPoint.y / 50) * 50;

            this.previewConstrucao.setVisible(true);
            this.previewConstrucao.setPosition(snapX, snapY);

            const dados = this.dadosDefesas[this.selecionada];
            
            // Retângulo de teste com 1px de folga para permitir encostar
            const areaPreview = new Phaser.Geom.Rectangle(
                snapX - dados.largura / 2 + 1,
                snapY - dados.altura / 2 + 1,
                dados.largura - 2,
                dados.altura - 2
            );

            const ocupado = this.defesas.getChildren().some(defesa => {
                return Phaser.Geom.Intersects.RectangleToRectangle(areaPreview, defesa.getBounds());
            });

            const sobreProcessador = Phaser.Geom.Intersects.RectangleToRectangle(areaPreview, this.processador.getBounds());

            if (ocupado || sobreProcessador || this.bits < dados.custo) {
                this.previewConstrucao.setFillStyle(0xff0000, 0.5);
            } else {
                this.previewConstrucao.setFillStyle(dados.cor, 0.5);
            }
        } catch (e) {
            // Se der qualquer erro no código de construção, o player não trava
            console.error("Erro no preview de construção:", e);
        }
    }

    // Método auxiliar para mudar o tamanho do fantasma
    atualizarPreview() {
        const dados = this.dadosDefesas[this.selecionada];
        this.previewConstrucao.setSize(dados.largura, dados.altura);
        this.previewConstrucao.setFillStyle(dados.cor, 0.5);
    }
}