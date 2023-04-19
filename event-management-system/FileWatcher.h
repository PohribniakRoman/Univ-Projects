#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <functional>

enum class FileStatus {created, modified, erased};

class FileWatcher {
 public:
    string path_to_watch;
    chrono::duration<int, milli> delay;

    FileWatcher(string path_to_watch, chrono::duration<int, milli> delay) : path_to_watch{path_to_watch}, delay{delay} {
        for(auto &file : filesystem::recursive_directory_iterator(path_to_watch)) {
             paths_[file.path().string()] = filesystem::last_write_time(file);
         }
    }
    void start(const function<void (string, FileStatus)> &action) {
        while (running_) {
            this_thread::sleep_for(delay);
            auto it = paths_.begin();
            while (it != paths_.end()) {
                if (!filesystem::exists(it->first)) {
                    action(it->first, FileStatus::erased);
                    it = paths_.erase(it);
                }
                else {
                    it++;
                }
            }
            for (auto &file: filesystem::recursive_directory_iterator(path_to_watch)) {
                auto current_file_last_write_time = filesystem::last_write_time(file);
                if (!contains(file.path().string())) {
                    paths_[file.path().string()] = current_file_last_write_time;
                    action(file.path().string(), FileStatus::created);
                } else {
                    if (paths_[file.path().string()] != current_file_last_write_time) {
                        paths_[file.path().string()] = current_file_last_write_time;
                        action(file.path().string(), FileStatus::modified);
                    }
                }
            }
        }
    }
private:
     unordered_map<string, filesystem::file_time_type> paths_;
     bool running_ = true;
     bool contains(const string &key) {
         auto el = paths_.find(key);
        return el != paths_.end();
    }
};