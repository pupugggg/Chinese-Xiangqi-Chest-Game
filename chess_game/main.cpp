#include"Manager.h"
#include<iostream>
int main()
{
	Manager::instance = new Manager();
	Manager::instance->Title();
	system("pause");
	return 0;
}