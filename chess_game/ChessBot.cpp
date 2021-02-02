#include"ChessBot.h"

ChessBot* ChessBot::instance;

void ChessBot::update()
{
	GameTreeNode::base = new GameTreeNode();
	copyCurrentBoard(Board::instance,GameTreeNode::base->nodeData);
	createGameTree(GameTreeNode::base, 2, 0);
	GameTreeNode::base->value = ABPruning(GameTreeNode::base, 2, -100000, 100000, 0);
	chageBoardFromBot();
	Manager::instance->round = !Manager::instance->round;
}
void ChessBot::output(GameTreeNode*b)
{
	ofstream o("output.txt",ios::app);
	o << b->layer << "-" << b->id << endl;
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
			o <<setw(2)<< b->nodeData[i][j]<<" ";
		o << endl;
	}
	o << b->value << endl;
	o << endl;
	o.close();
}
void ChessBot::print(vector<vector<int>>&v)
{
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
}
void ChessBot::createGameTree(GameTreeNode* node,int depth,int round)
{
	//output(node);
	if (depth == 0)
		return;
	int childCounter = 0;
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			if (round == GameParameter::AI_ROUND)
			{
				if (node->nodeData[i][j] != 0 && node->nodeData[i][j] < 8)
				{
					vector<Vector2> avail;
					avail.clear();
					posEnumerator(avail, node->nodeData, node->nodeData[i][j], Vector2(j, i));
					if (!(avail.empty()))
					{
						for (int k =0; k <avail.size(); k++)
						{
							node->child.push_back(new GameTreeNode(node));
							node->child[childCounter]->id = childCounter;
							node->child[childCounter]->layer = node->layer + 1;
							toPos(node->child[childCounter]->nodeData, Vector2(j, i), avail[k]);
							createGameTree(node->child[childCounter], depth - 1, !round);
							childCounter++;
						}
					}
				}
			}
			else if(round==GameParameter::PLAYER_ROUND)
			{
				if (node->nodeData[i][j] > 7)
				{
					vector<Vector2> avail;
					avail.clear();
					posEnumerator(avail, node->nodeData, node->nodeData[i][j], Vector2(j, i));
					if (!(avail.empty()))
					{
						for (int k = 0; k < avail.size(); k++)
						{
							node->child.push_back(new GameTreeNode(node));
							node->child[childCounter]->id = childCounter;
							node->child[childCounter]->layer = node->layer + 1;
							toPos(node->child[childCounter]->nodeData, Vector2(j, i), avail[k]);
							createGameTree(node->child[childCounter], depth - 1, !round);
							childCounter++;
						}
					}
				}
			}
		}
	}
}

int ChessBot::ABPruning(GameTreeNode*node, int depth, int alpha, int beta, int maximinzingPlayer)
{
	//output(node);
	if (depth == 0)
	{
		node->value=heuristicValue(node->nodeData, !maximinzingPlayer);
		return node->value;
	}
	if (maximinzingPlayer)
	{
		node->value = -100000;
		if (!(node->child.empty()))
		{
			for (int i = 0; i < node->child.size(); i++)
			{
				node->value = max(node->value,ABPruning(node->child[i],depth-1,alpha,beta,!maximinzingPlayer));
				alpha = max(alpha, node->value);
				if (alpha >= beta)
					break;
			}
		}
		return node->value;
	}
	else
	{
		node->value = 100000;
		if (!(node->child.empty()))
		{
			for (int i = 0; i < node->child.size(); i++)
			{
				node->value = min(node->value, ABPruning(node->child[i], depth - 1, alpha, beta, !maximinzingPlayer));
				beta = min(beta, node->value);
				if (alpha >= beta)
					break;
			}
		}
		return node->value;
	}
}

