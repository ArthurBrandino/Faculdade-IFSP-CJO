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
    <title>Home</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
    <h2>Bem-vindo, <%= user.getName() %>!</h2>

    <ul>
        <li><a href="task_register.jsp">Cadastrar nova tarefa</a></li>
    </ul>
</body>
</html>
