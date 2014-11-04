/**
*Parser Version 1.0 beta
*=======================
*Operator Support: + - * / ^ ()
*Variable Support: 1 unknown and n knowns
*
*Note
*====
*I haven't included any error handling function, so calling any undefined variable or using extra parenthesis will result to runtime
*errors.
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

using namespace std;

int part(string temp, int index, bool direction);
int part(string temp, int index=1);

class TwinFraction{
public:
    vector<double> nume, denom;
};
class Expression{
public:
    vector<double> coef;
    //Expression();
    //double eval(double x);
    void show();
    string ToString();
    Expression operator+(Expression obj2);
    Expression operator-(Expression obj2);
    Expression operator*(Expression obj2);
    Expression operator=(Expression obj2);
    TwinFraction operator/(Expression obj2);
};
void Expression::show(){
    register int i=coef.size()-1;
    if(coef.size()==0) cout << "0";
    for(;i>-1;i--)
    {
        if(coef[i]>0 && coef[i] != 1 && i>1) cout << "+" << coef[i] << "x^" << i << " ";
        else if(coef[i]>0 && coef[i] == 1 && i>1) cout << "+" << "x^" << i << " ";
        else if(coef[i]>0 && coef[i] != 1 && i==1) cout << "+" << coef[i] << "x" << " ";
        else if(coef[i]>0 && coef[i] != 1 && i==0) cout << "+" << coef[i];
        else if(coef[i]>0 && coef[i] == 1 && i==1) cout << "+" << "x" << " ";
        else if(coef[i]>0 && coef[i] == 1 && i==0) cout << "+" << "1";
        else if(coef[i]<0 && coef[i] != -1 && i>1) cout << coef[i] << "x^" << i << " ";
        else if(coef[i]<0 && coef[i] == -1 && i>1) cout << "-x^" << i << " ";
        else if(coef[i]<0 && coef[i] != -1 && i==1) cout << coef[i] << "x" << " ";
        else if(coef[i]<0 && coef[i] != -1 && i==0) cout << coef[i];
        else if(coef[i]<0 && coef[i] == -1 && i==1) cout << "-x" << " ";
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
    register int i=0,j;
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

class ExpTree{
public:
    void ToMemory(map<string,double> knowns, string unknown);
    Fraction val;
    string sval;
    bool sign[2]; //isPlus and isMul
    vector<int> relative;
    int no;//x*(x+2)
};
void ExpTree::ToMemory(map<string,double> knowns, string unknown){
    register int i,j,index=0,exp;
    string temp,term;
    double coef=1.0;
    bool sign;
    map<int,double> mymap;
    map<int,double>::iterator thisit;
    if(sval[0]!='+'&&sval[0]!='-') sval='+'+sval;
    while(!sval.empty()){
        coef=(sval[0]=='-') ? -1:1;
        index=0;
        term=sval.substr(1,part(sval,0,1)-1);
        while(!term.empty()){
            sign=(term[0]=='/') ? 0:1;
            i=part(term);
            temp=(term[0]=='/'||term[0]=='*') ? term.substr(1,i-1) : term.substr(0,i);
            j=temp.find('^');
            if(j==string::npos){
                if(sign==1){
                    if(temp==unknown) index++;
                    else if(knowns.find(temp)!=knowns.end())coef*=knowns[temp];
                    else coef*=atof(temp.c_str());
                }
                else{
                    if(temp==unknown) index--;
                    else if(knowns.find(temp)!=knowns.end())coef/=knowns[temp];
                    else coef/=atof(temp.c_str());
                }
            }
            else{
                exp=atoi(temp.substr(j+1,temp.length()-j-1).c_str());
                temp=temp.substr(0,j);
                if(sign==1){
                    if(temp==unknown) index+=exp;
                    else if(knowns.find(temp)!=knowns.end()) coef*=pow(knowns[temp],exp);
                    else coef*=pow(atof(temp.c_str()),exp);
                }
                else{
                    if(temp==unknown) index-=exp;
                    else if(knowns.find(temp)!=knowns.end()) coef*=pow(knowns[temp],exp);
                    else coef*=pow(atof(temp.c_str()),exp);
                }
            }
            term=term.substr(i,term.length()-i);
        }
        mymap[index]+=coef;
        sval=sval.substr(part(sval,0,1),sval.length()-part(sval,0,1)+1);
    }
    index=mymap.begin()->first;
    if(index >-1){
        index=mymap.rbegin()->first;
        val.nume.coef.resize(index+1,0);
        for(thisit=mymap.begin();thisit!=mymap.end();thisit++)val.nume.coef[thisit->first]+=thisit->second;
    }
    else{
        index*=(-1);
        val.nume.coef.resize((mymap.rbegin()->first)+index+1,0);
        val.denom.coef[0]=0;
        val.denom.coef.resize(index+1,0);
        val.denom.coef[val.denom.coef.size()-1]=1;
        for(thisit=mymap.begin();thisit!=mymap.end();thisit++)val.nume.coef[(thisit->first)+index]+=(thisit->second);
    }
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
vector<ExpTree> ToTree(string terms,map<string,double> knowns, string unknown){
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
    for(i=0;i<mytree.size();i++) mytree[i].ToMemory(knowns,unknown);
    return mytree;
}
ExpTree ReduceNode(vector<ExpTree> mytree){
    register int i,j,k,l,m,parent;
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
Fraction parse(string terms, map<string,double> knowns, string unknown){
    string temp,pemp="1";
    register int i=terms.find(")^"),j,k,l,m,exp;
    i=terms.find("((");
    while(i!=string::npos){
        terms=terms.substr(0,i+1)+'+'+terms.substr(i+1,terms.length()-i-1);
        i=terms.find("((");
    }
    /**No sign means multiplication :p**/
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
    terms=(terms[0]=='-'||terms[0]=='+')?terms:('+'+terms);
    i=terms.find("/(");
    k=i+1;
    l=part(terms,i,1);
    pemp="1";
    for(i=0;i<terms.length();i=part(terms,i,1)){
        k=i+1;
        l=part(terms,i,1)-1;
        temp=terms.substr(k,l-k+1);
        m=temp.find("/(");
        exp=m;
        pemp="1";
        while(m!=string::npos){
            j=match(temp,m+1);
            pemp+=('*'+temp.substr(m+1,j-m));
            temp=temp.substr(0,m)+temp.substr(j+1,temp.length()-j);
            m=temp.find("/(");
        }
        pemp="(+"+pemp+")";
    terms=(exp!=string::npos)?terms.substr(0,k)+temp+'/'+pemp+terms.substr(l+1,terms.length()-l-1): terms;
    }
    ExpTree mytree=ReduceNode(ToTree(terms,knowns,unknown));
    return mytree.val;
}

