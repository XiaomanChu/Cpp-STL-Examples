/********************************************************************************************
* 说明: std::set, std::multiset, std::unordered_set, std::unordered_multiset
*
*	template < class T,                        // set::key_type/value_type
			   class Compare = less<T>,        // set::key_compare/value_compare
			   class Alloc = allocator<T>      // set::allocator_type
			   > class set;

*	在一个set中，元素的value也可以标识它（该value本身是T类型的key），并且每个值都必须是唯一的。 

*	set中的元素添加后不能修改（元素始终为const），但可以通过把它删除，再添入新元素来改变。

*	在set内部，元素总是按照其内部比较对象（类型为Compare）进行排序, 默认从小到大排序。

*	set 通过自平衡二叉搜索树来实现

*	multiset跟set差别不大，区别是可以接收重复元素

*   unordered_set 由链表实现

*********************************************************************************************/
#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;

bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp {
	bool operator() (const int& lhs, const int& rhs) const
	{
		return lhs < rhs;
		//return lhs > rhs; //从大到小
	}
};

void showSet(std::set<int> theSet)
{
	//std::set<int>::iterator it;
	//for (it = theSet.begin(); it != theSet.end(); ++it)
	//	std::cout << ' ' << *it;
	//std::cout << '\n';
	for (auto x : theSet)std::cout << x << " ";
	std::cout << std::endl;
}
void showMultiSet(std::multiset<int> theSet)
{
	for (auto x : theSet)std::cout << x << " ";
	std::cout << std::endl;
}

int main()
{
	std::cout << "Hello Set!\n";
	/**---------------------------------------------------------------------------------------------------
	* 构造方式
	*/
	std::set<int> first;                           // empty set of ints

	int myints[] = { 10,20,30,40,50 };
	std::set<int> second(myints, myints + 5);        // 通过range构造

	std::set<int> third(second);                  // a copy of second，通过copy构造

	std::set<int> fourth(second.begin(), second.end());  // iterator ctor.通过迭代器构造

	std::set<int, std::greater<int>> fifth(myints, myints + 5);  //内部从大到小排序


	/*自定义构造比较方式*/
	std::set<int, classcomp> sixth(myints, myints + 5);                 // class as Compare, 通过类

	bool(*fn_pt)(int, int) = fncomp;
	std::set<int, bool(*)(int, int)> seventh(fn_pt);  // function pointer as Compare，通过函数指针

	/*操作符 = */
	first = second;                          // now second contains the 5 ints
	first = std::set<int>();                 // now first is empty

	/**---------------------------------------------------------------------------------------------------
	* 修改：插入、删除
	*/
	std::set<int> myset, tempset;
	std::set<int>::iterator it;
	std::pair<std::set<int>::iterator, bool> ret;

	// set some initial values:
	for (int i = 1; i <= 5; ++i) myset.insert(i * 10);    // set: 10 20 30 40 50

	tempset = myset;

	ret = myset.insert(20);               // no new element inserted, set 不能插入重复元素

	if (ret.second == false) it = ret.first;  // "it" now points to element 20

	myset.insert(it, 25);                 // max efficiency inserting
	myset.insert(it, 24);                 // max efficiency inserting
	myset.insert(it, 26);                 // no max efficiency inserting

	int myints_1[] = { 5,10,15 };              // 10 already in set, not inserted
	myset.insert(myints, myints + 3);

	std::cout << "myset contains:";
	showSet(myset);

	cout << "myset erase 25: ";
	myset.erase(25);  //删除25；
	showSet(myset);

	cout << "temp set:";
	showSet(tempset);

	cout << "\nswap myset & tempset\n";
	myset.swap(tempset);	//交换两个set
	showSet(myset);
	showSet(tempset);
	
	tempset.clear();  //清除

	cout << "emplace 25: ";
	myset.emplace(20);  //C++ 11 方法
	showSet(myset);

	/**---------------------------------------------------------------------------------------------------
	* 容量：大小、判空
	*/
	cout << "myset size: " << myset.size() << endl; //实际容量
	cout << "myset maxe_size: " << myset.max_size() << endl;  //最大容量
	cout << "myset is empty?：" << (myset.empty()? "true":"false") << endl;

	/**---------------------------------------------------------------------------------------------------
	* 迭代: 正向、反向
	*/
	std::cout << "\nmyset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)  
		std::cout << ' ' << *it;

	std::cout << "\nmyset contains(revert output):";
	std::set<int>::reverse_iterator rit;
	for (rit = myset.rbegin(); rit != myset.rend(); ++rit)   //如果是从小到大排序，则反过来输出
		std::cout << ' ' << *rit;

	/**---------------------------------------------------------------------------------------------------
	* 操作: find, count等
	*/
	std::set<int>::iterator itf = myset.find(25);
	cout <<"\nfind 25: " <<( (itf==myset.end())? -1 : *itf ) << endl;  //如果find()返回 myset.end(), 表示没找到；否则输入找到的元素。
	
	cout << "set 中20的个数：" << myset.count(20) << endl;  //因为set元素都是独一无二的，所以要么1，要么0

	/**---------------------------------------------------------------------------------------------------
	* multiset
	*/
	std::multiset<int> myMultiset(second.begin(), second.end());
	myMultiset.insert(20);
	myMultiset.emplace(20);
	cout << "\nMultiSet: ";
	showMultiSet(myMultiset);
	cout << "multiset 中20的个数：" << myMultiset.count(20) << endl;

	/**---------------------------------------------------------------------------------------------------
	* unordered_set, unordered_multiset 不排序的set
	*/
	std::unordered_set<int> unset({ 5, 2, 3, 6 });
	std::unordered_multiset<int> unmultiset({ 5, 2, 2, 2, 3, 6 });
	cout << "\n unordered_set: ";
	for (auto x : unset)cout << x <<" ";
	cout << "\n unordered_multiset: ";
	for (auto x : unmultiset)cout << x << " ";

	return 0;
}



