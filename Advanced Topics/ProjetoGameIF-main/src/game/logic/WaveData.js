
export const WAVES = [
    {
        id: 1,
        safeTime: 5000,   // 5 segundos de paz
        dangerTime: 15000, // 15 segundos nascendo bicho
        inimigos: [
            { classe: 'Worm', quantidade: 10, intervalo: 1000 }
        ],
        pastasParaCriar: 2
    },
    {
        id: 2,
        safeTime: 8000,
        dangerTime: 20000,
        inimigos: [
            { classe: 'Worm', quantidade: 15, intervalo: 800 },
            { classe: 'Trojan', quantidade: 2, intervalo: 3000 }
        ],
        pastasParaCriar: 4
    }
];