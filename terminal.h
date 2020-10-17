#ifndef Terminal_H
#define Terminal_H

#include <iostream>
#include <string>
#include <vector>
#include "customer.h"
#include "analytical.h"

#include <functional>
#include <vector>
#include <queue>

#include <time.h>
#include <math.h>
using namespace std;

class Terminal
{
public:
Terminal();

void Fill();     // fills up priority queue
void processEvent(); 		//processes either an arrival or a departure
float getInterval(float avg);	//generates intervals
void EventLoop();		
void processStatistics(Customer* ptr);

void generaterandomvector();

//fifo 
bool isempty();
void enqueue(Customer* ptr);
Customer* dequeue();


private: 
Customer* front;
Customer* rear;
priority_queue<Customer, vector<Customer>, greater<vector<Customer>::value_type> > pqueue;
float n;
float lambda;
float mu;
float M; 

float serverCount; //servers 
float numberprocesses;	//dummy number to simulate 
float currenttime;     
float leftofftime;	

float customerwaitcount; //statistics
float totalwaittime;
float totalservicetime;
float idletime;

vector<float> numbers; //stores all the random numbers

};
#endif
