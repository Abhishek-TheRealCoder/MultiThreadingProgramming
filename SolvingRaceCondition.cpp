
#include<iostream> 
#include<bits/stdc++.h>
#include<thread>
using namespace std;

std::mutex m;

int main()
{
    int counter = 0;
    auto incrementCounter = [&counter]() {
        lock_guard<mutex> lock(m); // lock the mutex to synchronize access to the counter variable
        for (int i = 0; i < 100000; i++) {
            counter++;
        }
    };

    thread t1(incrementCounter); // lambda function to increment the counter variable
    thread t2(incrementCounter); // lambda function to increment the counter variable

    t1.join();
    t2.join();

    cout << "Final Counter Value: " << counter << endl;

    return 0;
}