package controller;

import model.Usuario;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;


public class LoginServlet extends HttpServlet
{
    private static final String EMAIL_VALIDO = "nome@yahoo.com.br";
    private static final String SENHA_VALIDA = "senha";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
    	throws ServletException, IOException {
	        String email = request.getParameter("email");
	        String password = request.getParameter("password");
	
	        Usuario usuario = new Usuario();
	        usuario.setEmail(email);
	        usuario.setPassword(password);
	
	        if (EMAIL_VALIDO.equals(email) && SENHA_VALIDA.equals(password)) {
	            request.setAttribute("usuario", usuario);
	            request.getRequestDispatcher("/sucesso.jsp").forward(request, response);
	        } else {
	            request.getRequestDispatcher("/erro.jsp").forward(request, response);
	        }
    	}

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    	throws ServletException, IOException {
        	request.getRequestDispatcher("/index.jsp").forward(request, response);
    	}
}