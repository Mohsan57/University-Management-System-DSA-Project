#pragma once
#include"Registration office.h"
#include"HOD.h"
#include"Functions.h"

struct STU_NODE {
	int SAP_ID;		//For Store Sap ID
	string Email;		// For store Email
	int Students_Passwords;	// for store Passwords
	string Take_Students_Programes;	// Programes Stores
	STU_NODE* next;
	STU_NODE* prev;
};
struct STU_COUR {
	string Take_Student_courses;	//	 Courses
	int courses_credit_hour;	//	Credit Hour
	STU_COUR* next;
};

class Students :public Registration_office, private HOD {
protected:
	STU_NODE* stu_head;
	STU_NODE* stu_tail;
	STU_COUR* cour_head;
	STU_COUR* cour_tail;

	string Programes;
	//	Basic
	string First_Name, Last_Name;
	string Country, State;
	string City;
	unsigned long int Zip_Code;
	string Address;
	unsigned long int Phone_No;
	int Temp_Sap;
	//	DOB
	int day;
	int month;
	int year;
	int semes;
	int Semester_No;
	int position;
public:
	Students() {
		day = month = year = semes = Semester_No = position = 0;
		Zip_Code = Phone_No = 0;
		Temp_Sap = 0;
		cour_head = cour_tail = NULL;
		stu_head = stu_tail = NULL;
	}

	void New_Student_Input();	// if new student Register he Enter his id on it and Fill Requirments
	bool old_Student();		//	Login with Email and password that provided
	void Store_SAP_in_list();	//	Store Email, Sap id and password in the list
	void Register_New_Semester();	// Register new semester
	bool Repetition_of_taking_courses(string, int);	// Check Course Repeat or not
	void Display_Student_Basic_Information();	//	Display Student Info
	void store_Course_in_list(int, string, int);
	void show_Transcript();	// Show marks of student
	void stu_push_back(int, string, int ,string);
	bool specific_info(int, string, int);
	int total_credithour();
	void courses_push_back(string, int);
};


void Students::New_Student_Input() {
	int id;
	if (Registration_office::reg_front!=NULL) {	// If Student Not Register
		cout << "\t\t\tEnter Your Student ID: ";
		cin >> id;
		int position = 0;
		bool bol = Registration_office::check_Enter_ids(id, &Programes);
		
		if (bol == true) {	// If ID exist
			int ids = 7001;		// For auto create SAP ID
			cin.ignore();
			cout << "\t\t\tEnter Your First Name: ";
			getline(cin, First_Name);
			Charcter_Remover(First_Name, ' ', '.');
			cout << "\t\t\tEnter Your Last Name: ";
			getline(cin, Last_Name);
			Charcter_Remover(Last_Name, ' ', '.');
			while (true) {
				cout << "\t\t\tEnter DOB (dd mm yyyy):" << endl << "\t\t\t\t";	// Check Date
				cin >> day >> month >> year;
				if (day <= 31 && day > 0 && month > 0 && month <= 12)
					break;
			}

			cout << "\t\t\tEnter Phone No: ";
			cin >> Phone_No;
			cout << "\t\t\tEnter Country: ";
			cin >> Country;
			cout << "\t\t\tEnter State: ";
			cin >> State;
			cout << "\t\t\tEnter Zip Code: ";
			cin >> Zip_Code;
			cin.ignore();
			cout << "\t\t\tEnter Street Address: ";
			getline(cin, Address);
			Charcter_Remover(Address, ' ', '.');	// Remove space
			Store_SAP_in_list();
			if (stu_head!=NULL) {
				ids = stu_tail->SAP_ID;
				ids++;
			}
			cout << "\t\t\tYour SAP ID: " << ids << endl;
			string email = to_string(ids) + "@student.edu.uol.pk";
			cout << "\t\t\tYour Email ID: " << email << endl;	// Auto Create Email Address
			int New_pass;
			int confirm_pass;
			while (true)	// Password Create
			{
				cout << "\n\n\t\t\tCreate new password(Only Number): ";
				New_pass=passw();
				cout << "\t\t\tConfirm Password: ";
				confirm_pass=passw();
				if (New_pass == confirm_pass)
					break;
				else cout << "\n\t\t\t\tNot Match Password!" << (char)2 << endl;
			}

			ofstream file;
			file.open("Students Sap ID.txt", ios::app);	// Store All data Variable to files
			file << ids << "\t" << email << "\t" << confirm_pass << "\t" << Programes << endl;
			file.close();


			file.open("Students Information.txt", ios::app);
			file << ids << "\t" << First_Name << "\t" << Last_Name << "\t" << day << "\t" << month << "\t" << year << "\t"
				<< Phone_No << "\t" << Country << "\t" << State << "\t" << Zip_Code << "\t" << Address << endl;
			file.close();
		}
		else cout << "\n\nWrong Student ID" << endl;
	}
	else cout << "\nFirst Visit Registration Office " << endl;
}

