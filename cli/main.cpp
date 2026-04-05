#include <iostream>
#include <string>
#include <limits>
#include "../include/LRUCache.hpp"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void printBanner() {
    std::cout << "==================================\n";
    std::cout << "      Cache Simulator v1.0        \n";
    std::cout << "       LRU Implementation         \n";
    std::cout << "==================================\n\n";
}

void printMenu() {
    std::cout << "----------------------------------\n";
    std::cout << "           MAIN MENU              \n";
    std::cout << "----------------------------------\n";
    std::cout << "  1. Put (insert / update)        \n";
    std::cout << "  2. Get (lookup key)             \n";
    std::cout << "  3. Display cache state          \n";
    std::cout << "  4. Exit                         \n";
    std::cout << "----------------------------------\n";
    std::cout << "Choice: ";
}

int getCapacityFromUser() {
    int capacity;
    while (true) {
        std::cout << "Enter cache capacity: ";
        std::cin >> capacity;
        if (std::cin.fail() || capacity <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Capacity must be a positive integer.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return capacity;
        }
    }
}

void handlePut(LRUCache<int, int>& cache) {
    int key, value;
    std::cout << "\nEnter key   : ";
    std::cin >> key;
    std::cout << "Enter value : ";
    std::cin >> value;
    cache.put(key, value);
    std::cout << "Inserted → key: " << key << " | value: " << value << "\n";
    pauseScreen();
}

void handleGet(LRUCache<int, int>& cache) {
    int key;
    std::cout << "\nEnter key to lookup: ";
    std::cin >> key;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    try {
        int value = cache.get(key);
        std::cout << "Hit! key: " << key << " → value: " << value << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Miss! key: " << key << " not found in cache.\n";
    }
    pauseScreen();
}

int main() {
    clearScreen();
    printBanner();

    int capacity = getCapacityFromUser();
    LRUCache<int, int> cache(capacity);

    std::cout << "\nCache initialized with capacity: " << capacity << "\n";
    pauseScreen();

    int choice;
    bool running = true;

    while (running) {
        clearScreen();
        printBanner();
        printMenu();

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            pauseScreen();
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                handlePut(cache);
                break;
            case 2:
                handleGet(cache);
                break;
            case 3:
                cache.display();
                pauseScreen();
                break;
            case 4:
                std::cout << "\nFinal Cache State:\n";
                cache.display();
                std::cout << "\nExiting Cache Simulator. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please select 1-4.\n";
                pauseScreen();
        }
    }

    return 0;
}