#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

class TwinFraction{
public:
    vector<double> nume, denom;
};
class Expression{
public:
    vector<double> coef;
    //Expression();
    //double eval(double x);
    void show(string unknown);
    string ToString();
    Expression operator+(Expression obj2);
    Expression operator-(Expression obj2);
    Expression operator*(Expression obj2);
    Expression operator=(Expression obj2);
    TwinFraction operator/(Expression obj2);
};
void Expression::show(string unknown){
    register int i=coef.size()-1;
    if(coef.size()==0) cout << "0";
    for(;i>-1;i--)
    {
        if(coef[i]>0 && coef[i] != 1 && i>1) cout << "+" << coef[i] << unknown << "^" << i << " ";
        else if(coef[i]>0 && coef[i] == 1 && i>1) cout << "+" << unknown << "^" << i << " ";
        else if(coef[i]>0 && coef[i] != 1 && i==1) cout << "+" << coef[i] << unknown << " ";
        else if(coef[i]>0 && coef[i] != 1 && i==0) cout << "+" << coef[i];
        else if(coef[i]>0 && coef[i] == 1 && i==1) cout << "+" <<  unknown << " ";
        else if(coef[i]>0 && coef[i] == 1 && i==0) cout << "+" << "1";
        else if(coef[i]<0 && coef[i] != -1 && i>1) cout << coef[i] << unknown <<"^" << i << " ";
        else if(coef[i]<0 && coef[i] == -1 && i>1) cout << "-" <<  unknown << "^" << i << " ";
        else if(coef[i]<0 && coef[i] != -1 && i==1) cout << coef[i] <<  unknown << " ";
        else if(coef[i]<0 && coef[i] != -1 && i==0) cout << coef[i];
        else if(coef[i]<0 && coef[i] == -1 && i==1) cout << "-" << unknown << " ";
        else if(coef[i]<0 && coef[i] == -1 && i==0) cout << "-1";
    }
}
string Expression::ToString(){
    register int i=coef.size()-1;
    string mystring;
    if(coef.size()==0) mystring="0";
    for(;i>-1;i--)
    {
        stringstream num;
        num << coef[i];
        string a=num.str();
        num << i;
        string b=num.str();
        if(coef[i]>0 && coef[i] != 1 && i>1) mystring+="+"+a+"x^"+b;
        else if(coef[i]>0 && coef[i] == 1 && i>1) mystring+="+x^"+b;
        else if(coef[i]>0 && coef[i] != 1 && i==1) mystring+="+"+a+"x";
        else if(coef[i]>0 && coef[i] != 1 && i==0) mystring+="+"+a;
        else if(coef[i]>0 && coef[i] == 1 && i==1) mystring+="+x";
        else if(coef[i]>0 && coef[i] == 1 && i==0) mystring+="+1";
        else if(coef[i]<0 && coef[i] != -1 && i>1) mystring+=a+"x^"+b;
        else if(coef[i]<0 && coef[i] == -1 && i>1) mystring+="-x^"+b;
        else if(coef[i]<0 && coef[i] != -1 && i==1) mystring+=a+"x";
        else if(coef[i]<0 && coef[i] != -1 && i==0) mystring+=a;
        else if(coef[i]<0 && coef[i] == -1 && i==1) mystring+="-x";
        else if(coef[i]<0 && coef[i] == -1 && i==0) mystring+="-1";
    }
    return mystring;
}
Expression Expression::operator+(Expression obj2){
    Expression result;
    register int i=0;
    if(coef.size()>obj2.coef.size())
    {
        result.coef.resize(coef.size(),0.0);
        for(;i<obj2.coef.size();i++) result.coef[i]=coef[i]+obj2.coef[i];
        for(;i<coef.size();i++) result.coef[i]=coef[i];
    }
    else
    {
        result.coef.resize(obj2.coef.size(),0.0);
        for(;i<coef.size();i++) result.coef[i]=coef[i]+obj2.coef[i];
        for(;i<obj2.coef.size();i++) result.coef[i]=obj2.coef[i];
    }
    i=result.coef.size();
    while(result.coef[i-1]==0.0) i--;
    result.coef.resize(i);
    return result;
}
Expression Expression::operator-(Expression obj2){
    Expression temp;
    temp.coef.push_back(-1.0);
    temp=temp*obj2;
    temp=*this+temp;
    return temp;
}
Expression Expression::operator*(Expression obj2){
    Expression result;
    register int i=0,j;
    result.coef.resize(coef.size()+obj2.coef.size()-1,0.0);
    for(i=0;i<coef.size();i++) for(j=0;j<obj2.coef.size();j++) result.coef[i+j]+=coef[i]*obj2.coef[j];
    return result;
}
Expression Expression::operator=(Expression obj2){
    coef=obj2.coef;
    return *this;
}
TwinFraction Expression::operator/(Expression obj2){
    TwinFraction temp;
    temp.nume=coef;
    temp.denom=obj2.coef;
    return temp;
}

class Fraction{
public:
    Expression nume,denom;
    Fraction();
    void resize();
    Fraction operator+(Fraction obj2);
    Fraction operator-(Fraction obj2);
    Fraction operator*(Fraction obj2);
    Fraction operator/(Fraction obj2);
    Fraction operator=(Fraction obj2);
    Fraction operator=(TwinFraction obj2);
};
Fraction::Fraction(){
    nume.coef.push_back(0);
    denom.coef.push_back(1.0);
}
void Fraction::resize(){
    register int i=nume.coef.size()-1;
    while(nume.coef[i]==0)i--;
    nume.coef.resize(i+1);
    i=denom.coef.size()-1;
    while(denom.coef[i]==0)i--;
    denom.coef.resize(i+1);
}
Fraction Fraction::operator+(Fraction obj2){
    Fraction temp;
    temp.nume=nume*obj2.denom+denom*obj2.nume;
    temp.denom=denom*obj2.denom;
    return temp;
}
Fraction Fraction::operator-(Fraction obj2){
    Fraction temp;
    temp.nume=nume*obj2.denom-denom*obj2.nume;
    temp.denom=denom*obj2.denom;
    return temp;
}
Fraction Fraction::operator*(Fraction obj2){
    Fraction temp;
    temp.nume=nume*obj2.nume;
    temp.denom=denom*obj2.denom;
    return temp;
}
Fraction Fraction::operator/(Fraction obj2){
    Fraction temp;
    temp.nume=nume*obj2.denom;
    temp.denom=denom*obj2.nume;
    if (temp.denom.coef.size()==1){
        for(int i=0;i<temp.nume.coef.size();i++) temp.nume.coef[i]/=temp.denom.coef[0];
        temp.denom.coef[0]=1;
    }
    return temp;
}
Fraction Fraction::operator=(Fraction obj2){
    Fraction temp;
    nume=obj2.nume;
    denom=obj2.denom;
    return *this;
}
Fraction Fraction::operator=(TwinFraction obj2){
    Fraction temp;
    nume.coef=obj2.nume;
    denom.coef=obj2.denom;
    return *this;
}
