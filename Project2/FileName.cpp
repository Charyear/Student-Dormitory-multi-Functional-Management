#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    string id;
    int score;

    Student(string n = "", string i = "", int s = 0) : name(n), id(i), score(s) {}
};

class StudentManager {
private:
    vector<Student> students;
    string filename;

public:
    StudentManager(string fname) : filename(fname) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& student : students) {
                file << student.name << "," << student.id << "," << student.score << "\n";
            }
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                size_t pos1 = line.find(",");
                size_t pos2 = line.find(",", pos1 + 1);
                string name = line.substr(0, pos1);
                string id = line.substr(pos1 + 1, pos2 - pos1 - 1);
                int score = stoi(line.substr(pos2 + 1));
                students.push_back(Student(name, id, score));
            }
            file.close();
        }
    }

    void displayAll() {
        for (const auto& student : students) {
            cout << "Name: " << student.name
                 << ", ID: " << student.id
                 << ", Score: " << student.score << endl;
        }
    }
};

int main() {
    StudentManager manager("Student.txt");

    // Add some students
    manager.addStudent(Student("张三", "001", 85));
    manager.addStudent(Student("李四", "002", 92));
    manager.addStudent(Student("王五", "003", 78));

    // Save to file
    manager.saveToFile();

    // Clear and load from file
    StudentManager newManager("Student.txt");
    newManager.loadFromFile();

    // Display all students
    cout << "Students loaded from file:" << endl;
    newManager.displayAll();

    return 0;
}
