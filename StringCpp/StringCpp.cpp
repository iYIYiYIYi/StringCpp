// StringCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
typedef string Elemtype;
typedef int Status;
#define OK 1
#define SLNULL 0
#define ERROR 0
#define MAXSIZE 100
typedef struct Node {
	Elemtype date;
	int next;
};

struct StaticLink {
	Node Space[MAXSIZE];
	int head;
};

Status MallocSL(StaticLink* SLp, int* newnode) {
	int newp = SLp->Space[0].next;
	if (newp == SLNULL)
		return ERROR;
	SLp->Space[0].next = SLp->Space[newp].next;
	*newnode = newp;
	return OK;
}

Status FreeSL(StaticLink* SLp, int delnode) {
	SLp->Space[delnode].next = SLp->Space[0].next;
	SLp->Space[0].next = delnode;
	return OK;
}

Status InitStaticLink(StaticLink* SLp) {
	for (int i = 0; i < MAXSIZE; i++) {
		SLp->Space[i].date = "";
		SLp->Space[i].next = i + 1;
	}
	SLp->Space[MAXSIZE].next = SLNULL;
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
		if (p = SLNULL)
			break;
		p = SLp->Space[p].next;
	}
	if (p == SLNULL)
		return ERROR;
	if (MallocSL(SLp, &newnode) == ERROR)
		return ERROR;
	SLp->Space[newnode].date = e;
	SLp->Space[newnode].next = SLp->Space[p].next;
	SLp->Space[p].next = newnode;
	return OK;
}

Status DeleteSL(StaticLink* SLp, int deli, Elemtype e) {
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
	e = SLp->Space[delnode].date;
	SLp->Space[p].next = SLp->Space[delnode].next;
	FreeSL(SLp, delnode);
	return OK;
}

Status ShowSL(StaticLink SLp) {
	int i;
	for (i = 0; i < MAXSIZE; i++)
		printf("-8s%2%d\n", SLp.Space[i].date, SLp.Space[i].next);
	cout << "**********************" << endl;
	return OK;
}

int main() {
	StaticLink SLp;
	Elemtype e, pos;
	int i;
	InitStaticLink(&SLp);
	while (cin >> e) {
		if (e == "insert") {
			cin >> pos;
			Insert(&SLp, i, pos);
		}
		if (e == "delete") {
			cin >> i;
			DeleteSL(&SLp, i, pos);
		}
		if (e == "show") {
			ShowSL(SLp);
		}
		cout << endl;
	}
	return OK;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
