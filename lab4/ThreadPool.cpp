#include "ThreadPool.h"
#include <iostream>

CONDITION_VARIABLE taskReady;
int threadCount;
int taskCount;
int taskI;
RTL_CRITICAL_SECTION lock;
taskArgs tasks[1000];
HANDLE* workers;
bool disposed;

void threadPoolCreate(int count)
{
	InitializeCriticalSection(&lock);
	threadCount = count;
	workers = (HANDLE*)malloc(threadCount * sizeof(HANDLE));
	for (int i = 0; i < threadCount; i++)
	{
		workers[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work, NULL, 0, 0);
	}
	disposed = false;
	taskI = 0;
	taskCount = 0;
	InitializeConditionVariable(&taskReady);
}

void work()
{
	while (true)
	{
		taskArgs newTask = {};
		EnterCriticalSection(&lock);
		while (true)
		{
			if (disposed)
			{
				LeaveCriticalSection(&lock);
				return;
			}
			if (taskCount > 0)
			{
				newTask = tasks[taskI];
				taskI++;
				taskCount--;
				WakeAllConditionVariable(&taskReady);
				break;
			}
			SleepConditionVariableCS(&taskReady, &lock, INFINITE);
		}
		LeaveCriticalSection(&lock);
		if (newTask.task != nullptr)
		{
			newTask.task(newTask.left, newTask.right);
		}
	}
}

void addTask(taskArgs task)
{
	EnterCriticalSection(&lock);
	tasks[taskCount] = task;
	taskCount++;
	WakeAllConditionVariable(&taskReady);
	LeaveCriticalSection(&lock);
}

void finishTasks()
{
	EnterCriticalSection(&lock);
	while (taskCount > 0)
	{
		SleepConditionVariableCS(&taskReady, &lock, INFINITE);
	}
	disposed = true;
	WakeAllConditionVariable(&taskReady);
	LeaveCriticalSection(&lock);
	for (int i = 0; i < threadCount; i++)
	{
		CloseHandle(workers[i]);
	}
	free(workers);
	Sleep(500);
	DeleteCriticalSection(&lock);
}