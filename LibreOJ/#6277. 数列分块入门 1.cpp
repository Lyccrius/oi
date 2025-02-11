#include <iostream>

const int maxN = 5e4;
const int sqrtN = 223;

int n;
int a[maxN + 10];
int opt, l, r, c;

struct BlockArray {
    struct Block {
        int l, r;
        int tag;
    } block[sqrtN + 10];

    int bcnt;

    struct Array {
        int val;
        int bel;
    } array[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) {
            array[i].val = a[i];
            array[i].bel = (i - 1) / sqrtN + 1;
            if (array[i].bel != array[i - 1].bel) {
                block[array[i].bel].l = i;
            }
            block[array[i].bel].r = i;
            block[array[i].bel].tag = 0;
        }
        return;
    }

    void Modify(int l, int r, int c) {
        if (array[l].bel == array[r].bel) {
            for (int i = l; i <= r; i++) array[i].val += c;
            return;
        }
        for (int a = l; a <= block[array[l].bel].r; a++) array[a].val += c;
        for (int a = block[array[r].bel].l; a <= r; a++) array[a].val += c;
        for (int b = array[l].bel + 1; b < array[r].bel; b++) block[b].tag += c;
        return;
    }

    int Query(int r) {
        return array[r].val + block[array[r].bel].tag;
    }
} BA;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    BA.Init();
    for (int i = 1; i <= n; i++) {
        std::cin >> opt >> l >> r >> c;
        if (opt == 0) BA.Modify(l, r, c);
        else std::cout << BA.Query(r) << '\n';
    }
    return 0;
}