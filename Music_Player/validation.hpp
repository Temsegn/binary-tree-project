#include <iostream>
#include <string>

using namespace std;

class Validator {
public:
    bool isValidDate(const string& date) {
        // Check if the date string has the correct format (YYYY-MM-DD)
        if (date.length() != 10 || date[4] != '-' || date[7] != '-')
            return false;

        // Extract the year, month, and day parts from the string
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        // Perform additional validation based on specific rules
        if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
            return false;


        return true; // Date is valid
    }

    bool hasNoNumber(const string& str) {
        for (char c : str) {
            if (isdigit(c))
                return false;
        }

        return true; // String has no number characters
    }

    bool isValidRating(int rating) {
        return (rating >= 0 && rating <= 10);
    }
    bool isNumber(const std::string& str) {
    // Number validation logic implementation
    for (int i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}
};

