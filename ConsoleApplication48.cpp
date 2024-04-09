#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>
using namespace std;

class Student {
private:
	string name;
	string group;
	int age;
public:
	Student(string name, string group, int age) : name{ name }, group{ group }, age{ age } {}

	void savetofile(const string& filename) {
		ofstream fout(filename);
		if (fout.is_open())
		{
			fout << "Student name: " << name;
			fout << "\nStudent Group: " << group;
			fout << "\nStudent age: " << age;
			fout.close();
		}
		else
		{
			throw runtime_error("Cant opened this file");
		}
	}
};
class Magazine {
private:
	vector<Student> students;
	mutex mtx;
public:

	Magazine(){}

	void AddSTUDENT(const Student& studs) {
		lock_guard<mutex> lock(mtx);
		students.push_back(studs);
		cout << "Studentds Added\n";
	}

	void SaveStudentstoFile() {
		vector<thread> threads;
		for (size_t i = 0; i < students.size(); i++)
		{
			string filename = "Journal_" + to_string(i) + ".txt";
			threads.emplace_back(&Student::savetofile, &students[i], filename);
		}
		for (auto& t : threads) {
			t.join();
		}
	}
};


int main() {
	Magazine journ1, journ2;
	journ1.AddSTUDENT(Student("Artem", "PI-22-01", 15));

	journ1.AddSTUDENT(Student("Bob", "PI-21-01", 18));
	journ1.SaveStudentstoFile();
	journ2.AddSTUDENT(Student("Mike", "Groyp b", 20));

	journ2.AddSTUDENT(Student("John", "Groyp Z", 25));
	journ2.SaveStudentstoFile();

}