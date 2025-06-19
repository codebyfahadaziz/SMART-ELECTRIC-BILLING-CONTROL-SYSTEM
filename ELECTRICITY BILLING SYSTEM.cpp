#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

// ===== Appliance Class =====
class Appliance {
public:
    string name;
    int quantity;
    int hoursPerDay;
    int powerWatts;

    Appliance(string n, int q, int h, int p) {
        name = n;
        quantity = q;
        hoursPerDay = h;
        powerWatts = p;
    }

    double monthlyUnits() {
        return quantity * (hoursPerDay * powerWatts * 30) / 1000.0;
    }
};

// ===== BillCalculator Class =====
class BillCalculator {
public:
    static double calculateBill(double units, int userType) {
        double slab1_rate = 10.0;
        double slab2_rate = 15.0;
        double slab3_rate = 20.0;

        double commercial_slab1_rate = 12.0;
        double commercial_slab2_rate = 18.0;
        double commercial_slab3_rate = 25.0;

        double bill = 0.0;

        if (userType == 1) {
            if (units <= 100)
                bill = units * slab1_rate;
            else if (units <= 300)
                bill = 100 * slab1_rate + (units - 100) * slab2_rate;
            else
                bill = 100 * slab1_rate + 200 * slab2_rate + (units - 300) * slab3_rate;
        } else {
            if (units <= 100)
                bill = units * commercial_slab1_rate;
            else if (units <= 300)
                bill = 100 * commercial_slab1_rate + (units - 100) * commercial_slab2_rate;
            else
                bill = 100 * commercial_slab1_rate + 200 * commercial_slab2_rate + (units - 300) * commercial_slab3_rate;
        }

        return bill;
    }
};

// ===== SuggestionEngine Class =====
class SuggestionEngine {
public:
    static void suggestReduction(vector<Appliance>& appliances, double currentUnits, double targetReduction) {
        cout << "\n--- Suggestions to Reduce Your Bill ---\n";
        double reduced = 0;

        int size = (int)appliances.size();
        for (int i = 0; i < size; i++) {
            double usage = appliances[i].monthlyUnits();

            if (usage > 5 && reduced < targetReduction) {
                double saved = (appliances[i].quantity * appliances[i].powerWatts * 30) / 1000.0;
                cout << "- Use " << appliances[i].name << " for 1 hour less/day. Saves ~" << saved << " units/month.\n";
                reduced += saved;
            }
        }

        if (reduced < targetReduction) {
            cout << "- Also consider using energy-efficient models (e.g., inverter AC, LED lights).\n";
        }
    }
};

// ===== UserAccount Class =====
class UserAccount {
public:
    string referenceNumber;
    string password;

    UserAccount(string ref, string pass) {
        referenceNumber = ref;
        password = pass;
    }
};

vector<UserAccount> users;

UserAccount* findUser(string ref) {
    int size = (int)users.size();
    for (int i = 0; i < size; i++) {
        if (users[i].referenceNumber == ref)
            return &users[i];
    }
    return NULL;
}

UserAccount* loginOrRegister() {
    cout << "\nAre you a permanent user? (yes / no): ";
    string ans;
    cin >> ans;
    for (int i = 0; (unsigned)i < ans.length(); i++)
        ans[i] = (char)tolower(ans[i]);

    if (ans == "no") {
        cout << "Enter new reference number: ";
        string ref;
        cin >> ref;
        if (findUser(ref)) {
            cout << "Account with this reference number already exists.\n";
            return NULL;
        }

        cout << "Set a password: ";
        string pass;
        cin >> pass;
        users.push_back(UserAccount(ref, pass));
        cout << "Account created successfully!\n";
        return &users.back();
    }
    else {
        cout << "Enter reference number: ";
        string ref;
        cin >> ref;
        UserAccount* user = findUser(ref);
        if (!user) {
            cout << "No account found. Please register first.\n";
            return NULL;
        }
        cout << "Enter password: ";
        string pass;
        cin >> pass;
        if (user->password != pass) {
            cout << "Incorrect password.\n";
            return NULL;
        }
        cout << "Login successful!\n";
        return user;
    }
}

