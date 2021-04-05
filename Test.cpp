#include"vector.hpp"
#include<iostream>
#include<algorithm>
using namespace std;

void test_vector1()
{
	wzy::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] *= 2;
		cout << v[i] << " ";
	}
	cout << endl;

	wzy::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector2()
{
	wzy::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	v.resize(2);
	for (auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.resize(8);
	for (auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector3()
{
	wzy::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//auto it = std::find(v.begin(), v.end(),3);//或许这是哪个一开始空间的pos位置
 //   it = v.insert(it,40); //这个或许是新开辟的pos的位置

	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;

	////it = v.earse(it);
	//auto eit = v.begin();
	//while (eit != v.end())
	//{
	//	if (*eit % 2 == 0)
	//	{
	//		eit = v.earse(eit);
	//	}
	//	else
	//	{
	//		++eit;
	//	}
	//}

	//for (auto e : v)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;

	wzy::vector<int> copy(v);
	for (auto e : copy)
	{
		cout << e << " ";
	}
	cout << endl;

	wzy::vector<int> fz;
	fz.push_back(5);
	fz.push_back(6);
	fz.push_back(7);
	fz.push_back(8);

	v = fz;

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test_vector1();
	//test_vector2();
	test_vector3();
	return 0;
}