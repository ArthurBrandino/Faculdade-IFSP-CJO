import Phaser from 'phaser';

const config = {
    type: Phaser.AUTO,
    width: 800,
    height: 600,
    scene: {
        preload: preload,
        create: create
    }
}

const game = new Phaser.Game(config);

function preload(){
    this.load.image('logo', 'assets/images/phaser-logo.png');
}

function create() {
    this.add.image(400, 300, 'logo');
}