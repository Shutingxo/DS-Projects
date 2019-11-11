#include<iostream>
#include<stdlib.h>
#include<limits.h>
#include<cmath>
#include<fstream>
using namespace std;
ifstream fin("floor.data");
ofstream fout("final.path");
int m, n, B, Br, Bc;
int uncleaned = 0, steps = 0, battery=0 , posindex = 0, times = 1;
int ur=0, uc=0;
int pos[1000][2]; //{row,col}
int direc[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; //f l b r
bool back = false ,backtoB=false;
typedef struct _Floor{
    char block; // 0:uncleaned ,1:block ,R:robot
    bool cleaned;
    int order;
    int check;
}Floor;
class Robot{
    public:
        Robot(){};
        void setpos(int r,int c){
            rbrow = r;
            rbcol = c;
        }
        void move(int dir){
            rbrow += direc[dir][0];
            rbcol += direc[dir][1];
            pos[posindex][0] = rbrow;
            pos[posindex++][1] = rbcol;
        }
        int getposr(){
            return rbrow;
        }
        int getposc(){
            return rbcol;
        }
    private:
        int rbrow;
        int rbcol;
};
Robot robot;
Floor **Read(Floor** floor){
    int i, j;
    floor = new Floor *[m];
    for(i = 0; i < m;i++){
        floor[i] = new Floor[n];
    }
    for(i = 0; i < m;i++){
        for(j = 0; j < n;j++){
            fin >> floor[i][j].block;
            if(floor[i][j].block == 'R'){
                robot.setpos(i, j);
                Br = pos[posindex][0] = i;
                Bc = pos[posindex++][1] = j;
                floor[i][j].cleaned = true;
                //-----cout << i << " " << j << endl; 
            }
            else if(floor[i][j].block == '0'){
                floor[i][j].cleaned = false;
                floor[i][j].order = 0;
                floor[i][j].check = 0;
                uncleaned++;
            }
            else
                floor[i][j].cleaned = true; // Walls=cleaned
        }
    }

    //-----cout << uncleaned << endl;
    return floor;
}

int Dis(Floor** floor,int r,int c,int x,int y){
    int dr = 0, dc = 0, tmpr, tmpc, block = 0;
    int i, j,dis=0;
    tmpr = r;
    tmpc = c;
    if(floor[r][c].block == '1' ||floor[r][c].block == 'R'|| floor[r][c].order == times || floor[r][c].check == times )
        return -1;

    dr = tmpr - x;
    dc = tmpc - y;
    //-----cout << dr << " " << dc << endl;
    dis= abs(dr) + abs(dc);
    //-----cout << dis <<endl;
    for (j = dis; j > 0, tmpr != x; j--){
        if (dr < 0) // r is above x, down
            tmpr += direc[2][0];
        else if (dr > 0) //below , up
            tmpr += direc[0][0];
        if (floor[tmpr][tmpc].block == '1')
            block++;
    }
    for (j; j > 0, tmpc != y; j--){
        if (dc < 0) //left ,move right
            tmpc += direc[3][1];
        else if (dc > 0) //right ,move left
            tmpc += direc[1][1];
        if (floor[tmpr][tmpc].block == '1')
            block++;
    }
    if (tmpr == x && tmpc == y){
        if(block>0)
            dis = (dis + block) * 2;
    }
    return dis;
}
bool Moveb(Floor** floor,int r,int c){
    int d[4] = {0};
    int i,nextr,nextc;
    int count = 0;
    for (i = 0; i < 4; i++){
        nextr = r + direc[i][0];
        nextc = c + direc[i][1];
        d[i] = Dis(floor, nextr, nextc,pos[1][0],pos[1][1]);
    }
    for (i = 0; i < 4;i++){
        if(d[i]==-1)
            count++;
    }
    if(count==4)
        return false;
    return true;
}

void Back(Floor** floor,int r,int c){
    if(r == pos[1][0] && c == pos[1][1]){
        backtoB = 1;
        return;
    }
    int dis[4] = {0};
    int min = INT_MAX;
    int nextr, nextc, cur, count = 0;
    int i, j;
    for (i = 0; i < 4; i++){
        nextr = r + direc[i][0];
        nextc = c + direc[i][1];
        dis[i] = Dis(floor, nextr, nextc,pos[1][0],pos[1][1]);
        floor[nextr][nextc].check = times;
    }
    for (i = 0; i < 4; i++){
        if(dis[i] != -1 && dis[i] <= min){
            cur = i;
            min = dis[i];
        }
    }
    for (j = 0; j < 4; j++){
        cur = (j + cur) % 4;
        if(dis[cur]==-1)
            continue;
        nextr = r + direc[cur][0];
        nextc = c + direc[cur][1];
        if(Moveb(floor,nextr,nextc)){
            //cout << nextr << " " << nextc << endl;
            robot.move(cur);
            steps++;
            battery--;
            floor[nextr][nextc].order = times;
            if(floor[nextr][nextc].cleaned == false){
                floor[nextr][nextc].cleaned == true;
                uncleaned--;
                if(nextr==ur && nextc == uc){
                    ur = 0;
                    uc = 0;
                }
            }
            Back(floor, nextr, nextc);

            if(backtoB == true)
                break;
        }
    }
}
bool Check(Floor** floor){
    int i, j;
    if(ur !=0 && uc!=0)
        return true;
    if(ur == 0 && uc == 0){
        for (i = 1; i < m-1; i++){
            for(j = 1; j < n-1; j++){
                if(floor[i][j].cleaned == false){
                   ur = i;
                   uc = j;
                   //cout << ur << " " << uc << endl;
                   return true;
                }
            }
        }
    }
    return false;

}
bool Move(Floor** floor,int dir,int nextr,int nextc){
    int r = robot.getposr(), c = robot.getposc();
    if(nextr < 0 || nextr > m-1 || nextc < 0 || nextc > n-1)
        // Outside the boundary
        return false;
    if(floor[nextr][nextc].block == '1' || floor[nextr][nextc].block == 'R')
        // Block
        return false;
    if(floor[nextr][nextc].block == '0' && floor[nextr][nextc].cleaned == false)
        //uncleaned
        return true;
    if(floor[nextr][nextc].block == '0' && floor[nextr][nextc].cleaned == true){
        if (floor[nextr][nextc].order < times && Check(floor)){
            int r = robot.getposr(), c = robot.getposc();
            int min = INT_MAX,cur;
            int tmpr, tmpc;
            int d[4] = {0};
            if(r == Br && c == Bc)
                return true;
            for (int i = 0; i < 4; i++){
                tmpr = r + direc[i][0];
                tmpc = c + direc[i][1];
                d[i] = Dis(floor, tmpr, tmpc, ur, uc);
                if(d[i]!=-1 && d[i]<= min){
                   cur = i;
                   min = d[i];
                }
            }
            if(cur == dir)
                return true;
            else
                floor[nextr][nextc].check = times;
        }
    } 
    //else        
    return false;
}
void Clean(Floor** floor){
    int max;
    int nextr, nextc, cur=0, i, j;
    int r, c;
    if(m>=n)
        max = m;
    else
        max = n;

    while(uncleaned > 0){
        for (i = 0; i < 4; i++){
            for (j = 0; j < max,uncleaned > 0; j++){
                r = robot.getposr();
                c = robot.getposc();
                if(battery > (B/3)){
                    nextr = r + direc[i][0];
                    nextc = c + direc[i][1];
                    if(Move(floor,i,nextr,nextc)){
                        //cout << nextr << " " << nextc << endl;
                        robot.move(i);
                        steps++;
                        battery--;
                        floor[nextr][nextc].order = times;
                        if(floor[nextr][nextc].cleaned == false){
                            floor[nextr][nextc].cleaned = true;
                           uncleaned--;
                            if(nextr==ur && nextc == uc){
                              ur = 0;
                              uc = 0;
                            }
                        }
                    }
                    else
                        break;
                    
                }
                else{ //battery < B/2
                    back = true;
                    break;
                }
            }
            if(uncleaned == 0)
                back = true;
            if(back == true)
               break;
        }
        if(floor[r-1][c].cleaned == true && floor[r][c-1].cleaned == true && floor[r+1][c].cleaned == true && floor[r][c+1].cleaned == true){
            if(floor[r-1][c].order == times && floor[r][c-1].order == times && floor[r+1][c].order == times && floor[r][c+1].order == times)
            back = true;
        }
        r = robot.getposr();
        c = robot.getposc();
        if(back == true){
            times++;
            floor[r][c].order = times;
            Back(floor,r,c);
            // at (pos[1][0],pos[1][1])
            robot.setpos(Br, Bc);
            steps++;
            battery = B;
            times++;
            pos[posindex][0] = Br;
            pos[posindex++][1] = Bc;
            back = false;
            backtoB = false;
            //-----cout << uncleaned << endl;
        }
    }
    if(uncleaned == 0  && steps == 0){
        robot.setpos(Br, Bc);
        pos[posindex][0] = Br;
        pos[posindex++][1] = Bc;
        return;
    }
}

void showfloor(Floor** floor){
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n;j++){
            cout << floor[i][j].block;
        }
        cout << endl;
    }
}
void showpath(){
    fout << steps << endl;
    for (int i = 0; pos[i][0] != 0 && pos[i][1] != 0 ; i++){
        fout << pos[i][0] << " " << pos[i][1] << endl;
    }
    fout.close();
}
int main(){
    if(!fin){ //check file
		cout << "Filein error!";
		exit(1);
	}
	if(!fout){
		cout << "Fileout error!";
		exit(1);
	}
    fin >> m >> n >> B ; //row col battery
    battery = B;
    Floor **floor = Read(floor);
    //-----showfloor(floor);
    Clean(floor);
    showpath();
}
