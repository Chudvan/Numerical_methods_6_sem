#include <iostream>
#include <cmath>

using namespace std;

typedef double (*f)(double, double, double);

void predictor(double h, double x, double* y, f array_f[2]){
    double y_[2];
    y_[0] = y[0];
    y_[1] = y[1];

    double y_dy[2];

    double** c_k;
    c_k = new double*[5];
    for(int i = 0; i < 5; i++){
        c_k[i] = new double[2];
    }
    c_k[0][0] = c_k[0][1] = 0;

    double dx;
    double P;

    for(int k = 0; k < 4; k++){
        switch(k){
        case 0:
            dx = 0;
            P = h / 6;
            break;
        case 1:
        case 2:
            dx = h / 2;
            P = h / 3;
            break;
        case 3:
            dx = h;
            P = h / 6;
            break;
        }
        y_dy[0] = y_[0] + dx * c_k[k][0];
        y_dy[1] = y_[1] + dx * c_k[k][1];

        c_k[k + 1][0] = array_f[0](x + dx, y_dy[0], y_dy[1]);
        c_k[k + 1][1] = array_f[1](x + dx, y_dy[0], y_dy[1]);

        y[0] += P * c_k[k + 1][0];
        y[1] += P * c_k[k + 1][1];
    }
}

void corrector(double h, double x, double* y, double* y_1, double* y_2, f array_f[2]) {
    y_2[0] = y[0] + h / 2 * (array_f[0](x, y[0], y[1]) + array_f[0](x + h, y_1[0], y_1[1]));
    y_2[1] = y[1] + h / 2 * (array_f[1](x, y[0], y[1]) + array_f[1](x + h, y_1[0], y_1[1]));
}

bool is_precision(double e, double* y_1, double* y_2){
    return (abs(y_1[0] - y_2[0]) < e) && (abs(y_1[1] - y_2[1]) < e);
}

void Runge_Kutta_implicit(double e, double h, int N, double x, double* y, f array_f[2]){
    int i = 0;
    cout << i << " " << x << " " << y[0] << " " << y[1] << endl;

    double y_1[2], y_2[2];
    y_1[0] = y[0];
    y_1[1] = y[1];

    for(i = 1; i <= N; i++){
        predictor(h, x, y_1, array_f);

        corrector(h, x, y, y_1, y_2, array_f);
        while(!is_precision(e, y_1, y_2)){
            y_1[0] = y_2[0];
            y_1[1] = y_2[1];
            corrector(h, x, y, y_1, y_2, array_f);
        }

        x += h;
        y[0] = y_2[0];
        y[1] = y_2[1];
        y_1[0] = y_2[0];
        y_1[1] = y_2[1];
        cout << i << " " << x << " " << y[0] << " " << y[1] << endl;
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

    int N = (b - a) / h;
    double x = a;
    double *y = new double[2];
    y[0] = 10;
    y[1] = 20;
    f foo_m[] = {f1, f2};
    double e = 0.0001;

    Runge_Kutta_implicit(e, h, N, x, y, foo_m);

    return 0;
}
