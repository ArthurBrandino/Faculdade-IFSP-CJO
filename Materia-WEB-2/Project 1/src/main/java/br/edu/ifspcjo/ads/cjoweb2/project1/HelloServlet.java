package br.edu.ifspcjo.ads.cjoweb2.project1;

import java.io.IOException;
import java.io.PrintWriter;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@WebServlet("/servlet1") // mapear o servlet
public class HelloServlet extends HttpServlet{

	private static final long serialVersionUID = 1L;

	public HelloServlet() {
		super();
	}
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		//setar a codificação de caracteres da requisição
		req.setCharacterEncoding("UTF-8");
		//Obter os dados da requisição
		String name = req.getParameter("name");
		// setar o tipo de conteudo e a codificação de caracteres da resposta
		resp.setContentType("text/html;charset=UTF-8");
		//obter o escritor da resposta
		PrintWriter write = resp.getWriter();
		write.println("<!DOCTYPE html>");
		write.println("<html lang=\"pt-br\">");
		write.println("\t<head>");
		write.println("\t\t<meta charset=\"UTF-8\">");
		write.println("\t\t<title>Página de Boas-Vindas</title>");
		write.println("\t</head>");
		write.println("\t<body>");
		write.println("\t\t<h1>Seja Bem-Vindo(a), " + name + "</h1>");
		write.println("\t</body>");
		write.println("\t</html>");
		write.close();
	}
	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		doGet(req, resp);
	}
}
