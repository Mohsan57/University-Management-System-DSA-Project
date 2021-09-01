#include"CEO.h"
#include"HOD.h"
#include"Admin.h"
#include"Registration office.h"
#include"Student.h"
int main() {
	CEO ceo;
	HOD hod;
	Admin admin;
	system("color 0b");
	int choice = 1;
	while (choice != 0) {
		system("cls");


		// current date/time based on current system
		time_t now = time(0);
		tm* ltm = localtime(&now);
		// current date/time based on currnt system "now" store "Seconds" from January 1,1970 to current

		// local Time
		// print various components of tm structure.
		cout << "\t\t\t\t\t\t\t\tDate:" << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
		cout << "\t\t\t\t\t\t\t\tTime: " << ltm->tm_hour << ":";
		cout << ltm->tm_min << ":";
		cout << ltm->tm_sec << endl;

		cout << "\t\t\t\t----->\tWelcome To SAP System\t<-----" << endl;
		cout << "\t\t-----------------------------------------------------------------" << endl;
		cout << "\t\t|\t1: Login As a Student\t\t\t\t\t|" << endl;
		cout << "\t\t|\t2: Login As a Faculty\t\t\t\t\t|" << endl;
		cout << "\t\t|\t3: Register New Student\t\t\t\t\t|" << endl;
		cout << "\t\t|\t0: Exit\t\t\t\t\t\t\t|" << endl;
		cout << "\t\t-----------------------------------------------------------------" << endl;
		cout << "\t\t\tEnter Your Choice: ";
		cin >> choice;
		switch (choice) {
		case 1: {

			int choices = 1;
			while (choices != 0) {

				system("cls");
				cout << "\t\t\t\t----->\tWelcome To Student Login  <-----" << endl;
				cout << "\t\t-----------------------------------------------------------------" << endl;
				cout << "\t\t|\t1: Login As a new Student\t\t\t\t|" << endl;
				cout << "\t\t|\t2: Login with Email\t\t\t\t\t|" << endl;
				cout << "\t\t|\t0: Exit\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t-----------------------------------------------------------------" << endl;
				cout << "\t\t\tEnter Your Choice: ";
				cin >> choices;

				switch (choices) {
				case 1: {
					system("cls");
					admin.New_Student_Input();
					cout << "Enter Any Key to Continue..." << endl;
					_getch();
				}break;
				case 2: {
					int choices = 1;
					bool bol = admin.old_Student();
					if (bol == true) {
						while (choices != 0) {
							system("cls");
							cout << "\t\t\t\t----->\tWelcome To Student Page  <-----" << endl;
							cout << "\t\t-----------------------------------------------------------------" << endl;
							cout << "\t\t|\t1: Show Basic Information\t\t\t\t|" << endl;
							cout << "\t\t|\t2: Show Transcript\t\t\t\t\t|" << endl;
							cout << "\t\t|\t3: Register New Semester\t\t\t\t|" << endl;
							cout << "\t\t|\t0: Exit\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t-----------------------------------------------------------------" << endl;
							cout << "\t\t\tEnter Your Choice: ";
							cin >> choices;

							switch (choices) {
							case 1: {
								system("cls");
								admin.Display_Student_Basic_Information();
								cout << "Enter Any Key to Continue..." << endl;
								_getch();
							}break;
							case 2: {
								system("cls");
								//	student.show_Transcript();
								admin.Show_Marks_of_Students();
								cout << "Enter Any Key to Continue..." << endl;
								_getch();
							}break;
							case 3: {
								system("cls");
								admin.Register_New_Semester();
								cout << "Enter Any Key to Continue..." << endl;
								_getch();
							} break;
							case 0: {
								cout << "\t\t\tGood Bye " << (char)2 << endl;
							}break;
							default: {
								cout << "\t\t\tInvalid Input" << endl;
							} break;
							}

						}
					}
					cout << "Enter Any Key to Continue..." << endl;
					_getch();
				}break;
				case 0: {
					cout << "\t\t\tGood bye" << (char)1 << endl;
				} break;
				default: {
					cout << "\t\t\tInvalid Input" << endl;
				}
					   break;
				}

				cout << "Enter Any Key to Continue..." << endl;
				_getch();
			}
		} break;
		case 2: {
			int choices = 1;
			while (choices != 0) {
				system("cls");
				cout << "\t\t\t\t----->\tWelcome To Faculty Login  <-----" << endl;
				cout << "\t\t-----------------------------------------------------------------" << endl;
				cout << "\t\t|\t1: Login As a CEO\t\t\t\t\t|" << endl;
				cout << "\t\t|\t2: Login As a HOD\t\t\t\t\t|" << endl;
				cout << "\t\t|\t3: Login As a Admin\t\t\t\t\t|" << endl;
				//		cout << "\t\t|\t4: Login As a \t\t\t\t\t|" << endl;
				//		cout << "\t\t|\t2: Login As a HOD\t\t\t\t\t|" << endl;
				cout << "\t\t|\t0: Exit\t\t\t\t\t\t\t|" << endl;
				cout << "\t\t-----------------------------------------------------------------" << endl;
				cout << "\t\t\tEnter Your Choice: ";
				cin >> choices;
				switch (choices) {
				case 1: {
					ceo.Arrange_All_Functions();
				}break;
				case 2: {
					hod.Arrange_All_Functions();
				}break;
				case 3: {
					bool bol = admin.Login_Admin();
					if (bol == true) {
						int choices = 1;
						while (choices != 0) {
							system("cls");
							admin.Show_Department();
							cout << "\t\t\t\t----->\tWelcome To Admin Page\t<-----" << endl;
							cout << "\t\t-----------------------------------------------------------------" << endl;
							cout << "\t\t|\t1: Enter Marks of Students\t\t\t\t|" << endl;
							cout << "\t\t|\t0: Exit\t\t\t\t\t\t\t|" << endl;
							cout << "\t\t-----------------------------------------------------------------" << endl;
							cout << "\t\t\tEnter Your Choice: ";
							cin >> choices;
							switch (choices) {
							case 1: {
								system("cls");
								admin.Show_Semester_of_Student();
								cout << "Enter Any Key to Continue..." << endl;
								_getch();
							}break;
							case 0: {
								cout << "Good bye" << (char)2 << endl;
								break;
							}break;
							default:
								break;
							}
						}
					}
				}break;
				case 0: {

				}break;
				default:
					break;
				}
			}
			cout << "Enter Any Key to Continue..." << endl;
			_getch();
		} break;
		case 3: {
			system("cls");

			admin.Register_new_student();

			cout << "Enter Any Key to Continue..." << endl;
			_getch();
		} break;
		case 0: {
			cout << "\t\t\tGood Bye " << (char)2 << endl;
			break;
		} break;
		default: {
			cout << "Invalid Input " << (char)1 << endl;
		} break;

		}

	}
}
