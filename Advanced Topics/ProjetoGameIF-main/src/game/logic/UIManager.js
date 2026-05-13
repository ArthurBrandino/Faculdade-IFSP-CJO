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
        // JOGO
        const gameW = 950;
        const gameH = 550;
        this.scene.cameras.main.setViewport((this.w - gameW) / 2, 100, gameW, gameH);
        this.scene.cameras.main.setBackgroundColor('#000b00');

        // JANELA VIDA - Foca em 5000
        this.scene.lifeCamera = this.scene.cameras.add(20, 20, 300, 100).setName('LIFE');
        this.scene.lifeCamera.setBackgroundColor('#005300').setScroll(this.offVida, this.offVida);

        // JANELA BITS - Foca em 6000
        this.scene.bitsCamera = this.scene.cameras.add(this.w - 350, 20, 300, 100).setName('STATUS');
        this.scene.bitsCamera.setBackgroundColor('#0a0097').setScroll(this.offBits, this.offBits);

        // JANELA TURNO - Foca em 7000
        this.scene.waveCamera = this.scene.cameras.add(this.w - 320, 100, 300, 100).setName('WAVE');
        this.scene.waveCamera.setBackgroundColor('#4a4a00').setScroll(this.offWave, this.offWave);

        // BARRA DE TAREFAS - Foca em 8000
        const barH = 80; 
        this.scene.hotbarCamera = this.scene.cameras.add(0, this.h - barH, this.w, barH).setName('Hotbar');
        this.scene.hotbarCamera.setBackgroundColor('#0058aa').setScroll(this.offHotbar, this.offHotbar);
    }

    setupUIElements() {
        const estiloTexto = { fontSize: '30px', fill: '#00ff00', fontFamily: 'Courier', fontWeight: 'bold' };

        // VIDA (Ilha 5000)
        this.barraVida = this.scene.add.graphics();
        this.textoHUD = this.scene.add.text(this.offVida + 20, this.offVida + 65, 'CPU_STABILITY: OK', {
            fontSize: '14px', fill: '#00ff00', fontFamily: 'monospace'
        }).setDepth(2000);

        this.scene.events.on('update-hp', (atual, max) => this.desenharBarraVida(atual, max));

        // BITS (Ilha 6000)
        this.scene.textoBits = this.scene.add.text(this.offBits + 150, this.offBits + 50, 'BITS: 0', estiloTexto)
            .setOrigin(0.5).setDepth(2000);

        // TURNO (Ilha 7000)
        this.scene.textoTurno = this.scene.add.text(this.offWave + 150, this.offWave + 50, 'WAVE: 01', estiloTexto)
            .setOrigin(0.5).setDepth(2000);
            
        this.desenharBarraVida(100, 100);
        this.applyCameraIgnores();
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

        // RELÓGIO (Sem o botão menu em cima)
        this.txtTempoWave = this.scene.add.text(off + camera.width - 80, worldY, '00:00', {
            fontSize: '16px', fill: '#00ff00', fontFamily: 'monospace', fontWeight: 'bold'
        }).setOrigin(0.5).setDepth(2001);

        const larguraSlot = 55;
        const espacamento = 15;
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
        // Agora só precisamos dizer para a câmera do jogo ignorar as ilhas de UI
        const tudoUI = [
            this.scene.textoBits, this.scene.textoTurno, 
            this.barraVida, this.textoHUD, ...(this.iconesRef || [])
        ].filter(el => el != null);

        this.scene.cameras.main.ignore(tudoUI);
    }

    setupListeners() {
        this.scene.events.on('update-timer', (texto) => {
            if (this.txtTempoWave) {
                this.txtTempoWave.setText(texto);
                this.txtTempoWave.setFill(texto.includes("DANGER") ? '#ff0000' : '#00ff00');
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
}