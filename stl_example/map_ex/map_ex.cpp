/***************************************************************************************
* std::map; std::muitlmap;
* template < class Key,                                     // map::key_type, 键的类型
             class T,                                       // map::mapped_type, 值的类型
             class Compare = less<Key>,                     // map::key_compare, 比较器
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
#include <exception>
using namespace std;

/*自定义的比较器1，函数指针方式调用，key从大到小排序*/
template <typename T>
bool fncomp(T lhs, T rhs) { return lhs > rhs; }

/*自定义的比较器2，类调用方式，key从大到小排序*/
template <typename T>
struct classcomp {
	bool operator() (const T& lhs, const T& rhs) const
	{
		return lhs > rhs;
	}
};

/*这些是针对不同map构造方式写的打印函数*/
template <typename KeyType, typename ValType>
void showMap(std::map<KeyType, ValType> theMap)
{
	for (auto x : theMap) cout << x.first << " => " << x.second << endl;
}
template <typename KeyType, typename ValType>
void showMap(std::map<KeyType, ValType, classcomp<char> > theMap)
{
	for (auto x : theMap) cout << x.first << " => " << x.second << endl;
}
template <typename KeyType, typename ValType>
void showMap(std::map<KeyType, ValType, bool(*)(char, char) > theMap)
{
	for (auto x : theMap) cout << x.first << " => " << x.second << endl;
}

