#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("alee.in");
ofstream fout("alee.out");

int di[4] = {1,-1,0,0};
int dj[4] = {0,0,1,-1};

int startx, starty, stopx, stopy;
int N,M;
int Map[180][180];

queue < pair < int, int > > coada;

void Init(){
    fin >> N >> M;
    for(int i = 1; i <= M; i++){
        int x, y;
        fin >> x >> y;
        Map[x][y] = -1;
    }
    fin >> startx >> starty >> stopx >> stopy;
}

bool OK(int i, int j){
    if(i < 1 || j < 1 || i > N || j > N){
        return false;
    }
    if(Map[i][j] == -1){
        return false;
    }
    return true;
}

void Lee(){
    int i, j, urm_i, urm_j;
    Map[startx][starty] = 1;
    coada.push(make_pair(startx, starty));
    
    while ( !coada.empty() ) {
        i = coada.front().first;
        j = coada.front().second;
        coada.pop();
        
        for(int dir = 0; dir < 4; dir++){
            urm_i = i + di[dir];
            urm_j = j + dj[dir];
            if(OK(urm_i, urm_j) == true && Map[urm_i][urm_j] < 1){
                Map[urm_i][urm_j] = Map[i][j] + 1;
                coada.push(make_pair(urm_i, urm_j));
            }
        }
    }
}

int main()
{
    Init();
    Lee();
    fout<<Map[stopx][stopy];
}
