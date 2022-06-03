#include "Goods.h"

// Реалізація класу для збереження дати

int TDate::monthDate[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

TDate::TDate(int day1 = 1, int month1 = 1, int year1 = 1901) {
	if (year1 < 1900 || year1 > 2022) {
		cerr << "Incorrect enter year";
		exit(0);
	}
	if (month1 <= 0 || month1 > 12) {
		cerr << "Invalid enter month";
		exit(0);
	}
	if (day1 <= 0 || day1 > monthDate[month1 - 1]) {
		cerr << "Invalid entered day";
		exit(0);
	}
	this->day = day1;
	this->month = month1;
	this->year = year1;
}

void TDate::addDay(int day) {
	if (day < 0) {
		cerr << "Incorrected day";
		exit(0);
	}
	this->day += day;
	while (true) {
		if (this->day > monthDate[this->month - 1]) {
			this->day -= monthDate[this->month - 1];
			this->month += 1;
		}
		else break;
	}
}

// Реалізація базового класу 

Goods::Goods() {
	name = "noName";
	date;
	price = 0.0;
	number = 0;
}

Goods::Goods(string name1, TDate date1, float price1, int number1) : name(name1), date(date1) {
	if (price1 < 0) {
		cerr << "Incorrect entered price";
		exit(0);
	}
	if (number1 <= 0) {
		cerr << "Invalid number of products";
		exit(0);
	}
	this->price = price1;
	this->number = number1;
}

float Goods::get_sum() {
	return this->price * this->number;
}

// Реалізація похідного класу для збереження промислових товарів 

IndustrialGoods::IndustrialGoods(): Goods(), conditions(IN_STOCK) {}

IndustrialGoods::IndustrialGoods(string name1, TDate date1, float price1, int number1, Transport conditions1) :
	Goods(name1, date1, price1, number1), conditions(conditions1) {}

Transport IndustrialGoods::get_conditions() {
	return this->conditions;
}

// Реалізація похідного класу для збереження харчових товарів 

EatingGoods::EatingGoods() : Goods(), expiration(0) {}

EatingGoods::EatingGoods(string name1, TDate date1, float price1, int number1, int expiration1) :
	Goods(name1, date1, price1, number1){
	if (expiration1 < 0) {
		cerr << "Incorrected expiration date";
		exit(0);
	}
	this->expiration = expiration1;
}

bool EatingGoods::isSpoiledGood(TDate& currentDate) {
	TDate expirationDate = this->date;
	expirationDate.addDay(this->expiration);

	int cuurentDays = currentDate.year * 365 + (currentDate.month - 1) * 31 + currentDate.day;
	int expirationDays = expirationDate.year * 365 + (expirationDate.month - 1) * 31 + expirationDate.day;

	if (cuurentDays > expirationDays) {
		return true;
	}
	else if (expirationDays >= cuurentDays) {
		return false;
	}
}

// Допоміжні функції

IndustrialGoods* createInd(int numInd) {
	IndustrialGoods* indGoods = new IndustrialGoods[numInd];
	cout << "Add information about industrial product" << endl;
	string name, dateLine; float price; int num, cond; int dates[3];
 	for (int i = 0; i < numInd; i++) {
		cout << "Name product: ";
		cin.ignore(3200, '\n');
		getline(cin, name);

		cout << "Enter date in format[dd.mm.yyyy]: ";
		getline(cin, dateLine);
		for (int j = 0; j < 3; j++)
		{
			if (j == 2)
				dates[j] = stoi(dateLine);
			else {
				int pos = dateLine.find('.');
				dates[j] = stoi(dateLine.substr(0, pos));
				dateLine.erase(0, pos + 1);
			}
		}

		cout << "Enter price: ";
		cin >> price;

		cout << "Enter number of products: ";
		cin >> num;

		cout << "Enter a conditions of transoprt(0 - IN_STOCK, 1 - IN_TRADING_HALL): ";
		cin >> cond;

		indGoods[i] = IndustrialGoods(name, TDate(dates[0], dates[1], dates[2]), price, num, static_cast<Transport>(cond));
		cout << endl;
	}
	return indGoods;
}

EatingGoods* createEat(int numEat) {
	EatingGoods* eatGoods = new EatingGoods[numEat];
	cout << "Add information about eating product" << endl;
	string name, dateLine; float price; int num, expiriation; int dates[3];
	for (int i = 0; i < numEat; i++) {
		cout << "Name product: ";
		cin.ignore(3200, '\n');
		getline(cin, name);

		cout << "Enter date in format[dd.mm.yyyy]: ";
		getline(cin, dateLine);
		for (int j = 0; j < 3; j++)
		{
			if (j == 2)
				dates[j] = stoi(dateLine);
			else {
				int pos = dateLine.find('.');
				dates[j] = stoi(dateLine.substr(0, pos));
				dateLine.erase(0, pos + 1);
			}
		}

		cout << "Enter price: ";
		cin >> price;

		cout << "Enter number of products: ";
		cin >> num;

		cout << "Enter a expiration date: ";
		cin >> expiriation;

		eatGoods[i] = EatingGoods(name, TDate(dates[0], dates[1], dates[2]), price, num, expiriation);
		cout << endl;
	}
	return eatGoods;
}