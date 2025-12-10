/*
Purpose: Test case file for StackProject.

Input: None
Output: None
*/

//---- Main menu test cases ----//
/*
Case 1: Any character that isn't a digit 0-9.
Result: Invalid choice error.

Case 2: 5
Result: Invalid choice error.

Case 3: 0
Result: Invalid choice error.

Case 4: 3
Result: Exits program.

Case 5: 2
Result: Displays program details.

Case 6: 1
Result: Prompts for mathematical expression.
*/

//---- Expression evaluation test cases ----//

// Edge cases
/*
0       = 0
0 + 0   = 0
0 * 100 = 0
100 * 0 = 0
(0)     = 0
(-0)    = 0
1 - 1   = 0
5 / 5   = 1

1000000             = 1000000
9999 + 1            = 10000
((((5))))           = 5
1 + 2 + 3 + 4 + 5   = 15
*/

// Basic operations
/*
5 + 3       = 8
10 - 4      = 6
6 * 7       = 42
20 / 4      = 5
100 / 3
*/

// Order of operations
/*
2 + 3 * 4           = 14
10 - 6 / 2          = 7
5 * 2 + 3 * 4       = 22
20 / 4 - 2 * 3      = -1
2 + 3 * 4 - 5 / 1   = 9
*/

// Basic parentheses
/*
(5 + 3) * 2         = 16
(10 - 4) / 2        = 3
(6 + 2) * (3 - 1)   = 16
20 / (2 + 2)        = 5
(8 - 3) * (4 + 1)   = 25
*/

// Nested parentheses
/*
((5 + 3) * 2)               = 16
(2 + (3 * 4))               = 14
((10 - 2) / (1 + 1))        = 4
(5 * (3 + (2 - 1)))         = 20
((8 + 2) * ((6 - 3) + 1))   = 40
(((2 + 3) * 4) - 5)         = 15
*/

// Negative numbers
/*
(-5) + 3        = -2
10 + (-4)       = 6
(-6) * 7        = -42
20 / (-4)       = -5
(-8) - (-3)     = -5
(-5) * (-2)     = 10
((-3) + 5) * 2  = 4
10 - (-5 + 3)   = 12
*/

// Implicit multiplication
/*
2(3 + 4)        = 14
5(2)            = 10
(3 + 1)(2)      = 8
3(4)(5)         = 60
2(3 + 4(5 - 2)) = 30
(2 + 3)(4 + 5)  = 45
10(5 - 3)       = 20
*/

// Spaces
/*
5+3     = 8
5 +3    = 8
5+ 3    = 8
5 + 3   = 8

1 0 + 2 0           = 30
1  2  3 + 4  5  6   = 579
( 5 + 3 ) * 2       = 16
(5+3)*(7-2)         = 40
  5   +   3         = 8
*/

// Complex cases
/*
2 * (3 + 4) - 5                 = 9
((10 + 5) / 3) * 2              = 10
5 + 3 * (2 - 8 / 4)             = 5
((-5) + 3) * (10 - 7)           = -6
2(3 + 4(5 - 2)) + 1             = 31
((5 + (-3)) * 4) / 2            = 4
100 / (2 * (3 + 2))             = 10
(-10) / ((-2) + (-3))           = 2
3(2 + 1) - 4(5 - 3)             = 1
((8 - 3) * 2 + 10) / (4 - 1)    = 6
*/

// Same precedence left-to-right
/*
10 - 5 - 2      = 3
20 / 4 / 5      = 1
100 / 10 * 2    = 20
8 * 2 / 4       = 4
15 - 3 + 2 - 4  = 10
*/

// Stress tests
/*
5(3(2(1)))                              = 30
1 + 2 * 3 - 4 / 2 + 5                   = 10
((1 + 2) * (3 + 4)) / ((5 - 2) + 1)     = 5
(((10 - 2) * 3) + ((8 / 2) - 1)) * 2    = 54
100 - 20 * 3 + 40 / 2 - 5               = 55
2 * (3 + (4 * (5 - (6 / 2))))           = 22
(-100) + 50 * 2 / (-5) + 30             = -90
*/
