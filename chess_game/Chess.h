#include"GameParameter.h"

using namespace std;
#ifndef Chess_H
#define Chess_H

#include"Board.h"

class Chess {
public:
	Chess(int in);
	Chess();
	int id;
	string icon;
	Vector2 currentPos;
	vector<Vector2> availablePos;
	void cleanAvailablePos();
	virtual void select() {};
	bool operator ==(const Chess&);
	bool movable(Vector2);
	bool empty(Vector2);
	void iconSelector(int);
	
};

class Empty : public Chess
{
public:
	Empty() :Chess() {}
};
class General : public Chess
{
public:

	General(int in) :Chess(in) {};
	void select() {
		cleanAvailablePos();
		if (movable(Vector2(currentPos.x, currentPos.y - 1)))
			availablePos.push_back(Vector2(currentPos.x, currentPos.y - 1));
		if (movable(Vector2(currentPos.x, currentPos.y + 1)))
			availablePos.push_back(Vector2(currentPos.x, currentPos.y + 1));
		if (movable(Vector2(currentPos.x + 1, currentPos.y)))
			availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y));
		if (movable(Vector2(currentPos.x - 1, currentPos.y)))
			availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y));
		if (id == 1)
		{
			for (int i = currentPos.y + 1; i < GameParameter::BOARDHEIGHT; i++)
			{
				if (!empty(Vector2(currentPos.x, i)))
				{
					if (Board::instance->boardState[i][currentPos.x]->id == 8)
						availablePos.push_back(Vector2(currentPos.x, i));
					break;
				}
			}
		}
		else if (id == 8)
		{
			for (int i = currentPos.y - 1; i >=0; i--)
			{
				if (!empty(Vector2(currentPos.x, i)))
				{
					if (Board::instance->boardState[i][currentPos.x]->id == 1)
						availablePos.push_back(Vector2(currentPos.x, i));
					break;
				}
			}
		}
	}
		

};
class Soldier : public Chess
{
public:
	Soldier(int in):Chess(in){}
	void select() {
		cleanAvailablePos();
			if (movable(Vector2(currentPos.x - 1, currentPos.y - 1)))
			{
				availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y - 1));
			}
			if (movable(Vector2(currentPos.x + 1, currentPos.y - 1)))
			{
				availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y - 1));
			}
			if (movable(Vector2(currentPos.x + 1, currentPos.y + 1)))
			{
				availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y + 1));
			}
			if (movable(Vector2(currentPos.x - 1, currentPos.y + 1)))
			{
				availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y + 1));
			}
		
	}
};
class Elephant : public Chess
{
public:
	Elephant(int in):Chess(in){}
	void select()
	{
		cleanAvailablePos();
		if (id < 8) {
			if (movable(Vector2(currentPos.x + 2, currentPos.y + 2)) && empty(Vector2(currentPos.x + 1, currentPos.y + 1)) && currentPos.y + 2 <= GameParameter::BLACKRIVERSIDE)
			{
				availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y + 2));
			}
			
