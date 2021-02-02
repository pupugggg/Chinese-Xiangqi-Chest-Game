#include"GameTree.h"

GameTreeNode::GameTreeNode()
{
	Parent = NULL;
	child.clear();
	layer = 0;
}

GameTreeNode* GameTreeNode::base;

GameTreeNode::GameTreeNode(GameTreeNode*p)
{
	this->Parent = p;
	vector<int> tmp;
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		tmp.clear();
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			tmp.push_back(p->nodeData[i][j]);
		}
		nodeData.push_back(tmp);
	}
	child.clear();
}