// ===== SolarUser Class =====
class SolarUser {
private:
    bool hasSolarPanel;
    double solarGeneration;
    double totalConsumption;
    double profitLastMonth;
    double desiredProfit;
    const double ratePerKWh;

public:
    SolarUser() : hasSolarPanel(false), solarGeneration(0), totalConsumption(0),
                  profitLastMonth(0), desiredProfit(0), ratePerKWh(12.0) {}

    void userDetails() {
        string input;
        while (true) {
            cout << "Do You Have Solar Panels Installed? (yes / no): ";
            cin >> input;
            for (int i = 0; (unsigned)i < input.length(); i++)
                input[i] = (char)tolower(input[i]);

            if (input == "yes") {
                hasSolarPanel = true;
                break;
            } else if (input == "no") {
                hasSolarPanel = false;
                break;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no'.\n";
            }
        }

        cout << "Enter Your Total Monthly Energy Consumption (kWh): ";
        while (!(cin >> totalConsumption)) {
            cout << "Invalid input. Please enter a numeric value for total consumption: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (hasSolarPanel) {
            while (true) {
                cout << "Did you make money from your solar system last month? (yes / no): ";
                cin >> input;
                for (int i = 0; (unsigned)i < input.length(); i++)
                    input[i] = (char)tolower(input[i]);

                if (input == "yes") {
                    cout << "How much did you make last month? Rs. ";
                    while (!(cin >> profitLastMonth)) {
                        cout << "Invalid input. Please enter a numeric value for profit: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    do {
                        cout << "How much more money do you want to make this month? Rs. ";
                        while (!(cin >> desiredProfit)) {
                            cout << "Invalid input. Please enter a numeric value for desired profit: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (desiredProfit <= profitLastMonth) {
                            cout << "Desired profit must be greater than last month's profit. Please enter again.\n";
                        }
                    } while (desiredProfit <= profitLastMonth);
                    break;
                }
                else if (input == "no") {
                    profitLastMonth = 0;
                    desiredProfit = 0;
                    break;
                }
                else {
                    cout << "Invalid input. Please enter 'yes' or 'no'.\n";
                }
            }

            cout << "Enter Your Average Monthly Solar Energy Generation (kWh): ";
            while (!(cin >> solarGeneration)) {
                cout << "Invalid input. Please enter a numeric value for solar generation: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else {
            solarGeneration = 0;
            profitLastMonth = 0;
            desiredProfit = 0;
        }
    }

    double getNetUnits() {
        double net = totalConsumption - solarGeneration;
        if (net < 0) return 0.0;
        return net;
    }

    bool isMakingProfit() {
        return (profitLastMonth > 0);
    }

    double getProfitLastMonth() {
        return profitLastMonth;
    }

    double getDesiredProfit() {
        return desiredProfit;
    }

    bool getHasSolarPanel() {
        return hasSolarPanel;
    }

    void displaySolarSummary() {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "\n---- Solar Energy Summary ----\n";
        cout << "Total Consumption: " << totalConsumption << " kWh\n";
        cout << "Solar Generation: " << solarGeneration << " kWh\n";

        if (solarGeneration > totalConsumption) {
            double profitKWh = solarGeneration - totalConsumption;
            double profit = profitKWh * ratePerKWh;
            cout << "Surplus Energy: " << profitKWh << " kWh\n";
            cout << "Profit Earned: Rs. " << profit << "\n";

            if (desiredProfit > 0) {
                cout << "Desired Profit: Rs. " << desiredProfit << "\n";
                cout << "Increase solar generation or optimize usage to achieve your target profit.\n";
            }
        }
        else {
            double netBillable = totalConsumption - solarGeneration;
            cout << "Net Billable Units: " << netBillable << " kWh\n";
            cout << "Estimated Bill: Rs. " << (netBillable * ratePerKWh) << "\n";
        }

        cout << "\n--- Optimization Tips ---\n";
        if (!hasSolarPanel)
            cout << "Consider installing solar panels to reduce bills.\n";
        else if (solarGeneration < totalConsumption)
            cout << "Try increasing solar panel capacity or reducing usage.\n";
        else
            cout << "Excellent usage! You're energy positive.\n";
    }
};

// ===== Residential Class =====
class Residential {
private:
    SolarUser* solarUserPtr;
    vector<Appliance> appliances;

public:
    Residential(SolarUser* solarUserFromMain) {
        solarUserPtr = solarUserFromMain;
    }

