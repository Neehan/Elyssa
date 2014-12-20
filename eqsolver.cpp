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

struct Equation{
    string lhs,rhs;
    vector<string> val;
    int prec;
};

double solve(string LHS, string RHS, map<string,double>knowns, string unknown, string unknown2="@")
{
    register double a,b,c;
    Fraction lhs=parse(LHS,knowns,unknown,"@"),rhs=parse(RHS,knowns,unknown,"@");
    Fraction result=lhs-rhs;
    result.resize();
    if(result.nume.coef.size()==3){
        a=result.nume.coef[2][0];
        b=result.nume.coef[1][0];
        c=result.nume.coef[0][0];
        if(a<0){
            a*=(-1);
            b*=(-1);
            c*=(-1);
        }
        return (b*(-1)+sqrt(b*b-4*a*c))/(2*a);
    }
    else if(result.nume.coef.size()==2){
        a=result.nume.coef[1][0];
        b=result.nume.coef[0][0];
        return (-1)*b/a;
    }
}
double solve(string LHS1, string RHS1, string LHS2, string RHS2, map<string,double>knowns, string unknown1, string unknown2){///Output  unknown2's value
    register double a,b,c;
    Fraction rhs1=parse(RHS1,knowns,unknown1,unknown2),lhs2=parse(LHS2,knowns,unknown1,unknown2),rhs2=parse(RHS2,knowns,unknown1,unknown2);
    Fraction result=lhs2-rhs2;
    result=result.substitute(1,rhs1);
    result.resize();
    result.nume.optimize();
    if(result.nume.coef[0].size()==3){
        a=result.nume.coef[0][2];
        b=result.nume.coef[0][1];
        c=result.nume.coef[0][0];
        if(a<0){
            a*=(-1);
            b*=(-1);
            c*=(-1);
        }
        return (b*(-1)+sqrt(b*b-4*a*c))/(2*a);
    }
    else if(result.nume.coef[0].size()==2){
        a=result.nume.coef[0][1];
        b=result.nume.coef[0][0];
        return (-1)*b/a;
    }
}

vector<double> SOLVE( Equation eq1, Equation eq2, Equation eq3, Equation eq4,map<string,double>knowns4,map<string,double>knowns5, string v11, string v12,string v21, string v22){
    vector<double> indice(4,0); ///11 12 21 22
    double a=1,b,c;
    Fraction result1=parse(eq1.lhs,knowns4,v11,v12)-parse(eq1.rhs,knowns4,v11,v12);
    Fraction result2=parse(eq2.lhs,knowns5,v21,v22)-parse(eq2.rhs,knowns5,v21,v22);
    result2=result2.substitute(1,parse(eq3.rhs,knowns4,v11));
    Fraction result;
    result2=result2.substitute(2,parse(eq4.rhs,knowns4,"@",v12));

    result1.resize();
    //result1.nume.optimize();
    result2.resize();
    //result2.nume.optimize();

    if(result1.nume.coef.size()==2){

        Fraction temp;
        temp.nume.coef[0]=result1.nume.coef[0];

        for(int i=0;i<temp.nume.coef[0].size();i++) temp.nume.coef[0][i]*= (-1);
        temp.denom.coef[0]=result1.nume.coef[1];

        result=result2.substitute(1,temp);
        result.resize();
        //result.optimize();
        if(result.nume.coef[0].size()==3){
            a=result.nume.coef[0][2];
            b=result.nume.coef[0][1];
            c=result.nume.coef[0][0];
            if(a<0){
                a*=(-1);
                b*=(-1);
                c*=(-1);
            }
            indice[1]= (b*(-1)+sqrt(b*b-4*a*c))/(2*a);
        }
        else if(result.nume.coef[0].size()==2){
            a=result.nume.coef[0][1];
            b=result.nume.coef[0][0];
            indice[1]= (-1)*b/a;
        }

        indice[0]=temp.eval(1,indice[1]);
        indice[2]=parse(eq3.rhs,knowns4,v11).eval(indice[0],1);
        indice[3]=parse(eq4.rhs,knowns4,v12).eval(indice[1],1);
    }
    return indice;
}
