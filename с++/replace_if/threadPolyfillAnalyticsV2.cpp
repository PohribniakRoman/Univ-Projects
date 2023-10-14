#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>


void perform_replace_if(std::vector<int>& numbers, int num_trials) {

    std::vector<std::pair<int,int>> data;
    std::vector<std::pair<int,int>> sortedData;

    for (int num_threads = 1; num_threads <= 32; ++num_threads) {
        auto replace_if_function = [&](int thread_id) {
            auto start_time = std::chrono::high_resolution_clock::now();
            for (int i = thread_id; i < numbers.size(); i += num_threads) { // поліфіл&потоки
                if (numbers[i] % 2 == 0) {
                    numbers[i] = 0;
                }
            }
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            data.push_back({num_threads,duration.count()});
        };

        // Запускаємо num_threads потоків для обробки даних
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(replace_if_function, i);
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
    std::ofstream results_file("../replace_if_performance.txt");

    for(auto &i : data) {
        if(sortedData.empty()){
            sortedData.push_back(i);
            continue;
        }
        if(sortedData[sortedData.size()-1].first != i.first){
            int avgDuration = 0;
            for (auto &j : data) {
                if(j.first == i.first){
                    avgDuration+=i.second;
                }
            }
            sortedData.emplace_back(i.first,avgDuration/i.first);
        }
    }

    for (auto &i : sortedData) {
        results_file << i.first << " " << i.second << "\n";
    }

    results_file.close();
}

int main() {
    const int num_trials = 1000; // Кількість вимірювань для кожної реалізації
    const int num_elements = 10000; // Розмір вектора
    std::vector<int> numbers(num_elements, 1); // Вектор для аналізу

    perform_replace_if(numbers, num_trials);

    return 0;
}
