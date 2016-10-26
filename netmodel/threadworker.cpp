#include "threadworker.h"

ThreadWorker::ThreadWorker(int index, ThreadPool * poolPoint)
{
	m_nIndex = index;
	m_pThreadPool = poolPoint;
	m_pTaskList = (ListHeadTail *)malloc(sizeof(struct ListHeadTail) * 1);
	
	if(!m_pTaskList)
	{
			cout << "malloc failed!!"<<endl;
			assert(false);
	}
		
	m_pTaskList->pHead = NULL;
	m_pTaskList->pTail = NULL;
	

}

ThreadWorker::~ThreadWorker()
{
	m_nShutDown = 1;
	TaskNode * taskNode = m_pTaskList->pHead;
	while(taskNode)
	{
		TaskNode* nextNode = taskNode->pNext;
		if(taskNode->pTask)
		{
			delete(taskNode->pTask);
			taskNode->pTask = NULL;
		}

		free(taskNode);
		taskNode = nextNode;

	}
		
	if(m_pTaskList)
	{
		free(m_pTaskList);
		m_pTaskList = NULL;
	}
}


void ThreadWorker::insertTaskToList(TaskNode * taskNode)
{
	lock lock(m_mutexTask);
	//处理头部插入
	if( (m_pTaskList->pHead == m_pTaskList->pTail) &&  m_pTaskList->pHead == NULL)
	{
		m_pTaskList->pHead = taskNode;
		m_pTaskList->pTail = taskNode;
		taskNode->pPre = NULL;
		taskNode->pNext = NULL;
		
		return;
	}

	m_pTaskList->pTail->pNext = taskNode;
	taskNode->pPre = m_pTaskList->pTail;
	taskNode->pNext = NULL;

}


void ThreadWorker::threadWorkFunc(void)
{
	while(1)
	{
		// add lock 
		lock lock(m_mutexTask);
		//deal task
			
		while(m_pTaskList->pHead == m_pTaskList->pTail&& m_pTaskList->pTail  == NULL)
		{
			m_condTask.wait(m_mutexTask);
		}

		TaskNode * taskNode = m_pTaskList->pHead;
		while(taskNode)
		{
			TaskNode * taskNext = taskNode->pNext;
			if(taskNode->pTask)
			{
				taskNode->pTask->dealTask();
				delete(taskNode->pTask);
				taskNode->pTask = NULL;
			}

			free(taskNode);
			taskNext->pPre = NULL;
			taskNode = taskNext;

		}
		m_pTaskList->pHead = m_pTaskList->pTail = NULL;
		
	}
}