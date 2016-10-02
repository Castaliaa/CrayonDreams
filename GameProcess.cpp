/********************************
游戏程序主文件GameProcess.cpp
********************************/
#include "GameProcess.h"
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  游戏初始化 */
BOOL GameInitialize(HINSTANCE hInstance)
{
	//创建引擎
	g_pGE=new GameEngine(hInstance,TEXT("GameStart"),TEXT("Star Lost"),
		IDI_BIGICON,IDI_SMALLICON,FALSE,32,800,600);
	if(g_pGE==NULL)
		return false;
	
	//初始化引擎参数
	g_pGE->SetFrameDelay(15) ;		//设置游戏帧延时为15毫秒
	g_pGE->SetPause(false);			//设置暂停状态为false
	if(!g_pGE->CreateGameWindow())	//创建游戏窗口
	{
		MessageBox(NULL,"修改显示模式失败!\r\n程序退出!","错误",MB_OK| MB_ICONERROR);
		return FALSE;		//退出程序
	}
	
	
    
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏开始 */
void GameStart(HWND hWnd)
{
	/* 在这里添加游戏开始时的初始化代码 */
	
	/* 设置鼠标指针*/
	long nCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,nCur);
	
	//g_pLoadScene=new Sprite(NULL,"resource\\LoadScene.bmp");
	
	g_nScene=1;			//设置场景标志
	// g_nScene=2;			//设置场景标志
	g_bInitScene=FALSE;	//设置场景初始化标志
	
	InitScene_1(hWnd);	//初始化场景1
	// InitScene_2(hWnd);	//初始化场景1
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏逻辑 */
void GameAction(HWND hWnd)
{
	if(g_bInitScene)	//判断场景初始化是否完成
	{
		//通过场景标志来调用相关场景
		switch(g_nScene)	
		{
		case 1:
			if(PlayScene_1(hWnd))		//执行场景1游戏逻辑，通过返回值判断是否执行完毕
			{
				g_bInitScene=FALSE;	//设置场景初始化标志
				// InitScene_2(hWnd);	//初始化场景2;
			}
			break;
		case 2:
			if(PlayScene_2(hWnd))		//执行场景2游戏逻辑，通过返回值判断是否执行完毕
			{
				g_bInitScene=FALSE;	//设置场景初始化标志
			}
			break;
		case 3:
			PlayScene_3(hWnd);
		                  //执行场景3游戏逻辑
			break;
		}
	}

	
	
	InvalidateRect(hWnd,NULL,FALSE);	//强制刷新窗口
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景1初始化 */
BOOL InitScene_1(HWND hWnd)
{
	//载入游戏图像
	g_pSprGameStartBK=new Sprite(NULL,"resource\\GameStartBK.bmp");
	g_pSprHelp=new Sprite(NULL,"resource\\Help.bmp");
	g_pSprThanks=new Sprite(NULL,"resource\\Thanks.bmp");
	
	//将精灵添加到精灵管理对象，并设置相应Z顺序
	g_Sprm.AddSprite(g_pSprGameStartBK,0);
	g_Sprm.AddSprite(g_pSprHelp,1);              //“操作说明”框
	g_Sprm.AddSprite(g_pSprThanks,1);            //“特别感谢”框
    g_pSprHelp->SetVisible(FALSE);               //设置“操作说明”为不可见
	g_pSprThanks->SetVisible(FALSE);             //设置“特别感谢”为不可见
	
	//创建游戏音乐对象并打开文件
	g_pMscBGM1=new GameMusic("resource\\crayon07.mp3");
	g_pMscBGM1->Play(300,TRUE);	//重复播放音乐	
	
	g_bInitScene=TRUE;	//场景初始化完成
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景1运行 */
BOOL PlayScene_1(HWND hWnd)
{
	//设置精灵对象绘图信息
	g_pSprGameStartBK->SetDrawInfo(0,0,TRUE);
	g_pSprHelp->SetDrawInfo(400-g_pSprHelp->GetWidth()/2,300-g_pSprHelp->GetHeight()/2,TRUE,RGB(255,255,255));
	g_pSprThanks->SetDrawInfo(400-g_pSprThanks->GetWidth()/2,300-g_pSprThanks->GetHeight()/2,TRUE,RGB(255,255,255));
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景2初始化 */
BOOL InitScene_2(HWND hWnd)
{
	//载入背景
	g_pSprChooseLevelBK=new Sprite(NULL,"resource\\Test1BK.bmp");
	
	//载入星星动画图像，并初始化动画参数
	for(int i=0;i<=9;i++)
	{
		g_pSprStar[i]=new Sprite(NULL,"resource\\Star.bmp");
		g_pSprStar[i]->InitAnima(2,6,150);
		g_Sprm.AddSprite(g_pSprStar[i],1);
	}
	
	//将精灵添加到精灵管理对象
	g_Sprm.AddSprite(g_pSprChooseLevelBK,0);
	
	g_bInitScene=TRUE;	//设置场景初始化标志
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景2运行 */
BOOL PlayScene_2(HWND hWnd)
{
	//设置精灵对象信息
	g_pSprChooseLevelBK->SetDrawInfo(0,0,TRUE);
	g_pSprStar[0]->SetDrawAnimaInfo(363,67,StarCol[0],TRUE,RGB(255,255,255));
	g_pSprStar[1]->SetDrawAnimaInfo(288,196,StarCol[1],TRUE,RGB(255,255,255));
	g_pSprStar[2]->SetDrawAnimaInfo(153,201,StarCol[2],TRUE,RGB(255,255,255));
	g_pSprStar[3]->SetDrawAnimaInfo(257,324,StarCol[3],TRUE,RGB(255,255,255));
	g_pSprStar[4]->SetDrawAnimaInfo(238,472,StarCol[4],TRUE,RGB(255,255,255));
	g_pSprStar[5]->SetDrawAnimaInfo(377,407,StarCol[5],TRUE,RGB(255,255,255));
	g_pSprStar[6]->SetDrawAnimaInfo(521,475,StarCol[6],TRUE,RGB(255,255,255));
	g_pSprStar[7]->SetDrawAnimaInfo(481,324,StarCol[7],TRUE,RGB(255,255,255));
	g_pSprStar[8]->SetDrawAnimaInfo(596,207,StarCol[8],TRUE,RGB(255,255,255));
	g_pSprStar[9]->SetDrawAnimaInfo(448,196,StarCol[9],TRUE,RGB(255,255,255));
	
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景3初始化 */
BOOL InitScene_3(HWND hWnd)
{
	//载入背景
	g_pSprTestBK=new Sprite(NULL,"resource\\TestBK.bmp");
	mapbk=new Sprite(NULL,"resource\\mario.bmp");      //载入地图

	g_pSprBox=new Sprite(NULL,"resource\\TownBox.bmp");
	// g_pSprBox2=new Sprite(NULL,"resource\\TownBox.bmp");                              //加了一个箱子
	//载入动画图像，并初始化动画参数
	g_pSprTestAnima1=new Sprite(NULL,"resource\\Star.bmp"); //       111111
	g_pSprTestAnima1->InitAnima(2,6,150);
    g_pSprTestAnima2=new Sprite(NULL,"resource\\Star1.bmp");//        22222
	g_pSprTestAnima2->InitAnima(2,6,150);
	
	
	//将精灵添加到精灵管理对象
	g_Sprm.AddSprite(g_pSprTestBK,0);
	g_Sprm.AddSprite(g_pSprTestAnima1,3);
	g_Sprm.AddSprite(g_pSprTestAnima2,3);
	g_Sprm.AddSprite(g_pSprBox,3);
	// g_Sprm.AddSprite(g_pSprBox2,3);                                                 //加了一个箱子
    //g_Sprm.AddSprite(mapbk,3);                //输出的地图
	
	if(map.LoadMap(stage))
		map.AddMap2SpriteManager(g_Sprm);
    
	/*	g_ptTestAnima1.x=505;
	g_ptTestAnima1.y=137;*/
	
	//关闭场景一二音乐
    g_pMscBGM1->Stop();
	//创建游戏音乐对象并打开文件
	g_pMscMove=new GameMusic("resource\\hit.wav");
	g_pMscBGM=new GameMusic("resource\\bgm.mp3");
	g_pMscBGM->Play(300,TRUE);	//重复播放音乐	
	
	//创建游戏者星星物理运动对象
	RECT rObject={560,100,560+g_pSprTestAnima1->GetWidth()/6,100+g_pSprTestAnima1->GetHeight()/2};
	RECT rBound={0,0,g_pGE->GetWidth(),g_pGE->GetHeight()};
	POINTF ptFocus={0,0};
	POINTF ptVelo={0,5};
	POINTF ptAccelerate={0,0};
	POINTF ptDes={300,300};
	g_pPhyTest=new GamePhysics(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);
	// g_pPhyTest2=new GamePhysics(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);/////////2
	
	//创建箱子物理运动对象
	RECT rObject1={308,326,308+g_pSprBox->GetWidth(),326+g_pSprBox->GetHeight()};
	RECT rBound1={0,0,g_pGE->GetWidth(),g_pGE->GetHeight()};
	POINTF ptFocus1={0,0};
	POINTF ptVelo1={0,0};
	POINTF ptAccelerate1={0,0};
	POINTF ptDes1={300,300};
	g_pPhyBox=new GamePhysics(rObject1,rBound1,ptFocus1,ptVelo1,ptAccelerate1,ptDes1,FALSE);

	//加了一个箱子,除了第一个参数有所修改（修改了出现的位置），其余都移植了第一个箱子的属性
 //    RECT rObject2={408,326,408+g_pSprBox->GetWidth(),326+g_pSprBox->GetHeight()};
	// g_pPhyBox2=new GamePhysics(rObject2,rBound1,ptFocus1,ptVelo1,ptAccelerate1,ptDes1,FALSE);

	g_bInitScene=TRUE;	//设置场景初始化标志
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 场景3运行 */
BOOL PlayScene_3(HWND hWnd)
{
	//设置精灵对象信息
	g_pSprTestBK->SetDrawInfo(0,0,TRUE,(255,255,255));
	g_pSprBox->SetDrawInfo(g_pPhyBox->GetLeftTop().x,g_pPhyBox->GetLeftTop().y,TRUE);
	// g_pSprBox2->SetDrawInfo(g_pPhyBox2->GetLeftTop().x,g_pPhyBox2->GetLeftTop().y,TRUE);      //加了一个箱子
	// mapbk -> set
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  渲染游戏画面 */
void GamePaint(HDC hDC)
{
	if(g_bInitScene)	//判断场景初始化是否完成
		g_Sprm.Draw(hDC);
  	// 	if(g_nScene==3 && map.LoadMap(stage))
			// map.ShowMap(hDC,mapbk);
		

	// if(!g_bInitScene)	//判断场景初始化是否完成
	// 	g_pLoadScene->Draw(hDC,0,0);	//绘制加载场景时的等待画面
	// else
	// 	g_Sprm.Draw(hDC);				//绘制场景

	// if(g_nScene==3)
	// {	
	// 	if(map.LoadMap(stage))
	// 		map.ShowMap(hDC,mapbk);
	// }			//绘制场景
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 游戏结束 */
void GameEnd()
{
	g_Sprm.Release(TRUE);
	//delete	g_pLoadScene;
	delete g_pPhyTest;
	delete g_pPhyBox;
	// delete g_pPhyBox2;
	delete g_pGE;	//清除游戏引擎指针
	delete g_pMscBGM;
	delete g_pMscMove;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏激活 */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	
	
	/* 在这里添加具体的游戏激活事件处理代码 */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏暂停 */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
	
	/* 在这里添加具体的游戏暂停事件处理代码 */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 游戏窗口关闭 */
BOOL GameWindowClose(HWND hWnd)
{
	/* 游戏窗口关闭前的处理代码 */
	
	if(MessageBox(g_pGE->GetWindow(),"你确定要退出吗？","退出游戏",MB_YESNO|MB_DEFBUTTON2 | MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*键盘消息处理*/
void KeyEvent(HWND hWnd)
{
	if(g_nScene==3)
	{
		RECT r1;
		//这里把检测星星与箱子2碰撞的函数放在最前面首先判断，就不用在上下左右、上跳左跳右跳里面都分别进行判断了
		// if(g_pPhyTest->Collision(g_pPhyBox2,BA_STOP,&r1)) //检测星星与箱子2的碰撞，第二个参数是BA_STOP，注意我对GamePhysics类中的Collision进行了修改
		// {
		// 	g_pPhyTest->CheckErr(TRUE);	
		// }
		if(X>0)
		{		
			g_pPhyTest->SetVelo(Direction,velo);
			g_pPhyTest->SetMoveState(TRUE);
			g_pPhyTest->ShiftMove();
			//g_pPhyTest->SetMoveState(FALSE);
			//g_pPhyTest->SetVelo(0,5);
			g_pPhyTest->CheckErr(TRUE);	//检查是否超出焦点框
			velo+=1;
			Y=15;
			g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));
			X--;
		}
		else if(X==0&&Y>0)
		{	
			g_pPhyTest->SetVelo(Direction,velo);
			g_pPhyTest->SetMoveState(TRUE);
			g_pPhyTest->ShiftMove();
			g_pPhyTest->SetMoveState(FALSE);
			g_pPhyTest->SetVelo(0,5);
			g_pPhyTest->CheckErr(TRUE);	//检查是否超出焦点框
			g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));
			Y--;
			velo+=1;
		}
		else if(GetAsyncKeyState(VK_SPACE)<0&&GetAsyncKeyState(VK_LEFT)==0&&GetAsyncKeyState(VK_RIGHT)==0)		//只有上方向键按下
		{
			velo=-14;
			X=14;
			Direction=0;
		}
		else if(GetAsyncKeyState(VK_SPACE)<0&&GetAsyncKeyState(VK_LEFT)<0)		//判断左上方向键是否按下
		{
			velo=-14;
			X=14;
			Direction=-5;
		}
		else if(GetAsyncKeyState(VK_SPACE)<0&&GetAsyncKeyState(VK_RIGHT)<0)		//判断右上方向键是否按下
		{
			velo=-14;
			X=14;	
			Direction=5;
		}
		else if(GetAsyncKeyState(VK_UP)<0)
		{	
			g_pPhyTest->MoveDirect(DI_UP);	//游戏者物理运动对象向上移动
			g_pPhyTest->CheckErr(TRUE);	//检查是否超出焦点框
			
			//设置图像和绘图参数
			g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));
			g_pMscMove->Play(300,FALSE,FALSE);	//播放移动音效
			if(g_pPhyBox->Collision(g_pPhyTest,BA_REBOUND,&r1))
			{
				g_pPhyBox->MoveDirect(DI_UP);	//游戏者物理运动对象向上移动
				g_pPhyBox->CheckErr(TRUE);	
			}
		}
		else if(GetAsyncKeyState(VK_DOWN)<0)	//判断下方向键是否按下
		{
			g_pPhyTest->MoveDirect(DI_DOWN);	//游戏者物理运动对象向上移动
			g_pPhyTest->CheckErr(TRUE);	//检查是否超出焦点框
			
			//设置图像和绘图参数
			g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));
			g_pMscMove->Play(300,FALSE,FALSE);	//播放移动音效
			if(g_pPhyBox->Collision(g_pPhyTest,BA_REBOUND,&r1))
			{
				g_pPhyBox->MoveDirect(DI_DOWN);	//游戏者物理运动对象向上移动
				g_pPhyBox->CheckErr(TRUE);	
			}
		}
		else if(GetAsyncKeyState(VK_LEFT)<0)	//判断左方向键是否按下
		{		
			g_pPhyTest->MoveDirect(DI_LEFT);	//游戏者物理运动对象向上移动
			g_pPhyTest->CheckErr(TRUE);	//检查是否超出焦点框
			
			//设置图像和绘图参数
			g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));
			g_pMscMove->Play(300,FALSE,FALSE);	//播放移动音效
			if(g_pPhyBox->Collision(g_pPhyTest,BA_REBOUND,&r1))
			{
				g_pPhyBox->MoveDirect(DI_LEFT);	//游戏者物理运动对象向上移动
				g_pPhyBox->CheckErr(TRUE);	
			}
		}
		else if(GetAsyncKeyState(VK_RIGHT)<0)	//判断右方向键是否按下
		{	
			g_pPhyTest->MoveDirect(DI_RIGHT);	//游戏者物理运动对象向上移动
			g_pPhyTest->CheckErr(TRUE);	//检查是否超出焦点框
			
			//设置图像和绘图参数
			g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));
			g_pMscMove->Play(300,FALSE,FALSE);	//播放移动音效
			if(g_pPhyBox->Collision(g_pPhyTest,BA_REBOUND,&r1))
			{
				g_pPhyBox->MoveDirect(DI_RIGHT);	//游戏者物理运动对象向上移动
				g_pPhyBox->CheckErr(TRUE);	
			}
		}
		else if(GetAsyncKeyState(VK_PRIOR)<0)	//按下PageUp键，背景音乐音量增大
			g_pMscBGM->VolumeUp();
		else if(GetAsyncKeyState(VK_NEXT)<0)	//按下PageDown键，背景音乐音量减小
			g_pMscBGM->VolumeDown();
		else if(GetAsyncKeyState(VK_HOME )<0)	//按下Home键，重新播放背景音乐
			g_pMscBGM->Play(300,TRUE);
		else if(GetAsyncKeyState(VK_END )<0)	//按下End键，停止播放背景音乐
			g_pMscBGM->Stop();
		else if(GetAsyncKeyState(VK_ESCAPE)<0 )	//判断ESC键是否按下
			SendMessage(hWnd,WM_CLOSE,0,0);     //退出程序
		
		else 			//如果没有方向键被按下
		{
			g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));
		}
		// if(x>0){
		// 	g_pPhyTest2->SetVelo(direction,Velo);
		// 	g_pPhyTest2->SetMoveState(TRUE);
		// 	g_pPhyTest2->ShiftMove();
		// 	//g_pPhyTest->SetMoveState(FALSE);
		// 	//g_pPhyTest->SetVelo(0,5);
		// 	g_pPhyTest2->CheckErr(TRUE);	//检查是否超出焦点框
		// 	Velo+=1;
		// 	y=15;
		// 	g_pSprTestAnima2->SetDrawAnimaInfo(g_pPhyTest2->GetLeftTop().x,g_pPhyTest2->GetLeftTop().y,0,TRUE,RGB(255,255,255));
		// 	x--;}
		
	
		//  if(x==0&&y>0)
		// {	
		// 	g_pPhyTest2->SetVelo(direction,Velo);
		// 	g_pPhyTest2->SetMoveState(TRUE);
		// 	g_pPhyTest2->ShiftMove();
		// 	g_pPhyTest2->SetMoveState(FALSE);
		// 	g_pPhyTest2->SetVelo(0,5);
		// 	g_pPhyTest2->CheckErr(TRUE);	//检查是否超出焦点框
		// 	g_pSprTestAnima2->SetDrawAnimaInfo(g_pPhyTest2->GetLeftTop().x,g_pPhyTest2->GetLeftTop().y,0,TRUE,RGB(255,255,255));
		// 	y--;
		// 	Velo+=1;
		// }
		// else if(GetAsyncKeyState(57)<0&&GetAsyncKeyState(41)==0&&GetAsyncKeyState(44)==0)		//只有上方向键按下
		// {
		// 	Velo=-14;
		// 	x=14;
		// 	direction=0;
		// }
		// else if(GetAsyncKeyState(57)<0&&GetAsyncKeyState(41)<0)		//判断左上方向键是否按下
		// {
		// 	Velo=-14;
		// 	x=14;
		// 	direction=-5;
		// }
		// else if(GetAsyncKeyState(57)<0&&GetAsyncKeyState(44)<0)		//判断右上方向键是否按下
		// {
		// 	Velo=-14;
		// 	x=14;	
		// 	direction=5;
		// }
		
		// else if(GetAsyncKeyState(53)<0)	//判断下方向键是否按下
		// {
		// 	g_pPhyTest2->MoveDirect(DI_DOWN);	//游戏者物理运动对象向上移动
		// 	g_pPhyTest2->CheckErr(TRUE);	//检查是否超出焦点框
			
		// 	//设置图像和绘图参数
		// 	g_pSprTestAnima2->SetDrawAnimaInfo(g_pPhyTest2->GetLeftTop().x,g_pPhyTest2->GetLeftTop().y,0,TRUE,RGB(255,255,255));
		// 	g_pMscMove->Play(300,FALSE,FALSE);	//播放移动音效
		// 	if(g_pPhyBox->Collision(g_pPhyTest2,BA_REBOUND,&r1))
		// 	{
		// 		g_pPhyBox->MoveDirect(DI_DOWN);	//游戏者物理运动对象向上移动
		// 		g_pPhyBox->CheckErr(TRUE);	
		// 	}
		// }
		// else 	if(GetAsyncKeyState(41)<0)	//判断左方向键是否按下
		// {		
		// 	g_pPhyTest2->MoveDirect(DI_RIGHT);	//游戏者物理运动对象向上移动
		// 	g_pPhyTest2->CheckErr(TRUE);	//检查是否超出焦点框
			
		// 	//设置图像和绘图参数
		// 	g_pSprTestAnima2->SetDrawAnimaInfo(g_pPhyTest2->GetLeftTop().x,g_pPhyTest2->GetLeftTop().y,0,TRUE,RGB(255,255,255));
		// 	g_pMscMove->Play(300,FALSE,FALSE);	//播放移动音效
		// 	if(g_pPhyBox->Collision(g_pPhyTest2,BA_REBOUND,&r1))
		// 	{
		// 		g_pPhyBox->MoveDirect(DI_LEFT);	//游戏者物理运动对象向上移动
		// 		g_pPhyBox->CheckErr(TRUE);	
		// 	}
		// }
		// else 	if(GetAsyncKeyState(44)<0)	//判断右方向键是否按下
		// {	
		// 	g_pPhyTest2->MoveDirect(DI_RIGHT);	//游戏者物理运动对象向上移动
		// 	g_pPhyTest2->CheckErr(TRUE);	//检查是否超出焦点框
			
		// 	//设置图像和绘图参数
		// 	g_pSprTestAnima2->SetDrawAnimaInfo(g_pPhyTest2->GetLeftTop().x,g_pPhyTest2->GetLeftTop().y,0,TRUE,RGB(255,255,255));
		// 	g_pMscMove->Play(300,FALSE,FALSE);	//播放移动音效
		// 	if(g_pPhyBox->Collision(g_pPhyTest2,BA_REBOUND,&r1))
		// 	{
		// 		g_pPhyBox->MoveDirect(DI_RIGHT);	//游戏者物理运动对象向上移动
		// 		g_pPhyBox->CheckErr(TRUE);	
		// 	}
		// }
		
		
		// else 			//如果没有方向键被按下
		// {
		// 	g_pSprTestAnima2->SetDrawAnimaInfo(g_pPhyTest2->GetLeftTop().x,g_pPhyTest2->GetLeftTop().y,0,TRUE,RGB(255,255,255));
		// }
	}
	
}

