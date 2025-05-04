#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

const string BASE_LOG_FILE = "log.txt";
const size_t MAX_SIZE = 1024 * 1024;  // 1MB

int get_next_log_number() {
    int count = 1;
    while (fs::exists("log" + to_string(count) + ".txt")) {
        ++count;
    }
    return count;
}

void rotate_log_if_needed() {
    if (fs::exists(BASE_LOG_FILE)) {
        auto size = fs::file_size(BASE_LOG_FILE);
        if (size >= MAX_SIZE) {
            int next = get_next_log_number();
            fs::rename(BASE_LOG_FILE, "log" + to_string(next) + ".txt");
        }
    }
}

void write_log(const string& message) {
    rotate_log_if_needed();
    ofstream logfile(BASE_LOG_FILE, ios::app);
    logfile << message << endl;
    logfile.close();
}

int main() {
    string input;
    cout << "Log Rotating System - Enter 'exit' to quit.\n";
    while (true) {
        cout << "Enter log message: ";
        getline(cin, input);
        if (input == "exit") break;
        write_log(input);
        cout << "Log written.\n";
    }

    return 0;
}
