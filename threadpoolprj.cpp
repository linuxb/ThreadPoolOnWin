// threadpoolprj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include "pbthread.h"
#include "PBThreadPool.h"
#include "pbthread.h"

//using namespace std;



class CDoWork : public Runnable
{
public:
	CDoWork(){};
	~CDoWork(){ std::cout << "delete" << std::endl, Sleep(1000); };

	void Run()
	{
		std::cout << "thread start" << "\n\n" << std::endl;
		Sleep(3000);
		Task();
	}
	void Task()
	{
		while (1)
		{
			std::cout << "linking well\n\n" << std::endl;
			Sleep(1000);
		}
	}
private:
	char* extradisc = NULL;
	int count;
};

void  _tmain(int argc, _TCHAR* argv[])
{
	std::cout << *argv<< std::endl;
	printf("helloworld\n\n");
	Sleep(3000);
	CDoWork mytask;
	ThreadPoolExcute* mypool = new ThreadPoolExcute();
	mypool->initThreadPool();
	for (int i = 0; i < 9; i++)
	{
		while (mypool->Execute(&mytask))
		{
		}
		Sleep(1000);
	}
	mypool->Terminate();
	delete mypool;
	//析构对象
	mytask.~CDoWork();
	std::cout << "ThreadPool s over\n\n" << std::endl;
	system("pause");
	//return 0;
}

