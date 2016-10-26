#ifndef __THREADWORKER_H__
#define __THREADWORKER_H__
#include "basethread.h"
#include "task.h"
#include "netmodeldef.h"
#include "lock.h"
#include "mutex.h"
#include "condition.h"
#include <assert.h>
#include <stdlib.h>
class ThreadPool ;

struct TaskNode
{
	CTask * pTask;
	struct TaskNode * pNext;
	struct TaskNode * pPre;
};

struct ListHeadTail
{
	TaskNode * pHead;
	TaskNode * pTail;
};

class ThreadWorker: public BaseThread
{
public:
	ThreadWorker(int index, ThreadPool * poolPoint);
	~ThreadWorker();
	virtual void threadWorkFunc(void);

	void insertTaskToList(TaskNode * taskNode);

	void delTaskList(TaskNode * taskNode);

private:
	int m_nIndex;
	ThreadPool * m_pThreadPool;

	struct ListHeadTail * m_pTaskList;

	Mutex m_mutexTask;
	Condition m_condTask;
	Mutex m_mutexOutMsg;
	Condition m_condOutMsg;
};

#endif