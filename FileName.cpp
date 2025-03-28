//Automating the process of solving cryptarithmetic puzzles

#include <iostream>
using namespace std;

// Function to calculate the length of a null-terminated character array
int getLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Function to convert a character array number from any base to base 10
int ConvertToBase10(const char* number, int base) {
    int result = 0;
    int length = getLength(number);

    for (int i = 0; i < length; i++) {
        char digit = number[i];
        int val = (digit >= '0' && digit <= '9') ? digit - '0' : digit - 'A' + 10;
        if (val >= base) {
            return -1;
        }
        result = result * base + val;
    }
    return result;
}

// Function to convert a number from base 10 to another base as a null-terminated character array
void ConvertFromBase10(int number, int base, char* result) {
    char temp[101]; // Temporary array to store the result in reverse
    int index = 0;

    if (number == 0) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }

    while (number > 0) {
        int remainder = number % base;
        temp[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        number /= base;
    }

    // Reverse the result
    int resultIndex = 0;
    for (int i = index - 1; i >= 0; i--) {
        result[resultIndex++] = temp[i];
    }
    result[resultIndex] = '\0';
}

// Function to process a term or total based on the solution mapping
int ProcessTerm(const char* term, const int map[], int base, char* result) {
    char temp[101];
    int index = 0;

    for (int i = 0; term[i] != '\0'; i++) {
        char c = term[i];
        if (c >= 'A' && c <= 'Z') {
            int mappedVal = map[c - 'A'];
            if (mappedVal >= base) {
               return -1 ;
            }
            temp[index++] = mappedVal + '0';
        }
        else {
            temp[index++] = c;
        }
    }
    temp[index] = '\0';

    // Remove leading zeros
    int start = 0;
    while (temp[start] == '0' && temp[start + 1] != '\0') {
        start++;
    }

    // Copy result to the output
    index = 0;
    while (temp[start] != '\0') {
        result[index++] = temp[start++];
    }
    result[index] = '\0';
    return 0;
}

int main() {
    char solution[52], total[101], term[101], processedTerm[101], processedTotal[101];
    int map[26] = { 0 }, base, termCount,val = 0;
    bool errFound = false;
    // Input the solution mapping
    cout << "Input the solution mapping: ";
    cin >> solution;

    // Parse the solution mapping
    int solutionLength = getLength(solution);
    for (int i = 0; i < solutionLength; i += 2) {
        char letter = solution[i];
        int digit = solution[i + 1] - '0';

        // Ensure valid mapping
        if (digit < 0 || digit > 9 || letter < 'A' || letter > 'Z') {
            errFound = true;
        }

        map[letter - 'A'] = digit;
    }

    // Input the base
    cout << "Input the base: ";
    cin >> base;

    if (base < 2 || base > 36) {
        cout << "Error: Invalid base";
        return 0;
    }

    // Input the total
    cout << "Input the total: ";
    cin >> total;

    // Input the number of terms
    cout << "Input the number of terms: ";
    cin >> termCount;

    if (termCount <= 0) {
        cout << "Error: Invalid number of terms";
        return 0;
    }

    int calculatedSum = 0;
    cout << "Input the terms, one on a line:\n";
    for (int i = 0; i < termCount; i++) {
        cin >> term;

        val = ProcessTerm(term, map, base, processedTerm);
        if (val == -1)errFound = true;
        val = ConvertToBase10(processedTerm, base);
        if (val == -1) {
            errFound = true;
        }
        else calculatedSum += val;
    }

    val = ProcessTerm(total, map, base, processedTotal);
    if (val == -1)errFound = true;
    if (errFound) {
        cout << "Error";
        return 0;
    }
    int totalValue = ConvertToBase10(processedTotal, base);

    // Check if the calculated sum matches the given total
    if (calculatedSum == totalValue) {
        cout << "Correct";
    }
    else {
        cout << "Wrong";
    }

    return 0;
}