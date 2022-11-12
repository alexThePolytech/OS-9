#pragma once
#include <Windows.h>
#include <tchar.h>
#include <array>
#include <msclr\marshal.h>
#include <omp.h>
#include <chrono>


double* mainSum = new double(0);
long double* mainArr;
double* arrOfSums;
HANDLE* hThread;
int numOfThreads;
LPDWORD* threadInfo;

volatile unsigned long ResourseInUse = FALSE;

struct info {
	int indexOut;
	int startPos;
	int numOfSteps;
};

/*
* https://learn.microsoft.com/en-us/dotnet/api/system.threading.monitor?view=net-6.0
* The example of monitor usage in C#
*/
class Monitor
{
private:
	HANDLE EventFree;

public:
	Monitor()
	{
		EventFree = CreateEvent(NULL, TRUE, TRUE, L"MainEvent");
	}

	~Monitor()
	{
		CloseHandle(EventFree);
	}

	void Enter(double* obj)
	{
		WaitForSingleObject(EventFree, INFINITY);
		ResetEvent(EventFree);
	}

	void Exit(double* obj)
	{
		SetEvent(EventFree);
	}
};

info** datas;

DWORD WINAPI ThreadFunction(LPVOID param)
{
	//mainSum = (static_cast<double*>(param));
	info* data = reinterpret_cast<info*>(param);
	long double tmpSum = 0.0;
	for (int i = data->startPos; i < data->startPos + data->numOfSteps; i++) {
		tmpSum += mainArr[i];
	}

	arrOfSums[data->indexOut] = tmpSum;
	//for (long long i = 0; i < 1000000000000000; i++)
	//{
	//	i--;
	//}
	//*mainSum = *data->sum;

	return 0;
}

DWORD WINAPI ThreadFunctionInterlock(LPVOID param)
{
	info* data = reinterpret_cast<info*>(param);
	long double tmpSum = 0.0;
	for (int i = data->startPos; i < data->startPos + data->numOfSteps; i++) {
		tmpSum += mainArr[i];
	}

	while (InterlockedExchange(&ResourseInUse, TRUE) == TRUE)
		System::Threading::Thread::Sleep(0);

	*mainSum += tmpSum;
	InterlockedExchange(&ResourseInUse, FALSE);
	return 0;
}

DWORD WINAPI ThreadFunctionMonitor(LPVOID param)
{
	info* data = reinterpret_cast<info*>(param);
	long double tmpSum = 0.0;
	for (int i = data->startPos; i < data->startPos + data->numOfSteps; i++) {
		tmpSum += mainArr[i];
	}

	Monitor mon;
	mon.Enter(mainSum);
	*mainSum += tmpSum;
	mon.Exit(mainSum);
	return 0;
}