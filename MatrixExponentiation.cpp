/**This code computes the nth fibonacci number for very large n
 * using Matrix Exponentiation
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<long> > multiply(vector<vector<long> > x, vector<vector<long> > y, const int MOD) {
    int xn = x.size(), xm = x[0].size();
    int yn = y.size(), ym = y[0].size();
    assert(xm == yn);
    vector<vector<long> > ans(xn, vector<long>(ym));
    for(int i = 0; i < xn; ++i) {
        for(int j = 0; j < ym; ++j) {
            for(int k = 0; k < xm; ++k) {
                ans[i][j] += x[i][k] * y[k][j];
                ans[i][j] %= MOD;
            }
        }
    }
    return ref(ans);
}

vector<vector<long> > doMatrixExponentiation(vector<vector<long> > a, int b, const int MOD) {
    if(b == 1) {
        return a;
    }
    vector<vector<long> > ans = doMatrixExponentiation(multiply(a, a, MOD), b/2, MOD);
    if(b & 1) {
        ans = multiply(ans, a, MOD);
    }
    return ref(ans);
}

int getNthFibonacciNumber(int n) {
    assert(n > 0);
    vector<vector<long> > base({{1, 1}, {1, 0}});
    const int MOD = 1e9 + 7;
    return doMatrixExponentiation(base, n, MOD)[1][0];
}

int main()
{
    int n;
    cin >> n;   // enter n for Nth fibonacci number

    // F(1) = 1, F(2) = 1, F(n) = F(n-1) + F(n-2) for n > 2

    cout << n << "th fibonacci number is: " << getNthFibonacciNumber(n) << endl;

    return 0;
}