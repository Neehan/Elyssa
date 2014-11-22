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
#include "etc.cpp"
#include "fraction.cpp"
#include "parser.cpp"
#include "eqsolver.cpp"
#include "error_handler.cpp"

using namespace std;

#define PI 3.1415927

map<string,double> knowns1,knowns2,knowns3;
struct Equation{
    string lhs,rhs;
    vector<string> val;
    int prec;
};

void trig(string mystr, double nval, int no){
    string pemp=mystr.substr(0,3);
    double mval;
    if(no==1){
        if(pemp=="sin"){
            mval=asin(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns1[pemp]=mval*180/PI;
            knowns1["cos"+pemp]=cos(mval);
            knowns1["tan"+pemp]=tan(mval);
        }
        else if(pemp=="cos"){
            mval=acos(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns1[pemp]=mval*180.0/PI;
            knowns1["sin"+pemp]=sin(mval);
            knowns1["tan"+pemp]=tan(mval);
        }
        else if(pemp=="tan"){
            mval=atan(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns1[pemp]=mval*180.0/PI;
            knowns1["cos"+pemp]=cos(mval);
            knowns1["sin"+pemp]=sin(mval);
        }
    }
    else if(no==2){
        if(pemp=="sin"){
            mval=asin(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns2[pemp]=mval*180/PI;
            knowns2["cos"+pemp]=cos(mval);
            knowns2["tan"+pemp]=tan(mval);
        }
        else if(pemp=="cos"){
            mval=acos(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns2[pemp]=mval*180.0/PI;
            knowns2["sin"+pemp]=sin(mval);
            knowns2["tan"+pemp]=tan(mval);
        }
        else if(pemp=="tan"){
            mval=atan(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns2[pemp]=mval*180.0/PI;
            knowns2["cos"+pemp]=cos(mval);
            knowns2["sin"+pemp]=sin(mval);
        }
    }
    else if(no==3){
        if(pemp=="sin"){
            mval=asin(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns3[pemp]=mval*180/PI;
            knowns3["cos"+pemp]=cos(mval);
            knowns3["tan"+pemp]=tan(mval);
        }
        else if(pemp=="cos"){
            mval=acos(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns3[pemp]=mval*180.0/PI;
            knowns3["sin"+pemp]=sin(mval);
            knowns3["tan"+pemp]=tan(mval);
        }
        else if(pemp=="tan"){
            mval=atan(nval);
            pemp=mystr.substr(3,mystr.length()-3);
            knowns3[pemp]=mval*180.0/PI;
            knowns3["cos"+pemp]=cos(mval);
            knowns3["sin"+pemp]=sin(mval);
        }
    }
}

int main()
{
    xx:
    char b;
    register int i,j,temp,k=0,prec=-1;
    double nval,mval;
    ifstream fin("con_eq.txt");
    cout << "(S)ingle object\t (M)ultiple objects\n";
    cin >> b;
    if(b=='s'||b=='S'){
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
    }
    else{
        map<string,double>::iterator myit;
        string unknown="x",pemp, hmm;
        string val1,val2;
        vector<Equation> myeq;
        Equation a;
        cout << "Number of knowns (for first object)=";
        cin >> temp;
        cout << "Write them one at a line\n";
        for(i=0;i<temp;i++){
            cin >> pemp;
            cin >> hmm >> nval;
            knowns3[pemp]=nval;
            if(pemp.find("theta")!=string::npos){
                nval*=(PI/180);
                knowns3[pemp]=nval;
                knowns3["sin"+pemp]=sin(nval);
                knowns3["cos"+pemp]=cos(nval);
                knowns3["tan"+pemp]=tan(nval);
            }
            pemp.erase(pemp.length()-1);
            knowns1[pemp]=nval;
            if(pemp.find("theta")!=string::npos){
                nval*=(PI/180);
                knowns1[pemp]=nval;
                knowns1["sin"+pemp]=sin(nval);
                knowns1["cos"+pemp]=cos(nval);
                knowns1["tan"+pemp]=tan(nval);
            }
        }
        cout << "Number of knowns (for second object)=";
        cin >> temp;
        cout << "Write them one at a line\n";
        for(i=0;i<temp;i++){
            cin >> pemp;
            cin >> hmm >> nval;
            knowns3[pemp]=nval;
            if(pemp.find("theta")!=string::npos){
                nval*=(PI/180);
                knowns3[pemp]=nval;
                knowns3["sin"+pemp]=sin(nval);
                knowns3["cos"+pemp]=cos(nval);
                knowns3["tan"+pemp]=tan(nval);
            }
            pemp.erase(pemp.length()-1);
            knowns2[pemp]=nval;
            if(pemp.find("theta")!=string::npos){
                nval*=(PI/180);
                knowns2[pemp]=nval;
                knowns2["sin"+pemp]=sin(nval);
                knowns2["cos"+pemp]=cos(nval);
                knowns2["tan"+pemp]=tan(nval);
            }
        }
        vector<Equation> alge;
        cout << "Any other conditions?y/n\n";
        cin >> b;
        int NumOfCondition=0;
        if(b=='y'||b=='Y'){
            cout << "Number of conditions=";
            cin >> temp;
            NumOfCondition=temp;
            cout << "Write them one at a line\nFromat: Equation <space> variable1 <space> variable2\n";
            for(i=0;i<temp;i++){
                cin >> pemp;
                cin >> hmm >> hmm;
                a.lhs=pemp;
                a.rhs=hmm;
                cin >> pemp >> hmm;
                a.val.clear();
                a.val.push_back(pemp);
                a.val.push_back(hmm);
                alge.push_back(a);
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

        /**
m
4
d1 = 1.2
A1 = 3e-4
delta_Theta1 = 100
K1 = 385
3
l_f2 = 336000
m2 = 10e-3
/fusion2 = 0
y
1
Q1 = delta_Q2 Q1 delta_Q2
t1
        **/
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
        ifstream zin("con-eq.txt");
        while(zin >> a.lhs){
            a.val.clear();
            zin >> pemp >> a.rhs >> temp;
            for(i=0;i<temp;i++){
                zin >> pemp;
                a.val.push_back(pemp);
            }
            alge.push_back(a);
        }
        i=0;
        vector<int>dfltind;
        while(i<myeq.size()){
            int counter=0;
            dfltind.clear();
            for(j=0;j<myeq[i].val.size();j++){
                if(knowns1.find(myeq[i].val[j])==knowns1.end()){
                    counter++;
                    temp=j;
                }
            }
            j=temp;
            if(counter==1){
                nval=solve(myeq[i].lhs,myeq[i].rhs,knowns1,myeq[i].val[j]);
                myeq[i].val[j]+="1";
                knowns3[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,3);
                myeq[i].val[j].erase(myeq[i].val[j].length()-1);
                knowns1[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,1);
                i=0;
            }
            else i++;
        }
        i=0;
        while(i<myeq.size()){
            int counter=0;
            dfltind.clear();
            for(j=0;j<myeq[i].val.size();j++){
                if(knowns2.find(myeq[i].val[j])==knowns2.end()){
                    counter++;
                    temp=j;
                }
            }
            j=temp;
            if(counter==1){
                nval=solve(myeq[i].lhs,myeq[i].rhs,knowns2,myeq[i].val[j]);
                myeq[i].val[j]+="2";
                knowns3[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,3);
                myeq[i].val[j].erase(myeq[i].val[j].length()-1);
                knowns2[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,2);
                i=0;
            }
            else i++;
        }
        i=0;
        while(i<alge.size()){
            int counter=0;
            dfltind.clear();
            for(j=0;j<alge[i].val.size();j++){
                if(knowns3.find(alge[i].val[j])==knowns3.end()){
                    counter++;
                    temp=j;
                }
            }
            j=temp;
            if(counter==1){
                nval=solve(alge[i].lhs,alge[i].rhs,knowns3,alge[i].val[j]);
                knowns3[alge[i].val[j]]=nval;
                trig(alge[i].val[j],nval,3);
                i=0;
            }
            else i++;
        }
        if(NumOfCondition==1){
            i=1;
            while(i<alge.size()){
                int counter=0;
                dfltind.clear();
                for(j=0;j<alge[i].val.size();j++){
                    if(knowns3.find(alge[i].val[j])==knowns3.end()){
                        if(alge[i].val[j]==alge[0].val[0]||alge[i].val[j]==alge[0].val[1])counter++;
                    }
                }
                if(counter==2){
                    nval=solve(alge[0].lhs,alge[0].rhs,alge[i].lhs,alge[i].rhs,knowns3,alge[0].val[0], alge[0].val[1]);
                    knowns3[alge[0].val[1]]=nval;
                    trig(alge[0].val[1],nval,3);
                    pemp=alge[0].val[1];
                    nval=solve(alge[0].lhs,alge[0].rhs,knowns3,alge[0].val[0]);
                    knowns3[alge[0].val[0]]=nval;
                    trig(alge[0].val[0],nval,3);
                }
                else i++;
            }
        }
        for(myit=knowns3.begin();myit!=knowns3.end();myit++){
            pemp=myit->first;
            if(pemp[pemp.length()-1]=='1'){
                pemp.erase(pemp.length()-1);
                knowns1[pemp]=myit->second;
                trig(pemp,nval,1);
            }
            else if(pemp[pemp.length()-1]=='2'){
                pemp.erase(pemp.length()-1);
                knowns2[pemp]=myit->second;
                trig(pemp,nval,2);
            }
        }
        i=0;
        while(i<myeq.size()){
            int counter=0;
            dfltind.clear();
            for(j=0;j<myeq[i].val.size();j++){
                if(knowns1.find(myeq[i].val[j])==knowns1.end()){
                    counter++;
                    temp=j;
                }
            }
            j=temp;
            if(counter==1){
                nval=solve(myeq[i].lhs,myeq[i].rhs,knowns1,myeq[i].val[j]);
                myeq[i].val[j]+="1";
                knowns3[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,3);
                myeq[i].val[j].erase(myeq[i].val[j].length()-1);
                knowns1[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,1);
                i=0;
            }
            else i++;
        }
        i=0;
        while(i<myeq.size()){
            int counter=0;
            dfltind.clear();
            for(j=0;j<myeq[i].val.size();j++){
                if(knowns2.find(myeq[i].val[j])==knowns2.end()){
                    counter++;
                    temp=j;
                }
            }
            j=temp;
            if(counter==1){
                nval=solve(myeq[i].lhs,myeq[i].rhs,knowns2,myeq[i].val[j]);
                myeq[i].val[j]+="2";
                knowns3[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,3);
                myeq[i].val[j].erase(myeq[i].val[j].length()-1);
                knowns2[myeq[i].val[j]]=nval;
                trig(myeq[i].val[j],nval,2);
                i=0;
            }
            else i++;
        }
        if(knowns3.find(unknown)!=knowns3.end())cout << knowns3[unknown] << endl;
    }
    cout << "(N)ew\t(Q)uit\n";
    cin >> b;
    if(b=='n'||b=='N') goto xx;
    else return 0;
}
