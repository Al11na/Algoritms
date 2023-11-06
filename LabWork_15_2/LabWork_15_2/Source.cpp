#include <iostream>
#include <fstream> 
#include <string>
#include <conio.h>

using namespace std;

struct Student {
	string fullName;
	int group;
	int grades[5];
};

template<typename type>
void addItem(type*& arr, unsigned int& size, const type item);

template<typename type>
bool contains(const type* arr, const unsigned int size, const type item);

string to_size(string str, unsigned int len);

Student makeNewStudent();

void showStudentInfo(const Student student);

void showStudentsWithMeanGradeAbove(const Student* students, const unsigned int number, const long double meanGrade = 4.0);

void showStudentsFromSameGroups(const Student* students, const unsigned int number);

void showStudentsTable(const Student* students, const unsigned int& number, 
					   const unsigned int& fullNameLen = 30, const unsigned int& groupLen = 10, const unsigned int& gradesLen = 9);

void loadStudentsFromFile(const string file_name, Student*& students, unsigned int& number);

void saveStudentsInFile(const string file_name, const Student* students, const unsigned int number);

int main() {

	setlocale(LC_ALL, "rus");
	system("chcp 1251");

	string file_name = "students.txt";

	Student* students = new Student[0];
	unsigned int size = 0;

	loadStudentsFromFile(file_name, students, size);

	bool exit = false;
	while (!exit) {

		cout << "\nНажмите любую клавишу, чтобы перейти к меню";
		_getch();
		system("cls");

		cout << "1. Добавить студента;" << endl
			<< "2. Просмотреть всех студентов;" << endl
			<< "3. Просмотреть студентов с оценкой выше данной;" << endl
			<< "4. Просмотреть студентов, находящихся в одной группе;" << endl
			<< "5. Прекратить работу программы;" << endl
			<< "6. Сохранить студентов;" << endl
			<< "7. Загрузить сохранение;" << endl
			<< "Введите номер команды - ";
		int command;
		cin >> command;

		system("cls");

		if (command == 1) {
			addItem(students, size, makeNewStudent());
		}
		else if (command == 2) {
			showStudentsTable(students, size);
		}
		else if (command == 3) {
			float grade;
			cout << "Введите оценку - ";
			cin >> grade;

			system("cls");

			showStudentsWithMeanGradeAbove(students, size, grade);
		}
		else if (command == 4) {
			showStudentsFromSameGroups(students, size);
		}
		else if (command == 5) {
			exit = true;
			delete[] students;
			system("cls");
		}
		else if (command == 6) {
			saveStudentsInFile(file_name, students, size);
			cout << "Данные студентов успешно сохранены" << endl;
		}
		else if (command == 7) {
			delete[] students;
			students = new Student[0];
			size = 0;
			
			loadStudentsFromFile(file_name, students, size);
			
			cout << "Данные сохранения успешно загружены" << endl;
		}
		else {
			cout << "Введена неверная команда";
		}
	}



	return 0;
}


template<typename type>
void addItem(type*& arr, unsigned int& size, const type item) {
	size++;
	type* newArr = new type[size];

	for (unsigned int i = 0; i < size - 1; i++) {
		newArr[i] = arr[i];
	}
	newArr[size - 1] = item;

	delete[] arr;

	arr = newArr;
}

template<typename type>
bool contains(const type* arr, const unsigned int size, const type item)
{
	for (unsigned int i = 0; i < size; i++) {
		if (arr[i] == item) {
			return true;
		}
	}

	return false;
}


string to_size(string str, unsigned int len) {
	if (str.length() > len) {
		str = str.substr(0, len);
	}
	else {
		str.insert(0, string((len - str.length()) / 2, ' '));
		str.append(string(len - str.length(), ' '));
	}
	return str;
};

Student makeNewStudent() {
	Student newStudent;

	cin.ignore(32432, '\n');

	cout << "Введите ФИО студента: ";
	getline(cin, newStudent.fullName);

	cout << "Введите номер группы: ";
	cin >> newStudent.group;

	cout << "Введите 5 оценок: ";
	for (int i = 0; i < 5; i++) {
		cin >> newStudent.grades[i];
	}

	return newStudent;
}

