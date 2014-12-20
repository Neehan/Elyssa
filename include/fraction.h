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

bool CompareDoubles (double A, double B);

class Expression{
public:
    vector<vector<double> > coef;
    //Expression();
    double eval(double x,double y=1);
    void show(string unknown1, string unknown2="@");
    Expression optimize();
    Expression operator+(Expression obj2);
    Expression operator-(Expression obj2);
    Expression operator*(Expression obj2);
    Expression operator=(Expression obj2);
};
double Expression::eval(double x, double y){
    double val=0;
    for(int i=0;i<coef.size();i++)for(int j=0;j<coef[i].size();j++){
        val+=coef[i][j]*pow(x,i)*pow(y,j);
    }
    return val;
}
void Expression::show(string unknown1,string unknown2){
    register int j,i=coef.size()-1;
    cout << endl;
    if(coef.size()==0) cout << "0";
    for(;i>-1;i--){
        for(j=coef[i].size()-1;j>-1;j--){
        if(coef[i][j]>0 && coef[i][j] != 1 && i>1 && j>1) cout << "+" << coef[i][j] << unknown1 << "^" << i << unknown2 << "^" << j <<" ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i>1 && j==1) cout << "+" << coef[i][j] << unknown1 << "^" << i << unknown2 <<" ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i>1 && j==0) cout << "+" << coef[i][j] << unknown1 << "^" << i <<" ";
        else if(coef[i][j]>0 && coef[i][j] == 1 && i>1 && j>1) cout << "+" << unknown1 << "^" << i << unknown2 << "^" << j << " ";
        else if(coef[i][j]>0 && coef[i][j] == 1 && i>1 && j==1) cout << "+" << unknown1 << "^" << i << unknown2 << " ";
        else if(coef[i][j]>0 && coef[i][j] == 1 && i>1 && j==0) cout << "+" << unknown1 << "^" << i << " ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i==1 && j>1) cout << "+" << coef[i][j] << unknown1 << unknown2 << "^" << j << " ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i==1 && j==1) cout << "+" << coef[i][j] << unknown1 << unknown2 << " ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i==1 && j==0) cout << "+" << coef[i][j] << unknown1 << " ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i==0 && j>1) cout << "+" << coef[i][j] << unknown2 << "^" << j << " ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i==0 && j==1) cout << "+" << coef[i][j] << unknown2 << " ";
        else if(coef[i][j]>0 && coef[i][j] != 1 && i==0 && j==0) cout << "+" << coef[i][j];
        else if(coef[i][j]>0 && coef[i][j] == 1 && i==1 && j>1) cout << "+" <<  unknown1 << unknown2 << "^" << j << " ";
        else if(coef[i][j]>0 && coef[i][j] == 1 && i==1 && j==1) cout << "+" <<  unknown1 << unknown2 << " ";
        else if(coef[i][j]>0 && coef[i][j] == 1 && i==1 && j==0) cout << "+" <<  unknown1 << " ";
        else if(coef[i][j]>0 && coef[i][j] == 1 && i==0 && j>1) cout << "+" << unknown2 << "^" << j << " " ;
        else if(coef[i][j]>0 && coef[i][j] == 1 && i==0 && j==1) cout << "+" << unknown2 << " ";
        else if(coef[i][j]>0 && coef[i][j] == 1 && i==0 && j==0) cout << "+" << "1";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i>1 && j>1) cout << coef[i][j] << unknown1 <<"^" << i << unknown2 << "^" << j << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i>1 && j==1) cout << coef[i][j] << unknown1 <<"^" << i << unknown2 << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i>1 && j==0) cout << coef[i][j] << unknown1 <<"^" << i << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i>1 && j>1) cout << "-" <<  unknown1 << "^" << i << unknown2 << "^" << j << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i>1 && j==1) cout << "-" <<  unknown1 << "^" << i << unknown2 << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i>1 && j==0) cout << "-" <<  unknown1 << "^" << i << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i==1 && j>1) cout << coef[i][j] <<  unknown1 << unknown2 << "^" << j << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i==1 && j==1) cout << coef[i][j] <<  unknown1 << unknown2 << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i==1 && j==0) cout << coef[i][j] <<  unknown1 << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i==0 && j>1) cout << coef[i][j] << unknown2 << "^" << j << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i==0 && j==1) cout << coef[i][j] << unknown2 << " ";
        else if(coef[i][j]<0 && coef[i][j] != -1 && i==0 && j==0) cout << coef[i][j];
        else if(coef[i][j]<0 && coef[i][j] == -1 && i==1 && j>1) cout << "-" << unknown1 << unknown2 << "^" << j << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i==1 && j==1) cout << "-" << unknown1 << unknown2 << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i==1 && j==0) cout << "-" << unknown1 << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i==0 && j>1) cout << "-" << unknown2 << "^" << j << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i==0 && j==1) cout << "-" << unknown2 << " ";
        else if(coef[i][j]<0 && coef[i][j] == -1 && i==0 && j==0) cout << "-1";
        }
    }
    cout << endl;
}
Expression Expression::optimize(){
    int i,j,counter=0;
    while(CompareDoubles(coef[0][0],0)){
        counter=0;
        for(i=0;i<coef.size();i++) if(CompareDoubles(coef[i][0],0)) counter++;
        if(counter==coef.size()) for(i=0;i<coef.size();i++) if(coef[i].size()>1)coef[i].erase(coef[i].begin());
    }
    while(coef[0].size()==1&&CompareDoubles(coef[0][0],0)){/**Careful Boy, if your Fraction::resize() function is faulty, the whole thing is gonna crash.**/
        coef.erase(coef.begin());
    }
    return *this;
}
Expression Expression::operator+(Expression obj2){
    Expression result;
    vector<double> myveq;
    myveq.push_back(0.0);
    register int i=0,j;
    if(coef.size()>obj2.coef.size()){
        result.coef.resize(coef.size(),myveq);
        for(;i<obj2.coef.size();i++){
            if(coef[i].size()>obj2.coef[i].size()){
                result.coef[i].resize(coef[i].size(),0.0);
                for(j=0;j<obj2.coef[i].size();j++) result.coef[i][j]=coef[i][j]+obj2.coef[i][j];
                for(;j<coef[i].size();j++) result.coef[i][j]=coef[i][j];
            }
            else{
                result.coef[i].resize(obj2.coef[i].size(),0.0);
                for(j=0;j<coef[i].size();j++) result.coef[i][j]=coef[i][j]+obj2.coef[i][j];
                for(;j<obj2.coef[i].size();j++) result.coef[i][j]=obj2.coef[i][j];
            }
        }
        for(;i<coef.size();i++) result.coef[i]=coef[i];
    }
    else{
        result.coef.resize(obj2.coef.size(),myveq);
        for(;i<coef.size();i++){
            if(coef[i].size()>obj2.coef[i].size()){
                result.coef[i].resize(coef[i].size(),0.0);
                for(j=0;j<obj2.coef[i].size();j++) result.coef[i][j]=coef[i][j]+obj2.coef[i][j];
                for(;j<coef[i].size();j++) result.coef[i][j]=coef[i][j];
            }
            else{
                result.coef[i].resize(obj2.coef[i].size(),0.0);
                for(j=0;j<coef[i].size();j++) result.coef[i][j]=coef[i][j]+obj2.coef[i][j];
                for(;j<obj2.coef[i].size();j++) result.coef[i][j]=obj2.coef[i][j];
            }
        }
        for(;i<obj2.coef.size();i++) result.coef[i]=obj2.coef[i];
    }
    for(i=result.coef.size()-1;i>-1;i--){
        j=result.coef[i].size();
        while(CompareDoubles(result.coef[i][j-1],0)&&j>0)j--;
        result.coef[i].resize(j);
    }
    i=result.coef.size();
    while(i>0&&result.coef[i-1].empty()) i--;
    result.coef.resize(i);
    return result;
}
Expression Expression::operator-(Expression obj2){
    Expression temp;
    vector<double> myvec;
    myvec.push_back(-1.0);
    temp.coef.push_back(myvec);
    return (*this+temp*obj2);
}
Expression Expression::operator*(Expression obj2){
    Expression result;
    register int i,j,k,l,m;
    vector<double> myvec;
    myvec.push_back(0);
    result.coef.resize(coef.size()+obj2.coef.size()-1,myvec);
    for(i=0;i<coef.size();i++) {
        for(j=0;j<obj2.coef.size();j++){
            m=max(coef[i].size()+obj2.coef[j].size()-1,result.coef[i+j].size());
            result.coef[i+j].resize(m,0.0);
            for(k=0;k<coef[i].size();k++) for(l=0;l<obj2.coef[j].size();l++)result.coef[i+j][k+l]+=coef[i][k]*obj2.coef[j][l];
        }
    }
    return result;
}
Expression Expression::operator=(Expression obj2){
    coef=obj2.coef;
    return *this;
}

