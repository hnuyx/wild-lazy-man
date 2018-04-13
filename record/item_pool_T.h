/* File Name: item_pool_T.h
 *
 * Description: item pool
 *
 * Created by henuyx on 2015-06-04
 *
 */

#ifndef __ITEM_POOL_T_H__
#define __ITEM_POOL_T_H__

/*******************INCLUDE*******************************/
#include <stdio.h>
#include <stdlib.h>

/*******************GLOBAL********************************/

// malloc size or fix size
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
#else
template <typename ITEM>
#endif
class ItemPoolT
{
public:
	// item list
	typedef struct _ITEM_INFO
	{
		struct _ITEM_INFO *prev;
		struct _ITEM_INFO *next;

		ITEM item;
	} ItemInfo;

public:
	ItemPoolT();
	~ItemPoolT();

	// get item
	ItemInfo *get_item();
	// free item
	void free_item(ItemInfo *ii);

#ifdef _ITME_POOL_SIZE
private:
	// init pool
	void init_pool();
#else
public:
	// init pool
	void init_pool(int pool_size);
#endif

private:
#ifdef _ITME_POOL_SIZE
	ItemInfo m_ii_pool[SIZE];
#else
	ItemInfo *m_ii_pool;
#endif

	ItemInfo *m_free_head;
	ItemInfo *m_free_tail;

	int m_pool_size;
	bool m_init_flag;
};

#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
ItemPoolT<ITEM, SIZE>::ItemPoolT()
#else
template <typename ITEM>
ItemPoolT<ITEM>::ItemPoolT()
#endif
{
	m_init_flag = false;
	m_free_head = NULL;
	m_free_tail = NULL;

#ifdef _ITME_POOL_SIZE
	m_pool_size=SIZE;
	init_pool();
#else
	m_ii_pool = NULL;
#endif
}

#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
ItemPoolT<ITEM, SIZE>::~ItemPoolT()
#else
template <typename ITEM>
ItemPoolT<ITEM>::~ItemPoolT()
#endif
{
#ifdef _ITME_POOL_SIZE
#else
	if(NULL != m_ii_pool)
	{
		free(m_ii_pool);
	}
#endif
}

// get item
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
typename ItemPoolT<ITEM, SIZE>::ItemInfo* ItemPoolT<ITEM, SIZE>::get_item()
#else
template <typename ITEM>
typename ItemPoolT<ITEM>::ItemInfo* ItemPoolT<ITEM>::get_item()
#endif
{
	// at least one is not used
	ItemInfo *res = NULL;
	if(m_free_head != m_free_tail)
	{
		res = m_free_head;
		m_free_head = m_free_head->next;
		m_free_head->prev = NULL;

		res->prev = NULL;
		res->next = NULL;
	}

	return res;
}

// free item
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
void ItemPoolT<ITEM, SIZE>::free_item(ItemPoolT<ITEM, SIZE>::ItemInfo *ii)
#else
template <typename ITEM>
void ItemPoolT<ITEM>::free_item(ItemPoolT<ITEM>::ItemInfo *ii)
#endif
{
	if(NULL != ii)
	{
		m_free_tail->next = ii;
		ii->prev = m_free_tail;
		ii->next = NULL;
		memset(&(ii->item), 0, sizeof(ITEM));
		m_free_tail = ii;
	}

	return ;
}

// init pool
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
void ItemPoolT<ITEM, SIZE>::init_pool()
#else
template <typename ITEM>
void ItemPoolT<ITEM>::init_pool(int pool_size)
#endif
{
	if(m_init_flag)
	{
		return ;
	}

#ifdef _ITME_POOL_SIZE
	m_pool_size = SIZE;
#else
	// malloc pool
	m_ii_pool = (ItemInfo *)malloc(sizeof(ItemInfo) * pool_size);
	if(NULL == m_ii_pool)
	{
		return ;
	}
	m_pool_size = pool_size;
#endif

	// init pool, free list
	for(int i = 1; i < m_pool_size - 1; i ++)
	{
		m_ii_pool[i].prev = &(m_ii_pool[i - 1]);
		m_ii_pool[i].next = &(m_ii_pool[i + 1]);
		memset(&(m_ii_pool[i].item), 0, sizeof(ITEM));
	}

	m_ii_pool[0].prev = NULL;
	m_ii_pool[0].next = &(m_ii_pool[1]);
	memset(&(m_ii_pool[0].item), 0, sizeof(ITEM));

	m_ii_pool[m_pool_size - 1].prev = &(m_ii_pool[m_pool_size - 2]);
	m_ii_pool[m_pool_size - 1].next = NULL;
	memset(&(m_ii_pool[m_pool_size - 1].item), 0, sizeof(ITEM));

	m_free_head = &(m_ii_pool[0]);
	m_free_tail = &(m_ii_pool[m_pool_size - 1]);

	m_init_flag = true;
}

#endif

/*******************EOF***********************************/
