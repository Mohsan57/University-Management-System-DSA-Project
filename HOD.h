#pragma once
#include "CEO.h"
#include "Functions.h"
struct HOD_NODE {
	string subjet_Names;
	int creadit_hour;
	HOD_NODE* next;
};
class HOD {
protected:
	string Prog_name_store;
	int pass;
	string semester_Name;
	int semester_No;
	string Temp_Subject_Name;
	CEO ceo;	// composition  Association
	static int student_take_credit_hour;	// how much student take credit hour
public:
	HOD_NODE *hod_head;
	HOD_NODE* hod_tail;
	bool login();	// HOD Login with Programe ID and Password
	void Add_Semester();	//		Create Semester
	void store_Subject_list(string, int);	// Store All Data in lists
	void Display_Subjects(string, int);	//	Display Subjects
	bool checking_subject(string);	//	Check Subject Repeatition
	bool Already_data_in_file();	//	If file is Already in file
	void credit_hour_set() {	// for set Credit hour
		cout << "How much Student Take Credit hour: ";
		cin >> student_take_credit_hour;
	}
	int total_data_in_list();
	void Arrange_All_Functions();
	void hod_push_back(string, int);
	void show_Register_Student();
	int count_credithour();
	HOD() {
		pass = 0;
		semester_Name = "";
		semester_No = 0;
		Temp_Subject_Name = "";
		hod_head = NULL;
		hod_tail = NULL;
	}
	//	Varification That HOD Are Sure Add new Subjects 
	bool Varification() {
		int a = 0;
		while (1) {
			cout << "\t\t\t\tAre You Agree \n\t\t\t0: No\t1:Yes" << endl;
			cin >> a;
			if (a == 0) {
				return false;
			}
			else if (a == 1) {
				return true;
			}
			else cout << "\t\t\t\tInvalid Input:" << (char)1 << endl;
			if (a == 1 || a == 0) {
				break;
			}
		}
		return false;
	}//
};
int HOD::student_take_credit_hour = 18;
bool HOD::login() {
	int User_ID;
	ceo.Store_programes_List();
	cout << "\t\t\tEnter User ID: ";
	cin >> User_ID;
	cout << "\t\t\tEnter Password: ";
	pass = passw();
	bool bol = false;

	CEO_NODE* current = ceo.ceo_head;
	if (ceo.ceo_head == NULL) {
		bol = false;
	}
	while (current != NULL) {
		if (current->HOD_ID == User_ID) {
			bol = true;
			Prog_name_store = current->programes_names;
		}
		current = current->next;

	}
	if (bol == true && pass == 1234) {
		cout << "\n\t\t\t\ttWelcome To \'" << Prog_name_store << "\' Depatment " << (char)2 << endl;
		return true;
	}
	else {
		cout << "\n\t\t\tInvalid User ID/Password! " << (char)2 << endl;
		return false;
	}
}

void HOD::Add_Semester() {
	cout << "\t\t\tEnter Semester No: ";
	cin >> semester_No;
	semester_Name = (string)Prog_name_store + " " += to_string(semester_No) + ".txt";	// create file name
	bool check = Already_data_in_file();	// if Already File is create and Data in file then call Vrificationn Function
	if (check == true) {
		ofstream file;
		file.open(semester_Name, ios::app);
		string subjects;
		int creadit;
		int count_creadit = 0;
		int subject_counts = 0;
		subject_counts = total_data_in_list();
		cin.ignore();
		while (subjects != "exit()") {
			cout << "\t\t\tEnter Course Name: ";
			getline(cin, subjects);
			if (subjects != "exit()") {
				bool condition = checking_subject(subjects);	// Check Subject Repeatition
				if (condition == true) {	// If Subject not Repeat
					cout << "\t\t\tEnter \'" << subjects << "\' Creadit Hour: ";
					cin >> creadit;
					Charcter_Remover(subjects, ' ', '.');
					file << subjects << "\t" << creadit << endl;
					subject_counts++;
					cin.ignore();
				}
				else if (condition == false) {	// If Subject Already in File
					cout << "\t\t\t\'" << subjects << "\' Already Register" << (char)1 << endl;
				}
			}
			else if (subjects == "exit()") {
				store_Subject_list("", 0);
				count_creadit = count_credithour();
				cout << "\t\t\t\'" << subject_counts << "\' Courses Rigesterd and Total Creadit Hour is: " << count_creadit << endl;
			}
		}
		file.close();
	}
}

int HOD::count_credithour() {
	HOD_NODE* temp = hod_head;
	int size = 0;
	if (temp == NULL) {
		return size;
	}
	else {
		while (temp!=NULL) {
			size += temp->creadit_hour;
			temp = temp->next;
		}
		return size;
	}
}

int HOD::total_data_in_list() {
	HOD_NODE* temp = hod_head;
	if (temp == NULL) {
		return 0;
	}
	else {
		int i = 0;
		while (temp!=NULL) {
			i++;
			temp=temp->next;
		}
		return i;
	}
}

void HOD::store_Subject_list(string Semester_Name_From_out_of_class = "", int a = 0) {
	int Temp_Creadit;

	// Delete All data in Linked list
	HOD_NODE* temp;
	while (hod_head != NULL) {
		temp = hod_head;
		hod_head = hod_head->next;
		free(temp);
	}
	//***************************
	if (a == 1) {	// if call from in another function then this take input
		cout << "\t\t\tEnter Semester No: ";
		cin >> semester_No;
	}
	string semester_Name;
	int b = 0;
	if (Semester_Name_From_out_of_class.empty()) {
		semester_Name = (string)Prog_name_store + " " += to_string(semester_No) + ".txt";	// Creating File name
		b = 1;
	}
	else if (!Semester_Name_From_out_of_class.empty()) {
		b = 0;
		semester_Name = Semester_Name_From_out_of_class;
	}

	ifstream file(semester_Name);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream info(line);
			info >> Temp_Subject_Name >> Temp_Creadit;
			Charcter_Remover(Temp_Subject_Name, '.', ' ');
			hod_push_back(Temp_Subject_Name, Temp_Creadit); // Enter Data in list

		}
	}
	else {
		cout << "\t\t\tSemester Does not Exist:" << (char)2 << endl;
	}
	file.close();
}

