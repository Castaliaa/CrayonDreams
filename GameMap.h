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
const int objectnum=19;//地图中物品总数



 
struct MapObject
{
	int x;
	int y;
	int w;
	int h;
	int id;      //定义图片
	//int show;	//是否显示
}; 

class GameMap
{
	
public:
	//地图数据
	
    struct MapObject MapArray[objectnum];
	int LoadMap(int stage);
	int iMatch;//标识地图
	
	void ShowMap(HDC hDc,Sprite* a);
	//地图切换
	int FGetLineJumpCom(char *pchar,FILE *fp)
	{
	int ch=-1;
	int i=0;

	//过滤前面的非法字符
	while(!ISTEXT(ch) && !feof(fp))//当字符合法或文件已读完退出循环
	{
		ch=fgetc(fp);//读到字符并存储，非法则在下一循环中替换	
	}

	if(!ISTEXT(ch))//表示读到文件结束都没有合法字符
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
	
	//得到新的一行
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

	//过滤前面的非法字符
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