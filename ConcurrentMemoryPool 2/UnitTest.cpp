#include "Common.h"
#include "PageCache.h"
#include "ConcurrentAlloc.h"
//
//void TestSize()
//{
//	/*cout << SizeClass::Index(10) << endl;
//	cout << SizeClass::Index(16) << endl;
//	cout << SizeClass::Index(128) << endl;
//	cout << SizeClass::Index(129) << endl;
//	cout << SizeClass::Index(128 + 17) << endl;
//	cout << SizeClass::Index(1025) << endl;
//	cout << SizeClass::Index(1024 + 129) << endl;
//	cout << SizeClass::Index(8*1024+1) << endl;
//	cout << SizeClass::Index(8*1024 + 1024) << endl;
//	*/
//
//	cout << SizeClass::Roundup(10) << endl;
//	cout << SizeClass::Roundup(1025) << endl;
//	cout << SizeClass::Roundup(1024*8+1) << endl;
//
//	cout << SizeClass::NumMovePage(16) << endl;
//	cout << SizeClass::NumMovePage(1024) << endl;
//	cout << SizeClass::NumMovePage(1024*8) << endl;
//	cout << SizeClass::NumMovePage(1024*64) << endl;
//
//}
//
//void Alloc(size_t n)
//{
//	size_t begin1 = clock();
//	std::vector<void*> v;
//	for (size_t i = 0; i < n; ++i)
//	{
//		v.push_back(ConcurrentAlloc(10));
//	}
//
//	//v.push_back(ConcurrentAlloc(10));
//
//	for (size_t i = 0; i < n; ++i)
//	{
//		ConcurrentFree(v[i], 10);
//		cout << v[i] << endl;
//	}
//	v.clear();
//	size_t end1 = clock();
//
//	size_t begin2 = clock();
//	cout << endl << endl;
//	for (size_t i = 0; i < n; ++i)
//	{
//		v.push_back(ConcurrentAlloc(10));
//	}
//
//	for (size_t i = 0; i < n; ++i)
//	{
//		ConcurrentFree(v[i], 10);
//		cout << v[i] << endl;
//	}
//	v.clear();
//	size_t end2 = clock();
//
//	cout << end1 - begin1 << endl;
//	cout << end2 - begin2 << endl;
//}
//
//void TestThreadCache()
//{
//	std::thread t1(Alloc, 1000000);
//	//std::thread t2(Alloc, 5);
//	//std::thread t3(Alloc, 5);
//	//std::thread t4(Alloc, 5);
//
//	t1.join();
//	//t2.join();
//	//t3.join();
//	//t4.join();
//
//}
//
//void TestCentralCache()
//{
//	std::vector<void*> v;
//	for (size_t i = 0; i < 8; ++i)
//	{
//		v.push_back(ConcurrentAlloc(10));
//	}
//
//	for (size_t i = 0; i < 8; ++i)
//	{
//		//ConcurrentFree(v[i], 10);
//		cout << v[i] << endl;
//	}
//}
//
//void TestPageCache()
//{
//	PageCache::GetInstance()->NewSpan(2);
//}
//
//int main()
//{
//	//TestSize();
//	//TestThreadCache();
//	//TestCentralCache();
//	//TestPageCache();
//
//	//void* ptr = VirtualAlloc(0, (2)*(1 << PAGE_SHIFT),
//	//	MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//	//PageID id = (PageID)ptr >> PAGE_SHIFT;
//	//cout << id << endl;
//
//	//char* obj = (char*)ptr + 100;
//	//PageID objid = (PageID)obj >> PAGE_SHIFT;
//	//void* pageptr = (void*)(id << PAGE_SHIFT);
//	//cout << pageptr << endl;
//	//cout << ptr << endl;
//
//	return 0;
//}

void BenchmarkMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	size_t malloc_costtime = 0;
	size_t free_costtime = 0;
	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&, k]() {
			std::vector<void*> v;
			v.reserve(ntimes);
			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(malloc(16));
				}
				size_t end1 = clock();
				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					free(v[i]);
				}
				size_t end2 = clock();
				v.clear();
				malloc_costtime += end1 - begin1;
				free_costtime += end2 - begin2;
			}
		});
	}
	for (auto& t : vthread)
	{
		t.join();
	}
	printf("%u个线程并发执行%u轮次，每轮次malloc %u次: 花费：%u ms\n", nworks, rounds, ntimes, malloc_costtime);
	printf("%u个线程并发执行%u轮次，每轮次free %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, free_costtime);
	printf("%u个线程并发malloc&free %u次，总计花费：%u ms\n",
		nworks, nworks*rounds*ntimes, malloc_costtime + free_costtime);
}
// 单轮次申请释放次数 线程数 轮次
void BenchmarkConcurrentMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	size_t malloc_costtime = 0;
	size_t free_costtime = 0;
	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&]() {
			std::vector<void*> v;
			v.reserve(ntimes);
			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(ConcurrentAlloc(16));
				}
				size_t end1 = clock();
				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					ConcurrentFree(v[i],sizeof(v[i]));
				}
				size_t end2 = clock();
				v.clear();
				malloc_costtime += end1 - begin1;
				free_costtime += end2 - begin2;
			}
		});
	}
	for (auto& t : vthread)
	{
		t.join();
	}
	printf("%u个线程并发执行%u轮次，每轮次concurrent alloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, malloc_costtime);
	printf("%u个线程并发执行%u轮次，每轮次concurrent dealloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, free_costtime);
	printf("%u个线程并发concurrent alloc&dealloc %u次，总计花费：%u ms\n",
		nworks, nworks*rounds*ntimes, malloc_costtime + free_costtime);
}
int main()
{
	cout << "==========================================================" << endl;
	BenchmarkMalloc(100000, 4, 10);
	cout << endl << endl;
	BenchmarkConcurrentMalloc(100000, 4, 10);
	cout << "==========================================================" << endl;
	system("pause");
	return 0;
}