import { Clicker } from '../entities/Clicker.js';
import { Lixeira } from '../entities/Lixeira.js';
import { Firewall } from '../entities/Firewall.js';

export class UIManager {
    constructor(scene) {
        this.scene = scene;
        this.w = this.scene.scale.width;
        this.h = this.scene.scale.height;

        // "Ilhas" de UI para evitar que uma câmera veja a outra
        this.offVida = 5000;
        this.offBits = 6000;
        this.offWave = 7000;
        this.offHotbar = 8000;

        this.setupCameras();
        this.setupUIElements();
        this.criarIconesHotbar();
        this.setupListeners(); 
    }

    setupCameras() {
        // 1. Crie a câmera de fundo primeiro
        this.offBack = 9000;
        this.scene.backCamera = this.scene.cameras.add(0, 0, this.w, this.h).setName('GlobalBG');
        this.scene.backCamera.setScroll(this.offBack, this.offBack);

        // 2. JOGO (Câmera Main)
        const gameW = 950;
        const gameH = 550;
        this.scene.cameras.main.setViewport((this.w - gameW) / 2, 100, gameW, gameH);
        this.scene.cameras.main.setBackgroundColor('#000b00');

        
        this.scene.lifeCamera = this.scene.cameras.add(20, 20, 300, 100).setName('LIFE')
        .setBackgroundColor('#005300').setScroll(this.offVida, this.offVida);

        this.scene.bitsCamera = this.scene.cameras.add(this.w - 350, 20, 300, 100).setName('STATUS')
        .setBackgroundColor('#0a0097').setScroll(this.offBits, this.offBits);

        this.scene.waveCamera = this.scene.cameras.add(this.w - 320, 100, 300, 100).setName('WAVE')
        .setBackgroundColor('#4a4a00').setScroll(this.offWave, this.offWave);

        const barH = 80; 
        this.scene.hotbarCamera = this.scene.cameras.add(0, this.h - barH, this.w, barH).setName('Hotbar')
        .setBackgroundColor('#0058aa').setScroll(this.offHotbar, this.offHotbar);
        
        const cameraIndex = this.scene.cameras.cameras.indexOf(this.scene.backCamera);
        if (cameraIndex > -1) {
            const [cam] = this.scene.cameras.cameras.splice(cameraIndex, 1);
            this.scene.cameras.cameras.unshift(cam);
        }

        // Flash de Dano
        const { width, height } = this.scene.scale;
        this.scene.flashOverlay = this.scene.add.rectangle(width / 2, height / 2, width, height, 0xff0000);
        this.scene.flashOverlay.setScrollFactor(0); 
        this.scene.flashOverlay.setDepth(99999);   
        this.scene.flashOverlay.setAlpha(0);
    }
    
