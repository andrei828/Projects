#include <iostream>
#include <stdlib.h>
#include <conio.h>


using namespace std;

char a[100][100], b[100][100], e[100][100], t[100][100];
char colt_stanga_sus = 218;
char colt_dreapta_sus = 191;
char colt_stanga_jos = 192;
char colt_dreapta_jos = 217;
char linie_orizontala = 196;
char linie_verticala = 179;
char T_drepta = 195;
char T_stanga = 180;
char T_sus = 193;
char T_jos = 194;
char cruce = 197;
char cub = 178;
char cub_1 = 177;
char cub_0 = 176;
char varf = 254;
char avion = 219;
int o = 1;
int g = 0; //counts number of planes
int e_X;
int t_X;
bool l = false;
bool boo = true;
bool gol = true;
bool opponent = true;

struct offset_x {
    
    int x;
    
}S[9];

struct offset_y {
    
    int y;
    
}P[9];

void delete_aircraft(int orient, int x, int y, char a[100][100]) {
    /*orientare nord*/
    if (orient == 1) {
        for (int i = -2; i <= 2; i++) {
            a[x + 1][y + i] = NULL;
        }
        a[x + 2][y] = NULL;
        for (int i = -1; i <= 1; i++) {
            a[x + 3][y + i] = NULL;
        }
        a[x][y] = NULL;
    }
    /*orientare sud*/
    else if (orient == 2) {
        for (int i = -2; i <= 2; i++) {
            a[x - 1][y + i] = NULL;
        }
        a[x - 2][y] = NULL;
        for (int i = -1; i <= 1; i++) {
            a[x - 3][y + i] = NULL;
        }
        a[x][y] = NULL;
    }
    /*orientare vest*/
    else if (orient == 3) {
        for (int i = -2; i <= 2; i++) {
            a[x + i][y - 1] = NULL;
        }
        a[x][y - 2] = NULL;
        for (int i = -1; i <= 1; i++) {
            a[x + i][y - 3] = NULL;
            
        }
        a[x][y] = NULL;
    }
    /*orientare est*/
    else if (orient == 4) {
        for (int i = -2; i <= 2; i++) {
            a[x + i][y + 1] = NULL;
        }
        a[x][y + 2] = NULL;
        for (int i = -1; i <= 1; i++) {
            a[x + i][y + 3] = NULL;
        }
        a[x][y] = NULL;
    }
}

void display(char a[100][100]) {
    
    /* Linia cu charactere*/
    cout << "    ";
    for (int i = 0; i < 10; i++) {
        char c = 'A' + i;
        cout << c << " ";
    }cout << "\n"; cout << "   ";
    
    /* Prima linie tabel */
    
    cout << colt_stanga_sus;
    
    for (int i = 1; i < 18; i++) {
        cout << linie_orizontala; i++;
        cout << T_jos;
    }cout << linie_orizontala;
    cout << colt_dreapta_sus;
    cout << "\n";
    /* Liniile numerotate */
    int cor_x = 1, cor_y = 1;
    do {
        for (int k = 1; k <= 9; k++) {
            /* Linie goala vs linie numerotata*/
            
            /* Inceput linie */
            if (l == true) {
                cout << "   " << T_drepta;
                l = false;
            }
            else {
                cout << o++ << "  ";
                cout << linie_verticala;
                l = true;
            }
            
            /* linie */
            for (int i = 1; i < 18; i++) {
                if (l == false) {
                    cout << linie_orizontala; i++;
                    cout << cruce;
                }
                else {
                    cout << a[cor_x][cor_y]; i++; cor_y++;  ////////
                    cout << linie_verticala;
                }
            }
            /* Sfarsit linie*/
            if (l == false) {
                cout << linie_orizontala << T_stanga;
                cout << "\n"; //cout << o++ << "  ";
            }
            else {
                cout << a[cor_x][cor_y] << linie_verticala; cor_x++; cor_y = 1; ////////
                cout << "\n"; //cout << o++ << "  ";
            }
        } //end for
    } while (o < 10);
    /*ultima linie*/
    cout << o << " ";
    cout << linie_verticala;
    for (int i = 1; i <= 10; i++) {
        cout << a[cor_x][cor_y] << linie_verticala; cor_y++; /////////////////
    }cout << "\n   ";
    cout << colt_stanga_jos;
    for (int i = 1; i < 10; i++) {
        cout << linie_orizontala << T_sus;
    }cout << linie_orizontala << colt_dreapta_jos;
    l = false;
    o = 1;
    cout << '\n';
}

