#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <map>
#include <cstdlib> 
#include <algorithm> // for remove_if
using namespace std;

class LanguageManager {
private:
    map<string, string> translations;
public:
    void loadLanguage(const string& languageFile) {
        ifstream file(languageFile);
        string line;
        while (getline(file, line)) {
            size_t delimiterPos = line.find('=');
            if (delimiterPos != string::npos) {
                string key = line.substr(0, delimiterPos);
                string value = line.substr(delimiterPos + 1);
                translations[key] = value;
            }
        }
        file.close();
    }
    string getTranslation(const string& key) {
    if (translations.find(key) != translations.end()) {
        return translations[key];
    } else {
        cout << "Translation key not found: " << key << endl; // Debug statement
        return key; // Return the key itself if not found
    }
}
};

void printLine(char ch, int length) {
    for (int i = 0; i < length; i++) {
        cout << ch;
    }
    cout << endl;
}
void printHeader(const string& title) {
    printLine('=', 50);
    cout << "\t\t" << title << endl;
    printLine('=', 50);
}

string languageChecker(string languageChoice){
    if (languageChoice == "en") {
        return "en.txt";
    } else if (languageChoice == "es") {
        return "es.txt";
    }
    else if (languageChoice == "fr") {
        return "fr.txt";
    } else {
        cout << "Idioma no soportado. Usando inglés por defecto.\n";
        return "en.txt";
    }
}

// Base class for User
class User {
protected:
    char name[30];
    char mobile[15];
    char address[50];

public:
    virtual void accept(string langChoice) = 0; // Pure virtual function
    virtual void display() = 0; // Pure virtual function
};

// Class for Password Management
class PasswordManager {
private:
    char password[20];
    LanguageManager langManager;
public:
    void setPassword(int code, string language) {
        langManager.loadLanguage(language);
        if (code == 1234) {
            cout << langManager.getTranslation("PASSWORD_ENTER");
            cin.ignore();
            cin.getline(password, 20);
            fstream wr;
            wr.open("pass.txt", ios::out);
            wr.write((char*)this, sizeof(PasswordManager));
            wr.close();
        } else {
            cout << "\nCode Error";
        }
    }

    bool checkPassword(string language) {
        langManager.loadLanguage(language);
        char input[20];
        cout << langManager.getTranslation("PASSWORD");
        for (int i = 0; i < strlen(password); i++) {
            input[i] = getch();
            cout << "*";
        }
        input[strlen(password)] = '\0';
        return stricmp(input, password) == 0;
    }
};

// Class for Hotel Room
class HotelRoom : public User {
protected:
    int room_no;
    char checkInDate[15]; // New attribute for check-in date
    char checkOutDate[15];
    char Shanakti[15];
    LanguageManager LangManager;

public:
    char roomType[20];
    void accept(string langChoice) override {
    
    //langChoice = languageChecker(langChoice);
    LangManager.loadLanguage(langChoice);

    cin.ignore();
    cout << LangManager.getTranslation("ENTER_CheckIn_DATE") << endl; // Debug statement
    cin.getline(checkInDate, 15);
    cout << LangManager.getTranslation("ENTER_CheckOut_DATE") << endl; // Debug statement
    cin.getline(checkOutDate, 15);
    cout << LangManager.getTranslation("ENTER_FULL_NAME") << endl; // Debug statement
    cin.getline(name, 30);
    cout << LangManager.getTranslation("ENTER_MOBILE_NUMBER") << endl; // Debug statement
    cin >> mobile;
    cin.ignore();
    cout << LangManager.getTranslation("ENTER_SHANAKTI_CARD") << endl; // Debug statement
    cin.getline(Shanakti, 15);
    cout << LangManager.getTranslation("ENTER_ADDRESS") << endl; // Debug statement
    cin.getline(address, 50);
}


    void display() override {
        cout << "\nRoom number: " << room_no;
        cout << "\nName: " << name;
        cout << "\nMobile number: " << mobile;
        cout << "\nShanakti card number: " << Shanakti;
        cout << "\nAddress: " << address;
        cout << "\n----------------------------";
    }

    const char* getName() {
        return name;
    }
    // Getter for Shanakti card number
    const char* getShanakti() {
        return Shanakti;
    }
    // Getter for mobile number
    const char* getMobile() {
        return mobile;
    }
    // Getter for address
    const char* getAddress() {
        return address;
    }
    const char* getCheckInDate() {
        return checkInDate;
    }
    const char* getCheckOutDate() {
        return checkOutDate;
    }
    void setRoomNumber(int r) {
        room_no = r;
    }
    const char* getRoomType() {
        return roomType;
    }
    int getRoomNumber() {
        return room_no;
    }
};

void writeBookingToExcel(HotelRoom& room) {
    string command = "python write_to_excel.py " + to_string(room.getRoomNumber()) + " " +
                    room.getCheckInDate() + " " +
                    room.getCheckOutDate() + " " +
                    room.getName() + " " +
                    room.getMobile() + " " +
                    room.getShanakti() + " " +
                    room.getAddress();
    system(command.c_str()); // Call the Python script
}
   
