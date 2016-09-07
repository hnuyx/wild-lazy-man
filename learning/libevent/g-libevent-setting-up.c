// libevent setting up
// http://www.wangafu.net/~nickm/libevent-book/Ref1_libsetup.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <event.h>

/* discard all log */
void discard_all_log(int severity, const char *msg)
{
	// do nothing

	return ;
}

/* handle event log */
void handle_event_log(int severity, const char *msg)
{
	const char *s;
	switch(severity)
	{
	case _EVENT_LOG_DEBUG:
		s = "DEBUG";
		break;
	case _EVENT_LOG_MSG:
		s = "MSG";
		break;
	case _EVENT_LOG_WARN:
		s = "WARN";
		break;
	case _EVENT_LOG_ERR:
		s = "ERROR";
		break;
	default :
		s = "?????";
		break;
	}
	fprintf(stderr, "%5s-%s", s, msg);

	return ;
}

/* handle fatal error */
void handle_fatal_error(int err)
{
	fprintf(stderr, "fatal error %d-%s", err, strerror(err));
	return ;
}

#ifdef EVENT_SET_MEM_FUNCTIONS_IMPLEMENTED
/* handle memory management */
union alignment
{
	size_t sz;
	void *ptr;
	double dbl;
};
#define ALIGNMENT sizeof(union alignment)

#define INPTR(ptr) (((char *)ptr) - ALIGNMENT)
#define OUTPTR(ptr) (((char *)ptr) + ALIGNMENT)

static size_t total_allocated = 0;
static void* my_ev_malloc(size_t sz)
{
	void *ptr = malloc(sz + ALIGNMENT);
	if(!ptr)
	{
		return NULL;
	}
	total_allocated += sz;
	*(size_t *)ptr = sz;
	return OUTPTR(ptr);
}

static void *my_ev_realloc(void *ptr, size_t sz)
{
	size_t old_sz = 0;
	if(ptr)
	{
		ptr = INPTR(ptr);
		if(0 == sz)
		{
			free(ptr);
			return NULL;
		}
		old_sz = *(size_t *)ptr;
	}
	ptr = realloc(ptr, sz + ALIGNMENT);
	if(!ptr)
	{
		return NULL;
	}
	*(size_t *)ptr = sz;
	total_allocated += (sz - old_sz);
	return OUTPTR(ptr);
}

static void my_ev_free(void *ptr)
{
	ptr = INPTR(ptr);
	total_allocated -= *(size_t *)ptr;
	free(ptr);
}

#endif


int main()
{
	// enable debug mode
	event_enable_debug_mode();

	// set log callback
	event_set_log_callback(handle_event_log);

	// set fatal error callback
	event_set_fatal_callback(handle_fatal_error);

#ifdef EVENT_SET_MEM_FUNCTIONS_IMPLEMENTED
	// memory magement
	event_set_mem_functions(my_ev_malloc, my_ev_realloc, my_ev_free);
#endif

	return 0;
}
