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

vector<Student*> studentsss;
vector<Teacher*> teachersss;

Student* new_student;
int num_in_vec = NULL;

System::Void lab8::StudentForm::StudentForm_Load(System::Object^ sender, System::EventArgs^ e) {

	readStudentsFromFile(studentsss, "students.txt");
	readTeachersFromFile(teachersss, studentsss, "teachers.txt", "courses.txt");

	sortStudentsByRating(studentsss);

	for (auto stud : studentsss)
	{
		num_in_vec++;
		if (stud->get_id() == id_student)
		{
			new_student = stud;
			break;
		}
	}

	StudentForm::Text = marshal_as<String^>("Студент: " + new_student->get_name());
	label1->Text = marshal_as < String^>("Доброго дня, " + new_student->get_name());

	textBox1->Text = marshal_as<String^>(new_student->get_name());
	textBox2->Text = marshal_as<String^>(to_string(new_student->get_age()));
	textBox3->Text = marshal_as<String^>(to_string(new_student->get_id()));
	textBox4->Text = marshal_as<String^>(new_student->get_email());
	textBox5->Text = marshal_as<String^>(new_student->get_phone_number());
	textBox6->Text = marshal_as<String^>(to_string(new_student->get_rating()));


	for (auto pair : new_student->grade_stud)
	{
		listBox1->Items->Add(msclr::interop::marshal_as<String^>("Предмет: " + pair.first) + ", Оцінка: " + pair.second);
	}

	for (auto teach : teachersss)
	{
		listBox2->Items->Add(msclr::interop::marshal_as<String^>("Викладач: " + teach->get_name() + ", Крус: " + teach->get_course()->get_name()));
	}
}
System::Void lab8::StudentForm::StudentForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	writeStudentsToFile(studentsss, "students.txt");
	writeTeacherToFile(teachersss, "teachers.txt");
	saveCoursesToFile(teachersss, "courses.txt");

	Application::Exit();
}

System::Void lab8::StudentForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedText = listBox2->SelectedItem->ToString();
	size_t colonIndex = marshal_as<wstring>(selectedText).find(L', Курс:');

	if (colonIndex != wstring::npos) {
		// Отримання значень teachname та coursename
		String^ teachname = selectedText->Substring(10, colonIndex - 10)->Trim();  
		String^ coursename = selectedText->Substring(colonIndex + 8)->Trim();
		
		for (auto teach : teachersss)
		{
			if (teach->get_name() == marshal_as<string>(teachname) 
				&& marshal_as<string>(coursename) == teach->get_course()->get_name())
			{
				*teach->get_course() + new_student;
				MessageBox::Show("Вас успішно зареєстровано на курс " + marshal_as<String^>(teach->get_course()->get_name()));
				break;
			}
		}
	}
	
}
System::Void lab8::StudentForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedText = listBox2->SelectedItem->ToString();
	size_t colonIndex = marshal_as<wstring>(selectedText).find(L', Курс:');

	if (colonIndex != wstring::npos) {
		// Отримання значень teachname та coursename
		String^ teachname = selectedText->Substring(10, colonIndex - 10)->Trim();
		String^ coursename = selectedText->Substring(colonIndex + 8)->Trim();

		for (auto teach : teachersss)
		{
			if (teach->get_name() == marshal_as<string>(teachname)
				&& marshal_as<string>(coursename) == teach->get_course()->get_name())
			{
				*teach->get_course() - new_student;
				MessageBox::Show("Вас успішно відписано від курсу " + marshal_as<String^>(teach->get_course()->get_name()));
				break;
			}
		}
	}
}

System::Void lab8::StudentForm::listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
System::Void lab8::StudentForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult result = MessageBox::Show(
		"Ви точно хочете видалити себе із системи?",
		"Підтвердження",
		MessageBoxButtons::YesNo,
		MessageBoxIcon::Question
	);

	// Перевірка вибору користувача
	if (result == System::Windows::Forms::DialogResult::Yes) {
		delete_item(studentsss, num_in_vec);
		Application::Exit();
	}
	else {
		
	}
}

System::Void lab8::StudentForm::button4_Click(System::Object^ sender, System::EventArgs^ e) {
	new_student->set_name(marshal_as<string>(textBox1->Text));
	new_student->set_age(Convert::ToInt64(textBox2->Text));

	new_student->add_info(Convert::ToInt64(textBox3->Text), marshal_as<string>(textBox4->Text),
		marshal_as<string>(textBox5->Text));

	writeStudentsToFile(studentsss, "students.txt");
	MessageBox::Show(this, "Інформація про " + marshal_as<String^>(new_student->get_name()) + " збережена", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
