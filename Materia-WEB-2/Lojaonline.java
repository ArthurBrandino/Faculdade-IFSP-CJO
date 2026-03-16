package lojaonline;

public class Lojaonline
{
	public static void main(String[] args)
	{
		Cliente cliente = new Cliente("Fulano", "fulano@email.com", "400.289.220-00");
	
		Produto livro = new Produto("O Senhor dos Anéis", 100.0, 0.5);
		Produto jogo = new Produto("Minecraft", 250.0, 0.5);
		Produto console = new Produto("PlayStation 5", 2500.0, 3.0);
		
		Pedido pedido = new Pedido(cliente);
		pedido.adicionarProduto(livro);
		pedido.adicionarProduto(jogo);
		pedido.adicionarProduto(console);
		pedido.finalizar();
	}
}
