#include "QNode.h"


QNode::QNode(void)
{
	left = 0;
	top	 = 0;
	size = 0;
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
}

QNode::QNode(int _left, int _top, int _size, list<int> _list)
{
	left = _left;
	top	 = _top;
	size = _size;
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
	listObject = _list;
}

void QNode::Insert(int key)
{
	listObject.push_back(key);
}

QNode::QNode(const QNode& _node)
{
	left = _node.left;
	top = _node.top;
	size = _node.size;
	leftTop = _node.leftTop;
	leftBottom = _node.leftBottom;
	rightTop = _node.rightTop;
	rightBottom = _node.rightBottom;
	listObject = _node.listObject;
}

QNode::~QNode(void)
{
}
