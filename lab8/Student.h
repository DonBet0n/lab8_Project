#pragma once

#include "Human.h"
//#include "Course.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;

class Course;

//struct grade
//{
//	string subject;
//	int mark;
//};

class Student : virtual public Human
{
public:
	Student();
	Student(string name, int age);														//Конструктор
	Student(string name, int age, int id, string email, string phone_number) :			//Конструктор ініціалізації
		Human(name, age, id, email, phone_number) {}

	Student(const Student& other) :														//Конструктор копіювання
		Human(other) {}
	
	void subscription_on_course(Course *courseName);									//Метод підписки на курс
	void unbscription_on_course(Course* courseName);
	void add_info(int id, string email, string phone_number);							//Додовання додатковї інформації
		
	using Human::test;
	void test(int i);

	void set_name(string name);
	void set_age(int age);

	string get_name();																	//Отримати ім'я студента
	int get_age();
	int get_id();
	string get_email();
	string get_phone_number();
	int get_rating();

	
	Student& operator++() {									// Перевантаження префіксного оператора "++"
		rating++;
		return *this;
	}

	Student& operator--() {									// Перевантаження префіксного оператора "--"
		rating--;
		return *this;
	}
	
	Student& operator+=(int num) {
		rating += num;
		return *this;
	}
	Student& operator-=(int num) {
		rating -= num;
		return *this;
	}

	void show() override;																//Показати інформацію про студента
	void show_grades();

	multimap<string, int> grade_stud;
	

	~Student() override;
private:
	int rating;
};
