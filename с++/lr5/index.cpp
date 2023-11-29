#include <iostream>
#include <future>
#include <string>
#include <syncstream>
#include <chrono>


/*
No8.
 Усі обчислення: A,B1,B2,B3,C1,C2,D
“Повільні” обчислення:B1,C2
Залежності: B1(A), C1(B1,B2,B3) D(C1,C2)


 A -> B1 -> C1 -> D
           / \   /
          B2 B3 C2
 */

using namespace std;

void slow(const string& name) {
    this_thread::sleep_for(chrono::seconds(7));
    osyncstream(cout) << name << '\n';
}

void quick(const string& name) {
    this_thread::sleep_for(chrono::seconds(1));
    osyncstream(cout) << name << '\n';
}

void quickAB1C1() {
    quick("A");
    slow("B1");
}
void work()
{
    auto now = chrono::system_clock::now();
    auto result = async(launch::async, quickAB1C1);
    quick("B2");
    quick("B3");
    result.get();
    quick("C1");
    slow("C2");
    quick("D");
    osyncstream(cout) << "Work is done!\t" << format("{:%S}", chrono::system_clock::now() - now) << '\n';
}

int main() {
    work();
    return 0;
}