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
	defaultBoard[0] = "����������������������������������";
	defaultBoard[1] = "��  �x  �x  �x�@�x���x  �x  �x  ��";
	defaultBoard[2] = "���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��";
	defaultBoard[3] = "��  �x  �x  �x���x�@�x  �x  �x  ��";
	defaultBoard[4] = "���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��";
	defaultBoard[5] = "��  �x  �x  �x  �x  �x  �x  �x  ��";
	defaultBoard[6] = "���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��";
	defaultBoard[7] = "��  �x  �x  �x  �x  �x  �x  �x  ��";
	defaultBoard[8] = "���w�r�w�r�w�r�w�r�w�r�w�r�w�r�w��";
	defaultBoard[9] = "��      ���e           �~��     ��";
	defaultBoard[10] = "���w�s�w�s�w�s�w�s�w�s�w�s�w�s�w��";
	defaultBoard[11] = "��  �x  �x  �x  �x  �x  �x  �x  ��";
	defaultBoard[12] = "���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��";
	defaultBoard[13] = "��  �x  �x  �x  �x  �x  �x  �x  ��";
	defaultBoard[14] = "���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��";
	defaultBoard[15] = "��  �x  �x  �x�@�x���x  �x  �x  ��";
	defaultBoard[16] = "���w�q�w�q�w�q�w�q�w�q�w�q�w�q�w��";
	defaultBoard[17] = "��  �x  �x  �x���x�@�x  �x  �x  ��";
	defaultBoard[18] = "����������������������������������";

	cursor.X = GameParameter::OFFSET_BOARD_X;
	cursor.Y = GameParameter::OFFSET_BOARD_Y;

	startOptions[0] = "�}  �s  �C  ��";
	startOptions[1] = "�~  ��  �C  ��";
	startOptions[2] = "��  �}  �C  ��";

	options[0] = "�x�s�C��";
	options[1] = "���s�}�l";
	options[2] = "�^�D���";
	options[3] = "���}�C��";
}

void Display::drawAll()
{	
	const string right[19] = {
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"��                              ��",
		"����������������������������������",
		"�� Esc ���    < ����    >�٭�  ��",
		"��                              ��",
		"��    Enter     ����Ѥl        ��",
		"��                              ��",
		"��      ��                      ��",
		"��    ��  ��  ��V�䱱����    ��"
	};

	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	cout << "����������������������������������������������������������������������������������������������������������\n";
	cout << "������������ �� �p �� ��  ����������";
	SetConsoleTextAttribute(hConsole, 253); // �թ����r
	cout << "��  ��  ��  ��  ��  ��  ��  ��  ��";
	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	cout << "������������������������������������\n";	

	for (int i = 0; i < 19; i++)
	{
		cout << "��"; // �~�إ���
		cout << "��                              ��"; // �������
		SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
		cout << defaultBoard[i]; // �ѽL
		SetConsoleTextAttribute(hConsole, 7); // �©��զr
		cout << right[i]; // �k�䪬�A
		cout << "��"; // �~�إk��
		cout << endl;
	}

	cout << "����                              ��";
	SetConsoleTextAttribute(hConsole, 253);
	cout << "�E  �K  �C  ��  ��  �|  �T  �G  �@";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "��      ��                      ����\n";
	cout << "������������������������������������                                  ������������������������������������\n";
	cout << "����������������������������������������������������������������������������������������������������������\n";

	gotoXY(GameParameter::OFFSET_INFO_TURN_X - 10, GameParameter::OFFSET_INFO_TURN_Y);
	SetConsoleTextAttribute(hConsole, 11); // �©��C�r
	cout << "�{�b����          �U��";
	drawTurn();

	// �Ѥl
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++) 
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++) {		
			drawCursor(Vector2(j, i));
			if(Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // �թ����r
			cout << Board::instance->boardState[i][j]->icon;
		}		

	drawCursor(Vector2(0, 0));
}