void Students::Store_SAP_in_list() {
	//	Delete All data in Linked list
	STU_NODE* temp ;
	while (stu_head != NULL) {
		temp = stu_head;
		stu_head = stu_head->next;
		free(temp);
	}
	//***************************
	ifstream file("Students Sap ID.txt");	// read data in file
	string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			istringstream info(line);
			int sap;
			int pass;
			string email;
			string pro;
			info >> sap >> email >> pass >> pro;	// First Store in Variables then in list
			stu_push_back(sap, email, pass, pro);
		}
	}
	else cout << "First Register YourSlef" << endl;
	file.close();
}

void Students::stu_push_back(int sap, string email, int pass, string pro) {
	STU_NODE* newNode = new STU_NODE();
	newNode->SAP_ID = sap;
	newNode->Email = email;
	newNode->Students_Passwords = pass;
	newNode->Take_Students_Programes = pro;
	newNode->prev = newNode->next = NULL;
	if (stu_head == NULL) {
		stu_head = stu_tail = newNode;
		stu_head->prev = NULL;
		stu_tail->next = NULL;
	}
	else {
		stu_tail->next = newNode;
		newNode->prev = stu_tail;
		stu_tail = newNode;
		stu_tail->next = NULL;
	}
}

bool Students::old_Student() {
	string email;
	cout << "Enter Email: ";
	cin >> email;
	int pass;
	cout << "Enter Password: ";
	pass=passw();
	Store_SAP_in_list();
	position = email.find('@');	// Checking Sap ID in Email
	string sap_string = email.substr(0, position);
	istringstream info(sap_string);
	info >> Temp_Sap;
	bool bol = specific_info(Temp_Sap, email, pass);
	if (bol == true) {
		return true;
	}
	else { cout << "\t\t\t\tTry Again" << (char)2 << endl; return false; }
}

