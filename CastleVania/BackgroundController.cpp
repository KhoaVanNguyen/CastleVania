#include "BackgroundController.h"

BackgroundController::BackgroundController(void)
{
	tree = NULL;
	listObjects = NULL; // => list object, tất cả tile 
	nodes = NULL; //  số node 
	currentTiles = NULL; 
}

BackgroundController::BackgroundController(int level)
{
	string fileName;
	switch (level)
	{
	case 1:
		fileName = "Resources\\Maps\\Level1.txt";
		break;
	case 2:
		fileName = "Resources\\Maps\\Level2.txt";
		break;
	default:
		break;
	}
	
	ifstream map(fileName);

	currentTiles = new list<int>();

	if (map.is_open())
	{
		float posX, posY; int value;
		int count;
		map >> count;

		switch (level )
		{ 
		case 1:
			bgSprite = new GSprite(new GTexture("Resources\\Maps\\Level1.png", count, 1, count), 1000);
			break;
		case 2:
			bgSprite = new GSprite(new GTexture("Resources\\Maps\\Level2.png", count, 1, count), 1000);
			break;
		default:
			break;
		}
		
		map >> count >> G_MapWidth >> G_MapHeight;
		int id;
		listObjects = new std::map<int, Tile*>();
		Tile* _obj;
		for (int i = 0; i < count; i++)
		{
			//so thu tu dong - idObj -...
			map >> id >> value >> posX >> posY;

			listObjects->insert(pair<int, Tile*>(id, new Tile(value, posX, posY)));
		}

		//Doc quadtree
		string line;
		nodes = new std::map<int, QNode*>();
		int size;
		while (!map.eof())
		{
			//posX == left; posY == top; size == size q
			map >> id >> posX >> posY >> size;

			//Doc id Object trong node
			getline(map, line);
			istringstream str_line(line);
			list<int> *_objOfNode = new list<int>();
			while (str_line >> value)
			{
				_objOfNode->push_back(value);
			}

			QNode* _nodeTree = new QNode(posX, posY, size, *_objOfNode);

			//Dua node vao _myMap
			nodes->insert(pair<int, QNode*>(id, _nodeTree));
		}
		map.close();
	}
}

void BackgroundController::GetAvailableTiles(int viewportX, int viewportY)
{
	currentTiles->clear();
	GetObjectsIn(viewportX, viewportY, tree);
}

void BackgroundController::GetObjectsIn(int viewportX, int viewportY, QNode* _node)
{
	if (_node->leftTop != NULL)
	{
		if (viewportX < _node->rightTop->left && viewportY > _node->leftBottom->top)
			GetObjectsIn(viewportX, viewportY, _node->leftTop);
		if (viewportX + G_ScreenWidth > _node->rightTop->left && viewportY > _node->rightBottom->top)
			GetObjectsIn(viewportX, viewportY, _node->rightTop);
		if (viewportX < _node->rightBottom->left && viewportY - G_ScreenHeight < _node->leftBottom->top)
			GetObjectsIn(viewportX, viewportY, _node->leftBottom);
		if (viewportX + G_ScreenWidth > _node->rightBottom->left && viewportY - G_ScreenHeight < _node->rightBottom->top)
			GetObjectsIn(viewportX, viewportY, _node->rightBottom);
	}
	else
	{
		for (list<int>::iterator _itBegin = _node->listObject.begin(); _itBegin != _node->listObject.end(); _itBegin++)
		{
			currentTiles->push_back(*_itBegin);
		}
	}
}

void BackgroundController::LoadQuadTreeFromFile()
{
	
	Load(0, tree);
	// Sau hàm này, tree sẽ = với file levelX.txt

}

void BackgroundController::Load(int id, QNode *& _nodeTree)
{
	map<int, QNode*>::iterator _node = nodes->find(id);
	if (_node != nodes->end())
	{
		_nodeTree = new QNode(_node->second->left, _node->second->top, _node->second->size, _node->second->listObject);
		Load(_node->first * 8 + 1, _nodeTree->leftTop);
		Load(_node->first * 8 + 2, _nodeTree->rightTop);
		Load(_node->first * 8 + 3, _nodeTree->leftBottom);
		Load(_node->first * 8 + 4, _nodeTree->rightBottom);
	}
}

void BackgroundController::Draw(GCamera *camera)
{
	for (list<int>::iterator _itBegin = currentTiles->begin(); _itBegin != currentTiles->end(); _itBegin++)
	{
		Tile* obj = listObjects->find(*_itBegin)->second;
		D3DXVECTOR2 t = camera->Transform(obj->posX, obj->posY);
		bgSprite->DrawIndex(obj->idTile, t.x, t.y);
	}
}
BackgroundController::~BackgroundController(void)
{
}