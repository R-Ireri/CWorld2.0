#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    int id;
    string description;
    bool isComplete;

    Task(int _id, string _description, bool _isComplete) 
        : id(_id), description(_description), isComplete(_isComplete) {}
};

class ToDoList {
private:
    vector<Task> tasks;
    string filename;
    int nextId;

public:
    ToDoList() : filename("tasks.txt"), nextId(1) {
        loadTasks();
    }

    ~ToDoList() {
        saveTasks();
    }

    void addTask(const string &description) {
        tasks.push_back(Task(nextId++, description, false));
        cout << "Task added successfully!" << endl;
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks in your to-do list." << endl;
            return;
        }
        cout << "ID\tDescription\t\tStatus" << endl;
        cout << "---------------------------------------------" << endl;

        // Use a traditional for loop to iterate through tasks
        for (size_t i = 0; i < tasks.size(); ++i) {
            const Task& task = tasks[i];
            cout << task.id << "\t" << task.description 
                 << "\t\t" << (task.isComplete ? "Complete" : "Incomplete") << endl;
        }
    }

    void markTaskComplete(int id) {
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].id == id) {
                tasks[i].isComplete = true;
                cout << "Task marked as complete!" << endl;
                return;
            }
        }
        cout << "Task ID not found!" << endl;
    }

    void deleteTask(int id) {
        for (vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == id) {
                tasks.erase(it);
                cout << "Task deleted successfully!" << endl;
                return;
            }
        }
        cout << "Task ID not found!" << endl;
    }

private:
    void loadTasks() {
        ifstream file(filename.c_str());
        if (!file.is_open()) return;

        int id;
        string description;
        bool isComplete;

        while (file >> id >> isComplete) {
            file.ignore();  // Ignore the whitespace
            getline(file, description);
            tasks.push_back(Task(id, description, isComplete));
            nextId = (nextId > id) ? nextId : id + 1;  // Ensure unique IDs
        }

        file.close();
    }

    void saveTasks() const {
        ofstream file(filename.c_str());
        for (size_t i = 0; i < tasks.size(); ++i) {
            file << tasks[i].id << " " << tasks[i].isComplete << " " << tasks[i].description << endl;
        }
        file.close();
    }
};

void showMenu() {
    cout << "\nTo-Do List Menu:" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Mark Task as Complete" << endl;
    cout << "4. Delete Task" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    ToDoList toDoList;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();  // Ignore newline character left in the input buffer

        switch (choice) {
            case 1: {
                string description;
                cout << "Enter task description: ";
                getline(cin, description);
                toDoList.addTask(description);
                break;
            }
            case 2:
                toDoList.viewTasks();
                break;
            case 3: {
                int id;
                cout << "Enter task ID to mark as complete: ";
                cin >> id;
                toDoList.markTaskComplete(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter task ID to delete: ";
                cin >> id;
                toDoList.deleteTask(id);
                break;
            }
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}

