#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

char checkDateFormat(string date_to_check);
string readDateType1(string date_to_read);
string readDateType2(string date_to_read);
string readDateType3(string date_to_read);
string readDateType4and5(string date_to_read);

string changeDateFormat(string date_to_change);

string twoDigitsYear2fourDigits(string year);
string IntToString (int a);

int main (int argc, char * const argv[]) {
	ifstream read_file("./../../dates.txt"); // open file for reading
    string read_line; 
	
	ofstream new_file; // oopen file for writing
	new_file.open ("./../../new_dates.txt");
	
	
    while (getline(read_file, read_line))
    {
        new_file << changeDateFormat(read_line) << endl;
    }
	
	cout << endl << "Date changed! File saved!" << endl;
	
	new_file.close();
	read_file.close();
    return 0;
}

// changes date format to iso
string changeDateFormat(string date_to_change) {
	char date_format = checkDateFormat(date_to_change);
	
	switch (date_format) {
		case 0:
			return date_to_change;
			break;
		case 1:
			return readDateType1(date_to_change);
			break;
		case 2:
			return readDateType2(date_to_change);
			break;
		case 3:
			return readDateType3(date_to_change);
			break;
		default:
			return readDateType4and5(date_to_change);
			break;
	}
	
}

// Function to check date format.
// Returns:	0 if yyyy-mm-dd
//			1 if mm/dd/yy
//			2 if mm#yy#dd
//			3 if dd*mm*yyyy
//			4 if (month word) dd, yy
//			5 if (month word) dd, yyyy
// This function check for data separator (-/*#,) and lenght
char checkDateFormat(string date_to_check) {
	char separators[5] = {'-', '/', '#', '*'};
	
	for (int i = 0; i < 4; i++) {
		if(date_to_check.find(separators[i]) == string::npos) {
			continue; // not found so continue looking for
		} else {
			return i;
		}
	}
	
	// function still working so it is 4th or 5th date format, let's check
	// lenght and find out...
	if (date_to_check.length() == 10) {
		return 4;
	} else {
		return 5;
	}

}


// read date from format mm/dd/yy and change
string readDateType1(string date_to_read) {
	string day, month, year;
	day = date_to_read.substr(3, 2);
	month = date_to_read.substr(0, 2);
	year = date_to_read.substr(6, 2);
	if (atoi(year.c_str()) >= 50) {
		year = "19" + year;
	} else {
		year = "20" + year;
	}

	return year + "-" + month + "-" + day;
}

// read date from format mm#yy#dd and change
string readDateType2(string date_to_read) {
	string day, month, year;
	day = date_to_read.substr(6, 2);
	month = date_to_read.substr(0, 2);
	year = date_to_read.substr(3, 2);
	
	year = twoDigitsYear2fourDigits(year);
	
	return year + "-" + month + "-" + day;
}

// read date from format dd*mm*yyyy and change
string readDateType3(string date_to_read) {
	string day, month, year;
	day = date_to_read.substr(0, 2);
	month = date_to_read.substr(3, 2);
	year = date_to_read.substr(6, 4);
	
	return year + "-" + month + "-" + day;
}

// read date from format (month word) dd, yy(yy) and change
string readDateType4and5(string date_to_read) {
	string months_pattern[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	string day, month, year;
	
	day = date_to_read.substr(4, 2);
	month = date_to_read.substr(0, 3);
	year = date_to_read.substr(8);
	
	for(int i = 0; i < 12; i++) {
		if (month == months_pattern[i]) {
			if(i < 9)	month = "0" + IntToString(i+1);
			else month = IntToString(i+1);
		}
	}
	
	if(year.length() < 4) {
		year = twoDigitsYear2fourDigits(year);
	}
	
	return year + "-" + month + "-" + day;
}

// convert int to string
string IntToString (int a) {
    ostringstream temp;
    temp<<a;
    return temp.str();
}


// change two digits year to four digits year
string twoDigitsYear2fourDigits(string year) {
	if (atoi(year.c_str()) >= 50) {
		year = "19" + year;
	} else {
		year = "20" + year;
	}
	return year;
}

 
