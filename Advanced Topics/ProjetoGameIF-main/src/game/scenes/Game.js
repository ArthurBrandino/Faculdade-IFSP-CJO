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

        // 2. ELEMENTOS DE INTERFACE (HUD)
        this.bits = 0;
        this.textoBits = this.add.text(850, 16, 'Bits: 0', { fontSize: '32px', fill: '#fff' });
        this.textoBits.setScrollFactor(0);
        
        // Supondo que sua barra de vida seja um objeto (imagem ou container)
        // this.barraVida = ... 

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
        
        // A Câmera HUD deve IGNORAR tudo o que é do jogo
        this.hudCamera.ignore([this.enzinho, this.processador, this.inimigos]);


        this.hotbarCamera = this.cameras.add(450, 825, 1000, 100).setName('HUD');
        this.hotbarCamera.setBackgroundColor('#014901');
        this.hotbarCamera.ignore([this.enzinho, this.processador, this.inimigos]);
        this.hotbarCamera.ignore([
            this.textoBits, 
            this.processador.barraVida, 
            this.processador.textoHUD
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

        //Preview
        this.previewConstrucao = this.add.rectangle(0, 0, 100, 100, 0xffffff, 0.5);
        this.previewConstrucao.setOrigin(0.5).setDepth(100).setVisible(false);
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



        // 3. Atualizar seleção (Teclado)
        this.input.keyboard.on('keydown-ONE', () => { this.selecionada = 1; this.atualizarPreview(); });
        this.input.keyboard.on('keydown-TWO', () => { this.selecionada = 2; this.atualizarPreview(); });
        this.input.keyboard.on('keydown-THREE', () => { this.selecionada = 3; this.atualizarPreview(); });
        this.input.keyboard.on('keydown-FOUR', () => { this.selecionada = 4; this.atualizarPreview(); });

        // Clique 
        this.input.on('pointerdown', (pointer) => {
            // Converte a posição do clique na tela para a posição no mapa (mundo)
            const dadosAtuais = this.dadosDefesas[this.selecionada];
            const worldPoint = pointer.positionToCamera(this.cameras.main);

            if (dadosAtuais.modo === 'construcao') {
                // Se estiver em modo construção, chama a lógica que já temos
                this.tentarConstruir(worldPoint.x, worldPoint.y);
            } else {
                // MODO COMBATE 
                this.executarAcaoCombate(worldPoint);
            }
        });

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


        //testes
        const debugSpawn = (classeInimigo) => {
        const worldPoint = this.input.activePointer.positionToCamera(this.cameras.main);
        const inimigo = new classeInimigo(this, worldPoint.x, worldPoint.y);
            this.inimigos.add(inimigo);
        };

        this.input.keyboard.on('keydown-Q', () => debugSpawn(Worm));
        this.input.keyboard.on('keydown-E', () => debugSpawn(Trojan));
        this.input.keyboard.on('keydown-R', () => debugSpawn(ILY));
        this.input.keyboard.on('keydown-P', () => debugSpawn(Pastas));
        this.input.keyboard.on('keydown-T', () => this.adicionarBits(100));
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

    tentarConstruir(x, y) {
        const dados = this.dadosDefesas[this.selecionada];
        if (!this.dadosDefesas || !this.dadosDefesas[this.selecionada]) return;

        const validacao = this.validarConstrucao(x, y);

        if (validacao.podeConstruir && validacao.temGrana) {
            const novaDefesa = new dados.classe(this, validacao.x, validacao.y);

            if (novaDefesa) {
                this.bits -= validacao.custo;
                this.textoBits.setText('Bits: ' + this.bits);
                this.defesas.add(novaDefesa);
            }
        } else {
            if (!validacao.temGrana) console.log("Bits insuficientes!");
            else console.log("Espaço ocupado!");
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

        const dadosAtuais = this.dadosDefesas[this.selecionada];

        
        if (!dadosAtuais || dadosAtuais.modo === 'acao') {
            if (this.previewConstrucao) this.previewConstrucao.setVisible(false);
            if (this.previewRange) this.previewRange.setVisible(false);
            if (this.previewPreco) this.previewPreco.setVisible(false);
            return; 
        }

        try {
            const pointer = this.input.activePointer;
            const worldPoint = pointer.positionToCamera(this.cameras.main);
            const validacao = this.validarConstrucao(worldPoint.x, worldPoint.y);

            // 1. Visibilidade e Posição
            this.previewConstrucao.setVisible(true);
            this.previewPreco.setVisible(true);
            
            this.previewConstrucao.setPosition(validacao.x, validacao.y);
            this.previewPreco.setPosition(validacao.x, validacao.y);
            this.previewPreco.setText(`${dadosAtuais.custo} bits`);

            // 2. Lógica de Cores Única (Evita conflitos)
            const podeColocar = validacao.podeConstruir && validacao.temGrana;
            const corFeedback = podeColocar ? 0x00ff00 : 0xff0000; // Verde ou Vermelho
            
            // O retângulo usa a cor da torre se estiver OK, senão vermelho
            const corPreenchimento = podeColocar ? (dadosAtuais.cor || 0xffffff) : 0xff0000;
            this.previewConstrucao.setFillStyle(corPreenchimento, 0.5);

            // 3. Desenho do Range
            if(dadosAtuais.nome != 'Firewall')
            {
                this.previewRange.setVisible(true);
                this.previewRange.clear();
                this.previewRange.lineStyle(2, corFeedback, 0.5);
                this.previewRange.fillStyle(corFeedback, 0.1);
                const raio = dadosAtuais.range || 150; 
                this.previewRange.strokeCircle(validacao.x, validacao.y, raio);
                this.previewRange.fillCircle(validacao.x, validacao.y, raio);
            }
            else    
                this.previewRange.setVisible(false);

        } catch (e) {
            console.error("Erro no preview de construção:", e);
        }
        
    }

    validarConstrucao(x, y) {
        const dados = this.dadosDefesas[this.selecionada];
        if (!dados) return { podeConstruir: false };

        // Calcula o Snap (Centro do bloco de 50x50)
        const gridX = Math.floor(x / 50) * 50;
        const gridY = Math.floor(y / 50) * 50;

        const snapX = gridX + (dados.largura / 2);
        const snapY = gridY + (dados.altura / 2);

        const temGrana = this.bits >= dados.custo;

        // Retângulo virtual da nova construção que você quer colocar
        const novaArea = new Phaser.Geom.Rectangle(
            snapX - dados.largura / 2 + 1, 
            snapY - dados.altura / 2 + 1, 
            dados.largura - 2, 
            dados.altura - 2
        );

        // Verificamos se essa área encosta em defesas já existentes
        const ocupado = this.defesas.getChildren().some(defesa => {
            const areaLogicaExistente = new Phaser.Geom.Rectangle(
                defesa.x - defesa.width / 2 + 1,
                defesa.y - defesa.height / 2 + 1,
                defesa.width - 2,
                defesa.height - 2
            );

            return Phaser.Geom.Intersects.RectangleToRectangle(novaArea, areaLogicaExistente);
        });

        const sobreProcessador = Phaser.Geom.Intersects.RectangleToRectangle(novaArea, this.processador.getBounds());

        return {
            podeConstruir: !ocupado && !sobreProcessador,
            temGrana: temGrana,
            x: snapX,
            y: snapY,
            custo: dados.custo
        };
    }

    atualizarPreview() {
        const dados = this.dadosDefesas[this.selecionada];
        
        // Se for modo combate (ou dados não existirem), esconde o preview e sai da função
        if (!dados || dados.modo === 'acao') {
            this.previewConstrucao.setVisible(false);
            this.previewRange.setVisible(false);
            this.previewPreco.setVisible(false);
            return;
        }

        // Só define tamanho se as propriedades existirem
        if (dados.largura && dados.altura) {
            this.previewConstrucao.setSize(dados.largura, dados.altura);
            this.previewConstrucao.setFillStyle(dados.cor || 0xffffff, 0.5);
        }
    }
}