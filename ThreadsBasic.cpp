#include<thread>
#include<mutex>
#include<iostream>
#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;


void printHello()
{
    cout<< "Hello World " << this_thread::get_id() << endl;
}

void taskA()
{
    for(int i = 0;i < 5;i++)
    {
        sleep(1);
        cout<< "Task A\n"  ;
        fflush(stdout);
    }
}

void taskB()
{
    for(int i = 0;i < 5;i++)
    {
        sleep(1);
        cout<< "Task B\n" ;
        fflush(stdout);
    }
}


int main()
{
    
    
    std::thread t1(printHello);
    std::thread t2(taskA);
    std::thread t3(taskB);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}