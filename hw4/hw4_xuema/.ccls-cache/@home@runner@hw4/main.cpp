#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <limits>

using namespace std;

struct CityDistance {
    string city;
    int distance;
};

class Routes {
private:
    map<string, map<string, int>> routeMap;
    string inputFile;
public:
    Routes(string fileName) {
        inputFile = fileName;
    }

    void populateCities() {
        ifstream file(inputFile);
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string city1, city2;
            int distance;
            if (!(iss >> city1 >> city2 >> distance)) {
                break;
            }
            routeMap[city1][city2] = distance;
            routeMap[city2][city1] = distance; // Add the reverse path as well
        }
        file.close();
    }

    map<string, int> findShortestDistances(const string& startCity) {
        map<string, int> shortestDistances;
        queue<CityDistance> q;
        q.push({startCity, 0});
        shortestDistances[startCity] = 0;

        while (!q.empty()) {
            CityDistance current = q.front();
            q.pop();

            string currentCity = current.city;
            int currentDistance = current.distance;

            for (const auto& neighbor : routeMap[currentCity]) {
                string neighborCity = neighbor.first;
                int neighborDistance = neighbor.second;
                int updatedDistance = currentDistance + neighborDistance;

                if (shortestDistances.count(neighborCity) == 0 || updatedDistance < shortestDistances[neighborCity]) {
                    shortestDistances[neighborCity] = updatedDistance;
                    q.push({neighborCity, updatedDistance});
                }
            }
        }

        return shortestDistances;
    }
};

int main() {
    string fileName = "map.txt";
    Routes routes(fileName);
    routes.populateCities();

    string startCity;
    cout << "Enter the starting city: ";
    cin >> startCity;

    if (routes.findShortestDistances(startCity).count(startCity) == 0) {
        cout << "Starting city not found in the map." << endl;
        return 0;
    }

    map<string, int> shortestDistances = routes.findShortestDistances(startCity);

    ofstream outFile("shortestDistances.txt");
    if (outFile.is_open()) {
        for (const auto& entry : shortestDistances) {
            outFile << entry.first << ": " << entry.second << endl;
        }
        outFile.close();
        cout << "Shortest distances written to shortestDistances.txt." << endl;
    } else {
        cout << "Unable to write to shortestDistances.txt." << endl;
    }

    return 0;
}