class Fraction{
public:
    Expression nume,denom;
    Fraction();
    double eval(double x,double y=1);
    void resize();
    Fraction substitute(int varno, Fraction obj2);//coef is [x][y] and this is for x
    Fraction operator+(Fraction obj2);
    Fraction operator-(Fraction obj2);
    Fraction operator*(Fraction obj2);
    Fraction operator/(Fraction obj2);
    Fraction operator=(Fraction obj2);
    Fraction operator^(int n);
};
Fraction::Fraction(){
    vector<double>myvec;
    myvec.push_back(0);
    nume.coef.push_back(myvec);
    myvec[0]=1;
    denom.coef.push_back(myvec);
}
double Fraction::eval(double x,double y){
    return (nume.eval(x,y)/denom.eval(x,y));
}
Fraction Fraction::substitute(int varno, Fraction obj2){
    Fraction temp,result1,result2;
    vector<double>myvec;
    myvec.push_back(1);
    if(varno==1){
        for(register int i=0; i<nume.coef.size();i++)for(register int j=0; j<nume.coef[i].size();j++){
            temp.nume.coef.clear();
            temp.denom.coef.clear();
            temp.nume.coef.push_back(myvec);
            temp.nume.coef[0].resize(j+1,0);
            temp.nume.coef[0][0]=0;
            temp.nume.coef[0][j]=nume.coef[i][j];
            temp.denom.coef.push_back(myvec);
            result1=result1+temp*(obj2^i);
        }
        for(register int i=0; i<denom.coef.size();i++)for(register int j=0; j<denom.coef[i].size();j++){
            temp.nume.coef.clear();
            temp.denom.coef.clear();
            temp.nume.coef.push_back(myvec);
            temp.nume.coef[0].resize(j+1,0);
            temp.nume.coef[0][0]=0;
            temp.nume.coef[0][j]=denom.coef[i][j];
            temp.denom.coef.push_back(myvec);
            result2=result2+temp*(obj2^i);
        }
    }
    else{
        for(register int i=0; i<nume.coef.size();i++)for(register int j=0; j<nume.coef[i].size();j++){
            temp.nume.coef.clear();
            temp.denom.coef.clear();
            myvec[0]=0;
            temp.nume.coef.resize(i+1,myvec);
            temp.nume.coef[i][0]=nume.coef[i][j];
            myvec[0]=1;
            temp.denom.coef.push_back(myvec);
            result1=result1+temp*(obj2^j);
        }
        for(register int i=0; i<denom.coef.size();i++)for(register int j=0; j<denom.coef[i].size();j++){
            temp.nume.coef.clear();
            temp.denom.coef.clear();
            myvec[0]=0;
            temp.nume.coef.resize(i+1,myvec);
            temp.nume.coef[i][0]=denom.coef[i][j];
            myvec[0]=1;
            temp.denom.coef.push_back(myvec);
            result2=result2+temp*(obj2^j);
        }
    }
    return(result1/result2);
}
void Fraction::resize(){
    register int i=nume.coef.size()-1,j;
    for(;i>-1;i--){
        j=nume.coef[i].size()-1;
        while(j>-1&&CompareDoubles(nume.coef[i][j],0)) j--;
        nume.coef[i].resize(j+1);
    }
    i=nume.coef.size()-1;
    while(nume.coef[i].empty())i--;
    nume.coef.resize(i+1);
    i=denom.coef.size()-1;
    for(;i>-1;i--){
        j=denom.coef[i].size()-1;
        while(j>-1&&CompareDoubles(denom.coef[i][j],0)) j--;
        denom.coef[i].resize(j+1);
    }
    i=denom.coef.size()-1;
    while(denom.coef[i].empty())i--;
    denom.coef.resize(i+1);
    for(i=0;i<nume.coef.size();i++)if(nume.coef[i].size()==0)nume.coef[i].push_back(0);
    for(i=0;i<denom.coef.size();i++)if(denom.coef[i].size()==0)denom.coef[i].push_back(0);
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
Fraction Fraction::operator^(int n){
    Fraction temp;
    int i=0;
    temp.nume.coef[0][0]=1;
    for(;i<n;i++)temp=temp*(*this);
    return temp;
}
Fraction Fraction::operator/(Fraction obj2){
    Fraction temp;
    temp.nume=nume*obj2.denom;
    temp.denom=denom*obj2.nume;
    if (temp.denom.coef.size()==1&&temp.denom.coef[0].size()==1){
        for(int i=0;i<temp.nume.coef.size();i++)for(int j=0;j<temp.nume.coef[i].size();j++) temp.nume.coef[i][j]/=temp.denom.coef[0][0];
        temp.denom.coef[0][0]=1;
    }
    return temp;
}
Fraction Fraction::operator=(Fraction obj2){
    Fraction temp;
    nume=obj2.nume;
    denom=obj2.denom;
    return *this;
}
