#include<fstream>
#include<iostream>
#include<process.h>
#include<stdio.h>
#include<string.h>

using namespace std;

class Test {
private:
	int a[200][5];
	int size;
	int totalMarks;
	int numOfCorrectAns;
	int numOfIncorrectAns;
	int numOfSkippedAns;
	char fileName[20];
public:
	void input(int totalMarks, int size, int numOfCorrectAns,
			int numOfIncorrectAns, int numOfSkippedAns, int a[200][5]) {
		cout << "\nENTER FILE NAME : ";
		cin >> this->fileName;
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < 5; y++) {
				this->a[x][y] = a[x][y];
			}
		}
		this->size = size;
		this->totalMarks = totalMarks;
		this->numOfCorrectAns = numOfCorrectAns;
		this->numOfIncorrectAns = numOfIncorrectAns;
		this->numOfSkippedAns = numOfSkippedAns;
	}
	int getArray(int x, int y) {
		return this->a[x][y];
	}
	int getSize() {
		return this->size;
	}
	int getTotal() {
		return this->totalMarks;
	}
	int getCorrect() {
		return this->numOfCorrectAns;
	}
	int getIncorrect() {
		return this->numOfIncorrectAns;
	}
	int getSkip() {
		return this->numOfSkippedAns;
	}
	string getFileName() {
		return this->fileName;
	}
};

void print(int a[200][5], int size, int totalMarks) {
	int numOfPages;
	system("CLS");
	if (size % 10 == 0) {
		numOfPages = size / 10;
	} else {
		numOfPages = size / 10 + 1;
	}
	if (numOfPages == 1) {
		cout << "\nQno.\tOpt\tKey\tMarks" << endl;
		cout << "------------------------------" << endl;
		for (int i = 0; i < size; i++) {
			char yourAns = a[i][1];
			char ansKey = a[i][2];
			char sign = a[i][3];
			char marks = a[i][4];
			cout << a[i][0] << "\t" << yourAns << "\t" << ansKey << "\t" << sign
					<< marks << endl;
		}
		cout << "------------------------------";
		cout << "\nTOTAL MARKS = " << totalMarks << "/" << size * 4 << endl
				<< endl;
		system("pause");
	} else {
		int currPage = 1;
		label: system("CLS");
		cout << "\nQno.\tOpt\tKey\tMarks" << endl;
		cout << "------------------------------" << endl;
		for (int i = (currPage - 1) * 10; i < currPage * 10 && i < size; i++) {
			char yourAns = a[i][1];
			char ansKey = a[i][2];
			char sign = a[i][3];
			char marks = a[i][4];
			cout << a[i][0] << "\t" << yourAns << "\t" << ansKey << "\t" << sign
					<< marks << endl;
		}
		cout << "------------------------------";
		cout << "\nTOTAL MARKS = " << totalMarks << "/" << size * 4 << endl;
		int n;
		if (currPage == 1) {
			cout << "\n2 -> NEXT PAGE\n3 -> EXIT";
			cout << "\n\nENTER OPTION : ";
			cin >> n;
			if (n != 2 && n != 3) {
				cout << "ENTER A VALID OPTION <2/3>\n" << endl;
				system("pause");
				goto label;
			}
		} else if (currPage > 1 && currPage < numOfPages) {
			cout << "\n1 -> PREVIOUS PAGE\n2 -> NEXT PAGE\n3 -> EXIT";
			cout << "\n\nENTER OPTION : ";
			cin >> n;
			if (n != 1 && n != 2 && n != 3) {
				cout << "ENTER A VALID OPTION <1-3>\n" << endl;
				system("pause");
				goto label;
			}
		} else if (currPage == numOfPages) {
			cout << "\n1 -> PREVIOUS PAGE\n3 -> EXIT";
			cout << "\n\nENTER OPTION : ";
			cin >> n;
			if (n != 1 && n != 3) {
				cout << "ENTER A VALID OPTION <1/3>\n" << endl;
				system("pause");
				goto label;
			}
		}
		if (n == 1) {
			currPage--;
			goto label;
		} else if (n == 2) {
			currPage++;
			goto label;
		} else if (n == 3) {
			goto label1;
		}
	}
	label1: system("CLS");
	cout << "\nEXITED SUCCESSFULLY\n" << endl;
	system("pause");
}

void display(int totalMarks, int size, int numOfCorrectAns,
		int numOfIncorrectAns, int numOfSkippedAns, int a[200][5], bool flag =
				true) {
	label: system("CLS");
	cout << "\nTOTAL MARKS OBTAINED = " << totalMarks << "/" << size * 4;
	cout << "\n\nCORRECT : " << numOfCorrectAns << endl;
	cout << "INCORRECT : " << numOfIncorrectAns << endl;
	cout << "SKIPPED : " << numOfSkippedAns << endl;
	if (flag) {
		cout << "\nDO YOU WANT TO SAVE THIS TEST ? <y/n> : ";
		char ch;
		cin >> ch;
		if (ch == 'y') {
			Test t;
			t.input(totalMarks, size, numOfCorrectAns, numOfIncorrectAns,
					numOfSkippedAns, a);
			ofstream fout("record.dat", ios::app | ios::binary);
			fout.write((char*) &t, sizeof(t));
			fout.close();
			cout << "TEST SAVED\n";
		} else if (ch == 'n') {
			cout << "TEST NOT SAVED\n";
		} else {
			cout << "ENTER A VALID OPTION <y/n>\n" << endl;
			system("pause");
			goto label;
		}
	}
	cout << endl;
	system("pause");
	print(a, size, totalMarks);
}

