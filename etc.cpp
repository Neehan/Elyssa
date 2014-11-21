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
