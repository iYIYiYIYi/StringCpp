// StringCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*
*串由静态链表修改而来
*/

#include<iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
using namespace std;
typedef char Elemtype;
typedef int Status;
#define OK 1
#define SLNULL 0
#define ERROR 0
#define MAXSIZE 100
typedef struct Node {	//节点结构体，存储数据
	Elemtype data;
	int next;
};

struct StaticLink {
	Node Space[MAXSIZE];	//串结构体
	int head;
};

Status MallocSL(StaticLink* SLp, int* newnode) {	//创建头结点
	int newp = SLp->Space[0].next;
	if (newp == SLNULL)
		return ERROR;
	SLp->Space[0].next = SLp->Space[newp].next;
	*newnode = newp;
	return OK;
}

Status FreeSL(StaticLink* SLp, int delnode) {	//释放空间
	SLp->Space[delnode].next = SLp->Space[0].next;
	SLp->Space[0].next = delnode;
	return OK;
}

Status InitStaticLink(StaticLink* SLp) {
	for (int i = 0; i < MAXSIZE; i++) {	//初始化存储空间
		SLp->Space[i].data = ' ';
		SLp->Space[i].next = i + 1;
	}
	SLp->Space[MAXSIZE-1].next = SLNULL;
	SLp->head = SLNULL;
	if (MallocSL(SLp, &SLp->head) == ERROR)
		return ERROR;
	SLp->Space[SLp->head].next = SLNULL;
	return OK;
}

Status Insert(StaticLink* SLp, int ins, Elemtype e) {
	int i, newnode;
	int p = SLp->head;
	if (ins < 1)
		return ERROR;
	for (i = 0; i < ins; i++) {
		if (p == SLNULL)
			break;
		p = SLp->Space[p].next;
	}
	if (p == SLNULL)
		return ERROR;
	if (MallocSL(SLp, &newnode) == ERROR)
		return ERROR;
	SLp->Space[newnode].data = e;
	SLp->Space[newnode].next = SLp->Space[p].next;
	SLp->Space[p].next = newnode;
	SLp->Space[0].data++;//把Space[0]的data拿来存长度
	return OK;
}

Status DeleteSL(StaticLink* SLp, int deli, Elemtype* e) {
	int i;
	int p = SLp->head; int delnode;
	if (deli < 1)
		return ERROR;
	for (i = 0; i < deli; i++) {
		if (p == SLNULL)
			break;
		p = SLp->Space[p].next;
	}
	if (p == SLNULL)
		return ERROR;
	delnode = SLp->Space[p].next;
	*e = SLp->Space[delnode].data;
	SLp->Space[p].next = SLp->Space[delnode].next;
	FreeSL(SLp, delnode);
	SLp->Space[0].data--;
	return OK;
}

Status ShowSL(StaticLink SLp) {
	int i;
	for (i = 0; i < MAXSIZE; i++)
		printf("-8s%2%d\n", SLp.Space[i].data, SLp.Space[i].next);
	cout << "**********************" << endl;
	return OK;
}

Status push(StaticLink* SLp, Elemtype e) {
	int loc = SLp->Space[0].data;
	Insert(SLp, loc, e);
}

Status addString(char inchars[], int length, StaticLink* SLp) {	//往静态链表里存入串
	for (int i = 0; i < length; i++)
	{
		if (!push(SLp, inchars[i]))
			return ERROR;
	}
	push(SLp, '\0');
	return OK;
}

Status Match(char inchars[],int length,int* Loc,StaticLink* SLp) {
	for(int i=0;i<length;i++){

	}
	return OK;
}

int main() {
	StaticLink SLp;
	string e; char pos;
	int i;
	string in;
	cin >> in;
	int length = in.length;

	InitStaticLink(&SLp);

	return OK;
}