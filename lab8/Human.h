#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Human {
protected:
	string name;
	int age;
	int id;
	string email;
	string phone_number;
public:
	Human() {};
	Human(string name, int age, int id, string email, string phone_number) :
		name(name),
		age(age),
		id(id),
		email(email),
		phone_number(phone_number) {}
	Human(const Human& other) :
		name(other.name),
		age(other.age),
		id(other.id),
		email(other.email),
		phone_number(other.phone_number) {}
	virtual ~Human() {}
	virtual void show();
	void test();
};