import Phaser from 'phaser';
import Player from '../entities/Player';

export default class PreloadScene extends Phaser.Scene  {
    constructor(config) {
        super({key: 'GameScene'});
        this.config = config;
    }
    init()  {

    }
    create()    {
        this.createBackground();
        this.createPlayer();
    }

    update(time, delta) {

    }
    createBackground()  {
        thisadd.image(
            this.config.width * 0.5,
            this.config.height *0.5,
            'cenario'
        );
    }

    createPlayer()  {
        const startX = this.config.width * 0.5;
        const startY = this.config.height - 235;

        this.player = new Player(this, startX, startY);
    }
}