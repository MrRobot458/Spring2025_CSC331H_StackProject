/*
* Purpose:
*     This is a menu-driven program that prompts a user for a mathematical expression, evaluates it using two
*     linked-list-implemented stacks, and displays the result. One stack is for operands, the other for operators.
* 
* Input:
*     1. The user's choice from the menu options.
*     2. A mathematical expression.
* 
* Output:
*     1. The result of the mathematical expression provided by the user.
*     2. Menu of options and the results of the operation selected by the user.
*/

#include "LinkedStack.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

//---- Helper function prototypes ----//
void compute(LinkedStack<double>&, LinkedStack<char>&, string&, bool&);  // Applies a mathematical operator to two operands
void displayAbout();                                                     // Displays the program's details
void displayMenu(int&);                                                  // Displays the menu and gets the user's choice
double evaluateExpr(LinkedStack<double>&, LinkedStack<char>&, bool&);    // Evaluates a given mathematical expression using two stacks
int getPrecedence(char);                                                 // Returns a given operator's precedence
bool isOperator(char);                                                   // Returns true if a given character is an arithmetic operator, false otherwise

//---- Helper function definitions ----//

// Applies a mathematical operator to two operands
void compute(LinkedStack<double>& vals, LinkedStack<char>& ops, string& errorMsg, bool& errorFlag) {
    double operand1 = 0.0;  // 1st operand from values stack 
    double operand2 = 0.0;  // 2nd operand from values stack 
    char operation = '\0';  // Operator from operators stack

    // Get operator from operators stack
    ops.getTop(operation);
    ops.pop();

    // Get operands from values stack
    vals.getTop(operand2);
    vals.pop();
    vals.getTop(operand1);
    vals.pop();

    // Apply operator to operands in correct order
    if (operation == '*') {
        operand1 *= operand2;
    }
    else if (operation == '/') {
        if (operand2 != 0.0) {
            operand1 /= operand2;
        }
        else {
            errorFlag = true;
            errorMsg = "Division by zero.";
        }
    }
    else if (operation == '+') {
        operand1 += operand2;
    }
    else if (operation == '-') {
        operand1 -= operand2;
    }
    else {
        errorFlag = true;
        errorMsg = "Something went wrong. ";
        errorMsg += ((operation == '\0') ? "Did not fetch item from operator stack." : "Fetched invalid item from operator stack.");
    }
    // Push result onto values stack
    vals.push(operand1);
    return;
}

// Displays the program's details
void displayAbout() {
    cout << "\nThis program takes as input a mathematical expression and displays the result with 2 decimal places.\n"
        << "The expression is evaluated using two linked-list-implemented stacks. One stack for operands, the other for operators.\n"
        << "The expression must be valid. Any error will bring you back to the main menu.\n"
        << "A valid mathematical expression has the following:\n"
        << "    1. Valid operators: ( ) * / + -\n"
        << "    2. Only integers and valid digits (0-9).\n"
        << "    3. Negative numbers are allowed and must be in parentheses when necessary.\n"
        << "    4. Implicit multiplication (multiplication with parentheses) is allowed.\n"
        << "    5. Blank spaces will be ignored.\n"
        << "    6. Digits with blank spaces in between them will be treated as one whole number.\n"
        << "    7. Excluding characters already mentioned, no invalid characters.\n"
        << "    8. No invalid parentheses and/or parentheses sequencing.\n"
        << "    9. No extra or invalid sequencing of operators.\n";
    return;
}

