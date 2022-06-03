from lib import *

num_ind_goods = int(input("How many industrial products do you want create: "))
ind_goods = create_ind_goods(num_ind_goods)

num_eating_goods = int(input("How many eating products do you want create: "))
eating_goods = create_eating_goods(num_eating_goods)

time = datetime.now()
current_time = TDate(time.day, time.month, time.year)

full_price = 0
for i in range(num_eating_goods):
    if eating_goods[i].is_spoiled_good(current_time):
        full_price += eating_goods[i].get_sum()

print("The total price of all spoiled products is:", full_price)

full_price = 0
for i in range(num_ind_goods):
    if ind_goods[i].get_conditions() == "IN_STOCK":
        full_price += ind_goods[i].get_sum()

print("The total price of all products that store IN_STOCK:", full_price)