/* File Name: thread_base.cpp
 *
 * Description: thread base
 *
 * Created by henuyx on 2015-06-11
 *
 */

/*******************INCLUDE*******************************/
#include <signal.h>

#include "thread_base.h"

/*******************GLOBAL********************************/

ThreadBase::ThreadBase(int ds)
{
	pthread_attr_init(&m_tattr);
	pthread_attr_setdetachstate(&m_tattr, ds);

	m_tid = 0;
}

ThreadBase::~ThreadBase()
{
	pthread_attr_destroy(&m_tattr);
	if(0 != m_tid)
	{
		stop();
	}
}

/* create and run tcb */
int ThreadBase::create_run(ThreadCallback tcb, void *data)
{
	sigset_t sig_mask;
	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, SIGPIPE);
	pthread_sigmask(SIG_BLOCK, &sig_mask, NULL);

	//pthread_t tid = 0;
	return pthread_create(&m_tid, NULL, tcb, data);
}

/* run main-thread function process */
int ThreadBase::start()
{
	sigset_t sig_mask;
	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, SIGPIPE);
	pthread_sigmask(SIG_BLOCK, &sig_mask, NULL);

	return pthread_create(&m_tid, &m_tattr, call_func, this);
}

/* stop main-thread function process */
void ThreadBase::stop()
{
	pthread_cancel(m_tid);
	m_tid = 0;
}

/* call process */
void* ThreadBase::call_func(void *data)
{
	ThreadBase *tb = (ThreadBase *)data;
	tb->process();

	return NULL;
}

/*******************EOF***********************************/
