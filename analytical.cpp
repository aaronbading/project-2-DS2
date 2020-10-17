#include"analytical.h"
#include <iostream>

analytical::analytical(float lambda ,float mu, float M):lambda(lambda),mu(mu),M(M)
{ 
float sum=0;
   for(float i=0;i<=M-1;i++)
   {
   	sum=sum+(1/fact(i))*pow((lambda/mu),i);
   }

sum= sum + (1/fact(M))*pow(lambda/mu,M)*(M*mu)/(M*mu-lambda);
 
float Po = 1/sum, L ,W ,Lq , Wq ,rho;
L= (lambda*mu*pow(lambda/mu,M)*Po)/(fact(M-1)*pow(M*mu-lambda,2)) + lambda/mu;
W= L/lambda;
Lq=L-(lambda/mu);
Wq = Lq/lambda;
rho = lambda/(M*mu);
cout << "Analytical Model :  " << endl << endl;
cout << " 1) (Percent idle) Po =  "  << Po << endl;
cout << " 2) (Average number of people in the system) L =  " << L << endl;
cout << " 3) (Average time a Customer spends in System) W = "  << W <<endl;
cout << " 4) (The average numbers of customers in the queue) Lq = "<< Lq << endl;
cout << " 5) (Average time a Customer spends in Queue)  Wq = " << Wq << endl;
cout << " 6) (Utilization Factor) rho = " << rho << endl << endl;

}

float analytical::fact(float n)
{


  float  fact = 1, i;
   for(i=1; i<=n; i++)
   fact = fact * i;
return fact;
}
