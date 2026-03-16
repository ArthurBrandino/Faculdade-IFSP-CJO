package br.edu.ifspcjo.ads.web2.Exercicio1;

import java.io.IOException;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.RequestDispatcher;

@WebServlet("/LoginAluno")
public class LoginAluno extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		request.setCharacterEncoding("UTF-8");
		String nome = request.getParameter("name");
		String email = request.getParameter("email");
		String[] cursos = request.getParameterValues("cursos");

		Aluno aluno = new Aluno();
		aluno.setName(nome);
		aluno.setEmail(email);
		aluno.setCursos(cursos);

		request.setAttribute("aluno", aluno);

		RequestDispatcher dispatcher = request.getRequestDispatcher("/resposta.jsp");
		dispatcher.forward(request, response);
	}
}
