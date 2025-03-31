import sqlite3

def setup_database():
    conn = sqlite3.connect("data.db")
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS activities
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  date TEXT,
                  category TEXT,
                  task TEXT,
                  time_spent REAL,
                  value INTEGER,
                  points REAL)''')
    conn.commit()
    conn.close()

def add_activity(date, category, task, time_spent, value):
    points = time_spent * value
    conn = sqlite3.connect("data.db")
    c = conn.cursor()
    c.execute("INSERT INTO activities (date, category, task, time_spent, value, points) VALUES (?, ?, ?, ?, ?, ?)",
              (date, category, task, time_spent, value, points))
    conn.commit()
    conn.close()

def get_daily_summary(date):
    conn = sqlite3.connect("data.db")
    c = conn.cursor()
    c.execute("SELECT category, task, time_spent, points FROM activities WHERE date = ?", (date,))
    results = c.fetchall()
    conn.close()
    return results

def get_weekly_data(start_date, days=7):
    conn = sqlite3.connect("data.db")
    c = conn.cursor()
    c.execute("SELECT date, SUM(points), SUM(time_spent) FROM activities WHERE date >= ? GROUP BY date LIMIT ?",
              (start_date, days))
    results = c.fetchall()
    conn.close()
    return results