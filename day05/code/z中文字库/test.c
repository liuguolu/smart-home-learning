#include "font.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	Init_Font();

	Clean_Area(0,  //x������ʼ��
               0,  //y������ʼ��
			   800, //���ƵĿ��
			   480,//���Ƶĸ߶�
			   0x0); //����Ļָ�����������ɫ

	Display_characterX(0,          //x������ʼ��
					   0,          //y������ʼ��
					   "���Կ���������",   //GB2312 �����ַ���
					    0xFF0000,     //������ɫֵ
						 2);	

	UnInit_Font();		

	return 0;
}
