
#include "pbthread.h"

//构造函数
PBThread::PBThread(void) :m_prun(NULL), m_brun(false)
{

}

PBThread::PBThread(Runnable* p_run) : m_prun(p_run), m_brun(false),
m_threadname("")
{

}

PBThread::PBThread(const char* name, Runnable* p_run) : m_threadname(name),
m_prun(p_run), m_brun(false)
{

}

PBThread::PBThread(unsigned int id, const char* name, Runnable* p_run) :
m_prun(p_run), m_threadid(id), m_threadname(name), m_brun(false)
{

}

PBThread::PBThread(std::string name, unsigned int id, Runnable* p_run) :
m_prun(p_run), m_threadid(id), m_threadname(name), m_brun(false)
{

}

//析构函数
PBThread::~PBThread(void)
{

}

//start

void PBThread::Run()
{
	//线程在运行态
	if (!m_brun)
	{
		return;
	}
	//任务不为空
	if (NULL != m_prun)
	{
		m_prun->Run();
	}
	//阻塞队列
	m_brun = false;
}

//enter the waiting Queue
void PBThread::Join(int timeout)
{
	//
	//线程在等待队列或者没在进程中创建
	if ((NULL == m_handle) || (!m_brun))
	{
		return;
	}
	if (timeout <= 0)
	{
		timeout = INFINITE;
	}
	//等待函数
	::WaitForSingleObject(m_handle,timeout);
}

//start the Thread
bool PBThread::Start(bool issuspend)
{
	//run or waiting
	//creat the Thread
	//已经在运行
	if (m_brun)
	{
		return true;
	}
	//如被挂起
	//waiting queue等待队列
	if (issuspend)
	{
		//param:安全设置（NULL）,堆栈大小，回调指针，实例指针，标识，id指针
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, CREATE_SUSPENDED, &m_threadid);
	}
	else
	//线程被销毁
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, 0, &m_threadid);
	}
	//run
	m_brun = (NULL != m_handle);
	return m_brun;
}

//从阻塞队列回到运行态
void PBThread::Resume()
{
	//阻塞或挂起
	if ((m_brun) || (NULL == m_handle))
	{
		return;
	}
	::ResumeThread(m_handle);
}

//suspend 挂起
void PBThread::Suspend()
{
	if ((!m_brun) || (NULL == m_handle))
	{
		return;
	}
	::SuspendThread(m_handle);
	//suspend,join destroy:m_brun = false
	m_brun = false;
}

//终止线程
bool PBThread::Terminate(unsigned long ExitCode)
{
	//only for the running Thread
	if ((!m_brun) || (NULL == m_handle))
	{
		return true;
	}
	//关闭线程
	if (::TerminateThread(m_handle, ExitCode))
	{
		//关闭在进程中注册的句柄
		::CloseHandle(m_handle);
		return true;
	}
	std::cout << "failed to close the Thread" << "\n\n" << std::endl;
	Sleep(1000);
	return false;
}

unsigned int PBThread::GetThreadID()
{
	return m_threadid;
}

std::string PBThread::GetThreadName()
{
	if ("" == m_threadname)
	{
		return "no name";
	}
	else
	{
		return m_threadname;
	}
}

void PBThread::SetThreadname(const char* name)
{
	if (NULL == name)
	{
		m_threadname = "";
	}
	else
	{
		m_threadname = name;
	}
}

void PBThread::SetThreadID(unsigned int id)
{
	m_threadid = id;
}

unsigned int PBThread::StaticThreadFunc(void* prt)
{
	//线程指针
	PBThread* pthread = (PBThread*)prt;
	pthread->Run();
	return 0;
}






