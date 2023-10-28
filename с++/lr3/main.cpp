#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <vector>

using namespace std;

const int nt = 4;
map<string, int> actions = {{"a", 5}, {"b", 6}, {"c", 4}, {"d", 8}, {"e", 9}, {"f", 6}, {"g", 6}, {"h", 9}, {"i", 7}, {"j", 6}};

mutex mtx;
condition_variable cv;
bool finished = false;
int total_actions = 0;
int completed_actions = 0;

void performAction(const string& action, int action_number, ofstream& outfile) {
    this_thread::sleep_for(chrono::milliseconds(actions[action] * 100));

    unique_lock<mutex> lock(mtx);
    outfile << "З набору " << action << " виконано дію " << action_number << "." << endl;
    completed_actions++;

    if (completed_actions == total_actions) {
        finished = true;
        cv.notify_all();
    }
}

int main() {
    ofstream outfile("../results.txt");

    outfile << "Обчислення розпочато." << endl;

    for (const auto& action : actions) {
        total_actions += action.second;
    }

    vector<thread> threads;
    for (const auto& action : actions) {
        string action_name = action.first;
        int action_count = action.second;

        for (int i = 1; i <= action_count; i++) {
            threads.emplace_back(performAction, action_name, i, std::ref(outfile));
        }
    }

    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return finished; });

    outfile << "Обчислення завершено." << endl;
    outfile.close();

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
