#include"customer.h"
#include <iostream>
#include <string>


Customer::Customer(float arrival,bool decision):arrivalTime(arrival)
{next=nullptr;
isArrival=decision;
queueTime=arrival;
waittime=0;}

void Customer::setarrivalTime(float time)
{arrivalTime=time;}
float Customer::getarrivalTime()
{return arrivalTime;}
void Customer::setStart(float time)
{startOfServiceTime=time;}
float Customer::getStart()
{return startOfServiceTime;}
void Customer::setDeparture(float time)
{departureTime=time;}
float Customer::getDeparture()
{return departureTime;} 
void Customer::setisArrival(bool decision)
{this->isArrival=decision;}
bool Customer::getisArrival()
{return isArrival;}
void Customer::setqueueTime(float time)
{queueTime=time;}
void Customer::setnext(Customer* next)
{this->next=next;}
Customer* Customer::getnext()
{return next;}

float Customer::getqueueTime() const
{return queueTime;}
 bool operator > (const Customer& lhs, const Customer& rhs)
{ return lhs.getqueueTime() > rhs.getqueueTime();}
void Customer::setwait(float time)
{waittime=time;}
float Customer::getwait()
{return waittime;}


