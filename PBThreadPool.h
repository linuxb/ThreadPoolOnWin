#ifndef _PBTHREADPOOL_H_
#define _PBTHREADPOOL_H_

#include "pbthread.h"
#include <set>
#include <list>
//#include <stdafx.h>

class ThreadPoolExcute
{
public:

	ThreadPoolExcute(void);
	//ThreadPoolExcute(unsigned int _max, unsigned int _min);
	explicit ThreadPoolExcute(Runnable* type_task);

	~ThreadPoolExcute(void);

public:

	class CTWorker : public PBThread
	{
	public:
	    //CTWorker(void);
		CTWorker(Runnable* p_run, ThreadPoolExcute* t_pool);
		~CTWorker(void);

		void Run();

private:
		int t_workernum;
		Runnable* work_prun = NULL;
		bool enabledo = true;
		ThreadPoolExcute* w_pool_prt = NULL;
	};

public:

	unsigned int GetPoolSize();
	bool Execute(Runnable* p_runtask);
	//待处理任务链表
	//void Execute(std::list<Runnable*> p_task_list);
	//
	//void initThreadPool();
    bool initThreadPool(unsigned int max = 100, unsigned int min = 10);
	void Terminate();
	//获取任务
	Runnable* getTask();
	//销毁线程池
	void DestroyPool(bool enabledestroy = false);

private:
	//RB_Tree ThreadPool(红黑树线程池)
	typedef std::set<CTWorker*> _ThreadPoolExcute;
	typedef std::set<CTWorker*> _ThreadTrashPool;
	//RB Tree 迭代器
	typedef std::set<CTWorker*>::iterator _Threaditer;
	//任务链表
	typedef std::list<Runnable*> TaskList;



	_ThreadPoolExcute pool;
	_ThreadPoolExcute t_threadpool;
	//线程垃圾回收池
	_ThreadTrashPool t_trashthread;
	TaskList t_task;
	//_Threaditer t_iter;

	volatile  unsigned int max_thread_num;
	volatile  unsigned int min_thread_num;
	//busy worker
	volatile  unsigned int _t_pending_num;
	//互斥线程锁
	CRITICAL_SECTION t_csThreadPool;
	CRITICAL_SECTION t_csTasklist;
	//
	volatile bool m_brun;
	//线程池中是否可以插入新任务
	volatile bool enableInsertTask;
	volatile Runnable* type_task;

};

#endif