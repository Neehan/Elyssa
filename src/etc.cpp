#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list>

using namespace std;

#define DBL_EPSILON        1e-300

bool CompareDoubles (double A, double B)//No doubt
{
   double diff = A - B;
   return (diff < DBL_EPSILON) && (-diff < DBL_EPSILON);
}

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list>
using namespace std;
#define DBL_EPSILON        1e-300
bool CompareDoubles (double A, double B)//No doubt
{
   double diff = A - B;
   return (diff < DBL_EPSILON) && (-diff < DBL_EPSILON);
}
Adib Hasan
Commit changes

Commit changes  