/* 鼠标单击事件处理 */
void MouseLButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
	/* 在这里添加具体的鼠标单击事件处理代码 */
	BOOL CALLBACK DialogProc(HWND hwndDlg,UINT UMsg,WPARAM wParam,LPARAM IParam);
	
	
	if(g_pSprHelp->GetVisible()&&g_nScene==1)
	{
		g_pSprHelp->SetVisible(FALSE);
	}
	else if(g_pSprThanks->GetVisible()&&g_nScene==1)
	{
		g_pSprThanks->SetVisible(FALSE);
	}
	
	else if(x>278&&x<511&&y>252&&y<300&&g_nScene==1)
	{
		g_Sprm.Release(TRUE);		//删除精灵图像
		InitScene_2(hWnd);	//初始化场景2;
		g_nScene=2;
	}
	else if(x>278&&x<511&&y>324&&y<372&&g_nScene==1)
	{
		g_pSprHelp->SetVisible(TRUE);
	}
	else if(x>278&&x<511&&y>398&&y<447&&g_nScene==1)
	{
		g_pSprThanks->SetVisible(TRUE);
	}
	else if(x>278&&x<511&&y>464&&y<518&&g_nScene==1)
	{
		SendMessage (hWnd, WM_CLOSE, 0, 0) ;
		
	}
	else if(g_nScene==2)
	{  int ischange=0;
	   if(StarCol[0]==1){ stage=1;ischange=1;}
	   if(StarCol[1]==1){ stage=2;ischange=1;}
	   if(StarCol[2]==1){ stage=3;ischange=1;}
	   if(StarCol[3]==1){ stage=4;ischange=1;}
	   if(StarCol[4]==1){ stage=5;ischange=1;}
	   if(StarCol[5]==1){ stage=6;ischange=1;}
	   if(StarCol[6]==1){ stage=7;ischange=1;}
	   if(StarCol[7]==1){ stage=8;ischange=1;}
	   if(StarCol[8]==1){ stage=9;ischange=1;}
	   if(StarCol[9]==1){ stage=10;ischange=1;}
	   if(ischange==1){
		g_Sprm.Release(TRUE);		//删除精灵图像
		InitScene_3(hWnd);	//初始化场景3;
		g_nScene=3;}
	
	}
	else
	{
		char str1[100];
		sprintf(str1,"鼠标坐标X：%d     Y：%d    ",x,y); 
		MessageBox(hWnd,str1,"XJ's",MB_YESNO);
	}
	
}

