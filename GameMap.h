#ifndef GAMEMAP
#define GAMEMAP  1
#include<stdio.h>
#include<string.h>
#include"Sprite.h"
  
/*#define Land 0;
#define Red_brick 1;
#define Gate_red 2;
#define Gate_green 3;
#define DarkBlue_wall 4;
#define Gray_brick 5;
#define LightBlue_wall 6;*/


#define PATH_MAP1 "map\\map1.txt"

#define PATH_MAP2 "map\\map2.txt"

#define PATH_MAP3 "map\\map3.txt"

#define PATH_MAP4 "map\\map4.txt"

#define PATH_MAP5 "map\\map5.txt"

#define PATH_MAP6 "map\\map6.txt"

#define PATH_MAP7 "map\\map7.txt"

#define PATH_MAP8 "map\\map8.txt"

#define PATH_MAP9 "map\\map9.txt"

#define PATH_MAP10 "map\\map10.txt"
#define ISTEXT(x) ((x)>=32 && (x)<=126)
const int objectnum=19;//��ͼ����Ʒ����



 
struct MapObject
{
	int x;
	int y;
	int w;
	int h;
	int id;      //����ͼƬ
	//int show;	//�Ƿ���ʾ
}; 

class GameMap
{
	
public:
	//��ͼ����
	
    struct MapObject MapArray[objectnum];
	int LoadMap(int stage);
	int iMatch;//��ʶ��ͼ
	
	void ShowMap(HDC hDc,Sprite* a);
	//��ͼ�л�
	int FGetLineJumpCom(char *pchar,FILE *fp)
	{
	int ch=-1;
	int i=0;

	//����ǰ��ķǷ��ַ�
	while(!ISTEXT(ch) && !feof(fp))//���ַ��Ϸ����ļ��Ѷ����˳�ѭ��
	{
		ch=fgetc(fp);//�����ַ����洢���Ƿ�������һѭ�����滻	
	}

	if(!ISTEXT(ch))//��ʾ�����ļ�������û�кϷ��ַ�
	{
		pchar[0]=0;
		return 0;
	}

	//jump comment begin
	if(';' == ch)
	{
		while(ISTEXT(ch) && !feof(fp) )
		{
			ch=fgetc(fp);
		}
		while(!ISTEXT(ch) && !feof(fp))
		{
			ch=fgetc(fp);
		}
	}
	//jump comment end
	
	//�õ��µ�һ��
	while(ISTEXT(ch) && !feof(fp))
	{		
		pchar[i]=ch;
		i++;
		ch=fgetc(fp);
	}
	pchar[i]=0;
	return 1;
}

int FGetLine(char *pchar,FILE *fp)
{
	int ch=-1;
	int i=0;

	//����ǰ��ķǷ��ַ�
	while(!ISTEXT(ch) && !feof(fp))
	{
		ch=fgetc(fp);
	}

	if(!ISTEXT(ch))
	{
		pchar[0]=0;
		return 0;
	}
	
	while(ISTEXT(ch) && !feof(fp))
	{		
		pchar[i]=ch;
		i++;
		ch=fgetc(fp);
	}
	pchar[i]=0;
	return 1;
}

	~GameMap();
};

#endif