void display_opponent(char a[100][100]) {
    /* Linia cu charactere*/
    cout << "    ";
    for (int i = 0; i < 10; i++) {
        char c = 'A' + i;
        cout << c << " ";
    }cout << "\n"; cout << "   ";
    
    /* Prima linie tabel */
    
    cout << colt_stanga_sus;
    
    for (int i = 1; i < 18; i++) {
        cout << linie_orizontala; i++;
        cout << T_jos;
    }cout << linie_orizontala;
    cout << colt_dreapta_sus;
    cout << "\n";
    /* Liniile numerotate */
    int cor_x = 1, cor_y = 1;
    do {
        for (int k = 1; k <= 9; k++) {
            /* Linie goala vs linie numerotata*/
            
            /* Inceput linie */
            if (l == true) {
                cout << "   " << T_drepta;
                l = false;
            }
            else {
                cout << o++ << "  ";
                cout << linie_verticala;
                l = true;
            }
            
            /* linie */
            for (int i = 1; i < 18; i++) {
                if (l == false) {
                    cout << linie_orizontala; i++;
                    cout << cruce;
                }
                else {
                    cout << e[cor_x][cor_y]; i++; cor_y++;
                    cout << linie_verticala;
                }
            }
            /* Sfarsit linie*/
            if (l == false) {
                cout << linie_orizontala << T_stanga;
                cout << "\n"; //cout << o++ << "  ";
            }
            else {
                cout << e[cor_x][cor_y] << linie_verticala; cor_x++; cor_y = 1;
                cout << "\n"; //cout << o++ << "  ";
            }
        } //end for
    } while (o < 10);
    /*ultima linie*/
    cout << o << " ";
    cout << linie_verticala;
    for (int i = 1; i <= 10; i++) {
        cout << e[cor_x][cor_y] << linie_verticala; cor_y++;
    }cout << "\n   ";
    cout << colt_stanga_jos;
    for (int i = 1; i < 10; i++) {
        cout << linie_orizontala << T_sus;
    }cout << linie_orizontala << colt_dreapta_jos;
    l = false;
    o = 1;
    cout << '\n';
}

bool place_aircraft(int orient, int x, int y, char a[100][100]) {
    gol = true;
    /*orientare nord*/
    if (orient == 1) {
        if (x + 3 <= 10 && y - 2 <= 10 && y + 2 <= 10 && x + 3 > 0 && y - 2 > 0 && y + 2 > 0 && x > 0 && x <= 10 && y > 0 && y <= 10) {
            for (int i = -2; i <= 2; i++) {
                if (a[x + 1][y + i] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x + 2][y] != NULL) {
                gol = false;
                return false;
            }
            for (int i = -1; i <= 1; i++) {
                if (a[x + 3][y + i] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x][y] != NULL) {
                gol = false;
                return false;
            }
            if (gol == true) {
                for (int i = -2; i <= 2; i++) {
                    a[x + 1][y + i] = 219;
                }
                a[x + 2][y] = 219;
                for (int i = -1; i <= 1; i++) {
                    a[x + 3][y + i] = 219;
                }
                a[x][y] = 254;
                return true;
            }
            else {
                //cout << "Nu e loc boss :(\n";
                return false;
            }
        }
        else {
            //cout << "Nu este posibil :(\n";
            boo = false;
            return false;
        }
    }
    /*orientare sud*/
    else if (orient == 2) {
        if (x - 3 <= 10 && y - 2 <= 10 && y + 2 <= 10 && x - 3 > 0 && y - 2 > 0 && y + 2 > 0 && x > 0 && x <= 10 && y > 0 && y <= 10) {
            for (int i = -2; i <= 2; i++) {
                if (a[x - 1][y + i] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x - 2][y] != NULL) {
                gol = false;
                return false;
            }
            for (int i = -1; i <= 1; i++) {
                if (a[x - 3][y + i] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x][y] != NULL) {
                gol = false;
                return false;
            }
            if (gol == true) {
                for (int i = -2; i <= 2; i++) {
                    a[x - 1][y + i] = 219;
                }
                a[x - 2][y] = 219;
                for (int i = -1; i <= 1; i++) {
                    a[x - 3][y + i] = 219;
                }
                a[x][y] = 254;
                return true;
            }
            else {
                // cout << "Nu e loc boss :(\n";
                return true;
            }
        }
        else {
            //cout << "Nu este posibil :(\n";
            boo = false;
            return false;
        }
    }
    /*orientare vest*/
    else if (orient == 3) {
        if (y - 3 <= 10 && x - 2 <= 10 && x + 2 <= 10 && y - 3 > 0 && x - 2 > 0 && y + 2 > 0 && x > 0 && x <= 10 && y > 0 && y <= 10) {
            for (int i = -2; i <= 2; i++) {
                if (a[x + i][y - 1] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x][y - 2] != NULL) {
                gol = false;
                return false;
            }
            for (int i = -1; i <= 1; i++) {
                if (a[x + i][y - 3] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x][y] != NULL) {
                gol = false;
                return false;
            }
            if (gol == true) {
                for (int i = -2; i <= 2; i++) {
                    a[x + i][y - 1] = 219;
                }
                a[x][y - 2] = 219;
                for (int i = -1; i <= 1; i++) {
                    a[x + i][y - 3] = 219;
                }
                a[x][y] = 254;
                return true;
            }
            else {
                //cout << "Nu e loc boss :( \n";
                return false;
            }
        }
        else {
            //cout << "Nu este posibil :(\n";
            boo = false;
            return false;
        }
    }
    /*orientare est*/
    else if (orient == 4) {
        if (y + 3 <= 10 && x - 2 <= 10 && x + 2 <= 10 && y + 3 > 0 && x - 2 > 0 && y + 2 > 0 && x > 0 && x <= 10 && y > 0 && y <= 10) {
            for (int i = -2; i <= 2; i++) {
                if (a[x + i][y + 1] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x][y + 2] != false) {
                gol = false;
                return false;
            }
            for (int i = -1; i <= 1; i++) {
                if (a[x + i][y + 3] != NULL) {
                    gol = false;
                    return false;
                }
            }
            if (a[x][y] != NULL) {
                gol = false;
                return false;
            }
            if (gol == true) {
                for (int i = -2; i <= 2; i++) {
                    a[x + i][y + 1] = 219;
                }
                a[x][y + 2] = 219;
                for (int i = -1; i <= 1; i++) {
                    a[x + i][y + 3] = 219;
                }
                
                a[x][y] = 254;
                return true;
            }
            else {
                //cout << "Nu e loc boss :(\n";
                return false;
            }
        }
        else {
            //cout << "Nu este posibil :(\n";
            boo = false;
            return false;
        }
    }
}

