/* File Name: item_queue_T.h
 *
 * Description: item queue with time
 *
 * Created by henuyx on 2015-06-09
 *
 */

#ifndef __ITEM_QUEUE_T_H__
#define __ITEM_QUEUE_T_H__

/*******************INCLUDE*******************************/
#include <list>

/*******************GLOBAL********************************/

template <typename ID>
class ItemQueueT
{
public:
	typedef struct _ITEM
	{
		ID id;
		int time;
	} Item;
	typedef std::list<Item> ItemList;

public:
	ItemQueueT();
	virtual ~ItemQueueT();

	/* push item data,  return current count, -1 for failed */
	int push_item(ID &id, int t);
	/* check item count, return count from now to now-period */
	int check_item(int now, int period);
	/* clear all items, return current count, -1 for failed */
	int clear();
	/* clear timeout itmes(< now - timeout), return current count, -1 for failed */
	int clear_timeout(int now, int timeout);
	/* print item for now to now-period */
	void print_item(int now, int period);
	/* current count */
	int get_current_count();

protected:
	/* print item data, num is the num-th count, id is item data */
	virtual void print_id(int num, ID &id) = 0;
	/* copy item data */
	virtual void copy_id(ID &ids, ID &idd) = 0;

protected:

	/* item list */
	ItemList m_il;
	/* item count */
	int m_ic;
};

template <typename ID>
ItemQueueT<ID>::ItemQueueT()
{
	m_il.clear();
	m_ic = 0;
}

template <typename ID>
ItemQueueT<ID>::~ItemQueueT()
{
	m_il.clear();
	m_ic = 0;
}

/* push item data,  return current count, -1 for failed */
template <typename ID>
int ItemQueueT<ID>::push_item(ID &id, int t)
{
	if((unsigned int)(++ m_ic) == m_il.max_size())
	{
		-- m_ic;
		return -1;
	}
	else
	{
		Item item;
		item.id = id;
		copy_id(id, item.id);
		item.time = t;
		m_il.push_back(item);
	}

	return m_ic;
}

/* check item count, return count from now to now-period */
template <typename ID>
int ItemQueueT<ID>::check_item(int now, int period)
{
	int total = 0;
	for(typename ItemList::reverse_iterator riter = m_il.rbegin(); riter != m_il.rend(); ++ riter)
	{
		if(now - riter->time > period)
		{
			break;
		}

		++ total;
	}

	return total;
}

/* clear all items, return current count, -1 for failed */
template <typename ID>
int ItemQueueT<ID>::clear()
{
	m_il.clear();
	m_ic = 0;

	return m_ic;
}

/* clear timeout itmes(< now - timeout), return current count, -1 for failed */
template <typename ID>
int ItemQueueT<ID>::clear_timeout(int now, int timeout)
{
	typename ItemList::iterator begin = m_il.begin();
	typename ItemList::iterator end = m_il.end();
	typename ItemList::iterator iter = begin;
	while((iter != end) && (now - iter->time > timeout))
	{
		++ iter;
		m_ic --;
	}

	if(iter != begin)
	{
		m_il.erase(begin, iter);
	}

	return m_ic;
}

/* print item for now to now-period */
template <typename ID>
void ItemQueueT<ID>::print_item(int now, int period)
{
	int num = 1;
	for(typename ItemList::reverse_iterator riter = m_il.rbegin(); riter != m_il.rend(); ++ riter)
	{
		if(now - riter->time > period)
		{
			break;
		}
		print_id(num, riter->id);

		++ num;
	}

	return ;
}

/* current count */
template <typename ID>
int ItemQueueT<ID>::get_current_count()
{
	return m_ic;
}

#endif

/*******************EOF***********************************/
