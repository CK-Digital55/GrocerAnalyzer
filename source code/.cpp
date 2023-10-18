#include <iostream>
#include <fstream>
#include <map>
#include <string>

class GrocerAnalyzer {
private:
    std::map<std::string, int> dataMap;

public:
    GrocerAnalyzer() {}

    bool loadData(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            return false; // File not opened successfully
        }

        std::string item;
        while (inputFile >> item) {
            dataMap[item]++;
        }

        inputFile.close();
        return true;
    }

    int getItemFrequency(const std::string& item) {
        if (dataMap.find(item) != dataMap.end()) {
            return dataMap[item];
        }
        return 0; // Item not found
    }

    void printAllFrequencies() {
        for (const auto& pair : dataMap) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    void printHistogram() {
        for (const auto& pair : dataMap) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

    void saveDataToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        for (const auto& pair : dataMap) {
            outFile << pair.first << " " << pair.second << std::endl;
        }
        outFile.close();
    }
};

int main() {
    GrocerAnalyzer analyzer;
    if (!analyzer.loadData("CS210_Project_Three_Input_File.txt")) {
        std::cout << "Error loading the data file." << std::endl;
        return 1; // Return with an error code
    }

    analyzer.saveDataToFile("frequency.dat");

    int choice = 0;
    while (choice != 4) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Check Frequency of an Item\n";
        std::cout << "2. Print Frequencies of All Items\n";
        std::cout << "3. Print Histogram of All Items\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
        {
            std::cout << "Enter the item name: ";
            std::string item;
            std::cin >> item;
            std::cout << "Frequency of " << item << ": " << analyzer.getItemFrequency(item) << std::endl;
        }
        break;
        case 2:
            analyzer.printAllFrequencies();
            break;
        case 3:
            analyzer.printHistogram();
            break;
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Try again.\n";
            break;
        }
    }

    return 0;
}
