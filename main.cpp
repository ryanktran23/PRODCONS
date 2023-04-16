#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// This is the structure for Sales Record.
struct Record {
    int dd, mm, storeID, registerNum;
    float saleAmount;
};

// These are the global variables.
int b = 3;
int recordsGenerated = 0;
mutex m;

// These are the shared variables.
vector<Record> buffer;
int storeWideTotalSales[10];
int monthWiseTotalSales[12];
int aggregateSales = 0;
chrono::time_point<chrono::system_clock> startTime;
chrono::time_point<chrono::system_clock> endTime;

// These are the function prototypes.
void producer(int storeID);
void consumer(int consumerID);

// This is the main function.
int main(int argc, char *argv[]) {
    int p, c;
    vector<thread> producers;
    vector<thread> consumers;

    cout << "Enter the number of producers: ";
    cin >> p;
    cout << "Enter the number of consumers: ";
    cin >> c;

    for (int i = 0; i < 10; i++)
        storeWideTotalSales[i] = 0;
    for (int i = 0; i < 12; i++)
        monthWiseTotalSales[i] = 0;

    for (int i = 0; i < p; i++)
        producers.push_back(thread(producer, i + 1));
    for (int i = 0; i < c; i++)
        consumers.push_back(thread(consumer, i + 1));
    for (int i = 0; i < p; i++)
        producers[i].join();
    for (int i = 0; i < c; i++)
        consumers[i].join();

    endTime = chrono::system_clock::now();
    chrono::duration<double> elapsedTime = endTime - startTime;

    // This will print the overall statistics for the program.
    cout << "\nOverall Statistics:\n";
    cout << "Total Time: " << elapsedTime.count() << " seconds\n";
    cout << "Aggregate Sales: $" << aggregateSales << endl;
    for (int i = 0; i < 10; i++)
        cout << "Store " << i+1 << " Total Sales: $" << storeWideTotalSales[i] << endl;
    for (int i = 0; i < 12; i++)
        cout << "Month " << i+1 << " Total Sales: $" << monthWiseTotalSales[i] << endl;

    return 0;
}

// This is the producer function.
void producer(int storeID) {
    Record record;
    while (recordsGenerated < 1000) 
    {
        record.dd = (rand() % 30) + 1;
        record.mm = (rand() % 12) + 1;
        record.storeID = storeID;
        record.registerNum = (rand() % 6) + 1;
        record.saleAmount = (rand() % 950) + 50;
        m.lock();
        buffer.push_back(record);
        recordsGenerated++;
        m.unlock();

        int sleepTime = (rand() % 36) + 5;
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
}

// This is the consumer function.
void consumer(int consumerID) 
{
    int storeWideTotal = 0;
    int monthWiseTotal[12] = {0};
    while (recordsGenerated < 1000) {
        m.lock();

        if (buffer.size() > 0) 
        {
            Record record = buffer[buffer.size() - 1];
            buffer.pop_back();
            storeWideTotal += record.saleAmount;
            monthWiseTotal[record.mm - 1] += record.saleAmount;
            m.unlock();
        }
        else 
        {
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(5));
        }
    }

    m.lock();
    storeWideTotalSales[consumerID - 1] = storeWideTotal;
    for (int i = 0; i < 12; i++)
        monthWiseTotalSales[i] += monthWiseTotal[i];
    aggregateSales += storeWideTotal;
    m.unlock();

    // This will print the local statistics.
    cout << "\nConsumer " << consumerID << " Statistics:\n";
    cout << "Store " << consumerID << " Total Sales: $" << storeWideTotal << endl;
    for (int i = 0; i < 12; i++)
        cout << "Month " << i+1 << " Total Sales: $" << monthWiseTotal[i] << endl;
}
