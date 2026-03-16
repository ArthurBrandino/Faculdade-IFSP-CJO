package lojaonline;

import java.util.ArrayList;

public class Pedido 
{
	private Cliente cliente;
	private ArrayList<Produto> produtos;
	
	public Pedido(Cliente cliente)
	{
		this.cliente = cliente;
		produtos = new ArrayList<Produto>();
	}
	
	public void adicionarProduto(Produto produto)
	{
		produtos.add(produto);
	}
	
	private double calcularSubtotal()
	{
		double subtotal = 0.0;
		
		for (Produto produto : produtos)
		{
			subtotal += produto.getPreco();
		}
		
		return subtotal;
	}
	
	private double calcularFrete()
	{
		double frete = 0.0;
		
		for (Produto produto : produtos)
		{
			frete += produto.getPeso();
		}
			
		return frete * 5.0;
	}
	
	public void finalizar()
	{
		System.out.println("=====RESUMO DO PEDIDO=====");
		System.out.println(cliente);
		
		System.out.println("=====ITENS DO PEDIDO=====");
		for (Produto produto : produtos)
		{
			System.out.println(produto);
		}
		
		double subtotal = calcularSubtotal();
		double frete = calcularFrete();
		
		System.out.println("=====TOTAL=====");
		System.out.println("SUBTOTAL: " + subtotal);
		System.out.println("FRETE: " + frete);
		System.out.println("TOTAL: " + (subtotal + frete));
	}
}
