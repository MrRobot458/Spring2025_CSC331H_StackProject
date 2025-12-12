/*
* Purpose:
*     Test case file for Stack project.
* 
*     PASS = successful evaluation of expression
*     FAIL = failed evaluation of expression
* 
* Input: None.
* Output: None.
*/

//---- Main menu test cases ----//
/*
Case 1: Any character that isn't a digit 0-9.
Result: Invalid choice error. PASS

Case 2: 5
Result: Invalid choice error. PASS

Case 3: 0
Result: Invalid choice error. PASS

Case 4: 3
Result: Exits program. PASS

Case 5: 2
Result: Displays program details. PASS

Case 6: 1
Result: Prompts for mathematical expression. PASS
*/

//---- Expression evaluation test cases ----//

// Edge cases
/*
0       = 0  PASS
0 + 0   = 0  PASS
0 * 100 = 0  PASS
100 * 0 = 0  PASS
(0)     = 0  PASS
(-0)    = 0  PASS
1 - 1   = 0  PASS
5 / 5   = 1  PASS

1000000           = 1000000  PASS
9999 + 1          = 10000    PASS
((((5))))         = 5        PASS
1 + 2 + 3 + 4 + 5 = 15       PASS
*/

// Basic operations
/*
5 + 3   = 8      PASS
10 - 4  = 6      PASS
6 * 7   = 42     PASS
20 / 4  = 5      PASS
100 / 3 = 33.33  PASS
*/

// Order of operations
/*
2 + 3 * 4         = 14  PASS
10 - 6 / 2        = 7   PASS
5 * 2 + 3 * 4     = 22  PASS
20 / 4 - 2 * 3    = -1  PASS
2 + 3 * 4 - 5 / 1 = 9   PASS
*/

// Basic parentheses
/*
(5 + 3) * 2       = 16  PASS
(10 - 4) / 2      = 3   PASS
(6 + 2) * (3 - 1) = 16  PASS
20 / (2 + 2)      = 5   PASS
(8 - 3) * (4 + 1) = 25  PASS
*/

// Nested parentheses
/*
((5 + 3) * 2)             = 16  PASS
(2 + (3 * 4))             = 14  PASS
((10 - 2) / (1 + 1))      = 4   PASS
(5 * (3 + (2 - 1)))       = 20  PASS
((8 + 2) * ((6 - 3) + 1)) = 40  PASS
(((2 + 3) * 4) - 5)       = 15  PASS
*/

// Negative numbers
/*
(-5) + 3       = -2   PASS
10 + (-4)      = 6    PASS
(-6) * 7       = -42  PASS
20 / (-4)      = -5   PASS
(-8) - (-3)    = -5   PASS
(-5) * (-2)    = 10   PASS
((-3) + 5) * 2 = 4    PASS
10 - (-5 + 3)  = 12   PASS
*/

// Implicit multiplication
/*
2(3 + 4)        = 14  PASS
5(2)            = 10  PASS
(3 + 1)(2)      = 8   PASS
3(4)(5)         = 60  PASS
2(3 + 4(5 - 2)) = 30  PASS
(2 + 3)(4 + 5)  = 45  PASS
10(5 - 3)       = 20  PASS
*/

// Spaces
/*
5+3   = 8  PASS
5 +3  = 8  PASS
5+ 3  = 8  PASS
5 + 3 = 8  PASS

1 0 + 2 0         = 30   PASS
1  2  3 + 4  5  6 = 579  PASS
( 5 + 3 ) * 2     = 16   PASS
(5+3)*(7-2)       = 40   PASS
  5   +   3       = 8    PASS
*/

// Complex cases
/*
2 * (3 + 4) - 5              = 9     PASS
((10 + 5) / 3) * 2           = 10    PASS
5 + 3 * (2 - 8 / 4)          = 5     PASS
((-5) + 3) * (10 - 7)        = -6    PASS
2(3 + 4(5 - 2)) + 1          = 31    PASS
((5 + (-3)) * 4) / 2         = 4     PASS
100 / (2 * (3 + 2))          = 10    PASS
(-10) / ((-2) + (-3))        = 2     PASS
3(2 + 1) - 4(5 - 3)          = 1     PASS
((8 - 3) * 2 + 10) / (4 - 1) = 6.67  PASS
*/

// Same precedence left-to-right
/*
10 - 5 - 2     = 3   PASS
20 / 4 / 5     = 1   PASS
100 / 10 * 2   = 20  PASS
8 * 2 / 4      = 4   PASS
15 - 3 + 2 - 4 = 10  PASS
*/

// Stress tests
/*
5(3(2(1)))                = 30  PASS
1 + 2 * 3 - 4 / 2 + 5     = 10  PASS
100 - 20 * 3 + 40 / 2 - 5 = 55  PASS

((1 + 2) * (3 + 4)) / ((5 - 2) + 1)  = 5.25  PASS
(((10 - 2) * 3) + ((8 / 2) - 1)) * 2 = 54    PASS
2 * (3 + (4 * (5 - (6 / 2))))        = 22    PASS
(-100) + 50 * 2 / (-5) + 30          = -90   PASS 
*/
