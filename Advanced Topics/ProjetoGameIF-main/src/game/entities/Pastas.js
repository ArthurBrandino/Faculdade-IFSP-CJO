export class Pastas extends Phaser.GameObjects.Sprite {    
    constructor(scene, x, y) {
        const largura = 50;
        const altura = 50;
        super(scene, x, y, 'spr_folder', largura, altura);
        
        this.setFrame(1);
        this.vida = Phaser.Math.Between(3, 6); // vida aleatoria entre 3 e 6

        scene.add.existing(this);
        scene.physics.add.existing(this, true); // true para ser estático
        
        this.setInteractive(); // Permite Clicar
        this.on('pointerdown', () => {this.tentarMinerar();});
    }

    tentarMinerar(){
        const player = this.scene.enzinho;
        const dist = Phaser.Math.Distance.Between(this.x, this.y, player.x, player.y);

        if (dist < 150 ) {
            // Chamamos uma função na cena para adicionar os bits
            this.scene.adicionarBits(1);
            this.vida--;

            this.scene.tweens.add({
                targets: this,
                scale: 0.8,
                duration: 50,
                yoyo: true // Volta ao tamanho original
            });

            if(this.vida == 1) this.setFrame(0);
            if(this.vida <= 0)  this.destroy(); 
        } else {
            console.log("Muito longe para minerar!");
        }
    }

    static gerarGrupo(scene, quantidade) {
        for (let i = 0; i < quantidade; i++) {
            let xRaw = Phaser.Math.Between(100, 1900);
            let yRaw = Phaser.Math.Between(100, 1900);
            
            //Grid 50X50
            const xFinal = Math.floor(xRaw / 50) * 50 + 25;
            const yFinal = Math.floor(yRaw / 50) * 50 + 25;

            new Pastas(scene, xFinal, yFinal);
        }
    }
}