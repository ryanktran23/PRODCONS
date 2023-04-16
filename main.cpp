#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Structure for Sales Record
struct Record {
    int dd, mm, storeID, registerNum;
    float saleAmount;
};

// Global Variables
int b = 3;
int recordsGenerated = 0;
mutex m;

//Shared variables
vector<Record> buffer;
int storeWideTotalSales[10];
int monthWiseTotalSales[12];
int aggregateSales = 0;
chrono::time_point<chrono::system_clock> startTime;
chrono::time_point<chrono::system_clock> endTime;

//Function Prototypes
void producer(int storeID);
void consumer(int consumerID);

//Main Function
int main(int argc, char *argv[]) {
    int p, c;
    vector<thread> producers;
    vector<thread> consumers;

    // Taking inputs
    cout << "Enter the number of producers: ";
    cin >> p;
    cout << "Enter the number of consumers: ";
    cin >> c;

    // Initializing Shared Variables
    for (int i = 0; i < 10; i++)
        storeWideTotalSales[i] = 0;
    for (int i = 0; i < 12; i++)
        monthWiseTotalSales[i] = 0;

    // Creating Producers
    for (int i = 0; i < p; i++)
        producers.push_back(thread(producer, i + 1));

    // Creating Consumers
    for (int i = 0; i < c; i++)
        consumers.push_back(thread(consumer, i + 1));

    // Joining Producers
    for (int i = 0; i < p; i++)
        producers[i].join();

    // Joining Consumers
    for (int i = 0; i < c; i++)
        consumers[i].join();

    // Calculating total time
    endTime = chrono::system_clock::now();
    chrono::duration<double> elapsedTime = endTime - startTime;

    // Printing Overall Statistics
    cout << "\nOverall Statistics:\n";
    cout << "Total Time: " << elapsedTime.count() << " seconds\n";
    cout << "Aggregate Sales: $" << aggregateSales << endl;
    for (int i = 0; i < 10; i++)
        cout << "Store " << i+1 << " Total Sales: $" << storeWideTotalSales[i] << endl;
    for (int i = 0; i < 12; i++)
        cout << "Month " << i+1 << " Total Sales: $" << monthWiseTotalSales[i] << endl;

    return 0;
}

// Producer Function
void producer(int storeID) {
    Record record;
    while (recordsGenerated < 1000) {
        // Generating random sales information
        record.dd = (rand() % 30) + 1;
        record.mm = (rand() % 12) + 1;
        record.storeID = storeID;
        record.registerNum = (rand() % 6) + 1;
        record.saleAmount = (rand() % 950) + 50;

        // Acquiring mutex
        m.lock();

        // Adding record to buffer
        buffer.push_back(record);
        recordsGenerated++;

        // Releasing mutex
        m.unlock();

        // Sleeping for 5-40 milliseconds
        int sleepTime = (rand() % 36) + 5;
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
}

// Consumer Function
void consumer(int consumerID) {
    int storeWideTotal = 0;
    int monthWiseTotal[12] = {0};
    while (recordsGenerated < 1000) {
        // Acquiring mutex
        m.lock();

        if (buffer.size() > 0) {
            // Taking record from buffer
            Record record = buffer[buffer.size() - 1];
            buffer.pop_back();

            // Calculating local totals
            storeWideTotal += record.saleAmount;
            monthWiseTotal[record.mm - 1] += record.saleAmount;

            // Releasing mutex
            m.unlock();
        }
        else {
            // Releasing mutex
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(5));
        }
    }

    // Acquiring mutex
    m.lock();

    // Adding local totals to global totals
    storeWideTotalSales[consumerID - 1] = storeWideTotal;
    for (int i = 0; i < 12; i++)
        monthWiseTotalSales[i] += monthWiseTotal[i];
    aggregateSales += storeWideTotal;

    // Releasing mutex
    m.unlock();

    // Printing local statistics
    cout << "\nConsumer " << consumerID << " Statistics:\n";
    cout << "Store " << consumerID << " Total Sales: $" << storeWideTotal << endl;
    for (int i = 0; i < 12; i++)
        cout << "Month " << i+1 << " Total Sales: $" << monthWiseTotal[i] << endl;
}
