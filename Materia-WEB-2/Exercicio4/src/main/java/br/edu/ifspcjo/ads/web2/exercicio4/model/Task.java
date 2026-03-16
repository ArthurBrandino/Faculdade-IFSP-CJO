package model;

import java.util.Date;

public class Task {
    private int id;
    private String description;
    private Date date;
    private User user;

    public Task() {}

    public Task(int id, String description, Date date, User user) {
        this.id = id;
        this.description = description;
        this.date = date;
        this.user = user;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}
