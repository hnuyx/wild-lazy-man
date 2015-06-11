/* File Name: thread_base.h
 *
 * Description: thread base
 *
 * Created by henuyx on 2015-06-11
 *
 */

#ifndef __THREAD_BASE_H__
#define __THREAD_BASE_H__

/*******************INCLUDE*******************************/
#include <pthread.h>

/*******************GLOBAL********************************/

class ThreadBase
{
public:
	// callback for thread
	typedef void* (*ThreadCallback)(void *);

	ThreadBase(int ds = PTHREAD_CREATE_DETACHED);
	virtual ~ThreadBase();

	/* create and run tcb */
	int create_run(ThreadCallback tcb, void *data=NULL);

	/* run main-thread function process */
	int start();
	/* stop main-thread function process */
	void stop();
	/* main-thread functioin process */
	virtual void process() = 0;

protected:
	/* call process */
	static void *call_func(void *data);

	/* thread id, attribute, data */
	pthread_t m_tid;
	pthread_attr_t m_tattr;
};

#endif

/*******************EOF***********************************/
