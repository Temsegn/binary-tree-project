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
    if (year < 1890 || year > 2024 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Additional check for valid days based on the month and year
    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int daysInMonth = 31;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        daysInMonth = 30;
    else if (month == 2) {
        if (leapYear)
            daysInMonth = 29;
        else
            daysInMonth = 28;
    }

    // Perform alternative representation check for single-digit months and days
    if (date[5] == '0')
        month = stoi(date.substr(6, 1));
    if (date[8] == '0')
        day = stoi(date.substr(9, 1));

    if (day > daysInMonth)
        return false;

    return true; // Date is valid
}
  bool hasNoNumber(const string& str) {
    for (char c : str) {
        if (isdigit(c) || !isalpha(c))
            return false;
    }
    

    return true; // String has no number or non-alphabetic characters
}
    bool isValidRating(int rating) {
        return (rating >= 0 && rating <= 10);
    }
    bool isNumber(const string& str) {
    // Number validation logic implementation
    for (int i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}
};

