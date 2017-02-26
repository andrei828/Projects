#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

#define bara_verticala |
#define bara_orizontrala _
#define corp '#'
#define nxtLvl 500

using namespace std;

int lungime;
int scor;
bool e;
int level = 1;
int final;
char a[100][100];
pair <int, int> v[100];
pair <int, int> a_coord;

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

void get_aCoord(){
    
    do{
        a_coord.first  = rand() % 30;
        a_coord.second = rand() % 30;
    }while(a[a_coord.first][a_coord.second] == '#');
        a[a_coord.first][a_coord.second] = '@';
}

void initLvl1(){
    for(int i = 15; i >= 12; i--){
        v[lungime].first  = 15;
        v[lungime].second = i;
        lungime++;
    }
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
    

    get_aCoord();

}

void initLvl2(){
    for(int i = 15; i >= 12; i--){
        v[lungime].first  = 21;
        v[lungime].second = i;
        lungime++;
    }
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
    for(int i = 12; i < 18; i++){
        for(int j = 8; j < 22; j++){
            a[i][j] = '#';
        }
    }
    get_aCoord();
}

void initLvl3(){
    for(int i = 15; i >= 12; i--){
        v[lungime].first  = 15;
        v[lungime].second = i;
        lungime++;
    }
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
    
    for(int i = 6; i < 12; i++){
        for(int j = 8; j < 22; j++){
            a[i][j] = '#';
        }
    }
    for(int i = 18; i < 24; i++){
        for(int j = 8; j < 22; j++){
            a[i][j] = '#';
        }
    }
    
    get_aCoord();
}

void initLvl4(){
    for(int i = 15; i >= 12; i--){
        v[lungime].first  = 15;
        v[lungime].second = i;
        lungime++;
    }
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
    
    for(int i = 4; i < 10; i++){
        for(int j = 4; j < 11; j++){
            a[i][j] = '#';
        }
    }
    
    for(int i = 4; i < 10; i++){
        for(int j = 17; j < 24; j++){
            a[i][j] = '#';
        }
    }
    
    for(int i = 18; i < 24; i++){
        for(int j = 4; j < 11; j++){
            a[i][j] = '#';
        }
    }
    
    for(int i = 18; i < 24; i++){
        for(int j = 17; j < 24; j++){
            a[i][j] = '#';
        }
    }
}

void update_vLvl1(){
    
    for(int i = 0 ; i < 30; i++){
        for(int j = 0; j < 30; j++){
            a[i][j] = NULL;
        }
    }
    
    a[a_coord.first][a_coord.second] = '@';
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
}

void update_vLvl2(){
    
    for(int i = 0 ; i < 30; i++){
        for(int j = 0; j < 30; j++){
            a[i][j] = NULL;
        }
    }
    
    a[a_coord.first][a_coord.second] = '@';
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
    for(int i = 12; i < 18; i++){
        for(int j = 8; j < 22; j++){
            a[i][j] = '#';
        }
    }
}

void update_vLvl3(){
    for(int i = 0 ; i < 30; i++){
        for(int j = 0; j < 30; j++){
            a[i][j] = NULL;
        }
    }
    
    a[a_coord.first][a_coord.second] = '@';
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
    for(int i = 6; i < 12; i++){
        for(int j = 8; j < 22; j++){
            a[i][j] = '#';
        }
    }
    for(int i = 18; i < 24; i++){
        for(int j = 8; j < 22; j++){
            a[i][j] = '#';
        }
    }
}

void update_vLvl4(){
    for(int i = 0 ; i < 30; i++){
        for(int j = 0; j < 30; j++){
            a[i][j] = NULL;
        }
    }
    
    a[a_coord.first][a_coord.second] = '@';
    
    for(int i = 0; i < lungime; i++){
        a[v[i].first][v[i].second] = '#';
    }
    
    for(int i = 4; i < 10; i++){
        for(int j = 5; j < 12; j++){
            a[i][j] = '#';
        }
    }
    
    for(int i = 4; i < 10; i++){
        for(int j = 18; j < 25; j++){
            a[i][j] = '#';
        }
    }
    
    for(int i = 18; i < 24; i++){
        for(int j = 5; j < 12; j++){
            a[i][j] = '#';
        }
    }
    
    for(int i = 18; i < 24; i++){
        for(int j = 18; j < 25; j++){
            a[i][j] = '#';
        }
    }
}

