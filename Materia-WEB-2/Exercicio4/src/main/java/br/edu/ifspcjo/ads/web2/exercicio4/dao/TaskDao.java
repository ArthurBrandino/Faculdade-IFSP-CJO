package dao;

import model.Task;
import model.User;
import utils.DataSourceManager;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class TaskDao {

    public void create(Task task) {
        String sql = "INSERT INTO tasks (description, date, user_id) VALUES (?, ?, ?)";

        try (Connection conn = DataSourceManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, task.getDescription());
            stmt.setDate(2, new java.sql.Date(task.getDate().getTime()));
            stmt.setInt(3, task.getUser().getId());
            stmt.executeUpdate();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public List<Task> findAllByUser(User user) {
        List<Task> tasks = new ArrayList<>();
        String sql = "SELECT * FROM tasks WHERE user_id = ? ORDER BY date";

        try (Connection conn = DataSourceManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, user.getId());
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                Task task = new Task();
                task.setId(rs.getInt("id"));
                task.setDescription(rs.getString("description"));
                task.setDate(rs.getDate("date"));
                task.setUser(user);

                tasks.add(task);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return tasks;
    }
}
