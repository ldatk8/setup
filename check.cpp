/**
 *    author : Lăng Trọng Đạt
 *    created: 2024-08-15
**/
#include <bits/stdc++.h>
using namespace std;
#ifndef LANG_DAT
#define db(...) ;
#endif // LANG_DAT
#define int long long
#define mp make_pair
#define f first
#define se second
#define pb push_back
#define all(v) (v).begin(),

const int N = 1e5 + 5;
int g[N];
int n, m, k, a, b;

void gen() {
    ofstream out;
    out.open("three.inp");
    out << 1 << "\n";
    int n = 200, m = 20, q = 15;
    set<pair<int, int>> s;
    FOR(i, 1, m) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        s.insert({x, y});
    }
    m = si(s);
    out << n << " " << m << " " << q << "\n";
    for (auto[x, y] : s) {
        out << x << " " << y << " " << rand() % 400 + 1 << "\n";
    }
    FOR(i, 1, q) {
        out << rand() % m + 1 << " " << rand() % 200 + 1 << "\n";
    }

    out.close();
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    if (fopen("hi.inp", "r")) {
        freopen("hi.inp", "r", stdin);
//        freopen("hi.out", "w", stdout);
    }

    srand(time(NULL));
    system(string("g++ three_trau.cpp -o trau.exe").c_str());
    system(string("g++ three.cpp -o hi.exe").c_str());
    int tc = 100;
    FOR(i, 1, tc) {
        gen();

        system(string("trau.exe").c_str());
        system(string("hi.exe").c_str());

        db(i);

        if (system(string("fc /A three.out three_trau.out").c_str())) {
            db("fuck");
            return 0;
        }
    }
//    gen();
}
