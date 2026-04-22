export class Pastas extends Phaser.GameObjects.Rectangle {    
    constructor(scene, x, y) {
        super(scene, x, y, 50, 50, 0xffff00);
        
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


            if(this.vida <= 0)  this.destroy(); 
        } else {
            console.log("Muito longe para minerar!");
        }
    }

    static gerarGrupo(scene, quantidade) {
        for (let i = 0; i < quantidade; i++) {
            const x = Phaser.Math.Between(100, 1900);   // area X que Pode Ser spawnadas
            const y = Phaser.Math.Between(100, 1900);   // area Y que Pode Ser spawnadas
            
            // Aqui a classe cria instâncias de si mesma
            new Pastas(scene, x, y);
        }
    }
}