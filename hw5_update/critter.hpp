#include <iostream>
#include <cstdlib>
#include <ctime>

enum class CritterType { ANT, DOODLEBUG };

class Critter {
protected:
    int row;
    int col;

public:
    Critter(int row, int col) : row(row), col(col) {}
    virtual ~Critter() {}

    virtual CritterType getType() const = 0;
    virtual void move(std::vector<std::vector<Critter*>>& grid) = 0;
    virtual void breed(std::vector<std::vector<Critter*>>& grid) = 0;
    virtual void starve(std::vector<std::vector<Critter*>>& grid) = 0;
};

class Ant : public Critter {
private:
   
    
    int stepsSinceMating;
    int stepsSinceBreeding;

public:
    char anttype;
    Ant(int row, int col,char anttype) : Critter(row, col),  stepsSinceMating(0), stepsSinceBreeding(0), anttype{anttype}{}

    CritterType getType() const override { return CritterType::ANT; }

    void move(std::vector<std::vector<Critter*>>& grid) override {
        int newRow = row;
        int newCol = col;

        // Randomly choose a direction
        int direction = std::rand() % 8;

        if (direction == 0) {
            newRow--;
            newCol--;
        } else if (direction == 1) {
            newRow--;
        } else if (direction == 2) {
            newRow--;
            newCol++;
        } else if (direction == 3) {
            newCol--;
        } else if (direction == 4) {
            newCol++;
        } else if (direction == 5) {
            newRow++;
            newCol--;
        } else if (direction == 6) {
            newRow++;
        } else if (direction == 7) {
            newRow++;
            newCol++;
        }

        if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid.size()) {
            if (grid[newRow][newCol] == nullptr) {
                grid[newRow][newCol] = this;
                grid[row][col] = nullptr;
                row = newRow;
                col = newCol;
                stepsSinceMating++;
                stepsSinceBreeding++;
            }
        }
    }

    void breed(std::vector<std::vector<Critter*>>& grid) override {
        if (anttype !='Q' && stepsSinceMating >= 30) {
            int count = 0;
            int emptyCells = 0;
            std::vector<int> emptyRow;
            std::vector<int> emptyCol;

            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < grid.size() && j >= 0 && j < grid.size() && grid[i][j] == nullptr) {
                        emptyRow.push_back(i);
                        emptyCol.push_back(j);
                        emptyCells++;
                    }
                }
            }

            while (count < 10 && emptyCells > 0) {
                int index = std::rand() % emptyCells;
                int newRow = emptyRow[index];
                int newCol = emptyCol[index];
                grid[newRow][newCol] = new Ant(newRow, newCol,('W'));
                emptyRow.erase(emptyRow.begin() + index);
                emptyCol.erase(emptyCol.begin() + index);
                emptyCells--;
                count++;
            }

            stepsSinceMating = 0;
            stepsSinceBreeding = 0;
        } else {
            stepsSinceMating++;
            stepsSinceBreeding++;
        }

        if (anttype == 'Q' && stepsSinceMating >= 60) {
            grid[row][col] = nullptr;
        }
    }

    void starve(std::vector<std::vector<Critter*>>& grid) override {
        if (anttype!='Q' && stepsSinceBreeding >= 5) {
            grid[row][col] = nullptr;
        }
    }

    bool isQueen() const { return anttype == 'Q'; }
    char setanttype(char value) { anttype = value; }
};

class Doodlebug : public Critter {
private:
    int stepsSinceEating;
    int stepsSinceBreeding;

public:
    Doodlebug(int row, int col) : Critter(row, col), stepsSinceEating(0), stepsSinceBreeding(0) {}

    CritterType getType() const override { return CritterType::DOODLEBUG; }

    void move(std::vector<std::vector<Critter*>>& grid) override {
        int newRow = row;
        int newCol = col;

        // Randomly choose a direction
        int direction = std::rand() % 8;

        if (direction == 0) {
            newRow--;
            newCol--;
        } else if (direction == 1) {
            newRow--;
        } else if (direction == 2) {
            newRow--;
            newCol++;
        } else if (direction == 3) {
            newCol--;
        } else if (direction == 4) {
            newCol++;
        } else if (direction == 5) {
            newRow++;
            newCol--;
        } else if (direction == 6) {
            newRow++;
        } else if (direction == 7) {
            newRow++;
            newCol++;
        }

        if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid.size()) {
            if (grid[newRow][newCol] == nullptr) {
                grid[newRow][newCol] = this;
                grid[row][col] = nullptr;
                row = newRow;
                col = newCol;
                stepsSinceEating++;
                stepsSinceBreeding++;
            } else if (grid[newRow][newCol]->getType() == CritterType::ANT) {
                // Eat the ant
                delete grid[newRow][newCol];
                grid[newRow][newCol] = this;
                grid[row][col] = nullptr;
                row = newRow;
                col = newCol;
                stepsSinceEating = 0;
                stepsSinceBreeding++;
            }
        }
    }

    void breed(std::vector<std::vector<Critter*>>& grid) override {
        if (stepsSinceBreeding >= 10) {
            int count = 0;
            int emptyCells = 0;
            std::vector<int> emptyRow;
            std::vector<int> emptyCol;

            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < grid.size() && j >= 0 && j < grid.size() && grid[i][j] == nullptr) {
                        emptyRow.push_back(i);
                        emptyCol.push_back(j);
                        emptyCells++;
                    }
                }
            }

            while (count < 2 && emptyCells > 0) {
                int index = std::rand() % emptyCells;
                int newRow = emptyRow[index];
                int newCol = emptyCol[index];
                grid[newRow][newCol] = new Doodlebug(newRow, newCol);
                emptyRow.erase(emptyRow.begin() + index);
                emptyCol.erase(emptyCol.begin() + index);
                emptyCells--;
                count++;
            }

            stepsSinceBreeding = 0;
        } else {
            stepsSinceBreeding++;
        }
    }

    void starve(std::vector<std::vector<Critter*>>& grid) override {
        if (stepsSinceEating >= 5) {
            grid[row][col] = nullptr;
        }
    }
};
