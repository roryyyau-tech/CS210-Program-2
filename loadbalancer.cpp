/* loadbalancer.cpp
 *
 * Manage the CPU load by assigning next job to CPU with the least load
 */

#include "loadbalancer.h"

int loadbalancer::getTime()
{
   return systemTime;
}

void loadbalancer::incTime()
{
   systemTime++;
}
  
void loadbalancer::addRequest(request r)
{
   requestQueue.push(r);
   incTime();
}
  
request loadbalancer::getRequest()
{
   request r = requestQueue.top();
   requestQueue.pop();
   incTime();
   return r;
}


   // ignore warning here about no return value


bool loadbalancer::isRequestQueueEmpty()
{
   return requestQueue.empty();
} 

int loadbalancer::getSize()
{
   return requestQueue.size();
}


