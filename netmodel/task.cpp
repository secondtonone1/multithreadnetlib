#include "task.h"

void  defaultRunCb (void * data) {}

CTask::CTask()
{
	m_strTaskName = std::string("");
	m_ptrTaskCb = &defaultRunCb;
	m_ptrData = NULL;
	m_nLen = 0;
}

CTask::CTask(string taskName)
{
	m_strTaskName = taskName;
	m_ptrTaskCb = &defaultRunCb;
	m_ptrData = NULL;
	m_nLen = 0;
}

CTask::~CTask()
{
	m_strTaskName = std::string("");
	m_ptrTaskCb = &defaultRunCb;
	if(m_ptrData)
	{
		m_ptrData = NULL;
	}
}

void CTask::registerCb(taskRunCb taskCb, void * cbData)
{
	m_ptrTaskCb = taskCb;
	m_ptrData = cbData;
}

void CTask::dealTask()
{
	(*m_ptrTaskCb)(m_ptrData);
}

//void CTask::setTaskData(void * cbData, int len)
//{
//	m_ptrData = cbData;
//	m_nLen = len;
//}