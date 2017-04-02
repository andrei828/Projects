#include <fstream>
#include <cmath>
#define NULL 0
#define SQN 3
using namespace std;

ifstream fin("sudoku.in");
ofstream fout("sudoku.out");

int n;

bool checkRow(int x, int **a, int row){
    for(int col = 0 ; col < n; col++){
        if(a[row][col] == x){
            return true;
        }
    }
    return false;
}

bool checkCol(int x, int **a, int col){
    for(int row = 0; row < n; row++){
        if(a[row][col] == x){
            return true;
        }
    }
    return false;
}

bool checkBox(int x, int **a, int boxStartRow, int boxStartCol){
    for(int row = 0; row < SQN; row++){
        for(int col = 0; col < SQN; col++){
            if(a[row + boxStartRow][col + boxStartCol] == x){
                return true;
            }
        }
    }
    return false;
}

bool isSafe(int x, int **a, int row, int col){

        return !checkRow(x, a, row) &&
               !checkCol(x, a, col) &&
               !checkBox(x, a, row - row % SQN, col - col % SQN);
}

bool findUnasigned(int **a, int &row, int &col){        //find unasigned
    for(row = 0; row < n; row++){
        for(col = 0 ; col < n; col++){
            if(a[row][col] == NULL){
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int **a){            //backtracking algorithm
    int row = 0;
    int col = 0;
    
    //if there are no unasigned elements, exit
    if(findUnasigned(a, row, col) == false){
        return true;
    }
    //search for every posible element
    for(int k = 1; k <= n; k++){
        //check if it's posible to use
        if(isSafe(k, a, row, col) == true){
            //implement element in matrix
            a[row][col] = k;
            
            //recursion for backtracking
            if(solveSudoku(a) == true){
                return true;
            }
            
            //sets NULL and starts again to search
            a[row][col] = NULL;
        }
    }
    return false;
}

void display(int **a){                                //displays matrix
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < n ; j++){
            fout<<a[i][j]<<" ";
        }fout<<"\n";
    }
}

int main() {
    
    int **grid = new int*[100];
    
    for(int i = 0; i < 100; i++){
        grid[i] = new int[100];
    }
    n = 9;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> grid[i][j];
        }
    }
    /*grid[0][0] = 3; grid[0][1] = 4; grid[0][4] = 2; grid[0][6] = 8; grid[0][7] = 9; grid[0][8] = 1; grid[1][1] = 5; grid[1][2] = 9; grid[1][4] = 4; grid[1][6] = 6; grid[1][7] = 3; grid[1][8] = 2; grid[2][2] = 1; grid[2][5] = 9; grid[2][7] = 7; grid[3][4] = 8; grid[4][3] = 9; grid[4][5] = 1; grid[4][6] = 7; grid[4][7] = 2; grid[4][8] = 6; grid[5][3] = 6; grid[5][4] = 3; grid[5][8] = 5; grid[6][1] = 1; grid[6][3] = 5; grid[6][4] = 7; grid[6][8] = 8; grid[7][0] = 5; grid[7][1] = 6; grid[7][3] = 2; grid[7][4] = 1; grid[7][7] = 4; grid[8][0] = 4; grid[8][1] = 2; grid[8][2] = 7; grid[8][3] = 8; grid[8][8] = 3;
    display(grid);cout<<"\n\n";*/
    solveSudoku(grid);
    display(grid);
    
    for(int i = 0 ; i < 100; i++){
        delete grid[i];
    }
    delete grid;
}


