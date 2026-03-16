<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <title>Tarefas</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <h1>Adicionar Nova Tarefa</h1>
    <form action="task" method="post">
        <label for="description">Descrição:</label>
        <input type="text" id="description" name="description" required>
        <br>
        <label for="date">Data:</label>
        <input type="date" id="date" name="date" required>
        <br>
        <button type="submit">Adicionar</button>
    </form>
    <a href="task">Ver Tarefas Listadas</a>
</body>
</html>
