#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;
const int logN = 17;

int n;
int c[maxN + 10];
int x[maxN + 10], y[maxN + 10];

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        int val;
        lxl res;
    } node[maxN * 4 + maxN * logN];

    int ncnt;
    
    int root[maxN + 10];

    void Build(int &xNode, int l, int r){
        ncnt++;
        xNode = ncnt;
        node[xNode].l = l;
        node[xNode].r = r;
        return;
    }

    void PushUp(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        if (node[lNode].val > node[rNode].val) {
            node[xNode].val = node[lNode].val;
            node[xNode].res = node[lNode].res;
        }
        if (node[lNode].val < node[rNode].val) {
            node[xNode].val = node[rNode].val;
            node[xNode].res = node[rNode].res;
        }
        if (node[lNode].val == node[rNode].val) {
            node[xNode].val = node[lNode].val;
            node[xNode].res = node[lNode].res + node[rNode].res;
        }
        return;
    }

    void Modify(int &xNode, int p) {
        if (node[xNode].l == node[xNode].r) {
            node[xNode].val++;
            node[xNode].res = p;
            return;
        }
        int mid = (node[xNode].l + node[xNode].r) / 2;
        if (p <= mid) {
            if (node[xNode].lNode == 0) Build(node[xNode].lNode, node[xNode].l, mid);
            Modify(node[xNode].lNode, p);
        }
        if (p > mid) {
            if (node[xNode].rNode == 0) Build(node[xNode].rNode, mid + 1, node[xNode].r);
            Modify(node[xNode].rNode, p);
        }
        PushUp(xNode);
        return;
    }

    void Merge(int &xNode, int yNode) {
        if (xNode == 0 || yNode == 0) {
            xNode = xNode ^ yNode;
            return;
        }
        if (node[xNode].l == node[xNode].r) {
            node[xNode].val += node[yNode].val;
            node[xNode].res = node[xNode].l;
            return;
        }
        Merge(node[xNode].lNode, node[yNode].lNode);
        Merge(node[xNode].rNode, node[yNode].rNode);
        PushUp(xNode);
        return;
    }

    lxl Query(int xNode) {
        return node[xNode].res;
    }
} SGT;

namespace graph {
    struct Vertex {
        int head;
        lxl res;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u, int from) {
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            SGT.Merge(SGT.root[u], SGT.root[v]);
        }
        SGT.Modify(SGT.root[u], c[u]);
        vertex[u].res = SGT.Query(SGT.root[u]);
        return;
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> c[i], SGT.Build(SGT.root[i], 1, n);
    for (int i = 1; i < n; i++) std::cin >> x[i] >> y[i], graph::addEdge(x[i], y[i]), graph::addEdge(y[i], x[i]);
    graph::DFS(1, 0);
    for (int i = 1; i <= n; i++) std::cout << graph::vertex[i].res << ' ';
    return 0;
}