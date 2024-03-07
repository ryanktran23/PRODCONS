# Producer and Consumer Sales Report

C++ is used for the programming language and VSCode is the IDE.

In this program, we have a set of p producers and c consumers, each running as a single thread.
They are synchronized via shared buffer of size b. Each buffer item contains the following information: Sales Date (DD/MM/YY), store ID
(integer), register# (integer), sale amount (float). Each item represents a sales record from
a specific cashier register in a particular location of a retail-chain. Thus, each producer
reports sales from a specific store location. Each consumer represents an entity that reads
sales records and computes sales statistics locally. Each buffer item is consumed by one-
and-only-one consumer. When all sales records have been read (indicated by a special
flag set by another designated thread), each consumer adds its local statistics to the global
statistics (in the shred space). It also prints its own local statistics along with its ID. In
addition, your main program (parent process) prints the overall (global) statistics.

The statistics to be maintained are:
Store-wide total sales
Month-wise total sales (in all stores)
Aggregate sales (all sales together)
Total time for simulation (from begin to end)

Each producer produces records randomly. Assume that the DD field is 1-30, MM is 01-
12, and YY is always 16. Store IDs are in the 1 to p range (where p is the number of
producers). The register numbers range from 1-6 for any store. The sale amount in each
item can range between 0.50 and 999.99. Each producer generates its record with random
data. Run the program until 1000 items are produced by all producers together.
Obviously, the number of items produced so far (by all producers) need to be maintained
in shared memory. Each producer is assigned a fixed store ID when it is created.

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
