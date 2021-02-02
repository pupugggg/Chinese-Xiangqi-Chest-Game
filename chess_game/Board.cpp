#include"Board.h"

Board* Board::instance=NULL;

Board::Board()
{
	init();
}

void Board::replace(Chess *source, Chess *target)
{
	boardState[target->currentPos.y].insert(boardState[target->currentPos.y].begin() + target->currentPos.x, constructorInvoker(source->id));
	boardState[target->currentPos.y].erase(boardState[target->currentPos.y].begin() + target->currentPos.x+1);
	boardState[source->currentPos.y].insert(boardState[source->currentPos.y].begin() + source->currentPos.x, constructorInvoker(0));
	boardState[source->currentPos.y].erase(boardState[source->currentPos.y].begin() + source->currentPos.x + 1);
	boardState[target->currentPos.y][target->currentPos.x]->currentPos = Vector2(target->currentPos.x, target->currentPos.y);
	boardState[source->currentPos.y][source->currentPos.x]->currentPos = Vector2(source->currentPos.x, source->currentPos.y);
	delete source;
	delete target;
}
Chess* Board::constructorInvoker(int input)
{
	switch (input)
	{
	case 0:
		return (new Empty());
		break;
	case 1:
		return (new General(input));
		break;
	case 2:
		return (new Soldier(input));
		break;
	case 3:
		return (new Elephant(input));
		break;
	case 4:
		return (new Car(input));
		break;
	case 5:
		return (new Hourse(input));
		break;
	case 6:
		return (new Cannon(input));
		break;
	case 7:
		return (new Minion(input));
		break;
	case 8:
		return (new General(input));
		break;
	case 9:
		return (new Soldier(input));
		break;
	case 10:
		return (new Elephant(input));
		break;
	case 11:
		return (new Car(input));
		break;
	case 12:
		return (new Hourse(input));
		break;
	case 13:
		return (new Cannon(input));
		break;
	case 14:
		return (new Minion(input));
		break;
	}
	return NULL;
}

void Board::init()
{
	ifstream inputStream;
	int tmp;
	inputStream.open("Initial.txt", ios::in);
	for (int i = 0; i <  GameParameter::BOARDHEIGHT; i++)
	{
		vector<Chess*> temp;

		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			
			inputStream >> tmp;
			temp.push_back(constructorInvoker(tmp));
			temp[j]->currentPos = Vector2(j, i);
		}
		boardState.push_back(temp);
		temp.clear();
	}
	inputStream >> Manager::instance->round;
	inputStream.close();
}

void Board::pushBoard()
{
	
	if (record.size() == 50)
		record.erase(record.begin());
	vector<Chess*> innerTemp;
	vector<vector<Chess*>> outerTemp;
	outerTemp.clear();
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		innerTemp.clear();
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			innerTemp.push_back(constructorInvoker(boardState[i][j]->id));
			innerTemp[j]->currentPos = boardState[i][j]->currentPos;
		}
		outerTemp.push_back(innerTemp);
	}
	record.push_back(outerTemp);
}