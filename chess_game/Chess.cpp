#include"Chess.h"
bool Chess::operator==(const Chess& source)
{
	if (id == source.id)
		return true;
	else
		return false;
}
bool Chess::empty(Vector2 pos)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < GameParameter::BOARDWIDTH && pos.y < GameParameter::BOARDHEIGHT)
		return (Board::instance->boardState[pos.y][pos.x]->id == 0);
	else
		return false;
}
bool Chess::movable(Vector2 pos)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < GameParameter::BOARDWIDTH && pos.y < GameParameter::BOARDHEIGHT)
	{
		if (id < 8)
		{
			if ((id == 1 || id == 2) && pos.x >= GameParameter::PALACELEFT && pos.x <= GameParameter::PALACERIGHT && pos.y <= GameParameter::BLACKPALACETOP)
			{
				if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id > 7))
					return true;
			}
			else if (id == 1 || id == 2)
				return false;
			else if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id > 7))
				return true;
		}
		else
		{
			if ((id == 8 || id == 9) && pos.x >= GameParameter::PALACELEFT && pos.x <= GameParameter::PALACERIGHT && pos.y >= GameParameter::REDPALACETOP)
			{
				if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id < 8))
					return true;
			}
			else if (id == 8 || id == 9)
				return false;
			else if ((empty(pos)) || (Board::instance->boardState[pos.y][pos.x]->id < 8))
				return true;
		}
	}
	return false;
}

Chess::Chess(int in)
{
	id = in;
	iconSelector(in);
}

Chess::Chess()
{
	
	id = 0;
	icon = "";
}

void Chess::iconSelector(int in)
{
	switch (in)
	{
		case 1:
			icon = "�N";
			break;
		case 2:
			icon = "�h";
			break;
		case 3:
			icon = "�H";
			break;
		case 4:
			icon = "��";
			break;
		case 5:
			icon = "��";
			break;
		case 6:
			icon = "�]";
			break;
		case 7:
			icon = "��";
			break;
		case 8:
			icon = "��";
			break;
		case 9:
			icon = "�K";
			break;
		case 10:
			icon = "��";
			break;
		case 11:
			icon = "��";
			break;
		case 12:
			icon = "�X";
			break;
		case 13:
			icon = "��";
			break;
		case 14:
			icon = "�L";
			break;
		default:
			icon = "";
			break;
	}
}

void Chess::cleanAvailablePos() {
	availablePos.clear();
}