void calculateMarks(int a[200][5], int size) {
	int marks = 0;
	int numOfCorrectAns = 0;
	int numOfIncorrectAns = 0;
	int numOfSkippedAns = 0;
	for (int i = 0; i < size; i++) {
		if (a[i][1] == a[i][2]) {
			marks = marks + 4;
			a[i][3] = '+';
			a[i][4] = '4';
			numOfCorrectAns++;
		} else if (a[i][1] == 's') {
			a[i][3] = ' ';
			a[i][4] = '0';
			numOfSkippedAns++;
		} else {
			marks--;
			a[i][3] = '-';
			a[i][4] = '1';
			numOfIncorrectAns++;
		}
	}
	display(marks, size, numOfCorrectAns, numOfIncorrectAns, numOfSkippedAns,
			a);
}

void inputAnswerKey(int a[200][5], int size) {
	system("CLS");
	cout << "\nINPUT THE ANSWER KEY\n\n";
	for (int i = 0; i < size; i++) {
		label: cout << i + 1 << ")\t";
		char ansKey;
		cin >> ansKey;
		if (ansKey == 'a' || ansKey == 'b' || ansKey == 'c' || ansKey == 'd') {
			a[i][2] = ansKey;
		} else {
			cout << "ENTER A VALID OPTION <a-d>\n" << endl;
			system("pause");
			system("CLS");
			cout << "\nINPUT THE ANSWER KEY\n\n";
			for (int j = 0; j < i; j++) {
				char ch = a[j][2];
				cout << j + 1 << ")\t" << ch << endl;
			}
			goto label;
		}
	}
	calculateMarks(a, size);
}

void recheck(int a[200][5], int size) {
	label: system("CLS");
	int ques;
	cout << "\n\t\tREVIEW AND CHANGE";
	cout << "\n\nENTER QUES NO. :  ";
	cin >> ques;
	if (ques <= size) {
		char oldAns = a[ques - 1][1];
		cout << "ANS ENTERED : " << oldAns;
		label1: cout << "\n\nENTER NEW ANS : ";
		char newAns;
		cin >> newAns;
		if (newAns == 'a' || newAns == 'b' || newAns == 'c' || newAns == 'd'
				|| newAns == 's') {
			a[ques - 1][1] = newAns;
		} else {
			cout << "ENTER A VALID OPTION (a/b/c/d/s)\n" << endl;
			system("pause");
			system("CLS");
			cout << "\n\t\tREVIEW AND CHANGE";
			cout << "\n\nENTER QUES NO. :  " << ques << endl;
			cout << "ANS ENTERED : " << oldAns;
			goto label1;
		}
		cout << "\nANS CHANGED SUCCESSFULLY\n" << endl;
		system("pause");
	} else {
		cout << "ENTER A VALID OPTION <1-" << size << ">\n" << endl;
		system("pause");
		goto label;
	}
}

void displayEnteredInput(int a[200][5], int size) {
	label: system("CLS");
	int numOfCols;
	cout << "\nENTERED INPUT\n" << endl;
	if (size % 15 == 0) {
		numOfCols = size / 15;
	} else {
		numOfCols = size / 15 + 1;
	}
	for (int i = 0, currRow = 0; i < 15; i++, currRow++) {
		for (int currCol = 0, currQues = currRow;
				currCol < numOfCols && currQues < size; currCol++, currQues +=
						15) {
			char ans = a[currQues][1];
			cout << currQues + 1 << ")\t" << ans << "\t";
		}
		cout << endl;
	}
	cout
			<< "__________________\n\ny - SUBMIT TEST\nn - CHANGE ANSWER AND REVIEW";
	cout << "\n\nFINISH TEST ? <y/n> : ";
	char option;
	cin >> option;
	if (option == 'y') {
		system("CLS");
		cout << "\nTEST SUBMITTED\n" << endl;
		system("pause");
		inputAnswerKey(a, size);
	} else if (option == 'n') {
		recheck(a, size);
		goto label;
	} else {
		cout << "ENTER A VALID OPTION <y/n>\n" << endl;
		system("pause");
		goto label;
	}
}

void rules(int size) {
	system("CLS");
	cout << "\n\t\tRULES";
	cout << "\n\nTIME = " << 2 * size << " MIN" << "\t\tMAX MARKS = "
			<< 4 * size;
	cout << "\n\n1. Read the questions carefully." << endl;
	cout << "2. Correct response will award +4 marks." << endl;
	cout << "3. Incorrect response will deduct 1 marks i.e. -1." << endl;
	cout << "4. Any question marked as 's' will be marked as skipped." << endl;
	cout << "5. ZERO marks will be awarded for skipped questions." << endl;
	cout << "\n\n";
	system("pause");
}

