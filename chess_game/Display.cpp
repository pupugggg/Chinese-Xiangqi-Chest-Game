#include "Displayer.h"
#pragma comment(lib, "winmm.lib")

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
Display* Display::Instance;
Display::Display() : record(0)
{
	Init();
}

void Display::Init()
{
	defaultBoard[0] = "╔═╤═╤═╤═╤═╤═╤═╤═╗";
	defaultBoard[1] = "║  │  │  │＼│／│  │  │  ║";
	defaultBoard[2] = "║─┼─┼─┼─┼─┼─┼─┼─║";
	defaultBoard[3] = "║  │  │  │／│＼│  │  │  ║";
	defaultBoard[4] = "║─┼─┼─┼─┼─┼─┼─┼─║";
	defaultBoard[5] = "║  │  │  │  │  │  │  │  ║";
	defaultBoard[6] = "║─┼─┼─┼─┼─┼─┼─┼─║";
	defaultBoard[7] = "║  │  │  │  │  │  │  │  ║";
	defaultBoard[8] = "║─┴─┴─┴─┴─┴─┴─┴─║";
	defaultBoard[9] = "║      楚河           漢界     ║";
	defaultBoard[10] = "║─┬─┬─┬─┬─┬─┬─┬─║";
	defaultBoard[11] = "║  │  │  │  │  │  │  │  ║";
	defaultBoard[12] = "║─┼─┼─┼─┼─┼─┼─┼─║";
	defaultBoard[13] = "║  │  │  │  │  │  │  │  ║";
	defaultBoard[14] = "║─┼─┼─┼─┼─┼─┼─┼─║";
	defaultBoard[15] = "║  │  │  │＼│／│  │  │  ║";
	defaultBoard[16] = "║─┼─┼─┼─┼─┼─┼─┼─║";
	defaultBoard[17] = "║  │  │  │／│＼│  │  │  ║";
	defaultBoard[18] = "╚═╧═╧═╧═╧═╧═╧═╧═╝";

	cursor.X = GameParameter::OFFSET_BOARD_X;
	cursor.Y = GameParameter::OFFSET_BOARD_Y;

	startOptions[0] = "開  新  遊  戲";
	startOptions[1] = "繼  續  遊  戲";
	startOptions[2] = "離  開  遊  戲";

	options[0] = "儲存遊戲";
	options[1] = "重新開始";
	options[2] = "回主選單";
	options[3] = "離開遊戲";
}

void Display::drawAll()
{	
	const string right[19] = {
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"║                              ║",
		"╠═══════════════╣",
		"║ Esc 選單    < 悔棋    >還原  ║",
		"║                              ║",
		"║    Enter     選取棋子        ║",
		"║                              ║",
		"║      ↑                      ║",
		"║    ←  →  方向鍵控制游標    ║"
	};

	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	cout << "╔═══════════════════════════════════════════════════╗\n";
	cout << "║╔════ 戰 況 顯 示  ════╗";
	SetConsoleTextAttribute(hConsole, 253); // 白底紫字
	cout << "１  ２  ３  ４  ５  ６  ７  ８  ９";
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	cout << "╔═══════════════╗║\n";	

	for (int i = 0; i < 19; i++)
	{
		cout << "║"; // 外框左邊
		cout << "║                              ║"; // 左邊紀錄
		SetConsoleTextAttribute(hConsole, 240); // 白底黑字
		cout << defaultBoard[i]; // 棋盤
		SetConsoleTextAttribute(hConsole, 7); // 黑底白字
		cout << right[i]; // 右邊狀態
		cout << "║"; // 外框右邊
		cout << endl;
	}

	cout << "║║                              ║";
	SetConsoleTextAttribute(hConsole, 253);
	cout << "九  八  七  六  五  四  三  二  一";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "║      ↓                      ║║\n";
	cout << "║╚═══════════════╝                                  ╚═══════════════╝║\n";
	cout << "╚═══════════════════════════════════════════════════╝\n";

	gotoXY(GameParameter::OFFSET_INFO_TURN_X - 10, GameParameter::OFFSET_INFO_TURN_Y);
	SetConsoleTextAttribute(hConsole, 11); // 黑底青字
	cout << "現在輪到          下棋";
	drawTurn();

	// 棋子
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++) 
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++) {		
			drawCursor(Vector2(j, i));
			if(Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // 白底黑字
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // 白底紅字
			cout << Board::instance->boardState[i][j]->icon;
		}		

	drawCursor(Vector2(0, 0));
}