//鼠标左键弹起消息处理函数
void MouseLButtonUp(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//鼠标左键双击消息处理函数
void MouseDoubleClick(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//鼠标右键按下消息处理函数
void MouseRButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//鼠标移动消息处理函数
void MouseMove(HWND hWnd,int x,int y,WPARAM wParam)
{
	if(g_nScene==2)
	{
		if(x>363&&x<363+g_pSprStar[0]->GetWidth()/6&&y>67&&y<67+g_pSprStar[0]->GetHeight()/2)	StarCol[0]=1;
		else StarCol[0]=0;
		if(x>288&&x<288+g_pSprStar[1]->GetWidth()/6&&y>196&&y<196+g_pSprStar[0]->GetHeight()/2)	StarCol[1]=1;
		else StarCol[1]=0;
		if(x>153&&x<153+g_pSprStar[2]->GetWidth()/6&&y>201&&y<201+g_pSprStar[0]->GetHeight()/2)	StarCol[2]=1;
		else StarCol[2]=0;
		if(x>257&&x<257+g_pSprStar[3]->GetWidth()/6&&y>324&&y<324+g_pSprStar[0]->GetHeight()/2)	StarCol[3]=1;
		else StarCol[3]=0;
		if(x>238&&x<238+g_pSprStar[4]->GetWidth()/6&&y>472&&y<472+g_pSprStar[0]->GetHeight()/2)	StarCol[4]=1;
		else StarCol[4]=0;
		if(x>377&&x<377+g_pSprStar[5]->GetWidth()/6&&y>407&&y<407+g_pSprStar[0]->GetHeight()/2)	StarCol[5]=1;
		else StarCol[5]=0;
		if(x>521&&x<521+g_pSprStar[6]->GetWidth()/6&&y>475&&y<475+g_pSprStar[0]->GetHeight()/2)	StarCol[6]=1;
		else StarCol[6]=0;
		if(x>481&&x<481+g_pSprStar[7]->GetWidth()/6&&y>324&&y<324+g_pSprStar[0]->GetHeight()/2)	StarCol[7]=1;
		else StarCol[7]=0;
		if(x>596&&x<596+g_pSprStar[8]->GetWidth()/6&&y>207&&y<207+g_pSprStar[0]->GetHeight()/2)	StarCol[8]=1;
		else StarCol[8]=0;
		if(x>448&&x<448+g_pSprStar[9]->GetWidth()/6&&y>196&&y<196+g_pSprStar[0]->GetHeight()/2)	StarCol[9]=1;
		else StarCol[9]=0;
	}
}