void Display::drawBoard()
{
	// �e�ѽL
	SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
	drawCursor(Vector2(0, 0));
	cout << "����������������������������������";
	for (int i = 0; i < 10; i++)
	{
		drawCursor(Vector2(0, i));
		cout << defaultBoard[i * 2]; // �ѽL
		cout << endl;
	}
	// ��Ѥl
	for (int i = 0; i < GameParameter::BOARDHEIGHT; i++)
		for (int j = 0; j < GameParameter::BOARDWIDTH; j++) {
			drawCursor(Vector2(j, i));
			if (Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // �թ����r
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
			SetConsoleTextAttribute(hConsole, 144); // �ũ��¦r
			for (int j = 0; j < 2; j++) {
				cout << defaultBoard[pos[i].y * 2][pos[i].x * 4 + j];
			}
		}
		else {
			if (chess->id >= 8 && chess->id <= 14)
				SetConsoleTextAttribute(hConsole, 157); // �ũ����r
			else
				SetConsoleTextAttribute(hConsole, 144); // �ũ��¦r
		
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
			SetConsoleTextAttribute(hConsole, 240); // �ũ��¦r
			for (int j = 0; j < 2; j++) {
				cout << defaultBoard[pos[i].y * 2][pos[i].x * 4 + j];
			}
		}
		else {
			if (chess->id >= 8 && chess->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // �թ����r
			else
				SetConsoleTextAttribute(hConsole, 240); // �թ��¦r

			cout << chess->icon;
		}	
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawRecord(Vector2 pos)
{
	Vector2& cs = InputSystem::Instance->cursor; // ���
	Chess* chess = Board::instance->boardState[cs.y][cs.x]; // ��Ц�m���Ѥl
	gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + record % 20);
	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	//record++; // �}�Y�N�������ӭӥ[�@
	if (!(record % 20)) { // ��l���F
		for (int i = 0; i < 20; i++) { // �M�Ŭ���
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + i);
			cout << "                      ";
		} // �^��Ĥ@�����a�� 
		gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y);
	}
	printf("%3d ", ++record); //�⦳�X����ƥ[�@����print

	// ����
	if (Manager::instance->round) {
		SetConsoleTextAttribute(hConsole, 4); // �©����r	
		cout << "��";
		SetConsoleTextAttribute(hConsole, 7); // �©��զr	
		string str = " : " + chess->icon + "  ";
		str += getChineseNum(9 - pos.x); // �쥻�b�ĴX��

		if (cs.y == pos.y) {
			str += "  ��  " + getChineseNum(9 - cs.x); // ����ĴX��
			cout << str;
			records.push_back(str);
			return;
		}

		if (cs.y < pos.y)
			str += "  �i  ";
		else if (cs.y > pos.y)
			str += "  �h  ";

		if (chess->id == 9 || chess->id == 10 || chess->id == 12) // �K���X
			str += getChineseNum(9 - cs.x); // ����ĴX��
		else // �N���]��
			str += getChineseNum(abs(cs.y - pos.y)); // ��쥻�ۮt�X��
		cout << str;
		records.push_back(str);
	} // �¤�
	else {
		SetConsoleTextAttribute(hConsole, 8); // �©��Ǧr
		cout << "��";
		SetConsoleTextAttribute(hConsole, 7); // �©��զr	
		string str = " : " + chess->icon + "  ";
		str += getFullWidthNum(pos.x + 1); // �쥻�b�ĴX��

		if (cs.y == pos.y) {
			str += "  ��  " + getFullWidthNum(cs.x + 1); // ����ĴX��
			cout << str;
			records.push_back(str);
			return;
		}

		if (cs.y > pos.y)
			str += "  �i  ";
		else if (cs.y < pos.y)
			str += "  �h  ";

		if (chess->id == 2 || chess->id == 3 || chess->id == 5) // �h�H��
			str += getFullWidthNum(cs.x + 1); // ����ĴX��
		else // �N���]��
			str += getFullWidthNum(abs(cs.y - pos.y)); // ��쥻�ۮt�X��

		cout << str;
		records.push_back(str);
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawRecord2(Vector2 start, Vector2 end)
{
	Chess* chess = Board::instance->boardState[end.y][end.x]; // �Ѥl��������m
	gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + record % 20);
	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	//record++; // �}�Y�N�������ӭӥ[�@
	if (!(record % 20)) { // ��l���F
		for (int i = 0; i < 20; i++) { // �M�Ŭ���
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + i);
			cout << "                      ";
		} // �^��Ĥ@�����a�� 
		gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y);
	}
	printf("%3d ", ++record); //�⦳�X����ƥ[�@����print

	// ����
	if (Manager::instance->round) {
		SetConsoleTextAttribute(hConsole, 4); // �©����r	
		cout << "��";
		SetConsoleTextAttribute(hConsole, 7); // �©��զr	
		string str = " : " + chess->icon + "  ";
		str += getChineseNum(9 - start.x); // �쥻�b�ĴX��

		if (end.y == start.y) {
			str += "  ��  " + getChineseNum(9 - end.x); // ����ĴX��
			cout << str;
			records.push_back(str);
			return;
		}

		if (end.y < start.y)
			str += "  �i  ";
		else if (end.y > start.y)
			str += "  �h  ";

		if (chess->id == 9 || chess->id == 10 || chess->id == 12) // �K���X
			str += getChineseNum(9 - end.x); // ����ĴX��
		else // �N���]��
			str += getChineseNum(abs(end.y - start.y)); // ��쥻�ۮt�X��
		cout << str;
		records.push_back(str);
	} // �¤�
	else {
		SetConsoleTextAttribute(hConsole, 8); // �©��Ǧr
		cout << "��";
		SetConsoleTextAttribute(hConsole, 7); // �©��զr	
		string str = " : " + chess->icon + "  ";
		str += getFullWidthNum(start.x + 1); // �쥻�b�ĴX��

		if (end.y == start.y) {
			str += "  ��  " + getFullWidthNum(end.x + 1); // ����ĴX��
			cout << str;
			records.push_back(str);
			return;
		}

		if (end.y > start.y)
			str += "  �i  ";
		else if (end.y < start.y)
			str += "  �h  ";

		if (chess->id == 2 || chess->id == 3 || chess->id == 5) // �h�H��
			str += getFullWidthNum(end.x + 1); // ����ĴX��
		else // �N���]��
			str += getFullWidthNum(abs(end.y - start.y)); // ��쥻�ۮt�X��

		cout << str;
		records.push_back(str);
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::eraseRecord()
{
	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	if ((record % 20 == 1) && (record != 1))
	{
		for (int i = -20; i < 0; i++) {
			gotoXY(GameParameter::OFFSET_RECORD_X, GameParameter::OFFSET_RECORD_Y + i + 20);
			printf("%3d ", record + i);
			if ((Manager::instance->round + i) % 2) {
				SetConsoleTextAttribute(hConsole, 8); // �©��Ǧr
				cout << "��";	
			}
			else {
				SetConsoleTextAttribute(hConsole, 4); // �©����r	
				cout << "��";
			}
			SetConsoleTextAttribute(hConsole, 7); // �©��զr	
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
	SetConsoleTextAttribute(hConsole, 11); // �©��C�r
	cout << "�z��ܤF  ";

	if (Manager::instance->round)
		SetConsoleTextAttribute(hConsole, 4); // �©����r	
	else 
		SetConsoleTextAttribute(hConsole, 8); // �©��Ǧr	

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
		SetConsoleTextAttribute(hConsole, 4); // �©����r	
		cout << "�����";
	}
	else {
		SetConsoleTextAttribute(hConsole, 8); // �©��Ǧr
		cout << "�¦��";
	}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::moveChess(Vector2 pos)
{
	const Vector2& cs = InputSystem::Instance->cursor;
	const Chess* chess = Board::instance->boardState[pos.y][pos.x];

	if (chess->id >= 8 && chess->id <= 14)
		SetConsoleTextAttribute(hConsole, 252); // �թ����r
	else
		SetConsoleTextAttribute(hConsole, 240); // �թ��¦r

	// ��Ѥl�����Ъ���l
	drawCursor(cs);
	cout << chess->icon;
	// ��Ѥl�쥻����l�M��
	SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
	drawCursor(pos);
	for (int i = 0; i < 2; i++) {
		cout << defaultBoard[pos.y * 2][pos.x * 4 + i];
	}
	drawCursor(cs);
}

void Display::drawWithdrawWindow()
{
	SetConsoleTextAttribute(hConsole, 4); // �©����r	
	gotoXY(GameParameter::OFFSET_BOARD_X + 4, GameParameter::OFFSET_BOARD_Y + 6);
	cout << "������������������������";
	for (int i = 1; i < 6; i++) {
		gotoXY(GameParameter::OFFSET_BOARD_X + 4, GameParameter::OFFSET_BOARD_Y + 6 + i);
		cout << "��                    ��";
	}
	gotoXY(GameParameter::OFFSET_BOARD_X + 4, GameParameter::OFFSET_BOARD_Y + 12);
	cout << "������������������������";
	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 8);
	cout << "�T�w���� ?";
	gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 10);
	cout << "�O      �_";	
	withdraw = false;
	drawWithdrawPrompt();
}

void Display::drawWithdrawPrompt()
{
	SetConsoleTextAttribute(hConsole, 7); // �©��զr

	if (withdraw) {	
		gotoXY(GameParameter::OFFSET_BOARD_X + 19, GameParameter::OFFSET_BOARD_Y + 10);	
		cout << "�_";
		SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
		gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 10);
		cout << "�O";
	}
	else {
		gotoXY(GameParameter::OFFSET_BOARD_X + 11, GameParameter::OFFSET_BOARD_Y + 10);
		cout << "�O";
		SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
		gotoXY(GameParameter::OFFSET_BOARD_X + 19, GameParameter::OFFSET_BOARD_Y + 10);
		cout << "�_";	
	}

	withdraw = !withdraw;
}

