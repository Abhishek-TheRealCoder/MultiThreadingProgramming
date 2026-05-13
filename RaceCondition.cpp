// Race Condition is nothing but a situation where two or more threads are trying to access the same resource at the same time. 
// This can lead to unpredictable behavior and can cause bugs in the program
// Example of race condition is when two threads are trying to increment a shared counter variable at the same time.
// In this case, both threads may read the same value of the counter variable, increment it, and then write the new value back to the variable. 
// This can lead to a situation where the counter variable is not incremented correctly, and the final value of the counter variable may be less than the expected value.
// Like this small code snippet:
#include<iostream>  
#include<thread>
using namespace std;

int main()
{
    int counter = 0;

    auto incrementCounter = [&counter]() {
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

// In this example, both threads t1 and t2 are trying to increment the counter variable at the same time.
// This can lead to a race condition, and the final value of the counter variable may be less than 200000, which is the expected value.
// To avoid this race condition, we can use a lock mutex to synchronize access to the counter variable.
