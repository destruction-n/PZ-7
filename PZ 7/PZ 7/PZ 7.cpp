#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

struct student
{
	struct
	{
		string surname;
		string name;
		string patronymic;
	};
	struct
	{
		int day = 0;
		int month = 0;
		int year = 0;
		int age = 0;
	};

};
student* createStruct(int  number)
{
	int i, age = 0;
	student* arr = new student[number];
	for (i = 0; i < number; i++) {
		cout << "Введите фамилию, имя и отчество\n";
		cin >> arr[i].surname >> arr[i].name >> arr[i].patronymic;
		cout << "Введите день рождения\n";
		cin >> arr[i].day >> arr[i].month >> arr[i].year;

		time_t t = time(0);
		struct tm* T = new tm;
		localtime_s(T, &t);
		age = (T->tm_year + 1900) - arr[i].year;
		if (arr[i].month > (T->tm_mon + 1))	age--;
		else if (arr[i].month == (T->tm_mon + 1) && (arr[i].day > T->tm_mday)) age--;
		arr[i].age = age;
	}
	return arr;
}
void printStruct(student* arr, int  number)
{
	cout << "Фамилия/Имя/Отчество" << setw(10) << "День рождения" << setw(10) << "Возраст\n";
	for (int i = 0; i < number; i++)
		cout << arr[i].surname << setw(5) << arr[i].name << setw(5) << arr[i].patronymic << setw(10) << arr[i].day << "." << arr[i].month << "." << arr[i].year << setw(10) << arr[i].age << endl;
}
int findTheMostCommonName(student* arr, int number)
{
	int  count = 0, max_count = 0, positionOfName = 0, i, j;
	for (i = 0; i < number - 1; i++)
	{
		count = 0;
		for (j = i + 1; j < number; i++)
			if (arr[i].name == arr[j].name) count++;
		if (count > max_count) positionOfName = i;
	}
	return positionOfName;
}
void averageAge(student* arr, int number)
{
	double summ = 0, average = 0;
	for (int i = 0; i < number; i++)
		summ += arr[i].age;
	average = summ / number;
	cout << "Средний возраст: " << average;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int number, positionOfName;
	cout << "Введите число студентов\n";
	cin >> number;
	student* arr = createStruct(number);
	printStruct(arr, number);
	positionOfName = findTheMostCommonName(arr, number);
	if (positionOfName != 0) cout << "Самое распространённое имя: " << arr[positionOfName].name << endl;
	else cout << "Все имена различны\n";
	averageAge(arr, number);
}
