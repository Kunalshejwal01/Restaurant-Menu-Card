#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

class MenuItem {
protected:
    int id;
    string name;
    float price;

public:
    MenuItem(int i, string n, float p) : id(i), name(move(n)), price(p) {}
    virtual ~MenuItem() = default;
    virtual char getType() const = 0;

    int getId() const { return id; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    void setPrice(float p) { price = p; }

    void display() const {
        cout << left << setw(6) << id << setw(16) << name
             << setw(12) << (getType() == 'F' ? "Food" : "Beverage") << "Rs. " << price << endl;
    }
};

class FoodItem : public MenuItem {
public:
    using MenuItem::MenuItem;
    char getType() const override { return 'F'; }
};

class BeverageItem : public MenuItem {
public:
    using MenuItem::MenuItem;
    char getType() const override { return 'B'; }
};

const size_t MAX_ITEMS = 50;
vector<unique_ptr<MenuItem>> menu;

// Reads one value and discards the rest of the line; survives bad input.
template <class T>
bool read(T& value) {
    bool ok = static_cast<bool>(cin >> value);
    if (cin.eof()) exit(0);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return ok;
}

MenuItem* findItem(int id) {
    for (auto& item : menu)
        if (item->getId() == id) return item.get();
    return nullptr;
}

void addToMenu(char type, int id, const string& name, float price) {
    if (type == 'F') menu.push_back(make_unique<FoodItem>(id, name, price));
    else             menu.push_back(make_unique<BeverageItem>(id, name, price));
}

void saveMenu() {
    ofstream file("menu.txt");
    for (auto& item : menu)
        file << item->getType() << "|" << item->getId() << "|"
             << item->getName() << "|" << item->getPrice() << endl;
}

void loadMenu() {
    ifstream file("menu.txt");
    bool exists = file.is_open();
    istringstream defaults("F|101|Burger|120\nF|102|Pizza|220\nF|103|Fries|90\n"
                           "B|201|Cold Coffee|100\nB|202|Lemon Juice|60\n");
    istream& in = exists ? static_cast<istream&>(file) : defaults;

    string line;
    while (getline(in, line) && menu.size() < MAX_ITEMS) {
        istringstream ss(line);
        char type = 0;
        int id = 0;
        string name;
        float price = 0;

        ss >> type;
        ss.ignore();
        ss >> id;
        ss.ignore();
        getline(ss, name, '|');
        ss >> price;

        if (ss && (type == 'F' || type == 'B') && price > 0 && !findItem(id))
            addToMenu(type, id, name, price);
    }

    if (!exists) saveMenu();
}

void displayMenu() {
    cout << "\n========== MENU ==========\n";
    cout << left << setw(6) << "ID" << setw(16) << "Name" << setw(12) << "Category" << "Price\n";
    for (auto& item : menu)
        item->display();
}

void addItem() {
    int choice = 0;
    float price = 0;
    string name;

    if (menu.size() >= MAX_ITEMS) {
        cout << "Menu is full!\n";
        return;
    }

    cout << "\n1. Food\n2. Beverage\nSelect category: ";
    if (!read(choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid category!\n";
        return;
    }

    cout << "Enter item name: ";
    getline(cin, name);
    if (name.empty() || name.find('|') != string::npos) {
        cout << "Invalid name!\n";
        return;
    }

    cout << "Enter price: ";
    if (!read(price) || price <= 0) {
        cout << "Invalid price!\n";
        return;
    }

    int id = 100;
    for (auto& item : menu)
        id = max(id, item->getId());
    id++;

    addToMenu(choice == 1 ? 'F' : 'B', id, name, price);
    saveMenu();
    cout << "Item added successfully! ID: " << id << endl;
}

void updatePrice() {
    int id = 0;
    float price = 0;

    cout << "Enter Item ID: ";
    read(id);

    MenuItem* item = findItem(id);
    if (!item) {
        cout << "Item not found!\n";
        return;
    }

    cout << "Current Price: Rs. " << item->getPrice() << "\nEnter New Price: ";
    if (!read(price) || price <= 0) {
        cout << "Invalid price!\n";
        return;
    }

    item->setPrice(price);
    saveMenu();
    cout << "Price updated successfully!\n";
}

void generateBill() {
    float total = 0;

    ofstream file("bill.txt", ios::app);
    if (!file) {
        cout << "File opening error!\n";
        return;
    }
    file << fixed << setprecision(2) << "\n========== NEW BILL ==========\n";

    while (true) {
        int id = 0, quantity = 0;

        cout << "\nEnter Item ID (0 to finish): ";
        if (!read(id)) {
            cout << "Invalid Item ID!\n";
            continue;
        }
        if (id == 0)
            break;

        MenuItem* item = findItem(id);
        if (!item) {
            cout << "Invalid Item ID!\n";
            continue;
        }

        cout << "Enter Quantity: ";
        if (!read(quantity) || quantity <= 0) {
            cout << "Invalid quantity!\n";
            continue;
        }

        float amount = item->getPrice() * quantity;
        total += amount;

        cout << item->getName() << " = Rs. " << amount << endl;
        file << item->getName() << " x " << quantity << " = Rs. " << amount << endl;
    }

    cout << "\nTotal Bill: Rs. " << total << endl;
    file << "Total Bill: Rs. " << total << endl;
    cout << "Bill saved successfully!\n";
}

int main() {
    int choice = 0;

    cout << fixed << setprecision(2);
    loadMenu();

    do {
        cout << "\n===== RESTAURANT BILLING SYSTEM =====\n"
                "1. Display Menu\n"
                "2. Generate Bill\n"
                "3. Add Item\n"
                "4. Update Price\n"
                "5. Exit\n"
                "Enter choice: ";
        if (!read(choice))
            choice = 0;

        switch (choice) {
            case 1: displayMenu();   break;
            case 2: generateBill();  break;
            case 3: addItem();       break;
            case 4: updatePrice();   break;
            case 5: cout << "Thank you for visiting!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}