// Displays the menu and gets the user's choice
void displayMenu(int& choice) {
    cout << "\n****************** MENU ******************\n"
        << "  1. Evaluate a mathematical expression.\n"
        << "  2. About.\n"
        << "  3. Quit the program.\n"
        << "******************************************\n";

    cout << "\nPick a number. Enter your choice here: ";
    cin >> choice;

    // Clear the input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}

// Evaluates a given mathematical expression using two stacks
double evaluateExpr(LinkedStack<double>& values, LinkedStack<char>& operators, bool& errorFlag) {
    string digits = "";         // Stores digits in multi-digit integers
    string errorMsg = "";       // Stores the error message
    double result = 0.0;        // Result of the expression
    char current = '\0';        // Current character in the expression
    char temp = '\0';           // Temporary variable used for comparisons 
    bool negationFlag = false;  // Boolean flag for when negation is required

    // Get and validate first character
    cin.get(current);

    if (current == '-') {
        negationFlag = true;
    }
    else if (current == '\n') {
        errorFlag = true;
        errorMsg = "No input given.";
    }
    else if (current == ')') {
        errorFlag = true;
        errorMsg = "Invalid parentheses found.";
    }
    else if (isOperator(current)) {
        errorFlag = true;
        errorMsg = "Invalid operator sequencing.";
    }
    // Put character back to begin evaluation
    cin.putback(current);

    // Process the expression
    while (cin.get(current) && (current != '\n') && (!errorFlag)) {
        if (isspace(current)) {
            continue;
        }
        else if (isdigit(current)) {
            digits += current;

            // Get any remaining digits and push number onto values stack
            while (cin.get(current) && (isdigit(current) || current == ' ')) {
                if (isdigit(current)) digits += current;
            }
            cin.putback(current);
            values.push(stod(digits));

            // Reset for next number
            digits = "";

            if (cin.peek() == '(') cin.putback('*');
        }
        else if (current == '(') {
            // Push onto operators stack and remove spaces
            operators.push(current);

            while (cin.peek() == ' ') cin.ignore();

            // Check for negation and invalid parentheses
            temp = char(cin.peek());

            if (temp == '-') {
                negationFlag = true;
            }
            else if (temp == ')') {
                errorFlag = true;
                errorMsg = "Invalid parentheses found.";
            }
        }
        else if (current == ')') {
            if (!operators.isEmpty()) {
                // Compute until left parentheses is found
                operators.getTop(temp);

                while (temp != '(') {
                    compute(values, operators, errorMsg, errorFlag);

                    if (!operators.isEmpty()) operators.getTop(temp);
                    else break;
                }
                // Pop the left parentheses
                if ((!operators.isEmpty()) && (temp == '(')) {
                    operators.pop();
                }
                else {
                    errorFlag = true;
                    errorMsg = "Invalid parentheses found.";
                }
            }
            else {
                errorFlag = true;
                errorMsg = "Invalid parentheses found.";
            }
            // Remove spaces and check for implicit multiplication
            while (cin.peek() == ' ') cin.ignore();
            temp = char(cin.peek());

            if ((temp == '(') || isdigit(temp)) cin.putback('*');
        }
        else if (isOperator(current)) {
            // Compute until operators stack is empty or next operator has greater or equal precedence
            operators.getTop(temp);

            while ((!errorFlag) && (!operators.isEmpty()) && (getPrecedence(temp) >= getPrecedence(current))) {
                compute(values, operators, errorMsg, errorFlag);
                operators.getTop(temp);
            }
            // Handle negation
            if ((current == '-') && negationFlag) {
                // Check for 0
                if (cin.peek() != '0') values.push(-1.0);
                else values.push(0.0);

                current = '*';
                negationFlag = false;
            }
            // Push onto operators stack
            operators.push(current);

            // Remove spaces and check for invalid operator sequencing
            while (cin.peek() == ' ') cin.ignore();
            temp = char(cin.peek());

            if (isOperator(temp) || (temp == ')')) {
                errorFlag = true;
                errorMsg = "Invalid operator sequencing.";
            }
        }
        else {
            errorFlag = true;
            errorMsg = "Invalid character found.";
        }
    }
    // Finish rest of the expression
    if (!errorFlag) {
        while (!operators.isEmpty()) compute(values, operators, errorMsg, errorFlag);

        // Get and pop final result from values stack
        if (!errorFlag) {
            values.getTop(result);
            values.pop();
        }
    }
    // Check for missed numbers or operators
    if (!values.isEmpty()) {
        errorFlag = true;
        errorMsg = "Something went wrong. Missed number(s) left in operands stack.";
    }
    if (!operators.isEmpty()) {
        errorFlag = true;
        operators.getTop(temp);

        errorMsg = ((temp == ')') ? "Invalid parentheses found." : "Something went wrong. Missed operator(s) left in operators stack.");
    }
    // If there's an error, display error message
    if (errorFlag) cout << "\n\nError: " << errorMsg << "\n";
    return result;
}

// Returns a given operator's precedence
int getPrecedence(char op) {
    int precedence = 0;  // Precedence of given operator

    if ((op == '*') || (op == '/')) precedence = 2;
    else if ((op == '+') || (op == '-')) precedence = 1;
    return precedence;
}

// Returns true if a given character is an arithmetic operator, false otherwise
bool isOperator(char op) {
    bool check = false;  // Boolean flag for whether given character is an operator or not

    if ((op == '*') || (op == '/') || (op == '+') || (op == '-')) check = true;
    return check;
}

//---- Main program ----//
int main() {
    LinkedStack<double> valueStack;   // Stack for expression operands
    LinkedStack<char> operatorStack;  // Stack for expression operators
    double result = 0.0;              // Stores result of expression 
    int input = 0;                    // Stores user input
    bool hasError = false;            // Boolean flag for when expression has an error

    // Set output stream and display welcome message
    cout << fixed << setprecision(2);
    cout << "Hi!";
    displayAbout();

    // Get user's first choice
    displayMenu(input);

    // Do the requested operation until user quits
    while (input != 3) {
        if (input == 1) {
            // Reset the stacks
            while (!valueStack.isEmpty()) valueStack.pop();
            while (!operatorStack.isEmpty()) operatorStack.pop();

            // Reset error flag and result
            result = 0.0;
            hasError = false;

            // Evaluate expression and display result
            cout << "\nEnter mathematical expression below.\n\n" << "---> ";
            result = evaluateExpr(valueStack, operatorStack, hasError);

            if (!hasError) cout << "\n\nResult: " << result << "\n";

            // Clear the input buffer
            cin.clear();

            cout << "\nPress 'Enter' to continue...\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (input == 2) displayAbout();
        else cout << "\nError: Invalid choice. Choose a number from the menu below and try again.\n";

        // Get user's next choice
        displayMenu(input);
    }
    cout << "\nExiting program. Bye!\n";
    return 0;
}
