#include <iostream>
#include <future>
#include <string>
#include <syncstream>
#include <chrono>


/*
No15.
Усі обчислення: A1, A2, A3, A4, B, C, D
“Повільні” обчислення:A1,A2
Залежності: B(A1,A2), D(B), C(A3,A4)


A1 -> B ->  D        C
           /        /\
          A2       A3 A4
 */

using namespace std;

void slow(const string& name) {
    this_thread::sleep_for(chrono::seconds(10));
    osyncstream(cout) << name << '\n';
}

void quick(const string& name) {
    this_thread::sleep_for(chrono::seconds(1));
    osyncstream(cout) << name << '\n';
}

void quickА1A2BD() {
    slow("A1");
    slow("A2");
    quick("B");
    quick("D");
}
void work()
{
    auto now = chrono::system_clock::now();
    quickА1A2BD();
    quick("A3");
    quick("A4");
    quick("C");
    osyncstream(cout) << "Work is done!\t" << format("{:%S}", chrono::system_clock::now() - now) << '\n';
}

int main() {
    work();
    return 0;
}