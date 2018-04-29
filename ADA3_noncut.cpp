#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<queue>
#include<limits.h>
#include<list>
#define INF ULLONG_MAX
using namespace std;

typedef struct pos {
    int vertex;
    unsigned long long int dist;
    bool operator <(const struct pos &b)const {
        return dist>b.dist;
    }
}pos;

int main() {
    int n, m, s, t, u, v; scanf("%d%d%d%d", &n, &m, &s, &t);
    unsigned long long int w, total = 0;
    unsigned long long int d[n+1];
    vector<list<pos> >adjacencyList(n+1);
    pos edge1, edge2;
    
    for(int i = 0; i < m; i++) {
        scanf("%d%d%llu", &u, &v, &w);
        total += w;
        edge1.vertex = v-1; edge1.dist = w;
        adjacencyList[u-1].push_back(edge1);
        
        edge2.vertex = u-1; edge2.dist = w;
        adjacencyList[v-1].push_back(edge2);
    }
    
    priority_queue<pos>pq;
    int source = s-1, dest = t-1, count = 0;
    
    for(int i = 0; i < n; i++) {
        d[i] = INF;
    }
    d[source] = 0;
    
    for(int i = 0; i < n; i++) {
        pos x;
        x.vertex = i;
        x.dist = d[i];
        pq.push(x);
    }
    
    while(!pq.empty()) {
        pos que = pq.top();
        pq.pop();
        int u = que.vertex;
        printf("queue %d %llu , d[%d] %llu\n", u+1, que.dist,u+1, d[u]);
        if(u == dest || d[u] == INF) break;

        list<pos>::iterator v = adjacencyList[u].begin();
        list<pos>::iterator end = adjacencyList[u].end();
        //printf("size %lu\n", adjacencyList[u].size());
        for(; v != end ; v++) {
//          printf("adjancency %d %llu\n", (*v).vertex+1, (*v).dist);
            unsigned long long int zz = d[u] + (*v).dist;
            if(zz < d[(*v).vertex]) {
//              printf("%d->%d : %llu + %llu = zz %llu\n", u+1,(*v).vertex+1, d[u],(*v).dist,  zz);
                d[(*v).vertex] = zz;
                pos damn;
                damn.vertex = (*v).vertex;
                damn.dist = zz;
                pq.push(damn);
            }
        }
//     puts("---------------------------");
    }
    
//    for(int i = 0; i < n; i++) {
//        printf("%llu ", d[i]);
//    }
//    printf("\n");

    if(d[t-1] == INF) puts("-1");
    else printf("%llu\n", total-d[t-1]);
    
    return 0;
}