void HOD::hod_push_back(string name, int creadit) {
	HOD_NODE* newNode = new HOD_NODE();
	newNode->creadit_hour = creadit;
	newNode->subjet_Names = name;
	if (hod_head == NULL) {
		hod_head=hod_tail  = newNode;
		hod_tail->next = NULL;
	}
	else {
		hod_tail->next = newNode;
		hod_tail = newNode;
		hod_tail->next = NULL;
	}
}

void HOD::Display_Subjects(string Semester_Name_From_out_of_class = "", int i = 1) {

	store_Subject_list(Semester_Name_From_out_of_class, i);

	int Total_creadit_hour = 0;
	int a = 1;
	HOD_NODE* temp = hod_head;
	while (temp != NULL) {
		cout << "\t\t-----------------------------------------------------------" << endl;
		cout << "\t\t\t\t(" << a << ") Subject Names: " << temp->subjet_Names << endl;
		cout << "\t\t\t\tCredit Hour: " << temp->creadit_hour << endl;
		a++;
		Total_creadit_hour += temp->creadit_hour;
		cout << "\t\t-----------------------------------------------------------" << endl;
		temp = temp->next;
	}
	cout << "\t\t\t\tTotal Credit Hour: " << Total_creadit_hour << endl;
}

bool HOD::checking_subject(string subjects) {
	store_Subject_list();		//call the Funtion that store data in list
	bool condition = true;
	HOD_NODE* temp = hod_head;
	while (temp != NULL) {
		if (subjects == temp->subjet_Names) {
			condition = false;
			break;
		}
		temp = temp->next;
	}
	return condition;
}

bool HOD::Already_data_in_file() {
	store_Subject_list();
	if (hod_head!=NULL) {	// if file is not Empty
		cout << "\'" << semester_Name << "\' Have Already Subjects" << endl;
		cout << "Do You Want Edit this ?" << endl;
		bool bol;
		bol = Varification();
		return bol;
	}
	else {
		cout<<"\t\t\tCreated New Semester:" << (char)2 << endl;
		return true;
	}
}

void HOD::show_Register_Student() {
	int semes;
	cout << "Enter Semester: ";
	cin >> semes;
	string file_name;
	file_name = Prog_name_store + " " + to_string(semes) + " Students.txt";
	ifstream file;
	file.open(file_name);
	if (file.is_open()) {
		string line;
		int temp_sap;
		int count = 1;
		int temp_sem;
		string temp_cours[8];
		int temp_cred[8];
		while (getline(file, line)) {
			istringstream info(line);
			info >> temp_sap;
			info >> temp_sem;
			for (auto i = 0; i < 8; i++) {
				info >> temp_cours[i] >> temp_cred[i];
			}
			cout << "\t\t\t*******************************************************" << endl;
			cout << "\t\t\t\t\t" << count << "th Student" << endl;
			count++;
			cout << "\t\t\tSap:" << temp_sap << endl;
			cout << "\t\t\tSemester: " << temp_sem << endl;
			cout << "\t\t\t\t Courses That Register" << endl;
			for (int i = 0; i < 8; i++) {
				if (temp_cours[i].empty()) {
					break;
				}
				cout << "\t\t\t\t" << "Course Name: " << temp_cours[i] << endl;
				cout << "\t\t\t\t\t" << "Credit Hour: " << temp_cred[i] << endl;
				temp_cours[i] = "";
				temp_cred[i] = 0;
			}
			cout << "\t\t\t*******************************************************" << endl;
		}
	}
	else cout << "\n\t\t\tNot Any Student Register" << endl;
	file.close();
}


void HOD::Arrange_All_Functions() {
	bool bol = login();
	if (bol == true) {
		int choice = 1;
		while (choice != 0) {
			system("cls");
			cout << "\t\t\t\t----->\tWelcome To HOD " << Prog_name_store << " Page\t<-----" << endl;
			cout << "\t\t-----------------------------------------------------------------" << endl;
			cout << "\t\t|\t1: Add Semester\t\t\t\t\t\t|" << endl;
			cout << "\t\t|\t2: Display Courses of Semester\t\t\t\t|" << endl;
			cout << "\t\t|\t3: Display Register Student\t\t\t\t|" << endl;
			cout << "\t\t|\t4: Set Credit Huour\t\t\t\t\t|" << endl;
			cout << "\t\t|\t0: Exit\t\t\t\t\t\t\t|" << endl;
			cout << "\t\t-----------------------------------------------------------------" << endl;
			cout << "\t\t\tEnter Your Choice: ";
			cin >> choice;

			switch (choice) {
			case 1: {
				Add_Semester();
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}break;
			case 2: {
				Display_Subjects();
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}break;
			case 3: {
				show_Register_Student();
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}break;
			case 4: {
				credit_hour_set();
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}break;
			case 0: {
				cout << "\t\t\tGood Bye " << (char)2 << endl;
			}break;
			default: {
				cout << "\t\t\tInvalid Input" << (char)2 << endl;
				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			} break;
			}
		}
	}
}
