/********************************
��Ϸ�������ļ�GameProcess.cpp
********************************/
#include "GameProcess.h"
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ϸ��ʼ�� */
BOOL GameInitialize(HINSTANCE hInstance)
{
	//��������
	g_pGE=new GameEngine(hInstance,TEXT("GameStart"),TEXT("����������"),
		IDI_BIGICON,IDI_SMALLICON,FALSE,32,800,600);
	if(g_pGE==NULL)
		return false;
	
	//��ʼ���������
	g_pGE->SetFrameDelay(15) ;		//������Ϸ֡��ʱΪ15����
	g_pGE->SetPause(false);			//������ͣ״̬Ϊfalse
	if(!g_pGE->CreateGameWindow())	//������Ϸ����
	{
		MessageBox(NULL,"�޸���ʾģʽʧ��!\r\n�����˳�!","����",MB_OK| MB_ICONERROR);
		return FALSE;		//�˳�����
	}
	
	
    
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ʼ */
void GameStart(HWND hWnd)
{
	/* �����������Ϸ��ʼʱ�ĳ�ʼ������ */
	
	/* �������ָ��*/
	long nCur=(long)LoadCursor(g_pGE->GetInstance(),MAKEINTRESOURCE(IDC_MAINCURSOR));
	SetClassLong(hWnd, GCL_HCURSOR,nCur);
	
	//g_pLoadScene=new Sprite(NULL,"resource\\LoadScene.bmp");
	
	g_nScene=1;			//���ó�����־
	// g_nScene=2;			//���ó�����־
	g_bInitScene=FALSE;	//���ó�����ʼ����־
	
	InitScene_1(hWnd);	//��ʼ������1
	// InitScene_2(hWnd);	//��ʼ������1
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ�߼� */
void GameAction(HWND hWnd)
{
	if(g_bInitScene)	//�жϳ�����ʼ���Ƿ����
	{
		//ͨ��������־��������س���
		switch(g_nScene)	
		{
		case 1:
			if(PlayScene_1(hWnd))		//ִ�г���1��Ϸ�߼���ͨ������ֵ�ж��Ƿ�ִ�����
			{
				g_bInitScene=FALSE;	//���ó�����ʼ����־
				// InitScene_2(hWnd);	//��ʼ������2;
			}
			break;
		case 2:
			if(PlayScene_2(hWnd))		//ִ�г���2��Ϸ�߼���ͨ������ֵ�ж��Ƿ�ִ�����
			{
				g_bInitScene=FALSE;	//���ó�����ʼ����־
			}
			break;
		case 3:
			PlayScene_3(hWnd);
		                  //ִ�г���3��Ϸ�߼�
			break;
		}
	}

	
	
	InvalidateRect(hWnd,NULL,FALSE);	//ǿ��ˢ�´���
	UpdateWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����1��ʼ�� */
BOOL InitScene_1(HWND hWnd)
{
	//������Ϸͼ��
	g_pSprGameStartBK=new Sprite(NULL,"resource\\GameStartBK.bmp");
	g_pSprHelp=new Sprite(NULL,"resource\\Help.bmp");
	g_pSprThanks=new Sprite(NULL,"resource\\Thanks.bmp");
	
	//��������ӵ����������󣬲�������ӦZ˳��
	g_Sprm.AddSprite(g_pSprGameStartBK,0);
	g_Sprm.AddSprite(g_pSprHelp,1);              //������˵������
	g_Sprm.AddSprite(g_pSprThanks,1);            //���ر��л����
    g_pSprHelp->SetVisible(FALSE);               //���á�����˵����Ϊ���ɼ�
	g_pSprThanks->SetVisible(FALSE);             //���á��ر��л��Ϊ���ɼ�
	
	//������Ϸ���ֶ��󲢴��ļ�
	g_pMscBGM1=new GameMusic("resource\\crayon07.mp3");
	g_pMscBGM1->Play(300,TRUE);	//�ظ���������	
	
	g_bInitScene=TRUE;	//������ʼ�����
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����1���� */
BOOL PlayScene_1(HWND hWnd)
{
	//���þ�������ͼ��Ϣ
	g_pSprGameStartBK->SetDrawInfo(0,0,TRUE);
	g_pSprHelp->SetDrawInfo(400-g_pSprHelp->GetWidth()/2,300-g_pSprHelp->GetHeight()/2,TRUE,RGB(255,255,255));
	g_pSprThanks->SetDrawInfo(400-g_pSprThanks->GetWidth()/2,300-g_pSprThanks->GetHeight()/2,TRUE,RGB(255,255,255));
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����2��ʼ�� */
BOOL InitScene_2(HWND hWnd)
{
	//���뱳��
	g_pSprChooseLevelBK=new Sprite(NULL,"resource\\Test1BK.bmp");
	
	//�������Ƕ���ͼ�񣬲���ʼ����������
	for(int i=0;i<=9;i++)
	{
		g_pSprStar[i]=new Sprite(NULL,"resource\\Star.bmp");
		g_pSprStar[i]->InitAnima(2,6,150);
		g_Sprm.AddSprite(g_pSprStar[i],1);
	}
	
	//��������ӵ�����������
	g_Sprm.AddSprite(g_pSprChooseLevelBK,0);
	
	g_bInitScene=TRUE;	//���ó�����ʼ����־
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����2���� */
BOOL PlayScene_2(HWND hWnd)
{
	//���þ��������Ϣ
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

/* ����3��ʼ�� */
BOOL InitScene_3(HWND hWnd)
{
	//���뱳��
	g_pSprTestBK=new Sprite(NULL,"resource\\TestBK.bmp");
	// mapbk=new Sprite(NULL,"resource\\mario.bmp");      //�����ͼ

	g_pSprBox=new Sprite(NULL,"resource\\TownBox.bmp");
	// g_pSprBox2=new Sprite(NULL,"resource\\TownBox.bmp");                              //����һ������
	//���붯��ͼ�񣬲���ʼ����������
	g_pSprTestAnima1=new Sprite(NULL,"resource\\Star.bmp"); //       111111
	g_pSprTestAnima1->InitAnima(2,6,150);
    g_pSprTestAnima2=new Sprite(NULL,"resource\\Star1.bmp");//        22222
	g_pSprTestAnima2->InitAnima(2,6,150);
	
	
	//��������ӵ�����������
	g_Sprm.AddSprite(g_pSprTestBK,0);
	g_Sprm.AddSprite(g_pSprTestAnima1,3);
	g_Sprm.AddSprite(g_pSprTestAnima2,3);
	g_Sprm.AddSprite(g_pSprBox,3);
	// g_Sprm.AddSprite(g_pSprBox2,3);                                                 //����һ������
    //g_Sprm.AddSprite(mapbk,3);                //����ĵ�ͼ
	
	if(g_Map.LoadMap(stage))
		g_Map.AddMap2SpriteManager(g_Sprm);
    
	/*	g_ptTestAnima1.x=505;
	g_ptTestAnima1.y=137;*/
	
	//�رճ���һ������
    g_pMscBGM1->Stop();
	//������Ϸ���ֶ��󲢴��ļ�
	g_pMscMove=new GameMusic("resource\\hit.wav");
	g_pMscBGM=new GameMusic("resource\\bgm.mp3");
	g_pMscBGM->Play(300,TRUE);	//�ظ���������	
	
	//������Ϸ�����������˶�����
	RECT rObject={560,100,560+g_pSprTestAnima1->GetWidth()/6,100+g_pSprTestAnima1->GetHeight()/2};
	RECT rBound={0,0,g_pGE->GetWidth(),g_pGE->GetHeight()};
	POINTF ptFocus={0,0};
	POINTF ptVelo={0,5};
	POINTF ptAccelerate={0,0};
	POINTF ptDes={300,300};
	g_pPhyTest=new GamePhysics(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);
	// g_pPhyTest2=new GamePhysics(rObject,rBound,ptFocus,ptVelo,ptAccelerate,ptDes,FALSE);/////////2

	g_pPhyTest -> SetVelo(0, 0);
	g_pPhyTest -> SetAccelerate(g_gravityAcceleration);
	g_pPhyTest -> SetMoveState(true);

	
	//�������������˶�����
	RECT rObject1={308,326,308+g_pSprBox->GetWidth(),326+g_pSprBox->GetHeight()};
	RECT rBound1={0,0,g_pGE->GetWidth(),g_pGE->GetHeight()};
	POINTF ptFocus1={0,0};
	POINTF ptVelo1={0,0};
	POINTF ptAccelerate1={0,0};
	POINTF ptDes1={300,300};
	g_pPhyBox=new GamePhysics(rObject1,rBound1,ptFocus1,ptVelo1,ptAccelerate1,ptDes1,FALSE);

	g_pPhyBox -> SetVelo(0, 0);
	g_pPhyBox -> SetAccelerate(g_gravityAcceleration);
	g_pPhyBox -> SetMoveState(true);


	//����һ������,���˵�һ�����������޸ģ��޸��˳��ֵ�λ�ã������඼��ֲ�˵�һ�����ӵ�����
 //    RECT rObject2={408,326,408+g_pSprBox->GetWidth(),326+g_pSprBox->GetHeight()};
	// g_pPhyBox2=new GamePhysics(rObject2,rBound1,ptFocus1,ptVelo1,ptAccelerate1,ptDes1,FALSE);

	g_bInitScene=TRUE;	//���ó�����ʼ����־
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ����3���� */
BOOL PlayScene_3(HWND hWnd)
{
	//���þ��������Ϣ
	g_pSprTestBK->SetDrawInfo(0,0,TRUE,(255,255,255));
	g_pSprBox->SetDrawInfo(g_pPhyBox->GetLeftTop().x,g_pPhyBox->GetLeftTop().y,TRUE);
	// g_pSprBox2->SetDrawInfo(g_pPhyBox2->GetLeftTop().x,g_pPhyBox2->GetLeftTop().y,TRUE);      //����һ������
	
	g_pSprTestAnima1->SetDrawAnimaInfo(g_pPhyTest->GetLeftTop().x,g_pPhyTest->GetLeftTop().y,0,TRUE,RGB(255,255,255));

	// TODO:
	// ʵ�������������Ǻ���������ש����
	// ��ʵ���������ڵذ���
	// POINTF ptDes = {500, 500};
	// g_pPhyTest -> SetDes(ptDes);
	// g_pPhyTest -> SetMoveState(true);
	// g_pPhyTest -> MoveToDes();
	// g_pPhyTest -> SetMoveState(false);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  ��Ⱦ��Ϸ���� */
void GamePaint(HDC hDC)
{
	if(g_bInitScene)	//�жϳ�����ʼ���Ƿ����
		g_Sprm.Draw(hDC);
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* ��Ϸ���� */
void GameEnd()
{
	g_Sprm.Release(TRUE);
	g_Map.Release(TRUE);
	//delete	g_pLoadScene;
	delete g_pPhyTest;
	delete g_pPhyBox;
	// delete g_pPhyBox2;
	delete g_pGE;	//�����Ϸ����ָ��
	delete g_pMscBGM;
	delete g_pMscMove;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���� */
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);	
	
	/* ��������Ӿ������Ϸ�����¼�������� */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ��ͣ */
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
	
	/* ��������Ӿ������Ϸ��ͣ�¼�������� */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��Ϸ���ڹر� */
BOOL GameWindowClose(HWND hWnd)
{
	/* ��Ϸ���ڹر�ǰ�Ĵ������ */
	
	if(MessageBox(g_pGE->GetWindow(),"��ȷ��Ҫ�˳���","�˳���Ϸ",MB_YESNO|MB_DEFBUTTON2 | MB_ICONASTERISK)==IDYES)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*������Ϣ����*/
void KeyEvent(HWND hWnd)
{
	if(g_nScene==3)
	{
		RECT r1;
		//����Ѽ������������2��ײ�ĺ���������ǰ�������жϣ��Ͳ������������ҡ����������������涼�ֱ�����ж���
		// if(g_pPhyTest->Collision(g_pPhyBox2,BA_STOP,&r1)) //�������������2����ײ���ڶ���������BA_STOP��ע���Ҷ�GamePhysics���е�Collision�������޸�
		// {
		// 	g_pPhyTest->CheckErr(TRUE);	
		// }
		
		if(g_pPhyBox -> GetMoveState())
		{
			g_pPhyBox -> ShiftMove();
		}

		if(g_pPhyTest -> GetMoveState())
		{
			g_pPhyTest -> ShiftMove();
		}

		else if(GetAsyncKeyState(VK_UP)<0&&GetAsyncKeyState(VK_LEFT)==0&&GetAsyncKeyState(VK_RIGHT)==0)		//ֻ���Ϸ��������
		{
			g_pPhyTest -> SetVelo(0, -10);
			g_pPhyTest -> SetAccelerate(g_gravityAcceleration);
			g_pPhyTest -> SetMoveState(true);
		}
		else if(GetAsyncKeyState(VK_UP)<0&&GetAsyncKeyState(VK_LEFT)<0)		//�ж����Ϸ�����Ƿ���
		{
			g_pPhyTest -> SetVelo(-5, -10);
			g_pPhyTest -> SetAccelerate(g_gravityAcceleration);
			g_pPhyTest -> SetMoveState(true);
		}
		else if(GetAsyncKeyState(VK_UP)<0&&GetAsyncKeyState(VK_RIGHT)<0)		//�ж����Ϸ�����Ƿ���
		{
			g_pPhyTest -> SetVelo(5, -10);
			g_pPhyTest -> SetAccelerate(g_gravityAcceleration);
			g_pPhyTest -> SetMoveState(true);
		}
		
		else if(GetAsyncKeyState(VK_SPACE)<0)
		{	
			g_pPhyTest -> SetVelo(0, -5);
			g_pPhyTest->MoveDirect(DI_UP);	//��Ϸ�������˶����������ƶ�
			g_pPhyTest->CheckErr(TRUE);	//����Ƿ񳬳������
			
			//����ͼ��ͻ�ͼ����
			g_pMscMove->Play(300,FALSE,FALSE);	//�����ƶ���Ч
			if(g_pPhyBox->Collision(g_pPhyTest,BA_STOP,&r1))
			{
				g_pPhyBox->MoveDirect(DI_UP);	//��Ϸ�������˶����������ƶ�
				g_pPhyBox->CheckErr(TRUE);	
			}
			g_pPhyTest -> SetVelo(0, 0);
		}
		else if(GetAsyncKeyState(VK_DOWN)<0)	//�ж��·�����Ƿ���
		{
			g_pPhyTest -> SetVelo(0, 5);
			g_pPhyTest->MoveDirect(DI_DOWN);	//��Ϸ�������˶����������ƶ�
			g_pPhyTest->CheckErr(TRUE);	//����Ƿ񳬳������
			
			//����ͼ��ͻ�ͼ����
			g_pMscMove->Play(300,FALSE,FALSE);	//�����ƶ���Ч
			if(g_pPhyBox->Collision(g_pPhyTest,BA_STOP,&r1))
			{
				g_pPhyBox->MoveDirect(DI_DOWN);	//��Ϸ�������˶����������ƶ�
				g_pPhyBox->CheckErr(TRUE);	
			}
			g_pPhyTest -> SetVelo(0, 0);
		}
		else if(GetAsyncKeyState(VK_LEFT)<0)	//�ж�������Ƿ���
		{		
			// g_pPhyTest -> SetVelo(-5, g_pPhyTest -> GetVelo().y);
			g_pPhyTest -> SetVelo(-5, 0);
			// g_pPhyTest -> SetMoveState(true);
			// g_pPhyTest -> ShiftMove();
			g_pPhyTest->MoveDirect(DI_LEFT);	//��Ϸ�������˶����������ƶ�
			g_pPhyTest->CheckErr(TRUE);	//����Ƿ񳬳������
			
			//����ͼ��ͻ�ͼ����
			g_pMscMove->Play(300,FALSE,FALSE);	//�����ƶ���Ч
			if(g_pPhyBox->Collision(g_pPhyTest,BA_STOP,&r1))
			{
				g_pPhyBox->MoveDirect(DI_LEFT);	//��Ϸ�������˶����������ƶ�
				g_pPhyBox->CheckErr(TRUE);	
			}
			g_pPhyTest -> SetVelo(0, 0);
		}
		else if(GetAsyncKeyState(VK_RIGHT)<0)	//�ж��ҷ�����Ƿ���
		{	
			// g_pPhyTest -> SetVelo(5, g_pPhyTest -> GetVelo().y);
			g_pPhyTest -> SetVelo(5, 0);
			// g_pPhyTest -> SetMoveState(true);
			// g_pPhyTest -> ShiftMove();
			g_pPhyTest->MoveDirect(DI_RIGHT);	//��Ϸ�������˶����������ƶ�
			g_pPhyTest->CheckErr(TRUE);	//����Ƿ񳬳������
			
			//����ͼ��ͻ�ͼ����
			g_pMscMove->Play(300,FALSE,FALSE);	//�����ƶ���Ч
			if(g_pPhyBox->Collision(g_pPhyTest,BA_STOP,&r1))
			{
				g_pPhyBox->MoveDirect(DI_RIGHT);	//��Ϸ�������˶����������ƶ�
				g_pPhyBox->CheckErr(TRUE);	
			}
			g_pPhyTest -> SetVelo(0, 0);
		}
		else if(GetAsyncKeyState(VK_PRIOR)<0)	//����PageUp��������������������
			g_pMscBGM->VolumeUp();
		else if(GetAsyncKeyState(VK_NEXT)<0)	//����PageDown������������������С
			g_pMscBGM->VolumeDown();
		else if(GetAsyncKeyState(VK_HOME )<0)	//����Home�������²��ű�������
			g_pMscBGM->Play(300,TRUE);
		else if(GetAsyncKeyState(VK_END )<0)	//����End����ֹͣ���ű�������
			g_pMscBGM->Stop();
		else if(GetAsyncKeyState(VK_ESCAPE)<0 )	//�ж�ESC���Ƿ���
			SendMessage(hWnd,WM_CLOSE,0,0);     //�˳�����
		
		else 			//���û�з����������
		{
			g_pPhyTest -> SetVelo(0, 0);
			g_pPhyTest -> SetAccelerate(g_gravityAcceleration);
			g_pPhyTest -> SetMoveState(true);

			g_pPhyBox -> SetVelo(0, 0);
			g_pPhyBox -> SetAccelerate(g_gravityAcceleration);
			g_pPhyBox -> SetMoveState(true);

		}
	}
}

/* ��굥���¼����� */
void MouseLButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
	/* ��������Ӿ������굥���¼�������� */
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
		g_Sprm.Release(TRUE);		//ɾ������ͼ��
		InitScene_2(hWnd);	//��ʼ������2;
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
		g_Sprm.Release(TRUE);		//ɾ������ͼ��
		InitScene_3(hWnd);	//��ʼ������3;
		g_nScene=3;}
	
	}
	else
	{
		char str1[100];
		sprintf(str1,"�������X��%d     Y��%d    ",x,y); 
		MessageBox(hWnd,str1,"XJ's",MB_YESNO);
	}
	
}

//������������Ϣ������
void MouseLButtonUp(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//������˫����Ϣ������
void MouseDoubleClick(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//����Ҽ�������Ϣ������
void MouseRButtonDown(HWND hWnd,int x,int y,WPARAM wParam)
{
}

//����ƶ���Ϣ������
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

