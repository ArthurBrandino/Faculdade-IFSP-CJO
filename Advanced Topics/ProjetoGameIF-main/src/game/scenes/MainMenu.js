import { Scene } from 'phaser';

export class MainMenu extends Scene
{
    constructor ()
    {
        super('MainMenu');
    }

    create() {
        const { width, height } = this.scale;
        this.musicaMenu = this.sound.add('TurnOn'); 
        this.musicaMenu.play({ loop: true }); 

        //Layout do Menu
        const fundo = this.add.rectangle(width/2, height/2, width, height, 0x4493ee);
        const barracima = this.add.rectangle(width / 2, 0, width, 150, 0x245edb);
        const barrabaixo = this.add.rectangle(width / 2, height, width, 150, 0x245edb);
        
        //Painel Esquerdo 
        this.logoXP = this.add.image(width * 0.2 + 210, height * 0.4 -20, 'logo_winxp');
        this.logoXP.setScale(0.4);
        this.add.text(width * 0.1 + 100, height * 0.4 + 80, 'Para começar, clique no seu nome de usuário', { 
                fontSize: '18px', 
                fontFamily: 'Tahoma',
                fill: '#ffffff',
                shadow: { offsetX: 1, offsetY: 1, color: '#000000', blur: 2, fill: true } // Sombra suave estilo XP
        });

        //Divisor Central
        this.add.rectangle(width * 0.45, height/2, 2, height * 0.6, 0xffffff, 0.5);

        //Usuarios (Botao de Start)
        const userX = width * 0.55;
        const userY = height * 0.45;

        //Foto de Perfil
        const avatar = this.add.image(userX, userY, 'avatar')
            .setScale(0.08) 
            .setInteractive({ useHandCursor: true });
            
        //Nome do Usuário
        const userName = this.add.text(userX + 60, userY - 10, 'ADMINISTRADOR', { 
            fontSize: '22px', fontWeight: 'bold', fontFamily: 'Tahoma' 
        }).setInteractive({ useHandCursor: true });

        //Mensagem
        this.add.text(userX + 60, userY + 15, 'Clique aqui para logar', { 
            fontSize: '14px', fill: '#cccccc' 
        });

        // Lógica de Clique 

        const iniciarJogo = () => {
            this.musicaMenu.stop(); 

            const efeitoStart = this.sound.add('Start');
            efeitoStart.play();
            
            this.cameras.main.fadeOut(1000, 0, 0, 0);
            this.cameras.main.once('camerafadeoutcomplete', () => {
                // Passamos o EFEITO START (que ainda está tocando) para a cena Game
                this.scene.start('IntroCutscene', { somTransicao: efeitoStart });
            });
        };

        avatar.on('pointerdown', iniciarJogo);
        userName.on('pointerdown', iniciarJogo);

        // 6. Botão de Desligar 
        const containerDesligar = this.add.container(40, height - 35);

    
        this.onButton = this.add.image(0, 0, 'on_button');

        const desligarTexto = this.add.text(15, -8, ' Créditos', { 
            fontSize: '16px', 
            fill: '#fff',
            fontFamily: 'Tahoma' // Fonte clássica do XP
        });

        containerDesligar.add([this.onButton, desligarTexto]);

        containerDesligar.setSize(200, 30);
        containerDesligar.setInteractive({ useHandCursor: true });

        containerDesligar.on('pointerdown', () => {
            this.mostrarCreditos();
        });

        containerDesligar.on('pointerover', () => {
            desligarTexto.setStyle({ fill: '#ffcc00' });
            containerDesligar.setScale(0.95); // Aumenta 10%
        });

        containerDesligar.on('pointerout', () => {
            desligarTexto.setStyle({ fill: '#fff' });
            containerDesligar.setScale(1.0); // Volta ao tamanho normal
        });

    }
    mostrarCreditos() {
        const { width, height } = this.scale;

        const overlay = this.add.rectangle(width/2, height/2, width, height, 0x000000, 0.7);
        overlay.setInteractive(); 

        const janela = this.add.container(width/2, height/2);

        const fundoJanela = this.add.rectangle(0, 0, 400, 300, 0xced4d6);
        
        const bordaJanela = this.add.graphics();
        bordaJanela.lineStyle(2, 0x000000);
        bordaJanela.strokeRect(-200, -150, 400, 300);

        const barraTitulo = this.add.rectangle(0, -135, 400, 30, 0x000080);
        const titulo = this.add.text(-190, -145, 'System Credits', { 
            fontSize: '14px', fill: '#fff', fontWeight: 'bold' 
        });

        const containerFechar = this.add.container(185, -135); 

        const retanguloBotao = this.add.rectangle(0, 0, 20, 20, 0xcc0000);
        const txtFechar = this.add.text(0, 0, 'x', { fontSize: '16px', fill: '#fff' }).setOrigin(0.5);

        containerFechar.add([retanguloBotao, txtFechar]);
        containerFechar.setSize(20, 20);
        containerFechar.setInteractive({ useHandCursor: true });

        containerFechar.on('pointerover', () => containerFechar.setScale(0.9));
        containerFechar.on('pointerout', () => containerFechar.setScale(1.0));
        
        containerFechar.on('pointerdown', () => {
            janela.destroy();
            overlay.destroy();
            bordaJanela.destroy(); 
        });
        // 4. Texto dos Créditos
        const textoCreditos = this.add.text(0, 20, 
            'TROJAN.ENZINHO.EXE\n\n' +
            'Desenvolvido por: Arthur Brandino\n' +
            'Arte: Nicholas Koedel\n' +
            'Motor: Phaser 3\n\n' +
            '2026 - Todos os vírus reservados.', 
            { fontSize: '16px', fill: '#000', align: 'center', fontFamily: 'monospace' }
        ).setOrigin(0.5);

        // 5. Adicionar tudo à Janela
        // IMPORTANTE: Adicionamos o containerFechar como filho da janela
        janela.add([fundoJanela, barraTitulo, titulo, textoCreditos, containerFechar]);
    }
}