void Display::eraseWithdrawWindow()
{
	// �e�ѽL
	SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
	for (int i = 0; i < 7; i++) {
		gotoXY(4 + GameParameter::OFFSET_BOARD_X, 6 + i + GameParameter::OFFSET_BOARD_Y);
		for (int j = 4; j < 30; j++)
			cout << defaultBoard[6 + i][j];
	}
	// ��Ѥl
	for (int i = 3; i <= 6; i++)
		for (int j = 1; j <= 6; j++) {
			drawCursor(Vector2(j, i));
			if (Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // �թ����r
			cout << Board::instance->boardState[i][j]->icon;
		}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawMenu()
{
	SetConsoleTextAttribute(hConsole, 9); // �©��Ŧr	
	gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 6);
	cout << "��������������";
	for (int i = 1; i < 8; i += 2) {
		gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 6 + i);
		cout << "��          ��";
		gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 7 + i);
		cout << "��������������";
	}
	gotoXY(GameParameter::OFFSET_BOARD_X + 10, GameParameter::OFFSET_BOARD_Y + 14);
	cout << "��������������";

	chooseOption();
}

void Display::chooseOption()
{
	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	for (int i = 0; i < 4; i++) {
		gotoXY(GameParameter::OFFSET_BOARD_X + 13, GameParameter::OFFSET_BOARD_Y + 7 + (i * 2));
		cout << options[i];
	}

	SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
	gotoXY(GameParameter::OFFSET_BOARD_X + 13, GameParameter::OFFSET_BOARD_Y + 7 + (Manager::instance->option * 2));
	cout << options[Manager::instance->option];
}

