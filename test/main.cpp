#include <bits/stdc++.h>

using namespace std;

void Matrix(int p[], int n, int **m, int **s) {
    for (int i = 1; i <= n; ++i)
        m[i][i] = 0;
    for (int r = 2; r <= n; ++r) {
        for (int i = 1; i <= n; ++i) {
            int j = i + r - 1;
            m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
            s[i][j] = i;
            for (int k = i + 1; k < j; ++k) {
                int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (t < m[i][j]) {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
}

void Traceback(int i, int j, int **s) {
    if (i == j) {
        return;
    }
    Traceback(i, s[i][j], s);
    Traceback(s[i][j] + 1, j, s);
    cout << "Multiply A" << i << "," << s[i][j];
    cout << "and A" << (s[i][j] + 1) << "," << j << endl;
}

int main() {
    int n;
    while (cin >> n) {
        int **m = new int *[n + 1];
        int **s = new int *[n + 1];
        for (int i = 1; i <= n; i++) {
            m[i] = new int[n + 1];
            s[i] = new int[n + 1];
        }
        int p[n + 1];
        for (int i = 1; i <= n; ++i) {
            cin >> p[i];
        }
        Matrix(p, n, m, s);
        Traceback(1, n, s);
    }
}