void newTest() {
	label: system("CLS");
	int size;
	cout << "\nENTER NUMBER OF QUES : ";
	cin >> size;
	if (size > 0 && size <= 200) {
		int a[size][5];
		rules(size);
		system("CLS");
		cout << "\nINPUT ANSWERS\n" << endl;
		for (int i = 0; i < size; i++) {
			a[i][0] = i + 1;
			label1: cout << i + 1 << ")\t";
			char ans;
			cin >> ans;
			if (ans == 'a' || ans == 'b' || ans == 'c' || ans == 'd'
					|| ans == 's') {
				a[i][1] = ans;
			} else {
				cout << "\nENTER A VALID OPTION\n" << endl;
				system("pause");
				system("CLS");
				cout << "\nINPUT ANSWERS\n" << endl;
				for (int j = 0; j < i; j++) {
					ans = a[j][1];
					cout << j + 1 << ")\t" << ans << endl;
				}
				goto label1;
			}
		}
		cout << endl;
		system("pause");
		displayEnteredInput(a, size);
	} else {
		cout << "ENTER A VALID NUMBER <1-200>\n" << endl;
		system("pause");
		goto label;
	}
}

void del(string fileName) {
	system("CLS");
	Test t;
	ifstream fin("record.dat", ios::in | ios::binary);
	ofstream fout("temp.dat", ios::out | ios::binary);
	while (fin.read((char*) &t, sizeof(t))) {
		if (t.getFileName() == fileName) {
			cout << "\nFILE DELETED\n" << endl;
		} else {
			fout.write((char*) &t, sizeof(t));
		}
	}
	fin.close();
	fout.close();
	remove("record.dat");
	rename("temp.dat", "record.dat");
	system("pause");
}

void openFile() {
	label1: system("CLS");
	Test t;
	ifstream fin("record.dat", ios::in | ios::binary);
	cout << "\n\t\tFILES :" << endl;
	int count = 0;
	while (fin.read((char*) &t, sizeof(t))) {
		cout << "-> " << t.getFileName() << endl;
		count++;
	}
	if (count == 0) {
		cout << "[EMPTY]" << endl;
	}
	fin.close();
	cout << "\n1 -> VIEW FILE\n2 -> DELETE FILE\n3 -> BACK TO MAIN MENU\n"
			<< endl;
	cout << "ENTER OPTION <1-3> : ";
	int n;
	cin >> n;
	if (n == 1) {
		ifstream f("record.dat", ios::in | ios::binary);
		cout
				<< "___________________\n\nENTER FILE NAME TO OPEN <case senstive> : ";
		string fileName;
		cin >> fileName;
		bool found = 0;
		int a[200][5];
		while (f.read((char*) &t, sizeof(t))) {
			if (t.getFileName() == fileName) {
				found = 1;
				for (int i = 0; i < t.getSize(); i++) {
					for (int j = 0; j < 5; j++)
						a[i][j] = t.getArray(i, j);
				}
				display(t.getTotal(), t.getSize(), t.getCorrect(),
						t.getIncorrect(), t.getSkip(), a, false);
			}
			if (found) {
				goto label1;
			}
		}
		f.close();
		cout
				<< "\nFILE NOT FOUND.\nPLS MAKE SURE THAT YOU HAVE ENTERED THE CORRECT FILE NAME\n"
				<< endl;
		system("pause");
		goto label1;
	} else if (n == 2) {
		ifstream f("record.dat", ios::in | ios::binary);
		cout
				<< "___________________\n\nENTER FILE NAME TO DELETE <case senstive> : ";
		string fileName;
		cin >> fileName;
		bool found = 0;
		while (f.read((char*) &t, sizeof(t))) {
			if (t.getFileName() == fileName) {
				found = 1;
				del(fileName);
			}
			if (found) {
				goto label1;
			}
		}
		f.close();
		cout
				<< "\nFILE NOT FOUND.\nPLS MAKE SURE THAT YOU HAVE ENTERED THE CORRECT FILE NAME\n"
				<< endl;
		system("pause");
		goto label1;
	} else if (n == 3) {
		cout << endl;
		goto label;
	} else {
		cout << "ENTER A VALID OPTION <1-3>\n" << endl;
		system("pause");
		goto label1;
	}
	label: system("pause");
}

int main() {
	int i;
	do {
		system("CLS");
		cout << "\nWELCOME TO SANIDHYA's TEST CENTRE";
		cout << "\n\n1. -> NEW TEST";
		cout << "\n2. -> OPEN FILE";
		cout << "\n3. -> EXIT" << endl;
		cout << "\nENTER OPTION <1-3> : ";
		cin >> i;

		switch (i) {
		case 1:
			newTest();
			break;
		case 2:
			openFile();
			break;
		case 3:
			cout << "\nEXITED SUCCESSFULLY";
			exit(0);
			break;
		default:
			cout << "ENTER A VALID OPTION\n\n";
			system("pause");
			break;
		}
	} while (1);
	return 0;
}
