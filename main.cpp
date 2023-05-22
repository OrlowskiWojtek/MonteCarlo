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
    double arg = 0;
    // funkcja k argumentów x
   
    for(auto &i : x)
    {
        arg += i;
    }
    return sin(arg);
}

tuple <double,double> MCND(int N, vector <double> a, vector <double> b, double (*func)(vector <double>))
{
    // a i b to punkty początku oraz końca dla pewnego jednego wymiaru
    double V = 0;
    double S=0;
    double mult;
    vector <double> temp(b.size()); 
    vector <double> xiVec(b.size());
    for(int i = 0;i<N;i++)
    {   
        for(unsigned int j = 0; j < temp.size(); j++)
        {
            temp[j] = a[j] + (b[j] - a[j])*rand()/(RAND_MAX+1.);
        }
        S += func(temp);
        mult = 1;
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

    return {S/N,(V)/(N-1.) - pow(S,2)/(N*(N-1.))};
}

int main()
{
    srand(time(NULL));

    // niech to będzie funkcja 5 zmiennych od 0 do 1

    vector <double> a = {0,0,0};
    vector <double> b = {1,1,1};

    tuple <double,double> MCval = MCND(1e6,a,b,&g);

    cout << get<0>(MCval) << " " << get<1>(MCval)<< endl;


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

    return 0;
}

// teraz analiza monte Carlo 1D 
// calka wielowymiarowa z wariancją i przedziałem ufności