#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;


const double alpha = 2 * pow(10, -12);
const double beta = 0.;

double funT(double T){

    return -alpha*(pow(T, 4) - beta);
}

void HeunMethod(vector<double>& Ts, vector<double>& ts, double time_total, double (*fun)(double)){
    double h = (double)(time_total)/(ts.size() - 1);
    vector<double> y(Ts.size());

    for(int i = 0; i < Ts.size() - 1; i++){
        y[i + 1] = Ts[i] + h*fun(Ts[i]);
        Ts[i + 1] = Ts[i] + h/2 * (fun(Ts[i]) + fun(y[i+1]));
    }
}

void middlePointMethod(vector<double>& Ts, vector<double>& ts, double time_total, double (*fun)(double)){
    double h = (double)(time_total)/(ts.size() - 1);

    for(int i = 0; i < Ts.size() - 1; i++)
        Ts[i + 1] = Ts[i] + h*fun(Ts[i] + (h/2.0)*fun(Ts[i]));
}

void rungeKruttyMethod(vector<double>& Ts, vector<double>& ts, double time_total, double (*fun)(double)){
    double h = (double)(time_total)/(ts.size() - 1);
    vector<double> delta_y(Ts.size());

    for(int i = 0; i < Ts.size() - 1; i++){

        double k_1 = h*fun(Ts[i]);
        double k_2 = h*fun(Ts[i] + k_1/2);
        double k_3 = h*fun(Ts[i] + k_2/2);
        double k_4 = h*fun(Ts[i] + k_3);

        delta_y[i] = (1.0/6.0)*(k_1 + 2*k_2 + 2*k_3 + k_4);
        Ts[i+1] = Ts[i] + delta_y[i];
    }
}

// Eulers Algorithm:
void ODE_Algorithm(vector<double>& Ts, vector<double>& ts, double time_total, double (*fun)(double)){ 
    double h = (double)(time_total)/(ts.size() - 1);
    int i = 0;

    while(i < ts.size() - 1){
        Ts[i + 1] = Ts[i] + h*fun(Ts[i]);
        ts[i + 1] = ts[i] + h;
        i++;
    }
}

int main()
{
   int n = 100000;
    int time_total = 5912;

    vector<double> ts(n);

    vector<double> T_euler(n);
    vector<double> T_heun(n);
    vector<double> T_mid(n);
    vector<double> T_rk4(n);

    T_euler[0] = 5912;
    T_heun[0] = 5912;
    T_mid[0] = 5912;
    T_rk4[0] = 5912;

    ts[0] = 0;

    ODE_Algorithm(T_euler, ts, time_total, funT);

    HeunMethod(T_heun, ts, time_total, funT);

    middlePointMethod(T_mid, ts, time_total, funT);

    rungeKruttyMethod(T_rk4, ts, time_total, funT);

    cout << fixed << setprecision(3);

    cout << setw(12) << "t[s]" << setw(15) << "Euler" << setw(15) << "Heun" << setw(15) << "Midpoint" << setw(15) << "RK4" << endl;   

    for(int i = 0; i < 20; i++){

        cout << setw(12) << ts[i] << setw(15) << T_euler[i] 
        << setw(15) << T_heun[i]  << setw(15) << T_mid[i] 
        << setw(15) << T_rk4[i] << endl;
    }

    ofstream file("/Users/mateuszfaltyn/Desktop/studia/MetodyNumeryczne/RownaniaRozniczkowe/RozneMetodyRozwRR/TabelaPorownawczaMetodRR.csv");

    file << "t;Euler;Heun;Midpoint;RK4\n";

    for(int i = 0; i < n; i++)
        file << ts[i] << ";" << T_euler[i] << ";" << T_heun[i] << ";" << T_mid[i] << ";" << T_rk4[i] << "\n";

    file.close();

    return 0;
}
