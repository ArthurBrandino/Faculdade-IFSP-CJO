<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Cadastro de Usuários</title>
</head>
<body>
    <h2>Cadastro de Usuário</h2>
    <form action="register" method="post">
        <label for="name">Nome:</label><br>
        <input type="text" name="name" required><br><br>

        <label for="email">Email:</label><br>
        <input type="email" name="email" required><br><br>

        <label for="password">Senha:</label><br>
        <input type="password" name="password" required><br><br>

        <input type="submit" value="Cadastrar">
    </form>

    <p>Já é cadastrado? <a href="login.jsp">Login</a></p>
</body>
</html>
