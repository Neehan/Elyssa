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

double solve(string LHS, string RHS, map<string,double>knowns, string unknown, string unknown2="@")
{
    register double answer, a,b,c;
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
    register double answer, a,b,c;
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
