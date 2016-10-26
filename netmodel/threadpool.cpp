#include "threadpool.h"
#include "threadworker.h"

ThreadPool::ThreadPool(int num)
{
	for(int i = 0; i < num; i++)
	{
	
		ThreadWorker * threadWorker = new ThreadWorker(i,this);
		m_vecThreadWorkers.push_back(threadWorker);
	}
	
	m_nThreadCount = num;



}
	
ThreadPool::~ThreadPool()
{
	for(unsigned int i = 0; i < m_vecThreadWorkers.size(); i++)
	{
		if(m_vecThreadWorkers[i])
		{
			delete (m_vecThreadWorkers[i]);
			m_vecThreadWorkers[i] = NULL;
		}
	}

	
	m_nThreadCount = 0;


}



void ThreadPool::addTask(CTask * pTask, int listId)
{
	int round = listId%m_nThreadCount;
	TaskNode * taskNode = (TaskNode *)malloc(sizeof(struct TaskNode)*1);
	if(!taskNode)
	{
		cout << "malloc task node failde!!!"<<endl;
		return ;
	}

	taskNode->pTask = pTask;
	taskNode->pPre = NULL;
	taskNode->pNext = NULL;
	
	insertTaskNode(taskNode, round);

}



void ThreadPool::insertTaskNode(TaskNode * taskNode, int index)
{
	if(index >= m_nThreadCount)
	{
		return ;
	}

	m_vecThreadWorkers[index]->insertTaskToList(taskNode);
}