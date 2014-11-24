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
/**double* solve( Equation eq1, Equation eq2, Equation eq3, Equation eq4,map<string,double>knowns4,map<string,double>knowns5, string v11, string v21,string v12, string v22){
    double indice[4],a,b,c;
    Fraction result1=parse(eq1.lhs,knowns4,v11,v21)-parse(eq2.lhs,knowns4,v11,v21);
    Fraction result2=parse(eq1.rhs,knowns5,v12,v22)-parse(eq2.rhs,knowns5,v12,v22);
    Fraction result;
    result1=result1.substitute(1,parse(eq3.rhs,knowns5,v12,v22));
    result1=result1.substitute(2,parse(eq4.rhs,knowns5,v12,v22));
    result1.resize();
    result1.nume.optimize();
    result2.resize();
    result2.nume.optimize();
    if(result2.nume.coef.size()==2){
        result.nume.coef[0]=result2.nume.coef[0];
        for(int i=0;i<result.nume.coef[0].size();i++) result.nume.coef[0][j]*= (-1);
        result.nume.coef[1]=result2.nume.coef[1];
        result1=result1.substitute(1,result);
        result1.resize();
        result1.nume.optimize();
        if(result1.nume.coef[0].size()==3){
            a=result1.nume.coef[0][2];
            b=result1.nume.coef[0][1];
            c=result1.nume.coef[0][0];
            if(a<0){
                a*=(-1);
                b*=(-1);
                c*=(-1);
            }
            a = (b*(-1)+sqrt(b*b-4*a*c))/(2*a);
        }
        else if(result1.nume.coef[0].size()==2){
            a=result1.nume.coef[0][1];
            b=result1.nume.coef[0][0];
            a=(-1)*b/a;
        }
        ///a is val22
        indice[3]=a;
        indice[1]=result.eval(1,a);///val12
        indice[0]=parse(eq3.rhs,knowns5,val12).eval(indice[1]);
        indice[2]=parse(eq4.rhs,knowns5,val22).eval(indice[3]);
        return indice;
    }
}
**/
