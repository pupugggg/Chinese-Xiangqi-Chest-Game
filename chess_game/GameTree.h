#pragma once
#include<vector>
#include"GameParameter.h"
using namespace std;
class GameTreeNode {
public:
	static GameTreeNode *base;
	GameTreeNode();
	GameTreeNode(GameTreeNode*);
	vector<GameTreeNode* > child;
	GameTreeNode* Parent;
	vector<vector<int>> nodeData;
	int id;
	int layer;
	int value;
};