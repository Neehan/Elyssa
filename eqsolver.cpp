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

double solve(string LHS, string RHS, map<string,double>knowns, string unknown)
{
    register double answer, a,b,c;
    Fraction lhs=parse(LHS,knowns,unknown),rhs=parse(RHS,knowns,unknown);
    Fraction result=lhs-rhs;
    result.resize();
    if(result.nume.coef.size()==3){
        a=result.nume.coef[2];
        b=result.nume.coef[1];
        c=result.nume.coef[0];
        if(a<0){
            a*=(-1);
            b*=(-1);
            c*=(-1);
        }
        return (b*(-1)+sqrt(b*b-4*a*c))/(2*a);
    }
    else if(result.nume.coef.size()==2){
        a=result.nume.coef[1];
        b=result.nume.coef[0];
        return (-1)*b/a;
    }
}
