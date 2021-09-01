#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<conio.h>
#include<vector>
#include<Windows.h>
#include<ctime>
#include<string>
#include<sstream>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
using namespace std;
void Charcter_Remover(string& str, char remover, char changer) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == remover) {
			str[i] = changer;
		}
	}
}
string Grade_set(int marks) {
	string str;
	if (marks >= 90 && marks <= 100) {
		str = "A+";
	}
	else if (marks >= 80 && marks < 90) {
		str = "A";
	}
	else if (marks >= 70 && marks < 80) {
		str = "B";
	}
	else if (marks >= 60 && marks < 70) {
		str = "C";
	}
	else if (marks >= 50 && marks < 60) {
		str = "D";
	}
	else if (marks >= 0 && marks < 50) {
		str = "F";
	}
	return str;
}
void passw(string &pass) {
	pass = "";
	char ch;
	ch = _getch();
	while (1) {//character 13 is enter
		if (ch == 13)
			break;
		pass += ch;
		cout << '*';
		ch = _getch();
	}
}
int passw() {
	string pass = "";
	char ch;
	ch = _getch();
	while (1) {//character 13 is enter
		if (ch == 13)
			break;
		pass += ch;
		cout << '*';
		ch = _getch();
	}
	if (pass == "") {
		pass = "9";
	}
	int p = stoi(pass);
	return p;
}