void Display::eraseMenu()
{
	// �e�ѽL
	SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
	for (int i = 0; i < 9; i++) {
		gotoXY(10 + GameParameter::OFFSET_BOARD_X, 6 + i + GameParameter::OFFSET_BOARD_Y);
		for (int j = 10; j < 28; j++)
			cout << defaultBoard[6 + i][j];
	}
	// ��Ѥl
	for (int i = 3; i <= 7; i++)
		for (int j = 3; j <= 6; j++) {
			drawCursor(Vector2(j, i));
			if (Board::instance->boardState[i][j]->id >= 1 && Board::instance->boardState[i][j]->id <= 7)
				SetConsoleTextAttribute(hConsole, 240); // �թ��¦r
			else if (Board::instance->boardState[i][j]->id >= 8 && Board::instance->boardState[i][j]->id <= 14)
				SetConsoleTextAttribute(hConsole, 252); // �թ����r
			cout << Board::instance->boardState[i][j]->icon;
		}
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawCheckmate()
{
	gotoXY(GameParameter::OFFSET_INFO_CHESS_X - 2, GameParameter::OFFSET_INFO_CHESS_Y + 3);

	if (Manager::instance->checkMate == 1) {
		SetConsoleTextAttribute(hConsole, 8); // �©��Ǧr
		cout << "�¦��";
	}
	else if (!Manager::instance->checkMate) {
		SetConsoleTextAttribute(hConsole, 4); // �©����r
		cout << "�����";
	}
	if (Manager::instance->checkMate != -1) {
		SetConsoleTextAttribute(hConsole, 11); // �©��C�r
		cout << "  �Q�N�x�F!";
		drawCursor(InputSystem::Instance->cursor);
	}	
}

void Display::eraseCheckmate()
{
	gotoXY(GameParameter::OFFSET_INFO_CHESS_X - 2, GameParameter::OFFSET_INFO_CHESS_Y + 3);
	SetConsoleTextAttribute(hConsole, 11); // �©��C�r
	cout << "                   ";
	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawEnd()
{
	gotoXY(GameParameter::OFFSET_INFO_TURN_X - 10, GameParameter::OFFSET_INFO_TURN_Y);
	SetConsoleTextAttribute(hConsole, 7); // �©��զr
	cout << "                      ";
	gotoXY(GameParameter::OFFSET_INFO_TURN_X - 6, GameParameter::OFFSET_INFO_TURN_Y);

	if (Manager::instance->round) {
		SetConsoleTextAttribute(hConsole, 4); // �©����r	
		cout << "�����";
	}
	else {
		SetConsoleTextAttribute(hConsole, 8); // �©��Ǧr
		cout << "�¦��";
	}
	SetConsoleTextAttribute(hConsole, 11); // �©��C�r
	cout << "  ��ӤF!";

	drawCursor(InputSystem::Instance->cursor);
}

void Display::drawStartScene()
{
	PlaySound(TEXT("ErikSatie-LePiccadilly.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // Play BGM

	// �M�ſù�
	for (int i = 0; i < 30; i++) {
		gotoXY(i, 0);
		for (int j = 0; j < 120; j++)
			cout << ' ';
	}

	// �e��l
	SetConsoleTextAttribute(hConsole, 160); // �񩳶¦r
	gotoXY(0, 0);
	cout << "����������������������";
	for (int i = 0; i < 3; i++) {
		gotoXY(0, (i * 4) + 1);
		cout << "��                  ��";
		gotoXY(0, (i * 4) + 2);
		cout << "��                  ��";
		gotoXY(0, (i * 4) + 3);
		cout << "��                  ��";
		gotoXY(0, (i * 4) + 4);
		cout << "����������������������";
	}
	gotoXY(0, 12);
	cout << "����������������������";

	// �g�ﶵ
	for (int i = 0; i < 3; i++) {
		gotoXY(4, (i * 4) + 2);
		cout << startOptions[i];
	}
	gotoXY(4, 3);
	cout << "�w�w�w�w�w�w�w";
}

void Display::chooseStartOption()
{
	SetConsoleTextAttribute(hConsole, 160); // �񩳶¦r
	for (int i = 0; i < 3; i++) {
		gotoXY(4, (i * 4) + 3);
		cout << "              ";
	}
	gotoXY(4, (Manager::instance->startOption * 4) + 3);
	cout << "�w�w�w�w�w�w�w";
}

string Display::getChineseNum(int num)
{
	switch (num)
	{
	case 1:
		return "�@";
	case 2:
		return "�G";
	case 3:
		return "�T";
	case 4:
		return "�|";
	case 5:
		return "��";
	case 6:
		return "��";
	case 7:
		return "�C";
	case 8:
		return "�K";
	case 9:
		return "�E";
	}
}

string Display::getFullWidthNum(int num)
{
	switch (num)
	{
	case 1:
		return "��";
	case 2:
		return "��";
	case 3:
		return "��";
	case 4:
		return "��";
	case 5:
		return "��";
	case 6:
		return "��";
	case 7:
		return "��";
	case 8:
		return "��";
	case 9:
		return "��";
	}
}