void Display::drawBoard()
{
	// 畫棋盤
	SetConsoleTextAttribute(hConsole, 240); // 白底黑字
	drawCursor(Vector2(0, 0));
	cout << "╔═══════════════╗";
	for (int i = 0; i < 10; i++)
	{
		drawCursor(Vector2(0, i));
		cout << defaultBoard[i * 2]; // 棋盤
		cout << endl;
	}
	// 放棋子
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++) {
			drawCursor(Vector2(j, i));
			if (Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // 白底黑字
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // 白底紅字
			cout << Board::instance->boardState[i][j]->icon;
		}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::gotoXY(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(hConsole, cursor);
}

void Display::drawCursor(Vector2 cs)
{
	cursor.X = (cs.x * 4) + GameParameter::OFFSET_BOARD_X;
	cursor.Y = (cs.y * 2) + GameParameter::OFFSET_BOARD_Y;
	SetConsoleCursorPosition(hConsole, cursor);
}

void Display::drawPath()
{
	const Vector2& cs = InputSystem::Instance->cursor;
	const vector<Vector2>& pos = Board::instance->boardState[cs.y][cs.x]->availablePos;
	for (int i = 0; i < pos.size(); i++)
	{
		const Chess* chess = Board::instance->boardState[pos[i].y][pos[i].x];
		drawCursor(pos[i]);
		if (!chess->id)
		{
			SetConsoleTextAttribute(hConsole, 144); // 藍底黑字
			for (int j = 0; j < 2; j++) {
				cout << defaultBoard[pos[i].y * 2][pos[i].x * 4 + j];
			}
		}
		else {
			if (chess->id >= 8 && chess->id <= 14)
				SetConsoleTextAttribute(hConsole, 157); // 藍底紅字
			else
				SetConsoleTextAttribute(hConsole, 144); // 藍底黑字
		
			cout << chess->icon;
		}
	}
	drawCursor(cs);
}

void Display::erasePath(Vector2 p)
{
	const vector<Vector2>& pos = Board::instance->boardState[p.y][p.x]->availablePos;
	for (int i = 0; i < pos.size(); i++)
	{
		const Chess* chess = Board::instance->boardState[pos[i].y][pos[i].x];
		drawCursor(pos[i]);
		if (!chess->id)
		{
			SetConsoleTextAttribute(hConsole, 240); // 藍底黑字
			for (int j = 0; j < 2; j++) {
				cout << defaultBoard[pos[i].y * 2][pos[i].x * 4 + j];
			}
		}
		else {
			if (chess->id >= 8 && chess->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // 白底紅字
			else
				SetConsoleTextAttribute(hConsole, 240); // 白底黑字

			cout << chess->icon;
		}	
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawRecord(Vector2 pos)
{
	Vector2& cs = InputSystem::Instance->cursor; // 游標
	Chess* chess = Board::instance->boardState[cs.y][cs.x]; // 游標位置的棋子
	gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + record % 20);
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	//record++; // 開頭就先給它來個加一
	if (!(record % 20)) { // 格子滿了
		for (int i = 0; i < 20; i++) { // 清空紀錄
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + i);
			cout << "                      ";
		} // 回到第一筆的地方 
		gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y);
	}
	printf("%3d ", ++record); //把有幾筆資料加一之後print

	// 紅方
	if (Manager::instance->round) {
		SetConsoleTextAttribute(hConsole, 4); // 黑底紅字	
		cout << "紅";
		SetConsoleTextAttribute(hConsole, 7); // 黑底白字	
		string str = " : " + chess->icon + "  ";
		str += getChineseNum(9 - pos.x); // 原本在第幾路

		if (cs.y == pos.y) {
			str += "  平  " + getChineseNum(9 - cs.x); // 移到第幾路
			cout << str;
			records.push_back(str);
			return;
		}

		if (cs.y < pos.y)
			str += "  進  ";
		else if (cs.y > pos.y)
			str += "  退  ";

		if (chess->id == 9 || chess->id == 10 || chess->id == 12) // 仕像傌
			str += getChineseNum(9 - cs.x); // 移到第幾路
		else // 將車包卒
			str += getChineseNum(abs(cs.y - pos.y)); // 跟原本相差幾格
		cout << str;
		records.push_back(str);
	} // 黑方
	else {
		SetConsoleTextAttribute(hConsole, 8); // 黑底灰字
		cout << "黑";
		SetConsoleTextAttribute(hConsole, 7); // 黑底白字	
		string str = " : " + chess->icon + "  ";
		str += getFullWidthNum(pos.x + 1); // 原本在第幾路

		if (cs.y == pos.y) {
			str += "  平  " + getFullWidthNum(cs.x + 1); // 移到第幾路
			cout << str;
			records.push_back(str);
			return;
		}

		if (cs.y > pos.y)
			str += "  進  ";
		else if (cs.y < pos.y)
			str += "  退  ";

		if (chess->id == 2 || chess->id == 3 || chess->id == 5) // 士象馬
			str += getFullWidthNum(cs.x + 1); // 移到第幾路
		else // 將車包卒
			str += getFullWidthNum(abs(cs.y - pos.y)); // 跟原本相差幾格

		cout << str;
		records.push_back(str);
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawRecord2(Vector2 start, Vector2 end)
{
	Chess* chess = Board::instance->boardState[end.y][end.x]; // 棋子結束的位置
	gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + record % 20);
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	//record++; // 開頭就先給它來個加一
	if (!(record % 20)) { // 格子滿了
		for (int i = 0; i < 20; i++) { // 清空紀錄
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + i);
			cout << "                      ";
		} // 回到第一筆的地方 
		gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y);
	}
	printf("%3d ", ++record); //把有幾筆資料加一之後print

	// 紅方
	if (Manager::instance->round) {
		SetConsoleTextAttribute(hConsole, 4); // 黑底紅字	
		cout << "紅";
		SetConsoleTextAttribute(hConsole, 7); // 黑底白字	
		string str = " : " + chess->icon + "  ";
		str += getChineseNum(9 - start.x); // 原本在第幾路

		if (end.y == start.y) {
			str += "  平  " + getChineseNum(9 - end.x); // 移到第幾路
			cout << str;
			records.push_back(str);
			return;
		}

		if (end.y < start.y)
			str += "  進  ";
		else if (end.y > start.y)
			str += "  退  ";

		if (chess->id == 9 || chess->id == 10 || chess->id == 12) // 仕像傌
			str += getChineseNum(9 - end.x); // 移到第幾路
		else // 將車包卒
			str += getChineseNum(abs(end.y - start.y)); // 跟原本相差幾格
		cout << str;
		records.push_back(str);
	} // 黑方
	else {
		SetConsoleTextAttribute(hConsole, 8); // 黑底灰字
		cout << "黑";
		SetConsoleTextAttribute(hConsole, 7); // 黑底白字	
		string str = " : " + chess->icon + "  ";
		str += getFullWidthNum(start.x + 1); // 原本在第幾路

		if (end.y == start.y) {
			str += "  平  " + getFullWidthNum(end.x + 1); // 移到第幾路
			cout << str;
			records.push_back(str);
			return;
		}

		if (end.y > start.y)
			str += "  進  ";
		else if (end.y < start.y)
			str += "  退  ";

		if (chess->id == 2 || chess->id == 3 || chess->id == 5) // 士象馬
			str += getFullWidthNum(end.x + 1); // 移到第幾路
		else // 將車包卒
			str += getFullWidthNum(abs(end.y - start.y)); // 跟原本相差幾格

		cout << str;
		records.push_back(str);
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::eraseRecord()
{
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	if ((record % 20 == 1) && (record != 1))
	{
		for (int i = -20; i < 0; i++) {
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + i + 20);
			printf("%3d ", record + i);
			if ((Manager::instance->round + i) % 2) {
				SetConsoleTextAttribute(hConsole, 8); // 黑底灰字
				cout << "黑";	
			}
			else {
				SetConsoleTextAttribute(hConsole, 4); // 黑底紅字	
				cout << "紅";
			}
			SetConsoleTextAttribute(hConsole, 7); // 黑底白字	
			cout << records[record - 1 + i];
		}
	}
	else
	{
		if (!(record % 20))
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + 19);
		else
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y - 1 + record % 20);
		cout << "                      ";
		drawCursor(InputSystem::Instance->cursor);
	}
	record--;
	if (record < 0)
		record = 0;
}

