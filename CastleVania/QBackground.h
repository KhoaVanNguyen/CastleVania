#ifndef _QBACKGROUND_H_
#define _QBACKGROUND_H_

#include <list>
#include <map>
#include "TextureManager.h"
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
	void GetObjectsIn(int, int, QNode*);// lấy tất cả các object xuất hiện trên màn hình.
public:
	QNode *tree;
	GSprite* bgSprite;
	map<int, Tile*> *listObjects; // tất cả tiles từ file
	map<int, QNode*> *nodes; // tổng số nodes 
	list<int> *currentTiles; // danh sách các tile xuất hiện trong màn hình để vẽ

	QBackground(void);
	QBackground(int);
	void LoadQuadTreeFromFile(); // Load quadtree từ file
	void GetAvailableTiles(int, int); // Lấy danh sách các tiles vào biến currentTiles
	void Draw(GCamera *camera);
	~QBackground(void);
};

#endif