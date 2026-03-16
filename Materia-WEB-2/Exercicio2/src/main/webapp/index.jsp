<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="pt-BR">
<head>
	<meta charset="UTF-8">
	<title>Cadastro de Pessoas</title>
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<h1>Login</h1>
	<form action="LoginServlet" method="post">	
		<label for="email">E-mail:</label>
		<input type="email" name="email" id="email" required>
		
		<label for="password">Senha:</label>
		<input type="password" name="password" id="password" required>
		
		<input type="submit" value="Enviar">
	</form>
</body>
