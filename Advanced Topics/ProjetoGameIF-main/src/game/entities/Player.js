export class Player extends Phaser.GameObjects.Rectangle {
    constructor(scene, x, y) {
        // Cena, x, y, largura, altura, cor
        super(scene, x, y, 40, 40, 0x0000ff);
        
        // Adiciona à cena e ativa física
        scene.add.existing(this);
        scene.physics.add.existing(this);
        
        this.body.setCollideWorldBounds(true);
        this.speed = 300;
        this.cursors = scene.input.keyboard.createCursorKeys();
        this.teclasWASD = scene.input.keyboard.addKeys({
            up: Phaser.Input.Keyboard.KeyCodes.W,
            down: Phaser.Input.Keyboard.KeyCodes.S,
            left: Phaser.Input.Keyboard.KeyCodes.A,
            right: Phaser.Input.Keyboard.KeyCodes.D
        });
    }

    update() {
        const speed = 300;
        this.body.setVelocity(0);

        if (this.cursors.left.isDown || this.teclasWASD.left.isDown)        this.body.setVelocityX(-this.speed);
        else if (this.cursors.right.isDown || this.teclasWASD.right.isDown) this.body.setVelocityX(this.speed);
        if (this.cursors.up.isDown || this.teclasWASD.up.isDown)            this.body.setVelocityY(-this.speed);
        else if (this.cursors.down.isDown || this.teclasWASD.down.isDown)   this.body.setVelocityY(this.speed);
    }

    atacar(worldPoint, listaInimigos, listaPastas) {
        this.play('animacao-ataque');
    }
}