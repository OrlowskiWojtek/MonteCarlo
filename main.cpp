#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <tuple>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

// aproksymacja całki gausowskiej od 0 do 1

double g(vector<double> x)
{
    return (x[0]+3)*(x[1]+1)*(x[2]+2);
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

int main()
{
    srand(time(NULL));

    // niech to będzie funkcja 5 zmiennych od 0 do 1

    vector <double> a = {0,0,0};
    vector <double> b = {3,2,1};
    vector <double> temp(b.size());


    // approxMD(1e6,a,b,&MCND);

    cout << get<0>(MCND(1e6,temp,a,b,&g))<< endl;

    /*

    ifstream ifile;
    string filename = "data";

    for(int i = 1; i<=3; i++)
    {
        ifile.open("data"+to_string(i)+".dat");
        if(ifile)
        {
            ifile.close();
            string command ="rm data"+to_string(i)+".dat"; 
            char *cstr = new char[command.length() + 1];
            strcpy(cstr, command.c_str());
            system(cstr);
            delete[] cstr;
            cout << "deleted: data"+to_string(i)+".dat" << endl;  
        }
    }
    
    */

    return 0;
}

// teraz analiza monte Carlo 1D 
// calka wielowymiarowa z wariancją i przedziałem ufności