void Students::Register_New_Semester() {
	int a = 1;
	string fail_course;
	cout << "Register New Semester:" << endl;
	cout << "Enter Semester No: ";
	cin >> Semester_No;
	string file_name = Programes + " ";
	file_name += to_string(Semester_No) + ".txt";
	ifstream file;
	file.open(file_name);
	if (file.is_open()) {
		cout << "\t\t\tAviable Courses in \'" << Programes << "\' Semester \'" << Semester_No << "\'" << endl;

		HOD::Display_Subjects(file_name, 0); // Show Available Courses And Store in list
		string file_Name_of_course_store = Programes + " " + to_string(Semester_No) + " Students.txt";

		if (Semester_No == 1) { // If New Student Register Course in First Semester
				// Auto Register All Courses
			ofstream file2;
			file2.open(file_Name_of_course_store, ios::app);
			bool bol = Repetition_of_taking_courses(file_Name_of_course_store, Temp_Sap);
			if (bol == true) {
				file2 << Temp_Sap << "\t" << Semester_No;

				HOD_NODE* hod_node = hod_head;
				if(hod_node!=NULL){
					while (hod_node!=NULL) {
						file2 << "\t" << hod_node->subjet_Names << "\t" << hod_node->creadit_hour;
						hod_node = hod_node->next;
					}
				}
				file2 << endl;
			}
			else cout << "\t\t\tYou alredy Register in This Semester" << (char)2 << endl;
			file2.close();
		}
		else {	// if Student want to Register antore Semester
			cin.ignore();
			string temp_store = "";
			ofstream file2;
			file2.open(file_Name_of_course_store, ios::app);

			string Courses;
			bool bol = Repetition_of_taking_courses(file_Name_of_course_store, Temp_Sap);	// Check the Student Already Register OR not
			if (bol == true) {

				cout << "\t\t\t\tEnter Course Name That you want Take Register" << endl;
				cout << "\t\tall(): for Take All courses if Credit hour are less or equal " << HOD::student_take_credit_hour << endl;
				cout << "\t\t\texit(): for Exit()" << endl;
				while (true) {
					cout << "\t\t\t\tEnter Course Name: ";
					getline(cin, Courses);
					int t = 0;
					int temp_store_size_of_credit_hour = total_credithour();

					if (Courses == "all()") {	// if student enter All() then Automatic all Courses Register
						HOD_NODE* hod_node = hod_head;
						if (hod_node!=NULL) {
							if (temp_store_size_of_credit_hour <= HOD::student_take_credit_hour) {
								file2 << Temp_Sap << "\t" << Semester_No;
								
								
								if (hod_node != NULL) {
									while (hod_node != NULL) {
										file2 << "\t" << hod_node->subjet_Names << "\t" << hod_node->creadit_hour;
										hod_node = hod_node->next;
									}
								}

								file2 << endl;

								break;
								cout << "\n\t\t\tcongratulations You Register All Courses " << (char)1 << endl;
							}
							else {
								t = 1;
							}
						}
						else t = 1;
					}
					if (t == 1) {				// If course Greater Then HOD Privade Credit hour
						cout << "\t\tSorry You only can Register \'" << HOD::student_take_credit_hour << "\' Hour And this Semester contains \'" << temp_store_size_of_credit_hour << "\'" << endl;
						cout << "\n\t\t\tPlease Register One by One Course" << endl;
					}
					if (Courses == "exit()") {
						cout << "\t\t\t\tGood bye()" << endl;
						file2 << endl;
						break;
					}
					else {						// If student want One by One course Register
						vector<string> temp_course_store;
						ifstream file3(file_Name_of_course_store);
						string line2;
						while (getline(file3, line2)) {
							string temp;
							istringstream info(line2);
							info >> temp;
							Charcter_Remover(temp, '.', ' ');
							temp_course_store.push_back(temp);
						}
						bool condition = true;
						file3.close();
						for (int i = 0; i < temp_course_store.size(); i++) {
							if (Courses == temp_course_store[i]) {
								condition = false;
							}

						}
						if (condition == false) {
							cout << "\n\t\t\tThis Course Already Register " << (char)1 << endl;
						}
						if (condition == true) {
							condition = false;
							HOD_NODE* tmp = hod_head;
							while (tmp != NULL) {
								if (a == 1) {
									file2 << Temp_Sap << "\t" << Semester_No;
									a++;
								}

								if (Courses == tmp->subjet_Names) {
									condition = true;
									temp_store = Courses;
									Charcter_Remover(tmp->subjet_Names, ' ', '.');
									file2 << "\t" << tmp->subjet_Names << "\t" << tmp->creadit_hour;
								}
								tmp = tmp->next;
							}
							if (condition == false) {
								cout << "\t\t\t Invalid Course Name " << (char)1 << endl;
							}
						}
					}
				}
			}
			else cout << "\t\t\t\tYou already Register in this Course " << (char)2 << endl;
			file2.close();
		}
	}
	else cout << "\t\t\t\tThis Semester is Not Aviable till HOD created it. " << (char)2 << endl;
	file.close();
}

