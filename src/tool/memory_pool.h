/*
* poll.h
*
*  Created on: 2015年9月1日
*      Author: woqucc
*/

#ifndef MEMORY_POLL_H_
#define MEMORY_POLL_H_
#include<cstdlib>
#include<iostream>
#include<new>
namespace myml
{
	/**
	* 内存池类，用于一次性分配的大量内存的管理。
	* */

	template<class T>
	class memory_pool
	{

	private:
		typedef struct memory_struct
		{
			T t;
			struct memory_struct* next_free;
		} memory_struct;
		const size_t _max_size;
		memory_struct* _block_start, *_block_end;
		memory_struct* _free_head;
		memory_struct* _new;                    //the last allocated memory's pointer
		memory_struct* _delete;                 //the last recovered memory's pointer
	public:
		size_t size;	
		/**< 内存池大小*/
		/**
		* 构造函数
		* @param max_size 内存池大小
		* */
		memory_pool(size_t max_size);
		~memory_pool();
		/**
		* 从内存池中分配新内存
		* @return 分配的新内存
		* */
		T* pool_new();
		/**
		* 将无用的内存归还给内存池
		*@param t 要删除的内存对象地址
		*@return 删除成功 true
		*@return 删除失败 false
		* */
		bool pool_delete(T* t);
	};
	template<class T>
	memory_pool<T>::memory_pool(size_t max_size) :
		size(0), _free_head(NULL), _new(NULL), _delete(NULL), _max_size(max_size)
	{
		_block_start = new memory_struct[_max_size]();
		_block_end = _block_start + _max_size - 1;
	}
	template<class T>
	memory_pool<T>::~memory_pool()
	{
		delete[](_block_end - _max_size + 1);
	}
	template<class T>
	T* memory_pool<T>::pool_new()
	{

		if (_free_head > 0)
		{
			_new = _free_head;
			_free_head = (memory_struct*)_free_head->next_free;
			memset(_new, 0, sizeof(memory_struct));
			return new(_new)T;
		}

		else
		{
			if (_block_start <= _block_end)
			{
				_block_start++;
				return new(_block_start - 1)T;
			}
			return NULL;
		}
	}
	template<class T>
	bool memory_pool<T>::pool_delete(T* t)
	{

		_delete = reinterpret_cast<memory_struct*>(t);
		//cout << _delete << " " << _free_head << " " << _delete->next_free << endl;
		if ((_delete->next_free == NULL && _delete != _free_head) || _free_head == NULL)
		{
			_delete->next_free = _free_head;
			_free_head = _delete;
			return true;
		}
		else
		{
			return false;
		}

	}
}
#endif /* POLL_H_ */
