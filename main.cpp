/*
-------------------------------------------------------
Disaster Response & Relief Resource Management System
Author: Mazhar Ali
Course: Programming Fundamentals
Concepts Used:
- Arrays
- Structures
- File Handling
- Functions
- Menu Driven Program
-------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

const int MAX_ITEMS = 50;

// ================= STRUCTURES =================

struct Resource {
    int id;
    string name;
    int quantity;
};

struct Area {
    int id;
    string city;
    int population;
    string disasterType;
    string severity;
};

// ================= UTILITY =================

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ================= FILE HANDLING =================

void saveResources(Resource r[], int count) {
    ofstream file("resources.txt");
    if (!file) return;

    for (int i = 0; i < count; i++) {
        file << r[i].id << endl;
        file << r[i].name << endl;
        file << r[i].quantity << endl;
    }
    file.close();
}

void loadResources(Resource r[], int &count) {
    ifstream file("resources.txt");
    count = 0;
    if (!file) return;

    while (count < MAX_ITEMS && file >> r[count].id) {
        file.ignore();
        getline(file, r[count].name);
        file >> r[count].quantity;
        file.ignore();
        count++;
    }
    file.close();
}

void saveAreas(Area a[], int count) {
    ofstream file("areas.txt");
    if (!file) return;

    for (int i = 0; i < count; i++) {
        file << a[i].id << endl;
        file << a[i].city << endl;
        file << a[i].population << endl;
        file << a[i].disasterType << endl;
        file << a[i].severity << endl;
    }
    file.close();
}

void loadAreas(Area a[], int &count) {
    ifstream file("areas.txt");
    count = 0;
    if (!file) return;

    while (count < MAX_ITEMS && file >> a[count].id) {
        file.ignore();
        getline(file, a[count].city);
        file >> a[count].population;
        file.ignore();
        getline(file, a[count].disasterType);
        getline(file, a[count].severity);
        count++;
    }
    file.close();
}

// ================= RESOURCE MANAGEMENT =================

void addResource(Resource r[], int &count) {
    if (count >= MAX_ITEMS) {
        cout << "Limit reached.\n";
        return;
    }

    cout << "Enter Resource ID: ";
    cin >> r[count].id;
    clearInput();

    cout << "Enter Resource Name: ";
    getline(cin, r[count].name);

    cout << "Enter Quantity: ";
    cin >> r[count].quantity;
    clearInput();

    count++;
    cout << "Resource added successfully!\n";
}

void viewResources(Resource r[], int count) {
    if (count == 0) {
        cout << "No resources available.\n";
        return;
    }

    cout << "\n--- Resources ---\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << r[i].id
             << " | Name: " << r[i].name
             << " | Qty: " << r[i].quantity << endl;
    }
}

void updateResource(Resource r[], int count) {
    int id;
    cout << "Enter Resource ID to update: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (r[i].id == id) {
            cout << "Current Quantity: " << r[i].quantity << endl;
            cout << "Enter New Quantity: ";
            cin >> r[i].quantity;
            cout << "Resource updated successfully!\n";
            return;
        }
    }
    cout << "Resource not found.\n";
}

// ================= AREA MANAGEMENT =================

void addArea(Area a[], int &count) {
    if (count >= MAX_ITEMS) {
        cout << "Limit reached.\n";
        return;
    }

    cout << "Enter Area ID: ";
    cin >> a[count].id;
    clearInput();

    cout << "Enter City: ";
    getline(cin, a[count].city);

    cout << "Enter Population: ";
    cin >> a[count].population;
    clearInput();

    cout << "Enter Disaster Type: ";
    getline(cin, a[count].disasterType);

    cout << "Severity (1-Low, 2-Average, 3-High): ";
    int s;
    cin >> s;
    clearInput();

    if (s == 1) a[count].severity = "Low";
    else if (s == 2) a[count].severity = "Average";
    else a[count].severity = "High";

    count++;
    cout << "Area added successfully!\n";
}

void viewAreas(Area a[], int count) {
    if (count == 0) {
        cout << "No areas available.\n";
        return;
    }

    cout << "\n--- Areas ---\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << a[i].id
             << " | City: " << a[i].city
             << " | Pop: " << a[i].population
             << " | Disaster: " << a[i].disasterType
             << " | Severity: " << a[i].severity << endl;
    }
}

void updateArea(Area a[], int count) {
    if (count == 0) {
        cout << "No areas available.\n";
        return;
    }

    int id;
    cout << "Enter Area ID to update: ";
    cin >> id;
    clearInput();

    for (int i = 0; i < count; i++) {
        if (a[i].id == id) {

            cout << "Current Population: " << a[i].population << endl;
            cout << "Enter New Population: ";
            cin >> a[i].population;
            clearInput();

            cout << "Enter New Disaster Type: ";
            getline(cin, a[i].disasterType);

            cout << "Enter New Severity (1-Low, 2-Average, 3-High): ";
            int s;
            cin >> s;
            clearInput();

            if (s == 1) a[i].severity = "Low";
            else if (s == 2) a[i].severity = "Average";
            else if (s == 3) a[i].severity = "High";

            cout << "Area updated successfully!\n";
            return;
        }
    }
    cout << "Area not found.\n";
}

// ================= ALLOCATION =================

void appendAllocation(string entry) {
    ofstream file("allocations.txt", ios::app);
    file << entry << endl;
    file.close();
}

void allocate(Resource r[], int rCount, Area a[], int aCount) {
    if (rCount == 0 || aCount == 0) {
        cout << "Resources or Areas missing.\n";
        return;
    }

    int areaID;
    cout << "Enter Area ID: ";
    cin >> areaID;

    int areaIndex = -1;
    for (int i = 0; i < aCount; i++) {
        if (a[i].id == areaID) {
            areaIndex = i;
            break;
        }
    }

    if (areaIndex == -1) {
        cout << "Invalid Area ID.\n";
        return;
    }

    int suggested;
    if (a[areaIndex].severity == "High")
        suggested = a[areaIndex].population * 20 / 100;
    else if (a[areaIndex].severity == "Average")
        suggested = a[areaIndex].population * 10 / 100;
    else
        suggested = a[areaIndex].population * 5 / 100;

    cout << "Suggested Allocation: " << suggested << endl;

    int resID;
    cout << "Enter Resource ID: ";
    cin >> resID;

    int resIndex = -1;
    for (int i = 0; i < rCount; i++) {
        if (r[i].id == resID) {
            resIndex = i;
            break;
        }
    }

    if (resIndex == -1) {
        cout << "Invalid Resource ID.\n";
        return;
    }

    int amount;
    cout << "Enter Quantity to Allocate: ";
    cin >> amount;

    if (amount > r[resIndex].quantity) {
        cout << "WARNING: Not enough resources. Allocating all available.\n";
        amount = r[resIndex].quantity;
    }

    r[resIndex].quantity -= amount;

    string entry =
        "Area: " + a[areaIndex].city +
        " | Resource: " + r[resIndex].name +
        " | Allocated: " + to_string(amount) +
        " | Severity: " + a[areaIndex].severity;

    appendAllocation(entry);

    cout << "Allocation successful.\n";
}

// ================= REPORT =================

void viewReport() {
    ifstream file("allocations.txt");
    if (!file) {
        cout << "No report found.\n";
        return;
    }

    cout << "\n--- Relief Report ---\n";
    string line;
    while (getline(file, line))
        cout << line << endl;

    file.close();
}

// ================= SUMMARY =================

void systemSummary(Resource r[], int rCount, Area a[], int aCount) {
    int totalQty = 0;
    for (int i = 0; i < rCount; i++)
        totalQty += r[i].quantity;

    cout << "\n===== SYSTEM SUMMARY =====\n";
    cout << "Total Resources: " << rCount << endl;
    cout << "Total Areas: " << aCount << endl;
    cout << "Total Available Units: " << totalQty << endl;
}

// ================= MAIN =================

int main() {
    Resource resources[MAX_ITEMS];
    Area areas[MAX_ITEMS];

    int resourceCount = 0;
    int areaCount = 0;

    loadResources(resources, resourceCount);
    loadAreas(areas, areaCount);

    int choice;

    do {
        cout << "\n===== DRRS MAIN MENU =====\n";
        cout << "1. Add Resource\n";
        cout << "2. View Resources\n";
        cout << "3. Update Resource\n";
        cout << "4. Add Area\n";
        cout << "5. View Areas\n";
        cout << "6. Update Area\n";
        cout << "7. Allocate Resources\n";
        cout << "8. View Report\n";
        cout << "9. System Summary\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addResource(resources, resourceCount); break;
            case 2: viewResources(resources, resourceCount); break;
            case 3: updateResource(resources, resourceCount); break;
            case 4: addArea(areas, areaCount); break;
            case 5: viewAreas(areas, areaCount); break;
            case 6: updateArea(areas, areaCount); break;
            case 7: allocate(resources, resourceCount, areas, areaCount); break;
            case 8: viewReport(); break;
            case 9: systemSummary(resources, resourceCount, areas, areaCount); break;
            case 10:
                saveResources(resources, resourceCount);
                saveAreas(areas, areaCount);
                cout << "Data saved. Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 10);

    return 0;
}
