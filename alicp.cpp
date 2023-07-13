#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
};


void signup() {
    User newUser;

    cout << "Enter username: ";
    cin >> newUser.username;

    cout << "Enter password: ";
    cin >> newUser.password;

    ofstream file("users.txt", ios::app);
    file << newUser.username << " " << newUser.password << endl;
    file.close();

    cout << "Account created successfully!" << endl;
}


bool login(User& loginUser) {
    cout << "Enter username: ";
    cin >> loginUser.username;

    cout << "Enter password: ";
    cin >> loginUser.password;

    ifstream file("users.txt");
    string username, password;

    while (file >> username >> password) {
        if (loginUser.username == username && loginUser.password == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void billing(const User& loginUser){
    const int numMedicines = 10;
    int medi;
    double total_bill = 0, discount = 0;
    int quantities[numMedicines] = {0}; 

    cout << "Welcome to the Medical Store" << endl;
    cout << "Medicines: " << endl;
    cout << "1. Panadol - Price: 300 Rs" << endl;
    cout << "2. Aspirin - Price: 200 Rs" << endl;
    cout << "3. Paracetamol - Price: 150 Rs" << endl;
    cout << "4. Rigix - Price: 120 Rs" << endl;
    cout << "5. Beflam - Price: 100 Rs" << endl;
    cout << "6. Brexin - Price: 250 Rs" << endl;
    cout << "7. Myteka - Price: 400 Rs" << endl;
    cout << "8. Gravinate - Price: 150 Rs" << endl;
    cout << "9. Mefnac - Price: 150 Rs" << endl;
    cout << "10. Proxen - Price: 350 Rs" << endl;

    cout << "Enter the Medicine Number you Need: ";
    cin >> medi;

    double prices[] = {300, 200, 150, 120, 100, 250, 400, 150, 150, 350};
    string medicines[] = {"Panadol", "Aspirin", "Paracetamol", "Rigix", "Beflam",
                          "Brexin", "Myteka", "Gravinate", "Mefnac", "Proxen"};

    if (medi >= 1 && medi <= numMedicines){
        cout << "How many do you need? ";
        cin >> quantities[medi - 1]; 
        total_bill += prices[medi - 1] * quantities[medi - 1];

        char choice;
        cout << "Do you need other medicines? (y/n): ";
        cin >> choice;

        while (choice == 'y' || choice == 'Y'){
            cout << "Enter the Medicine Number you Need: ";
            cin >> medi;

            if (medi >= 1 && medi <= numMedicines){
                cout << "How many do you need? ";
                cin >> quantities[medi - 1]; 
                total_bill += prices[medi - 1] * quantities[medi - 1];
            } 
			
			else {
                cout << "Invalid medicine selection." << endl;
            }

            cout << "Do you need other medicines? (y/n): ";
            cin >> choice;
        }

        if (total_bill >= 2000) {
            discount = total_bill - (total_bill * 0.25);
            cout << "Your Bill is over 2000 Rs." << endl;
            cout << "You are eligible for a discount." << endl;
            cout << "Now your total bill is " << discount << " Rs." << endl;
        } else {
            cout << "Your Total Bill is " << total_bill << " Rs." << endl;
        }

        ofstream outputFile("billing.txt", ios::app);
        if (outputFile.is_open()) {
            outputFile << "Username: " << loginUser.username << endl;
            outputFile << "Total Bill: " << total_bill << " Rs." << endl;
            if (discount > 0) {
                outputFile << "Discounted Bill: " << discount << " Rs." << endl;
            }
            outputFile << "Medicines Ordered:" << endl;
            for (int i = 0; i < numMedicines; i++) {
                if (quantities[i] > 0) {
                    outputFile << medicines[i] << " - Quantity: " << quantities[i] << endl;
                }
            }
            outputFile << "-------------------------" << endl;
            outputFile.close();
        } else {
            cout << "Failed to open the file." << endl;
        }
    } else {
        cout << "Invalid medicine selection." << endl;
    }

    cout << "Have a Nice Day!" << endl;
}

void recordSummary(){
    ifstream file("billing.txt");
    string line;

    if (file.is_open()){
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    } else {
        cout << "Failed to open the file." << endl;
    }
}

void searchUserOrder(){
    string username;
    cout << "Enter username to search: ";
    cin >> username;

    ifstream file("billing.txt");
    string line;
    bool userFound = false;

    if (file.is_open()) {
    	
        while (getline(file, line)) {
        	
            if (line.find("Username: " + username) != string::npos) {
                userFound = true;
                cout << "Orders for User: " << username << endl;
                cout << line << endl; 
                while (getline(file, line) && line != "-------------------------"){
                    cout << line << endl;
                }

                break;
            }
            
        }

        file.close();

        if (!userFound){
            cout << "User not found or has no orders." << endl;
        }
    } 
	
	else {
        cout << "Failed to open the file." << endl;
    }
}

int main(){
	
    int choice;
    string password;

    User loginUser;
    
    do {
    	cout << "                                                  Assalamualaikum" << endl;
        cout << "            ============================Welcome To The Medical Store============================" << endl << endl << endl;
        
        cout << "1. Sign up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Search User Orders" << endl;
        cout << "4. Record Summary" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signup();
                 system("cls");
                break;
            case 2:
                if (login(loginUser)) {
                    cout << "Login successful!" << endl;
                    system("cls");
                    billing(loginUser);

                } 
				
				else {
                    cout << "Invalid username or password!" << endl;
                }
                break;
                
            case 3:
                searchUserOrder();
                break;
                 system("cls");
                 
            case 4:
                recordSummary();
                break;
                 system("cls");
                 
            case 5:
                cout << "Exiting From program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
                
        }
    } while (choice != 5);

    return 0;
}