    void run() {
        cout << "\n--- Residential User ---\n";

        cout << "\n--- Appliance Entry ---\n";
        int count;
        cout << "How many types of appliances do you want to enter? ";
        while (!(cin >> count) || count <= 0) {
            cout << "Invalid input. Please enter a positive integer for the number of appliances: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < count; ++i) {
            string name;
            int qty = 0, hours = 0, watts = 0;

            while (true) {
                cout << "Appliance #" << (i + 1) << " name: ";
                getline(cin, name);
                if (name.empty()) {
                    cout << "Appliance name cannot be empty. Please re-enter.\n";
                    continue;
                }
                if (!isalpha(name[0])) {
                    cout << "Appliance name must start with a letter. Please re-enter.\n";
                    continue;
                }
                break;
            }

            while (true) {
                cout << "Quantity of " << name << " (max 10): ";
                cin >> qty;
                if (qty > 0 && qty <= 10) break;
                cout << "Quantity must be between 1 and 10. Please re-enter.\n";
            }

            while (true) {
                cout << "Hours per day used (max 24): ";
                cin >> hours;
                if (hours >= 0 && hours <= 24) break;
                cout << "Please enter valid hours (0-24). Please re-enter.\n";
            }

            cout << "Power rating (Watts): ";
            cin >> watts;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            appliances.push_back(Appliance(name, qty, hours, watts));
        }

        double totalUnits = 0;
        int size = (int)appliances.size();
        for (int i = 0; i < size; ++i) {
            totalUnits += appliances[i].monthlyUnits();
        }

        cout << "\n--- Usage Summary ---\n";
        cout << "Total Units Used by Appliances: " << totalUnits << " kWh\n";

        double adjustedUnits = solarUserPtr->getNetUnits();
        double bill = BillCalculator::calculateBill(adjustedUnits, 1);
        cout << "Estimated Bill after Solar Adjustment: Rs. " << bill << "\n";

        double target;
        cout << "\nHow many units would you like to reduce monthly? ";
        while (!(cin >> target)) {
            cout << "Invalid input. Please enter a numeric value for target reduction: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        SuggestionEngine::suggestReduction(appliances, totalUnits, target);

        displaySummary(totalUnits, bill);
        solarUserPtr->displaySolarSummary();
    }

    void displaySummary(double totalUnits, double bill) {
        cout << "\n==============================\n";
        cout << "|          Summary Table      |\n";
        cout << "==============================\n";
        cout << left << setw(25) << "Total Units Used:" << totalUnits << " kWh\n";
        cout << left << setw(25) << "Estimated Bill:" << "Rs. " << bill << endl;
        cout << "====================================\n";
    }
};

// ===== Commercial Class =====
class Commercial {
private:
    SolarUser* solarUserPtr;
    vector<Appliance> appliances;

public:
    Commercial(SolarUser* solarUserFromMain) {
        solarUserPtr = solarUserFromMain;
    }

