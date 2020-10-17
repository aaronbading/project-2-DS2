#include "terminal.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <time.h>

Terminal::Terminal()
{

cout << " Simulation input : " << endl << endl;
cout << " n = number of arrivals to simulate (we will test with >1000 up to 5000)" << endl;
cin >> n;
cout << " lambda = average arrivals in a time period." << endl;
cin >> lambda;
cout << " mu = average number served in a time period." << endl;
cin >> mu;
cout << "M - the number of service channels (1 to 10) " << endl;
//error checking
bool decision=true;
while(decision)
{
cin >> M;
if(M>0&&M<=10)
decision=false;
}
serverCount=M; //set server count to M 
numberprocesses=n; //dummy number is n

currenttime=0;
totalwaittime=0;
generaterandomvector();  // this fills out vector of random numbers of size n*2 for all arrivals and departures. to generate the intervals. 

front=nullptr;
rear=nullptr;
priority_queue<Customer, vector<Customer>, greater<vector<Customer>::value_type >> pqueue_greater;
pqueue=pqueue_greater;
customerwaitcount=0;
// Fill with entries
Fill();
EventLoop();
analytical object(lambda,mu,M);

}

//FILL
void  Terminal::Fill()
{
	float prevtime=0;
	//first fill
	if(pqueue.empty())
	{prevtime=0;}
	else   //not first fill
	{prevtime=leftofftime;}

	float arrivaltime;	
	for(int i=0;numberprocesses>0&&i<200; i++)
	{arrivaltime=prevtime+getInterval(lambda); //generate time interval and then add it to the previous time so its linear. 
	prevtime=arrivaltime;
	Customer object(arrivaltime,true);
	pqueue.push(object);
	numberprocesses--;
	}
	leftofftime=arrivaltime;

}

//PROCESSSTATISTICS
void Terminal::processStatistics(Customer* ptr)
{

	if(ptr->getwait() >0)
	{customerwaitcount++;}
totalwaittime=totalwaittime+ptr->getwait();
totalservicetime= totalservicetime+ (ptr->getDeparture()-ptr->getarrivalTime());

	if(serverCount==M)
	{// idle time
		if(!pqueue.empty())
		{//meaning there are more arrivals left.
			Customer top=pqueue.top();
		idletime=idletime+(top.getarrivalTime()-currenttime);
		}	
	}

}

//PROCESSEVENT
void Terminal::processEvent()
{
//this function follows the logic of the pseuodocode given

 Customer current =pqueue.top();
 Customer* currentptr= &current;
 pqueue.pop();
 currenttime=current.getqueueTime();
 if(current.getisArrival())
 {   // arrival turns into a departure so we must generate departure time and change its queuetime to its departure time. also setting its isArrival to falsei
	 if( serverCount >0)
 	{//startof service time == its arrival time     departure is just that time plus the generated interval
	serverCount--;
	current.setStart(current.getqueueTime());
	float interval =getInterval(mu);
	interval=current.getarrivalTime() +interval;
	current.setDeparture(interval);
	current.setqueueTime(interval);
	current.setisArrival(false);
	pqueue.push(current);
	}
	else
	{enqueue(currentptr);}
 }
   else
  {//processing departure

  serverCount++;
    processStatistics(currentptr); //we must pass in current in here to do the analysis on that departure

  	if(!isempty())
	{//remove from Fifo, manipulate fifo, put in pqueue.

	Customer* ptr=dequeue();
	ptr->setStart(currenttime); //getting service at current's departure time.

        float interval =getInterval(mu);

        interval=currenttime +interval;

	ptr->setDeparture(interval);

	ptr->setqueueTime(interval);

	ptr->setwait(ptr->getStart()-ptr->getarrivalTime());
       	//setting the waittime in this case

	pqueue.push(*ptr);
	serverCount--;
	//case where a customer had to wait , so the difference between arrival time and start of service time will be the time that that person waited
	
	}

   }

}
//GETINTERVAL
float Terminal::getInterval(float avg)
{
	float nextrandom=0.5;// incase the vector somehow is empty
	if(!numbers.empty())
	{ nextrandom= numbers.back();
		numbers.pop_back();}

float interval = -1*(1/avg)*log(nextrandom);

return interval;
}
//GENERATERANDOM
void Terminal::generaterandomvector()
{
vector<float> myvector;
numbers=myvector;
  srand( (unsigned)time( NULL ) );

    for (int i = 0; i < n*2; i++)
    {
        numbers.push_back( (float) rand()/RAND_MAX);
    }

}
//EVENT LOOP
void Terminal::EventLoop()
{

 while (!pqueue.empty())
 {processEvent();
if(numberprocesses>0&& pqueue.size()<=M+1)
Fill();

 }

 //RESULTS
cout << "  Simulation Results :  " << endl << endl;
cout << " 1) (Percent idle) Po =  " << idletime/leftofftime << endl;
cout << " 3) (Average time a Customer spends in System) W = " << (totalwaittime+totalservicetime)/n << endl;
cout << " 5) (Average time a Customer spends in Queue)  Wq = " << totalwaittime/n << endl;
cout << " 6) (Utilization Factor) rho = " << totalservicetime/(M*leftofftime) << endl;
cout << "Probability of having to wait for service = " << customerwaitcount/n << endl << endl;
}


//fifo function below
bool Terminal::isempty()
{
if(front==nullptr&& rear==nullptr)
{return true;}
else
{return false;}

}
void Terminal::enqueue(Customer* ptr)
{
//empty
if(front==nullptr)
{front=ptr;
rear=ptr;}
else
{rear->setnext(ptr);
	rear=ptr;
}

}
Customer* Terminal::dequeue()
{
	if(isempty())
	{return nullptr;}
	else
	{
		
		if(front==rear)
		{

		Customer* ptr= front;
		front=nullptr;
		rear=nullptr;
		return ptr;
		}
		else
		{
		Customer* ptr=front;
		front=front->getnext();
		return ptr;
		}
	
	}


}








