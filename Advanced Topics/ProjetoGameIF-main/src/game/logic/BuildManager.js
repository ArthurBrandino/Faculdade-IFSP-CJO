export class BuildManager {
    constructor(scene) {
        this.scene = scene;
        this.preview = scene.add.sprite(0, 0, '')
            .setAlpha(0.6)
            .setVisible(false)
            .setDepth(100)
            .setOrigin(0.5, 0.5);
        this.rangeGraphics = scene.previewRange;
        this.precoText = scene.previewPreco;
    }

    validarConstrucao(x, y) {
        const dados = this.scene.dadosDefesas[this.scene.selecionada];
        if (!dados) return { podeConstruir: false };

        // Calcula o Snap (Grade de 50x50)
        const gridX = Math.floor(x / 50) * 50;
        const gridY = Math.floor(y / 50) * 50;

        const snapX = gridX + (dados.largura / 2);
        const snapY = gridY + (dados.altura / 2);

        const temGrana = this.scene.bits >= dados.custo;

        const novaArea = new Phaser.Geom.Rectangle(
            snapX - dados.largura / 2 + 1, 
            snapY - dados.altura / 2 + 1, 
            dados.largura - 2, 
            dados.altura - 2
        );

        // Checa colisão com torres existentes
        const ocupado = this.scene.defesas.getChildren().some(defesa => {
            const areaLogicaExistente = new Phaser.Geom.Rectangle(
                defesa.x - defesa.width / 2 + 1,
                defesa.y - defesa.height / 2 + 1,
                defesa.width - 2,
                defesa.height - 2
            );
            return Phaser.Geom.Intersects.RectangleToRectangle(novaArea, areaLogicaExistente);
        });

        const sobreProcessador = Phaser.Geom.Intersects.RectangleToRectangle(novaArea, this.scene.processador.getBounds());

        return {
            podeConstruir: !ocupado && !sobreProcessador,
            temGrana: temGrana,
            x: snapX,
            y: snapY,
            custo: dados.custo
        };
    }

    tentarConstruir(x, y) {
        const dados = this.scene.dadosDefesas[this.scene.selecionada];
        if (!dados || dados.modo !== 'construcao') return;

        const validacao = this.validarConstrucao(x, y);

        if (validacao.podeConstruir && validacao.temGrana) {
            const novaDefesa = new dados.classe(this.scene, validacao.x, validacao.y);

            if (novaDefesa) {
                this.scene.bits -= validacao.custo;
                this.scene.textoBits.setText('Bits: ' + this.scene.bits);
                this.scene.defesas.add(novaDefesa);
                return true;
            }
        }
        return false;
    }

    atualizarPreview(mousePointer, dadosAtuais) {
        if (!dadosAtuais || dadosAtuais.modo !== 'construcao') {
            this.esconderPreview();
            return;
        }

        const worldPoint = mousePointer.positionToCamera(this.scene.cameras.main);
        const validacao = this.validarConstrucao(worldPoint.x, worldPoint.y);

        this.preview.setVisible(true);

        const nomeTextura = `spr_${dadosAtuais.nome.toLowerCase()}`;
        this.preview.setTexture(nomeTextura); 
        
        // Força o tamanho do sprite para o que está definido nos dados da torre
        this.preview.setDisplaySize(dadosAtuais.largura, dadosAtuais.altura);
        this.preview.setPosition(validacao.x, validacao.y);

        this.precoText.setVisible(true);
        this.precoText.setPosition(validacao.x, validacao.y);
        this.precoText.setText(`${dadosAtuais.custo} bits`);

        const podeColocar = validacao.podeConstruir && validacao.temGrana;
        const corFeedback = podeColocar ? 0x00ff00 : 0xff0000;

        this.preview.setTint(corFeedback);

        this.desenharRange(validacao.x, validacao.y, dadosAtuais, corFeedback);
    }

    desenharRange(x, y, dados, cor) {
        if (dados.nome !== 'Firewall') {
            this.rangeGraphics.setVisible(true);
            this.rangeGraphics.clear();
            this.rangeGraphics.lineStyle(2, cor, 0.5);
            this.rangeGraphics.fillStyle(cor, 0.1);
            const raio = dados.range || 150;
            this.rangeGraphics.strokeCircle(x, y, raio);
            this.rangeGraphics.fillCircle(x, y, raio);
        } else {
            this.rangeGraphics.setVisible(false);
        }
    }

    esconderPreview() {
        this.preview.setVisible(false);
        this.rangeGraphics.setVisible(false);
        this.precoText.setVisible(false);
    }
}