void Students::store_Course_in_list(int sap = 0, string file_name_out_of_class = "", int a = 1) {
	//	Delete All data in Linked list
	STU_COUR* temp;
	while (cour_head != NULL) {
		temp = cour_head;
		cour_head = cour_head->next;
		free(temp);
	}
	//***************************
	if (a == 1) {
		cout << "Enter Semester No: ";
		cin >> semes;
	}
	string file_name;
	if (file_name_out_of_class.empty()) {	//create File Name
		file_name = Programes + " " + to_string(semes) + " Students.txt";
		
	}
	else file_name = file_name_out_of_class;
	ifstream file(file_name);
	if (file.is_open()) {
		string line;
		int temp_sap=0;
		int temp_sem=0;
		string temp_cours[8];
		int temp_cred[8];
		if (a == 1) {
			sap = Temp_Sap;
		}
		while (getline(file, line)) {
			istringstream info(line);
			info >> temp_sap;
			info >> temp_sem;
			if (temp_sap == sap) {
				for (auto i = 0; i < 8; i++) {
					info >> temp_cours[i] >> temp_cred[i];
				}
			}
		}
		cout << "\t\t\tSap: " << sap << endl;
		cout << "\t\t\tSemester: " << temp_sem << endl;
		for (int i = 0; i < 8; i++) {
			if (temp_cours[i].empty()) {
				break;
			}
			Charcter_Remover(temp_cours[i], '.', ' ');
			{

			}
			courses_push_back(temp_cours[i], temp_cred[i]);
		}
	}
	else cout << "You Not Register This Semester still " << (char)2 << endl;
	file.close();
}

bool Students::specific_info(int sap, string email, int pass) {
	STU_NODE* temp = stu_head;
	if (temp != NULL) {
		while (temp != NULL) {
			if (temp->Email == email && temp->SAP_ID == sap && temp->Students_Passwords == pass) {
				Programes = temp->Take_Students_Programes;
				return true;
			}
			temp=temp->next;
		}
	}
	return false;
}

bool Students::Repetition_of_taking_courses(string File_Name, int  Sap_ID_of_Student) {
	ifstream file(File_Name);	// Check Repeat data in File
	string line;
	bool bol = true;
	if (file.is_open()) {
		while (getline(file, line)) {
			istringstream info(line);
			int sap;
			info >> sap;
			if (sap == Sap_ID_of_Student) {
				bol = false;
			}
		}
	}
	file.close();
	return bol;
}

int Students::total_credithour() {
	HOD_NODE* temp = hod_head;
	int hour = 0;
	if (temp != NULL) {
		while (temp!=NULL) {
			hour += temp->creadit_hour;
			temp = temp->next;
		}
	}
	return hour;
}

void Students::courses_push_back(string course,int creadit) {
	STU_COUR* newNode = new STU_COUR();
	newNode->Take_Student_courses = course;
	newNode->courses_credit_hour = creadit;
	newNode->next = NULL;
	if (cour_head == NULL) {
		cour_head = cour_tail = newNode;
	}
	else {
		cour_tail->next = newNode;
		cour_tail = newNode;
		cour_tail->next = NULL;
	}
}

void Students::Display_Student_Basic_Information() {
	ifstream file("Students Information.txt");	// Read Data in File
	string line;
	int Sap;
	while (getline(file, line)) {
		istringstream info(line);
		info >> Sap >> First_Name >> Last_Name >> day >> month >> year >> Phone_No >> Country >> State >> Zip_Code >> Address;
		if (Sap == Temp_Sap) {
			Charcter_Remover(First_Name, '.', ' ');
			cout << "\t\t\t\tFirst Name: " << First_Name << endl;
			Charcter_Remover(Last_Name, '.', ' ');
			cout << "\t\t\t\tLast Name: " << Last_Name << endl;
			cout << "\t\t\t\tDate of Birth: " << day << ":" << month << ":" << year << endl;
			cout << "\t\t\t\tPhone No: " << Phone_No << endl;
			cout << "\t\t\t\tCountry: " << Country << endl;
			cout << "\t\t\t\tStat: " << State << endl;
			cout << "\t\t\t\tZip Code: " << Zip_Code << endl;
			Charcter_Remover(Address, '.', ' ');
			cout << "\t\t\t\tAddress: " << Address << endl;
		}
	}
	file.close();
}
