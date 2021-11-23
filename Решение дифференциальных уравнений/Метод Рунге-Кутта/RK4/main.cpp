#include <iostream>
#include <cmath>

using namespace std;

typedef double (*f)(double, double, double);

void new_point(double h, double x, double* y, f array_f[2]){
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

void Runge_Kutta(double h, int N, double x, double* y, f array_f[2]){
    int i = 0;
    cout << i << " " << x << " " << y[0] << " " << y[1] << endl;
    for(i = 1; i <= N; i++){
        new_point(h, x, y, array_f);
        x += h;
        cout << i << " " << x << " " << y[0] << " " << y[1] << endl;
    }
}

double f1(double x, double y_1, double y_2){
    return y_2;
}

double f2(double x, double y_1, double y_2){
    return pow(M_E, (-x) * y_1);
}

int main()
{
    double a = 0;
    double b = 3;
    double h = 0.1;

    int N = (b - a) / h;
    double x = a;
    double *y = new double[2];
    y[0] = 0;
    y[1] = 0;
    f foo_m[] = {f1, f2};

    Runge_Kutta(h, N, x, y, foo_m);

    return 0;
}
