#include <algorithm>
#include <cstdbool>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

using namespace std;

class Delivery;
class Management;
class Supplier;
class Restaurant;
class Menu;
class Inventory;
class Order;
class Customer;
class FoodCart;

class Delivery {
public:
  string address;
  string userName;
  bool deliveryStatus;
  string driverName;
  int orderID;

public:
  Delivery(string address, string userName, bool deliveryStatus,
           string driverName, int orderID);

  virtual ~Delivery() {}

  // Check if the delivery order was made
  virtual bool isDeliveryOrderMade() const;
  // Perform actions to mark the order as delivered
  virtual void markDelivered();
  // Check if the restaurant has finished preparing the order and gave it to the driver
  virtual bool isPickedUpFromShop() const;
  // Display delivery information
  static void displayDeliveryInfo(Delivery *del);
};

class Management {
public:
  string restaurantID;
  string ownerID;
  string phoneNumber;
  string emailAddress;

public:
  Management(string restaurantID, string ownerID, string phoneNumber,
             string emailAddress);

  virtual ~Management() {}

  // Respond to customer issues
  virtual void respondCustomerIssues();
  // Order supplies for the restaurant
  virtual void orderSupplies();
  // Provide a discount to an unhappy customer
  virtual void provideDiscountUnhappyCustomer();
  // Convert Management object to string
  virtual string toString() const;
  // Increase the price of menu items
  virtual void increaseMenuPrice();
  // Decrease the price of menu items
  virtual void decreaseMenuPrice();
};

class Supplier {
public:
  string supplierID;
  string restaurantID;
  string ingredientsID;
  string email;
  string address;
  string inventoryOrderStatus;
  int estimatedArrivalTime;

public:
  Supplier(string supplierID, string restaurantID, string ingredientsID,
           string email, string address, string inventoryOrderStatus,
           int estimatedArrivalTime);

  virtual ~Supplier() {}

  // Receive restaurant order
  virtual void receivingRestaurantOrder();
  // Assign a driver for delivery
  virtual void assignDriver();
  // Send order confirmation to the restaurant
  virtual void sendOrderConfirmation();
  // Send estimated arrival time to the restaurant
  virtual void sendEstimatedArrivalTime();
  // Fill the order by preparing the items
  virtual void fillingOrder();
  // Add items to the order
  virtual void addItemsOrder();
  // Remove items from the order
  virtual void removeItemsOrder();
};

class Restaurant {
public:
  string restaurantName;
  string restaurantID;
  string orderID;
  string restaurantAddress;

public:
  Restaurant(string restaurantName, string restaurantID, string orderID,
             string restaurantAddress);

  virtual ~Restaurant() {}

  // Remove a menu item from the restaurant
  virtual void removeMenuItem();
  // Add a menu item to the restaurant
  virtual void addMenuItem();
  // Address order issues
  virtual void addressOrderIssues();
  // Check the status of orders in the kitchen
  virtual void kitchenOrderStatus();
};

class Menu {
public:
  string name;
  Restaurant *restaurant;
  vector<string> items;
  int price;

public:
  Menu(string name, Restaurant *restaurant, vector<string> items, int price);

  virtual ~Menu() {}

  // Add a menu to the restaurant
  virtual void addMenu();
  // Add items to the menu
  virtual void addItems();
  // Remove items from the menu
  virtual void removeItems();
  // Display the menu
  virtual void displayMenu();
};

class Inventory {
public:
  string ingredientID;
  string restaurantID;
  string supplierID;
  string nameIngredient;

public:
  Inventory(string ingredientID, string restaurantID, string supplierID,
            string nameIngredient);

  virtual ~Inventory() {}

  // Mark that a meal has been made using the inventory
  virtual void mealMade();
  // Remove inventory items
  virtual void removeInventory();
  // Add inventory items
  virtual void addInventory();
  // Get details about the ingredients in the inventory
  virtual void ingredientsDetails();
};

class Order {
public:
  int orderID;
  string customerName;
  Restaurant *restaurant;
  int price;

public:
  Order(int orderID, string customerName, Restaurant *restaurant, int price);

  virtual ~Order() {}

  // Submit the order
  virtual void submitOrder();
  // Restaurant accepts the order
  virtual void restaurantAcceptOrder();
  // Save the order
  virtual void saveOrder();
  // Convert Order object to string
  virtual string toString() const;
};

class Customer {
public:
  string address;
  string favoriteRestaurant;
  string cartID;
  string favoriteOrder;
  string customerID;

public:
  Customer(string address, string favoriteRestaurant, string cartID,
           string favoriteOrder, string customerID);

  virtual ~Customer() {}

  // Set up a customer account
  virtual void setUpAccount();
  // Add items to the customer's cart
  virtual void addItems();
  // Remove items from the customer's cart
  virtual void removeItems();
  // Choose a delivery type
  virtual void chooseType();
};

class FoodCart {
public:
  string customerID;
  string orderID;
  string cartID;
  string restaurantID;

public:
  FoodCart(string customerID, string orderID, string cartID,
           string restaurantID);

  virtual ~FoodCart() {}

  // Add an item to the cart
  virtual void addItemCart();
  // Remove an item from the cart
  virtual void removeItemCart();
  // Proceed to checkout
  virtual void checkout();
  // Display the order status
  virtual void displayOrderStatus();
  // Send the order receipt
  virtual void sendOrderReceipt();
};


