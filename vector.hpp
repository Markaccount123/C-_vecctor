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

	//����ȥ���ã���������ȡ�������Զ�pos���λ�ý����޸�
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
			_start = tmp;//��ʱ���¿ռ��ͷβ�ȶ�Ҫ����
			//����㲻��_finish��_endofstorage��������ô���������ͻ��ΪҰָ��
			_finish = _start + sz; //��������Ϊ_start���µģ�����_finish��ԭ���ģ���ʱһ���ټ���_start�ͱ�Ϊ0�ˣ�
			//������Ҫ����ԭ����size()��С
			_endofstorage = _start + n;
		}
	}

	void resize(size_t n, const T& val = T())
	{
		//resize�ǲ������ռ�ģ��������ǿ��Բ�ȡһЩ����ǿ�Ƶ����ռ�Ĵ�С��������һ���ֲ������潨��һ��tmp����ʱ����Ȼ�󽻻�
		if (n > capacity())
			reserve(n);

		if (n < size()) // ����ǻ�ͼ�ĵ�һ�����
		{
			_finish = _start + n;
		}
		else
		{
			//����ǵڶ��������û�г���capacity�Ĵ�С�����ǳ�����size�Ĵ�С
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
		//ֻҪ�ǲ����뵽�ĵ�һ�������Ӧ���ǿռ乻����
		check_capacity();
		*_finish = x;
		_finish++;
	}

	void pop_back()
	{
		assert(_finish > _start);
		--_finish;
	}
	//�������ӿ��п��ܻ���ɵ�����ʧЧ������
	//�����ڹٷ���stl����ʵ�ǽ����������⣬ֻ����ͨ���Ĳ��÷���ֵ�ķ�ʽ,
	//���ص��²�������λ�õĵ����������տ��Խ��������ʧЧ������
	iterator insert(iterator pos, const T& x)
	{
		assert(pos >= _start && pos <= _finish);
		size_t posi = pos - _start;
		//ֻҪ���ݣ���ôpos�������ض�ʧЧ
		check_capacity();
		//����Ҳ���������׻᲻��ʧЧ�������ˣ�ֱ�����°�pos��λ�ø�һ��
		pos = _start + posi;
		//����Ҫ����Ų������Ȼ�ᵼ�����ݵĸ���
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