void ChessBot::chageBoardFromBot()
{
	
	int count = 0;
	
	for (int i = 0; i < GameTreeNode::base->child.size(); i++)
	{
		if (GameTreeNode::base->value == GameTreeNode::base->child[i]->value)
		{
			
			Vector2 first,second;
			for (int k = 0; k < GameParameter::BOARDHEIGHT; k++) {
				for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
				{
					if (GameTreeNode::base->child[i]->nodeData[k][j] != Board::instance->boardState[k][j]->id)
					{
						if (GameTreeNode::base->child[i]->nodeData[k][j] == 0)
							first = Vector2(j, k);
						else
							second = Vector2(j, k);
						Chess*tmp = Board::instance->boardState[k][j];
						Board::instance->boardState[k][j] = Board::instance->constructorInvoker(GameTreeNode::base->child[i]->nodeData[k][j]);
						Board::instance->boardState[k][j]->currentPos = Vector2(j, k);
						delete tmp;

					}
				}	
			}
			Display::Instance->drawRecord2(first, second);
			break;
		}
	}
	Display::Instance->drawBoard();
}

void ChessBot::copyCurrentBoard(const Board*const currentBoard,vector<vector<int>>&temp)
{
	temp.clear();
	vector<int> tmp;
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		tmp.clear();
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			tmp.push_back(Board::instance->boardState[i][j]->id);
		}
		temp.push_back(tmp);
	}

}


int ChessBot::heuristicValue(vector<vector<int>>&bS,int round)
{
	int value=0;
	if (round == GameParameter::AI_ROUND)
	{
		for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
		{
			for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
			{
				if (bS[i][j] < 8&&bS[i][j]!=0)
				{
					value += valueSelection(bS[i][j]);
				}
			}
		}
	}
	else if (round == GameParameter::PLAYER_ROUND)
	{
		for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
		{
			for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
			{
				if (bS[i][j] > 7)
				{
					value += valueSelection(bS[i][j]);
				}
			}
		}
	}
	return value;
}

int ChessBot::valueSelection(int &id)
{
	switch (id)
	{
	case 0:
		return 0;
		break;
	case 1://1
		return 10000 ;
		break;
	case 2://2
		return 900;
		break;
	case 3://2
		return 325;
		break;
	case 4://2
		return 500;
		break;
	case 5://2
		return 300;
		break;
	case 6://2
		return 400;
		break;
	case 7://5
		return 200;
		break;
	case 8:
		return 10000;
		break;
	case 9:
		return 900;
		break;
	case 10:
		return 325;
		break;
	case 11:
		return 500;
		break;
	case 12:
		return 300;
		break;
	case 13:
		return 400;
		break;
	case 14:
		return 200;
		break;

	default:
		return 0;
		break;
	}
}

void ChessBot::toPos(vector<vector<int>>&source,Vector2 orin,Vector2 tar)
{
	source[tar.y][tar.x] = source[orin.y][orin.x];
	source[orin.y][orin.x] = 0;
}

bool ChessBot::movable(Vector2 pos,const vector<vector<int> >&board,int id)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < GameParameter::BOARDWIDTH && pos.y < GameParameter::BOARDHEIGHT)
	{
		if (id < 8)
		{
			if ((id == 1 || id == 2) && pos.x >= GameParameter::PALACELEFT && pos.x <= GameParameter::PALACERIGHT && pos.y <= GameParameter::BLACKPALACETOP)
			{
				if ((empty(pos,board)) || (board[pos.y][pos.x] > 7))
					return true;
			}
			else if (id == 1 || id == 2)
				return false;
			else if ((empty(pos,board)) || (board[pos.y][pos.x]  > 7))
				return true;
		}
		else
		{
			if ((id == 8 || id == 9) && pos.x >= GameParameter::PALACELEFT && pos.x <= GameParameter::PALACERIGHT && pos.y >= GameParameter::REDPALACETOP)
			{
				if ((empty(pos,board)) || (board[pos.y][pos.x]  < 8))
					return true;
			}
			else if (id == 8 || id == 9)
				return false;
			else if ((empty(pos,board)) || (board[pos.y][pos.x]  < 8))
				return true;
		}
	}
	return false;
}
bool ChessBot::empty(Vector2 pos,const vector<vector<int> >&board)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < GameParameter::BOARDWIDTH && pos.y < GameParameter::BOARDHEIGHT)
		return (board[pos.y][pos.x]== 0);
	else
		return false;
}

