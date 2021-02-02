#include"Manager.h"
Manager* Manager::instance;

Manager::Manager()
{
	Botmode = false;
	init();
}

void Manager::init()
{
	ChessBot::instance = new ChessBot();
	InputSystem::Instance = new InputSystem();
	Display::Instance = new Display();
	gameOver = false;
	startT = clock();
	endT = clock();
	checkMate = -1;
	option = 0;
	startOption = 0;

}

void Manager::start()
{
	
	system("CLS");
	Board::instance->pushBoard();
	Display::Instance->drawAll();
	Display::Instance->eraseRecord();
	Display::Instance->record = 0;
	//vector<string>().swap(Display::Instance->records);
	routeSelect();
	while (!gameOver)
	{
		double timeFrame = endT - startT;
		if (timeFrame >= GameParameter::FRAMERATE)
		{
		InputSystem::Instance->keyUpdate();
		InputSystem::Instance->cursorUpdate();
			update();
			render();
			startT = clock();
		
		}
		endT = clock();
	}
	Botmode = false;
	Title();
}

void Manager::render()
{
	Display::Instance->drawCursor(InputSystem::Instance->cursor);
}

void Manager::update()
{

	openMenu();
	roundCtrl();	
	winConditionCheck();
	checkMateCheck();

}

void Manager::winConditionCheck()
{
	gameOver = true;
	bool f = false;
	for(int i=0;i<GameParameter::BOARDHEIGHT;i++)
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			if (Board::instance->boardState[i][j]->id == 1)
			{
				f = true;
			}
			if (f&&Board::instance->boardState[i][j]->id == 8)
			{
				gameOver = false;
			}
		}
	if (gameOver)
	{
		round = !round;
		Display::Instance->drawEnd();
	}
}

void Manager::routeSelect()
{
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
			Board::instance->boardState[i][j]->select();
}

void Manager::roundCtrl()
{
	Vector2 v = InputSystem::Instance->cursor;
	if (InputSystem::Instance->keyState[vaildiInput::enter] && round == 1 && Board::instance->boardState[v.y][v.x]->id > 7)
	{
		//Board::instance->boardState[v.y][v.x]->select();
		routeSelect();
		Display::Instance->drawPath();
		Display::Instance->drawInfo();
		InputSystem::Instance->choose();
		
		
	}
	else if (!Botmode&&InputSystem::Instance->keyState[vaildiInput::enter] && round == 0 && Board::instance->boardState[v.y][v.x]->id < 8 && Board::instance->boardState[v.y][v.x]->id != 0)
	{
		routeSelect();
		//Board::instance->boardState[v.y][v.x]->select();
		Display::Instance->drawPath();
		Display::Instance->drawInfo();
		InputSystem::Instance->choose();
	}
	 if (Botmode&&round == 0)
	{
		ChessBot::instance->update();
	}
	Display::Instance->drawTurn();

	ofstream o("debu.txt");
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
			o << Board::instance->boardState[i][j]->id<<" ";
		o << endl;
	}
	o.close();
}

void Manager::checkMateCheck()
{
	Display::Instance->eraseCheckmate();
	checkMate = -1;
	for(int i=0;i<GameParameter::BOARDHEIGHT;i++)
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			
			for (int k = 0; k < Board::instance->boardState[i][j]->availablePos.size(); k++)
			{
				Vector2 pos = Board::instance->boardState[i][j]->availablePos[k];
				if (Board::instance->boardState[pos.y][pos.x]->id == 1 && round==0)
					checkMate = 1;
				else if (Board::instance->boardState[pos.y][pos.x]->id == 8 && round == 1)
					checkMate = 0;
			}
		}
	Display::Instance->drawCheckmate();
	
}

void Manager::withdraw()
{
	char tmp;
	bool flag=false;
	Display::Instance->drawWithdrawWindow();
	while(!flag)
	{
		tmp = _getch();
		if (tmp == 13)
		{
			flag = true;
#ifndef GET_CH_ONCE
			tmp = _getch();
#endif 

			
		}
		else {
			switch (tmp = _getch())
			{
			case 77: //right
			case 75: //left			
				Display::Instance->drawWithdrawPrompt();
				break;
			}
		}
	}
	Display::Instance->eraseWithdrawWindow();

	int idx = Board::instance->record.size() - 3;

	if (Display::Instance->withdraw||idx < 0)
		return;
	//Manager::instance->round = !Manager::instance->round;
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			Chess* temp = Board::instance->boardState[i][j];
			Board::instance->boardState[i][j] = Board::instance->constructorInvoker(Board::instance->record[idx][i][j]->id);
			Board::instance->boardState[i][j]->currentPos = Board::instance->record[idx][i][j]->currentPos;
			delete temp;
		}
	}
	Board::instance->record.erase(Board::instance->record.end() - 2, Board::instance->record.end());
	//Board::instance->record.pop_back();
	routeSelect();
	Display::Instance->drawBoard();
	Display::Instance->eraseRecord();
	Display::Instance->eraseRecord();
}

