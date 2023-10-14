#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

template <typename ForwardIt, typename UnaryPredicate, typename T>
void replace_if_polyfill(ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value) {
    for (; first != last; ++first) {
        if (p(*first)) {
            *first = new_value;
        }
    }
}

int main() {
   const int num_trials = 10;
   const int num_elements = 10000;
   std::vector<int> numbers(num_elements, 1);

   std::ofstream results_file("../replace_if_performance.txt");

   for (int i = 0; i < num_trials; ++i) {
       auto start_time = std::chrono::high_resolution_clock::now();
    //    std::replace_if(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; }, 0); 
       replace_if_polyfill(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; }, 0);
       auto end_time = std::chrono::high_resolution_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
       results_file << duration.count() << " " << i+1 << "\n";

       std::fill(numbers.begin(), numbers.end(), 1);
   }

   results_file.close();
   return 0;
}