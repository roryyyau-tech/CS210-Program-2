#include "request.h"
#include "webserver.cpp"
#include "loadbalancer.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

const int NUM_SERVERS = 5;
int processID = 0;

request createRandomRequest()
{
    request r;
    stringstream sourceAddress;
    stringstream destinationAddress;

    sourceAddress << (rand() % 256) << "."
                 << (rand() % 256) << "."
                 << (rand() % 256) << "."
                 << (rand() % 256);

    destinationAddress << (rand() % 256) << "."
                        << (rand() % 256) << "."
                        << (rand() % 256) << "."
                        << (rand() % 256);


   r.source = sourceAddress.str();
   r.destination = destinationAddress.str();
   r.processTime = rand() % 500;
   r.pid = ++processID;
   return r;
}

int main() 
{
    //fixed seed so program is deterministic
    srand(1);

    loadbalancer lb;

    //start w 10 requests in the load balancer
    for (int i = 0; i < 10; i++) 
    {
        lb.addRequest(createRandomRequest());
    }
    //make 5 web servers
    webserver webArray[NUM_SERVERS];

    for (int i = 0; i < NUM_SERVERS; i++) 
    {
        webArray[i] = webserver(static_cast<char>('A' + i));
        webArray[i].addRequest(lb.getRequest(), lb.getTime());
    }
    //run the simulation
    while(lb.getTime() < 10000) 
    {
       int currentTime = lb.getTime();
       int queueSize = lb.getSize();
       int serverIndex = currentTime % NUM_SERVERS;

       if(webArray[serverIndex].isRequestDone(currentTime))
        {
            request finishedRequest = webArray[serverIndex].getRequest();

            cout << "Finished at " << currentTime << " "
                << webArray[serverIndex].getName()
                << " pid " << finishedRequest.pid
                << "/" << queueSize
                << " process time was " << finishedRequest.processTime
                << " processed request from "
                << finishedRequest.source
                << " to "
                << finishedRequest.destination
                << endl;

            webArray[serverIndex].addRequest(
                lb.getRequest(),
                currentTime
            );
        }
    // Occasionally add a new request.
      if (rand() % 10 == 0)
      {
         lb.addRequest(createRandomRequest());
      }

      lb.incTime();
   }

   return 0;
     
}

