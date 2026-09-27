import openpyxl

def view_rooms():
    try:
        workbook = openpyxl.load_workbook('record.xlsx')
        worksheet = workbook.active

        # Print the header for room summary
        print("Room Number | Status")
        print("-----------------------")

        for row in worksheet.iter_rows(min_row=2, values_only=True):
            room_number = row[0]  # Assuming room number is in the first column
            status = "Available" if row[1] is None else "Booked"  # Assuming second column indicates booking status
            print(f"{room_number} | {status}")

    except FileNotFoundError:
        print("Error: The Excel file 'record.xlsx' does not exist.")

if __name__ == "__main__":
    view_rooms()
