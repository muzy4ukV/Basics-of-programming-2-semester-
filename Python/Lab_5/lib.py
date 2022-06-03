from datetime import datetime
MONTH_DATE = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

class TDate:
    def __init__(self, day, month, year):
        if year < 1900 or year > 2022:
            print("Incorrect enter year")
            exit(0)
        if month <= 0 or month > 12:
            print("Invalid enter month")
            exit(0)
        if day <= 0 or day > MONTH_DATE[month - 1]:
            print("Invalid entered day")
            exit(0)
        self.day = day
        self.month = month
        self.year = year

    def add_day(self, day):
        self.day += day
        while True:
            if self.day > MONTH_DATE[self.month - 1]:
                self.day -= MONTH_DATE[self.month - 1]
                self.month += 1
            else: 
                break

class Goods:
    def __init__(self, name, date, price, number):
        self._name = name
        self._date = date
        if price < 0:
            print("Incorrect entered price")
            exit(0)
        if number <= 0:
            print("Invalid number of products")
            exit(0)
        self._price = price
        self._number = number

    def get_sum(self):
        return self._price * self._number


class Industrial_Goods(Goods):
    def __init__(self, name, date, price, number, conditions):
        super().__init__(name, date, price, number)
        self.__conditions = conditions

    def get_conditions(self):
        return self.__conditions

class Eating_Goods(Goods):
    def __init__(self, name, date, price, number, expiration):
        super().__init__(name, date, price, number)
        if expiration < 0:
            print("Incorrected expiration date")
            exit(0)
        self.__expiration = expiration
    def is_spoiled_good(self, current_date):
        expiration_date = self._date
        expiration_date.add_day(self.__expiration)

        current_days = current_date.year * 365 + (current_date.month - 1) * 31 + current_date.day
        expiration_days = expiration_date.year * 365 + (expiration_date.month - 1) * 31 + expiration_date.day

        if current_days > expiration_days:
            return True
        elif expiration_days >= current_days:
            return False

def create_ind_goods(num_ind_goods):
    ind_goods = []
    print("Add information about industrial product")

    for i in range(num_ind_goods):
        name = input("Name product: ")
        date = input("Enter date in format[dd.mm.yyyy]: ")
        date = date.split('.')
        for i in range(3):
            date[i] = int(date[i])
        price = float(input("Enter price: "))
        number = int(input("Enter number of products: "))
        conditions = input("Enter a conditions of transoprt(IN_STOCK, IN_TRADING_HALL): ")
        ind_goods.append(Industrial_Goods(name, TDate(date[0], date[1], date[2]), price, number, conditions))
        print()
    return ind_goods

def create_eating_goods(num_eating_goods):
    eating_goods = []
    print("Add information about eating product")

    for i in range(num_eating_goods):
        name = input("Name product: ")
        date = input("Enter date in format[dd.mm.yyyy]: ")
        date = date.split('.')
        for i in range(3):
            date[i] = int(date[i])
        price = float(input("Enter price: "))
        number = int(input("Enter number of products: "))
        expiriation = int(input("Enter a expiration date: "))
        eating_goods.append(Eating_Goods(name, TDate(date[0], date[1], date[2]), price, number, expiriation))
        print()
    return eating_goods


