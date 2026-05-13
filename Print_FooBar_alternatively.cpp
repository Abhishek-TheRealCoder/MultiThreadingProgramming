// Suppose you are given the following code:

// class FooBar {
//   public void foo() {
//     for (int i = 0; i < n; i++) {
//       print("foo");
//     }
//   }

//   public void bar() {
//     for (int i = 0; i < n; i++) {
//       print("bar");
//     }
//   }
// }
// The same instance of FooBar will be passed to two different threads:

// thread A will call foo(), while
// thread B will call bar().
// Modify the given program to output "foobar" n times.

 

// Example 1:

// Input: n = 1
// Output: "foobar"
// Explanation: There are two threads being fired asynchronously. One of them calls foo(), while the other calls bar().
// "foobar" is being output 1 time.

// Example 2:

// Input: n = 2
// Output: "foobarfoobar"
// Explanation: "foobar" is being output 2 times.
 

// Constraints:

// 1 <= n <= 1000
#include<iostream>
#include<bits/stdc++.h>
#include<thread>

using namespace std;

class FooBar {
private:
    int n;
    condition_variable cv;
    bool isFooDone;
    mutex mtx;

public:
    FooBar(int n) {
        this->n = n;
        this->isFooDone = false;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<std::mutex>lock(mtx);
            while(isFooDone)
            {
                cv.wait(lock);
            }
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            isFooDone = true;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<std::mutex>lock(mtx);
            while(!isFooDone)   // !False = true
            {
                cv.wait(lock);
            }
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            isFooDone = false;
            cv.notify_all();
        }
    }
};

int main()
{
    int n = 2;
    FooBar foobar(n);
    thread t1(&FooBar::foo, &foobar, [](){cout<<"foo";});
    thread t2(&FooBar::bar, &foobar, [](){cout<<"bar";});
    t1.join();
    t2.join();
    return 0;
}