void Manager::restart()
{
	releaseBoard();
	delete Board::instance;
	delete InputSystem::Instance ;
	delete Display::Instance ;
	Board::instance = new Board();
	init();
	start();
}

void Manager::save()
{
	ofstream outputStream("RecordFile.txt");
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			outputStream << Board::instance->boardState[i][j]->id;
			if (j != GameParameter::BOARDWIDTH - 1)
				outputStream << " ";
		}
		outputStream << endl;
	}
	outputStream << Manager::instance->round << endl;
	outputStream.close();
}

void Manager::load()
{
	releaseBoard();
	Display::Instance->eraseRecord();
	ifstream inputStream("RecordFile.txt");
	int tmp;
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		vector<Chess*> temp;

		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{

			inputStream >> tmp;
			temp.push_back(Board::instance->constructorInvoker(tmp));
			temp[j]->currentPos = Vector2(j, i);
		}
		Board::instance->boardState.push_back(temp);
		temp.clear();
	}
	inputStream >> Manager::instance->round;
	
	inputStream.close();
	gameOver = false;
}

void Manager::doOption()
{
	switch (option)
	{
	case 0:
		save();
		break;
	case 1:
		restart();
		break;
	case 2:
		Botmode = false;
		Title();
		
		break;
	case 3:
		quit();
		break;
	
	}
}

void Manager::openMenu()
{
	if (!InputSystem::Instance->keyState[vaildiInput::ESC])
		return;
	Display::Instance->drawMenu();
	bool flag = false;
	while (!flag)
	{
		char tmp = _getch();
		if (tmp == 27)
		{
			
			flag = true;
		
#ifndef GET_CH_ONCE
			tmp = _getch();
#endif 
		}
		else if (tmp == 13)
		{
#ifndef GET_CH_ONCE
			tmp = _getch();
#endif 
			flag = true;
			InputSystem::Instance->keyState[vaildiInput::ESC] = false;
			doOption();
		}
		else
		{
			switch (tmp = _getch())
			{
			case 72:
				//up
				option--;
				break;
			case 80:
				//down
				option++;
				break;
			}
			if (option < 0)
				option = 3;
			else if (option > 3)
				option = 0;
			Display::Instance->chooseOption();
		}

	}
	Display::Instance->eraseMenu();
}

void Manager::quit()
{
	exit(0);
}

void Manager::Title()
{
	
	system("CLS");
	Board::instance = new Board();
	Display::Instance->drawStartScene();
	bool flag = false;
	while (!flag)
	{
		char tmp = _getch();
		if (tmp == 13)
		{
#ifndef GET_CH_ONCE
			tmp = _getch();
#endif 
			flag = true;
			doStartOption();
		}
		else if (tmp == 46)
		{
#ifndef GET_CH_ONCE
			tmp = _getch();
#endif 
			Botmode = true;
		}
		else
		{
			switch (tmp = _getch())
			{
			case 72:
				//up
				startOption--;
				break;
			case 80:
				//down
				startOption++;
				break;
			}
			if (startOption < 0)
				startOption = 2;
			else if (startOption > 2)
				startOption = 0;
			Display::Instance->chooseStartOption();
		}

	}
}

void Manager::doStartOption()
{
	switch (startOption)
	{
	case 0:
		init();
		start();
		break;
	case 1:
		load();
		start();
		break;
	case 2:
		quit();
		break;
	default:
		break;
	}
}

void Manager::releaseBoard()
{
	if (Board::instance == NULL)
		return;
	system("CLS");
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
	{
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
		{
			delete Board::instance->boardState[i][j];
		}
		Board::instance->boardState[i].clear();
	}
	Board::instance->boardState.clear();

	for (int k = 0; k < Board::instance->record.size(); k++) {
		for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
		{
			for (int j = 0; j < GameParameter::BOARDWIDTH; j++)
			{
				delete Board::instance->record[k][i][j];
			}
			Board::instance->record[k][i].clear();
		}
		Board::instance->record[k].clear();
	}
	Board::instance->record.clear();
}