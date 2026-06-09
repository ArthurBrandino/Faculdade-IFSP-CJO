import Phaser from 'phaser';

export class Player extends Phaser.Physics.Arcade.Sprite {
    constructor(scene, x, y) {
        super(scene, x, y, 'player_idle', 0);
        
        scene.add.existing(this);
        scene.physics.add.existing(this);
        
        this.body.setCollideWorldBounds(true);
        this.speed = 300;
        this.danoAtaque = 1;
        this.cursors = scene.input.keyboard.createCursorKeys();
        this.teclasWASD = scene.input.keyboard.addKeys({
            up: Phaser.Input.Keyboard.KeyCodes.W,
            down: Phaser.Input.Keyboard.KeyCodes.S,
            left: Phaser.Input.Keyboard.KeyCodes.A,
            right: Phaser.Input.Keyboard.KeyCodes.D
        });

        this.setScale(2.5); 
        this.setPixelArt = true; 

        this.body.setSize(14, 16);
        this.body.setOffset(5, 6);

        this.ultimaDirecaoX = 0;
        this.ultimaDirecaoY = 1; 
        this.ultimoCliqueTempo = 0;

        this.configurarAnimacoes(scene);

        if (scene.anims.exists('player_idle_down')) {
            this.play('player_idle_down');
        }
    }

    configurarAnimacoes(scene) {
        // --- IDLES ---
        if (!scene.anims.exists('player_idle_down')) {
            scene.anims.create({ key: 'player_idle_down', frames: scene.anims.generateFrameNumbers('player_idle', { start: 0, end: 3 }), frameRate: 6, loop: -1 });
        }
        if (!scene.anims.exists('player_idle_side')) {
            scene.anims.create({ key: 'player_idle_side', frames: scene.anims.generateFrameNumbers('player_idle', { start: 8, end: 11 }), frameRate: 6, loop: -1 });
        }
        if (!scene.anims.exists('player_idle_up')) {
            scene.anims.create({ key: 'player_idle_up', frames: scene.anims.generateFrameNumbers('player_idle', { start: 16, end: 19 }), frameRate: 6, loop: -1 });
        }

        // --- CORRIDAS ---
        if (!scene.anims.exists('player_run_down')) {
            scene.anims.create({ key: 'player_run_down', frames: scene.anims.generateFrameNumbers('player_run', { start: 0, end: 5 }), frameRate: 12, loop: -1 });
        }
        if (!scene.anims.exists('player_run_side')) {
            scene.anims.create({ key: 'player_run_side', frames: scene.anims.generateFrameNumbers('player_run', { start: 12, end: 17 }), frameRate: 12, loop: -1 });
        }
        if (!scene.anims.exists('player_run_up')) {
            scene.anims.create({ key: 'player_run_up', frames: scene.anims.generateFrameNumbers('player_run', { start: 24, end: 29 }), frameRate: 12, loop: -1 });
        }

        // --- ATAQUES ---
        if (!scene.anims.exists('player_attack_down')) {
            scene.anims.create({ key: 'player_attack_down', frames: scene.anims.generateFrameNumbers('player_attack', { start: 0, end: 5 }), frameRate: 14, loop: 0 });
        }
        if (!scene.anims.exists('player_attack_side')) {
            scene.anims.create({ key: 'player_attack_side', frames: scene.anims.generateFrameNumbers('player_attack', { start: 12, end: 17 }), frameRate: 14, loop: 0 });
        }
        if (!scene.anims.exists('player_attack_up')) {
            scene.anims.create({ key: 'player_attack_up', frames: scene.anims.generateFrameNumbers('player_attack', { start: 24, end: 29 }), frameRate: 14, loop: 0 });
        }

        // --- INTERAÇÃO / CONSTRUÇÃO (Novas animações baseadas no Interact-Sheet) ---
        if (!scene.anims.exists('player_interact_down')) {
            scene.anims.create({ key: 'player_interact_down', frames: scene.anims.generateFrameNumbers('player_interact', { start: 0, end: 3 }), frameRate: 12, loop: 0 });
        }
        if (!scene.anims.exists('player_interact_side')) {
            scene.anims.create({ key: 'player_interact_side', frames: scene.anims.generateFrameNumbers('player_interact', { start: 8, end: 11 }), frameRate: 12, loop: 0 });
        }
        if (!scene.anims.exists('player_interact_up')) {
            scene.anims.create({ key: 'player_interact_up', frames: scene.anims.generateFrameNumbers('player_interact', { start: 16, end: 19 }), frameRate: 12, loop: 0 });
        }
    }

