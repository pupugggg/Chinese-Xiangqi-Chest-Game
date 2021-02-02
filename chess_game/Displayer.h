#pragma once
#include "Board.h"
#include "GameParameter.h"
#include "InputSystem.h"
using namespace std;

class Display
{
public:
	Display();
	static Display* Instance;	// Ensure the existence for all different operators
	vector<string> records;
	int record;
	bool withdraw;
	void drawAll(); // �e��������(���������k��info�u�|����l�A�S�����e)
	void drawBoard(); // �e�ѽL
	void drawCursor(Vector2 cs); // ���ʴѽL�W���y��, �j�p 9*10
	void drawPath(); // �e���|
	void erasePath(Vector2 p); // ����|����, ��J���OtmpPos, ��moveChess�@��
	void drawRecord(Vector2 pos); // �������
	void drawRecord2(Vector2 start, Vector2 end); // �qstart���ʨ�end
	void eraseRecord(); // �����̷s�@������
	void drawInfo(); // �k����ܿ�ܭ��Ӵ�
	void eraseInfo(); // ��Info����
	void drawTurn(); // �k����ܲ{�b����
	void moveChess(Vector2 pos); // ���ʴѤl
	void drawWithdrawWindow(); // ���ѵ���
	void eraseWithdrawWindow(); // �⮬�ѵ�������
	void drawWithdrawPrompt(); // ������ܬO�Χ_(�n����)
	void drawMenu();  // ���
	void eraseMenu(); // ��������
	void chooseOption(); // ���ʿﶵ(��manager�̪�option�A�q0~3)
	void drawCheckmate(); // ��ܳQ�N�x
	void eraseCheckmate(); // �����Q�N�x���r
	void drawEnd(); // �������
	void drawStartScene(); // �}�l�e��
	void chooseStartOption();
private:
	void Init();
	void gotoXY(int x, int y); // ���ʴ�Цb��ӵ�������m
	string getChineseNum(int num);
	string getFullWidthNum(int num);
	string defaultBoard[19];
	string startOptions[3];
	string options[4];
	COORD cursor;
};