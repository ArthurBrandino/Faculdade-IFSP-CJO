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
    },
    // --- WAVE 3: Introdução do ILY (O rolo compressor lento) ---
    {
        id: 3,
        safeTime: 8000,
        dangerTime: 25000,
        inimigos: [
            { classe: 'ILY', quantidade: 2, intervalo: 8000 }, // Jogador PRECISA comprar Firewall aqui
            { classe: 'Worm', quantidade: 8, intervalo: 1500 }
        ],
        pastasParaCriar: 3
    },
    // --- WAVE 4: O Combo do Trojan (Esponja de Clicker) ---
    {
        id: 4,
        safeTime: 10000,
        dangerTime: 30000,
        inimigos: [
            { classe: 'Trojan', quantidade: 5, intervalo: 4000 }, // Vai testar os Clickers e soltar muitos Worms ao morrer
            { classe: 'Worm', quantidade: 12, intervalo: 1000 }
        ],
        pastasParaCriar: 5
    },
    // --- WAVE 5: Pressão de Linha (ILY Avançando com Escolta) ---
    {
        id: 5,
        safeTime: 10000,
        dangerTime: 35000,
        inimigos: [
            { classe: 'ILY', quantidade: 3, intervalo: 6000 },
            { classe: 'Trojan', quantidade: 3, intervalo: 5000 },
            { classe: 'Worm', quantidade: 15, intervalo: 800 }
        ],
        pastasParaCriar: 6
    },
    // --- WAVE 6: Teste da Lixeira (O Enxame de Worms) ---
    {
        id: 6,
        safeTime: 12000,
        dangerTime: 40000,
        inimigos: [
            // Uma enxurrada de Worms vindo muito rápido para forçar dano em área (Lixeira)
            { classe: 'Worm', quantidade: 35, intervalo: 400 } 
        ],
        pastasParaCriar: 5
    },
    // --- WAVE 7: Divisão de Atenção (Trojan + ILY juntos) ---
    {
        id: 7,
        safeTime: 12000,
        dangerTime: 45000,
        inimigos: [
            { classe: 'Trojan', quantidade: 6, intervalo: 3500 },
            { classe: 'ILY', quantidade: 4, intervalo: 5000 }
        ],
        pastasParaCriar: 8
    },
    // --- WAVE 8: Inundação de Memória ---
    {
        id: 8,
        safeTime: 15000,
        dangerTime: 50000,
        inimigos: [
            { classe: 'Worm', quantidade: 25, intervalo: 600 },
            { classe: 'ILY', quantidade: 5, intervalo: 4000 },
            { classe: 'Trojan', quantidade: 4, intervalo: 4500 }
        ],
        pastasParaCriar: 7
    },
    // --- WAVE 9: Corrida do Ouro (Muito bicho rápido, pouca vida) ---
    {
        id: 9,
        safeTime: 15000,
        dangerTime: 45000,
        inimigos: [
            { classe: 'Worm', quantidade: 50, intervalo: 300 }, // Metralhadora de Worms
            { classe: 'ILY', quantidade: 2, intervalo: 10000 }
        ],
        pastasParaCriar: 10
    },
    // --- WAVE 10: APOCALIPSE DO SISTEMA (O Teste Estresse Final) ---
    {
        id: 10,
        safeTime: 20000,
        dangerTime: 60000,
        inimigos: [
            { classe: 'ILY', quantidade: 8, intervalo: 3000 },     // Destruidores constantes
            { classe: 'Trojan', quantidade: 10, intervalo: 2500 },  // Vão spawnar 30 Worms extras ao morrer!
            { classe: 'Worm', quantidade: 40, intervalo: 400 }     // Caos na tela
        ],
        pastasParaCriar: 15 // O mapa vai virar um lixão de pastas!
    }
];