void check_plane(char a[100][100], char e[100][100]) {
    int x = 1, y = 1;
    int jucator;
    if (opponent == true) {
        jucator = 1;
    }
    else {
        jucator = 2;
    }
    e[x][y] = cub;
    system("cls");
    cout << "\n\tJucator: "<<jucator<<"\n\n";
    char c;
    display(e);
    
    while (1) {
        if (g == 1) {
            break;
        }
        
        switch (c = _getch()) {
            case 119:  //w
                if (x == 1) {
                    break;
                }
                if (e[x - 1][y] == NULL) {
                    e[x][y] = NULL;
                    x--;
                    system("cls");
                    cout << "\n\tJucator: " << jucator << "\n\n";
                    e[x][y] = cub;
                    display(e);
                }
                break;
            case 97:  //a
                if (y == 1) {
                    break;
                }
                if (e[x][y - 1] == NULL) {
                    e[x][y] = NULL;
                    y--;
                    system("cls");
                    cout << "\n\tJucator: " << jucator << "\n\n";
                    e[x][y] = cub;
                    display(e);
                }
                break;
            case 115:  //s
                if (x == 10) {
                    break;
                }
                if (e[x+1][y] == NULL) {
                    e[x][y] = NULL;
                    x++;
                    system("cls");
                    cout << "\n\tJucator: " << jucator << "\n\n";
                    e[x][y] = cub;
                    display(e);
                }
                break;
            case 100:  //d
                if (y == 10) {
                    break;
                }
                if (e[x][y+1] == NULL) {
                    e[x][y] = NULL;
                    y++;
                    system("cls");
                    cout << "\n\tJucator: " << jucator << "\n\n";
                    e[x][y] = cub;
                    display(e);
                }
                break;
            case 32:  //space
                g++;
                if (a[x][y] == varf) {
                    e[x][y] = 'X';	//lovit varf
                    if (jucator == 1) {
                        e_X++;
                    }
                    else {
                        t_X++;
                    }
                }
                else if(a[x][y] == avion) {
                    e[x][y] = 'Y';  //lovit avion
                }
                else {
                    e[x][y] = 'O';	//ratat
                }
                
                x = 1;
                y = 1;
                system("cls");
                cout << "\n\tJucator: " << jucator << "\n\n";
                e[x][y] = cub;
                display(e);
                break;
            default:
                break;
        }
    }
    g = 0;
    if (opponent == true) {
        opponent = false;
    }
    else {
        opponent = true;
    }
}

