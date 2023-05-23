#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <tuple>
#include <vector>

using namespace std;


double g(vector<double> x)
{
    return exp(x[0]);
}

tuple <double,double> MCND(int N,vector <double> temp, vector <double> a, vector <double> b, double (*func)(vector <double>))
{
    // a i b to punkty początku oraz końca dla pewnego jednego wymiaru
    double V = 0;
    double S=0;
    double mult;
    for(int i = 0;i<N;i++)
    {   
        for(unsigned int j = 0; j < temp.size(); j++)
        {
            temp[j] = a[j] + (b[j] - a[j])*rand()/(RAND_MAX+1.);
        }
        S += func(temp);
        mult = 1.;
        for(unsigned int j = 0; j < temp.size(); j++)
        {
            mult *= b[j] - a[j];
        }
        V += pow(mult*func(temp),2);
    }

    for(unsigned int i = 0; i < temp.size(); i++)
    {
        S *= (b[i]-a[i]); 
    }

    return {S/N,V/(N-1.) - pow(S/N,2)*N/(N-1.)};
}

void approxMD(int N, vector <double> a, vector <double> b, tuple <double,double> (*MC)(int, vector <double>, vector <double>, vector<double>, double (*)(vector<double>)))
{
    ofstream file;
    file.open("data.dat");
    tuple <double,double> MCval;
    vector <double> temp(b.size()); 
    for(int i = 1000; i<= N; i+= 1000)
    {
        MCval = MC(i,temp,a,b,&g);
        file  << i <<" "<< get<0>(MCval) << " " << get<0>(MCval) - 2*sqrt(get<1>(MCval)/N) 
        << " " << get<0>(MCval) + 2*sqrt(get<1>(MCval)/N) << endl;
        cout << "In progress: " << i/(double)N*100 << "%" << endl;
    }

    file.close();

}

void getData(int N)
{
    vector <double> a = {4};
    vector <double> b = {5};
    vector <double> temp(b.size());
    tuple<double,double> MC = MCND(N,temp,a,b,&g);
    cout << "Ilość losowań: " << N <<" | Wartość całki: "<< get<0>(MC) << " | błąd dolny:  " << get<0>(MC) - 2*sqrt(get<1>(MC)/N) 
        << " | błąd górny: " << get<0>(MC) + 2*sqrt(get<1>(MC)/N) << endl;
}

int main()
{
    srand(time(NULL));

    // approxMD(1e6,a,b,&MCND);

    getData(1e6);
   

    return 0;
}

// calka wielowymiarowa z wariancją i przedziałem ufności