#include <windows.h>
#include <iostream>
#include <thread>

using namespace std;

HANDLE hSem;

const int N = 100;
int a = 0;
int b = 0;

void thread1() {
    for(int i = 0; i < N; i++) {
        WaitForSingleObject(hSem, INFINITE);
        a = b + 3;
        b--;
        cout << "[Thread 1: a = " << a << ", b = " << b << ']' << endl;
        ReleaseSemaphore(hSem, 1, nullptr);
    }
}

void thread2() {
    for(int i = 0; i < N; i++) {
        WaitForSingleObject(hSem, INFINITE);
        b += 2;
        cout << "[Thread 2: b = " << b << ']' << endl;
        ReleaseSemaphore(hSem, 1, nullptr);
    }
}

int main() {
    hSem = CreateSemaphore(nullptr, 1, 1, "MySemaphore1");
    thread thr1(thread1);
    thread thr2(thread2);
    thr1.join();
    thr2.join();

    cout << "\nTotal values: \n" << "a = " << a << "\nb = " << b << endl;
    return 0;
}