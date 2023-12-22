#pragma once
#include "TeacherForm.h"
#include "MenuForm.h"
#include "StudentManagement.h"

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

vector<Student*> studentss;
vector<Teacher*> teacherss;

Teacher* new_teacher;
int num_in_vec2;

System::Void lab8::TeacherForm::TeacherForm_Load(System::Object^ sender, System::EventArgs^ e) {

	readStudentsFromFile(studentss, "students.txt");
	readTeachersFromFile(teacherss, studentss, "teachers.txt", "courses.txt");

	sortStudentsByRating(studentss);

	for (auto teach : teacherss)
	{
		num_in_vec2++;
		if (teach->get_id() == id_teacher)
		{
			new_teacher = teach;
			break;
		}
	}


	label1->Text = marshal_as < String^>("Доброго дня, " + new_teacher->get_name());

	textBox1->Text = msclr::interop::marshal_as<String^>(new_teacher->get_name());
	textBox2->Text = msclr::interop::marshal_as<String^>(to_string(new_teacher->get_age()));
	textBox3->Text = msclr::interop::marshal_as<String^>(to_string(new_teacher->get_id()));
	textBox4->Text = msclr::interop::marshal_as<String^>(new_teacher->get_email());
	textBox5->Text = msclr::interop::marshal_as<String^>(new_teacher->get_phone_number());
	textBox6->Text = msclr::interop::marshal_as<String^>(new_teacher->get_teaching_experience());

	textBox7->Text = msclr::interop::marshal_as<String^>(new_teacher->get_course()->get_name());
	textBox8->Text = msclr::interop::marshal_as<String^>(to_string(new_teacher->get_course()->get_course_code()));
	textBox9->Text = msclr::interop::marshal_as<String^>(to_string(new_teacher->get_course()->get_maxStudent()));
	textBox10->Text = msclr::interop::marshal_as<String^>(to_string(new_teacher->get_course()->get_studentMap().size()));

	for (auto pair : new_teacher->get_course()->get_studentMap())
	{
		listBox1->Items->Add(msclr::interop::marshal_as<String^>("Ім'я: " + pair.first->get_name()) + ", Id: " + pair.second);
	}

}

System::Void lab8::TeacherForm::TeacherForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	writeStudentsToFile(studentss, "students.txt");
	writeTeacherToFile(teacherss, "teachers.txt");
	saveCoursesToFile(teacherss, "courses.txt");

	Application::Exit();
}

System::Void lab8::TeacherForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	new_teacher->get_course()->save_course_info();
	MessageBox::Show(this, "Курс успішно збережнено у файл Course_" + marshal_as<String^>(new_teacher->get_course()->get_name()) + ".txt", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void lab8::TeacherForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {

	new_teacher->set_name(marshal_as<string>(textBox1->Text));
	new_teacher->set_age(Convert::ToInt64(textBox2->Text));

	new_teacher->set_id(Convert::ToInt64(textBox3->Text));

	new_teacher->add_info(marshal_as<string>(textBox4->Text),
		marshal_as<string>(textBox5->Text),
		marshal_as<string>(textBox6->Text));

	writeTeacherToFile(teacherss, "teachers.txt");
	MessageBox::Show(this, "Інформація про " + marshal_as<String^>(new_teacher->get_name()) + " збережена", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void lab8::TeacherForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
	int id;
	for (int i = 0; i < listBox1->Items->Count; i++)
	{
		if (listBox1->SelectedIndices->Contains(i))
		{
			String^ item = listBox1->Items[i]->ToString();
			std::string itemStr = marshal_as<std::string>(item);

			size_t pos = itemStr.find("Id:");
			if (pos != std::string::npos)
			{
				std::string idStr = itemStr.substr(pos + 3);
				id = std::stoi(idStr);
				break;
			}
		}
	}

	for (auto pair : new_teacher->get_course()->get_studentMap())
	{
		if (pair.second == id)
		{
			StudentManagement^ stud_mag_form = gcnew StudentManagement(pair.first);
			stud_mag_form->Show();
		}
	}
}

System::Void lab8::TeacherForm::button4_Click(System::Object^ sender, System::EventArgs^ e) {

	int id;
	for (int i = 0; i < listBox1->Items->Count; i++)
	{
		if (listBox1->SelectedIndices->Contains(i))
		{
			String^ item = listBox1->Items[i]->ToString();
			std::string itemStr = marshal_as<std::string>(item);

			size_t pos = itemStr.find("Id:");
			if (pos != std::string::npos)
			{
				std::string idStr = itemStr.substr(pos + 3);
				id = std::stoi(idStr);
				break;
			}
		}
	}

	for (auto pair : new_teacher->get_course()->get_studentMap())
	{
		if (pair.second == id)
		{
			*new_teacher->get_course() - pair.first;
			MessageBox::Show(this, "Студента " + marshal_as<String^>(pair.first->get_name()) + " успішно відраховано", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);

			listBox1->Items->Clear();
			for (auto pair : new_teacher->get_course()->get_studentMap())
			{
				listBox1->Items->Add(marshal_as<String^>("Ім'я: " + pair.first->get_name()) + ", Id: " + pair.second);
			}
		}
	}


}

System::Void lab8::TeacherForm::button5_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult result = MessageBox::Show(
		"Ви точно хочете видалити себе із системи?",
		"Підтвердження",
		MessageBoxButtons::YesNo,
		MessageBoxIcon::Question
	);

	// Перевірка вибору користувача
	if (result == System::Windows::Forms::DialogResult::Yes) {
		delete_item(teacherss, num_in_vec2);
		Application::Exit();
	}
	else {

	}
}