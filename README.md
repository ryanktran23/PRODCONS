# CS471-Semester-Project

2023 CS471 Semester Course Project

For: Ryan Tran (UID: 01127167)

This is for Problem 1: Producer-Consumer problem.
C++ is used for the programming language and VSCode is the IDE.

To run the program, in the terminal compile the code with 

"g++ -std=c++11 main.cpp -lpthread -o main"

and run the program,

"./main"

it will then prompt the user for an input. It will prompt the user for:

"Enter number of producers: "

Once the user enters in a number, then the program will prompt for the user:

"Enter the number of consumers: "

Once the user enters a value for both prompts, the terminal will print out
the Consumer Statistics for Consumer 1 and Consumer 2. With a random number
generator, the data for the sales for the store is random and not always the
same. The output will show the Store # and the total sales that store had within
all 12 months. It will then show the total sales for each month specifically.
The program will also print out the overall statistics for all consumer stores.
This includes the total time and the aggregate sales for the # of consumers that
the user input before.
