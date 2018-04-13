/* File Name: item_pool_key_T.h
 *
 * Description: item pool by key
 *
 * Created by henuyx on 2015-06-09
 *
 */

#ifndef __ITEM_POOL_KEY_T_H__
#define __ITEM_POOL_KEY_T_H__

/*******************INCLUDE*******************************/
#include <string>
#include <ext/hash_map>

/*******************GLOBAL********************************/

#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
#else
template <typename ITEM>
#endif
class ItemPoolKeyT
{
public:
	// item info
	typedef struct _ITEM_INFO
	{
		struct _ITEM_INFO *prev;
		struct _ITEM_INFO *next;
		int idx;
		std::string key;

		ITEM item;
	} ItemInfo;

	// hash map: key->idx
	struct str_hash
	{
		size_t operator()(const std::string &str) const
		{
			return __gnu_cxx::__stl_hash_string(str.c_str());
		}
	};
	typedef __gnu_cxx::hash_map<std::string, int, str_hash> KeyPosMap;

public:
	ItemPoolKeyT();
	~ItemPoolKeyT();

public:
	/* get free idx */
	int get_free_idx(std::string key);
	/* get used idx by key, return idx >=0, -1 for failed */
	int get_used_idx(std::string key);
	/* get idx */
	int get_idx(std::string key);
	/* get item by idx */
	ITEM* get_item(int idx);
	/* free used item */
	void free_used_item(int idx);

	/* init pool */
#ifdef _ITME_POOL_SIZE
private:
	void init_pool();
#else
public:
	void init_pool(int pool_size);
#endif

protected:
	// key-idx map
	KeyPosMap m_key_idx_map;
	// pool

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
ItemPoolKeyT<ITEM, SIZE>::ItemPoolKeyT()
#else
template <typename ITEM>
ItemPoolKeyT<ITEM>::ItemPoolKeyT()
#endif
{
	m_init_flag = false;
	m_key_idx_map.clear();
	m_free_head = NULL;
	m_free_tail = NULL;

#ifdef _ITME_POOL_SIZE
	init_pool();
#endif
}

#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
ItemPoolKeyT<ITEM, SIZE>::~ItemPoolKeyT()
#else
template <typename ITEM>
ItemPoolKeyT<ITEM>::~ItemPoolKeyT()
#endif
{
	m_key_idx_map.clear();
}

/* init pool */
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
void ItemPoolKeyT<ITEM, SIZE>::init_pool()
#else
template <typename ITEM>
void ItemPoolKeyT<ITEM>::init_pool(int pool_size)
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
	// prev = cur - 1; next = cur + 1;
	for(int i = 1; i < m_pool_size - 1; i ++)
	{
		m_ii_pool[i].prev = &m_ii_pool[i-1];
		m_ii_pool[i].next = &m_ii_pool[i+1];
		m_ii_pool[i].idx = i;
	}

	// head
	m_ii_pool[0].prev = NULL;
	m_ii_pool[0].next= &m_ii_pool[1];
	m_ii_pool[0].idx = 0;

	// tail
	m_ii_pool[m_pool_size - 1].prev = &m_ii_pool[m_pool_size - 2];
	m_ii_pool[m_pool_size - 1].next = NULL;
	m_ii_pool[m_pool_size - 1].idx = m_pool_size - 1;

	// free head, tail
	m_free_head = &m_ii_pool[0];
	m_free_tail = &m_ii_pool[m_pool_size - 1];

	m_init_flag = true;
}

/* get free idx */
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
int ItemPoolKeyT<ITEM, SIZE>::get_free_idx(std::string key)
#else
template <typename ITEM>
int ItemPoolKeyT<ITEM>::get_free_idx(std::string key)
#endif
{
	// always keep one left for free
	if(m_free_head == m_free_tail)
	{
		return -1;
	}

	//m_key_idx_map.insert(std::pair<std::string, int>(key, m_free_head->idx));
	m_key_idx_map[key] = m_free_head->idx;
	m_free_head->key = key;

	m_free_head = m_free_head->next;
	return (m_free_head->prev->idx);
}

/* get used idx by key, return idx >=0, -1 for failed */
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
int ItemPoolKeyT<ITEM, SIZE>::get_used_idx(std::string key)
#else
template <typename ITEM>
int ItemPoolKeyT<ITEM>::get_used_idx(std::string key)
#endif
{
	typename KeyPosMap::iterator it = m_key_idx_map.find(key);
	if(m_key_idx_map.end() != it)
	{
		return it->second;
	}

	return -1;
}

/* get idx, return idx >=0, -1 for failed */
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
int ItemPoolKeyT<ITEM, SIZE>::get_idx(std::string key)
#else
template <typename ITEM>
int ItemPoolKeyT<ITEM>::get_idx(std::string key)
#endif
{
	int idx = get_used_idx(key);
	if(-1 == idx)
	{
		return get_free_idx(key);
	}

	return idx;
}

/* get item by idx */
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
ITEM* ItemPoolKeyT<ITEM, SIZE>::get_item(int idx)
#else
template <typename ITEM>
ITEM* ItemPoolKeyT<ITEM>::get_item(int idx)
#endif
{
	if((idx >= 0) && (idx < m_pool_size))
	{
		return &(m_ii_pool[idx].item);
	}

	return NULL;
}

/* free used item */
#ifdef _ITME_POOL_SIZE
template <typename ITEM, int SIZE>
void ItemPoolKeyT<ITEM, SIZE>::free_used_item(int idx)
#else
template <typename ITEM>
void ItemPoolKeyT<ITEM>::free_used_item(int idx)
#endif
{
	m_key_idx_map.erase(m_ii_pool[idx].key);
	m_ii_pool[idx].key.clear();
	m_ii_pool[idx].next = NULL;
	m_ii_pool[idx].prev = m_free_tail;
	m_free_tail->next = &m_ii_pool[idx];
	m_free_tail = &m_ii_pool[idx];
}

#endif

/*******************EOF***********************************/