void put_planes(char a[100][100]) {
    int jucator;
    if (opponent == true) {
        jucator = 1;
    }
    else {
        jucator = 2;
    }
    system("cls");
    cout << "\n\nAseaza-ti cele trei avioane\n";
    cout << "\tJucator: " << jucator << "\n\n";
    int orient = 1, x = 3, y = 5;
    char c;
    place_aircraft(orient, x, y, a);
    display(a);
    
    while (1) {
        if (g == 3) {
            break;
        }
        switch (c = _getch()) {
            case 119:  //w
                delete_aircraft(orient, x, y, a);
                x--;
                if (place_aircraft(orient, x, y, a) == false) {
                    //delete_aircraft(orient, x, y);
                    x++;
                    place_aircraft(orient, x, y, a);
                }
                system("cls");
                cout << "\n\nAseaza-ti cele trei avioane\n";
                cout << "\tJucator: " << jucator << "\n\n";
                display(a);
                break;
            case 97:  //a
                delete_aircraft(orient, x, y, a);
                y--;
                if (place_aircraft(orient, x, y, a) == false) {
                    //delete_aircraft(orient, x, y);
                    y++;
                    place_aircraft(orient, x, y, a);
                }
                system("cls");
                cout << "\n\nAseaza-ti cele trei avioane\n";
                cout << "\tJucator: " << jucator << "\n\n";
                display(a);
                break;
            case 115:  //s
                delete_aircraft(orient, x, y, a);
                x++;
                if (place_aircraft(orient, x, y, a) == false) {
                    //delete_aircraft(orient, x, y);
                    x--;
                    place_aircraft(orient, x, y, a);
                }
                system("cls");
                cout << "\n\nAseaza-ti cele trei avioane\n";
                cout << "\tJucator: " << jucator << "\n\n";
                display(a);
                break;
            case 100:  //d
                delete_aircraft(orient, x, y, a);
                y++;
                if (place_aircraft(orient, x, y, a) == false) {
                    //delete_aircraft(orient, x, y);
                    y--;
                    place_aircraft(orient, x, y, a);
                }
                system("cls");
                cout << "\n\nAseaza-ti cele trei avioane\n";
                cout << "\tJucator: " << jucator << "\n\n";
                display(a);
                break;
            case 114:  //r
                delete_aircraft(orient, x, y, a);
                if (orient == 4) {
                    orient = 1;
                }
                else {
                    orient++;
                }
                if (place_aircraft(orient, x, y, a) == false) {
                    //delete_aircraft(orient, x, y);
                    if (orient == 1) {
                        orient = 4;
                    }
                    else {
                        orient--;
                    }
                    place_aircraft(orient, x, y, a);
                }
                system("cls");
                cout << "\n\nAseaza-ti cele trei avioane\n";
                cout << "\tJucator: " << jucator << "\n\n";
                display(a);
                break;
            case 32:  //space
                g++;
                place_aircraft(1, 1, 3, a);
                orient = 1;
                x = 1;
                y = 3;
                system("cls");
                cout << "\n\nAseaza-ti cele trei avioane\n";
                cout << "\tJucator: " << jucator << "\n\n";
                display(a);
                break;
            default:
                break;
        }
    }
    g = 0;
    if (opponent == true) {
        opponent = false;
    }
    else {
        opponent = true;
    }
}

int main() {
    int jucator;
    if (opponent == true) {
        jucator = 1;
    }
    else {
        jucator = 2;
    }
    
    system("Color F0");
    put_planes(a);
    put_planes(b);
    cout << "\n";
    
    while (e_X < 3 || t_X< 3) {
        check_plane(b, e);
        if (e_X == 3) {
            cout << "*****************************\n";
            cout << "Jucatorul 1 a castigat\n";
            cout << "*****************************\n";
            break;
        }
        else if(t_X == 3){
            cout << "*****************************\n";
            cout << "Jucatorul 2 a castigat\n";
            cout << "*****************************\n";
            break;
        }
        check_plane(a, t);
        if (e_X == 3) {
            cout << "*****************************\n";
            cout << "Jucatorul 1 a castigat\n";
            cout << "*****************************\n";
            break;
        }
        else if(t_X == 3){
            cout << "*****************************\n";
            cout << "Jucatorul 2 a castigat\n";
            cout << "*****************************\n";
            break;
        }
    }
}