			if (movable(Vector2(currentPos.x - 2, currentPos.y + 2)) && empty(Vector2(currentPos.x - 1, currentPos.y + 1)) && currentPos.y + 2 <= GameParameter::BLACKRIVERSIDE)
			{
				availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y + 2));
			}
			if (movable(Vector2(currentPos.x + 2, currentPos.y - 2)) && empty(Vector2(currentPos.x + 1, currentPos.y - 1)))
			{
				availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y - 2));
			}
			if (movable(Vector2(currentPos.x - 2, currentPos.y - 2)) && empty(Vector2(currentPos.x - 1, currentPos.y - 1)))
			{
				availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y - 2));
			}
		}
		else {
			if (movable(Vector2(currentPos.x + 2, currentPos.y + 2)) && empty(Vector2(currentPos.x + 1, currentPos.y + 1)))
			{
				availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y + 2));
			}

			if (movable(Vector2(currentPos.x - 2, currentPos.y + 2)) && empty(Vector2(currentPos.x - 1, currentPos.y + 1)))
			{
				availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y + 2));
			}
			if (movable(Vector2(currentPos.x + 2, currentPos.y - 2)) && empty(Vector2(currentPos.x + 1, currentPos.y - 1)) && currentPos.y - 2 >= GameParameter::REDRIVERSIDE)
			{
				availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y - 2));
			}
			if (movable(Vector2(currentPos.x - 2, currentPos.y - 2)) && empty(Vector2(currentPos.x - 1, currentPos.y - 1)) && currentPos.y - 2 >= GameParameter::REDRIVERSIDE)
			{
				availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y - 2));
			}
		}
	}
};
class Car : public Chess
{
public:
	Car(int in):Chess(in){}
	void select()
	{
		cleanAvailablePos();
		for (int i = currentPos.x + 1; i < GameParameter::BOARDWIDTH; i++)
		{
			if (!empty(Vector2(i, currentPos.y)) && movable(Vector2(i, currentPos.y)))
			{
				availablePos.push_back(Vector2(i, currentPos.y));
				break;
			}
			else if (!movable(Vector2(i, currentPos.y)))
				break;
			else
				availablePos.push_back(Vector2(i, currentPos.y));
		}
		for (int i = currentPos.x - 1; i >= 0; i--)
		{
			if (!empty(Vector2(i, currentPos.y)) && movable(Vector2(i, currentPos.y)))
			{
				availablePos.push_back(Vector2(i, currentPos.y));
				break;
			}
			else if (!movable(Vector2(i, currentPos.y)))
				break;
			else
				availablePos.push_back(Vector2(i, currentPos.y));
		}
		for (int i = currentPos.y + 1; i < GameParameter::BOARDHEIGHT; i++)
		{
			if (!empty(Vector2(currentPos.x,i)) && movable(Vector2(currentPos.x, i)))
			{
				availablePos.push_back(Vector2(currentPos.x, i));
				break;
			}
			else if (!movable(Vector2(currentPos.x, i)))
				break;
			else
				availablePos.push_back(Vector2(currentPos.x, i));
		}
		for (int i = currentPos.y - 1; i >= 0; i--)
		{
			if (!empty(Vector2( currentPos.x,i)) && movable(Vector2(currentPos.x, i)))
			{
				availablePos.push_back(Vector2(currentPos.x, i));
				break;
			}
			else if (!movable(Vector2(currentPos.x, i)))
				break;
			else
				availablePos.push_back(Vector2(currentPos.x, i));
		}
	}
};
class Hourse : public Chess
{
public:
	Hourse(int in):Chess(in){}
	void select()
	{
		cleanAvailablePos();
		//down
		if (movable(Vector2(currentPos.x, currentPos.y + 1)) && empty(Vector2(currentPos.x, currentPos.y + 1)))
		{
			if (movable(Vector2(currentPos.x + 1, currentPos.y + 2)))
				availablePos.push_back(Vector2(currentPos.x+1, currentPos.y + 2));
			if (movable(Vector2(currentPos.x - 1, currentPos.y + 2)))
				availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y + 2));
		}
		//top
		if (movable(Vector2(currentPos.x, currentPos.y - 1)) && empty(Vector2(currentPos.x, currentPos.y - 1)))
		{
			if (movable(Vector2(currentPos.x + 1, currentPos.y - 2)))
				availablePos.push_back(Vector2(currentPos.x+1, currentPos.y - 2));
			if (movable(Vector2(currentPos.x - 1, currentPos.y - 2)))
				availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y - 2));
		}
		//right
		if (movable(Vector2(currentPos.x+1, currentPos.y)) && empty(Vector2(currentPos.x+1, currentPos.y)))
		{
			if (movable(Vector2(currentPos.x + 2, currentPos.y + 1)))
				availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y + 1));
			if (movable(Vector2(currentPos.x + 2, currentPos.y - 1)))
				availablePos.push_back(Vector2(currentPos.x + 2, currentPos.y - 1));
		}
		//left
		if (movable(Vector2(currentPos.x - 1, currentPos.y)) && empty(Vector2(currentPos.x - 1, currentPos.y)))
		{
			if (movable(Vector2(currentPos.x - 2, currentPos.y + 1)))
				availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y + 1));
			if (movable(Vector2(currentPos.x - 2, currentPos.y - 1)))
				availablePos.push_back(Vector2(currentPos.x - 2, currentPos.y - 1));
		}
	}
};
class Cannon : public Chess
{
public:
	Cannon(int in):Chess(in){ }
	void select()
	{
		cleanAvailablePos();
		//x positive search
		for (int i = currentPos.x + 1; i < GameParameter::BOARDWIDTH; i++)
		{
			if (!empty(Vector2(i, currentPos.y)))
			{
				for (int j = i + 1; j < GameParameter::BOARDWIDTH; j++)
				{
					if (movable(Vector2(j, currentPos.y)) && !empty(Vector2(j, currentPos.y)))
					{
						availablePos.push_back(Vector2(j,currentPos.y));
						break;
					}
					else if (empty(Vector2(j, currentPos.y)))
					{
						continue;
					}
					else if (!movable(Vector2(j, currentPos.y)))
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
			if (!empty(Vector2(i, currentPos.y)))
			{
				for (int j = i - 1; j >= 0; j--)
				{
					if (movable(Vector2(j, currentPos.y)) && !empty(Vector2(j, currentPos.y)))
					{
						availablePos.push_back(Vector2(j, currentPos.y));
						break;
					}
					else if (empty(Vector2(j, currentPos.y)))
					{
						continue;
					}
					else if (!movable(Vector2(j, currentPos.y)))
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
			if (!empty(Vector2(currentPos.x, i)))
			{
				for (int j = i + 1; j < GameParameter::BOARDHEIGHT; j++)
				{
					if (movable(Vector2(currentPos.x, j)) && !empty(Vector2(currentPos.x, j)))
					{
						availablePos.push_back(Vector2(currentPos.x, j));
						break;
					}
					else if (empty(Vector2(currentPos.x, j)))
					{
						continue;
					}
					else if (!movable(Vector2(currentPos.x, j)))
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
			if (!empty(Vector2(currentPos.x, i)))
			{
				for (int j = i - 1; j >= 0 ; j--)
				{
					if (movable(Vector2(currentPos.x, j)) && !empty(Vector2(currentPos.x, j)))
					{
						availablePos.push_back(Vector2(currentPos.x, j));
						break;
					}
					else if (empty(Vector2(currentPos.x, j)))
					{
						continue;
					}
					else if (!movable(Vector2(currentPos.x, j)))
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
};
class Minion : public Chess
{
public:
	Minion(int in):Chess(in){  }
	void select()
	{
		cleanAvailablePos();
		if (id < 8)
		{
			if (movable(Vector2(currentPos.x, currentPos.y + 1)))
				availablePos.push_back(Vector2(currentPos.x, currentPos.y + 1));
			if (currentPos.y > GameParameter::BLACKRIVERSIDE)
			{
				if (movable(Vector2(currentPos.x+1, currentPos.y )))
					availablePos.push_back(Vector2(currentPos.x+1, currentPos.y ));
				if (movable(Vector2(currentPos.x-1, currentPos.y )))
					availablePos.push_back(Vector2(currentPos.x-1, currentPos.y ));
			}
		}
		else
		{
			if (movable(Vector2(currentPos.x, currentPos.y - 1)))
				availablePos.push_back(Vector2(currentPos.x, currentPos.y - 1));
			if (currentPos.y < GameParameter::REDRIVERSIDE)
			{
				if (movable(Vector2(currentPos.x + 1, currentPos.y)))
					availablePos.push_back(Vector2(currentPos.x + 1, currentPos.y));
				if (movable(Vector2(currentPos.x - 1, currentPos.y)))
					availablePos.push_back(Vector2(currentPos.x - 1, currentPos.y));
			}
		}
	}
};
#endif