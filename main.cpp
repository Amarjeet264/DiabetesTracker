#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>  // For numeric limits

using namespace std;

// Function to get a valid integer input with a prompt
int getValidIntInput(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
        } else if (value <= 0) {
            cout << "Value must be greater than 0. Please try again.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input
            return value;
        }
    }
}

// Function to get a valid double input with a prompt
double getValidDoubleInput(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number.\n";
        } else if (value <= 0) {
            cout << "Value must be greater than 0. Please try again.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input
            return value;
        }
    }
}

// Function to get a valid character input with a prompt, ensuring it's one of the allowed characters
char getValidCharInput(const string &prompt, const string &validChars) {
    char value;
    while (true) {
        cout << prompt;
        cin >> value;
        value = toupper(value); // Convert to uppercase for consistency
        if (validChars.find(value) != string::npos) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input
            return value;
        } else {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter one of the following: " << validChars << "\n";
        }
    }
}

// Function to check if a character is within a valid options list
bool checkInput(char ch, const vector<char> &validOptions) {
    return find(validOptions.begin(), validOptions.end(), ch) != validOptions.end();
}

// Function to get a valid character input based on provided valid options
char getValidInput(char ch, const vector<char> &validOptions) {
    while (!checkInput(ch, validOptions)) {
        cout << "Invalid input. Please re-enter: ";
        cin >> ch;
        ch = toupper(ch);
    }
    return ch;
}

// Diabetes class containing all the required functionalities
class Diabetes {
private:
    int age;
    float weight, height;
    char symptoms[10];

public:
    void getInput() {
        age = getValidIntInput("Enter your age: ");
        weight = getValidDoubleInput("Enter your weight (in kg): ");
        height = getValidDoubleInput("Enter your height (in m): ");
    }

    void getSymptoms(int level) {
        vector<string> questions;
        vector<vector<char>> validOptions;

        if (level == 1) {
            questions = {
                "Appetite (H/L/N): ",
                "Frequency of Thirst (H/L/N): ",
                "Frequency of Urination (H/L/N): ",
                "Vision (I/N): ",
                "Urine Sugar (P/A): ",
                "Ketonuria (P/A): ",
                "Fasting Blood Sugar (H/L/N): ",
                "R B S (H/L/N): ",
                "Family History of Diabetes (P/A): ",
                "OGTT (D/N): "
            };
            validOptions = {
                {'H', 'L', 'N'}, {'H', 'L', 'N'}, {'H', 'L', 'N'}, {'I', 'N'},
                {'P', 'A'}, {'P', 'A'}, {'H', 'L', 'N'}, {'H', 'L', 'N'},
                {'P', 'A'}, {'D', 'N'}
            };
        } else if (level == 2) {
            questions = {
                "Pancreatitis (P/A): ", "Carcinoma (P/A): ", "Cirrhosis (P/A): ",
                "HCTS (H/L/N): ", "Hepatitis (P/A): ", "Hormonal Disorder (P/A): ",
                "Pancreatectomy (P/A): "
            };
            validOptions = {
                {'P', 'A'}, {'P', 'A'}, {'P', 'A'}, {'H', 'L', 'N'},
                {'P', 'A'}, {'P', 'A'}, {'P', 'A'}
            };
        } else if (level == 3) {
            questions = {
                "Age Group (Y/M/E): ", "BMI Category (N/A/B/O): ",
                "Duration of Symptoms (W/M/Y): ", "Ketonuria (P/A): ", "Auto Antibodies (P/A): "
            };
            validOptions = {
                {'Y', 'M', 'E'}, {'N', 'A', 'B', 'O'}, {'W', 'M', 'Y'}, {'P', 'A'}, {'P', 'A'}
            };
            symptoms[0] = getAgeGroup();
            symptoms[1] = getBMICategory();
            cout << questions[0] << symptoms[0] << endl;
            cout << questions[1] << symptoms[1] << endl;
            questions.erase(questions.begin(), questions.begin() + 2);
            validOptions.erase(validOptions.begin(), validOptions.begin() + 2);
        }

        for (int i = 0; i < questions.size(); ++i) {
            cout << questions[i];
            char input;
            cin >> input;
            input = toupper(input);
            symptoms[i] = getValidInput(input, validOptions[i]);
        }
    }

    char getAgeGroup() {
        if (age < 35) return 'Y';
        else if (age < 60) return 'M';
        else return 'E';
    }

    char getBMICategory() {
        float bmi = weight / (height * height);
        if (bmi < 19) return 'B';
        else if (bmi < 25) return 'N';
        else if (bmi < 30) return 'A';
        else return 'O';
    }

    int analyzeSymptoms(int level) {
        if (level == 1) {
            int count = 0;
            for (int i = 0; i < 10; i++) {
                if (symptoms[i] == 'H' || symptoms[i] == 'P' || symptoms[i] == 'D' || symptoms[i] == 'I') {
                    count++;
                }
            }
            if (symptoms[9] == 'D' || (symptoms[5] == 'P' && symptoms[6] == 'H' && symptoms[7] == 'H') || count > 5) {
                return -1;
            }
        } else if (level == 2) {
            for (int i = 0; i < 7; i++) {
                if (symptoms[i] == 'P' || symptoms[i] == 'H') {
                    return -1;
                }
            }
        } else if (level == 3) {
            if ((symptoms[0] == 'Y' && symptoms[1] == 'N' && symptoms[2] == 'W' && symptoms[3] == 'P' && symptoms[4] == 'P') ||
                (symptoms[0] == 'Y' && symptoms[1] == 'B' && symptoms[2] == 'W' && symptoms[3] == 'P' && symptoms[4] == 'P') ||
                (symptoms[0] == 'Y' && symptoms[1] == 'N' && symptoms[2] == 'M' && symptoms[3] == 'P' && symptoms[4] == 'P') ||
                (symptoms[0] == 'Y' && symptoms[1] == 'N' && symptoms[2] == 'Y' && symptoms[3] == 'P' && symptoms[4] == 'P')) {
                return 0;
            } else {
                return -1;
            }
        }
        return 0;
    }

    void displayMessage(int result, int level) {
        if (result == 0) {
            if (level == 1) {
                cout << "The person is not diabetic." << endl;
            } else if (level == 2) {
                cout << "It is primary diabetes." << endl;
            } else if (level == 3) {
                cout << "It is insulin-dependent diabetes." << endl;
            }
        } else {
            if (level == 1) {
                cout << "The person is diabetic. Proceed to the next level? (Y/N): ";
            } else if (level == 2) {
                cout << "It is secondary diabetes." << endl;
            } else if (level == 3) {
                cout << "It is non-insulin-dependent diabetes." << endl;
            }
        }

        if (result != 0 || level == 1) {
            char proceed;
            cin >> proceed;
            if (toupper(proceed) == 'N') {
                cout << "Exiting program." << endl;
                exit(0);
            }
        }
    }
};

int main() {
    Diabetes diabetesTest;

    diabetesTest.getInput();

    for (int level = 1; level <= 3; level++) {
        diabetesTest.getSymptoms(level);
        int result = diabetesTest.analyzeSymptoms(level);
        diabetesTest.displayMessage(result, level);
        if (result == 0 && level != 3) break;
    }

    return 0;
}
