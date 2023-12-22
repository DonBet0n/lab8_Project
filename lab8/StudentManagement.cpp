#include "StudentManagement.h"

#include <msclr/marshal_cppstd.h>
#include <string>

using namespace System;
using namespace msclr::interop;

System::Void lab8::StudentManagement::StudentManagement_Load(System::Object^ sender, System::EventArgs^ e) {

	StudentManagement::Text = marshal_as<String^>("Студент: " + new_student->get_name());

	for (auto pair : new_student->grade_stud)
	{
		listBox1->Items->Add(marshal_as<String^>(pair.first + ": " + to_string(pair.second)));
	}
	numericUpDown1->Value = new_student->get_rating();
}

System::Void lab8::StudentManagement::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedText = listBox1->SelectedItem->ToString();
	size_t colonIndex = marshal_as<wstring>(selectedText).find(L':');

	if (colonIndex != std::wstring::npos) {
		// Отримання значень subject та mark
		String^ subject1 = selectedText->Substring(0, colonIndex)->Trim();
		int mark1 = Convert::ToInt32(selectedText->Substring(colonIndex + 1)->Trim());


		String^ inputText = textBox1->Text;

		size_t colonIndex = marshal_as<wstring>(inputText).find(L':');
		if (colonIndex != wstring::npos) {

			String^ subject2 = inputText->Substring(0, colonIndex);
			int mark2 = Convert::ToInt32(inputText->Substring(colonIndex + 1));

			if (subject1 == subject2)
			{
				for (auto it = new_student->grade_stud.begin(); it != new_student->grade_stud.end(); ++it)
				{
					if (it->first == marshal_as<string>(subject1))
					{
						// Замінюємо значення за допомогою ітератора
						it->second = mark2;
						break;
					}
				}
			}
			else
			{
				new_student->grade_stud.insert({ marshal_as<string>(subject2) , mark2 });
			}
		
			listBox1->Items->Clear();
			for (auto pair : new_student->grade_stud)
			{
				listBox1->Items->Add(marshal_as<String^>(pair.first + ": " + to_string(pair.second)));
			}
		}
	}

	*new_student-= new_student->get_rating();
	*new_student+= (int)numericUpDown1->Value;

	MessageBox::Show(this, "Данні успішно збережені", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void lab8::StudentManagement::listBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	String^ selectedText = listBox1->SelectedItem->ToString();
	size_t colonIndex = marshal_as<wstring>(selectedText).find(L':');

	if (colonIndex != std::wstring::npos) {
		// Отримання значень subject та mark
		String^ subject = selectedText->Substring(0, colonIndex)->Trim();
		int mark = Convert::ToInt32(selectedText->Substring(colonIndex + 1)->Trim());

		textBox1->Text = subject + ": " + mark;
	}
}
