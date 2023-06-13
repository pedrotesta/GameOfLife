#include <iostream>
#include <vector>
#include <random>
#include <numeric>

#define DEFAULT_GRID_WIDTH 20
#define DEFAULT_GRID_LENGHT 20

using namespace std;

void fillGridRandomly(vector<vector<int>>& cell_grid){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);
    distribution(gen);

    for(unsigned int i = 0; i < cell_grid.size(); i++){
        for(unsigned int j = 0; j < cell_grid[0].size(); j++){
            cell_grid[i][j] = distribution(gen);
        }
    }
}

void showGrid(vector<vector<int>>& cell_grid){
    for(unsigned int i = 0; i < cell_grid.size(); i++){
        for(unsigned int j = 0; j < cell_grid[0].size(); j++){
            cout << cell_grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int checkNeighborhood(const vector<vector<int>> cell_grid, unsigned int i, unsigned int j){
    int alive_neighborhood = 0;
    i += 1;
    j += 1;
    alive_neighborhood += cell_grid[i][j-1];
    alive_neighborhood += cell_grid[i-1][j-1];
    alive_neighborhood += cell_grid[i+1][j-1];
    alive_neighborhood += cell_grid[i][j+1];
    alive_neighborhood += cell_grid[i-1][j+1];
    alive_neighborhood += cell_grid[i+1][j+1];
    alive_neighborhood += cell_grid[i-1][j];
    alive_neighborhood += cell_grid[i+1][j];

    return alive_neighborhood;
}

vector<vector<int>> addBorder(const vector<vector<int>> cell_grid){
    vector<vector<int>> grid_with_border(cell_grid.size() + 2, vector<int>(cell_grid[0].size() + 2));

    for(unsigned int i = 0; i < cell_grid.size(); i++){
        for(unsigned int j = 0; j < cell_grid[0].size(); j++){
            grid_with_border[i+1][j+1] = cell_grid[i][j];
        }
    }
    return grid_with_border;
}

void updateGridValues(vector<vector<int>>& cell_grid){
    vector<vector<int>> gridWithBorder = addBorder(cell_grid);

    for(unsigned int i = 0; i < cell_grid.size(); i++){
        for(unsigned int j = 0; j < cell_grid[0].size(); j++){
            int aliveNeighborhood = 0;
            aliveNeighborhood = checkNeighborhood(gridWithBorder, i, j);

            if(cell_grid[i][j]){
                if(aliveNeighborhood < 2 || aliveNeighborhood > 3){
                    cell_grid[i][j] = 0;
                }
            }
            else{
                if(aliveNeighborhood == 3){
                    cell_grid[i][j] = 1;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {    
    int gridWidth = DEFAULT_GRID_WIDTH;
    int gridLenght= DEFAULT_GRID_LENGHT;

    if(argc == 3){
        gridWidth = stoi(argv[1]);
        gridLenght = stoi(argv[2]);
    }

    vector<vector<int>> cellGrid(gridLenght, vector<int>(gridWidth));

    fillGridRandomly(cellGrid);
    showGrid(cellGrid);

    int sumOfGrid = 0;
    for (const auto& row : cellGrid) {
        sumOfGrid += accumulate(row.begin(), row.end(), 0);
    }

    while(sumOfGrid > 0){
        updateGridValues(cellGrid);
        showGrid(cellGrid);

        sumOfGrid = 0;
        for (const auto& row : cellGrid) {
            sumOfGrid += accumulate(row.begin(), row.end(), 0);
        }
    }
    
    return 0;
}