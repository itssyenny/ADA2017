#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include<iostream>
#include<vector>
#define MAX 100001
using namespace std;
int n, m, traversed, reentered;
bool __you_are_eligible;
int visited[MAX], __is_connected[MAX], __to_go[MAX], __next_to[MAX], path[MAX];
vector<vector<int> >G(MAX);

bool check_the_adjacency(int vertex, int from) {
    for(int i = 0; i < G[from].size(); i++) {
        if(G[from][i] == vertex) return true;
    }
    return false;
}

void dfs(int s) {
    //come to an end
//    cout << "Masuk dfs" << "\n";
    if(G[s].size() == 1) {
        if(G[s][0] > 0 && !visited[G[s][0]]) {
            visited[G[s][0]] = 1;
            __is_connected[G[s][0]] = 1;
            __next_to[s] = G[s][0];
            traversed++;
            dfs(G[s][0]);
        }
        return;
    }
    
    for(int i = 0; i < G[s].size() ; i++) {
        if(!visited[G[s][i]]  && __is_connected[G[s][i]] == 0) {
            visited[G[s][i]] = 1;
            traversed++;
            dfs(G[s][i]);
        }
    }
}
//--------------------------------------------------------------------------
int __retrieve(int a) {
    int temp = a;
    if(__to_go[a] != -2) return __to_go[a];
    while(a != __next_to[a]) {
        a = __next_to[a];
    }
    __to_go[temp] = a;
    return a;
}

void __dfs_again(int s) {
    if(!visited[s] && __is_connected[s] == 0) {
        visited[s] = 1;
        reentered++;
        int after = __retrieve(s);
        for(int j = 0; j < G[after].size(); j++) {
            __dfs_again(G[after][j]);
        }
    }
    return;
}

//You do this to run the graph backwards.
void __running(int s) {
    int __new;
    if(s == reentered) {
//        cout << "path[" << s-1 << "] " << path[s-1] << "\n";
        __new = __retrieve(path[s-1]);
        // cout << "__new " << __new << "\n";
        if(check_the_adjacency(path[0], __new) == true) {
            __you_are_eligible = true;
            for(int i = 0; i < reentered; i++) {
                cout << path[i]+1 << " ";
    //                printf("%d ", path[i]+1);
                int suck = path[i];
                while(suck != __next_to[suck]) {
                    suck = __next_to[suck];
                    cout << suck+1 << " ";
                    //printf("%d ", suck+1);
                }
            }
            cout << path[0]+1 << "\n";
            exit(0);
        }
    }
    __new = __retrieve(path[s-1]);
    for(int i = 0; i < G[__new].size(); i++) {
        if(__is_connected[G[__new][i]] == 0) {
            path[s] = G[__new][i];
            __is_connected[G[__new][i]] = 1;

            __running(s+1);
            __is_connected[G[__new][i]] = 0;
        }
    }
    
}
void check__the__visited() {
    for(int i = 0; i < n; i++) {
        cout << visited[i] << "\n";
    }
}
int main () {
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    
    int u, v;
    for(int i = 0; i < m; i++) {
        cin >> u >> v;
        u--, v--;
        //check whether v is adjacency to the u and has not been inputted
        if(u != v && check_the_adjacency(v, u) == false) {
            G[u].push_back(v);
        }
    }
    
    for(int i = 0; i < n; i++) {
        __next_to[i] = i;
        path[i] = -1;
        __to_go[i] = -2;
        visited[i] = 0;
        __is_connected[i] = 0;
    }

    traversed = 1;
    visited[0] = 1;
    dfs(0);
    
//    cout << "traversed " << traversed << ", n " << n << "\n";
    if(traversed != n) {
//        cout << "Masuk ke traversed != n" << "\n";
        cout << "-1" << "\n";
    } else {
//        cout << "Masuk ke traversed == n" << "\n";
        for(int i = 0; i < n; i++) visited[i] = 0;

        reentered = 0;
        __dfs_again(0);

        path[0] = 0;
        __is_connected[0] = 1;
        __you_are_eligible = false;
        
        __running(1);
//        cout << "You are eligible " << __you_are_eligible << "\n";
        if(__you_are_eligible == false) {
//            cout << "masuk false" << "\n";
            cout << "-1" << "\n";
        }
    }
    
    return 0;
}
