from database import setup_database, add_activity, get_daily_summary, get_weekly_data
from tracker import log_activity
from visuals import show_daily_summary, plot_weekly_points
from datetime import datetime, timedelta

def main():
    setup_database()
    while True:
        print("\n1. Log Activity\n2. View Today’s Summary\n3. View Weekly Chart\n4. Exit")
        choice = input("Choose an option: ")
        
        if choice == "1":
            date, category, task, time_spent, value = log_activity()
            add_activity(date, category, task, time_spent, value)
            print("Activity logged!")
        
        elif choice == "2":
            today = datetime.now().strftime("%Y-%m-%d")
            data = get_daily_summary(today)
            show_daily_summary(today, data)
        
        elif choice == "3":
            start_date = (datetime.now() - timedelta(days=6)).strftime("%Y-%m-%d")
            data = get_weekly_data(start_date)
            plot_weekly_points(data)
        
        elif choice == "4":
            print("Goodbye!")
            break
        
        else:
            print("Invalid option, try again.")

if __name__ == "__main__":
    main()