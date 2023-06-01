// pa9 Matthew Xue (6/1/2023)
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<string> stores = {"Amazon", "Best Buy", "Apple", "Nike", "converse"};

// display the prices from different stores
void displayPrices(const map<string, vector<double>>& prices) {
    cout << setw(15) << "Product";
    for (const auto& store : stores) {
        cout << setw(15) << store;
    }
    cout << "\n";

    for (const auto& item : prices) {
        cout << setw(15) << item.first;
        for (const auto& price : item.second) {
            cout << setw(15) << price;
        }
        cout << "\n";
    }
}

// display the average prices
void displayAveragePrices(const map<string, vector<double>>& prices) {
    cout << "Average Prices:\n";
    vector<pair<string, double>> averages;

    for (const auto& item : prices) {
        double sum = 0.0;
        for (const auto& price : item.second) {
            sum += price;
        }
        double average = sum / item.second.size();
        averages.emplace_back(item.first, average);
    }

    // sort the averages in ascending order of the average cost
    sort(averages.begin(), averages.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second < b.second;
    });

    for (const auto& average : averages) {
        cout << setw(15) << average.first << " average price is: " << average.second << "\n";
    }
}

// find the store offering the best price for each item
void findBestPrices(const map<string, vector<double>>& prices) {
    cout << "Best Prices:\n";

    for (const auto& item : prices) {
        double minPrice = item.second[0];
        string bestStore = stores[0];

        for (size_t i = 1; i < item.second.size(); ++i) {
            if (item.second[i] < minPrice) {
                minPrice = item.second[i];
                bestStore = stores[i];
            }
        }

        cout << setw(15) << item.first << " should be bought from: " << bestStore << "\n";
    }
}

int main() {
    map<string, vector<double>> prices;

    vector<string> items = {"Air Forces", "Airpods", "High Top Shoes", "Macbook Pro", "Shorts"};

    // randomly generate prices for each store's item
    for (const auto& item : items) {
        vector<double> itemPrices;
        for (size_t i = 0; i < stores.size(); ++i) {
            double price = 10.0 + (rand() % 990) + 10; // Random price between $10 and $999
            itemPrices.push_back(price);
        }
        prices[item] = itemPrices;
    }

    displayPrices(prices);
    cout << endl;
    displayAveragePrices(prices);
    cout << endl;
    findBestPrices(prices);

    return 0;
}