int main()
{
    std::cout << "Hello Map!\n";

	/**---------------------------------------------------------------------------------------------------------------
	* 构造方式
	*/
	cout << "\n-----------------------------------构造方式: ----------------------------------------------------" << endl;
	std::map<char, int> map1;

	map1['a'] = 10;
	map1['c'] = 30;
	map1['b'] = 99;
	map1['d'] = 70;
	cout << "\n1. map1: \n";
	showMap(map1);

	std::map<char, int> map2(map1.rbegin(), map1.rend());  //通过复制构造, 默认会按照 'a'->'b'->'c'->'d'的顺序储存

	std::map<char, int> map3(map2);

	std::map<char, int, classcomp<char>> map4;    // 指定某个class比较器
	map4['a'] = 10;
	map4['c'] = 30;
	map4['b'] = 99;
	map4['d'] = 70;
	cout << "\n2.  map4: \n";
	showMap(map4);

	bool(*fn_pt)(char, char) = fncomp;
	std::map<char, int, bool(*)(char, char)> map5(fn_pt); // 指定比较器, 通过函数指针调用
	map5['a'] = 10;
	map5['c'] = 30;
	map5['b'] = 99;
	map5['d'] = 70;
	cout << "\n3. map5: \n";
	showMap(map5);

	std::map<std::string, int> map6 = { //列表形式一次性构造
		{ "alpha", 0 },
		{ "beta", 0 },
		{ "gamma", 0 } };
	cout << "\n4. map6: \n";
	showMap(map6);

	/*通过操作符 = 构造*/
	map2 = map1;                 // 重置map2的元素, 使之与map1相等
	map1 = std::map<char, int>();  // 清空 map1

	/**---------------------------------------------------------------------------------------------------------------
	* 插入:	map.insert(pair<keyType, valueType>(key, value)); 
			map[key] = value
	*/
	cout << "\n-----------------------------------插入元素: ----------------------------------------------------\n" << endl;
	std::map<char, int> mymap;

	// 1. 单一元素插入
	// insert 返回类型：std::pair<std::map<xxx, xxx>::iterator, bool>
	mymap.insert(std::pair<char, int>('a', 100));
	mymap.insert(std::pair<char, int>('z', 200));

	// 1.1 插入成功判断
	std::pair<std::map<char, int>::iterator, bool> ret;
	ret = mymap.insert(std::pair<char, int>('z', 500));
	if (ret.second == false) //返回值ret.first 为插入位置的iter, ret.second 为bool值, 代表是否元素已存在
	{
		std::cout << "插入失败：元素 "<< ret.first->first <<" 已存在, ";
		std::cout << "当前z=> value： " << ret.first->second << '\n';	//ret.first->second 为已存在的value

	}

	//2. 通过给出提示位置插入
	std::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, std::pair<char, int>('b', 300));  // max efficiency inserting(事先知道紧挨着首元素'a')
	mymap.insert(it, std::pair<char, int>('c', 400));  // no max efficiency inserting(不如直接默认二叉树顺序来插入划算）

	//3. 给定范围插入:
	std::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));  //从开头，到'c'的位置(不包含c)，复制键值对

	//4. 通过操作符[]插入 or 修改：
	std::map<string, long long> mapToErase;
	std::map<string, long long>::iterator erase_it;
	mapToErase["alex"] = 18722216;  //通过[]操作符插入
	mapToErase["john"] = 18722124;
	mapToErase["luke"] = 18722444;
	mapToErase["jerry"] = 18722333;
	mapToErase["Tom"] = 18722111;
	mapToErase["Richard"] = 18722000;

	//打印结果:
	std::cout << "mymap contains:\n";
	showMap(mymap);

	std::cout << "anothermap contains:\n";
	showMap(anothermap);

	/**---------------------------------------------------------------------------------------------------------------
	* 删除:	erase(key)
			erase(iterator)
			erase(range)
	*/
	cout << "\n-----------------------------------删除元素: ----------------------------------------------------" << endl;
	std::cout << "\n待删除map:\n";
	showMap(mapToErase);
	mapToErase.erase("jerry");          //通过key删除

	erase_it = mapToErase.find("john"); // 通过迭代器删除
	mapToErase.erase(erase_it);

	std::cout << "\n删除之后:\n";
	showMap(mapToErase);

	erase_it = mapToErase.find("Tom");	// 范围删除
	mapToErase.erase(erase_it, mapToErase.end());

	std::cout << "\n范围删除之后:\n";
	showMap(mapToErase);

	/**---------------------------------------------------------------------------------------------------------------
	* 访问:	[]
			.at()
	*/
	cout << "\n-----------------------------------访问元素: ----------------------------------------------------" << endl;
	cout << "\n1. 操作符[]访问: ";
	cout << "\nmap1['c']: " << map2['c'] << endl;
	map2['c'] = 33; //直接像数组一样修改
	cout << "map1['c']: " << map2['c'] << endl;
	cout << "map1['e']: " << map2['e'] << endl; //注意：如果访问到一个不存在的元素，该方法会自动插入一个key,对应元素为默认值,
												//如果value是int,则为0; 如果是string, 则为""

	cout << "\n2. .at()访问：";
	map6.at("alpha") = 10;
	map6.at("beta") = 20;
	map6.at("gamma") = 30;
	cout << "\nmap6:\n";
	showMap(map6);

	try
	{
		cout << map6.at("delta") << endl;  //不同于[]访问，.at()如果访问到一个不存在的key, 则会抛出异常
	}
	catch (const std::exception& e)
	{
		cout << "访问元素出错：" << e.what() << endl;
	}

	/**----------------------------------------------------------------------------------------------------------------
	* 容量：大小、判空
	*/
	cout << "-----------------------------------容量判断: ----------------------------------------------------" << endl;
	cout << "\nmymap size: " << mymap.size() << endl;
	cout << "mymap max_size: " << mymap.max_size() << endl;
	cout << "mymap is empty? "<< (mymap.empty() ? "true" : "false") << endl;

	/**----------------------------------------------------------------------------------------------------------------
	* 操作: find, count等
	*/
	cout << "\n-----------------------------------其它操作: ----------------------------------------------------" << endl;
	std::map<char, int>::iterator itf = mymap.find('c');
	cout << "\nfind 'c': " << ((itf == mymap.end()) ? -1 : itf->second) << endl;  //如果find()返回 mymap.end(), 表示没找到；否则输入找到的元素。

	cout << "map 中20的个数：" << mymap.count(20) << endl;  //因为map元素都是独一无二的，所以要么1，要么0

	/**----------------------------------------------------------------------------------------------------------------
	* MultiMap: 相同元素操作
	*/
	cout << "\n-----------------------------------MultiMap: ----------------------------------------------------" << endl;

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

	//借此，我们也可以得到key == 'b'的所有元素
	cout << endl << "key 为b的所有值：";
	for (mmit = itlow; mmit != itupper; ++mmit)cout << mmit->second << " ";

	cout << "\n\n\n";
	return 0;
}