// Class for Hotel Management
class HotelManagement {
private:
    HotelRoom room;
    PasswordManager passwordManager;
    LanguageManager langManager;

public:
   void bookRoom(string lang) {
    int r;
    langManager.loadLanguage(lang);
    string command = "python listAvailable_rooms.py";
    system(command.c_str());
    cout << langManager.getTranslation("ENTER_ROOM_NUMBER");
    cin >> r;
    if (checkRoomAvailability(r)) {

        room.setRoomNumber(r);
                // Get room type using Python
        string getRoomTypeCmd = "python get_room_type.py " + to_string(r);
        FILE* pipe = popen(getRoomTypeCmd.c_str(), "r");
        if (!pipe) {
            cerr << "Failed to get room type\n";
            return;
        }

        char buffer[128];
        string roomType = "";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            roomType += buffer;
        }
        pclose(pipe);

        // Strip newline
        roomType.erase(remove_if(roomType.begin(), roomType.end(), ::isspace), roomType.end());

        // Set the room type directly
        strcpy(room.roomType, roomType.c_str());

        room.accept(lang);
        writeBookingToExcel(room); 
        
        printHeader("Booking Successful");
        cout << langManager.getTranslation("BOOKING_SUCCESSFULLY")<< endl;
    } else {
        printHeader("Booking Failed");
        cout << langManager.getTranslation("BOOKING_FAILED") << endl;
    }
}



    void cancelBooking(string lang) {
    langManager.loadLanguage(lang);
    int r;
    cout << langManager.getTranslation("ENTER_ROOM_NUMBER");
    cin >> r;

    // Call the Python script to cancel the booking
    string command = "python cancelBooking.py " + to_string(r);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Failed to run command\n";
        return; // Handle error
    }

    char buffer[128];
    string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer; // Read the output from the command
    }
    pclose(pipe);

    // Check the result from the Python script
    if (result == "True\n") {
        cout << langManager.getTranslation("BOOKING_CANCELLED") << endl;
    } else {
        cout << langManager.getTranslation("ROOM_NOT_FOUND") << endl;
    }
}


   void viewAllRooms() {
    string command = "python view_room.py"; // Call the Python script to read from Excel
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Failed to run command\n";
        return; // Handle error
    }

    char buffer[128];
    string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer; // Read the output from the command
    }
    pclose(pipe);

    // Print the result (room summary) received from the Python script
    cout << result;
}




    void changePassword(string lang) {
        langManager.loadLanguage(lang);
        int code;
        cout << langManager.getTranslation("PASSWORD");
        cin >> code;
        passwordManager.setPassword(code, lang);
    }

    void viewRoomStatus(string language) {
        langManager.loadLanguage(language);
        if (passwordManager.checkPassword(language)) {
            int room_number;
        cout << langManager.getTranslation("ROOM_STATUS_FIND");
        cin >> room_number;
        // Call the Python script to get room details
        string command = "python view_room_status.py " + to_string(room_number);
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            cerr << "Failed to run command\n";
            return; // Handle error
        }
        char buffer[128];
        string result = "";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer; // Read the output from the command
        }
        pclose(pipe);
        // Print the result (room details) received from the Python script
        cout << result;
    }
}
    void processPayment(string lang) {
    //lang = languageChecker(lang);
    langManager.loadLanguage(lang);
    float amount;
    cout << langManager.getTranslation("ENTER_PAYMENT_AMOUNT");
    cin >> amount;
    cout << langManager.getTranslation("PROCESSING_PAYMENT") << "...\n";
    // Simulate payment processing
    cout << langManager.getTranslation("PAYMENT_SUCCESSFUL");
}


private:
      bool checkRoomAvailability(int r) {
    if (r <= 0) {
        cerr << "Invalid room number." << endl;
        return false; // Invalid room number
    }

    string command = "python read_rom_excel.py " + to_string(r);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Failed to run command\n";
        return false; // Assume unavailable if error
    }

    char buffer[128];
    string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    // ✅ Strip all whitespace and newlines from result
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());

    return result == "True";
}


   
   



};



int main() {
    LanguageManager langManager;
    HotelManagement hotel;
    string languageChoice;

    cout << "Seleccione el idioma (en/es/fr): ";
    cin >> languageChoice;

    //languageChoice = languageChecker(languageChoice);
    langManager.loadLanguage(languageChoice);

    int choice;
    while (true) {
        printHeader(langManager.getTranslation("WELCOME"));
        cout << "\n\t\t1. " << langManager.getTranslation("BOOK_ROOM");
        cout << "\n\t\t2. " << langManager.getTranslation("VIEW_ROOMS");
        cout << "\n\t\t3. " << langManager.getTranslation("CHANGE_PASSWORD");
        cout << "\n\t\t4. " << langManager.getTranslation("VIEW_ROOM_STATUS");
        cout << "\n\t\t5. " << langManager.getTranslation("CANCEL_BOOKING");
        cout << "\n\t\t6. " << langManager.getTranslation("PROCESS_PAYMENT");
        cout << "\n\t\t7. " << langManager.getTranslation("EXIT");
        cout << "\n" << langManager.getTranslation("SELECT_CHOICE") << " ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.bookRoom(languageChoice);
                break;
            case 2:
                hotel.viewAllRooms();
                break;
            case 3:
                hotel.changePassword(languageChoice);
                break;
            case 4:
                hotel.viewRoomStatus(languageChoice);
                break;
            case 5:
                hotel.cancelBooking(languageChoice); // Call cancel booking
                break;
            case 6:
                hotel.processPayment(languageChoice); // Call payment processing
                break;
            case 7:
                cout << "\n" << langManager.getTranslation("EXIT") << " !!!";
                return 0;
            default:
                cout << "\n" << langManager.getTranslation("INVALID_CHOICE");
        }
    }
}
