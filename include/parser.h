#ifndef PARSER_H
#define PARSER_H

/**
*Parser Version 2.1
*=======================
*Operator Support: + - * / ^ ()
*Variable Support: 2 unknowns and n knowns
*
*Note
*====
*I haven't included any error handling function, so calling any undefined variable or using extra
*parenthesis will result in runtime errors.
**/
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
#include "fraction.h"

using namespace std;

int match(string temp, int index);
int revmatch(string temp, int index);
int part(string temp, int index, bool direction);
int part(string temp, int index=1);
int varpart(string temp, int index);
string div_err(string terms);

class ExpTree{
public:
    void ToMemory(map<string,double> knowns, string unknown1, string unknown2="@");
    Fraction val;
    string sval;
    bool sign[2]; //isPlus and isMul
    vector<int> relative;
    int no;
};
void ExpTree::ToMemory(map<string,double> knowns, string unknown1, string unknown2){
    register int i,j,index1=0, index2=0,exp;
    string temp,term;
    double coef=1.0;
    bool sign;
    Fraction myfrac, tempfrac;
    vector<double> myvec;
    myvec.push_back(0);
    if(sval[0]!='+'&&sval[0]!='-') sval='+'+sval;
    while(!sval.empty()){
        coef=(sval[0]=='-') ? -1:1;
        index1=0;
        index2=0;
        term=sval.substr(1,part(sval,0,1)-1);
        while(!term.empty()){
            sign=(term[0]=='/') ? 0:1;
            i=part(term);
            temp=(term[0]=='/'||term[0]=='*') ? term.substr(1,i-1) : term.substr(0,i);
            j=temp.find('^');
            if(j==string::npos){
                if(sign==1){
                    if(temp==unknown1) index1++;
                    else if(temp==unknown2) index2++;
                    else if(knowns.find(temp)!=knowns.end())coef*=knowns[temp];
                    else coef*=atof(temp.c_str());
                }
                else{
                    if(temp==unknown1) index1--;
                    else if(temp==unknown2) index2--;
                    else if(knowns.find(temp)!=knowns.end())coef/=knowns[temp];
                    else coef/=atof(temp.c_str());
                }
            }
            else{
                exp=atoi(temp.substr(j+1,temp.length()-j-1).c_str());
                temp=temp.substr(0,j);
                if(sign==1){
                    if(temp==unknown1) index1+=exp;
                    else if(temp==unknown2) index2+=exp;
                    else if(knowns.find(temp)!=knowns.end()) coef*=pow(knowns[temp],exp);
                    else coef*=pow(atof(temp.c_str()),exp);
                }
                else{
                    if(temp==unknown1) index1-=exp;
                    else if(temp==unknown2) index2-=exp;
                    else if(knowns.find(temp)!=knowns.end()) coef/=pow(knowns[temp],exp);
                    else coef/=pow(atof(temp.c_str()),exp);
                }
            }
            term=term.substr(i,term.length()-i);
        }
        if(index1>-1&&index2>-1){
            tempfrac.nume.coef.clear();
            tempfrac.denom.coef.clear();
            tempfrac.denom.coef.push_back(myvec);
            tempfrac.denom.coef[0][0]=1;
            tempfrac.nume.coef.resize(index1+1,myvec);
            tempfrac.nume.coef[index1].resize(index2+1,0);
            tempfrac.nume.coef[index1][index2]=coef;
            myfrac=myfrac+tempfrac;
        }
        else if(index1>-1&&index2<0){
            index2*=-1;
            tempfrac.nume.coef.clear();
            tempfrac.denom.coef.clear();
            tempfrac.denom.coef.push_back(myvec);
            tempfrac.denom.coef[0].resize(index2+1,0.0);
            tempfrac.denom.coef[0][index2]=1;
            tempfrac.nume.coef.resize(index1+1,myvec);
            tempfrac.nume.coef[index1][0]=coef;
            myfrac=myfrac+tempfrac;
        }
        else if(index1<0&&index2>-1){
            index1*=-1;
            tempfrac.nume.coef.clear();
            tempfrac.denom.coef.clear();
            tempfrac.denom.coef.resize(index1+1,myvec);
            tempfrac.denom.coef[index1][0]=1;
            tempfrac.nume.coef.push_back(myvec);
            tempfrac.nume.coef[0].resize(index2+1,0);
            tempfrac.nume.coef[0][index2]=coef;
            myfrac=myfrac+tempfrac;
        }
        else{
            index1*=-1;
            index2*=-1;
            tempfrac.nume.coef.clear();
            tempfrac.denom.coef.clear();
            tempfrac.nume.coef.push_back(myvec);
            tempfrac.nume.coef[0][0]=coef;
            tempfrac.denom.coef.resize(index1+1,myvec);
            tempfrac.denom.coef[index1].resize(index2+1,0);
            tempfrac.denom.coef[index1][index2]=1;
            myfrac=myfrac+tempfrac;
        }
        sval=sval.substr(part(sval,0,1),sval.length()-part(sval,0,1)+1);
    }
    val=myfrac;
}

