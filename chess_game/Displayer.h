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
	void drawAll(); // 畫全部介面(左邊紀錄跟右邊info只會有格子，沒有內容)
	void drawBoard(); // 畫棋盤
	void drawCursor(Vector2 cs); // 移動棋盤上的座標, 大小 9*10
	void drawPath(); // 畫路徑
	void erasePath(Vector2 p); // 把路徑擦掉, 輸入的是tmpPos, 跟moveChess一樣
	void drawRecord(Vector2 pos); // 左邊紀錄
	void drawRecord2(Vector2 start, Vector2 end); // 從start移動到end
	void eraseRecord(); // 擦掉最新一條紀錄
	void drawInfo(); // 右邊顯示選擇哪個棋
	void eraseInfo(); // 把Info擦掉
	void drawTurn(); // 右邊顯示現在換誰
	void moveChess(Vector2 pos); // 移動棋子
	void drawWithdrawWindow(); // 悔棋視窗
	void eraseWithdrawWindow(); // 把悔棋視窗關掉
	void drawWithdrawPrompt(); // 切換選擇是或否(要悔棋)
	void drawMenu();  // 選單
	void eraseMenu(); // 把選單關掉
	void chooseOption(); // 移動選項(用manager裡的option，從0~3)
	void drawCheckmate(); // 顯示被將軍
	void eraseCheckmate(); // 擦掉被將軍的字
	void drawEnd(); // 結束顯示
	void drawStartScene(); // 開始畫面
	void chooseStartOption();
private:
	void Init();
	void gotoXY(int x, int y); // 移動游標在整個視窗的位置
	string getChineseNum(int num);
	string getFullWidthNum(int num);
	string defaultBoard[19];
	string startOptions[3];
	string options[4];
	COORD cursor;
};