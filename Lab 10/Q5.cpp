#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string FILENAME = "todo.txt";

struct Task {
    string description;
    bool done;

    string to_string() const {
        return (done ? "[x] " : "[ ] ") + description;
    }

    static Task from_string(const string& line) {
        Task t;
        if (line.rfind("[x] ", 0) == 0) {
            t.done = true;
            t.description = line.substr(4);
        } else if (line.rfind("[ ] ", 0) == 0) {
            t.done = false;
            t.description = line.substr(4);
        } else {
            t.done = false;
            t.description = line;
        }
        return t;
    }
};

// Load all tasks
vector<Task> load_tasks() {
    vector<Task> tasks;
    ifstream file(FILENAME);
    string line;
    while (getline(file, line)) {
        tasks.push_back(Task::from_string(line));
    }
    file.close();
    return tasks;
}

// Save all tasks (overwrite)
void save_tasks(const vector<Task>& tasks) {
    ofstream file(FILENAME);
    for (const auto& task : tasks) {
        file << task.to_string() << endl;
    }
    file.close();
}

// Add a task
void add_task(const string& description) {
    ofstream file(FILENAME, ios::app);
    file << "[ ] " << description << endl;
    file.close();
}

// Mark task as done
void mark_done(int index) {
    auto tasks = load_tasks();
    if (index < 1 || index > tasks.size()) {
        cout << "Invalid task number." << endl;
        return;
    }
    tasks[index - 1].done = true;
    save_tasks(tasks);
    cout << "Task marked as done." << endl;
}

// Display all tasks
void view_tasks() {
    auto tasks = load_tasks();
    if (tasks.empty()) {
        cout << "No tasks found." << endl;
        return;
    }
    int i = 1;
    for (const auto& t : tasks) {
        cout << i++ << ". " << t.to_string() << endl;
    }
}

// Main menu
void menu() {
    while (true) {
        cout << "\nTo-Do List Manager\n1. Add Task\n2. View Tasks\n3. Mark Task as Done\n4. Exit\nChoose: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string desc;
            cout << "Enter task description: ";
            getline(cin, desc);
            add_task(desc);
            cout << "Task added.\n";
        } else if (choice == 2) {
            view_tasks();
        } else if (choice == 3) {
            int num;
            cout << "Enter task number to mark as done: ";
            cin >> num;
            mark_done(num);
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
