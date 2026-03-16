<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="java.util.List,br.edu.ifspcjo.ads.web2.Exercicio1.Aluno"%>
<!DOCTYPE html>
<html lang="pt-BR">
<head>
	<meta charset="UTF-8">
	<title>Confrimação de Formulário</title>
</head>
<body>
	<%
    	Aluno aluno = (Aluno) request.getAttribute("aluno");
   	 	String[] cursos = aluno.getCursos();
	%>

	<p>Nome: <%= aluno.getName() %></p>
	<p>Email: <%= aluno.getEmail() %></p>

	<ul>
	    <% for (String curso : cursos) { %>
	        <li><%= curso %></li>
	    <% } %>
	</ul>

</body>
</html>