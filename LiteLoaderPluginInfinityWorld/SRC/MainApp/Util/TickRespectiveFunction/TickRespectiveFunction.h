#pragma once
#include "..\Timer.h"
#include <functional>

/*
* This loop calls the function
*/
class TickRespectiveFunction
{
public:
    TickRespectiveFunction(int maxExecutionTime = 35)
        : maxExecutionTime(maxExecutionTime)
    {
    };

	// This function returns true if the execution finished before the timer maxed :)
	bool run();

    void allocateFunction(std::function<bool()> function);

    template<typename ClassType>
    void allocateFunction(ClassType* classInstance, bool (ClassType::* memberFunction)())
    {
        std::function<bool()> func = [classInstance, memberFunction]() -> bool {
            return (classInstance->*memberFunction)();
        };

        callFunction = func;
    }

private:
	std::function<bool()> callFunction;
    int maxExecutionTime;
};

