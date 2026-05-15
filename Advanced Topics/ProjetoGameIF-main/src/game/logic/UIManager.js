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
        this.globalBG = this.scene.add.image(this.offBack + (this.w/2), this.offBack + (this.h/2), 'meu-wallpaper')
            .setDisplaySize(this.w, this.h).setDepth(-1);

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
            if (!this.barraVida || !this.barraVida.scene) return; // Proteção total
            this.desenharBarraVida(atual, max);
        };

        this.onUpdateBits = (valor) => {
            if (!this.scene.textoBits || !this.scene.textoBits.scene) return; // Proteção total
            this.scene.textoBits.setText('BITS: ' + valor);
        };

        // 2. Registre os eventos no Scene Events
        // IMPORTANTE: Use o scene.events da cena do JOGO, não o do Manager global se houver
        this.scene.events.on('update-hp', this.onUpdateHP);
        this.scene.events.on('update-bits', this.onUpdateBits);

        // 3. A LIMPEZA DEFINITIVA (O evento 'shutdown' é nativo e infalível)
        this.scene.events.once('shutdown', () => {
            this.scene.events.off('update-hp', this.onUpdateHP);
            this.scene.events.off('update-bits', this.onUpdateBits);
            
            // Mate os textos manualmente para não sobrarem referências
            this.barraVida = null;
            if(this.scene.textoBits) this.scene.textoBits = null;
            if(this.scene.textoTurno) this.scene.textoTurno = null;
            
            console.log("UI Manager: Listeners removidos com sucesso.");
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
        
        // BOTÃO START
        this.btnStart = this.scene.add.rectangle(off + 45, worldY, 70, 40, 0x00ff00, 0.2)
            .setStrokeStyle(2, 0x00ff00).setInteractive({ useHandCursor: true }).setDepth(2000);

        this.txtStart = this.scene.add.text(off + 45, worldY, 'START', {
            fontSize: '14px', fill: '#00ff00', fontWeight: 'bold', fontFamily: 'monospace'
        }).setOrigin(0.5).setDepth(2001);

        // RELÓGIO 
        this.txtTempoWave = this.scene.add.text(off + camera.width - 80, worldY, '00:00', {
            fontSize: '16px', fill: '#00ff00', fontFamily: 'monospace', fontWeight: 'bold'
        }).setOrigin(0.5).setDepth(2001);

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
        this.iconesRef = [this.btnStart, this.txtStart, this.txtTempoWave];

        itensHotbar.forEach((item, i) => {
            const x = off + inicioX + i * (larguraSlot + espacamento);

            const bg = this.scene.add.rectangle(x, worldY, larguraSlot, larguraSlot, 0x000000)
                .setStrokeStyle(2, 0xffffff).setInteractive({ useHandCursor: true }).setDepth(2000);

            const txtNum = this.scene.add.text(x, worldY - 15, i + 1, { 
                fontSize: '12px', fill: '#00ff00', fontFamily: 'monospace' 
            }).setOrigin(0.5).setDepth(2001);

            const txtNome = this.scene.add.text(x, worldY + 5, item.nome, { fontSize: '9px', fill: '#ffffff' })
                .setOrigin(0.5).setDepth(2001);

            if (item.preco > 0) {
                const txtPreco = this.scene.add.text(x, worldY + 18, `$${item.preco}`, { fontSize: '9px', fill: '#ffff00' })
                    .setOrigin(0.5).setDepth(2001);
                this.iconesRef.push(txtPreco);
            }

            this.slots[i + 1] = bg;
            bg.on('pointerdown', () => this.selecionarSlot(i + 1));
            this.iconesRef.push(bg, txtNum, txtNome);
        });

        this.selecionarSlot(1);
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
}