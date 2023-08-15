#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Item { // Item class to hold data 
private:
    std::string name;
    std::string category;
    int quantity;
    double price;

public:
    Item(std::string n, std::string c, int q, double p)
        : name(n), category(c), quantity(q), price(p) {} // Initializing 

    std::string getName() const { // get name function 
        return name;
    }

    std::string getCategory() const { // get category function
        return category;
    }

    int getQuantity() const { // get quantity function 
        return quantity;
    }

    double getPrice() const { // get price function 
        return price;
    }
};

class Inventory {
private:
    std::vector<Item> items;

public:
    void addItem(const Item& item) {
        items.push_back(item);
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const Item& item : items) {
                file << item.getName() << "," << item.getCategory() << ","
                    << item.getQuantity() << "," << item.getPrice() << "\n";
            }
            file.close();
            std::cout << " Inventory data saved to file: " << filename << "\n";
        }
        else {
            std::cout << " Error opening file for saving" << filename << "\n";
        }
        


    }

    void loadFromFile(const std::string& filename) { // load file function to load inventory

        std::ifstream file(filename);   
        if (file.is_open()) {
            items.clear();

            std::string name, category, line;
            int quantity;
            double price;

            while (std::getline(file, line)) {
                std::istringstream iss(line);

                if (std::getline(iss, name, ',') &&
                    std::getline(iss, category, ',') &&
                    (iss >> quantity) && (iss.ignore(), true) &&
                    (iss >> price))
                {
                    addItem(Item(name, category, quantity, price));
                }
                else {
                    std::cout << "Error parsing line: " << line << "\n";
                }
            }
            file.close();
        }
        else {
            std::cout << "Error opening file: " << filename << "\n";
        }
    }


    void display() const { // Display items in inventory function
        for (const Item& item : items) {
            std::cout << "Name: " << item.getName() << "\n";
            std::cout << "Category: " << item.getCategory() << "\n";
            std::cout << "Quantity: " << item.getQuantity() << "\n";
            std::cout << "Price: " << item.getPrice() << "\n";
            std::cout << "-----------------------\n";
        }
    }

    bool isEmpty() const {
        return items.empty(); 
    } // is empty bool function incase text file is empty 
};

int main() {
    Inventory inventory;
    inventory.loadFromFile("inventory.txt");
    inventory.saveToFile("inventory.txt");

    int choice;
    do {
        std::cout << "This is a Inventory Management System \n";
        std::cout << "1. Add Item \n";
        std::cout << "2. Display Inventory\n";
        std::cout << "3. Save and Exit\n";
        std::cout << "4. Load Inventory from File\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name, category;
            int quantity;
            double price;

            std::cout << "Enter item name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter item category: ";
            std::getline(std::cin, category);

            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            std::cout << "Enter price in dollars please: ";
            std::cin >> price;

            inventory.addItem(Item(name, category, quantity, price)); 

            break;
        }
        case 2:
            if (inventory.isEmpty()) {
                std::cout << "The Inventory is empty.\n";
            }
            else {
                std::cout << " Inventory:\n";
                inventory.display();
            }
            break;

        case 3:
            inventory.saveToFile("inventory.txt");
            std::cout << "Inventory data saved. Exiting.\n";
            break;

        case 4: {
            std::cout << "Enter the name of the file to load from: ";
            std::string filename;
            std::cin.ignore();
            std::getline(std::cin, filename);

            inventory.loadFromFile(filename); // calling load from file 


            if (!inventory.isEmpty()) {
                std::cout << "Inventory loaded from file.\n";
            }
            else {
                std::cout << "Error loading inventory from file.\n";
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 3);

    return 0;
} // end main 
