#include <iostream>
#include "Human.h"

using namespace std;

void Human::show() {
	cout << "I�'�: " << name << endl;
	cout << "�i�: " << age << endl;
	if (id != NULL || email != "" || phone_number != "")
	{
		cout << "Id: " << id << endl;
		cout << "�����: " << email << endl;
		cout << "����� ��������: " << phone_number << endl;
	}
}

void Human::test() {
	cout << "Test from Human" << endl;
}
