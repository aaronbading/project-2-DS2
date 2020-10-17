#ifndef Customer_H
#define Customer_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Customer
{
public:
Customer(float arrival,bool decision);

void setarrivalTime(float time);
float getarrivalTime();
void setStart(float time);
float getStart();
void setDeparture(float time);
float getDeparture();
void setisArrival(bool decision);
bool getisArrival();
void setqueueTime(float time);
void setnext(Customer* next);
Customer* getnext();
float getqueueTime() const;
 friend bool operator > (const Customer& lhs, const Customer& rhs);
void setwait(float time);
float getwait();


private:

float queueTime;
float arrivalTime;
float startOfServiceTime;
float departureTime;

bool isArrival;
Customer* next;
float waittime;
};
#endif
