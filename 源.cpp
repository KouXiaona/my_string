/*string �������ʵ��*///�����ַ���˳���

#include<string>
#include<iostream>
using namespace std;
#pragma warning(disable:4996)

class String
{
public:


	//���캯��
	//�޲ι���
	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(0)
	{
		_str[_size] = '\0';
		_capacity = 15;
	}


	//ȫȱʡ����
	//�Ż�֮��
	String(const char*str)
	{
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size;
	}
	/*String(char* str)
		:_str(str)//�ͷ�ָ��ָ��Ŀռ������ͷš���Ϊ123���ַ���������
		          //����Ӧ�ÿ�һ���ռ���ַ������ݿ�����ȥ��������ֻ������һ����ַ
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
	//��������
	String(const String& str)
		:_str(new char[str._capacity + 1])
		, _size(str._size)
		, _capacity(str._capacity)
	{
	//�������Դ����
		strcpy(_str, str._str);
		cout << "String" << endl;
	}

	 //��ֵ����
	String &operator=(const String& str)
	{
		if (this != &str)
		{
			//���ռ�
			char* tmp = new char[str._capacity + 1];
			//���ݿ���
			strcpy(tmp, str._str);
			//�ͷ�ԭ�пռ�
			delete[] _str; 
			//����ĸ�ֵ���������
			_str = tmp;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
  */
	

	//���򵥵Ŀ�������:�ִ�д�������ù��캯����ͨ�����캯�����ռ䣬�������ݣ�
	//���ͨ����Ա����Դ�Ľ�������ɿ���������߼���
	String(const String& str)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(str._str);
		Swap(tmp);
	}


	//������Ľ����������Ч��̫���ˣ�����һ�㶼���Լ�дһ�ݽ�������
	void Swap(String& str)//ָ�����Դ��������
	{
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}


	//����ĸ�ֵ������ִ�д�������븴��:����ʱ���п�������
	String& operator=(String str)
	{
		Swap(str);
		return *this;
	}


	const char * c_str()const
	{
		return _str;
	}


	void pushBack(const char& ch)//β��
	{
		//�������
		if (_size == _capacity)
		{
			size_t newc = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newc);
		}
		//β��
		_str[_size] = ch;
		//����size
		++_size;
		_str[_size] = '\0';
	}


	void reserve(size_t n)//����
	{
		if (n > _capacity)
		{
			//���ռ䣺+1����>���\0
			char* tmp = new char[n + 1];
			//����
			strcpy(tmp, _str);
			//�ͷ�ԭ�пռ�
			delete[] _str;

			//����ָ�򣬸�������
			_str = tmp;
			_capacity = n;
		}
	}


	//��������һ�ַ�������Ԫ�صĻ��ƣ����ַ�װ�����ԣ�����Ҫ��ע������ʵ��ϸ�ڣ�
	//�Ϳ���ֱ�ӷ��ʣ��ɶ���д��Ԫ��
	//ʹ�÷�ʽ������ָ�롣1.֧�ֽ����ã�����>��ȡָ��λ�õ�����
	//2.λ�ÿ����ƶ�������>ָ������λ��

	//string ��������ͨ��ָ��ʵ��
	typedef char* iterator;
	typedef const char* const_iterator;

	//�ɶ���д������������
	iterator begin()
	{
		//��һ��Ԫ�ص�λ��
		return _str;
	}
	iterator end()
	{
		//���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	//ֻ������������
	const_iterator begin() const
	{
		//��һ��Ԫ�ص�λ��
		return _str;
	}
	const_iterator end() const
	{
		//���һ��Ԫ�ص���һ��λ��
		return _str+_size;
	}


private:
	char* _str;//����ָ��
	size_t _size;//Ԫ�ظ���
	size_t _capacity;//����
};



void test()
{
	string s;//��һ�¿���������ô��ʵ�ֵ�
	const char* ptr = s.c_str();
	cout << s.c_str() << "����" << endl;

	String Str;
	const char* ptr2 = Str.c_str();
	cout << Str.c_str() << "����" << endl;

	string str2("123");
	ptr2 = str2.c_str();
	cout << ptr2 << endl;/*��Ȼ����������������ǵ�������������ʱ�������⡣
						 �����Ϊ�ַ����������ַ�����������ָ�븶��ȥ�ͷ��ͷ�
						 ���Ƕ��ϵĿռ䣬�ͷ��˴���Ŀռ䣬���´���
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
	//��ֵ�Ϳ������첻д�в��У����Զ����ɣ����ǻᣬ���ǻ����ǳ���������´����Դ��ֻ�����˳�Ա�����ĵ�ַ����������Դ���ᵼ����Դ����ͷţ�Ȼ����������
	//���Բ��У�Ҫ�Լ�д,�����
	String s("123");
	String copy = s;
	String coy2(s);

	//��ֵ
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

	cout << s.c_str() << endl;//��������

	//����������
	String::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		//д����
		*it = '0';
		++it;
	}
	cout << endl;
}


void printString(const String& str)
{
	//����������
	String::const_iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		//ֻ����������֧��д����
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