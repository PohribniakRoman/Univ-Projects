#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <numeric>
#include <execution>

template <typename ForwardIt, typename UnaryPredicate, typename T>
void replace_if_polyfill(ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value) {
    for (; first != last; ++first) {
        if (p(*first)) {
            *first = new_value;
        }
    }
}

int main() {
    const int num_trials = 1000;  // Кількість вимірювань для кожної реалізації
    const int num_elements = 10000; // Розмір вектора
    const int num_threads[] = {1,2,3,4,5,6,7,8,9,10,16,32}; // Різна кількість потоків для аналізу

    // Вектор для збереження результатів
    std::vector<double> execution_times;

    for (int num_thread : num_threads) {
        double total_time = 0;

        for (int i = 0; i < num_trials; ++i) {
            // Генеруємо вектор з випадковими числами
            std::vector<int> numbers(num_elements, 1);

            // Вимірюємо час для std::replace_if з використанням різної кількості потоків
            auto start_time = std::chrono::high_resolution_clock::now();
            // std::replace_if(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; }, 0);
            replace_if_polyfill(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; }, 0);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            total_time += duration.count();
        }

        // Обчислюємо середній час виконання
        double average_time = total_time / num_trials;

        // Записуємо результат в вектор
        execution_times.push_back(average_time);
    }

    // Записуємо результати у файл для побудови графіку
    std::ofstream results_file("../replace_if_performance.txt");

    for (int i = 0; i < sizeof(num_threads) / sizeof(num_threads[0]); ++i) {
        results_file << num_threads[i] << " " << execution_times[i] << "\n";
    }

    results_file.close();

    return 0;
}