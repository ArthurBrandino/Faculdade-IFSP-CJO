import Player from '.Player.js';

export default class Cangaceiro extends Player{
    constructor(name, weapon, petName, petType){
        super(name, weapon);
        this.petName= petName;
        this.petType = petType
    }
    callPet() {
        console.log(`- ${this.name} chama seu ${this.petType} ${this.petName} para auxiliar na batalha...`);
    }
    attack(){
        console.log(`- ${this.name} faz um ataque duplo de ${this.weapon} e ${this.petType}!`);
    }
}