    setupUIElements() {
        // 1. Cria o Wallpaper na ilha 9000 (Onde a backCamera está olhando estática)
        this.globalBG = this.scene.add.image(this.offBack + (this.w/2), this.offBack + (this.h/2), 'meu-wallpaper')
            .setDisplaySize(this.w, this.h).setDepth(-1);

        // --- MOLDURA DA JANELA PRINCIPAL DO JOGO (NA ILHA DE FUNDO - IGUAL OS HUDS) ---
        const gameW = 950;
        const gameH = 550;
        
        // Pegamos a EXATA posição da tela onde o Viewport da main foi desenhado:
        // X = (this.w - gameW) / 2  e  Y = 100
        // E somamos o 'this.offBack' para jogar esse desenho lá para a ilha 9000 da backCamera!
        const molduraX = this.offBack + ((this.w - gameW) / 2);
        const molduraY = this.offBack + 100; 

        // Criamos a moldura na ilha de fundo.
        // Como a backCamera está estática em (9000, 9000), a barra azul e as bordas vão ficar 
        // perfeitamente travadas na tela, contornando o jogo por fora!
        this.janelaJogoContainer = this.criarMolduraWinXP(molduraX, molduraY, gameW, gameH, "C:\\Games\\Cyber_Defense.exe");


        const estiloValor = { fontSize: '28px', fill: '#000', fontFamily: 'Courier', fontWeight: 'bold' };

        // --- HUD VIDA (Ilha 5000) ---
        this.criarMolduraWinXP(this.offVida, this.offVida, 300, 100, "SYSTEM_MONITOR.EXE");
        this.barraVida = this.scene.add.graphics();
        this.textoHUD = this.scene.add.text(this.offVida + 15, this.offVida + 75, 'STATUS: OK', {
            fontSize: '12px', fill: '#000', fontFamily: 'monospace'
        });

        // --- HUD BITS (Ilha 6000) ---
        this.criarMolduraWinXP(this.offBits, this.offBits, 300, 100, "BIT_COUNTER.SYS");
        this.scene.textoBits = this.scene.add.text(this.offBits + 150, this.offBits + 60, 'BITS: 0', estiloValor).setOrigin(0.5);

        // --- HUD WAVE (Ilha 7000) ---
        this.criarMolduraWinXP(this.offWave, this.offWave, 300, 100, "WAVE_MANAGER.DLL");
        this.scene.textoTurno = this.scene.add.text(this.offWave + 150, this.offWave + 60, 'WAVE: 01', estiloValor).setOrigin(0.5);

        // --- GERENCIAMENTO DE EVENTOS ---
        this.onUpdateHP = (atual, max) => {
            if (!this.barraVida || !this.barraVida.scene) return; 
            this.desenharBarraVida(atual, max);
        };

        this.onUpdateBits = (valor) => {
            if (!this.scene.textoBits || !this.scene.textoBits.scene) return; 
            this.scene.textoBits.setText('BITS: ' + valor);
        };

        this.scene.events.on('update-hp', this.onUpdateHP);
        this.scene.events.on('update-bits', this.onUpdateBits);

        this.scene.events.once('shutdown', () => {
            this.scene.events.off('update-hp', this.onUpdateHP);
            this.scene.events.off('update-bits', this.onUpdateBits);
            this.barraVida = null;
            if(this.scene.textoBits) this.scene.textoBits = null;
            if(this.scene.textoTurno) this.scene.textoTurno = null;
        });
    }

    atualizarTextoWave(numero) {
        
        const waveFormatada = String(numero).padStart(2, '0');
        this.scene.textoTurno.setText(`WAVE: ${waveFormatada}`);
    }

    desenharBarraVida(atual, max) {
        this.barraVida.clear();
        const off = this.offVida;
        const x = off + 15; 
        const y = off + 35;
        const larguraTotal = 270;

        this.barraVida.fillStyle(0x000000, 0.5);
        this.barraVida.fillRect(x, y, larguraTotal, 20);

        const larguraVida = (atual / max) * larguraTotal;
        const corBarra = atual < 30 ? 0xff0000 : (atual < 60 ? 0xffff00 : 0x00ff00);
        
        this.barraVida.fillStyle(corBarra);
        this.barraVida.fillRect(x, y, larguraVida, 20);

        this.barraVida.lineStyle(2, 0xffffff);
        this.barraVida.strokeRect(x, y, larguraTotal, 20);

        if (atual < 30) this.textoHUD.setText('CPU_STABILITY: CRITICAL').setFill('#ff0000');
        else if (atual < 60) this.textoHUD.setText('CPU_STABILITY: WARNING').setFill('#ffff00');
        else this.textoHUD.setText('CPU_STABILITY: OK').setFill('#00ff00');
    }

    criarIconesHotbar() {
        
        const off = this.offHotbar;
        const camera = this.scene.hotbarCamera;
        const worldY = off + (camera.height / 2);

        this.criarBotaoStart(off, worldY);

        this.criarRelogio(off, worldY, camera);

        this.criarItens(off, worldY, camera)
    }

