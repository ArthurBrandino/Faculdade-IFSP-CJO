class Enemy{
    constructor(type){
        this.type = type;
        this.health = 100;
    }
    attack(){
        console.log(`O $ction({this.type} esta atacando!`);
    };

}

const tiozao = new Enemy('Ogro');
const paraiba = new Enemy('Calango');

tiozao.attack();
paraiba.attack();