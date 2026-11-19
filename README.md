<div align="center">

# 🍽️ Restaurant Menu Card & Billing System

**A console-based restaurant management and billing application built with C++.**

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/C%2B%2B-14-orange.svg)](https://en.cppreference.com/w/cpp/14.html)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

</div>

---

## 📌 Overview

The **Restaurant Menu Card & Billing System** is a menu and billing application developed in C++. It allows a restaurant operator to view menu items, add new food or beverage items, update item prices, and generate customer bills through a simple menu-driven interface.

The project demonstrates core C++ concepts, particularly **Object-Oriented Programming (OOP)**, inheritance, runtime polymorphism, dynamic memory management, and file handling.

## ✨ Features

- **Display Menu:** View all available food and beverage items with their IDs and prices.
- **Generate Bill:** Select menu items by ID, enter quantities, and calculate the total amount.
- **Add Menu Items:** Add new food or beverage items with automatically generated IDs.
- **Update Prices:** Change the price of an existing menu item.
- **Persistent Menu Storage:** Save menu data in `menu.txt` and load it when the program starts.
- **Bill History:** Append generated bills to `bill.txt`.
- **Input Validation:** Handle invalid menu choices, item IDs, prices, and quantities.
- **Default Menu:** Create a starter menu automatically when no menu data file exists.

## 🛠️ Technologies & Concepts

| Technology / Concept | Usage |
|---|---|
| C++14 | Core programming language |
| Classes and Objects | Represent menu items |
| Inheritance | `FoodItem` and `BeverageItem` inherit from `MenuItem` |
| Runtime Polymorphism | Virtual functions and overridden `getType()` |
| Encapsulation | Menu item data is maintained through class members |
| STL `vector` | Store menu items dynamically |
| Smart Pointers | Manage menu item memory using `unique_ptr` |
| File Handling | Read and write menu and bill records |
| Input Validation | Handle invalid user input |

## 📂 Project Structure

```text
Restaurant-Menu-Card/
│
├── restaurant.cpp   # Main C++ source code
├── menu.txt         # Persistent menu data
├── bill.txt         # Generated bill records
├── run.txt          # Sample run / output reference
├── restaurant.exe   # Windows executable (if included)
└── README.md        # Project documentation
```

> The program creates `menu.txt` automatically with default menu items if the file does not already exist. Generated bills are appended to `bill.txt`.

## ⚙️ Requirements

- A C++ compiler with **C++14** support, such as GCC, MinGW, or Clang.
- A terminal or command prompt.
- No external libraries are required.

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/Kunalshejwal01/Restaurant-Menu-Card.git
```

### 2. Open the project directory

```bash
cd Restaurant-Menu-Card
```

### 3. Compile the program

**Using GCC / MinGW:**

```bash
g++ -std=c++14 restaurant.cpp -o restaurant
```

### 4. Run the program

**Windows:**

```bash
restaurant.exe
```

**Linux / macOS:**

```bash
./restaurant
```

## 🧾 How to Use

After launching the program, the following menu is displayed:

```text
===== RESTAURANT BILLING SYSTEM =====
1. Display Menu
2. Generate Bill
3. Add Item
4. Update Price
5. Exit

Enter choice:
```

Choose an option by entering its corresponding number.

| Option | Operation |
|---|---|
| 1 | Display all menu items |
| 2 | Generate a bill by entering item IDs and quantities |
| 3 | Add a food or beverage item |
| 4 | Update the price of an existing item |
| 5 | Exit the application |

### Default Menu Items

If `menu.txt` is not present when the program starts, the application initializes the following sample items:

| ID | Item | Category | Price |
|---:|---|---|---:|
| 101 | Burger | Food | ₹120 |
| 102 | Pizza | Food | ₹220 |
| 103 | Fries | Food | ₹90 |
| 201 | Cold Coffee | Beverage | ₹100 |
| 202 | Lemon Juice | Beverage | ₹60 |

### Bill Calculation

The application calculates each item's amount using:

```text
Item Amount = Item Price × Quantity
Total Bill  = Sum of all Item Amounts
```

Enter `0` as the item ID to finish entering items and display the total bill.

## 🧠 Object-Oriented Design

The application uses a base class and two derived classes:

```text
              MenuItem
              /      \
             /        \
        FoodItem   BeverageItem
```

- **`MenuItem`:** Base class containing the item ID, name, price, and common operations.
- **`FoodItem`:** Derived class representing food products.
- **`BeverageItem`:** Derived class representing beverages.

The virtual `getType()` function is overridden in the derived classes to identify the category of each menu item. Menu objects are managed using `unique_ptr` and stored in a `vector`.

## 💾 Data Storage

The project uses text files for basic data persistence:

- **`menu.txt`:** Stores menu records in the format `Type|ID|Name|Price`.
- **`bill.txt`:** Stores generated bill details. New bills are appended to the file.

Keep these files in the same working directory from which you run the application.

## ⚠️ Limitations

- The application is console-based and does not include a graphical user interface.
- It does not use a database; data is stored in text files.
- The menu supports a maximum of 50 items.
- It is a basic billing application and does not include user authentication, tax calculation, or online payment integration.

## 🔮 Future Improvements

- Add item deletion and item-name editing.
- Add customer details and bill numbers.
- Include GST and discount calculations.
- Add search and category filters.
- Introduce a graphical user interface.
- Replace text-file storage with a database.
- Add printable receipts and daily sales reports.

## 👨‍💻 Author

**Kunal Shejwal**

GitHub: [@Kunalshejwal01](https://github.com/Kunalshejwal01)

## 📄 License

No license has been specified for this repository. Contact the repository owner before reusing or distributing the project.

---

<div align="center">

**Thank you for checking out this project!**

</div>