void showStudentInfo(const Student student) {
	cout << "Информация о студенте:" << endl
		<< "ФИО - " << student.fullName << endl
		<< "Группа - " << student.group << endl
		<< "Оценки: ";
	for (int i = 0; i < 5; i++) {
		cout << student.grades[i] << " ";
	}
	cout << endl << endl;
}

void showStudentsWithMeanGradeAbove(const Student* students, const unsigned int number, const long double meanGrade) {
	Student* foundStudents = new Student[0];
	unsigned int size = 0;

	for (unsigned int i = 0; i < number; i++) {
		long double studentMeanGrade = 0.;
		for (int j = 0; j < 5; j++) {
			studentMeanGrade += students[i].grades[j];
		}
		studentMeanGrade /= 5;
		if (studentMeanGrade > meanGrade) {
			addItem(foundStudents, size, students[i]);
		}
	}

	showStudentsTable(foundStudents, size);

	delete[] foundStudents;
}

void showStudentsFromSameGroups(const Student* students, const unsigned int number) {

	int* shownGroups = new int[0];
	unsigned shownGroupsNumber = 0;

	Student* foundStudents = new Student[0];
	unsigned int size = 0;

	for (unsigned int i = 0; i < number; i++) {
		if (!contains(shownGroups, shownGroupsNumber, students[i].group)) {

			addItem(shownGroups, shownGroupsNumber, students[i].group);
			unsigned int count = 0;

			for (unsigned int j = i + 1; j < number; j++) {
				if (students[i].group == students[j].group) {
					addItem(foundStudents, size, students[j]);
					count++;
				}
			}

			if (count > 0) {
				addItem(foundStudents, size, students[i]);
			}
		}
	}

	showStudentsTable(foundStudents, size);

	delete[] foundStudents;
}

void showStudentsTable(const Student* students, const unsigned int& number, const unsigned int& fullNameLen, const unsigned int& groupLen, const unsigned int& gradesLen) {
	for (int i = 0; i < fullNameLen + groupLen + gradesLen + 4; i++) {
		cout << "—";
	}
	cout << endl;

	cout << '|' << to_size("ФИО", fullNameLen) << '|' << to_size("Группа", groupLen) << '|' << to_size("Оценки", gradesLen) << '|' << endl;

	for (int i = 0; i < number; i++) {

		for (int j = 0; j < fullNameLen + groupLen + gradesLen + 4; j++) {
			cout << "—";
		}
		cout << endl;

		Student student = students[i];
		cout << '|';

		string fullName = student.fullName;
		fullName = to_size(fullName, fullNameLen);
		cout << fullName << '|';

		string group = to_string(student.group);
		group = to_size(group, groupLen);
		cout << group << '|';

		string grades;
		for (int j = 0; j < 4; j++) {
			grades.append(to_string(student.grades[j]));
			grades.append(" ");
		}
		grades.append(to_string(student.grades[4]));
		grades = to_size(grades, gradesLen);
		cout << grades << '|';

		cout << endl;
	}

	for (int i = 0; i < fullNameLen + groupLen + gradesLen + 4; i++) {
		cout << "—";
	}
	cout << endl;
}

void loadStudentsFromFile(const string file_name, Student*& students, unsigned int& number) {
	ifstream file(file_name, ios::in);

	int size;
	file >> size;

	for (int i = 0; i < size; i++) {
		Student student;

		file.ignore(32432, '\n');
		getline(file, student.fullName);
		file >> student.group;
		for (int j = 0; j < 5; j++) {
			file >> student.grades[j];
		}

		addItem(students, number, student);
	}
}

void saveStudentsInFile(const string file_name, const Student* students, const unsigned int number) {
	ofstream file(file_name, ios::out);

	file << number << endl;

	for (int i = 0; i < number; i++) {
		Student student = students[i];

		file << student.fullName << endl
			 << student.group << endl;
		for (int j = 0; j < 4; j++) {
			file << student.grades[j] << ' ';
		}
		file << student.grades[4] << endl;
	}
}


