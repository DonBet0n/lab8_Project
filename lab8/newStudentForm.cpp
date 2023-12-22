#include "newStudentForm.h"
#include "StudentForm.h"
#include "TeacherForm.h"
#include "MenuForm.h"

#include "Human.h"
#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "GroupMonitor.h"
#include "Department.h"

#include <msclr/marshal_cppstd.h>
#include <string>

#include "command.h"

using namespace msclr::interop;

vector<Student*> studentssss;
vector<Teacher*> teacherssss;

Student* new_studentt;
int num_in_vec3 = NULL;

System::Void lab8::newStudentForm::newStudentForm_Load(System::Object^ sender, System::EventArgs^ e) {
	readStudentsFromFile(studentssss, "students.txt");
	readTeachersFromFile(teacherssss, studentssss, "teachers.txt", "courses.txt");

	sortStudentsByRating(studentssss);

	for (auto stud : studentssss)
	{
		num_in_vec3++;
		if (stud->get_id() == id_student)
		{
			new_studentt = stud;
			break;
		}
	}
	textBox3->Text = Convert::ToString(id_student);

	/*for (auto pair : new_studentt->grade_stud)
	{
		listBox1->Items->Add(msclr::interop::marshal_as<String^>("Предмет: " + pair.first) + ", Оцінка: " + pair.second);
	}*/

	for (auto teach : teacherssss)
	{
		listBox2->Items->Add(msclr::interop::marshal_as<String^>("Викладач: " + teach->get_name() + ", Крус: " + teach->get_course()->get_name()));
	}
}

System::Void lab8::newStudentForm::button4_Click(System::Object^ sender, System::EventArgs^ e) {
	Student* student = new Student();
	new_studentt = student;
	new_studentt->set_name(marshal_as<string>(textBox1->Text));
	new_studentt->set_age(Convert::ToInt64(textBox2->Text));

	new_studentt->add_info(Convert::ToInt64(textBox3->Text), marshal_as<string>(textBox4->Text),
		marshal_as<string>(textBox5->Text));

	studentssss.push_back(new_studentt);

	writeStudentsToFile(studentssss, "students.txt");
	button1->Enabled = true;
	button2->Enabled = true;
	button3->Enabled = true;
	MessageBox::Show(this, "Інформація про " + marshal_as<String^>(new_studentt->get_name()) + " збережена", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
	studentssss.clear();
	readStudentsFromFile(studentssss, "students.txt");
}

System::Void lab8::newStudentForm::newStudentForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	writeStudentsToFile(studentssss, "students.txt");
	writeTeacherToFile(teacherssss, "teachers.txt");
	saveCoursesToFile(teacherssss, "courses.txt");

	Application::Exit();
}

System::Void lab8::newStudentForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedText = listBox2->SelectedItem->ToString();
	size_t colonIndex = marshal_as<wstring>(selectedText).find(L', Курс:');

	if (colonIndex != wstring::npos) {
		// Отримання значень teachname та coursename
		String^ teachname = selectedText->Substring(10, colonIndex - 10)->Trim();
		String^ coursename = selectedText->Substring(colonIndex + 8)->Trim();

		for (auto teach : teacherssss)
		{
			if (teach->get_name() == marshal_as<string>(teachname)
				&& marshal_as<string>(coursename) == teach->get_course()->get_name())
			{
				*teach->get_course() + new_studentt;
				MessageBox::Show("Вас успішно зареєстровано на курс " + marshal_as<String^>(teach->get_course()->get_name()));
				break;
			}
		}
	}
}
System::Void lab8::newStudentForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedText = listBox2->SelectedItem->ToString();
	size_t colonIndex = marshal_as<wstring>(selectedText).find(L', Курс:');

	if (colonIndex != wstring::npos) {
		// Отримання значень teachname та coursename
		String^ teachname = selectedText->Substring(10, colonIndex - 10)->Trim();
		String^ coursename = selectedText->Substring(colonIndex + 8)->Trim();

		for (auto teach : teacherssss)
		{
			if (teach->get_name() == marshal_as<string>(teachname)
				&& marshal_as<string>(coursename) == teach->get_course()->get_name())
			{
				*teach->get_course() - new_studentt;
				MessageBox::Show("Вас успішно відписано від курсу " + marshal_as<String^>(teach->get_course()->get_name()));
				break;
			}
		}
	}
}
System::Void lab8::newStudentForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult result = MessageBox::Show(
			"Ви точно хочете видалити себе із системи?",
			"Підтвердження",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question
		);

		// Перевірка вибору користувача
		if (result == System::Windows::Forms::DialogResult::Yes) {
			delete_item(studentssss, num_in_vec3);
			Application::Exit();
		}
		else {

		}
}