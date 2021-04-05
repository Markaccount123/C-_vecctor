#pragma once 
#include<assert.h>

namespace wzy
{
template<class T>
class vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const_iterator begin()const
	{
		return _start;
	}

	const_iterator end()const
	{
		return _finish;
	}
	vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{

	}

	~vector()
	{
		delete[] _start;
		_start = _finish = _endofstorage = nullptr;
	}

	template<class InputIterator>
	vector(InputIterator first, InputIterator last)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		reserve(last - first);
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}


	void swap(vector<T>& v)
	{
		std::swap(_start, v._start);
		std::swap(_finish, v._finish);
		std::swap(_endofstorage, v._endofstorage);
	}


	vector(const vector<T>& v)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		vector tmp(v.begin(), v.end());
		swap(tmp);
	}

	vector<T>& operator=(vector<T> v)
	{
		swap(v);
		return v;
	}
	size_t capacity()
	{
		return _endofstorage - _start;
	}

	size_t size()
	{
		return _finish - _start;
	}

	//这里去引用，不但可以取到还可以对pos这个位置进行修改
	T& operator[](size_t pos)
	{
		assert(pos < size());
		return _start[pos];
	}

	void reserve(size_t n)
	{
		if (n > capacity())
		{
			size_t sz = size();
			T* tmp = new T[n];
			memcpy(tmp, _start, sizeof(T)*size());
			delete[] _start;
			_start = tmp;//此时把新空间的头尾等都要给他
			//如果你不把_finish和_endofstorage给他，那么他们两个就会成为野指针
			_finish = _start + sz; //这里是因为_start是新的，但是_finish是原来的，此时一减再加上_start就变为0了，
			//所以需要保留原来的size()大小
			_endofstorage = _start + n;
		}
	}

	void resize(size_t n, const T& val = T())
	{
		//resize是不能缩空间的，但是我们可以采取一些方法强制的缩空间的大小，就是在一个局部域里面建立一个tmp的临时对象，然后交换
		if (n > capacity())
			reserve(n);

		if (n < size()) // 这就是画图的第一种情况
		{
			_finish = _start + n;
		}
		else
		{
			//这就是第二种情况，没有超过capacity的大小，但是超过了size的大小
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}
	}

	void check_capacity()
	{
		if (_finish == _endofstorage)
		{
			size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
			reserve(newcapacity);
		}
	}

	void push_back(const T& x)
	{
		//只要是插入想到的第一个问题就应该是空间够不够
		check_capacity();
		*_finish = x;
		_finish++;
	}

	void pop_back()
	{
		assert(_finish > _start);
		--_finish;
	}
	//这两个接口有可能会造成迭代器失效的问题
	//但是在官方的stl中其实是解决了这个问题，只不过通过的采用返回值的方式,
	//返回的新插入数据位置的迭代器，接收可以解决迭代器失效的问题
	iterator insert(iterator pos, const T& x)
	{
		assert(pos >= _start && pos <= _finish);
		size_t posi = pos - _start;
		//只要增容，那么pos迭代器必定失效
		check_capacity();
		//所以也不管他到底会不会失效的问题了，直接重新把pos的位置给一下
		pos = _start + posi;
		//必须要倒着挪动，不然会导致数据的覆盖
		iterator end = _finish - 1;
		while (end >= pos)
		{
			*(end + 1) = *end;
			--end;
		}
		*pos = x;
		++_finish;
		return pos;
	}
	iterator earse(iterator pos)
	{
		assert(pos >= _start && pos <= _finish);
		iterator it = pos + 1;
		while (it != _finish)
		{
			*(it - 1) = *it;
			++it;
		}
		--_finish;
		return pos;
	}
private:

	iterator _start;
	iterator _finish;
	iterator _endofstorage;
};
}