void ChessBot::posEnumerator(vector<Vector2>&availablePos,const vector<vector<int> >&board, int id,Vector2 currentPos)
{
	if (id == 1)
	{
		if (movable(Vector2(currentPos.x, currentPos.y - 1),board,id))
			availablePos.push_back(Vector2(currentPos.x, currentPos.y - 1));
		if (movable(Vector2(currentPos.x, currentPos.y + 1), board, id))
			availablePos.push_back(Vector2(currentPos.x, currentPos.y + 1));
		if (movable(Vector2(currentPos.x + 1, currentPos.y), board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y));
		if (movable(Vector2(currentPos.x - 1, currentPos.y), board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y));
			for (int i = currentPos.y + 1; i < GameParameter::BOARDHEIGHT; i++)
			{
				if (!empty(Vector2(currentPos.x, i), board))
				{
					if (board[i][currentPos.x]== 8)
						availablePos.push_back(Vector2(currentPos.x, i));
					break;
				}
			}
		
	}
	else if (id == 2)
	{
		if (movable(Vector2(currentPos.x - 1, currentPos.y - 1),board, id))
		{
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y - 1));
		}
		if (movable(Vector2(currentPos.x + 1, currentPos.y - 1),board, id))
		{
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y - 1));
		}
		if (movable(Vector2(currentPos.x + 1, currentPos.y + 1),board, id))
		{
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y + 1));
		}
		if (movable(Vector2(currentPos.x - 1, currentPos.y + 1), board, id))
		{
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y + 1));
		}
	}
	else if (id == 3)
	{
		if (movable(Vector2(currentPos.x + 2, currentPos.y + 2),board, id) && empty(Vector2(currentPos.x + 1, currentPos.y + 1), board) && currentPos.y + 2 <= GameParameter::BLACKRIVERSIDE)
		{
			availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y + 2));
		}

		if (movable(Vector2(currentPos.x - 2, currentPos.y + 2), board, id) && empty(Vector2(currentPos.x - 1, currentPos.y + 1), board) && currentPos.y + 2 <= GameParameter::BLACKRIVERSIDE)
		{
			availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y + 2));
		}
		if (movable(Vector2(currentPos.x + 2, currentPos.y - 2), board, id) && empty(Vector2(currentPos.x + 1, currentPos.y - 1), board))
		{
			availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y - 2));
		}
		if (movable(Vector2(currentPos.x - 2, currentPos.y - 2), board, id) && empty(Vector2(currentPos.x - 1, currentPos.y - 1), board))
		{
			availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y - 2));
		}
	}
	else if (id == 4)
	{
		for (int i = currentPos.x + 1; i < GameParameter::BOARDWIDTH; i++)
		{
			if (!empty(Vector2(i, currentPos.y),board) && movable(Vector2(i, currentPos.y), board, id))
			{
				availablePos.push_back(Vector2(i, currentPos.y));
				break;
			}
			else if (!movable(Vector2(i, currentPos.y), board, id))
				break;
			else
				availablePos.push_back(Vector2(i, currentPos.y));
		}
		for (int i = currentPos.x - 1; i >= 0; i--)
		{
			if (!empty(Vector2(i, currentPos.y), board) && movable(Vector2(i, currentPos.y), board, id))
			{
				availablePos.push_back(Vector2(i, currentPos.y));
				break;
			}
			else if (!movable(Vector2(i, currentPos.y), board, id))
				break;
			else
				availablePos.push_back(Vector2(i, currentPos.y));
		}
		for (int i = currentPos.y + 1; i < GameParameter::BOARDHEIGHT; i++)
		{
			if (!empty(Vector2(currentPos.x, i), board) && movable(Vector2(currentPos.x, i), board, id))
			{
				availablePos.push_back(Vector2(currentPos.x, i));
				break;
			}
			else if (!movable(Vector2(currentPos.x, i), board, id))
				break;
			else
				availablePos.push_back(Vector2(currentPos.x, i));
		}
		for (int i = currentPos.y - 1; i >= 0; i--)
		{
			if (!empty(Vector2(currentPos.x, i), board) && movable(Vector2(currentPos.x, i), board, id))
			{
				availablePos.push_back(Vector2(currentPos.x, i));
				break;
			}
			else if (!movable(Vector2(currentPos.x, i), board, id))
				break;
			else
				availablePos.push_back(Vector2(currentPos.x, i));
		}
	}
	else if (id == 5)
	{
	if (movable(Vector2(currentPos.x, currentPos.y + 1), board, id) && empty(Vector2(currentPos.x, currentPos.y + 1), board))
	{
		if (movable(Vector2(currentPos.x + 1, currentPos.y + 2), board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y + 2));
		if (movable(Vector2(currentPos.x - 1, currentPos.y + 2), board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y + 2));
	}
	//top
	if (movable(Vector2(currentPos.x, currentPos.y - 1), board, id) && empty(Vector2(currentPos.x, currentPos.y - 1), board))
	{
		if (movable(Vector2(currentPos.x + 1, currentPos.y - 2), board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y - 2));
		if (movable(Vector2(currentPos.x - 1, currentPos.y - 2), board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y - 2));
	}
	//right
	if (movable(Vector2(currentPos.x + 1, currentPos.y), board, id) && empty(Vector2(currentPos.x + 1, currentPos.y), board))
	{
		if (movable(Vector2(currentPos.x + 2, currentPos.y + 1), board, id))
			availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y + 1));
		if (movable(Vector2(currentPos.x + 2, currentPos.y - 1), board, id))
			availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y - 1));
	}
	//left
	if (movable(Vector2(currentPos.x - 1, currentPos.y), board, id) && empty(Vector2(currentPos.x - 1, currentPos.y), board))
	{
		if (movable(Vector2(currentPos.x - 2, currentPos.y + 1), board, id))
			availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y + 1));
		if (movable(Vector2(currentPos.x - 2, currentPos.y - 1), board, id))
			availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y - 1));
	}
	}
	else if (id == 6)
	{
	//x positive search
	for (int i = currentPos.x + 1; i < GameParameter::BOARDWIDTH; i++)
	{
		if (!empty(Vector2(i, currentPos.y),board))
		{
			for (int j = i + 1; j < GameParameter::BOARDWIDTH; j++)
			{
				if (movable(Vector2(j, currentPos.y),board, id) && !empty(Vector2(j, currentPos.y),board))
				{
					availablePos.push_back(Vector2(j, currentPos.y));
					break;
				}
				else if (empty(Vector2(j, currentPos.y), board))
				{
					continue;
				}
				else if (!movable(Vector2(j, currentPos.y), board, id))
				{
					break;
				}
			}
			break;
		}
		else
			availablePos.push_back(Vector2(i, currentPos.y));
	}
	//x negative search
	for (int i = currentPos.x - 1; i >= 0; i--)
	{
		if (!empty(Vector2(i, currentPos.y), board))
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (movable(Vector2(j, currentPos.y), board, id) && !empty(Vector2(j, currentPos.y), board))
				{
					availablePos.push_back(Vector2(j, currentPos.y));
					break;
				}
				else if (empty(Vector2(j, currentPos.y), board))
				{
					continue;
				}
				else if (!movable(Vector2(j, currentPos.y), board, id))
				{
					break;
				}
			}
			break;
		}
		else
			availablePos.push_back(Vector2(i, currentPos.y));
	}
	//y down search
	for (int i = currentPos.y + 1; i < GameParameter::BOARDHEIGHT; i++)
	{
		if (!empty(Vector2(currentPos.x, i), board))
		{
			for (int j = i + 1; j < GameParameter::BOARDHEIGHT; j++)
			{
				if (movable(Vector2(currentPos.x, j), board, id) && !empty(Vector2(currentPos.x, j), board))
				{
					availablePos.push_back(Vector2(currentPos.x, j));
					break;
				}
				else if (empty(Vector2(currentPos.x, j), board))
				{
					continue;
				}
				else if (!movable(Vector2(currentPos.x, j), board, id))
				{
					break;
				}
			}
			break;
		}
		else
			availablePos.push_back(Vector2(currentPos.x, i));
	}
	//y up search
	for (int i = currentPos.y - 1; i >= 0; i--)
	{
		if (!empty(Vector2(currentPos.x, i), board))
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (movable(Vector2(currentPos.x, j), board, id) && !empty(Vector2(currentPos.x, j), board))
				{
					availablePos.push_back(Vector2(currentPos.x, j));
					break;
				}
				else if (empty(Vector2(currentPos.x, j), board))
				{
					continue;
				}
				else if (!movable(Vector2(currentPos.x, j), board, id))
				{
					break;
				}

			}
			break;
		}
		else
			availablePos.push_back(Vector2(currentPos.x, i));
	}
	}
	else if (id == 7)
	{
	if (movable(Vector2(currentPos.x, currentPos.y + 1),board, id))
		availablePos.push_back(Vector2(currentPos.x, currentPos.y + 1));
	if (currentPos.y > GameParameter::BLACKRIVERSIDE)
	{
		if (movable(Vector2(currentPos.x + 1, currentPos.y), board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y));
		if (movable(Vector2(currentPos.x - 1, currentPos.y), board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y));
	}
	}
	else if (id == 8)
	{
		if (movable(Vector2(currentPos.x, currentPos.y - 1), board, id))
			availablePos.push_back(Vector2(currentPos.x, currentPos.y - 1));
		if (movable(Vector2(currentPos.x, currentPos.y + 1), board, id))
			availablePos.push_back(Vector2(currentPos.x, currentPos.y + 1));
		if (movable(Vector2(currentPos.x + 1, currentPos.y), board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y));
		if (movable(Vector2(currentPos.x - 1, currentPos.y), board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y));
		for (int i = currentPos.y - 1; i >= 0; i--)
		{
			if (!empty(Vector2(currentPos.x, i),board))
			{
				if (board[i][currentPos.x]== 1)
					availablePos.push_back(Vector2(currentPos.x, i));
				break;
			}
		}
	}
	else if (id == 9)
	{
		if (movable(Vector2(currentPos.x - 1, currentPos.y - 1), board, id))
		{
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y - 1));
		}
		if (movable(Vector2(currentPos.x + 1, currentPos.y - 1), board, id))
		{
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y - 1));
		}
		if (movable(Vector2(currentPos.x + 1, currentPos.y + 1), board, id))
		{
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y + 1));
		}
		if (movable(Vector2(currentPos.x - 1, currentPos.y + 1), board, id))
		{
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y + 1));
		}
	}
	else if (id == 10)
	{
	if (movable(Vector2(currentPos.x + 2, currentPos.y + 2),board, id) && empty(Vector2(currentPos.x + 1, currentPos.y + 1), board))
	{
		availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y + 2));
	}

	if (movable(Vector2(currentPos.x - 2, currentPos.y + 2), board, id) && empty(Vector2(currentPos.x - 1, currentPos.y + 1), board))
	{
		availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y + 2));
	}
	if (movable(Vector2(currentPos.x + 2, currentPos.y - 2), board, id) && empty(Vector2(currentPos.x + 1, currentPos.y - 1), board) && currentPos.y - 2 >= GameParameter::REDRIVERSIDE)
	{
		availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y - 2));
	}
	if (movable(Vector2(currentPos.x - 2, currentPos.y - 2), board, id) && empty(Vector2(currentPos.x - 1, currentPos.y - 1), board) && currentPos.y - 2 >= GameParameter::REDRIVERSIDE)
	{
		availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y - 2));
	}
	}
	else if (id == 11)
	{
	for (int i = currentPos.x + 1; i < GameParameter::BOARDWIDTH; i++)
	{
		if (!empty(Vector2(i, currentPos.y), board) && movable(Vector2(i, currentPos.y), board, id))
		{
			availablePos.push_back(Vector2(i, currentPos.y));
			break;
		}
		else if (!movable(Vector2(i, currentPos.y), board, id))
			break;
		else
			availablePos.push_back(Vector2(i, currentPos.y));
	}
	for (int i = currentPos.x - 1; i >= 0; i--)
	{
		if (!empty(Vector2(i, currentPos.y), board) && movable(Vector2(i, currentPos.y), board, id))
		{
			availablePos.push_back(Vector2(i, currentPos.y));
			break;
		}
		else if (!movable(Vector2(i, currentPos.y), board, id))
			break;
		else
			availablePos.push_back(Vector2(i, currentPos.y));
	}
	for (int i = currentPos.y + 1; i < GameParameter::BOARDHEIGHT; i++)
	{
		if (!empty(Vector2(currentPos.x, i), board) && movable(Vector2(currentPos.x, i), board, id))
		{
			availablePos.push_back(Vector2(currentPos.x, i));
			break;
		}
		else if (!movable(Vector2(currentPos.x, i), board, id))
			break;
		else
			availablePos.push_back(Vector2(currentPos.x, i));
	}
	for (int i = currentPos.y - 1; i >= 0; i--)
	{
		if (!empty(Vector2(currentPos.x, i), board) && movable(Vector2(currentPos.x, i), board, id))
		{
			availablePos.push_back(Vector2(currentPos.x, i));
			break;
		}
		else if (!movable(Vector2(currentPos.x, i), board, id))
			break;
		else
			availablePos.push_back(Vector2(currentPos.x, i));
	}
	}
	else if (id == 12)
	{
	if (movable(Vector2(currentPos.x, currentPos.y + 1),board, id) && empty(Vector2(currentPos.x, currentPos.y + 1), board))
	{
		if (movable(Vector2(currentPos.x + 1, currentPos.y + 2), board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y + 2));
		if (movable(Vector2(currentPos.x - 1, currentPos.y + 2), board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y + 2));
	}
	//top
	if (movable(Vector2(currentPos.x, currentPos.y - 1), board, id) && empty(Vector2(currentPos.x, currentPos.y - 1), board))
	{
		if (movable(Vector2(currentPos.x + 1, currentPos.y - 2), board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y - 2));
		if (movable(Vector2(currentPos.x - 1, currentPos.y - 2), board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y - 2));
	}
	//right
	if (movable(Vector2(currentPos.x + 1, currentPos.y), board, id) && empty(Vector2(currentPos.x + 1, currentPos.y), board))
	{
		if (movable(Vector2(currentPos.x + 2, currentPos.y + 1), board, id))
			availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y + 1));
		if (movable(Vector2(currentPos.x + 2, currentPos.y - 1), board, id))
			availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y - 1));
	}
	//left
	if (movable(Vector2(currentPos.x - 1, currentPos.y), board, id) && empty(Vector2(currentPos.x - 1, currentPos.y), board))
	{
		if (movable(Vector2(currentPos.x - 2, currentPos.y + 1), board, id))
			availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y + 1));
		if (movable(Vector2(currentPos.x - 2, currentPos.y - 1), board, id))
			availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y - 1));
	}
	}
	else if (id == 13)
	{
	//x positive search
	for (int i = currentPos.x + 1; i < GameParameter::BOARDWIDTH; i++)
	{
		if (!empty(Vector2(i, currentPos.y), board))
		{
			for (int j = i + 1; j < GameParameter::BOARDWIDTH; j++)
			{
				if (movable(Vector2(j, currentPos.y), board, id) && !empty(Vector2(j, currentPos.y), board))
				{
					availablePos.push_back(Vector2(j, currentPos.y));
					break;
				}
				else if (empty(Vector2(j, currentPos.y), board))
				{
					continue;
				}
				else if (!movable(Vector2(j, currentPos.y), board, id))
				{
					break;
				}
			}
			break;
		}
		else
			availablePos.push_back(Vector2(i, currentPos.y));
	}
	//x negative search
	for (int i = currentPos.x - 1; i >= 0; i--)
	{
		if (!empty(Vector2(i, currentPos.y), board))
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (movable(Vector2(j, currentPos.y), board, id) && !empty(Vector2(j, currentPos.y), board))
				{
					availablePos.push_back(Vector2(j, currentPos.y));
					break;
				}
				else if (empty(Vector2(j, currentPos.y), board))
				{
					continue;
				}
				else if (!movable(Vector2(j, currentPos.y), board, id))
				{
					break;
				}
			}
			break;
		}
		else
			availablePos.push_back(Vector2(i, currentPos.y));
	}
	//y down search
	for (int i = currentPos.y + 1; i < GameParameter::BOARDHEIGHT; i++)
	{
		if (!empty(Vector2(currentPos.x, i), board))
		{
			for (int j = i + 1; j < GameParameter::BOARDHEIGHT; j++)
			{
				if (movable(Vector2(currentPos.x, j), board, id) && !empty(Vector2(currentPos.x, j), board))
				{
					availablePos.push_back(Vector2(currentPos.x, j));
					break;
				}
				else if (empty(Vector2(currentPos.x, j), board))
				{
					continue;
				}
				else if (!movable(Vector2(currentPos.x, j), board, id))
				{
					break;
				}
			}
			break;
		}
		else
			availablePos.push_back(Vector2(currentPos.x, i));
	}
	//y up search
	for (int i = currentPos.y - 1; i >= 0; i--)
	{
		if (!empty(Vector2(currentPos.x, i), board))
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (movable(Vector2(currentPos.x, j), board, id) && !empty(Vector2(currentPos.x, j), board))
				{
					availablePos.push_back(Vector2(currentPos.x, j));
					break;
				}
				else if (empty(Vector2(currentPos.x, j), board))
				{
					continue;
				}
				else if (!movable(Vector2(currentPos.x, j), board, id))
				{
					break;
				}

			}
			break;
		}
		else
			availablePos.push_back(Vector2(currentPos.x, i));
	}
	}
	else if (id == 14)
	{
	if (movable(Vector2(currentPos.x, currentPos.y - 1),board, id))
		availablePos.push_back(Vector2(currentPos.x, currentPos.y - 1));
	if (currentPos.y < GameParameter::REDRIVERSIDE)
	{
		if (movable(Vector2(currentPos.x + 1, currentPos.y),board, id))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y));
		if (movable(Vector2(currentPos.x - 1, currentPos.y),board, id))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y));
	}
	}
}

ChessBot::ChessBot() {};

void ChessBot::copy2DVector(vector<vector<int>>&target, const vector<vector<int>>&source)
{
	vector<int> tmp;
	clear2DVector(target);
	for (int i = 0; i <GameParameter::BOARDHEIGHT; i++)
	{
		tmp.clear();
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			tmp.push_back(source[i][j]);
		}
		target.push_back(tmp);
	}
}

void ChessBot::clear2DVector(vector<vector<int>>&source)
{
	for (int i = 0; i < source.size(); i++)
		source[i].clear();
	source.clear();
}
bool ChessBot::winCon(const vector<vector<int>>&board)
{
	bool gameOver = true;
	bool f = false;
	for (int i = 0; i<GameParameter::BOARDHEIGHT; i++)
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			if (board[i][j]== 1)
			{
				f = true;
			}
			if (f&&board[i][j]== 8)
			{
				gameOver = false;
			}
		}
	return gameOver;
}