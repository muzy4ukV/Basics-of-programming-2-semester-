#include "Goods.h"

int main()
{
	cout << "How many industrial products do you want create: ";
	int numInd; cin >> numInd;
	IndustrialGoods* indGoods = createInd(numInd);

	cout << "How many eating products do you want create: ";
	int numEat; cin >> numEat;
	EatingGoods* eatGoods = createEat(numEat);

	struct tm current_time;
	time_t t = time(0);
	localtime_s(&current_time, &t);
	TDate currentTime(current_time.tm_mday, current_time.tm_mon + 1, 1900 + current_time.tm_year);
	
	int full_price = 0;
	for (int i = 0; i < numEat; i++) {
		if (eatGoods[i].isSpoiledGood(currentTime)) {
			full_price += eatGoods[i].get_sum();
		}
	}
	cout << "The total price of all spoiled products is: " << full_price << endl;

	full_price = 0;
	for (int i = 0; i < numInd; i++) {
		if (indGoods[i].get_conditions() == IN_STOCK) {
			full_price += indGoods[i].get_sum();
		}
	}

	cout << "The total price of all products that store IN_STOCK: " << full_price << endl;

	return 0;
}