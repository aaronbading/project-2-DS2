#ifndef Analytical_H
#define Analytical_H

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class analytical
{
public:
analytical(float lambda ,float mu, float M);
float fact(float n);


private:    
float lambda;
float mu;
float M;

};
#endif
               
