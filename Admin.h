#pragma once
#include"Functions.h"
#include"HOD.h"
#include"Student.h"

class Admin :public Students, private HOD {
protected:
	int Student_Sap_Id;
	int Marks[8];
	string file_path[8];
	int semester_No_of_student_takes[8];
	string Admin_Department;
	CEO ceo;
public:
	Admin() {
		for (int i = 0; i < 8; i++)
			Marks[i] = 0;
	}
	bool Login_Admin();	// Admin login
	void Show_Semester_of_Student();	//Show Student Semesters that he Register
	void Enter_Marks_of_Students(int);	// Admin ccan Enter Marks of Student
	bool store_Marks_in_list(string, int, int);
	void Show_Marks_of_Students();
	void Show_Department() {
		cout << "\n\n\t\t\t\tWelcome To \'" << Admin_Department << "\'" << (char)2 << endl << endl << endl;
	}
	bool check_semesterNo_ofStudents(int);
};


bool Admin::Login_Admin() {
	ceo.Store_programes_List();
	int User_ID;
	cout << "\t\t\tEnter User ID: ";
	cin >> User_ID;
	cout << "\t\t\tEnter Password: ";
	int pass=passw();
	bool bol = false;
	CEO_NODE* current = ceo.ceo_head;
	
	while (current != NULL) {
		if (current->HOD_ID == User_ID) {
			bol = true;
			Admin_Department = current->programes_names;
			
			break;
		}

		current = current->next;

	}
	if (bol == true && pass == 1234) {
		return true;
	}
	else {
		cout << "\n\t\t\t  Invalid User ID/Password!" << (char)2 << endl;
		return false;
	}
}

void Admin::Enter_Marks_of_Students(int Student_Sap_id) {
	cout << "Enter Semester No: ";
	int a;
	cin >> a;
	store_Marks_in_list("", a, Student_Sap_Id);
	cout << "work outer" << endl;
	if(Marks[0]==0){
		cout << "work inner";
		if (stu_head == NULL) {
			bool bol = check_semesterNo_ofStudents(a);
			if (bol == true) {
				string file_name = Admin_Department + " " + to_string(a) + " Students.txt";
				cout << "\t\t\t Courses That Student Register" << endl;
				Students::store_Course_in_list(Student_Sap_Id, file_name, 0);
				ofstream file;
				file_name = Admin_Department + " " + to_string(a) + " Student Marks.txt";
				file.open(file_name, ios::app);
				cout << "\t\t\t***********************************************************" << endl;
				cout << "\t\t\t\tEnter Marks of Register Coures" << endl;
				file << Student_Sap_Id << "\t";

				STU_COUR* cour = cour_head;
				if (cour != NULL) {
					while (cour != NULL) {
						int marks;
						cout << "\t\t\t\t\'" << cour->Take_Student_courses << "\' Makrs: ";
						cin >> marks;
						file << marks << "\t";
						cour = cour->next;
					}
				}
				cout << "\t\t\t***********************************************************" << endl;

				file << -1 << endl;
				file.close();
			}
		}
	}
	else {
		cout << "\t\t\t\tYou Already Enter Marks" << endl;
	}
}

bool Admin::check_semesterNo_ofStudents(int num) {
	for (int i = 0; i < 8; i++) {
		cout << semester_No_of_student_takes[i] << endl;
		if (semester_No_of_student_takes[i] == num) {
			
			return true;
		}
	}
	return false;
}

bool Admin::store_Marks_in_list(string prog = "", int semester = 0, int sap = 0) {
	for (int l = 0; l < 8; l++) {
		Marks[l] = 0;
	}
	int temp_sap;
	int i = 0;
	string file_name;
	if (prog.empty()) {
		file_name = Admin_Department + " " + to_string(semester) + " Student Marks.txt";
	}
	else file_name = prog + " " + to_string(semester) + " Student Marks.txt";
	ifstream file;
	file.open(file_name);
	string line;
	bool bol2 = true;
	bool bol = false;
	if (file.is_open()) {
		bol = true;
		while (getline(file, line)) {
			istringstream info(line);
			info >> temp_sap;
			cout << temp_sap << endl;
			cout << "Sap: " << sap << endl;
			int num = 0;
			i = 0;
			if (sap == temp_sap) {
				while (true) {
					info >> num;
					if (num == -1)
						break;
					else {
						Marks[i]=num;
						i++;
					}
				}
			}
		}
	}
	file.close();
	return bol;
}

void Admin::Show_Semester_of_Student() {
	cout << "Enter Student SAP ID: ";
	cin >> Student_Sap_Id;
	bool bol = false;
	int temp = 0;
	ifstream file;
	for (int i = 1; i <= 8; i++) {
		string file_name = Admin_Department + " " + to_string(i) + " Students.txt";
		file_path[i-1]=(file_name);
	}
	for (int i = 1; i <= 8; i++) {
		bol = false;
		file.open(file_path[i - 1]);
		if (file.is_open()) {
			string line;
			int Temp_Sap_Store;
			while (getline(file, line)) {
				istringstream info(line);
				info >> Temp_Sap_Store;
				if (Student_Sap_Id == Temp_Sap_Store)
					bol = true;
			}
			file.close();
			if (bol == true) {
				temp = 1;
				cout << "This Student Register in Semester: " << i << endl;
				semester_No_of_student_takes[i - 1] = i;
			}
		}
	}
	if (temp == 1) {
		Enter_Marks_of_Students(Student_Sap_Id);
	}
	else if (temp == 0) cout << "This Student Not Register" << (char)2 << endl;
}

void Admin::Show_Marks_of_Students() {
	store_Course_in_list(0, "", 1);
	bool bol=store_Marks_in_list(Students::Programes, semes, Temp_Sap);
	if (bol == true) {
		if (Marks[0] != 0) {
			int i = 0;
			cout << "\t\t**************************************************" << endl;
			STU_COUR* temp = cour_head;
			while (temp != NULL) {
				cout << "\t\t\tCourse: " << temp->Take_Student_courses << endl;
				cout << "\t\t\tMarks: " << Marks[i] << endl;
				cout << "\t\t\tGrade: " << Grade_set(Marks[i]) << endl;
				i++;
				temp = temp->next;
			}
			cout << "\t\t**************************************************" << endl;
		}
	}
	else cout << "Please contact Your Admin For Enter Marks " << (char)2 << endl;

}