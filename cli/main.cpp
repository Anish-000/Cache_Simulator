#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include "../include/LRUCache.hpp"
#include "../include/LFUCache.hpp"
#include "../include/FIFOCache.hpp"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void printBanner() {
    std::cout << "==================================\n";
    std::cout << "      Cache Simulator v1.0        \n";
    std::cout << "==================================\n\n";
}

void printPolicyMenu() {
    std::cout << "----------------------------------\n";
    std::cout << "       SELECT CACHE POLICY        \n";
    std::cout << "----------------------------------\n";
    std::cout << "  1. LRU (Least Recently Used)    \n";
    std::cout << "  2. LFU (Least Frequently Used)  \n";
    std::cout << "  3. FIFO (First In First Out)    \n";
    std::cout << "----------------------------------\n";
    std::cout << "Choice: ";
}

void printMenu(const std::string& policy) {
    std::cout << "----------------------------------\n";
    std::cout << "     MAIN MENU [" << policy << "]          \n";
    std::cout << "----------------------------------\n";
    std::cout << "  1. Put (insert / update)        \n";
    std::cout << "  2. Get (lookup key)             \n";
    std::cout << "  3. Display cache state          \n";
    std::cout << "  4. Change policy                \n";
    std::cout << "  5. Exit                         \n";
    std::cout << "----------------------------------\n";
    std::cout << "Choice: ";
}

int getValidInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

void handlePut(CachePolicy<int, int>& cache) {
    int key = getValidInt("\nEnter key   : ");
    int value = getValidInt("Enter value : ");
    cache.put(key, value);
    std::cout << "Inserted -> key: " << key << " | value: " << value << "\n";
    pauseScreen();
}

void handleGet(CachePolicy<int, int>& cache) {
    int key = getValidInt("\nEnter key to lookup: ");
    try {
        int value = cache.get(key);
        std::cout << "Hit! key: " << key << " -> value: " << value << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Miss! key: " << key << " not found in cache.\n";
    }
    pauseScreen();
}

std::unique_ptr<CachePolicy<int, int>> selectPolicy(int& capacity) {
    int policyChoice = getValidInt("");
    capacity = getValidInt("Enter cache capacity: ");

    switch (policyChoice) {
        case 1:
            std::cout << "LRU Cache initialized with capacity: " << capacity << "\n";
            return std::make_unique<LRUCache<int, int>>(capacity);
        case 2:
            std::cout << "LFU Cache initialized with capacity: " << capacity << "\n";
            return std::make_unique<LFUCache<int, int>>(capacity);
        case 3:
            std::cout << "FIFO Cache initialized with capacity: " << capacity << "\n";
            return std::make_unique<FIFOCache<int, int>>(capacity);
        default:
            std::cout << "Invalid choice. Defaulting to LRU.\n";
            return std::make_unique<LRUCache<int, int>>(capacity);
    }
}

int main() {
    clearScreen();
    printBanner();
    printPolicyMenu();

    int capacity = 0;
    std::string policyNames[] = {"", "LRU", "LFU", "FIFO"};
    int policyChoice = 1;

    auto cache = selectPolicy(capacity);
    pauseScreen();

    int choice;
    bool running = true;
    std::string currentPolicy = "LRU";

    while (running) {
        clearScreen();
        printBanner();
        printMenu(currentPolicy);

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
                handlePut(*cache);
                break;
            case 2:
                handleGet(*cache);
                break;
            case 3:
                cache->display();
                pauseScreen();
                break;
            case 4:
                clearScreen();
                printBanner();
                printPolicyMenu();
                cache = selectPolicy(capacity);
                currentPolicy = policyNames[policyChoice];
                pauseScreen();
                break;
            case 5:
                std::cout << "\nFinal Cache State:\n";
                cache->display();
                std::cout << "\nExiting Cache Simulator. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please select 1-5.\n";
                pauseScreen();
        }
    }

    return 0;
}