#pragma once

#include <iostream>
#include <string>
using namespace std;

class TDate {
public:
	int day;
	int month;
	int year;
	static int monthDate[12];
	TDate(int day1, int month1, int year1);
	void addDay(int);
};

enum Transport {
	IN_STOCK,
	IN_TRADING_HALL
};

class Goods {
protected:
	string name;
	TDate date;
	float price;
	int number;
	Goods();
	Goods(string, TDate, float, int);
public:
	float get_sum();
};

class IndustrialGoods : public Goods {
	Transport conditions;
public:
	IndustrialGoods();
	IndustrialGoods(string, TDate, float, int, Transport);
	Transport get_conditions();
};

class EatingGoods : public Goods {
	int expiration;
public:
	EatingGoods();
	EatingGoods(string, TDate, float, int, int);
	bool isSpoiledGood(TDate&);
};

IndustrialGoods* createInd(int numInd);
EatingGoods* createEat(int numEat);