    update() {
        this.body.setVelocity(0);
        let moveX = 0;
        let moveY = 0;

        if (this.cursors.left.isDown || this.teclasWASD.left.isDown)       moveX = -1;
        else if (this.cursors.right.isDown || this.teclasWASD.right.isDown) moveX = 1;

        if (this.cursors.up.isDown || this.teclasWASD.up.isDown)           moveY = -1;
        else if (this.cursors.down.isDown || this.teclasWASD.down.isDown)   moveY = 1;

        if (moveX !== 0 || moveY !== 0) {
            this.body.setVelocityX(moveX * this.speed);
            this.body.setVelocityY(moveY * this.speed);
        }

        // Se estiver atacando OU construindo, deixa a animação visual terminar antes de aplicar corrida/idle
        if (this.anims.isPlaying && (this.anims.currentAnim.key.startsWith('player_attack') || this.anims.currentAnim.key.startsWith('player_interact'))) {
            if (moveY !== 0) { this.ultimaDirecaoY = moveY; this.ultimaDirecaoX = 0; }
            else if (moveX !== 0) { this.ultimaDirecaoX = moveX; this.ultimaDirecaoY = 0; }
            return; 
        }

        // Máquina de estados padrão
        if (moveY === 1) {
            this.play('player_run_down', true);
            this.ultimaDirecaoY = 1;
            this.ultimaDirecaoX = 0;
        } 
        else if (moveY === -1) {
            this.play('player_run_up', true);
            this.ultimaDirecaoY = -1;
            this.ultimaDirecaoX = 0;
        } 
        else if (moveX !== 0) {
            this.play('player_run_side', true);
            this.setFlipX(moveX === -1);
            this.ultimaDirecaoX = moveX;
            this.ultimaDirecaoY = 0;
        } 
        else {
            if (this.ultimaDirecaoY === 1)       this.play('player_idle_down', true);
            else if (this.ultimaDirecaoY === -1) this.play('player_idle_up', true);
            else if (this.ultimaDirecaoX !== 0) {
                this.play('player_idle_side', true);
                this.setFlipX(this.ultimaDirecaoX === -1);
            } else {
                this.play('player_idle_down', true);
            }
        }
    }

    atacar(worldPoint, listaInimigos, listaPastas) {
        const tempoAtual = this.scene.time.now;
        const diferencaTempo = tempoAtual - this.ultimoCliqueTempo;
        this.ultimoCliqueTempo = tempoAtual;

        let escalaVelocidade = 1;
        if (diferencaTempo < 300) {
            escalaVelocidade = 1 + ((300 - diferencaTempo) / 250); 
            escalaVelocidade = Phaser.Math.Clamp(escalaVelocidade, 1, 1.8);
        }

        const angulo = Phaser.Math.Angle.Between(this.x, this.y, worldPoint.x, worldPoint.y);
        const graus = Phaser.Math.RadToDeg(angulo);

        let animAtaque = 'player_attack_down';

        if (graus >= -135 && graus < -45)      animAtaque = 'player_attack_up';
        else if (graus >= 45 && graus < 135)   animAtaque = 'player_attack_down';
        else if (graus < -135 || graus >= 135) { animAtaque = 'player_attack_side'; this.setFlipX(true); }
        else                                  { animAtaque = 'player_attack_side'; this.setFlipX(false); }

        this.play(animAtaque, true);
        this.anims.timeScale = escalaVelocidade;
    }

    // =====================================================================
    // NOVO MÉTODO: DISPARA A ANIMAÇÃO DE CONSTRUÇÃO NA DIREÇÃO DO EVENTO
    // =====================================================================
    interagir(worldPoint) {
        // Redefine a escala de tempo para velocidade normal de construção (1.0)
        this.anims.timeScale = 1.0;

        // Calcula para onde o jogador deve olhar baseado na posição da construção
        const angulo = Phaser.Math.Angle.Between(this.x, this.y, worldPoint.x, worldPoint.y);
        const graus = Phaser.Math.RadToDeg(angulo);

        let animInteract = 'player_interact_down';

        if (graus >= -135 && graus < -45) {
            animInteract = 'player_interact_up';
            this.ultimaDirecaoY = -1;
            this.ultimaDirecaoX = 0;
        }
        else if (graus >= 45 && graus < 135) {
            animInteract = 'player_interact_down';
            this.ultimaDirecaoY = 1;
            this.ultimaDirecaoX = 0;
        }
        else if (graus < -135 || graus >= 135) {
            animInteract = 'player_interact_side';
            this.setFlipX(true);
            this.ultimaDirecaoX = -1;
            this.ultimaDirecaoY = 0;
        }
        else {
            animInteract = 'player_interact_side';
            this.setFlipX(false);
            this.ultimaDirecaoX = 1;
            this.ultimaDirecaoY = 0;
        }

        this.play(animInteract, true);
    }
}