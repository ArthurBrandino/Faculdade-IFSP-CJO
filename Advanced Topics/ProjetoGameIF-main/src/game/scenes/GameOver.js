import { Scene } from 'phaser';

export class GameOver extends Scene
{
    constructor ()
    {
        super('GameOver');
    }

    create ()
    {
        this.sound.stopAll();
        this.sound.play('death_processador');
        this.sound.play('Shutdown');
        
        // 1. O Azul Oficial da BSOD do Windows XP (#0000AA)
        this.cameras.main.setBackgroundColor('#0000aa');

        // Referências de tamanho da tela para posicionamento do texto
        const { width, height } = this.scale;
        const margemX = 50;

        // Estilo de texto padrão para a Tela Azul (Fiel ao original)
        const estiloBSOD = {
            fontFamily: '"Lucida Console", "Courier New", Courier, monospace',
            fontSize: '18px',
            fill: '#ffffff',
            align: 'left',
            wordWrap: { width: width - (margemX * 2), useAdvancedWrap: true }
        };

        // --- NOVO: FAIXA DE DESTAQUE DO GAME OVER (Estilo Janela de Erro Antiga) ---
        // Desenha um retângulo branco no topo para criar o contraste
        const barraTitulo = this.add.graphics();
        barraTitulo.fillStyle(0xffffff, 1);
        barraTitulo.fillRect(margemX, 40, width - (margemX * 2), 35);

        // Texto GAME OVER azul escuro em cima da barra branca
        this.add.text(width / 2, 57, "--- GAME OVER ---", {
            fontFamily: '"Lucida Console", "Courier New", Courier, monospace',
            fontSize: '22px',
            fontWeight: 'bold',
            fill: '#0000aa',
        }).setOrigin(0.5);


        // --- CORPO DO TEXTO ---
        let textoCompleto = "A problem has been detected and Cyber_Defense.exe has been terminated to prevent damage to your computer.\n\n";
        textoCompleto += "SYSTEM_STATUS: CORRUPTED_BY_MALWARE\n\n";
        textoCompleto += "If this is the first time you've seen this Stop error screen, restart your computer. If this screen appears again, follow these steps:\n\n";
        textoCompleto += "Check to make sure any new hardware or software (like your FIREWALL, CLICKER or LIXEIRA) is properly installed.\n";
        textoCompleto += "If problems continue, disable or remove any newly installed software or drivers. Check your system resources for virus or malware infections.\n\n";
        
        // --- CÓDIGOS TÉCNICOS INVENTADOS ---
        textoCompleto += "Technical information:\n\n";
        textoCompleto += "*** STOP: 0x000000D1 (0x0000000C, 0x00000002, 0x00000000, 0xF86B5A89)\n\n";
        textoCompleto += "*** cyber_defense.sys - Address F86B5A89 base at F86B0000, DateStamp 36b122e2";

        // Adiciona a muralha de texto na tela (empurrada um pouco para baixo por causa da barra)
        this.add.text(margemX, 100, textoCompleto, estiloBSOD);


        // --- NOVO: PARTE INTERATIVA EM DESTAQUE (PISCANDO) ---
        // Texto isolado na parte inferior da tela para chamar a atenção do jogador
        const textoClique = this.add.text(width / 2, height - 80, "Press any key or CLICK ANYWHERE to continue", {
            fontFamily: '"Lucida Console", "Courier New", Courier, monospace',
            fontSize: '18px',
            fill: '#ffff00', // Amarelo clássico de alerta para quebrar o padrão branco
            fontWeight: 'bold'
        }).setOrigin(0.5);

        // Efeito de piscar (Blink) no texto de clique usando Tweens do Phaser
        this.tweens.add({
            targets: textoClique,
            alpha: 0,
            duration: 600,
            yoyo: true,
            repeat: -1
        });


        // --- INTERATIVIDADE ---
        // Captura tanto o clique do mouse quanto o toque na tela
        this.input.once('pointerdown', () => {
            this.scene.start('BadEnding');
        });

        // Opcional: Se o jogador apertar qualquer tecla do teclado, também reinicia
        this.input.keyboard.once('keydown', () => {
            this.scene.start('BadEnding');
        });
    }
}