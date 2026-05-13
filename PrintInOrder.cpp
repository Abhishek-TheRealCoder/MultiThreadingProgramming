// Suppose we have a class:

// public class Foo {
//   public void first() { print("first"); }
//   public void second() { print("second"); }
//   public void third() { print("third"); }
// }
// The same instance of Foo will be passed to three different threads. Thread A will call first(), thread B will call second(), 
// and thread C will call third(). Design a mechanism and modify the program to ensure that second() is executed after first(), 
// and third() is executed after second().

// Note:
// We do not know how the threads will be scheduled in the operating system, even though the numbers in the input seem to imply the ordering. The input format you see is mainly to ensure our tests' comprehensiveness.
#include<iostream>
#include<bits/stdc++.h>
#include<thread>
using namespace std;

class Foo {
public:
    condition_variable cv;
    bool isFirstDone = false;
    bool isSecondDone = true;
    bool isThirdDone = true;
    std::mutex mtx;
    Foo() {
        
    }

    void first(function<void()> printFirst) { // function<void()> is declaring a function type that takes no arguments and returns void. printFirst is the name of the function parameter that we will use to call the function that we want to execute in the first() method.
        unique_lock<mutex>lock(mtx);
        while(isFirstDone)
        {
            cv.wait(lock);   // wait until isFirstDone is false, which means that printFirst() has been executed so that we can execute printSecond() and printThird() in the correct order.
        } 
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        isFirstDone = true;
        isSecondDone = false;
        cv.notify_all();
    }

    void second(function<void()> printSecond) { 
        unique_lock<mutex>lock(mtx);
        while(isSecondDone)
        {
            cv.wait(lock);
        }
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        isSecondDone = true;
        isThirdDone = false;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex>lock(mtx);
        while(isThirdDone)
        {
            cv.wait(lock);
        }
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        isThirdDone = true;
        isFirstDone = false;
        cv.notify_all();
    }
};


int main()
{
    Foo foo;
    vector<int> order = {1,3,2};
    
    thread t1, t2, t3;
    
    for(int i = 0; i < order.size(); i++)
    {
        if(order[i] == 1)
        {
            t1 = thread(&Foo::first, &foo, [](){cout << "first";});//&Foo::first is a pointer to member function, &foo is the pointer to object instance on which we want to call the member function, and [](){cout << "first";} is the argument that we want to pass to the member function.
        }
        else if(order[i] == 2)
        {
            t2 = thread(&Foo::second, &foo, [](){cout << "second";});
        }
        else
        {
            t3 = thread(&Foo::third, &foo, [](){cout << "third";});
        }
    }

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
 