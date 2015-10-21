#ifndef _PBTHREAD_H
#define _PBTHREAD_H

#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//runnable

class Runnable
{
	//线程执行基类
public:
	Runnable(){};
	
	virtual ~Runnable(){};

//protected:
	virtual void Run() = 0;

};

class PBThread : public Runnable
{
private:
	explicit PBThread(const PBThread& prt);
public:
	PBThread(void);
	PBThread(Runnable* prun);
	PBThread(const char* threadname, Runnable* prun = NULL);
	PBThread(unsigned int thread_id, const char* threadname, Runnable* prun = NULL);
	PBThread(std::string threadname, unsigned int thread_id, Runnable* prun = NULL);

	~PBThread(void);

	//void Start();
	bool Start(bool m_issuspend = false);
	//线程启动

	virtual void Run();
	//线程释放资源，进入等待队列
	void Join(int timeout = -1);

	//线程从挂起备用过渡至运行态（RB_Tree）
	void Resume();

	//线程挂起
	void Suspend();

	bool Terminate(unsigned long ExitCode);

	std::string GetThreadName();

	unsigned int GetThreadID();

	void SetThreadname(const char* name);
	void SetThreadID(unsigned int _id);

private:
	//回调
	static unsigned int WINAPI StaticThreadFunc(void* prt);
private:
	//线程句柄
	HANDLE m_handle = NULL;
	//
	Runnable* const m_prun;
	//id
	unsigned int m_threadid;
	//name
	std::string  m_threadname;
	//run or not
	volatile bool m_brun;
	//volatile bool m_issuspend;
};
#endif 