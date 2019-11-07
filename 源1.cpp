

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

int mian() {
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