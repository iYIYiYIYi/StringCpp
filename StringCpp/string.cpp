#include<iostream>
using namespace std;
class Mystring//定义串类
{
	friend ostream& operator <<(ostream& out, Mystring& s);//输出运算符重载
	friend istream& operator >>(istream& out, Mystring& s);//读入运算符重载
private:
	char* Head=NULL;//头,用于串的寻找
	int length=0;//长度
public:
	Mystring() 
	{
	}//默认构造，无参
	Mystring(const char equal_const_s[])
	{
		int size = 0;
		for (size; equal_const_s[size] != '\0'; size++);
		this->length = size;
		this->Head = new char[this->length + 1];
		for (int i = 0; i < this->length; i++)
			this->Head[i] = equal_const_s[i];
		this->Head[this->length] = '\0';
	}//默认构造，有参
	Mystring operator+(Mystring plus_s)
	{
		Mystring s;
		s.length = this->length + plus_s.length;
		s.Head = new char[s.length + 1];
		for (int i = 0; i < this->length; i++)
			s.Head[i] = this->Head[i];
		for (int i = this->length; i < s.length; i++)
			s.Head[i] = plus_s.Head[i - this->length];
		s.Head[s.length] = '\0';
		return s;
	}//加号重载，两串合并操作
	Mystring& operator=(Mystring equal_s)
	{
		if (this->Head != NULL) delete this->Head;
		this->length = equal_s.length;
		this->Head = new char[this->length + 1];
		for (int i = 0; i < this->length; i++)
			this->Head[i] = equal_s.Head[i];
		this->Head[this->length] = '\0';
		return *this;
	}//深拷贝，等号重载，拷贝操作
	Mystring& operator=(const char equal_const_s[])
	{
		if (this->Head != NULL) delete this->Head;
		int size = 0;
		for (size; equal_const_s[size] != '\0'; size++);
		this->length = size;
		this->Head = new char[this->length + 1];
		for (int i = 0; i < this->length; i++)
			this->Head[i] = equal_const_s[i];
		this->Head[this->length] = '\0';
		return *this;
	}//深拷贝，等号重载，字符串常量拷贝操作
	Mystring substring(int start_pos,int length)
	{
		Mystring s;
		if (start_pos + length <= this->length)
			s.length = length;
		else
			s.length = this->length - start_pos;
		s.Head = new char[s.length + 1];
		for (int i = 0; i + start_pos < this->length && i < length; i++)
			s.Head[i] = this->Head[start_pos + i];
		s.Head[s.length] = '\0';
		return s;
	}//取子串操作
	bool operator==(Mystring comp_s)
	{
		if (this->length != comp_s.length) return false;
		for (int i = 0; i < this->length; i++)
			if (this->Head[i] != comp_s.Head[i]) return false;
		return true;
	}//判断两串是否相等
	bool operator>(Mystring comp_s)
	{
		for (int i = 0; i < this->length && i < comp_s.length; i++)
			if (this->Head[i] > comp_s.Head[i]) return true;
			else if (this->Head[i] < comp_s.Head[i]) return false;
		return false;
	}//判断前一个串是否大于后一个串
	bool operator<(Mystring comp_s)
	{
		for (int i = 0; i < this->length && i < comp_s.length; i++)
			if (this->Head[i] < comp_s.Head[i]) return true;
			else if (this->Head[i] > comp_s.Head[i]) return false;
		return false;
	}//判断前一个串是否小于后一个串
	char& operator[](char i)
	{
		return this->Head[i];
	}//获取下标值
	void myinsert(Mystring insert_s,int pos)
	{
		if (pos > this->length) return;
		Mystring s;
		s.length = insert_s.length + this->length;
		s.Head = new char[s.length+1];
		for (int i = 0; i < pos; i++)
		{
			s.Head[i] = this->Head[i];
		}
		for (int i = pos; i <pos + insert_s.length; i++)
		{
			s.Head[i] = insert_s.Head[i - pos];
		}
		for (int i = pos + insert_s.length; i < s.length; i++)
		{
			s.Head[i] = this->Head[i - insert_s.length];
		}
		s.Head[s.length] = '\0';
		*this = s;
	}//在串第pos个位置之后插入目标串
	void mydelete(int pos, int length)
	{
		if (pos + length > this->length)
		{
			this->length = this->length - length;
			this->Head[this->length] = '\0';
		}
		else
		{
			for (int i = pos; i < this->length - length; i++)
			{
				this->Head[i] = this->Head[length + i];
			}
			this->length = this->length - length;
			this->Head[this->length] = '\0';
		}
	}//删除串pos位置之后的length为字符
	int find_equal_index(Mystring s)
	{
		static int next[1000000] = { 0 };
		//memset(next, 0, 1000000);//这里不需要初始化，程序运行不影响
		s.get_next(next);
		int j = 0;
		for (int i = 0; i <= this->size(); i++)
		{
			if (this->Head[i] == s[j])
			{
				j++;
				if (j == s.size())
					return i - j + 1;
				continue;
			}
			else
			{
				if (next[j] == -1)
					continue;
				else
				{
					i--;
					j = next[j];
				}
			}
		}
		return -1;
	}//kmp算法 返回第一个与目标串相等的子串下标 如果没有则返回-1
	void get_next(int next[])
	{
		next[0] = -1;
		int pre_p = -1;
		int end_p = 0;
		while (end_p < this->length-1)
		{
			if (pre_p == -1 || this->Head[pre_p] == this->Head[end_p])
			{
				pre_p++;
				end_p++;
				next[end_p] = pre_p;
			}
			else
			{
				pre_p = next[pre_p];
			}
		}
	}
	bool empty()
	{
		if (this->length == 0) return true;
		else return false;
	}//判断是否为空
	void clear()
	{
		delete this->Head;
		this->Head = NULL;
		this->length = 0;
	}//清空串
	int size()//返回串的长度
	{
		return this->length;
	}
};
ostream& operator<<(ostream& out, Mystring& s)
{
	for (int i = 0; i < s.length; i++)
		cout << s.Head[i];
	return out;
}//左移号重载，输出操作
istream& operator>>(istream& in, Mystring& s)
{
	static char temp_space[10000000];
	cin >> temp_space;
	int size = 0;
	for (size; temp_space[size] != '\0'; size++);
	s.length = size;
	s.Head = new char[size + 1];
	for (int i = 0; i < size; i++)
		s.Head[i] = temp_space[i];
	s.Head[size] = '\0';
	return in;
}//右移号重载，输入操作
int main()
{

}

