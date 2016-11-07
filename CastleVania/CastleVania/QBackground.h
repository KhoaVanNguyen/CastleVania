#ifndef _QBACKGROUND_H_
#define _QBACKGROUND_H_

#include <list>
#include <map>

#include "GCamera.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include "QNode.h"

using namespace std;

class QBackground
{
	void Load(int, QNode*&);
	void GetNodeObject(int , int , QNode*);
public:
	QNode *tree;
	GSprite* bgSprite;
	map<int, Tile*> *_myObject;
	map<int, QNode*> *_nodeOfTree;
	list<int> *_listTile;

	QBackground(void);
	QBackground(int);
	void LoadTree();
	void GetTreeObject(int, int);
	//void Draw(CCamera *camera);
	~QBackground(void);
};

#endif