    applyCameraIgnores() {
        const tudoUI = [
            this.scene.textoBits, this.scene.textoTurno, 
            this.barraVida, this.textoHUD, ...(this.iconesRef || [])
        ].filter(el => el != null);

        // 1. A câmera principal deve ignorar a UI E a imagem de background
        this.scene.cameras.main.ignore([...tudoUI, this.globalBG]);

        // 2. A câmera de background ignora a UI (você já fez isso)
        this.scene.backCamera.ignore(tudoUI);

        // 3. Opcional: Se as HUDs estiverem "cortando" o fundo, 
        // faça elas ignorarem o background também
        this.scene.lifeCamera.ignore(this.globalBG);
        this.scene.bitsCamera.ignore(this.globalBG);
        this.scene.waveCamera.ignore(this.globalBG);
        this.scene.hotbarCamera.ignore(this.globalBG);
    }

    setupListeners() {
        this.scene.events.on('update-timer', (texto) => {
            // VERIFICAÇÃO BLINDADA: 
            // O texto existe E a cena dele ainda está ativa?
            if (this.txtTempoWave && this.txtTempoWave.scene && this.txtTempoWave.scene.sys.isActive()) {
                this.txtTempoWave.setText(texto);
                this.txtTempoWave.setFill(texto.includes("DANGER") ? '#ff0000' : '#00ff00');
            }
        });

        // Mesma lógica aqui para evitar erros em outras partes da UI
        this.scene.events.on('proxima-wave', (numeroDaWave) => {
            if (this.scene && this.scene.sys.isActive()) {
                this.atualizarTextoWave(numeroDaWave);
            }
        });
    }

    selecionarSlot(index) {
        this.slots.forEach(slot => { if (slot) slot.setStrokeStyle(2, 0xffffff); });
        if (this.slots[index]) this.slots[index].setStrokeStyle(4, 0x00ff00);
        this.scene.selecionada = index;
        this.scene.events.emit('trocou-slot', index);
    }

    atualizarBits(valor) {
        if (this.scene.textoBits) this.scene.textoBits.setText('BITS: ' + valor);
    }

    criarMolduraWinXP(x, y, largura, altura, tituloTexto) {
        // 1. Fundo Cinza
        const fundo = this.scene.add.rectangle(x, y, largura, altura, 0xced4d6).setOrigin(0, 0);
        
        // 2. Barra de Título Azul
        const barra = this.scene.add.rectangle(x, y, largura, 25, 0x000080).setOrigin(0, 0);
        
        // 3. Texto do Título
        this.scene.add.text(x + 5, y + 5, tituloTexto, { 
            fontSize: '12px', fill: '#fff', fontWeight: 'bold', fontFamily: 'Tahoma' 
        });

        // 4. Borda Preta
        const borda = this.scene.add.graphics();
        borda.lineStyle(2, 0x000000);
        borda.strokeRect(x, y, largura, altura);

        return { fundo, barra };
    }

    criarBotaoStart(off, worldY){
        
        // ---  BOTÃO START  ---
        const startX = off + 85; 
        const startWidth = 110;  
        const startHeight = 34;

        // Base Verde 
        this.btnStart = this.scene.add.rectangle(startX, worldY, startWidth, startHeight, 0x388A34)
            .setStrokeStyle(1.5, 0x2E6A29) 
            .setInteractive({ useHandCursor: true })
            .setDepth(2000);

        //Logo 
        this.menuLogo = this.scene.add.image(startX - (startWidth / 2) + 18, worldY, 'menu')
            .setScale(0.25)
            .setDepth(2001);

        // 3. Texto 
        this.txtStart = this.scene.add.text(startX + 12, worldY, 'start', {
            fontSize: '16px', 
            fill: '#ffffff', 
            fontWeight: 'bold', 
            fontStyle: 'italic',
            fontFamily: 'Tahoma, Arial, sans-serif',
            shadow: { offsetX: 1, offsetY: 1, color: '#000000', blur: 1, stroke: false, fill: true }
        }).setOrigin(0.5).setDepth(2001);

        // --- INTERATIVIDADE DO BOTÃO START ---
        this.btnStart.on('pointerover', () => this.btnStart.setFillStyle(0x4CA647));  // Brilha ao passar o mouse
        this.btnStart.on('pointerout', () => this.btnStart.setFillStyle(0x388A34));   // Restaura a cor padrão
        this.btnStart.on('pointerdown', () => this.btnStart.setFillStyle(0x286325));  // Escurece ao clicar
    }

