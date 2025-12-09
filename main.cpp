/*
Purpose:
    This is a menu-driven program that prompts a user for a valid mathematical expression, evaluates it using two
    linked-list-implemented stacks, and displays the result.

Input:
    1. The user's choice from the program's menu options.
    2. A valid mathematical expression.

Output:
    1. The evaluated result of the mathematical expression provided by the user.
    2. Menu of options and the results of the operation selected by the user.
*/

#include "LinkedStack.h"
#include <iostream>
#include <limits>

using namespace std;

//---- Helper function prototypes ----//
void compute(LinkedStack<double>&, LinkedStack<char>&, string&, bool&);  // Applies a mathematical operator to two operands
void displayAbout();                                                     // Displays the program's details
void displayMenu(int&);                                                  // Displays the menu and gets the user's choice
double evaluateExpr(LinkedStack<double>&, LinkedStack<char>&, bool&);    // Evaluates a given mathematical expression using two stacks
int getPrecedence(char);                                                 // Returns a given operator's precedence
void handleNegation();                                                   // Handles necessary negation when the current character is a minus sign
bool isOperator(char);                                                   // Returns true if a given character is a mathematical operator, false otherwise
void trimSpaces();                                                       // Reads and discards continuous blank spaces


//---- Helper function definitions ----//

// Applies a mathematical operator to two operands
void compute(LinkedStack<double>& vals, LinkedStack<char>& ops, string& errorMsg, bool& errorFlag) {
    double operand1 = 0.0;  // Stores the 1st operand
    double operand2 = 0.0;  // Stores the 2nd operand
    char operation = '\0';  // Stores the next operator from the operator stack

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
    // Push the result
    vals.push(operand1);
    return;
}

// Displays the program's details
void displayAbout() {
    cout << "\nThis program takes as input a mathematical expression and displays the result to 3 decimal places.\n"
        << "The expression is evaluated using two linked-list-implemented stacks. One stack for operands, the other for operators.\n"
        << "The expression must be valid. Any error will bring you back to the main menu.\n"
        << "A valid mathematical expression has the following:\n"
        << "    1. Valid operators: ( ) * / + -\n"
        << "    2. Only interger numbers and valid digits (0-9).\n"
        << "    3. Negative numbers are allowed and must be in parentheses when necessary.\n"
        << "    4. Multiplication by parentheses is allowed.\n"
        << "    5. Blank spaces will be skipped over and ignored.\n"
        << "    6. Excluding characters already mentioned, no invalid characters.\n"
        << "    7. No invalid parentheses and/or parentheses sequencing.\n"
        << "    8. No extra or invalid sequencing of operators.\n";
    return;
}

// Displays the menu and gets the user's choice
void displayMenu(int& choice) {
    cout << "\n***************** MENU *****************\n"
        << "1. Evaluate a mathematical expression.\n"
        << "2. About.\n"
        << "3. Quit the program.\n"
        << "****************************************\n";

    cout << "\nPick a number. Enter your choice here: ";
    cin >> choice;

    // Clear the input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}

// Evaluates a given mathematical expression using two stacks
double evaluateExpr(LinkedStack<double>& values, LinkedStack<char>& operators, bool& errorFlag) {
    string digits = "";         // Stores the digits in multi-digit integers
    string errorMsg = "";       // Stores the relevant error message
    double result = 0.0;        // Stores the result of the expression
    char current = '\0';        // Stores the current character in the expression
    char temp = '\0';           // Used when checking for missed operators
    bool negationFlag = false;  // Boolean flag for when negation is required

    // Boolean flags for errors
    // bool divisionByZero = false;      // Division by zero
    // bool invalidCharacters = false;   // Invalid characters
    // bool invalidParentheses = false;  // Invalid parentheses
    // bool invalidOperator = false;     // Invalid operator(s)
    // bool missedNumber = false;        // Missed numbers
    // bool missedOperator = false;      // Missed operators

    // Get and validate first character
    cin >> current;

    if (current == '-') {
        negationFlag = true;

        // Put character back to begin evaluation
        cin.putback(current);
    }
    else {
        if (current == ')') {
            errorFlag = true;
            errorMsg = "Invalid parentheses found.";
        }
        if (isOperator(current)) {
            errorFlag = true;
            errorMsg = "Invalid operator found.";
        }
    }
    // Process the rest of the expression
    /*
    3. While there are still characters to read in the expression (using cin):
        1. Get next character.
        2. If new character is:
            1. A digit:
                1. Add the character to the digits string.
                2. While next character is a digit (using cin):
                    1. Get next character.
                    2. Append new character to the digits string.
                3. Put the current character back onto the front of the input stream.
                4. Convert the digits string to type double.
                5. Push the new value onto values stack.
                6. While next character is a blank space: Ignore and discard.
                7. If next character is a left parentheses: Add '*' to the front of the input stream.
            2. A left parentheses '(':
                1. Push it onto operators stack.
                2. While next character is a blank space: Ignore and discard.
                3. If next character is a minus sign: Set negation flag to true.
                4. If next character is a right parentheses: Throw error for invalid parentheses.
            3. A right parentheses ')':
                1. While top of operators stack is not a left parentheses:
                    1. compute(ops, vals);
                2. Pop left parentheses from operators stack.
                3. While next character is a blank space: Ignore and discard.
                4. If next character is a left parentheses or a digit: Add '*' to the front of the input stream.
            4. An operator:
                1. While operators stack not empty and top of operators stack has >= precedence:
                    1. compute(ops, vals);
                2. If character is a minus sign and negation flag is set to true:
                    1. Push -1.0 onto values stack.
                    2. Change character to a multiplication sign.
                    3. Set negation flag to false.
                3. Push character onto operators stack.
                4. While next character is a blank space: Ignore and discard.
                5. If next character is an operator (+, -, *, /) or right parentheses: Throw error for invalid operator sequencing.
            5. Anything else: Throw error for invalid character.
    */
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
    if (errorFlag) {
        cout << "\n\nError: " << errorMsg << "\n";
    }
    return result;
}

// Returns a given operator's precedence
int getPrecedence(char);

// Handles necessary negation when the current character is a minus sign
void handleNegation();

// Returns true if a given character is an arithmetic operator, false otherwise
bool isOperator(char);

// Reads and discards continuous blank spaces
void trimSpaces();

//---- Main program ----//
int main() {
    LinkedStack<double> valueStack;   // Stores the operands of a mathematical expression
    LinkedStack<char> operatorStack;  // Stores the operators of a mathematical expression 
    double result = 0.0;              // Stores the result of a mathematical expression 
    int input = 0;                    // Stores the user's input
    bool hasError = false;            // Boolean flag for when the expression has an error

    cout << "Hi!";
    displayAbout();

    // Get user's first choice
    displayMenu(input);

    // Do the requested operation until user quits
    while (input != 3) {
        if (input == 1) {
            // Empty the stacks
            while (!valueStack.isEmpty()) valueStack.pop();
            while (!operatorStack.isEmpty()) operatorStack.pop();
            
            cout << "\nEnter mathematical expression below.\n\n" << "---> ";

            // Evaluate mathematical expression and display result
            result = evaluateExpr(valueStack, operatorStack, hasError);

            if (!hasError) cout << "\n\nResult: " << result << "\n";

            // Reset
            result = 0.0;

            // Clear the input buffer
            cin.clear();
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
