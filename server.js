const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const path = require('path');
const app = express();
const db = new sqlite3.Database('./students_info.db'); // Путь к вашей базе данных

app.use(express.static(path.join(__dirname, 'public')));

app.get('/data', (req, res) => {
    db.all('SELECT * FROM student_info', (err, rows) => {
        if (err) {
            res.status(500).send(err.message);
        } else {
            res.json(rows);
        }
    });
});

app.get('/search', (req, res) => {
    const { id, name } = req.query;
    let query = 'SELECT * FROM student_info WHERE 1=1';
    if (id) {
        query += ` AND ID = ${id}`;
    }
    if (name) {
        query += ` AND NAME LIKE '%${name}%'`;
    }
    db.all(query, (err, rows) => {
        if (err) {
            res.status(500).send(err.message);
        } else {
            res.json(rows);
        }
    });
});

app.listen(3000, () => {
    console.log('Server running on port 3000');
});
