/***************************************************************************************
* std::map; std::muitlmap;
* template < class Key,                                     // map::key_type
             class T,                                       // map::mapped_type
             class Compare = less<Key>,                     // map::key_compare
             class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
             > class map;
* 说明：
* map是一种关联容器，其中的元素由key和value构成的键值对来组成；

* 在map中，key是有序排列的，key和value的类型可能不同，但一起组合成一种value_type类型：
		typedef pair<const Key, T> value_type;

* map中的值可以通过[]操作符直接访问

* map通常由二叉搜索树实现，读写操作O(logN）
* unorder_map通常由hashing实现，具备常数级的读写速度，

****************************************************************************************/

#include <iostream>
#include <map>
#include <string>
using namespace std;

template <typename T>
bool fncomp(T lhs, T rhs) { return lhs < rhs; }

template <typename T>
struct classcomp {
	bool operator() (const T& lhs, const T& rhs) const
	{
		return lhs < rhs;
	}
};

template <typename KeyType, typename ValType>
void showMap(std::map<KeyType, ValType> theMap)
{
	for (auto x : theMap) cout << x.first << " => " << x.second << endl;
}

int main()
{
    std::cout << "Hello Map!\n";

	/**---------------------------------------------------------------------------------------------------
	* 构造方式
	*/
	std::map<char, int> first;

	first['a'] = 10;
	first['c'] = 50;
	first['b'] = 30;
	first['d'] = 70;

	std::map<char, int> second(first.begin(), first.end());  //默认会按照 'a'->'b'->'c'->'d'的顺序储存

	std::map<char, int> third(second);

	std::map<char, int, classcomp<char>> fourth;                 // class as Compare

	bool(*fn_pt)(char, char) = fncomp;
	std::map<char, int, bool(*)(char, char)> fifth(fn_pt); // function pointer as Compare

	/*通过操作符 = */
	second = first;                 // second now equal first
	first = std::map<char, int>();  // now first is now empty

	/**---------------------------------------------------------------------------------------------------
	* 插入:	map.insert(pair<keyType, valueType>(key, value)); 
			map[key] = value
	*/
	std::map<char, int> mymap;

	// first insert function version (single parameter):
	// insert 返回类型：std::pair<std::map<xxx, xxx>::iterator, bool>
	mymap.insert(std::pair<char, int>('a', 100));
	mymap.insert(std::pair<char, int>('z', 200));

	std::pair<std::map<char, int>::iterator, bool> ret;
	ret = mymap.insert(std::pair<char, int>('z', 500));
	if (ret.second == false)							//ret.first 为插入位置的iter, ret.second 为是否已存在的判断
	{
		std::cout << "element "<< ret.first->first <<" already existed";
		std::cout << " with a value of " << ret.first->second << '\n';	//ret.firs->second 为value

	}

	// second insert function version (with hint position): //通过认为提示位置插入
	std::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, std::pair<char, int>('b', 300));  // max efficiency inserting(事先知道紧挨着 'a')
	mymap.insert(it, std::pair<char, int>('c', 400));  // no max efficiency inserting(不如直接默认二叉树来插入划算）

	// third insert function version (range insertion):
	std::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));  //从开头，到'c'的位置，复制元素

	// showing contents:
	std::cout << "mymap contains:\n";
	showMap(mymap);

	std::cout << "anothermap contains:\n";
	showMap(anothermap);

	/**---------------------------------------------------------------------------------------------------
	* 删除:	erase(key)
			erase(iterator)
			erase(range)
	*/
	std::map<string, int> mapToErase;
	std::map<string, int>::iterator erase_it;
	mapToErase["alex"] = 18800000000;  //通过[]操作符插入
	mapToErase["john"] = 18811111111;
	mapToErase["luke"] = 18322222222;
	mapToErase["jerry"] = 18233333333;
	mapToErase["Tom"] = 18044444444;
	mapToErase["Richard"] = 18655555555;
	std::cout << "what we have in mapToErase:\n";
	showMap(mapToErase);

	mapToErase.erase("jerry");          //通过key删除

	erase_it = mapToErase.find("john"); // 通过迭代器删除
	mapToErase.erase(erase_it);

	erase_it = mapToErase.find("Tom");	// 范围删除
	mapToErase.erase(erase_it, mapToErase.end());

	std::cout << "what we have after erase:\n";
	showMap(mapToErase);

	/**---------------------------------------------------------------------------------------------------
	* 容量：大小、判空
	*/
	cout << "\nmymap size: " << mymap.size() << endl;
	cout << "mymap max_size: " << mymap.max_size() << endl;
	cout << "mymap is empty? "<< (mymap.empty() ? "true" : "false") << endl;

	/**---------------------------------------------------------------------------------------------------
	* 操作: find, count等
	*/
	std::map<char, int>::iterator itf = mymap.find('c');
	cout << "\nfind 'c': " << ((itf == mymap.end()) ? -1 : itf->second) << endl;  //如果find()返回 mymap.end(), 表示没找到；否则输入找到的元素。

	cout << "map 中20的个数：" << mymap.count(20) << endl;  //因为map元素都是独一无二的，所以要么1，要么0

	/**---------------------------------------------------------------------------------------------------
	* multiMap: 相同元素操作
	*/

	std::multimap<char, int> mymm;
	std::multimap<char, int>::iterator mmit, itlow, itupper;

	mymm.insert(std::pair<char, int>('a', 10));
	mymm.insert(std::pair<char, int>('b', 20));
	mymm.insert(std::pair<char, int>('b', 30));
	mymm.insert(std::pair<char, int>('b', 40));
	mymm.insert(std::pair<char, int>('c', 50));
	mymm.insert(std::pair<char, int>('c', 60));
	mymm.insert(std::pair<char, int>('d', 60));

	std::cout << "\nmymm contains:\n";
	for (char ch = 'a'; ch <= 'd'; ch++)
	{
		std::pair <std::multimap<char, int>::iterator, std::multimap<char, int>::iterator> mmret;
		mmret = mymm.equal_range(ch);  //当ch==b时， mmret->first指向('b', 20)， mmret->second指向('c', 50))
		std::cout << ch << " =>";
		for (mmit = mmret.first; mmit != mmret.second; ++mmit)
			std::cout << ' ' << mmit->second;
		std::cout << '\n';
	}

	itlow = mymm.lower_bound('b');   //指向 'b' 的下边界闭区间，也就是[ ('b', 20)
	itupper = mymm.upper_bound('b'); //指向 'b' 的上边界开区间， 也就是('c', 50) )

	//藉此，我们也可以得到key == 'b'的所有元素
	cout << endl << "key 为b的所有值：";
	for (mmit = itlow; mmit != itupper; ++mmit)cout << mmit->second << " ";


	return 0;
}


