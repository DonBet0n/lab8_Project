#include "MenuForm.h"
#include "TeacherForm.h"
#include "StudentForm.h"
#include "newStudentForm.h"
#include "newTeacherForm.h"

#include "Human.h"
#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "GroupMonitor.h"
#include "Department.h"

#include "command.h"

#include <vector>
#include <windows.h>
#include <msclr/marshal_cppstd.h>
#include <time.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace std;



[STAThread]

void main(cli::array<System::String^>^ args)
{
	srand(time(0));
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	lab8::MenuForm form; //назва створеного проекту
	Application::Run(% form); //запуск форми
}

vector<Student*> students;
vector<Teacher*> teachers;

Department<string, Course> department;

System::Void lab8::MenuForm::MenuForm_Load(System::Object^ sender, System::EventArgs^ e) {

	readStudentsFromFile(students, "students.txt");
	readTeachersFromFile(teachers, students, "teachers.txt", "courses.txt");

	sortStudentsByRating(students);
}

System::Void lab8::MenuForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {

	int id_student = Convert::ToInt64(textBox1->Text);
	for (auto stud : students)
	{
		if (stud->get_id() == id_student)
		{
			StudentForm^ stud_form = gcnew StudentForm();
			stud_form->id_student = id_student;
			stud_form->Show();
			MenuForm::Hide();
			return;
			break;
		}
	}

	newStudentForm^ new_stud_form = gcnew newStudentForm();
	new_stud_form->id_student = id_student;
	new_stud_form->Show();
	MenuForm::Hide();

}
System::Void lab8::MenuForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {

	int id_teacher = Convert::ToInt64(textBox2->Text);
	for (auto teach : teachers)
	{
		if (teach->get_id() == id_teacher)
		{
			TeacherForm^ teach_form = gcnew TeacherForm();
			teach_form->id_teacher = id_teacher;
			teach_form->Show();
			MenuForm::Hide();
			return;
			break;
		}
	}
	newTeacherForm^ new_stud_form = gcnew newTeacherForm();
	new_stud_form->id_teacherr = id_teacher;
	new_stud_form->Show();
	MenuForm::Hide();

}