int main()
{
    char a;
    register int i,j,temp;
    double nval;
    map<string,double> knowns;
    string unknown="x",pemp, hmm;
    string val="(x-2)(x+2)^3/(x^3-1)^2+x/(x+3)^2";
    cout << "Open parse.ini with notepad to change the names/values of variables.You can change them anytime.\n";
    xx:
    cout <<"\nExpression=";
    cin >> val;
    cout << "\n";
    ifstream fin("parser.ini");
    fin >> pemp;
    fin >> unknown;
    fin >> pemp;
    fin >> temp;
    for(i=0;i<temp;i++){
        fin >> pemp;
        fin >> hmm >> nval;
        knowns[pemp]=nval;
    }
    //knowns["y"]=1;
    //string unknown="x";
    //string val="(x-2)(x+2)^3/(x^3-1)^2+x/(x+3)^2";
    //ExpTree mytree=ReduceNode(ToTree(val,knowns,unknown));
    Fraction thetree=parse(val,knowns,unknown);
    thetree.nume.show();
    cout << "\n";
    if(thetree.denom.coef.size()>1){
        for(j=0;j<max(thetree.nume.coef.size(),thetree.denom.coef.size());j++)cout << "-----";
        cout << "\n";
        thetree.denom.show();
        cout << "\n\n";
    }cout << "(N)ew\t(Q)uit\n";
    cin >> a;
    cout << "\n";
    system("cls");
    if(a=='n'||a=='N') goto xx;
    else return 0;
}
