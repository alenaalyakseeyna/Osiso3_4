#pragma once
#include <Windows.h>
#include <string>

// delegate

typedef void (*taskDelegate)(int, int);
typedef struct
{
	taskDelegate task;
	int left;
	int right;
}taskArgs;


void threadPoolCreate(int);
void work();
void addTask(taskArgs);
void finishTasks();

