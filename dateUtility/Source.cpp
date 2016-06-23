#include<stdio.h>
#include<iostream>
#include<string>


using System::Globalization::PersianCalendar;
using System::Globalization::HijriCalendar;
using System::DateTime;
using System::Convert;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;

void parseDate(string, string &, string &, string &);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout<< "dateUtility version 1.0" << endl;
		cout<< "Usage: dateUtility /P /A dd/mm/yyyy" << endl;
		cout << "/P		converts Gregorian date to Persian date" << endl;
		cout << "/A		converts Persian date to Hijri date" << endl;
		cout << "Notes:" << endl;
		cout << "If neither /P or /A switches are specified, the program assumes conversion of Persian date to Gregorian date ." << endl;
		cout << "mm and dd can be one or two digits." << endl;

		return 1;
	}
	string inputDate = "";
	string month, day, year;	
	PersianCalendar pDate;
	DateTime gDate;	
	HijriCalendar hDate;
	if (argc >= 3 && argv[1][0]=='/') { //a switch is specified
		inputDate = argv[2];
		if (inputDate.length() < 8) {
			cerr << "Input date's length is wrong." << endl;
			return 1;
		}
		parseDate(inputDate, day,month, year);
		switch (argv[1][1]) {
		case 'P':
		{
			DateTime gDate(std::stoi(year), std::stoi(month), std::stoi(day));
			cout << "Persian Date is: " << pDate.GetDayOfMonth(gDate) << "/" << pDate.GetMonth(gDate) << "/" << pDate.GetYear(gDate) << endl;
			break;
		}
		case 'A':
			gDate = pDate.ToDateTime(std::atoi(year.c_str()), std::atoi(month.c_str()), std::atoi(day.c_str()), 0, 0, 0, 0);
			cout << "Hijri date is: " << hDate.GetDayOfMonth(gDate) << "/" << hDate.GetMonth(gDate) << "/" << hDate.GetYear(gDate) << endl;			
			break;
		default:
			cerr << "Unknown switch" << endl;
			break;
		
		}
	}
	else {		
		inputDate = argv[1];
		if (inputDate.length() < 8) {
			cerr << "Input date's length is wrong." << endl;
			return 1;
		}
		parseDate(inputDate,  day, month, year);
		gDate = pDate.ToDateTime(std::atoi(year.c_str()), std::atoi(month.c_str()), std::atoi(day.c_str()), 0, 0, 0, 0);
		cout << "Gregorian date is: " << gDate.Day << "/" << gDate.Month << "/" <<gDate.Year << endl;

	}	
		
	return 0;
}

void parseDate(string inputDate, string &day, string &month, string &year) {
	int index = 0;
	char dateParts[3][5];
	int partsIndex = 0;

	while (inputDate[index]) //process date input and separate parts
	{
		if (inputDate[index] == '/') {
			index++;
			continue;
		}
		else if (isdigit(inputDate[index])) {
			int j = 0;
			while (isdigit(inputDate[index]))
			{
				dateParts[partsIndex][j++] = inputDate[index++];
			}
			dateParts[partsIndex][j] = '\0';
			partsIndex++;
		}

	}

	day= dateParts[0];
	month = dateParts[1];
	year = dateParts[2];


}
