#include "TickRespectiveFunction.h"


void TickRespectiveFunction::allocateFunction(std::function<bool()> function)
{
	callFunction = function;
}

bool TickRespectiveFunction::run()
{
	Timer* t = new Timer();

	int localCurrentTime = 0;
	bool continueExecution = true;
	while (localCurrentTime < maxExecutionTime && continueExecution)
	{
		t->getTime();
		continueExecution = callFunction();
		localCurrentTime += t->getTime();
	}

	return continueExecution;
}