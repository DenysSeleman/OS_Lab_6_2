#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
using namespace std;

mutex mtx;
const int incrementTimes = 1000000;

void increment_f(int& num)
{
    for (int i = 0; i < incrementTimes; i++)
        num++;
}

void mutex_increment_f(int& num)
{
    lock_guard<mutex> guard(mtx);
    for (int i = 0; i < incrementTimes; i++)
        num++;
}

int main()
{
    int num = 0;
    thread first(increment_f, ref(num));
    thread second(increment_f, ref(num));
    first.join();
    second.join();
    cout << "Simple variant: num = " << num << "\n";

    int m_num = 0;
    thread m_first(mutex_increment_f, ref(m_num));
    thread m_second(mutex_increment_f, ref(m_num));
    m_first.join();
    m_second.join();
    cout << "Mutex variant: m_num = " << m_num << "\n";

    return 0;
}