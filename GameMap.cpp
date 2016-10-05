#include "GameMap.h"
// #include "GameProcess.h"
int MapbkObjNum;//地图中背景物品数
int nRectX[]={0,0,0,0,0,0,0,0};
int nRectY[]={0,50,100,150,250,350,400,500};//所画物品在原图的起始坐标
int nRectWidth[]={50,50,50,50,50,50,100,100};
int nRectHeight[]={50,50,50,100,100,100,50,100};//所画物品的宽度和高度    用数组表示所对应id的这些量

GameMap::~GameMap()
{
	Release();	//释放资源
}

int GameMap::LoadMap(int stage)
{   
	FILE *fp;
	char temp[50]={0};
	int find=0;
	int i;
	//memset(MapArray,0,sizeof(MapArray));//0 代表NULL 给数组赋全
	MapbkObjNum=0;
	if(stage==1)  fp=fopen(PATH_MAP1,"r");
	if(stage==2)  fp=fopen(PATH_MAP2,"r");
    if(stage==3)  fp=fopen(PATH_MAP3,"r");
	if(stage==4)  fp=fopen(PATH_MAP4,"r");
	if(stage==5)  fp=fopen(PATH_MAP5,"r");
	if(stage==6)  fp=fopen(PATH_MAP6,"r");
	if(stage==7)  fp=fopen(PATH_MAP7,"r");
	if(stage==8)  fp=fopen(PATH_MAP8,"r");
	if(stage==9)  fp=fopen(PATH_MAP9,"r");
	if(stage==10) fp=fopen(PATH_MAP10,"r");

	if(!fp)
	{
		return 0;
	}

	while(!find && !feof(fp))
	{
		FGetLine(temp,fp);
		if(temp[0]=='*' && temp[1]=='0'+iMatch)
		{
			find=1;
		}
	}
	if(!find)
	{
		return 0;
	}

	//找到了某一关的地图数据
	i=0;
	FGetLineJumpCom(temp,fp);	
	while(temp[0]!='#' && !feof(fp))
	{
		//map data
		sscanf(temp,"%d %d %d %d %d",//将temp中的数据依次赋给以下几个成员
			&MapArray[i].x,
			&MapArray[i].y,
			&MapArray[i].w,
			&MapArray[i].h,
			&MapArray[i].id);			
		//MapArray[i].show=0;
		MapbkObjNum++;
		i++;
		FGetLineJumpCom(temp,fp);	
	}
    fclose(fp);
	return 1;
	
}
//显示地图
void GameMap::ShowMap(HDC hDc,Sprite *mapbk)	// 这个方法是直接画图，不便于管理，用AddMap2SpriteManager取代之
{  
	int i;
	int xstart,ystart;
	int j,k;

	for(i=0;i<MapbkObjNum;i++)
	{
		ystart=MapArray[i].y*50;
		
		//	switch(MapArray[i].id)
		
		for(j=0;j<MapArray[i].h;j++)
		{
			xstart=MapArray[i].x*50;
			for(k=0;k<MapArray[i].w;k++)
			{
				mapbk->DrawRect(hDc,xstart,ystart,nRectX[MapArray[i].id],nRectY[MapArray[i].id],nRectWidth[MapArray[i].id],nRectHeight[MapArray[i].id],TRUE,(255,255,255));		
				xstart+=nRectWidth[MapArray[i].id];
			}
			ystart+=nRectHeight[MapArray[i].id];				
		} // end of for
	}
}

void GameMap::AddMap2SpriteManager(SpriteManage &Sprm) // 将地图物品添加到精灵管理类，取代ShowMap函数
{
	int i, j, k;
	int xstart, ystart;
	for(i=0;i<MapbkObjNum;i++)
	{
		ystart=MapArray[i].y*50;
		
		for(j=0;j<MapArray[i].h;j++)
		{
			xstart=MapArray[i].x*50;
			for(k=0;k<MapArray[i].w;k++)
			{
				// TODO: 
				Sprite *pSprMap = new Sprite(NULL,"resource\\mario.bmp");
				Sprm.AddSprite(pSprMap, 2);			// 地图加到背景层的上一层
				pSprMap -> SetDrawRectInfo(xstart, ystart, nRectX[MapArray[i].id], nRectY[MapArray[i].id],
						nRectWidth[MapArray[i].id],nRectHeight[MapArray[i].id], TRUE, (255,255,255));		// 设置绘图信息

				xstart+=nRectWidth[MapArray[i].id];
			}
			ystart+=nRectHeight[MapArray[i].id];				
		}
		// TODO: 创建地图物品物理对象
		if(MapArray[i].id == 1 || MapArray[i].id == 0) 
		{
			RECT rObject={MapArray[i].x*50, MapArray[i].y*50,
					MapArray[i].x*50 + MapArray[i].w*nRectWidth[MapArray[i].id],
					MapArray[i].y*50 + MapArray[i].h*nRectHeight[MapArray[i].id]};

			RECT rBound={0,0,800,600};
			// extern GameEngine * g_pGE;
			// RECT rBound={0,0,g_pGE->GetWidth(),g_pGE->GetHeight()};
			GamePhysics* pPhysics = new GamePhysics(rObject,rBound);
			pPhysics -> SetCheckBox();
			AddMapObject(pPhysics);
		}
		else if(MapArray[i].id == 3)	// 先只考虑黄色的门
		{
			RECT rObject={MapArray[i].x*50, MapArray[i].y*50,
					MapArray[i].x*50 + MapArray[i].w*nRectWidth[MapArray[i].id],
					MapArray[i].y*50 + MapArray[i].h*nRectHeight[MapArray[i].id]};

			RECT rBound={0,0,800,600};
			GamePhysics* pPhysics = new GamePhysics(rObject,rBound);
			pPhysics -> SetCheckBox();
			m_gpDestination = pPhysics;
		}
	}
}

/*添加物理指针*/
BOOL GameMap::AddMapObject(GamePhysics* pPhysics)
{
	if (pPhysics != NULL)			
	{
		m_vPhysicsManager.push_back(pPhysics);
		return TRUE;
	}
	return FALSE;
}

/*释放资源*/
void GameMap::Release(BOOL bDelPhysics)
{
	if (!m_vPhysicsManager.empty())	//判断容器是否为空
	{
		if(bDelPhysics)
		{
			vector<GamePhysics *>::iterator siPhysics;
			for (siPhysics = m_vPhysicsManager.begin(); siPhysics != m_vPhysicsManager.end(); siPhysics++)
				delete *siPhysics;	//删除精灵对象
		}
		m_vPhysicsManager.clear();			//删除容器中的精灵对象指针
		vector<GamePhysics *>(m_vPhysicsManager).swap(m_vPhysicsManager);	//压缩容器
	}
	delete m_gpDestination;
	m_gpDestination = NULL;
}