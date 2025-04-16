#include "teste_vector.h"

void test_vector()
{
	MyVector<int> v1;
	assert(v1.Size() == 0);
	assert(v1.Capacity() == 5);

	MyVector<int> v2(7);
	assert(v2.Size() == 0);
	assert(v2.Capacity() == 7);

	v1.push_back(1);
	v1.push_back(2);

	MyVector<int> v3 = v1;
	assert(v3.Size() == 2);
	assert(v3.Capacity() == 5);
	assert(v3.at(0) == 1);
	assert(v3.at(1) == 2);
}

void test_push_back()
{
	MyVector<int> v;
	assert(v.Size() == 0);

	v.push_back(10);
	assert(v.Size() == 1);
	assert(v.at(0) == 10);

	for (int i = 20; i < 30; i++)
		v.push_back(i);
	assert(v.Size() == 11);
}

void test_erase()
{
	MyVector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	assert(v.Size() == 3);

	v.erase(v.begin());
	assert(v.Size() == 2);
	assert(v.at(0) == 2);

	v.erase(v.begin() + 1);
	assert(v.Size() == 1);
	assert(v.at(0) == 2);

	v.erase(v.begin());
	assert(v.Size() == 0);
}

void teste_vector()
{
	test_vector();
	test_push_back();
	test_erase();
	test_iterator();
}

void test_iterator()
{
	MyVector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	assert(v.Size() == 5);

	int sum = 0;
	auto it1 = v.begin();
	while (it1 != v.end())
	{
		sum += *it1;
		++it1;
	}
	assert(sum == 15);

	sum = 0;
	for (const int x : v)
		sum += x;
	assert(sum == 15);

	try {
		v.at(100) = 1;
		assert(false);
	}
	catch (const std::out_of_range&) {
		assert(true);
	}
	
	try {
		auto it = v.begin() + 100;
		it.next();
		assert(false);
	}
	catch (const std::out_of_range&) {
		assert(true);
	}

	try {
		auto it = v.begin();
		for (int i = 0; i < 100; i++)
			it.next();
		assert(false);
	}
	catch (const std::out_of_range&) {
		assert(true);
	}

	MyVector<int> v1 = MyVector<int>(10);
	assert(v1.Capacity() == 10);
	v1 = MyVector<int>(20);
	assert(v1.Capacity() == 20);
}
