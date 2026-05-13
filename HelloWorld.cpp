#include<iostream>
#include<bits/stdc++.h>
#include<thread>

using namespace std;
std::mutex m;

void HelloWorld()
{
    std::lock_guard<std::mutex> lock(m);
    cout << "Hello World " << this_thread::get_id() << "\n\n";
}
int main()
{
    cout<< this_thread::get_id() << endl;

    vector<thread> threads;
    int n = thread::hardware_concurrency();
    cout << "Number of concurrent threads supported: " << n << endl;

    for(int i = 0;i < 5;i++)
    {
        threads.emplace_back(thread(HelloWorld));
    }

    for(int i = 0;i < 5;i++)
    {
        threads[i].join();
    }
    
    return 0;
}