    void run() {
        cout << "\n--- Commercial User ---\n";

        cout << "\n--- Appliance Entry ---\n";
        int count;
        cout << "How many types of appliances do you want to enter? ";
        while (!(cin >> count) || count <= 0) {
            cout << "Invalid input. Please enter a positive integer for the number of appliances: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < count; ++i) {
            string name;
            int qty = 0, hours = 0, watts = 0;

            while (true) {
                cout << "Appliance #" << (i + 1) << " name: ";
                getline(cin, name);
                if (name.empty()) {
                    cout << "Appliance name cannot be empty. Please re-enter.\n";
                    continue;
                }
                if (!isalpha(name[0])) {
                    cout << "Appliance name must start with a letter. Please re-enter.\n";
                    continue;
                }
                break;
            }

            while (true) {
                cout << "Quantity of " << name << " (max 10): ";
                cin >> qty;
                if (qty > 0 && qty <= 10) break;
                cout << "Quantity must be between 1 and 10. Please re-enter.\n";
            }

            while (true) {
                cout << "Hours per day used (max 24): ";
                cin >> hours;
                if (hours >= 0 && hours <= 24) break;
                cout << "Please enter valid hours (0-24). Please re-enter.\n";
            }

            cout << "Power rating (Watts): ";
            cin >> watts;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            appliances.push_back(Appliance(name, qty, hours, watts));
        }

        double totalUnits = 0;
        int size = (int)appliances.size();
        for (int i = 0; i < size; ++i) {
            totalUnits += appliances[i].monthlyUnits();
        }

        cout << "\n--- Usage Summary ---\n";
        cout << "Total Units Used by Appliances: " << totalUnits << " kWh\n";

        double adjustedUnits = solarUserPtr->getNetUnits();
        double bill = BillCalculator::calculateBill(adjustedUnits, 2);
        cout << "Estimated Bill after Solar Adjustment: Rs. " << bill << "\n";

        double target;
        cout << "\nHow many units would you like to reduce monthly? ";
        while (!(cin >> target)) {
            cout << "Invalid input. Please enter a numeric value for target reduction: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        SuggestionEngine::suggestReduction(appliances, totalUnits, target);

        displaySummary(totalUnits, bill);
        solarUserPtr->displaySolarSummary();
    }

    void displaySummary(double totalUnits, double bill) {
        cout << "\n==============================\n";
        cout << "|          Summary Table      |\n";
        cout << "==============================\n";
        cout << left << setw(25) << "Total Units Used:" << totalUnits << " kWh\n";
        cout << left << setw(25) << "Estimated Bill:" << "Rs. " << bill << endl;
        cout << "====================================\n";
    }
};

// ===== Main Function =====
int main() {
    string userName;
    string refNumber;
    double lastUnits;
    double lastBill;

    cout << "------------------------------SMART BILLING CONTROL SYSTEM------------------------------" << endl;
    cout << "\n==============================\n";
    cout << "|    Customer Details Entry    |\n";
    cout << "==============================\n";

    cout << "Enter your full name: ";
    getline(cin, userName);
    cout << "Enter your reference number: ";
    cin >> refNumber;

    cout << "Enter your last month's consumed units: ";
    while (!(cin >> lastUnits) || lastUnits < 0) {
        cout << "Invalid input. Please enter a non-negative numeric value for last month's consumed units: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    lastBill = BillCalculator::calculateBill(lastUnits, 1);
    cout << "Your last month's bill is: Rs. " << lastBill << endl;

    SolarUser solarUser;
    solarUser.userDetails();
    double solarGeneration = solarUser.getNetUnits();

    if (!solarUser.isMakingProfit()) {
        double targetBill;
        cout << "Enter the bill amount you would like to pay: ";
        while (!(cin >> targetBill) || targetBill < 0) {
            cout << "Invalid input. Please enter a non-negative numeric value for target bill amount: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // targetBill can be used if required for additional features
    }
    else {
        cout << "You are making money from your solar system.\n";
        cout << "Last month's profit: Rs. " << solarUser.getProfitLastMonth() << endl;
        cout << "Desired profit this month: Rs. " << solarUser.getDesiredProfit() << endl;
    }

    double estimatedUnits = lastUnits - solarGeneration;
    if (estimatedUnits < 0) estimatedUnits = 0;

    cout << "\n==============================\n";
    cout << "|   Target-Based Bill Table   |\n";
    cout << "==============================\n";
    cout << left << setw(25) << "Customer Name:" << userName << endl;
    cout << left << setw(25) << "Reference Number:" << refNumber << endl;
    cout << left << setw(25) << "Last Consumed Units:" << lastUnits << " kWh" << endl;
    cout << left << setw(25) << "Last Bill Amount:" << "Rs. " << lastBill << endl;
    cout << left << setw(25) << "Units You Can Use (After Solar):" << estimatedUnits << " kWh" << endl;

    cout << "\n==============================\n";

    string again;

    do {
        cout << "\n--- Smart Electricity Bill System ---\n";
        cout << "1. Exit\n";
        cout << "2. Residential User\n";
        cout << "3. Commercial User\n";
        cout << "Enter your choice: ";
        int choice;
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter 1, 2 or 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 1) {
            cout << "Exiting... Goodbye!\n";
            break;
        }

        switch (choice) {
            case 2: {
                Residential r(&solarUser);
                r.run();
                break;
            }
            case 3: {
                Commercial c(&solarUser);
                c.run();
                break;
            }
            default:
                cout << "Invalid option!\n";
        }

        cout << "\nWould you like to run again? (yes / no): ";
        cin >> again;
        for (int i = 0; (unsigned)i < again.length(); i++)
            again[i] = (char)tolower(again[i]);

    } while (again == "yes");

    cout << "Thanks for using the program!\n";
    return 0;
}


