#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

// Problem to solve:
// dT/dt = -alpha(T^4 - beta) 
// T(0) = 5912
// t = 5912s

const double alpha = 2 * pow(10, -12);
const double beta = 0.;

double funT(double T){

    return -alpha*(pow(T, 4) - beta);
}

// Metoda Eulera
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
    vector<double> Ts(100000);
    vector<double> ts(100000);
    int time_total = 5912;

    Ts[0] = 5912.0;
    ts[0] = 0;

    ODE_Algorithm(Ts, ts, time_total, funT);

    cout << fixed << setprecision(3);
    cout << "Otrzymane wyniki: " << endl;
    cout << "Czas [s]\t" << "Temp [K]\t" << "Krok\n"; 

    for(int i = 0; i < ts.size(); i++)
        cout << ts[i]<< "\t" << Ts[i] << "\t\t" << i << "\n";    

    ofstream file("/Users/mateuszfaltyn/Desktop/studia/MetodyNumeryczne/RownaniaRozniczkowe/wyniki.csv");

    for(int i = 0; i < ts.size(); i++)
        file << ts[i] << ";" << Ts[i] << endl;
    
    
    return 0;
}
