
#include "newTeacherForm.h"
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

vector<Student*> studentsssss;
vector<Teacher*> teachersssss;

Teacher* new_teacherr;
int num_in_vec4;

System::Void lab8::newTeacherForm::newTeacherForm_Load(System::Object^ sender, System::EventArgs^ e) {

	readStudentsFromFile(studentsssss, "students.txt");
	readTeachersFromFile(teachersssss, studentsssss, "teachers.txt", "courses.txt");

	sortStudentsByRating(studentsssss);

	for (auto teach : teachersssss)
	{
		num_in_vec4++;
		if (teach->get_id() == id_teacherr)
		{
			new_teacherr = teach;
			break;
		}
	}

	textBox3->Text = Convert::ToString(id_teacherr);
}

System::Void lab8::newTeacherForm::newTeacherForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	writeStudentsToFile(studentsssss, "students.txt");
	writeTeacherToFile(teachersssss, "teachers.txt");
	saveCoursesToFile(teachersssss, "courses.txt");

	Application::Exit();
}

System::Void lab8::newTeacherForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	new_teacherr->get_course()->save_course_info();
	MessageBox::Show(this, "Курс успішно збережнено у файл Course_" + marshal_as<String^>(new_teacherr->get_course()->get_name()) + ".txt", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void lab8::newTeacherForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	Teacher* teach = new Teacher("",0);
	new_teacherr = teach;
	new_teacherr->set_name(marshal_as<string>(textBox1->Text));
	new_teacherr->set_age(Convert::ToInt64(textBox2->Text));

	new_teacherr->set_id(Convert::ToInt64(textBox3->Text));

	new_teacherr->add_info(marshal_as<string>(textBox4->Text),
		marshal_as<string>(textBox5->Text),
		marshal_as<string>(textBox6->Text));

	teachersssss.push_back(new_teacherr);

	writeTeacherToFile(teachersssss, "teachers.txt");
	MessageBox::Show(this, "Інформація про " + marshal_as<String^>(new_teacherr->get_name()) + " збережена", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
	teachersssss.clear();
	readTeachersFromFile(teachersssss, studentsssss, "teachers.txt", "courses.txt");

	button2->Enabled = true;
	button3->Enabled = true;
	button4->Enabled = true;
	button5->Enabled = true;
	button6->Enabled = true;
}

System::Void lab8::newTeacherForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
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

	for (auto pair : new_teacherr->get_course()->get_studentMap())
	{
		if (pair.second == id)
		{
			StudentManagement^ stud_mag_form = gcnew StudentManagement(pair.first);
			stud_mag_form->Show();
		}
	}
}

System::Void lab8::newTeacherForm::button4_Click(System::Object^ sender, System::EventArgs^ e) {

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

	for (auto pair : new_teacherr->get_course()->get_studentMap())
	{
		if (pair.second == id)
		{
			*new_teacherr->get_course() - pair.first;
			MessageBox::Show(this, "Студента " + marshal_as<String^>(pair.first->get_name()) + " успішно відраховано", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);

			listBox1->Items->Clear();
			for (auto pair : new_teacherr->get_course()->get_studentMap())
			{
				listBox1->Items->Add(marshal_as<String^>("Ім'я: " + pair.first->get_name()) + ", Id: " + pair.second);
			}
		}
	}


}

System::Void lab8::newTeacherForm::button5_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::DialogResult result = MessageBox::Show(
		"Ви точно хочете видалити себе із системи?",
		"Підтвердження",
		MessageBoxButtons::YesNo,
		MessageBoxIcon::Question
	);

	// Перевірка вибору користувача
	if (result == System::Windows::Forms::DialogResult::Yes) {
		delete_item(teachersssss, num_in_vec4);
		Application::Exit();
	}
	else {

	}
}

System::Void lab8::newTeacherForm::button6_Click(System::Object^ sender, System::EventArgs^ e) {
	new_teacherr->create_course(marshal_as<string>(textBox7->Text),
		Convert::ToInt64(textBox8->Text), Convert::ToInt64(textBox8->Text));
	saveCoursesToFile(teachersssss, "courses.txt");

}