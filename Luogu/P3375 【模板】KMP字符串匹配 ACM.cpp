#include <iostream>
#include <deque>
#include <cstring>

typedef char chr;
typedef std::deque<int> diq;

const int maxN = 1e6;
const int maxM = 1e6;

chr s1[maxN + 10];
chr s2[maxM + 10];
int n;
int m;

struct AhoCosarickAutomaton {
    struct Node {
        int son[30];
        int fail;
        int index;
    } node[maxM + 10];
    
    int ncnt;
    int root;

    void Insert(chr *str) {
        int u = root;
        for (int i = 1; str[i]; i++) {
            int ch = str[i] - 'A' + 1;
            if (node[u].son[ch] == 0) node[u].son[ch] = ++ncnt;
            u = node[u].son[ch];
            //printf("node[%d].ch = %c\n", u, 'A' + ch - 1);
        }
        node[u].index = true;
        return;
    }

    void Build() {
        diq q;
        for (int i = 1; i <= 26; i++) if (node[root].son[i]) q.push_back(node[root].son[i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int i = 1; i <= 26; i++) {
                if (node[u].son[i]) {
                    node[node[u].son[i]].fail = node[node[u].fail].son[i];
                    q.push_back(node[u].son[i]);
                } else {
                    node[u].son[i] = node[node[u].fail].son[i];
                }
            }
        }
        //for (int i = 1; i <= ncnt; i++) printf("node[%d].fail = %d\n", i, node[i].fail);
        return;
    }

    void Query(chr *str) {
        int u = root;
        for (int i = 1; str[i]; i++) {
            int ch = str[i] - 'A' + 1;
            u = node[u].son[ch];
            if (node[u].index) {
                std::cout << i - m + 1 << '\n';
            }
        }
        for (int i = 1; i <= ncnt; i++) std::cout << node[i].fail << ' ';
        return;
    }
} ACM;

int main() {
    std::cin >> (s1 + 1);
    std::cin >> (s2 + 1);
    n = strlen(s1 + 1);
    m = strlen(s2 + 1);
    ACM.Insert(s2);
    ACM.Build();
    ACM.Query(s1);
    return 0;
}