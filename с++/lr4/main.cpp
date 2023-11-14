#include <mutex>
#include <random>
#include <iostream>
#include <fstream>
#include <syncstream>
#include <thread>
#include <future>
#include <cmath>
#include <string>

using namespace std;

#define CNT

mutex mu;

int f1(int n);
int f2(int n);
int f3(int n);
int f4(int n);

int (*functions[])(int) = {f1, f2, f3, f4};

int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int cnt4 = 0;
int max_threads = std::thread::hardware_concurrency() == 0 ? 2 : std::thread::hardware_concurrency();
int active_threads = 1;

bool isFree()
{
    return active_threads < max_threads;
}

int rand_num(int min, int max)
{
    mt19937 g(time(NULL));
    uniform_int_distribution<int> d(min, max);
    return d(g);
}

int f1(int n)
{
#ifdef CNT
    {
        lock_guard<mutex> guard(mu);
        cnt1++;
    }
#endif
    osyncstream(cout) << "I am function f1, currently working\n";
    this_thread::sleep_for(chrono::milliseconds(rand_num(10, 30)));

    if (n == 0)
        return 1;

    int i1, i2;
    do
    {
        i1 = rand_num(0, 3);
    } while (i1 == 0);
    do
    {
        i2 = rand_num(0, 3);
    } while (i1 == i2 || i2 == 0);
    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i1], n - 1);
        active_threads++;
        int res1 = functions[i2](2 * n / 3);
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }
    int res1 = functions[i1](n - 1);
    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i2], 2 * n / 3);
        active_threads++;
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }
    return res1 + functions[i2](2 * n / 3);
}

int f2(int n)
{
#ifdef CNT
    {
        lock_guard<mutex> guard(mu);
        cnt2++;
    }
#endif
    osyncstream(cout) << "I am function f2, currently working\n";
    this_thread::sleep_for(chrono::milliseconds(rand_num(1, 10)));

    if (n == 0)
        return 1;

    int i1, i2;
    do
    {
        i1 = rand_num(0, 3);
    } while (i1 == 1);
    do
    {
        i2 = rand_num(0, 3);
    } while (i1 == i2 || i2 == 1);
    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i1], n - 1);
        active_threads++;
        int res1 = functions[i2](2 * n / 3);
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }
    int res1 = functions[i1](n - 1);
    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i2], 2 * n / 3);
        active_threads++;
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }
    return res1 + functions[i2](2 * n / 3);
}

int f3(int n)
{
#ifdef CNT
    {
        lock_guard<mutex> guard(mu);
        cnt3++;
    }
#endif
    osyncstream(cout) << "I am function f3, currently working\n";
    this_thread::sleep_for(chrono::milliseconds(rand_num(1, 10)));

    if (n == 0)
        return 1;
    int i1, i2;
    do
    {
        i1 = rand_num(0, 3);
    } while (i1 == 2);
    do
    {
        i2 = rand_num(0, 3);
    } while (i1 == i2 || i2 == 2);
    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i1], n - 1);
        active_threads++;
        int res1 = functions[i2](2 * n / 3);
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }
    int res1 = functions[i1](n - 1);
    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i2], 2 * n / 3);
        active_threads++;
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }
    return res1 + functions[i2](2 * n / 3);
}

int f4(int n)
{
#ifdef CNT
    {
        lock_guard<mutex> guard(mu);
        cnt4++;
    }
#endif
    osyncstream(cout) << "I am function f4, currently working\n";
    this_thread::sleep_for(chrono::milliseconds(rand_num(1, 10)));

    if (n == 0)
        return 1;

    int i1, i2;
    do
    {
        i1 = rand_num(0, 3);
    } while (i1 == 3);

    do
    {
        i2 = rand_num(0, 3);
    } while (i1 == i2 || i2 == 3);

    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i1], n - 1);
        active_threads++;
        int res1 = functions[i2](2 * n / 3);
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }

    int res1 = functions[i1](n - 1);
    if (isFree())
    {
        future<int> myFuture = async(std::launch::async, functions[i2], 2 * n / 3);
        active_threads++;
        int res2 = myFuture.get();
        active_threads--;
        return res1 + res2;
    }
    return res1 + functions[i2](2 * n / 3);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    int n = stoi(argv[1]);

    functions[0](n);

#ifdef CNT
    osyncstream(cout) << "Number of calls f1: " << cnt1 << endl;
    osyncstream(cout) << "Number of calls f2: " << cnt2 << endl;
    osyncstream(cout) << "Number of calls f3: " << cnt3 << endl;
    osyncstream(cout) << "Number of calls f4: " << cnt4 << endl;
#endif

    return 0;
}
