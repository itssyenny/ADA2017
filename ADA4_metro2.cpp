#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<ctype.h>
#include<algorithm>
#include<limits.h>
#include<ctime>
#define is_set(R, u) R&(~u)
#define __and_it(R, u) R&u

using namespace std;

__int128 G[128], one = 1;
int n, m, answer;
//answer : maximum clique number

int additional(__int128 x) {
  return __builtin_popcountll(x >> 64) + __builtin_popcountll(x&((one << 64)-1));
}

int randomize(__int128 bitset, int one_in_bitset) {
  int help;
  one_in_bitset = additional(bitset);
  int random = rand() % one_in_bitset + 1;
  for(int i = 0, j = 0; i < n; i++) {
    if(bitset&(one << i)) j++;
    if(j == random) {help = i ; break;};
  }
  return help;
}

void clique(__int128 bitset, int one_in_bitset) {
  if(one_in_bitset > answer) answer = one_in_bitset;
  // printf("one in bitchset = %d\n", one_in_bitset);

  int temp = one_in_bitset + additional(bitset);
  if(temp <= answer) return;

  int pivot = randomize(bitset, one_in_bitset);
    __int128 bitset_s = is_set(bitset, G[pivot]);

  while(bitset_s && temp > answer) {
    int continued = randomize(bitset_s, one_in_bitset);

    bitset ^= (one << continued);
    bitset_s ^= (one << continued);
    temp--;

    if(continued == pivot || (bitset_s&G[continued])) {
      clique(__and_it(bitset, G[continued]), one_in_bitset+1);
    }
  }
}

int main() {
  srand(time(NULL));
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
    G[i] = 0;
  }

  int u, v; 
  for(int i = 0; i < m; i++) {
    scanf("%d%d", &u, &v);
    G[u] |= (one << v);
    G[v] |= (one << u);
  }

  __int128 p = (one << n) - 1;
  clique(p, 0);
  printf("%d\n", answer);
  return 0;
}
