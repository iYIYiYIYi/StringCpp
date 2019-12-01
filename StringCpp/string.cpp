#include<iostream>
using namespace std;
class Mystring//���崮��
{
	friend ostream& operator <<(ostream& out, Mystring& s);//������������
	friend istream& operator >>(istream& out, Mystring& s);//�������������
private:
	char* Head=NULL;//ͷ,���ڴ���Ѱ��
	int length=0;//����
public:
	Mystring() 
	{
	}//Ĭ�Ϲ��죬�޲�
	Mystring(const char equal_const_s[])
	{
		int size = 0;
		for (size; equal_const_s[size] != '\0'; size++);
		this->length = size;
		this->Head = new char[this->length + 1];
		for (int i = 0; i < this->length; i++)
			this->Head[i] = equal_const_s[i];
		this->Head[this->length] = '\0';
	}//Ĭ�Ϲ��죬�в�
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
	}//�Ӻ����أ������ϲ�����
	Mystring& operator=(Mystring equal_s)
	{
		if (this->Head != NULL) delete this->Head;
		this->length = equal_s.length;
		this->Head = new char[this->length + 1];
		for (int i = 0; i < this->length; i++)
			this->Head[i] = equal_s.Head[i];
		this->Head[this->length] = '\0';
		return *this;
	}//������Ⱥ����أ���������
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
	}//������Ⱥ����أ��ַ���������������
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
	}//ȡ�Ӵ�����
	bool operator==(Mystring comp_s)
	{
		if (this->length != comp_s.length) return false;
		for (int i = 0; i < this->length; i++)
			if (this->Head[i] != comp_s.Head[i]) return false;
		return true;
	}//�ж������Ƿ����
	bool operator>(Mystring comp_s)
	{
		for (int i = 0; i < this->length && i < comp_s.length; i++)
			if (this->Head[i] > comp_s.Head[i]) return true;
			else if (this->Head[i] < comp_s.Head[i]) return false;
		return false;
	}//�ж�ǰһ�����Ƿ���ں�һ����
	bool operator<(Mystring comp_s)
	{
		for (int i = 0; i < this->length && i < comp_s.length; i++)
			if (this->Head[i] < comp_s.Head[i]) return true;
			else if (this->Head[i] > comp_s.Head[i]) return false;
		return false;
	}//�ж�ǰһ�����Ƿ�С�ں�һ����
	char& operator[](char i)
	{
		return this->Head[i];
	}//��ȡ�±�ֵ
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
	}//�ڴ���pos��λ��֮�����Ŀ�괮
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
	}//ɾ����posλ��֮���lengthΪ�ַ�
	int find_equal_index(Mystring s)
	{
		static int next[1000000] = { 0 };
		//memset(next, 0, 1000000);//���ﲻ��Ҫ��ʼ�����������в�Ӱ��
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
	}//kmp�㷨 ���ص�һ����Ŀ�괮��ȵ��Ӵ��±� ���û���򷵻�-1
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
	}//�ж��Ƿ�Ϊ��
	void clear()
	{
		delete this->Head;
		this->Head = NULL;
		this->length = 0;
	}//��մ�
	int size()//���ش��ĳ���
	{
		return this->length;
	}
};
ostream& operator<<(ostream& out, Mystring& s)
{
	for (int i = 0; i < s.length; i++)
		cout << s.Head[i];
	return out;
}//���ƺ����أ��������
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
}//���ƺ����أ��������
int main()
{

}

