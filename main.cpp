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
#include "fraction.cpp"
#include "parser.cpp"
#include "eqsolver.cpp"

using namespace std;

#define PI 3.1415927

struct Equation{
    string lhs,rhs;
    vector<string> val;
    int prec;
};

int main()
{
    xx:
    char b;
    register int i,j,temp,k=0,prec=-1;
    double nval,mval;
    map<string,double> knowns;
    map<string,double>::iterator myit;
    string unknown="x",pemp, hmm;
    string val1,val2;
    vector<Equation> myeq;
    Equation a;
    cout << "\nNumber of knowns=";
    ifstream fin("parser.ini");
    cin >> temp;
    cout << "Write them one at a line\n";
    for(i=0;i<temp;i++){
        cin >> pemp;
        cin >> hmm >> nval;
        knowns[pemp]=nval;
        if(pemp.find("theta")!=string::npos){
            nval*=(PI/180);
            knowns[pemp]=nval;
            knowns["sin"+pemp]=sin(nval);
            knowns["cos"+pemp]=cos(nval);
            knowns["tan"+pemp]=tan(nval);

        }
    }
    cout << "What to find=";
    cin >> unknown;
    /**ifstream tin("const.txt");
    i=0;
    while(tin >> pemp){
        tin >> hmm >> nval;
        knowns[pemp]=nval;
        i++;
    }**/
    ifstream rin("eq.txt");
    while(rin >> a.lhs){
        a.val.clear();
        rin >> pemp >> a.rhs >> temp;
        for(i=0;i<temp;i++){
            rin >> pemp;
            a.val.push_back(pemp);
        }
        myeq.push_back(a);
    }
    i=0;
    vector<int>dfltind;
    while(i<myeq.size()){
        int counter=0;
        dfltind.clear();
        for(j=0;j<myeq[i].val.size();j++){
            if(knowns.find(myeq[i].val[j])==knowns.end()){
                counter++;
                temp=j;
            }
        }
        j=temp;
        if(counter==1){
            nval=solve(myeq[i].lhs,myeq[i].rhs,knowns,myeq[i].val[j]);
            knowns[myeq[i].val[j]]=nval;
            pemp=myeq[i].val[j].substr(0,3);
            //cout << myeq[i].lhs << "=" << myeq[i].rhs << " " << myeq[i].val[j] << " " << nval << endl;
            if(pemp=="sin"){
                mval=asin(nval);
                pemp=myeq[i].val[j].substr(3,myeq[i].val[j].length()-3);
                knowns[pemp]=mval*180/PI;
                knowns["cos"+pemp]=cos(mval);
                knowns["tan"+pemp]=tan(mval);
            }
            else if(pemp=="cos"){
                mval=acos(nval);
                pemp=myeq[i].val[j].substr(3,myeq[i].val[j].length()-3);
                knowns[pemp]=mval*180.0/PI;
                knowns["sin"+pemp]=sin(mval);
                knowns["tan"+pemp]=tan(mval);
            }
            else if(pemp=="tan"){
                mval=atan(nval);
                pemp=myeq[i].val[j].substr(3,myeq[i].val[j].length()-3);
                knowns[pemp]=mval*180.0/PI;
                knowns["cos"+pemp]=cos(mval);
                knowns["sin"+pemp]=sin(mval);
            }
            i=0;
        }
        else i++;
    }
    if(knowns.find(unknown)!=knowns.end())cout << knowns[unknown] << endl;
    cout << "(N)ew\t(Q)uit\n";
    cin >> b;
    if(b=='n'||b=='N') goto xx;
    else return 0;
}