void move(char c){
    
    if(c == 'w'){
        //no collision
        if(v[0].first-1 != v[1].first && a[v[0].first-1][v[0].second] != '@' && a[v[0].first-1][v[0].second] != '#' && v[0].first-1 <= 29 && v[0].first-1 >= 0 && v[0].second <= 29 && v[0].second > 0){
            
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
        v[0].first--;
        //colission with itself
        }else if(a[v[0].first-1][v[0].second] == '#' || v[0].first-1 > 29 || v[0].first-1 < 0 || v[0].second > 29 || v[0].second < 0){
            cout<<"\n                          ****************GAME OVER****************\n";
            e = true;
            final = true;
            return;
        //collision with point
        }else if(a[v[0].first-1][v[0].second] == '@'){
            a[v[0].first-1][v[0].second] = NULL;
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            v[0].first--;
            for(int i = lungime; i >= 1; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            lungime++;
            get_aCoord();
            scor += 100;
            if(scor == nxtLvl){
                e = true;
                level++;
            }
            return;
        }
    }else if(c == 'd'){
        //no collision
        if(v[0].second+1 != v[1].second && a[v[0].first][v[0].second+1] != '@' && a[v[0].first][v[0].second+1] != '#' && v[0].second+1 <= 29 && v[0].second+1 >= 0 && v[0].first <= 29 && v[0].first >= 0){
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
        v[0].second++;
        //collision with itself
        }else if(a[v[0].first][v[0].second+1] == '#' || v[0].second+1 > 29 || v[0].second+1 < 0 || v[0].first > 29 || v[0].first < 0){
            cout<<"\n                          ****************GAME OVER****************\n";
            e = true;
            final = true;
            return;
        //collision with point
        }else if(a[v[0].first][v[0].second+1] == '@'){
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            v[0].second++;
            for(int i = lungime; i >= 1; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            lungime++;
            get_aCoord();
            scor += 100;
            if(scor == nxtLvl){
                e = true;
                level++;
            }
            return;
        }
    }else if(c == 'a'){
        //no collision
        if(v[0].second-1 != v[1].second && a[v[0].first][v[0].second-1] != '@' && a[v[0].first][v[0].second-1] != '#' && v[0].second-1 <= 29 && v[0].second-1 >= 0 && v[0].first <= 29 && v[0].first >= 0){
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
        v[0].second--;
        //collision with itself
        }else if(a[v[0].first][v[0].second-1] == '#' || v[0].second-1 > 29 || v[0].second-1 < 0 || v[0].first > 29 || v[0].first < 0){
            cout<<"\n                          ****************GAME OVER****************\n";
            e = true;
            final = true;
            return;
        //collision with point
        }else if(a[v[0].first][v[0].second-1] == '@'){
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            v[0].second--;
            for(int i = lungime; i >= 1; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            lungime++;
            get_aCoord();
            scor += 100;
            if(scor == nxtLvl){
                e = true;
                level++;
            }
            return;
        }
    }else if(c == 's'){
        //no collision
        if(v[0].first+1 != v[1].first && a[v[0].first+1][v[0].second] != '@' && a[v[0].first+1][v[0].second] != '#' && v[0].first+1 <= 29 && v[0].first+1 >= 0 && v[0].second <= 29 && v[0].second >= 0){
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
        v[0].first++;
            //collision with itself
        }else if(a[v[0].first+1][v[0].second] == '#' || v[0].first+1 > 29 || v[0].first+1 < 0 || v[0].second > 29 || v[0].second < 0){
            cout<<"\n                          ****************GAME OVER****************\n";
            e = true;
            final = true;
            return;
        //collision with point
        }else if(a[v[0].first+1][v[0].second] == '@'){
            for(int i = lungime-1; i > 0; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            v[0].first++;
            for(int i = lungime; i >= 1; i--){
                v[i].first  = v[i-1].first;
                v[i].second = v[i-1].second;
            }
            lungime++;
            get_aCoord();
            scor += 100;
            if(scor == nxtLvl){
                e = true;
                level++;
            }
            return;
        }
    }
    if(level == 1){
        update_vLvl1();
    }else if(level == 2){
        update_vLvl2();
    }else if(level == 3){
        update_vLvl3();
    }else if(level == 4){
        update_vLvl4();
    }
}

void display()
{
    cout<<"\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t  SNAKE\n";
    //  top
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    //  end top
    
    //  body
    for(int i = 0; i < 30; i++){
        cout<<"               ";
        cout<<"|";
        for(int j = 0; j < 30; j++){
            cout<<" ";
            if(a[i][j] == NULL){
                cout<<" ";
            }else{
                cout<<a[i][j];
            }
        }cout<<"|\n";
    }
    //  end body
    
    //  bottom
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    cout<<"               ";
    cout<<"Score: "<<scor<<"\n";
    //  end bottom
}

void menuYes(){
    cout<<"\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t  SNAKE\n";
    //  top
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    //  end top
    
    //  body
    for(int i = 0; i < 15; i++){
        cout<<"               ";
        cout<<"|";
        for(int j = 0; j < 30; j++){
            cout<<"  ";
        }cout<<"|\n";
    }
    cout<<"               | \t\t\tDo you want to start the game?             | \n";
    cout<<"               |\t\t\t    X Yes            No                         | \n";
    for(int i = 0; i < 15; i++){
        cout<<"               ";
        cout<<"|";
        for(int j = 0; j < 30; j++){
            cout<<"  ";
        }cout<<"|\n";
    }
    //  end body
    
    //  bottom
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    cout<<"               ";
    cout<<"Score: "<<scor<<"\n";
    //  end bottom
}

void menuNo(){
    cout<<"\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t  SNAKE\n";
    //  top
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    //  end top
    
    //  body
    for(int i = 0; i < 15; i++){
        cout<<"               ";
        cout<<"|";
        for(int j = 0; j < 30; j++){
            cout<<"  ";
        }cout<<"|\n";
    }
    cout<<"               | \t\t\tDo you want to start the game?             | \n";
    cout<<"               |\t\t\t      Yes          X No                         | \n";
    for(int i = 0; i < 15; i++){
        cout<<"               ";
        cout<<"|";
        for(int j = 0; j < 30; j++){
            cout<<"  ";
        }cout<<"|\n";
    }
    //  end body
    
    //  bottom
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    cout<<"               ";
    cout<<"Score: "<<scor<<"\n";
    //  end bottom
}

void congrats(){
    cout<<"\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t  SNAKE\n";
    //  top
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    //  end top
    
    //  body
    for(int i = 0; i < 15; i++){
        cout<<"               ";
        cout<<"|";
        for(int j = 0; j < 30; j++){
            cout<<"  ";
        }cout<<"|\n";
    }
    cout<<"               | \t\t\t\tCongratulations                      | \n";
    cout<<"               | \t\t\t\t                                     | \n";
    cout<<"               |\t\t\t\t  Next Level                         | \n";
    cout<<"               | \t\t\t\t                                     | \n";
    cout<<"               | \t\t             Reach 500 points                     | \n";
    for(int i = 1; i < 15; i++){
        cout<<"               ";
        cout<<"|";
        for(int j = 0; j < 30; j++){
            cout<<"  ";
        }cout<<"|\n";
    }
    //  end body
    
    //  bottom
    cout<<"               ";
    cout<<" ";
    for(int i = 0; i < 60; i++)
    {
        cout<<"-";
    }cout<<"\n";
    cout<<"               ";
    cout<<"Score: "<<scor<<"\n";
    //  end bottom
}

void clear(){
    for(int i = 0; i < 30; i++){
        for(int j = 0; j < 30; j++){
            a[i][j] = NULL;
        }
    }
    lungime = 0;

}

int main()
{
    srand(time(NULL));
    char plm = 'a';
    bool ent = true;
    char aux;
    menuYes();
    do {
        if(kbhit()){
            plm = getchar();
            if(plm == 'd'){
                menuNo();
                ent = false;
            }else if(plm == 'a'){
                menuYes();
                ent = true;
            }
        }
    }while(plm != '\n');
    if(ent == true){
        //lvl 1
    char c = 'd';
    initLvl1();
    while(!e){
        display();
        usleep(100000);
        
            move(c);
        
        aux = c;
        if(kbhit()){
            c = getchar();
            if(c == 'd' && aux != 'a'){
                move(c);
            }else if(c == 'w' && aux != 's'){
                move(c);
            }else if(c == 'a' && aux != 'd'){
                move(c);
            }else if(c == 's' && aux != 'w'){
                move(c);
            }else{
                c = aux;
            }
        }
    }
    if(!final){
        //lvl 2
        scor = 0;
        level = 2;
        e = false;
        c = 'd';
        clear();
        initLvl2();
        congrats();
        usleep(1500000);
        update_vLvl2();
        while (!e) {
            display();
            usleep(100000);
            
            move(c);
            
            aux = c;
            if(kbhit()){
                c = getchar();
                if(c == 'd' && aux != 'a'){
                    move(c);
                }else if(c == 'w' && aux != 's'){
                    move(c);
                }else if(c == 'a' && aux != 'd'){
                    move(c);
                }else if(c == 's' && aux != 'w'){
                    move(c);
                }else{
                    c = aux;
                }
            }
        }
    }
    if(!final){
        //lvl 3
        scor = 0;
        level = 3;
        e = false;
        c = 'd';
        clear();
        initLvl3();
        congrats();
        usleep(1500000);
        update_vLvl3();
        while (!e) {
            display();
            usleep(100000);
            
            move(c);
            
            aux = c;
            if(kbhit()){
                c = getchar();
                if(c == 'd' && aux != 'a'){
                    move(c);
                }else if(c == 'w' && aux != 's'){
                    move(c);
                }else if(c == 'a' && aux != 'd'){
                    move(c);
                }else if(c == 's' && aux != 'w'){
                    move(c);
                }else{
                    c = aux;
                }
            }
        }

    }
    if(!final){
        //lvl 4
        scor = 0;
        level = 4;
        e = false;
        c = 'd';
        clear();
        initLvl4();
        congrats();
        usleep(1500000);
        update_vLvl4();
        while (!e) {
            display();
            usleep(100000);
            
            move(c);
            
            aux = c;
            if(kbhit()){
                c = getchar();
                if(c == 'd' && aux != 'a'){
                    move(c);
                }else if(c == 'w' && aux != 's'){
                    move(c);
                }else if(c == 'a' && aux != 'd'){
                    move(c);
                }else if(c == 's' && aux != 'w'){
                    move(c);
                }else{
                    c = aux;
                }
            }
        }
    }
    if(!final){
        cout<<"                          ***********Thanks for playing*************\n";
    }
    }else{
        cout<<"Du-te in plm";
    }
}
