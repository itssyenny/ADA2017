#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<limits.h>
#include<list>
#include<algorithm>
using namespace std;
typedef struct pos {
    int degree, vertex;
} pos;

int acompare(const void *a, const void *b) { 
    pos *fa = (pos*)a;
    pos *fb = (pos*)b;
    if(fa->degree > fb->degree) return -1;
    else if(fa->degree < fb->degree) return 1;
    else if(fa->vertex < fb->vertex) return -1;
    else if(fa->vertex > fb->vertex) return 1;
    else return 0;
}

vector<list<int> > G(200001);
pos d[200001];
int visited[200001], deleted[200001], sorted[200001];
int counts[200001], triangles[1024][3];

int K3(int n) {
    //sort the degree first:
    int start = 0;
    //1:
    for(int i = 0 ; i < n-2; i++) {
        int vi = d[i].vertex;
        visited[vi] = 1;    //has already been visited
        
        list<int>::iterator u = G[vi].begin();
        for(; u != G[vi].end(); u++) {
            if(visited[*u] == 0 && deleted[*u] == 0) visited[*u] = 1;
        }

        u = G[vi].begin();
        //2: for each marked vertex u :
        for(; u != G[vi].end(); u++) {

            if(visited[*u] == 1 && deleted[*u] == 0) {

                list<int>::iterator w = G[*u].begin();
                //3:
                for( ; w != G[*u].end(); w++) {

                    if(*w != vi && (visited[*w] == 1 && deleted[*w] == 0)) {
                        counts[vi]++;    
                        counts[(*u)]++;  
                        counts[(*w)]++;
                        triangles[start][0] = vi;   
                        triangles[start][1] = *u;   
                        triangles[start][2] = *w;
                        start++;
                    }
                }//end for 3
                //Erase the mark from *u
                deleted[*u] = 0;
                visited[*u] = 0;
            }
        } //end for 2
        deleted[vi] = 1;
    } //end for 1
    return start;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    int u, v, cnt = 0;
    
    for(int i = 0; i < n; i++) {
        d[i].degree = 0;
        counts[i] = 0;
        deleted[i] = 0;
        visited[i] = -1;
    }
    
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        visited[u] = 0; 
        visited[v] = 0;
    }

    //Sorting in decreasing order based on the degree
    for(int i = 0; i < n; i++) {
        list<int>::iterator j = G[i].begin();
        for(; j != G[i].end(); j++) {
            d[i].vertex  = i;
            d[i].degree = G[i].size();
        }
    }

    qsort(d, n, sizeof(pos), acompare);  
    
    //Process the k clique
    if(m == 0) puts("1");
    else {    
        int k, start;   
        start = K3(n);

        if(start == 0) k = 2;
        else {
            k = 3;
            for(int j = 0; j < start; j++) {
                if(counts[triangles[j][0]] >= 3 && counts[triangles[j][1]] >= 3 && counts[triangles[j][2]] >= 3) {
                    k = 4;
                    break;
                }
            }
        }
        printf("%d\n", k);
        
    }
    return 0;
}

