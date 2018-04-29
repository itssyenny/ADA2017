#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
using namespace std;
#define add(u, R) R |= (1ULL << u);
#define remove(u, R) R &= ~(1ULL << u)
#define is_set(u, R) R&(1ULL << u)
typedef struct Vertex{
    int adjacent[40];
    int size;
}Vertex;

unsigned long long int G[40];
bool visited[40];
int volunteer[40];
int min_cost = INT_MAX, n, m;

int get_cost(unsigned long long int R, Vertex V[]) {
    //This part runs in O(n) as the adjacencies are not that many
    int counted[40] = {0}, sum = 0;
    unsigned long long int x, y;

    for(int i = 0; i < n; i++) {
        x = is_set(i, R);
        if(x != 0 && !counted[i]) {
            sum += volunteer[i];
            counted[i] = 1;
            for(int j = 0; j < V[i].size; j++) {

                y = is_set(V[i].adjacent[j], R);

                if(counted[V[i].adjacent[j]] == 0 && y == 0) {
                    sum += volunteer[V[i].adjacent[j]];
                    counted[V[i].adjacent[j]] = 1;
                    // cout << "    adjacency " << j+1 << ",sum " << sum << endl;
                }
            }
        }
    }
    return sum;
}
void dfs(int v, unsigned long long int R,struct Vertex V[]) {
    visited[v] = true;
    //cout << "vertex " << v+1 << endl;
    //current cost
    
    int cost = get_cost(R,V);
    // cout << "cost " << cost << endl;
    
    if(min_cost < cost) return;
    if(v == 0) {
        min_cost = cost;
        return;
    }
    //copy the set and remove the v first :
    unsigned long long int K = R;
    remove(v, K);
    for(int i = 0; i < V[v].size; i++){
        unsigned long long int x = is_set(V[v].adjacent[i], G[v]);
        unsigned long long int y = (G[V[v].adjacent[i]]&K);
        if(visited[V[v].adjacent[i]] == false && (x != 0 && y == 0)) {
            add(V[v].adjacent[i], R);
            visited[V[v].adjacent[i]] = true;
            dfs(V[v].adjacent[i], R,V);
            remove(V[v].adjacent[i], R);
            visited[V[v].adjacent[i]] = false;
        }
    }
}

int main () {
    int u, v;
    Vertex V[40];
    
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        G[i] = 0;
        visited[i] = false;
        V[i].size = 0;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &volunteer[i]); 
    }
    
    for(int i = 0; i < m ; i++) {
        scanf("%d%d", &u, &v);
        u--, v--;
        
        V[u].adjacent[V[u].size] = v;
        V[u].size++;
        
        
        V[v].adjacent[V[v].size] = u;
        V[v].size++;
        
        G[u] |= (1ULL << v);
        G[v] |= (1ULL << u);
    }
    
    unsigned long long int R = 0;
    add((n-1), R);
    dfs((n-1), R, V);
    printf("%d\n", min_cost);
    return 0;
}

