#pragma once
#include <Windows.h>
#include "ThreadPool.h"
#include <iostream>
#include <string>
#include <fstream>

std::string arr[1000];
std::string someArr[1000] = {};

void Merge(int left, int mid, int right) 
{
	int i1 = left;
	int i2 = mid + 1;
	for (int i = left; i <= right; i++)
	{
		if (i1 == mid + 1)
		{
			someArr[i] = arr[i2];
			i2++;
		}
		else
		{
			if (i2 == right + 1)
			{
				someArr[i] = arr[i1];
				i1++;
			}
			else
			{
				if (arr[i2] < arr[i1])
				{
					someArr[i] = arr[i2];
					i2++;
				}
				else
				{
					someArr[i] = arr[i1];
					i1++;
				}
			}
		}
	}
	for (int i = left; i <= right; i++)
	{
		arr[i] = someArr[i];
	}
}

void Sort(int left, int right) 
{
	if (left == right)
	{
		return;
	}
	int mid = (left + right) / 2;
	Sort(left, mid);
	Sort(mid + 1, right);
	Merge(left, mid, right);
}

int main()
{
	std::cout << "Enter the number of threads\n";
	int countThread;
	std::cin >> countThread;
	std::ifstream in("1.txt");
	int n = 0;
	if (in.is_open()) 
	{
		std::string line;
		while (getline(in, line)) {
			arr[n] = line;
			n++;
		}
	}
	in.close();

	if (n < countThread)
	{
		countThread = n;
	}
	threadPoolCreate(countThread);

	int cT = countThread;
	int nn = n;
	int i1 = 0;
	for (int i = 0; i < countThread; i++) 
	{
		taskArgs task;
		task.task = Sort;
		task.left = i1;
		task.right = i1 + nn / cT - 1;
		addTask(task);
		i1 += nn / cT;
		nn -= nn / cT;
		cT--;
	}
	finishTasks();

	cT = countThread;
	nn = n;
	i1 = 0;

	for (int i = 0; i < countThread; i++)
	{
		if (i1 != 0)
		{
			Merge(0, i1 - 1, i1 + nn / cT - 1);
		}
		i1 += nn / cT;
		nn -= nn / cT;
		cT--;
	}

	for (int i = 0; i < n; i++) 
	{
		std::cout << arr[i] << " ";
	}
}