    criarRelogio(off, worldY, camera, barH){
        // ÁREA DO RELÓGIO
        const trayX = off + camera.width - 75;
        const trayWidth = 160;
        const trayHeight = barH;

        this.trayBG = this.scene.add.rectangle(trayX, worldY, trayWidth, trayHeight, 0x16619eff)
            .setStrokeStyle(1, 0x2595f0ff)
            .setDepth(2000);

        this.txtTempoWave = this.scene.add.text(trayX, worldY, '00:00', {
            fontSize: '20px', 
            fill: '#ffffff', 
            fontFamily: 'Tahoma, Arial, sans-serif', 
            fontWeight: 'bold'
        }).setOrigin(0.5).setDepth(2001);
    }

    criarItens(off, worldY, camera){
         // --- CRIAÇÃO DOS SLOTS DE ITENS (MANTIDA A LÓGICA ORIGINAL) ---
        const larguraSlot = 55;
        const espacamento = 45;
        const totalSlots = 4;
        const larguraGrupo = (totalSlots * larguraSlot) + ((totalSlots - 1) * espacamento);
        const inicioX = (camera.width / 2) - (larguraGrupo / 2) + (larguraSlot / 2);

        const itensHotbar = [
            { nome: 'CURSOR', preco: 0 },
            { nome: 'CLICKER', preco: Clicker.CUSTO },
            { nome: 'LIXEIRA', preco: Lixeira.CUSTO },
            { nome: 'FIREWALL', preco: Firewall.CUSTO }
        ];

        this.slots = [];
        // Atualizado o array de referências para incluir as novas peças visuais
        this.iconesRef = [this.btnStart, this.menuLogo, this.txtStart, this.trayBG, this.txtTempoWave];

        itensHotbar.forEach((item, i) => {
            const x = off + inicioX + i * (larguraSlot + espacamento);

            // Estética cinza clássica de botão do Windows para os slots desmarcados
            const bg = this.scene.add.rectangle(x, worldY, larguraSlot, larguraSlot, 0xd4d0c8)
                .setStrokeStyle(1.5, 0xffffff) // Borda clara imitando relevo clássico
                .setInteractive({ useHandCursor: true })
                .setDepth(2000);

            const txtNum = this.scene.add.text(x - 18, worldY - 18, i + 1, { 
                fontSize: '11px', 
                fill: '#808080', 
                fontFamily: 'Tahoma, Arial, sans-serif',
                fontWeight: 'bold'
            }).setOrigin(0.5).setDepth(2001);

            const txtNome = this.scene.add.text(x, worldY - 2, item.nome, { 
                fontSize: '10px', 
                fill: '#000000',
                fontFamily: 'Tahoma, Arial, sans-serif',
                fontWeight: 'bold'
            }).setOrigin(0.5).setDepth(2001);

            if (item.preco > 0) {
                const txtPreco = this.scene.add.text(x, worldY + 14, `$${item.preco}`, { 
                    fontSize: '10px', 
                    fill: '#008000', // Preco em verde clássico de sistema
                    fontFamily: 'Tahoma, Arial, sans-serif'
                }).setOrigin(0.5).setDepth(2001);
                this.iconesRef.push(txtPreco);
            }

            this.slots[i + 1] = bg;
            bg.on('pointerdown', () => this.selecionarSlot(i + 1));
            this.iconesRef.push(bg, txtNum, txtNome);
        });

        this.selecionarSlot(1);
    }
}