void Display::drawInfo()
{
	const Vector2& cs = InputSystem::Instance->cursor;
	gotoXY(GameParameter::OFFSET_INFO_CHESS_X, GameParameter::OFFSET_INFO_CHESS_Y);
	SetConsoleTextAttribute(hConsole, 11); // 黑底青字
	cout << "您選擇了  ";

	if (Manager::instance->round)
		SetConsoleTextAttribute(hConsole, 4); // 黑底紅字	
	else 
		SetConsoleTextAttribute(hConsole, 8); // 黑底灰字	

	cout << Board::instance->boardState[cs.y][cs.x]->icon;
	drawCursor(InputSystem::Instance->cursor);
}

void Display::eraseInfo()
{
	SetConsoleTextAttribute(hConsole, 4);
	const Vector2& cs = InputSystem::Instance->cursor;
	gotoXY(GameParameter::OFFSET_INFO_CHESS_X, GameParameter::OFFSET_INFO_CHESS_Y);
	cout << "              ";
	drawCursor(InputSystem::Instance->cursor);
	
}

void Display::drawTurn()
{
	gotoXY(GameParameter::OFFSET_INFO_TURN_X, GameParameter::OFFSET_INFO_TURN_Y);
 
	if (Manager::instance->round) {
		SetConsoleTextAttribute(hConsole, 4); // 黑底紅字	
		cout << "紅色方";
	}
	else {
		SetConsoleTextAttribute(hConsole, 8); // 黑底灰字
		cout << "黑色方";
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::moveChess(Vector2 pos)
{
	const Vector2& cs = InputSystem::Instance->cursor;
	const Chess* chess = Board::instance->boardState[pos.y][pos.x];

	if (chess->id >= 8 && chess->id <= 14)
		SetConsoleTextAttribute(hConsole, 252); // 白底紅字
	else
		SetConsoleTextAttribute(hConsole, 240); // 白底黑字

	// 把棋子移到游標的位子
	drawCursor(cs);
	cout << chess->icon;
	// 把棋子原本的位子清掉
	SetConsoleTextAttribute(hConsole, 240); // 白底黑字
	drawCursor(pos);
	for (int i = 0; i < 2; i++) {
		cout << defaultBoard[pos.y * 2][pos.x * 4 + i];
	}
	drawCursor(cs);
}

void Display::drawWithdrawWindow()
{
	SetConsoleTextAttribute(hConsole, 4); // 黑底紅字	
	gotoXY(GameParameter::OFFSET_BOARD_X + 4, GameParameter::OFFSET_BOARD_Y + 6);
	cout << "╔══════════╗";
	for (int i = 1; i < 6; i++) {
		gotoXY(GameParameter::OFFSET_BOARD_X + 4, GameParameter::OFFSET_BOARD_Y + 6 + i);
		cout << "║                    ║";
	}
	gotoXY(GameParameter::OFFSET_BOARD_X + 4, GameParameter::OFFSET_BOARD_Y + 12);
	cout << "╚══════════╝";
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 8);
	cout << "確定悔棋 ?";
	gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 10);
	cout << "是      否";	
	withdraw = false;
	drawWithdrawPrompt();
}

