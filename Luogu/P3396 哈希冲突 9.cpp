#include <iostream>
#include <map>

typedef char chr;

const int maxN = 1.5e5;
const int maxM = 1.5e5;

int n, m;
int a[maxN + 10];
std::map<int, std::map<int, int> > b;
chr cmp; int x, y;

void prework() {
    for (int p = 1; p <= n; p++) {
        for (int i = 1; i <= n; i++) {
            b[p][i % p] += a[i];
        }
    }
    return;
}

int query(int p, int i) {
    return b[p][i % p];
}

void modify(int i, int val) {
    for (int p = 1; p <= n; p++) {
        b[p][i % p] += val - a[i];
    }
    a[i] = val;
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i]; prework();
    for (int i = 1; i <= m; i++) {
        std::cin >> cmp >> x >> y;
        if (cmp == 'A') std::cout << query(x, y) << '\n';
        else if (cmp == 'C') modify(x, y);
    }
    return 0;
}