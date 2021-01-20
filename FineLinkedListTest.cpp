#include "FineLinkedList.h"
#include "FineCircularBuffer.h"
#include <iostream>
#include <thread>
#include <sstream>

using namespace std;

fineList<int> fList;
fineBuffer<int, 10> fBuffer;

void fineListFunction(int i, int s, int d) {
    for (int j = s; j < d; j++)
        if (!fList.add(j + i * j))
            cout << "Fine Grained add error." << endl;

    for (int j = s; j < d; j++)
        if (!fList.contains(j + i * j))
            cout << "Fine Grained contains error." << endl;

    for (int j = s; j < d; j++)
        if (!fList.remove(j + i * j))
            cout << "Fine Grained remove error." << endl;
}

int main(int argc, char* argv[])
{
    // *****************************************************************
    //  Data declarations...

    const char* bold = "\033[1m";
    const char* unbold = "\033[0m";
    string		stars = "";
    string      bars = "";
    int threadCount = 4;
    stringstream mySS;

    stars.append(65, '*');
    bars.append(60, '-');

    // Dynamically allocate threadCount threads
    thread* t1 = new thread[threadCount];

    // *****************************************************************
    // Display header

    cout << stars << endl << bold << "Concurrent Linked List Tests" <<
        unbold << endl << endl;

    // *****************************************************************
    // Fine Grained Linked List

    cout << bars << endl << bold << "Fine Grained Linked List" << unbold <<
        unbold << endl;

    for (int threadNum = 1; threadNum <= threadCount; threadNum++) {
        // Start time
        auto f1 = chrono::high_resolution_clock::now();

        // Start up threads...
        for (int i = 0; i < threadNum; i++) {
            t1[i] = thread(&fineListFunction, i, i * (10000 / threadNum), (i + 1) * (10000 / threadNum));
        }


        // Wait for threads to finish...
        for (int i = 0; i < threadNum; i++)
            t1[i].join();

        // End time
        auto f2 = chrono::high_resolution_clock::now();

        cout << "   Run-time: " << chrono::duration_cast<chrono::milliseconds>(f2 - f1).count()
            << " milliseconds" << endl << endl;
    }

    // *****************************************************************
    // All done...

    delete[] t1;
}