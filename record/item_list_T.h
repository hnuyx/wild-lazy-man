/* File Name: item_list_T.h
 *
 * Description: item list, based on "item_pool_T.h"
 *
 * Created by henuyx on 2015-06-04
 *
 */

#ifndef __ITEM_LIST_T_H__
#define __ITEM_LIST_T_H__

/*******************INCLUDE*******************************/
#include "item_pool_T.h"

/*******************GLOBAL********************************/

#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
#else
template <typename ITEM>
#endif
class ItemListT
{
public:
#ifdef _ITME_POO_SIZE
	typedef ItemPoolT<ITEM, SIZE> POOL_MANAGER;
#else
	typedef ItemPoolT<ITEM> POOL_MANAGER;
#endif

public:
	ItemListT();
	virtual ~ItemListT();

	// push item at front, return 0 for success, -1 for failed
	int push_item_front(ITEM &item);
	// push item at back, return 0 for success, -1 for failed
	int push_item_back(ITEM &item);
	// pop item from front
	void pop_item_front();
	// pop item from back
	void pop_item_back();
	// clear all items
	void clear();
	// is empty, return true for empty, false for not empty
	bool is_empty();

#ifdef _ITME_POO_SIZE
#else
	// init pool size
	static void init_pool(int pool_size);
#endif

protected:
	typename POOL_MANAGER::ItemInfo *m_head;
	typename POOL_MANAGER::ItemInfo *m_tail;

	static POOL_MANAGER m_item_pool;
};

#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
typename ItemListT<ITEM, SIZE>::POOL_MANAGER ItemListT<ITEM, SIZE>::m_item_pool;
#else
template <typename ITEM>
typename ItemListT<ITEM>::POOL_MANAGER ItemListT<ITEM>::m_item_pool;
#endif

#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
ItemListT<ITEM, SIZE>::ItemListT()
#else
template <typename ITEM>
ItemListT<ITEM>::ItemListT()
#endif
{
	m_head = NULL;
	m_tail = NULL;
}

#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
ItemListT<ITEM, SIZE>::~ItemListT()
#else
template <typename ITEM>
ItemListT<ITEM>::~ItemListT()
#endif
{
}

// push item, return 0 for success, -1 for failed
#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
int ItemListT<ITEM, SIZE>::push_item_front(ITEM &item)
#else
template <typename ITEM>
int ItemListT<ITEM>::push_item_front(ITEM &item)
#endif
{
	typename POOL_MANAGER::ItemInfo *new_item = m_item_pool.get_item();
	if(NULL == new_item)
	{
		return -1;
	}

	new_item->item = item;

	if(NULL == m_head && NULL == m_tail)
	{
		m_head = new_item;
		m_tail = new_item;
	}
	else
	{
		new_item->next = m_head;
		m_head->prev = new_item;
		m_head = new_item;
	}

	return 0;
}

// push item, return 0 for success, -1 for failed
#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
int ItemListT<ITEM, SIZE>::push_item_back(ITEM &item)
#else
template <typename ITEM>
int ItemListT<ITEM>::push_item_back(ITEM &item)
#endif
{
	typename POOL_MANAGER::ItemInfo *new_item = m_item_pool.get_item();
	if(NULL == new_item)
	{
		return -1;
	}

	new_item->item = item;

	if((NULL == m_head) &&
		(NULL == m_tail))
	{
		m_head = new_item;
		m_tail = new_item;
	}
	else
	{
		m_tail->next = new_item;
		new_item->prev = m_tail;
		m_tail = new_item;
	}

	return 0;
}

// pop item from front
#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
void ItemListT<ITEM, SIZE>::pop_item_front()
#else
template <typename ITEM>
void ItemListT<ITEM>::pop_item_front()
#endif
{
	// no item
	if((NULL == m_head) &&
		(NULL == m_tail))
	{
		return ;
	}

	// only one item
	if(m_head == m_tail)
	{
		m_item_pool.free_item(m_head);
		m_head = NULL;
		m_tail = NULL;

		return ;
	}

	// free first item
	m_head = m_head->next;
	m_item_pool.free_item(m_head->prev);
	m_head->prev = NULL;

	return ;
}

// pop item from back
#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
void ItemListT<ITEM, SIZE>::pop_item_back()
#else
template <typename ITEM>
void ItemListT<ITEM>::pop_item_back()
#endif
{
	// no item
	if((NULL == m_head) &&
		(NULL == m_tail))
	{
		return ;
	}

	// only one item
	if(m_head == m_tail)
	{
		m_item_pool.free_item(m_tail);
		m_head = NULL;
		m_tail = NULL;

		return ;
	}

	// free back item
	m_tail = m_tail->prev;
	m_item_pool.free_item(m_tail->next);
	m_tail->next = NULL;

	return ;
}

// clear all items
#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
void ItemListT<ITEM, SIZE>::clear()
#else
template <typename ITEM>
void ItemListT<ITEM>::clear()
#endif
{
	while(NULL != m_head)
	{
		typename POOL_MANAGER::ItemInfo *m_tmp = m_head;
		m_head = m_head->next;

		m_item_pool.free_item(m_tmp);
	}

	m_tail = NULL;
}

// is empty, return true for empty, false for not empty
#ifdef _ITME_POO_SIZE
template <typename ITEM, int SIZE>
bool ItemListT<ITEM, SIZE>::is_empty()
#else
template <typename ITEM>
bool ItemListT<ITEM>::is_empty()
#endif
{
	if((NULL == m_head) &&
		(NULL == m_tail))
	{
		return true;
	}

	return false;
}

// init pool size
#ifdef _ITME_POO_SIZE
#else
template <typename ITEM>
void ItemListT<ITEM>::init_pool(int pool_size)
{
	m_item_pool.init_pool(pool_size);
}
#endif

#endif

/*******************EOF***********************************/
