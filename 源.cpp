/*string 类的自我实现*///管理字符的顺序表

#include<string>
#include<iostream>
using namespace std;
#pragma warning(disable:4996)

class String
{
public:


	//构造函数
	//无参构造
	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(0)
	{
		_str[_size] = '\0';
		_capacity = 15;
	}


	//全缺省构造
	//优化之后
	String(const char*str)
	{
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size;
	}
	/*String(char* str)
		:_str(str)//释放指针指向的空间会错误释放。因为123在字符常量区，
		          //所以应该开一个空间把字符串内容拷贝过去，而不是只传过来一个地址
		, _size(strlen(str))
		, _capacity(strlen(str))
	{

	}*/


	~String()
	{
		if (_str)
		{
			delete[] _str;
			_size = _capacity = 0;
			_str = nullptr;
		}
		cout << "~string()" << endl;

	}

/*
	//拷贝构造
	String(const String& str)
		:_str(new char[str._capacity + 1])
		, _size(str._size)
		, _capacity(str._capacity)
	{
	//深拷贝，资源拷贝
		strcpy(_str, str._str);
		cout << "String" << endl;
	}

	 //赋值重载
	String &operator=(const String& str)
	{
		if (this != &str)
		{
			//开空间
			char* tmp = new char[str._capacity + 1];
			//内容拷贝
			strcpy(tmp, str._str);
			//释放原有空间
			delete[] _str; 
			//深拷贝的赋值运算符重载
			_str = tmp;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
  */
	

	//更简单的拷贝构造:现代写法；复用构造函数。通过构造函数开空间，拷贝内容，
	//最后通过成员和资源的交换，完成拷贝构造的逻辑。
	String(const String& str)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(str._str);
		Swap(tmp);
	}


	//库里面的交换是深拷贝，效率太低了，所以一般都是自己写一份交换代码
	void Swap(String& str)//指向的资源发生交换
	{
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}


	//深拷贝的赋值运算符现代写法，代码复用:传参时进行拷贝构造
	String& operator=(String str)
	{
		Swap(str);
		return *this;
	}


	const char * c_str()const
	{
		return _str;
	}


	void pushBack(const char& ch)//尾插
	{
		//检查容量
		if (_size == _capacity)
		{
			size_t newc = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newc);
		}
		//尾插
		_str[_size] = ch;
		//更新size
		++_size;
		_str[_size] = '\0';
	}


	void reserve(size_t n)//增容
	{
		if (n > _capacity)
		{
			//开空间：+1——>存放\0
			char* tmp = new char[n + 1];
			//拷贝
			strcpy(tmp, _str);
			//释放原有空间
			delete[] _str;

			//更新指向，更新容量
			_str = tmp;
			_capacity = n;
		}
	}


	//迭代器：一种访问容器元素的机制，体现封装的特性，不需要关注容器的实现细节，
	//就可以直接访问（可读可写）元素
	//使用方式类似于指针。1.支持解引用，——>获取指向位置的内容
	//2.位置可以移动。——>指向其他位置

	//string 迭代器：通过指针实现
	typedef char* iterator;
	typedef const char* const_iterator;

	//可读可写调用下面两个
	iterator begin()
	{
		//第一个元素的位置
		return _str;
	}
	iterator end()
	{
		//最后一个元素的下一个位置
		return _str + _size;
	}

	//只读用下面两个
	const_iterator begin() const
	{
		//第一个元素的位置
		return _str;
	}
	const_iterator end() const
	{
		//最后一个元素的下一个位置
		return _str+_size;
	}


private:
	char* _str;//数据指针
	size_t _size;//元素个数
	size_t _capacity;//容量
};



void test()
{
	string s;//看一下库里面是怎么样实现的
	const char* ptr = s.c_str();
	cout << s.c_str() << "结束" << endl;

	String Str;
	const char* ptr2 = Str.c_str();
	cout << Str.c_str() << "结束" << endl;

	string str2("123");
	ptr2 = str2.c_str();
	cout << ptr2 << endl;/*虽然可以正常输出，但是调用析构函数的时候会出问题。
						 亦可能为字符常量是在字符常量区，将指针付过去释放释放
						 的是堆上的空间，释放了错误的空间，导致错误
~String()
{
	if (_str)
	{
		delete[] _str;
		_size = _capacity = 0;
		_str = nullptr;
	}
	cout << "~string()" << endl;

}
						 */
}


void test2()
{
	//赋值和拷贝构造不写行不行？会自动生成！会是会，但是会进行浅拷贝，不会拷贝资源，只拷贝了成员变量的地址，不拷贝资源。会导致资源多次释放，然后程序崩溃。
	//所以不行，要自己写,深拷贝，
	String s("123");
	String copy = s;
	String coy2(s);

	//赋值
	String s2 = "456";
	copy = s2;
}


void test3()
{
	String s = "";
	s.pushBack('a');
	s.pushBack('b');
	s.pushBack('c');
	s.pushBack('d');
	s.pushBack('e');
	s.pushBack('f');

	cout << s.c_str() << endl;//遍历内容

	//迭代器遍历
	String::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		//写操作
		*it = '0';
		++it;
	}
	cout << endl;
}


void printString(const String& str)
{
	//迭代器遍历
	String::const_iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		//只读迭代器不支持写操作
		//*it = '0';
		++it;
	}
	cout << endl;
}

int main()
{
	//test();
	//test2();
	test3();
	return 0;
}