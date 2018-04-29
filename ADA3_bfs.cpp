#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<limits.h>
using namespace std;
typedef struct pos {
    int x, y, step;
}pos;

char a[3001][3001];

int dir[4][2] = {{0,1}, {1,0}, {-1, 0}, {0,-1}};

bool check(pos a, int n, int m) {
    if(a.x >= 0 && a.y >= 0 && a.x < n && a.y < m) return true;
    return false;
}

void clear(queue<pos> &q) {
    queue<pos>empty;
    swap( q, empty);
}
int main () {
    int n,m; scanf("%d%d", &n, &m);
    int k = 0, e = 0; // the num of people.
    bool visited[n+1][m+1];
    int distance[n+1][m+1];
    pos p[100001], exit[n*m+1];
    queue<pos>q;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf(" %c", &a[i][j]);
            if(a[i][j] == 'P') {
                p[k].x = i;     p[k].step = 0;
                p[k].y = j;     k++;
            }else if(a[i][j] == 'E') {
                e++;
                exit[e].x = i;
                exit[e].y = j;
                exit[e].step = 0;
                q.push(exit[e]);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            distance[i][j] = -1;
    }
    
    memset(visited, false, sizeof(visited));
    
    for(int i = 0; i < e; i++) {
        while(!q.empty()) {
            pos temp = q.front();
            q.pop();
            for(int j = 0; j < 4; j++) {
                pos next;
                next.x = temp.x + dir[j][0];
                next.y = temp.y + dir[j][1];
                next.step = temp.step + 1;
                
                if(check(next,n,m) && !visited[next.x][next.y]) {
                    if(a[next.x][next.y] == 'F') continue;
                    else if(a[next.x][next.y] == '.' || a[next.x][next.y] == 'P') {
                        visited[next.x][next.y] = true;
                        distance[next.x][next.y] = next.step;
                        q.push(next);
                    }
                }
            }
        }   //end of while
    }
//    for(int i = 0; i < n; i++) {
//        for(int j = 0; j < m; j++)
//            printf("%d ", distance[i][j]);
//        printf("\n");
//    }

    for(int i = 0; i < k; i++) {
        if(distance[p[i].x][p[i].y] != -1) printf("%d\n",distance[p[i].x][p[i].y]);
        else puts("Died");
    }
    
    return 0;
}

