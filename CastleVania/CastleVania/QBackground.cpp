#include "QBackground.h"

QBackground::QBackground(void)
{
	tree = NULL;
	_myObject = NULL;
	_nodeOfTree = NULL;
	_listTile = NULL;
}

QBackground::QBackground(int level)
{
	string fileName;
	switch(level)
	{
	case 1:
		fileName = "Resources\\Maps\\Level1.txt";
		break;
	case 2:
		fileName = "Resources\\Maps\\Level2.txt";
		break;
	case 3:
		fileName = "Resources\\Maps\\Level3.txt";
		break;
	}

	ifstream map (fileName);

	_listTile = new list<int>();

	if(map.is_open())
	{		
		float posX, posY; int value;
		int count;
		map>> count;
		switch(level)
		{
		case 1:
			bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level1.png", count, 1, count), 1000);
			break;
		case 2:
			bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level2.png", count, 1, count), 1000);
			break;
		case 3:
			bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level3.png", count, 1, count), 1000);
			break;
		}
		map>> count >> G_MapWidth >> G_MapHeight;
		int id; 
		_myObject = new std::map<int, Tile*>();
		Tile* _obj;
		for (int i = 0; i < count; i++)
		{
			//so thu tu dong - idObj -...
			map>> id >> value >> posX >> posY;		

			_myObject->insert(pair<int, Tile*>(id, new Tile(value, posX, posY)));
		}

		//Doc quadtree
		string line;
		_nodeOfTree = new std::map<int, QNode*>();
		int size;
		while(!map.eof())  
		{
			//posX == left; posY == top; size == size q
			map>> id >> posX >> posY >> size;

			//Doc id Object trong node
			getline(map, line);
			istringstream str_line(line);			
			list<int> *_objOfNode = new list<int>();
			while(str_line >> value)
			{
				_objOfNode->push_back(value);
			}

			QNode* _nodeTree = new QNode(posX, posY, size, *_objOfNode);

			//Dua node vao _myMap
			_nodeOfTree->insert(pair<int, QNode*>(id, _nodeTree));
		}
		map.close();
	}
}

void QBackground::GetTreeObject(int viewportX, int viewportY)
{
	_listTile->clear();

	GetNodeObject(viewportX, viewportY, tree);
}

void QBackground::GetNodeObject(int viewportX, int viewportY, QNode* _node)
{
	if(_node->leftTop != NULL)
	{
		if(viewportX < _node->rightTop->left && viewportY > _node->leftBottom->top)
			GetNodeObject(viewportX, viewportY, _node->leftTop);
		if(viewportX + G_ScreenWidth > _node->rightTop->left && viewportY > _node->rightBottom->top)
			GetNodeObject(viewportX, viewportY, _node->rightTop);
		if(viewportX < _node->rightBottom->left && viewportY - G_ScreenHeight < _node->leftBottom->top)
			GetNodeObject(viewportX, viewportY, _node->leftBottom);
		if(viewportX + G_ScreenWidth > _node->rightBottom->left && viewportY - G_ScreenHeight < _node->rightBottom->top)
			GetNodeObject(viewportX, viewportY, _node->rightBottom);
	}
	else
	{
		for (list<int>::iterator _itBegin = _node->listObject.begin(); _itBegin!=_node->listObject.end(); _itBegin++) 
		{
			_listTile->push_back(*_itBegin);
		}
	}
}

void QBackground::LoadTree()
{
	Load(0, tree);
}

void QBackground::Load(int id, QNode *& _nodeTree)
{
	map<int, QNode*>::iterator _node = _nodeOfTree->find(id);
	if(_node != _nodeOfTree->end())
	{
		_nodeTree = new QNode(_node->second->left, _node->second->top, _node->second->size, _node->second->listObject);
		Load(_node->first*8 + 1, _nodeTree->leftTop);
		Load(_node->first*8 + 2, _nodeTree->rightTop);
		Load(_node->first*8 + 3, _nodeTree->leftBottom);
		Load(_node->first*8 + 4, _nodeTree->rightBottom);
	}
}

void QBackground::Draw(CCamera *camera)
{
	for (list<int>::iterator _itBegin = _listTile->begin(); _itBegin!=_listTile->end(); _itBegin++) 
	{ 
		Tile* obj = _myObject->find(*_itBegin)->second;
		D3DXVECTOR2 t = camera->Transform(obj->posX, obj->posY);
		bgSprite->DrawIndex(obj->idTile, t.x, t.y);
	}
}

QBackground::~QBackground(void)
{
}