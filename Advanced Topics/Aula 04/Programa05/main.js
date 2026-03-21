import Player from './Cangaceiro.js';

console.log("\n=> Playing... The Calango's Hunter \n");

const player = new Player('Walter paraiba', 'pexeira', 'Lampiao', 'calango');

player.callPet();
player.attack();
player.takeDamage(30);

console.log();