int match(string temp, int index){
    register int i=index, count1=1,count2=0;
    while(count1!=count2)
    {
        i++;
        if(temp[i]=='(') count1++;
        if(temp[i]==')') count2++;
    }
    return i;
}
int revmatch(string temp, int index){
    register int i=index, count1=0,count2=1;
    while(count1!=count2)
    {
        i--;
        if(temp[i]=='(') count1++;
        if(temp[i]==')') count2++;
    }
    return i;
}
int part(string temp, int index, bool direction){
    register int i;
    if(direction==0){
        i=index-1;
        if(i<0) return i;
        while(i>-1&&temp[i]!='+'&&temp[i]!='-')i--;
        return i;
    }
    else{
        i=index+1;
        if(i>=temp.length()) return i;
        while(i<temp.length()&&temp[i]!='+'&&temp[i]!='-'){
            if(temp[i]=='(') i=match(temp,i);
            i++;
        }
        return i;
    }
}
int part(string temp, int index){
    register int i=index;
    for(;i<temp.length();i++) if(temp[i]=='*' || temp[i]=='/') return i;
    return i;
}
int varpart(string temp, int index){
    register int i;
    i=index-1;
    if(i<0) return i;
    while(i>-1&&temp[i]!='+'&&temp[i]!='-'&&temp[i]!='*'&&temp[i]!='/'){
        if(temp[i]==')') i=revmatch(temp,i);
        i--;
    }
    return i;
}
string div_err(string terms){
    int i,j,k,l,m,counter;
    string temp;
    for(i=0;i<terms.length();i=part(terms,i,1)){
        k=i+1;
        l=part(terms,i,1);
        temp=terms.substr(k,l-k);
        string pemp1="1",pemp2="1";
        counter=0;
        j=0;
        m=(temp[j]=='(') ? match(temp,j)+1:part(temp,j+1);
        pemp1+="*"+temp.substr(j,m-j);
        for(j=m;j<temp.length();j++){
            if(temp[j]=='/'){
                m=(temp[j+1]=='(') ? match(temp,j+1)+1:part(temp,j+1);
                pemp2+="*"+temp.substr(j+1,m-j-1);
                counter++;
                j=m-1;
            }
            else if(temp[j]=='*'){
                m=(temp[j+1]=='(') ? match(temp,j+1)+1:part(temp,j+1);
                pemp1+="*"+temp.substr(j+1,m-j-1);
                j=m-1;
            }
        }
        pemp1.erase(0,2);
        pemp2.erase(0,2);
        pemp2=(counter>1)? "(+"+pemp2+")" : pemp2;
        temp=(!pemp2.empty())?pemp1+"/"+pemp2:pemp1;
        terms=terms.substr(0,k)+temp+terms.substr(l,terms.length()-l);
    }
    return terms;
}

