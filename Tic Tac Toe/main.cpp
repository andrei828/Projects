#include <iostream>

using namespace std;

char a[100][100];
char colt_stanga_sus  = 218;
char colt_dreapta_sus = 191;
char colt_stanga_jos  = 192;
char colt_dreapta_jos = 217;
char linie_orizontala = 196;
char linie_verticala  = 179;
char T_dreapta = 195;
char T_stanga = 180;
char T_sus = 193;
char T_jos = 194;
char cruce = 197;
int o = 1;
bool l = true;
bool junk = true;
int temp_x;
int temp_y;

void init(){
    for(int i = 1 ; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            a[i][j] = 'a';
        }
    }
}

/*display matrix*/
void display1(){
    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            cout<<a[i][j]<<" ";
        }cout<<"\n";
    }
}

void display(){
    int cor_x = 1, cor_y = 1;
    
    /*linie litere*/
    cout<<"   ";
    for(int i = 0; i < 3; i++){
        char c = 'A' + i;
        cout<<c<<" ";
    }cout<<"\n";
    
    /*top linie*/
    cout<<"  ";
    cout<<colt_stanga_sus;
    for(int i = 0; i < 2; i++){
        cout<<linie_orizontala<<T_jos;
    }
    cout<<linie_orizontala<<colt_dreapta_sus;
    cout<<"\n";
    
    /*rest linii*/
    do{
        if(l == true){
            cout<<o<<" "; o++;
            cout<<linie_verticala;
            l = false;
        }else{
            cout<<"  "<<T_dreapta;
            l = true;
        }
        
        for(int i = 0; i < 2; i++){
            if(l == false){
                cout<<a[cor_x][cor_y]<<linie_verticala; cor_y++;  // adauga matrice
            }else {
                cout<<linie_orizontala<<cruce;
            }
        }
        if(l == false){
            cout<<a[cor_x][cor_y]<<linie_verticala; cor_y++; // adauga matrice
            cor_x = cor_x + 1;
        }else{
            cout<<linie_orizontala<<T_stanga;
        }cout<<"\n";
        
        
        cor_y = 1;
    }while(o < 4);
    
    /*ultima linie*/
    cout<<"  "<<colt_stanga_jos;
    for(int i = 0; i < 2; i++){
        cout<<linie_orizontala<<T_sus;
    }
    cout<<linie_orizontala<<colt_dreapta_jos<<"\n";
    l = true;
    o = 1;
}

void putFirstO(int x, int y){
    if(x == 1 && y == 1){
        a[x][y+1] = 'O';
    }else if(x == 1 && y == 2){
        a[x+2][y] = 'O';
    }else if(x == 1 && y == 3){
        a[x+1][y-1] = 'O';
    }else if(x == 2 && y == 1){
        a[x][y+2] = 'O';
    }else if(x == 2 && y == 2){
        a[x+1][y+1] = 'O';
    }else if(x == 2 && y == 3){
        a[x][y-2] = 'O';
    }else if(x == 3 && y == 1){
        a[x-1][y+1] = 'O';
    }else if(x == 3 && y == 2){
        a[x-2][y] = 'O';
    }else if(x == 3 && y == 3){
        a[x-1][y-1] = 'O';
    }
}

bool isFull(){
    /*checks if matrix is full*/
    for(int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
            if(a[i][j] == 'a'){
                return false;
            }
        }
    }
    return true;
}

int getXperCol(int y){
    /*gets number of 'X's on a column*/
    int contor = 0;
    for(int i = 1; i <= 3; i++){
        if(a[i][y] == 'X'){
            contor++;
        }
    }
    return contor;
}

int getXperRow(int x){
    /*gets number of 'X's on a column*/
    int contor = 0;
    for(int i = 1; i <= 3; i++){
        if(a[x][i] == 'X'){
            contor++;
        }
    }
    return contor;
}

int getXperDiag1(){
    /*gets number of 'X's on the first diagonal*/
    int contor = 0;
    for(int i = 1; i <= 3; i++){
        if(a[i][i] == 'X'){
            contor++;
        }
    }
    return contor;
}

int getXperDiag2(){
    /*gets number of 'X's on the second diagonal*/
    int contor = 0;
    for(int i = 1, j = 3; j >= 1; i++, j--){
        if(a[i][j] == 'X'){
            contor++;
        }
    }
    return contor;
}

void mat(){
    int x,y;
    cout<<"Insert the coordonates: ";
    cin>>x>>y;
    a[x][y] = 'X';
    putFirstO(x,y);
    temp_x = x;
    temp_y = y;
}

void solve(){
    int x,y;
    cout<<"Insert the coordonates: ";
    cin>>x>>y;
    a[x][y] = 'X';
    
    /*block Xs*/
    int xCol1  = getXperCol(1);
    int xCol2  = getXperCol(2);
    int xCol3  = getXperCol(3);
    int xRow1  = getXperRow(1);
    int xRow2  = getXperRow(2);
    int xRow3  = getXperRow(3);
    int xDiag1 = getXperDiag1();
    int xDiag2 = getXperDiag2();
    
    if(xCol1 == 3 || xCol2 == 3 || xCol3 == 3 || xRow1 == 3 || xRow2 == 3 || xRow3 == 3 || xDiag1 == 3 || xDiag2 == 3 || isFull() == true){
        cout<<"Game over\n";
        return;
    }
    
    if(xCol1 > 1){
        for(int i = 1; i <= 3; i++){
            if(a[i][1] == 'a'){
                a[i][1] = 'O';
                break;
            }
        }
    }else if(xCol2 > 1){
        for(int i = 1; i <= 3; i++){
            if(a[i][2] == 'a'){
                a[i][2] = 'O';
                break;
            }
        }
    }else if(xCol3 > 1){
        for(int i = 1; i <= 3; i++){
            if(a[i][3] == 'a'){
                a[i][3] = 'O';
                break;
            }
        }
        
    }else if (xRow1 > 1){
        for(int i = 1; i <= 3; i++){
            if(a[1][i] == 'a'){
                a[1][i] = 'O';
                break;
            }
        }
    }else if(xRow2 > 1){
        for(int i = 1; i <= 3; i++){
            if(a[2][i] == 'a'){
                a[2][i] = 'O';
                break;
            }
        }
    }else if(xRow3 > 1){
        for(int i = 1; i <= 3; i++){
            if(a[3][i] == 'a'){
                a[3][i] = 'O';
                break;
            }
        }
    }else if(xDiag1 > 1){
        for(int i = 1; i <= 3; i++){
            if(a[i][i] == 'a'){
                a[i][i] = 'O';
                break;
            }
        }
    }else if(xDiag2 > 1){
        for(int i = 1, j = 3; j >= 1; i++, j--){
            if(a[i][j] == 'a'){
                a[i][j] = 'O';
                break;
            }
        }
    }
}

int main()
{
    init();//only for display1()
    mat();
    //display();
    display1();
    for(int i = 0; i < 3; i++){
    solve();
    //display();
    display1();
    }
    return 0;
}