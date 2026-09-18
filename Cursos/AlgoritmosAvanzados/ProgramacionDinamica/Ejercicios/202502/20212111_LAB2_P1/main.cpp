#include <iomanip>
#include <iostream>
using namespace std;

const int ESTADOS = 4;
const int N=45;

void calcularVersionAgaporni(int n) {
    long long dp[ESTADOS][N + 1];
    dp[0][1] = 1; // B
    dp[1][1] = 0;
    dp[2][1] = 1; // R
    dp[3][1] = 0;
    dp[0][2] = 1; // BR
    dp[1][2] = 0;
    dp[2][2] = 1; // RB
    dp[3][2] = 0;
    dp[0][3] = 1; // BRB
    dp[1][3] = 1; // BAR
    dp[2][3] = 1; // RBR
    dp[3][3] = 1; // RAB
    if (n>=4) {
        for (int i = 4; i <= n; i++) {
            dp[0][i] = dp[2][i-1] + dp[3][i-1];
            dp[1][i] = dp[0][i-1];
            dp[2][i] = dp[0][i-1] + dp[1][i-1];
            dp[3][i] = dp[2][i-1];
        }
    }

    long long result = dp[0][n] + dp[1][n] + dp[2][n] + dp[3][n];
    cout << result << endl;
}

int main() {
    int n;
    cout << "Ingrese el valor de n (1<=n<=45):" << endl;
    cin >> n;
    if (n < 1 || n > 45) {
        cout << "No cumple la condicion" << endl;
    } else {
        //calcularVersionMichi(n);
        calcularVersionAgaporni(n);
    }
    return 0;
}
