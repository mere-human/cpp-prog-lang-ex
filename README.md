# cpp-prog-lang-ex
## Exercise Solutions From Book "The C++Programming Language (4ed)" By Stroustrup

The list is incomplete. Some of the exercises are to be implemented while others are not very interesting for me.
Numbers corresponds to chapter numbers from book.

### Table of exercises done or to be done

| No  | Desc | Complexity | Status |
|:--- |:----|:--------- |:----- |
| **6** | **Types and Declarations**                     |     |      |
| 6-1  | "Hello, world!"                                 | 2   | Done |
| 6-2  | Determine whether `char` is signed or not         | 1   | Done |
| 6-7  | Print ASCII characters and their integer values | 1.5 | Done |
| 6-13 | Print values without an array                   | 1.5 | Done |
| **7** | **Pointers, Arrays, and References**           |     |      |
| 7-1  | Declarations                                    | 1   | Done |
| 7-3  | Types definition using alias                    | 1.5 | Done |
| 7-8  | Compute the size and the length of a C-string   | 1.5 | Done |
| 7-9  | Function calls                                  | 1   | Done |
| **8** | **Structures, Unions, and Enumerations**       |     |      |
| 8-1  | Struct with integral type members               | 1   | Done |
| 8-4  | `Date` struct                                     | 1.5 | Done |
| 8-5  | Season enum with operations                     | 2   | Done |
| **9** | **Statements** | | |
| 9-1  | Rewrite `for`-statement as a `while`-statement      | 1 | Done |
| 9-2  | See how compiler reacts on certain errors       | 1 | Done |
| 9-4  | Function `atoi` that converts C-string to int | 2 | Done |
| 9-5  | Function `itoa` that converts int to C-string | 2 | Done |
| 9-7  | Strip comments out of a C++ program | 2.5 | Done |
| **10** | **Expressions** | | |
| 10-7  | Implement and test: `strlen, strcpy, strcmp` | 2 | Done |
| 10-9  | Function `cat` that concatenates two C-strings | 2 | Done |
| 10-10 | Function `rev` that reverses the characters in C-string | 2 | Done |
| 10-11 | Type in the calculator example and get it to work | 2 | Done |
| 10-12 | Calculator: report line numbers for errors | 2 | Done |
| **11** | **Select Operations** | | |
| 11-2  | Allocate so much memory that `bad_alloc` is thrown | 2 | Done |
| **12** | **Functions** | | |
| 12-1  | Declarations of certain functions | 1 | Done   |
| 12-2  | Describe using alias | 1 | Done   |
| 12-3  | "Hello, world!" that takes a name from command line | 1.5 | Done   |
| 12-4  | Program that reads files and writes them on cout | 1.5 | Done   |
| 12-5  | Convert a small C program to C++ | 2 | Done   |
| 12-6  | Eliminate arrays and "naked" news from the result of prev. ex. | 2 | Done   |
| 12-9  | Invert two-dimensional array | 2.5 | Done   |
| 12-10 | Encrypt input using `c^key[i]` and write to output | 2 | Done   |
| 12-11 | Decipher messages by 12-10 w/o knowing the key | 3.5 | TODO   |
| 12-12 | Tiny Encryption Algorithm | 2 | TODO   |
| 12-16 | Macro processor that expands simple macros | 3 | Done   |
| 12-17 | `error` function that takes `printf`-style formatting | 3 | TODO   |
| 12-18 | Subset of `printf`| 2 | TODO   |
| 12-19 | Add functions as `sqrt(), log(), sin()` to the calculator | 2 | Done   |
| 12-20 | Factorial w/o recursion | 1 | Done   |
| 12-21 | Add one day, one month and one year to a Date struct | 2 | In dev |
| **13** | **Exception Handling** | | |
| 13-1 | `Checked_ptr<T>` that points to an element of an array with run-time errors | 3 | Done |
| 13-2 | Search a binary tree of nodes based on a `char*` field | 3 | Done |
| 13-3 | Class `Int` that throws rather than overflowing or underflowing | 3 | Done |
| 13-4 | C++ equivalents that throw for C file functions | 2.5 | Done |
| 13-5 | `Vector` template with `Range` and `Size` exceptions | 2.5 | Done |
| 13-6 | Sum of a `Vector` w/o examining the size | 1 | Done |
| 13-8 | Modified `main()` that catches all exceptions and use `abort()` | 1 | Done |
| 13-9 | Class or template for callbacks | 2 | Done |
| 13-11 | Performance of exception throwing at different levels | 2 | TODO |
| 13-13 | Modified calculator that uses exceptions | 2 | Done |
| 13-14 | Functions `plus, minus, multiply, divide` that check for overflow/underflow | 2.5 | Done |
| 13-15 | Modified calculator that uses functions from 13-14 | 2 | Done |
| **14** | **Namespaces** | | |
| 14-1 | Modify program that uses library w/o namespace to use namespace for it | 2 | TODO |
| 14-2 | Modify calculator to use namespaces | 2.5 | Done |
| **15** | **Files** | | |
| 15-1 | Find where the standard library headers and nonstandard ones are kept on your system | 2 | TODO |
| 15-3 | Read source file and write out the names of included files | 2.5 | Done |
| 15-4 | Modify the program from 15-3 to print number of lines (comment, non-comment, whitespace) | 3 | Done |
| 15-7 | Read and compare performance of reading files | 3 | TODO |
| 15-8 | Modify the calculator so that it can be invoked as a simple function call | 2 | TODO |
| **16** | **Classes** | | |
| 16-1 | Find the error in `Date::add_year()` | 1 | Done |
| 16-2 | Complete and test Date. Reimplement it with "number of days after..." representation | 2.5 | Done |
| 16-7 | Define, implement and test a set of integers, class `Intset` | 3 | Done |
| 16-8 | Modify class `Intset` into a set of nodes | 1.5 | Done |
| 16-9 | Define a class for analyzing simple arithmetic expressions | 1.5 | TODO |
| 16-13 | Modify "Hello, world!" example to print strings befoore and after `main()` | 1 | TODO |
| 16-16 | Write a function that produces a map holding each string and the number of lines | 3 | TODO |
| **17** | **Construction, Cleanup, Copy and Move** | | |
| 17-1 | Implement the functions of the "canonical complete class" `X` and print their name and address | 2 | Done |
| 17-4 | `Vector` class with an initializer-list constructor and `Count` type constructor | 1 | Done |
| 17-5 | Simple document editor | 3 | TODO |
| 17-6 | Simple `Matrix` based on ch.17.5.2 | 3 | Done |
| **18** | **Overloading** | | |
| 18-1 | Describe conversions | 2 | TODO |
| 18-2 | Complete and test class `String` from ch.19.3 (Why is it here?) | 2 | TODO |
| 18-4 | Define a class `RINT` that behaves like an int except limited operators | 1 | TODO |
| 18-9 | Define a class `Vec4` | 2 | TODO |
| 18-10 | Define a class `Mat4` and Gaussian elimination | 3 | TODO |
| 18-11 | Define a class `Vector` similar to `Vec4` but with size | 2 | TODO |
| 18-12 | Define a class `Matrix` similar to `Mat4` but with size | 3 | TODO |
| 18-13 | Pointer to member | 1 | TODO |
| 18-14 | Define a class `Index` for an exponent and `2**I`  | 1.5 | Done |
| **19** | **Special Operations** | | |
| 19-1 | Complete class `Ptr` from ch.19.2.4 | 2 | TODO |
| 19-2 | Define an external iterator for class `String` | 2 | TODO |
| 19-3 | Provide a substring operator for `String` by overloading `()` | 1.5 | TODO |
| 19-4 | Design class `String` so that the substring operator can be used on LHS | 3 | TODO |
| **20** | **Derived Classes** | | |
| 20-2 | Implement a simple graphics system with `Window, Shape, Line`, etc | 3.5 | TODO |
| 20-3 | Implement operations to vary the appearance of the `Shape` segments | 2 | TODO |
| 20-4 | Provide a function `Line::arrowhead()` | 2.5 | TODO |
| 20-5 | Make sure that points and line segments that fall outside the `Window` do not appear on the screen | 3.5 | TODO |
| 20-6 | Add a `Text` type to the graphics system | 2.5 | TODO |
| 20-7 | Define a function that draws a line connecting two shapes | 2 | TODO |
| 20-8 | Add a notion of color to the graphics system | 3 | TODO |
| 20-10 | Define intersect function for `Shape` that implements double dispatch | 2.5 | TODO |
| 20-11 | Design and implement a library for writing event-driven simulations | 5 | TODO |
| 20-14 | Outline a different implementation strategy for the `lval_box` example from ch.21.2 | 3 | TODO |

## TODO
1. Add each file and directory
1. Cleanup each file and it's description
1. Integrate with CMake or similar (optional)
1. Read the result of 15-1 by the 15-3