void Display::drawWithdrawPrompt()
{
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字

	if (withdraw) {	
		gotoXY(GameParameter::OFFSET_BOARD_X + 19, GameParameter::OFFSET_BOARD_Y + 10);	
		cout << "否";
		SetConsoleTextAttribute(hConsole, 240); // 白底黑字
		gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 10);
		cout << "是";
	}
	else {
		gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 10);
		cout << "是";
		SetConsoleTextAttribute(hConsole, 240); // 白底黑字
		gotoXY(GameParameter::OFFSET_BOARD_X + 19, GameParameter::OFFSET_BOARD_Y + 10);
		cout << "否";	
	}

	withdraw = !withdraw;
}

void Display::eraseWithdrawWindow()
{
	// 畫棋盤
	SetConsoleTextAttribute(hConsole, 240); // 白底黑字
	for (int i = 0; i < 7; i++) {
		gotoXY(4 + GameParameter::OFFSET_BOARD_X, 6 + i + GameParameter::OFFSET_BOARD_Y);
		for (int j = 4; j < 30; j++)
			cout << defaultBoard[6 + i][j];
	}
	// 放棋子
	for (int i = 3; i <= 6; i++)
		for (int j = 1; j <= 6; j++) {
			drawCursor(Vector2(j, i));
			if (Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // 白底黑字
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // 白底紅字
			cout << Board::instance->boardState[i][j]->icon;
		}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawMenu()
{
	SetConsoleTextAttribute(hConsole, 9); // 黑底藍字	
	gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 6);
	cout << "╔═════╗";
	for (int i = 1; i < 8; i += 2) {
		gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 6 + i);
		cout << "║          ║";
		gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 7 + i);
		cout << "╠═════╣";
	}
	gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 14);
	cout << "╚═════╝";

	chooseOption();
}

void Display::chooseOption()
{
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	for (int i = 0; i < 4; i++) {
		gotoXY(GameParameter::OFFSET_BOARD_X + 13, GameParameter::OFFSET_BOARD_Y + 7 + (i * 2));
		cout << options[i];
	}

	SetConsoleTextAttribute(hConsole, 240); // 白底黑字
	gotoXY(GameParameter::OFFSET_BOARD_X + 13, GameParameter::OFFSET_BOARD_Y + 7 + (Manager::instance->option * 2));
	cout << options[Manager::instance->option];
}

