<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <title>Tarefas Atuais</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <h1>Lista de Tarefas</h1>
    <table border="1">
        <tr>
            <th>ID</th>
            <th>Descrição</th>
            <th>Data</th>
        </tr>
        <c:forEach var="task" items="${tasks}">
            <tr>
                <td>${task.id}</td>
                <td>${task.description}</td>
                <td>${task.date}</td>
            </tr>
        </c:forEach>
    </table>
    <a href="formulario.jsp">Adicionar Nova Tarefa</a>
</body>
</html>
