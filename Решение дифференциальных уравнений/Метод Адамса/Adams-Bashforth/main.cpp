#include <iostream>

using namespace std;

typedef long double ld;
typedef double (*f)(double, double, double);

void Adams_Bashforth(int order, int n, double h, double x, double* y, f array_f[2]){
    if(order < 1 || order > 5){
        cout << "Error! Order must be integer in range [1, 5]";
        return;
    }
    double** t = new double*[3];
    for(int i = 0; i < 3; i++){
        t[i] = new double[order];
    }

    t[0][0] = y[0];
    t[1][0] = y[1];
    t[2][0] = x;

    int AB_table[6][5];
    AB_table[0][0] = 1;
    AB_table[0][1] = 2;
    AB_table[0][2] = 12;
    AB_table[0][3] = 24;
    AB_table[0][4] = 720;
    AB_table[1][0] = 1;
    AB_table[1][1] = 3;
    AB_table[1][2] = 23;
    AB_table[1][3] = 55;
    AB_table[1][4] = 1901;
    AB_table[2][1] = -1;
    AB_table[2][2] = -16;
    AB_table[2][3] = -59;
    AB_table[2][4] = -2774;
    AB_table[3][2] = 5;
    AB_table[3][3] = 37;
    AB_table[3][4] = 2616;
    AB_table[4][3] = -9;
    AB_table[4][4] = -1274;
    AB_table[5][4] = 251;

    double sum;

    for(int j = 0; j < order - 1; j++){
        for(int i = 0; i < 2; i++){
            sum = 0;
            for(int k = 0; k < j + 1; k++){
                sum += AB_table[k + 1][j] * array_f[i](x - k * h, t[0][j - k], t[1][j - k]);
            }
            sum *= h / AB_table[0][j];
            t[i][j + 1] = t[i][j] + sum;
        }
        x += h;
        t[2][j + 1] = x;

        cout << j << " " << t[2][j] << " " << t[0][j] << " " << t[1][j] << endl;
    }

    cout << order - 1 << " " << t[2][order - 1] << " " << t[0][order - 1] << " " << t[1][order - 1] << endl;

    double new_values[2];

    for(int j = order; j < n; j++){
        for(int i = 0; i < 2; i++){
            sum = 0;
            for(int k = 0; k < order; k++){
                sum += AB_table[k + 1][order - 1] * array_f[i](x - k * h, t[0][order - 1 - k], t[1][order - 1 - k]);
            }
            sum *= h / AB_table[0][order - 1];
            new_values[i] = t[i][order - 1] + sum;
        }

        for(int m = 1; m < order; m++){
            t[0][m - 1] = t[0][m];
            t[1][m - 1] = t[1][m];
        }

        t[0][order - 1] = new_values[0];
        t[1][order - 1] = new_values[1];
        x += h;
        t[2][order - 1] = x;

        cout << j << " " << x << " " << t[0][order - 1] << " " << t[1][order - 1] << endl;
    }
}

double f1(double x, double y_1, double y_2){
    return -1000 * y_1 + 999 * y_2;
}

double f2(double x, double y_1, double y_2){
    return y_1 - 2 * y_2;
}

int main()
{
    double a = 0;
    double b = 0.001;
    double h = 0.00001;

    int N = (b - a) / h + 1;
    double x = a;
    double *y = new double[2];
    y[0] = 10;
    y[1] = 20;
    f foo_m[] = {f1, f2};

    Adams_Bashforth(3, N, h, x, y, foo_m);

    return 0;
}