void Display::eraseMenu()
{
	// 畫棋盤
	SetConsoleTextAttribute(hConsole, 240); // 白底黑字
	for (int i = 0; i < 9; i++) {
		gotoXY(10 + GameParameter::OFFSET_BOARD_X, 6 + i + GameParameter::OFFSET_BOARD_Y);
		for (int j = 10; j < 28; j++)
			cout << defaultBoard[6 + i][j];
	}
	// 放棋子
	for (int i = 3; i <= 7; i++)
		for (int j = 3; j <= 6; j++) {
			drawCursor(Vector2(j, i));
			if (Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // 白底黑字
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // 白底紅字
			cout << Board::instance->boardState[i][j]->icon;
		}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawCheckmate()
{
	gotoXY(GameParameter::OFFSET_INFO_CHESS_X - 2, GameParameter::OFFSET_INFO_CHESS_Y + 3);

	if (Manager::instance->checkMate == 1) {
		SetConsoleTextAttribute(hConsole, 8); // 黑底灰字
		cout << "黑色方";
	}
	else if (!Manager::instance->checkMate) {
		SetConsoleTextAttribute(hConsole, 4); // 黑底紅字
		cout << "紅色方";
	}
	if (Manager::instance->checkMate != -1) {
		SetConsoleTextAttribute(hConsole, 11); // 黑底青字
		cout << "  被將軍了!";
		drawCursor(InputSystem::Instance->cursor);
	}	
}

void Display::eraseCheckmate()
{
	gotoXY(GameParameter::OFFSET_INFO_CHESS_X - 2, GameParameter::OFFSET_INFO_CHESS_Y + 3);
	SetConsoleTextAttribute(hConsole, 11); // 黑底青字
	cout << "                   ";
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawEnd()
{
	gotoXY(GameParameter::OFFSET_INFO_TURN_X - 10, GameParameter::OFFSET_INFO_TURN_Y);
	SetConsoleTextAttribute(hConsole, 7); // 黑底白字
	cout << "                      ";
	gotoXY(GameParameter::OFFSET_INFO_TURN_X - 6, GameParameter::OFFSET_INFO_TURN_Y);

	if (Manager::instance->round) {
		SetConsoleTextAttribute(hConsole, 4); // 黑底紅字	
		cout << "紅色方";
	}
	else {
		SetConsoleTextAttribute(hConsole, 8); // 黑底灰字
		cout << "黑色方";
	}
	SetConsoleTextAttribute(hConsole, 11); // 黑底青字
	cout << "  獲勝了!";

	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawStartScene()
{
	PlaySound(TEXT("ErikSatie-LePiccadilly.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // Play BGM

	// 清空螢幕
	for (int i = 0; i < 30; i++) {
		gotoXY(i, 0);
		for (int j = 0; j < 120; j++)
			cout << ' ';
	}

	// 畫格子
	SetConsoleTextAttribute(hConsole, 160); // 綠底黑字
	gotoXY(0, 0);
	cout << "╔═════════╗";
	for (int i = 0; i < 3; i++) {
		gotoXY(0, (i * 4) + 1);
		cout << "║                  ║";
		gotoXY(0, (i * 4) + 2);
		cout << "║                  ║";
		gotoXY(0, (i * 4) + 3);
		cout << "║                  ║";
		gotoXY(0, (i * 4) + 4);
		cout << "╠═════════╣";
	}
	gotoXY(0, 12);
	cout << "╚═════════╝";

	// 寫選項
	for (int i = 0; i < 3; i++) {
		gotoXY(4, (i * 4) + 2);
		cout << startOptions[i];
	}
	gotoXY(4, 3);
	cout << "───────";
}

void Display::chooseStartOption()
{
	SetConsoleTextAttribute(hConsole, 160); // 綠底黑字
	for (int i = 0; i < 3; i++) {
		gotoXY(4, (i * 4) + 3);
		cout << "              ";
	}
	gotoXY(4, (Manager::instance->startOption * 4) + 3);
	cout << "───────";
}

string Display::getChineseNum(int num)
{
	switch (num)
	{
	case 1:
		return "一";
	case 2:
		return "二";
	case 3:
		return "三";
	case 4:
		return "四";
	case 5:
		return "五";
	case 6:
		return "六";
	case 7:
		return "七";
	case 8:
		return "八";
	case 9:
		return "九";
	}
}

string Display::getFullWidthNum(int num)
{
	switch (num)
	{
	case 1:
		return "１";
	case 2:
		return "２";
	case 3:
		return "３";
	case 4:
		return "４";
	case 5:
		return "５";
	case 6:
		return "６";
	case 7:
		return "７";
	case 8:
		return "８";
	case 9:
		return "９";
	}
}