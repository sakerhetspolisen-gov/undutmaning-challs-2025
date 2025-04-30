import sys
from datetime import datetime, timedelta
import random

WORK_START_HOUR = 9
WORK_END_HOUR = 17

def is_weekday(date):
    return date.weekday() < 5  # Monday=0, Sunday=6

def randomize_time(date):
    """Randomize time within work hours."""
    random_hour = random.randint(WORK_START_HOUR, WORK_END_HOUR - 1)
    random_minute = random.randint(0, 59)
    random_second = random.randint(0, 59)
    date = date.replace(hour=random_hour, minute=random_minute, second=random_second)
    return date

def next_working_time(date):
    """Ensures the date is on a weekday and during work hours, moving forward if necessary."""
    if date.hour >= WORK_END_HOUR:
        # Move to the next day if time is after working hours
        date += timedelta(days=1)
        date = date.replace(hour=WORK_START_HOUR, minute=0, second=0)
    if date.weekday() >= 5:  # If it's a weekend, move to the next Monday
        date += timedelta(days=(7 - date.weekday()))
    return date

def adjust_time(date, increment_days=False):
    """Adjusts the time, randomizing within work hours and moving to next working day if required."""
    if increment_days:
        # Move to the next day (considering weekends)
        date += timedelta(days=1)
    date = next_working_time(date)
    return randomize_time(date)

def parse_and_update_dates(input_file, output_file, start_date_str):
    try:
        # Convert start_date_str to datetime object
        current_date = datetime.strptime(start_date_str, '%Y-%m-%d %H:%M:%S')
    except ValueError as e:
        print(f"Error: Invalid date format '{start_date_str}'. Please use 'YYYY-MM-DD HH:MM:SS'.")
        sys.exit(1)

    try:
        # Open input and output files
        with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
            print(f"Processing file '{input_file}'...")

            lines = infile.readlines()
            last_mailer_line = None
            increment_days = False
            pair_count = 0

            for line in lines:
                if line.startswith("From MAILER-DAEMON "):
                    # Write updated "From MAILER-DAEMON" line
                    current_date = adjust_time(current_date, increment_days)
                    new_mailer_line = f"From MAILER-DAEMON {current_date.strftime('%a %b %d %H:%M:%S %Y')}\n"
                    outfile.write(new_mailer_line)
                    last_mailer_line = new_mailer_line
                    increment_days = True  # Ensure that the next pair has a later date
                    pair_count += 1
                    print(f"Updated 'From MAILER-DAEMON' line with new randomized date: {current_date.strftime('%Y-%m-%d %H:%M:%S')}")
                elif line.startswith("Date:"):
                    if last_mailer_line:
                        # Write updated "Date:" line to match the From MAILER-DAEMON date
                        new_date_line = f"Date: {current_date.strftime('%a, %d %b %Y %H:%M:%S +0000')}\n"
                        outfile.write(new_date_line)
                        last_mailer_line = None  # Reset for next pair
                        print(f"Updated 'Date:' line with new randomized date: {current_date.strftime('%Y-%m-%d %H:%M:%S')}")
                    else:
                        # Skip if we encounter a Date without a corresponding MAILER-DAEMON line
                        print("Warning: 'Date:' found without a preceding 'From MAILER-DAEMON'. Skipping this line.")
                        outfile.write(line)
                else:
                    # Write other lines unchanged
                    outfile.write(line)

            print(f"Processing complete. {pair_count} 'From MAILER-DAEMON' and 'Date:' pairs updated.")
            print(f"Output written to '{output_file}'.")

    except FileNotFoundError:
        print(f"Error: File '{input_file}' not found. Please check the file path.")
        sys.exit(1)
    except IOError as e:
        print(f"Error: I/O error occurred while reading '{input_file}' or writing '{output_file}': {e}")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python update_dates.py <input_file> <output_file> <start_date 'YYYY-MM-DD HH:MM:SS'>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    start_date_str = sys.argv[3]

    print("Starting date update process...")
    parse_and_update_dates(input_file, output_file, start_date_str)
