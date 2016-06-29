#include <stdio.h>
#include <event.h>

void timer_cb(evutil_socket_t fd, short ev, void *arg)
{
	printf("successfully call timer_cb\n");

	// set timer
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	// add ev to the list of monitored events
	event_add((struct event *)arg, &tv);
}

int main()
{
	// init event liberary
	event_init();

	// set timer
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	// init ev
	struct event ev;
	evtimer_set(&ev, timer_cb, &ev);

	// add ev to the list of monitored events
	event_add(&ev, &tv);

	// loop and dispatch events
	event_dispatch();

	return 0;
}
