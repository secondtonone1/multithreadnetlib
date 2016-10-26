#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "task.h"
#include <list>
#include <vector>
#include "netmodeldef.h"
#include <assert.h>
#include "threadworker.h"
#include <stdlib.h>

class ThreadPool
{
public:
	ThreadPool(int num);
	~ThreadPool();

	void addTask(CTask * pTask, int listId);

	struct ListHeadTail *  getTaskList(int index);


private:
	void insertTaskNode(TaskNode * pNode, int index);

	void delTaskList(TaskNode * pNode);

	std::vector<ThreadWorker *> m_vecThreadWorkers;
	int m_nThreadCount;

};

#endif