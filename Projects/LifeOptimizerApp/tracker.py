from datetime import datetime

def log_activity():
    date = datetime.now().strftime("%Y-%m-%d")
    category = input("Category (e.g., Study, Work, Health): ")
    task = input("Task: ")
    time_spent = float(input("Time spent (hours, e.g., 2.5): "))
    value = int(input("Value (1-10): "))
    return date, category, task, time_spent, value