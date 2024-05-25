#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#pragma GCC optimize("Ofast,unroll-loops")

void tr_sqr(std::vector<std::vector<int>>& x) {
    int n = x.size();
    if (n != x[0].size()) return;
    std::unique_ptr<std::vector<std::vector<int>>> temp(new std::vector<std::vector<int>>);
    *temp = x;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            x[i][j] = (*temp)[j][i];
        }
    }
}

void pad(std::vector<std::vector<int>>& x, int& c, int& t) {
    int n = x.size();
    int m = x[0].size();
    if (n == m) return;
    if (n > m) {
        t = 0; // type
        c = n - m; // displace
        for (auto& i : x) {
            for (int j = 0; j < c; ++j) {
                i.push_back(0);
            }
        }
    }
    else if (n < m) {
        t = 1;
        c = m - n;
        for (int i = 0; i < c; ++i) {
            std::vector<int> a(m, 0);
            x.push_back(a);
        }
    }
}

void rpad(std::vector<std::vector<int>>& x, int c, int t) {
    if (t == 0) {
        for (int i = 0; i < c; ++i) {
            x.pop_back();
        }
    }
    else if (t == 1) {
        for (auto& i : x) {
            for (int j = 0; j < c; ++j) {
                i.pop_back();
            }
        }
    }
}

void tr(std::vector<std::vector<int>>& x) {
    std::unique_ptr<int> c(new int);
    std::unique_ptr<int> t(new int);
    *c, *t = 0;
    pad(x, *c, *t);
    tr_sqr(x);
    rpad(x, *c, *t);
}

std::vector<std::vector<int>> gen(int n, int m) {
    std::vector<std::vector<int>> t(n);
    for (int i = 0; i < n; ++i) {
        std::vector<int> a(m);
        for (int j = 0; j < m; ++j) {
            a[j] = static_cast<int>(rand() % 100);
        }
        t[i] = a;   
    }
    return t;
}

void p_m(std::vector<std::vector<int>>& x) {
    for (auto& i : x) {
        for (auto& j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    srand (time(NULL));
    std::vector<std::vector<int>> t = gen(4, 4);
    p_m(t);
    tr(t);
    std::cout << std::endl;
    p_m(t);
    return 0;
}
