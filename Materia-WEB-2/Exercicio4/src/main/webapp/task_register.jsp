<%@ page contentType="text/html;charset=UTF-8" %>
<%@ page import="model.User" %>
<%
    User user = (User) session.getAttribute("user");
    if (user == null) {
        response.sendRedirect("login.jsp");
        return;
    }
%>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Nova Tarefa</title>
</head>
<body>
    <h2>Nova Tarefa</h2>
    <form action="add-task" method="post">
        <label for="description">Descrição:</label><br>
        <input type="text" name="description" required><br><br>

        <label for="date">Data:</label><br>
        <input type="date" name="date" required><br><br>

        <input type="submit" value="Salvar Tarefa">
    </form>

    <p style="color:red;">
        <%= request.getAttribute("error") != null ? request.getAttribute("error") : "" %>
    </p>

    <p><a href="home.jsp">Retornar</a></p>
</body>
</html>
