function Enemy(type){
    this.type = type;
    this.health =100;
}

Enemy.prototype.attack = function(){
    console.log(`O ${this.type} esta atacando!`);
};

const tiozao = new Enemy('Ogro');
const paraiba = new Enemy('Calango');

tiozao.attack();
paraiba.attack();