// hw4 - finding the shortest distance (Matthew Xue - 6/5)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <limits>

using namespace std;

// creating structure
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
    // read the input file 
    void populateCities() {
        ifstream file(inputFile);
        string line;
        // read each line of the input file
        while (getline(file, line)) {
            istringstream iss(line);
            string city1, city2;
            int distance;
            // stop reading when the format below is not printed
            if (!(iss >> city1 >> city2 >> distance)) {
                break;
            }
            routeMap[city1][city2] = distance;
            routeMap[city2][city1] = distance; // reverse path
        }
        file.close();
    }
    
    map<string, int> findShortestDistances(const string& startCity) {
        map<string, int> shortestDistances;
        queue<CityDistance> q;
        q.push({startCity, 0}); // pushes starting city and distance to queue
        shortestDistances[startCity] = 0; // set starting distance to 0

        while (!q.empty()) {
            CityDistance current = q.front(); 
            q.pop(); // first city is dequeued

            string currentCity = current.city;  
            int currentDistance = current.distance;
            // iterates over the the neighbor cities of current city
            for (const auto& neighbor : routeMap[currentCity]) {
                string neighborCity = neighbor.first;
                int neighborDistance = neighbor.second;
                int updatedDistance = currentDistance + neighborDistance;

                // checks if the neighbor is not in shortestdistance map
                // and if the distance is shorter, then it will update the distance
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

    // write everything in a file name shortestDistances
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






