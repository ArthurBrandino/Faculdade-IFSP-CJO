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
            // Força o texto a quebrar linha sozinho antes de estourar a tela
            wordWrap: { width: width - (margemX * 2), useAdvancedWrap: true }
        };

        // --- BLOCO 1: TÍTULO DA NOTIFICAÇÃO ---
        let textoCompleto = "A problem has been detected and Cyber_Defense.exe has been terminated to prevent damage to your computer.\n\n";
        
        // --- BLOCO 2: O ERRO EM CAIXA ALTA (Geralmente o motivo do Game Over) ---
        textoCompleto += "GAME_OVER_SYSTEM_DESTROYED\n\n";
        
        // --- BLOCO 3: INSTRUÇÕES CLÁSSICAS ---
        textoCompleto += "If this is the first time you've seen this Stop error screen, restart your computer. If this screen appears again, follow these steps:\n\n";
        textoCompleto += "Check to make sure any new hardware or software (like your FIREWALL or CLICKER) is properly installed.\n";
        textoCompleto += "If problems continue, disable or remove any newly installed software or drivers. Check your system resources for virus or malware infections.\n\n";
        
        // --- BLOCO 4: COMANDO INTERATIVO PARA O JOGADOR ---
        textoCompleto += "Click anywhere with your mouse to restart the system and try again.\n\n";
        
        // --- BLOCO 5: CÓDIGOS TÉCNICOS INVENTADOS (HEXADECIMAIS DE ZUERA) ---
        textoCompleto += "Technical information:\n\n";
        textoCompleto += "*** STOP: 0x000000D1 (0x0000000C, 0x00000002, 0x00000000, 0xF86B5A89)\n\n";
        textoCompleto += "*** cyber_defense.sys - Address F86B5A89 base at F86B0000, DateStamp 36b122e2";

        // Adiciona a muralha de texto na tela
        this.add.text(margemX, 60, textoCompleto, estiloBSOD);

        // --- INTERATIVIDADE ---
        // Ao clicar, "reinicia" a máquina voltando para o menu principal
        this.input.once('pointerdown', () => {
            this.scene.start('MainMenu');
        });
    }
}