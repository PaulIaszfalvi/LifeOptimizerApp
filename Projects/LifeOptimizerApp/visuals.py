import matplotlib.pyplot as plt

def show_daily_summary(date, data):
    if not data:
        print(f"No data for {date}")
        return
    print(f"\nDaily Summary for {date}:")
    total_points = 0
    total_time = 0
    for category, task, time, points in data:
        print(f"- {category}: {task} | {time} hrs | {points} pts")
        total_points += points
        total_time += time
    print(f"Total: {total_time} hrs, {total_points} pts")

def plot_weekly_points(data):
    dates = [row[0] for row in data]
    points = [row[1] for row in data]
    plt.plot(dates, points, marker='o')
    plt.title("Weekly Points")
    plt.xlabel("Date")
    plt.ylabel("Points")
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()