vector<ExpTree> ToTree(string terms,map<string,double> knowns, string unknown1,string unknown2="@"){
    register int i,j,k,l;
    stack<ExpTree> container;
    vector<ExpTree> mytree;
    vector<int>::iterator myit;
    ExpTree var,var2;
    var.sval=terms;
    var.sign[0]=1;
    var.sign[1]=1;
    var.no=0;
    container.push(var);
    mytree.push_back(var);
    while(!container.empty()){
        var=container.top();
        container.pop();
        var.sval=div_err(var.sval);
        i=var.sval.find('(');
        j=(i!= string::npos) ? match(var.sval,i) : string::npos;
        if(i!= string::npos){
            k=part(var.sval,i,0);
            l=part(var.sval,j,1);
            var2.relative.clear();
            if(var.sval[k+1]=='(' && j< var.sval.length()-1){
                var2.sval=var.sval.substr(i,j-i+1);
                if(var2.sval[0]!='+' && var2.sval[0]!='-') var2.sval='+' + var2.sval;
                myit=find(var2.relative.begin(), var2.relative.end(),var.no);
                if(myit==var2.relative.end())var2.relative.push_back(var.no);
                var2.sign[0]=(var.sval[k]=='+') ? 1:0;
                var2.sign[1]=(var.sval[j+1]=='*') ? 1:0;
                mytree.push_back(var2);
                mytree[mytree.size()-1].no=mytree.size()-1;
                myit=find(mytree[var.no].relative.begin(), mytree[var.no].relative.end(),mytree.size()-1);
                if(myit==mytree[var.no].relative.end())mytree[var.no].relative.push_back(mytree.size()-1);
                container.push(mytree[mytree.size()-1]);

                var2.sval=var.sval.substr(j+2,l-j-2);
                if(var2.sval[0]!='+' && var2.sval[0]!='-') var2.sval='+' + var2.sval;
                myit=find(var2.relative.begin(), var2.relative.end(),var.no);
                if(myit==var2.relative.end())var2.relative.push_back(var.no);
                var2.sign[0]=1;
                var2.sign[1]=(var.sval[j+1]=='*') ? 1:0;
                mytree.push_back(var2);
                mytree[mytree.size()-1].no=mytree.size()-1;
                myit=find(mytree[var.no].relative.begin(), mytree[var.no].relative.end(),mytree.size()-1);
                if(myit==mytree[var.no].relative.end())mytree[var.no].relative.push_back(mytree.size()-1);
                container.push(mytree[mytree.size()-1]);
                mytree[var.no].sval=var.sval.substr(0,k)+var.sval.substr(l,var.sval.length()-l+1);
                if(mytree[var.no].sval.empty()) mytree[var.no].sval="+0";
               }
            else if(var.sval[k+1]=='(' && j==var.sval.length()-1){
                mytree[var.no].sval=var.sval.substr(2,var.sval.length()-3);
            }
            else{
                var2.sval=var.sval.substr(k,i-k-1);
                myit=find(var2.relative.begin(), var2.relative.end(),var.no);
                if(myit==var2.relative.end())var2.relative.push_back(var.no);
                var2.sign[0]=(var.sval[k]=='+') ? 1:0;
                var2.sign[1]=(var.sval[i-1]=='*') ? 1:0;
                mytree.push_back(var2);
                mytree[mytree.size()-1].no=mytree.size()-1;
                myit=find(mytree[var.no].relative.begin(), mytree[var.no].relative.end(),mytree.size()-1);
                if(myit==mytree[var.no].relative.end())mytree[var.no].relative.push_back(mytree.size()-1);
                container.push(mytree[mytree.size()-1]);

                var2.sval=var.sval.substr(i,l-i);
                if(var2.sval[0]!='+' && var2.sval[0]!='-') var2.sval='+' + var2.sval;
                myit=find(var2.relative.begin(), var2.relative.end(),var.no);
                if(myit==var2.relative.end())var2.relative.push_back(var.no);
                var2.sign[0]=1;
                var2.sign[1]=(var.sval[i-1]=='*') ? 1:0;
                mytree.push_back(var2);
                mytree[mytree.size()-1].no=mytree.size()-1;
                myit=find(mytree[var.no].relative.begin(), mytree[var.no].relative.end(),mytree.size()-1);
                if(myit==mytree[var.no].relative.end())mytree[var.no].relative.push_back(mytree.size()-1);
                container.push(mytree[mytree.size()-1]);
                mytree[var.no].sval=var.sval.substr(0,k)+var.sval.substr(l,var.sval.length()-l+1);
                if(mytree[var.no].sval=="") mytree[var.no].sval="+0";
            }
            if(mytree[var.no].sval.find('(') != string::npos) container.push(mytree[var.no]);
        }
    }
    for(i=0;i<mytree.size();i++) mytree[i].ToMemory(knowns,unknown1,unknown2);
    return mytree;
}
ExpTree ReduceNode(vector<ExpTree> mytree){
    register int i,j,parent;
    stack<ExpTree> holder;
    ExpTree var;
    i=mytree.size()-1;
    for(;i>0;i-=2){
        parent=mytree[i].relative[0];
        mytree[parent].relative.erase(find(mytree[parent].relative.begin(),mytree[parent].relative.end(),i));
        mytree[parent].relative.erase(find(mytree[parent].relative.begin(),mytree[parent].relative.end(),i-1));
        j=i-1;
        if(mytree[j].sign[0]==0&&mytree[j].sign[1]==0){
            mytree[parent].val=mytree[parent].val-mytree[j].val/mytree[i].val;
        }
        else if(mytree[j].sign[0]==0&&mytree[j].sign[1]==1){
                        mytree[parent].val=mytree[parent].val-mytree[j].val*mytree[i].val;
        }
        else if(mytree[j].sign[0]==1&&mytree[j].sign[1]==0){
            mytree[parent].val=mytree[parent].val+mytree[j].val/mytree[i].val;
        }
        else if(mytree[j].sign[0]==1&&mytree[j].sign[1]==1){
            mytree[parent].val=mytree[parent].val+mytree[j].val*mytree[i].val;
        }
        mytree.resize(i-1);
    }
    return mytree[0];
}
Fraction parse(string terms, map<string,double> knowns, string unknown1, string unknown2="@"){
    string temp,pemp="1";
    register int i=terms.find(")^"),j,k,l,m,exp;
    terms=(terms[0]=='-'||terms[0]=='+')?terms:('+'+terms);
    i=terms.find("((");
    while(i!=string::npos){
        terms=terms.substr(0,i+1)+'+'+terms.substr(i+1,terms.length()-i-1);
        i=terms.find("((");
    }

    /**No sign means multiplication :p **/

    for(i=0;i<terms.length();i++){
        if(terms[i+1]=='('&&terms[i]!='+'&&terms[i]!='-'&&terms[i]!='*'&&terms[i]!='/'){
            terms=terms.substr(0,i+1)+'*'+terms.substr(i+1,terms.length()-i);
        }
    }
    for(i=terms.length()-3;i>-1;i--){
        if(terms[i]==')'&&terms[i+1]!='+'&&terms[i+1]!='-'&&terms[i+1]!='*'&&terms[i+1]!='/'){
            if(terms[i+1]=='^'){
                j=i+2;
                while(j<terms.length()&&isdigit(terms[j]))j++;
                if(j<terms.length()&&terms[j]!='+'&&terms[j]!='-'&&terms[j]!='*'&&terms[j]!='/'){
                    terms=terms.substr(0,j)+'*'+terms.substr(j,terms.length()-j+1);
                }
            }
            else terms=terms.substr(0,i+1)+'*'+terms.substr(i+1,terms.length()-i);
        }
    }
    /**i=1;
    while(i<terms.length()){
        while(isdigit(terms[i])||terms[i]=='.') i++;
        if(i<terms.length()&&terms[i]!='^'&&terms[i]!='+'&&terms[i]!='-'&&terms[i]!='*'&&terms[i]!='/') terms=terms.substr(0,j)+'*'+terms.substr(j,terms.length()-j);
    }**/

    /**Negative Powers**/

    i=terms.find("^-");
    while(i!=string::npos){
        if(terms[i-1]==')') j=revmatch(terms,i-1)-1;
        else j=varpart(terms,i-1);
        switch(terms[j]){
        case '/':
            terms[j]='*';
            terms=terms.substr(0,i+1)+terms.substr(i+2,terms.length()-i-2);
            break;
        case '*':
            terms[j]='/';
            terms=terms.substr(0,i+1)+terms.substr(i+2,terms.length()-i-2);
            break;
        default:
            terms=terms.substr(0,j+1)+"1/"+terms.substr(j+1,i-j)+terms.substr(i+2,terms.length()-i-2);
            break;
        }
        i=terms.find("^-");
    }

    /**Resolving Bracket Power Issue**/

    i=terms.find(")^");
    while(i!=string::npos){
        j=min(part(terms,i+2),part(terms,i+2,1));
        exp=atoi(terms.substr(i+2,j-i-2).c_str());
        register int k=i, count1=0,count2=1;
        while(count1!=count2){
            k--;
            if(terms[k]=='(') count1++;
            if(terms[k]==')') count2++;
        }
        if(terms[k-1]=='/'){
            temp=terms.substr(0,i+1);
            for(l=1;l<exp;l++) temp+=("*1/"+terms.substr(k,i-k+1));
            terms=temp+terms.substr(j,terms.length()-j+1);
        }
        else{
            temp=terms.substr(0,i+1);
            for(l=1;l<exp;l++) temp+=("*"+terms.substr(k,i-k+1));
            terms=temp+terms.substr(j,terms.length()-j+1);
        }
        i=terms.find(")^");
    }
    ExpTree mytree=ReduceNode(ToTree(terms,knowns,unknown1,unknown2));
    return mytree.val;
}
#endif
