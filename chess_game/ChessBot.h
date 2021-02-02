#pragma once
#include"Manager.h"
#include"GameTree.h"
class ChessBot {
public:
	ChessBot();
	static ChessBot* instance;
	void copyCurrentBoard(const Board*const,vector<vector<int> >& temp);
	
	int minimax(vector<vector<int> >&,int round,int depth,int previousW);
	int valueSelection(int& id);
	int heuristicValue(vector<vector<int>>&bS,int round);
	void update();
	void posEnumerator(vector<Vector2>&pos,const vector<vector<int> >&board,int id,Vector2);
	void toPos(vector<vector<int> >&,Vector2,Vector2);
	vector<vector<int>> currentBoardState;
	bool empty(Vector2, const vector<vector<int> >&);
	bool movable(Vector2,const vector<vector<int> >&board,int);
	void chageBoardFromBot();
	void copy2DVector(vector<vector<int>>&, const vector<vector<int>>&);
	void clear2DVector(vector<vector<int>>&);
	int ABPruning(GameTreeNode*node, int depth, int alpha, int beta, int maximinzingPlayer);
	bool winCon(const vector<vector<int>>&board);
	/***************************************************/
	void createGameTree(GameTreeNode*,int depth,int round);
	void cleanGameTree(GameTreeNode*);
	void print(vector<vector<int>>&v);
	void output(GameTreeNode*);
};