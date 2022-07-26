# Food_Ordering_System
A project on C++ with functionalities like login, signup, order by food, order by hotel, cart, order history to implement the food ordering system. MYSQL database is used for storing and retrieving the data. <br>
 For connecting database in c++ with XAMPP server we need some files and they are,<br>
 * libmysql.dll
 * libmysql.a
 * mysql header files <br>
 We are required to put these files in MinGW folder in Dev-CPP and set the respective path in Code-Blocks for Database Connectivity with XAMPP server and the dll file is copied in the place of exe file. <br>
 ![Screenshot (18)](https://user-images.githubusercontent.com/76902858/126878542-976cb5db-c122-49ff-97c9-77b755374aba.png)

### MODULES:
* Signup
* Login
* Order by food
* Order by hotel
* Cart
* Order history

### SIGNUP:
* Get the inputs from the user like username, password, confirm password, email and phone number.
* Validate the inputs
* Username must be alphabets
* Password must be atleast of 8 characters which includes lowercase, uppercase, number and special characters.
* Email must contains '@' and '.' characters and the length should be greater than 5.
* Phone number must have exactly 10 digits and should contains only numbers.
* If all the above conditions are satisfied, then the user details are stored in database. 
![Screenshot (11)](https://user-images.githubusercontent.com/76902858/126878321-cbd23cc6-73a0-4830-b8b9-d8f5dd782f82.png)

### LOGIN:
* E-mail and password are checked from the database. Once verified, user are allowed to choose the food either by searching foods or searching the hotels.
![Screenshot (12)](https://user-images.githubusercontent.com/76902858/126878359-0f95797b-fe25-4932-8f1f-c6720260f09b.png)

### ORDER_BY_HOTEL:
* Select the hotel.
* After selecting, it will shows the available foods with their costs.
* Select the food and enter the number of items to order.
* Once you selected all the foods, choose cart.
![Screenshot (13)](https://user-images.githubusercontent.com/76902858/126878368-79a5e04e-0f79-4572-96c9-5ca1e31e0ee3.png)

### ORDER_BY_FOOD:
* Select the food you'd like to order in the list.
* Enter the number of items to order.
* Once you selected all the foods, choose cart.
![Screenshot (14)](https://user-images.githubusercontent.com/76902858/126878363-963a4684-f8a6-4954-8892-44a64d2a44d7.png)
![Screenshot (15)](https://user-images.githubusercontent.com/76902858/126878504-d12fec2e-53fb-4510-9bec-95ea07eb1912.png)


### CART:
* Display the food id, total count and price of each food, and total cost of your orders.
* If you want to add more in your cart, then you are allowed.
* Then, confirm your order and eat with joy... :)
![Screenshot (16)](https://user-images.githubusercontent.com/76902858/126878387-67732698-44b1-4dab-b6a6-2ea6a605fe2c.png)

### Order history:
* You can also view your history of your orders.
