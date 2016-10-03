/*********************************
	游戏物理动作头文件GamePhysics.h
*********************************/

#ifndef DEF_GAMEPHYSICS		//条件编译，目的是防止文件被重复编译

#define DEF_GAMEPHYSICS  1

#include "windows.h"
#include "stdio.h"
#include "math.h"
#include <vector>		//包含vector
using namespace std;	// 引用标准模板库std

//定义碰撞后的动作常量
typedef		int		BOUNDACTION;
const BOUNDACTION	BA_STOP=0,
					BA_LOOP=1,
					BA_REBOUND=2,
					BA_CLEAR=3;	

//定义方向常量
typedef int DIRECTION;			
const DIRECTION DI_STOP=0,
				DI_LEFT=1,
				DI_RIGHT=2,
				DI_UP=3,
				DI_DOWN=4;

//定义float型点结构POINTF
typedef struct POINTFtag
{
public:
	float x;
	float y;
	
	//定义赋值运算符＝
	const	POINTFtag  & operator   =(const POINTFtag &pt)   
	{   
		x=pt.x;
		y=pt.y;
		return * this ;
	}
	
	//定义加法运算符＋
	const	POINTFtag  operator	+(const POINTFtag &pt)
	{	
		POINTFtag ptTmp;
		ptTmp.x=x+pt.x;
		ptTmp.y=y+pt.y;
		return ptTmp;
	}

	//定义减法运算符-
	const 	POINTFtag  operator	-(const POINTFtag &pt)
	{
		POINTFtag ptTmp;
		ptTmp.x=x-pt.x;
		ptTmp.y=y-pt.y;
		return ptTmp;
	}
} POINTF;


/*游戏物理动作类*/

class GamePhysics
{
protected:
	POINTF	m_ptFocus;			//对象焦点坐标，以相对于对象左上角的偏移位置来表示
	POINTF	m_ptPos;			//以对象焦点的全局坐标来表示的，对象在画面中的位置
	RECT	m_rObject;			//对象范围	
	RECT	m_rFocusBound;		//对象焦点运动范围
	RECT	m_rBound;			//对象运动范围


	POINTF	m_ptVelo;			//速度矢量
	POINTF	m_ptAccelerate;		//加速度
	float	m_fStep;			//移动时的步长，相当于速度矢量m_ptVelo的速度(即长度)		
	POINTF	m_ptDes;			//移动时的有效目标点

	DIRECTION	m_Direct;		//运动方向
	
	BOOL	m_bMove;			//对象是否运动的标志

	BOOL	m_bPathArrive;		//对象是否到达路径终点
	int		m_nPathIndex;		//路径点下标索引
	BOOL	m_bInitIndex;		//路径索引是否初始化

	BOOL	m_bVisible;			//对象是否可见
	/*新增用于碰撞检测的属性*/
	BOUNDACTION		m_BoundAction;		//物体撞上运动边框后的动作

	RECT	m_rCheckBox;		//碰撞检测框

public:
	//构造函数
	GamePhysics();	

	//按指定的对象的范围和运动范围来构造对象
	GamePhysics(RECT rObject,RECT rBound);

	//按指定的对象矩形rObject、运动范围rBound、焦点ptFocus、速度ptVelo、加速度ptAccelerate、目标点ptDes和运动状态bMove来构造对象
	GamePhysics(RECT rObject,RECT rBound,POINTF ptFocus,POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove);

	//析构函数
	~GamePhysics();


	/*访问对象属性方法*/

	//设置对象范围
	void SetObjectRect(RECT r)
	{
		CopyRect(&m_rObject,&r);
		SetCheckBox(m_rObject);			//设置碰撞检测矩形
	};
	void SetObjectRect(int left,int top,int right,int bottom)
	{
		m_rObject.left=left;
		m_rObject.top=top;
		m_rObject.right=right;
		m_rObject.bottom=bottom;
	};
	//获取对象范围
	RECT GetObjectRect()
	{
		return m_rObject;
	};

	//获取宽度
	int GetWidth()
	{
		return m_rObject.right-m_rObject.left;
	};


	//获取高度	
	int GetHeight()
	{
		return m_rObject.bottom-m_rObject.top;
	};
	
	//设置对象焦点位置(相对于对象左上角的偏移值)
	void SetFocus(POINTF ptFocus)
	{	
		m_ptFocus=ptFocus;
		
		//同时应改变对象的焦点运动范围????????
		m_rFocusBound.left=(int)m_ptFocus.x+m_rBound.left;	
		m_rFocusBound.top=(int)m_ptFocus.y+m_rBound.top;
		m_rFocusBound.right=m_rBound.right-(GetWidth()-(int)m_ptFocus.x);
		m_rFocusBound.bottom=m_rBound.bottom-(GetHeight()-(int)m_ptFocus.y);
	};
	void SetFocus(float x,float y)
	{	
		POINTF pt={x,y};
		SetFocus(pt);
	};
	//获取对象焦点位置
	POINTF GetFocus()
	{
		return m_ptFocus;
	};

	//获取对象焦点的运动范围
	RECT GetFocusBound()
	{
		return m_rFocusBound;
	};

	//设置、获取对象的坐标(以焦点在全局画面中的位置表示)
	void SetPos(POINTF ptPos)
	{	
		m_ptPos=ptPos;
	
		POINTF pt=ptPos-m_ptFocus;	//计算对象左上角坐标

		int w=m_rObject.right-m_rObject.left;
		int h=m_rObject.bottom-m_rObject.top;

		m_rObject.left=(int)pt.x;
		m_rObject.top=(int)pt.y;
		m_rObject.right=(int)pt.x+w;
		m_rObject.bottom=(int)pt.y+h;
		SetCheckBox(m_rObject);			//设置碰撞检测矩形
	};
	void SetPos(float x,float y)
	{	
		POINTF pt={x,y};
		SetPos(pt);
	};
	//获取对象的坐标
	POINTF GetPos()
	{
		return m_ptPos;
	};

	//改变对象左上角点的坐标
	void SetLeftTop(POINTF pt)
	{
		int nWidth=m_rObject.right-m_rObject.left;
		int nHeight=m_rObject.bottom-m_rObject.top;

		m_rObject.left=(int)pt.x;	//改变对象的范围坐标
		m_rObject.top=(int)pt.y;
		m_rObject.right=(int)pt.x+nWidth;
		m_rObject.bottom=(int)pt.y+nHeight;

		SetCheckBox(m_rObject);			//设置碰撞检测矩形
	};
	void SetLeftTop(int x,int y)
	{
		int nWidth=m_rObject.right-m_rObject.left;
		int nHeight=m_rObject.bottom-m_rObject.top;

		m_rObject.left=x;
		m_rObject.top=y;
		m_rObject.right=x+nWidth;
		m_rObject.bottom=y+nHeight;

		SetCheckBox(m_rObject);			//设置碰撞检测矩形

	};		
	//获取对象左上角点的坐标
	POINTF GetLeftTop()
	{
		POINTF pt={(float)m_rObject.left,(float)m_rObject.top};
		return pt;
	};

	//设置运动范围
	void SetRectBound(RECT rc)
	{
		CopyRect(&m_rBound,&rc);
	};
	void SetRectBound(int left,int top,int right,int bottom)
	{
		m_rBound.left=left;
		m_rBound.top=top;
		m_rBound.right=right;
		m_rBound.bottom=bottom;
	};
	//获取运动范围
	RECT GetRectBound()
	{
		return m_rBound;
	};
	
	//根据目标点pt来设置运动时的有效目标点
	void SetDes(POINTF pt)
	{
		if(pt.x<m_rFocusBound.left) 			//如果向左超出
			pt.x=(float)m_rFocusBound.left;
		else if(pt.x>m_rFocusBound.right) 		//如果向右超出
			pt.x=(float)m_rFocusBound.right;

		if(pt.y<m_rFocusBound.top)				//如果向上超出
			pt.y=(float)m_rFocusBound.top;
		else if(pt.y>m_rFocusBound.bottom) 		//如果向下超出
			pt.y=(float)m_rFocusBound.bottom;

		m_ptDes=pt;				//设置有效目标点
		m_bPathArrive=FALSE;	//设置到达路径终点状态为FALSE
	};
	void SetDes(float x,float y)
	{
		POINTF pt={x,y};
		SetDes(pt);

	};
	//获取有效目标点
	POINTF GetDes()
	{
		return m_ptDes;
	};

	//获取对象是否到达目标点的状态
	BOOL GetPathArrive()
	{
		return m_bPathArrive;
	}

	//设置速度，速度改变后则运动步长与方向也随之改变
	void SetVelo(POINTF ptVelo)
	{
		m_ptVelo=ptVelo;	//设置速度
		m_fStep=(float)hypot(ptVelo.x,ptVelo.y);	//计算运动的步长
		
		//计算运动方向
		if(fabs(m_ptVelo.x)<0.001 && fabs(m_ptVelo.y)<0.001)
			m_Direct=DI_STOP;
		else if((m_ptVelo.x+m_ptVelo.y)>0)
		{
			if(m_ptVelo.x>=m_ptVelo.y)
				m_Direct=DI_RIGHT;
			else
				m_Direct=DI_DOWN;
		}
		else
		{
			if(m_ptVelo.x>m_ptVelo.y)
				m_Direct=DI_UP;
			else
				m_Direct=DI_LEFT;
		}
	};
	void SetVelo(float x,float y)
	{
		POINTF pt={x,y};
		SetVelo(pt);
	};
	//获取速度
	POINTF GetVelo()
	{
		return m_ptVelo;
	};

	//获取运动方向
	DIRECTION GetDirect()
	{
		return m_Direct;
	};

	//设置加速度
	void SetAccelerate(POINTF ptAccelerate)
	{
		m_ptAccelerate=ptAccelerate;
	};
	void SetAccelerate(float x,float y)
	{
		m_ptAccelerate.x=x;
		m_ptAccelerate.y=y;
	};

	//设置对象运动状态
	void SetMoveState(BOOL bMove)
	{
		m_bMove=bMove;
	};
	//获取对象运动状态	
	BOOL GetMoveState()
	{
		return m_bMove;
	};

	//  设置、获取对象是否可见
	void SetVisible(BOOL bVisible)
	{
		m_bVisible=bVisible;
	};

	BOOL GetVisible()
	{
		return m_bVisible;
	};
	
	/*常规方法*/

	//按指定的对象范围rObject和运动范围rBound来设置对象参数
	void SetObject(RECT rObject,RECT rBound);

	// 按指定的对象的范围rObject、运动范围rBound、焦点ptFocus、速度ptVelo、加速度ptAccelerate、目标点ptDes和运动状态bMove来设置对象参数
	void SetObject(RECT rObject,RECT rBound,POINTF ptFocus,POINTF ptVelo,POINTF ptAccelerate,POINTF ptDes,BOOL bMove);

	//均速运动
	void	UniformMove();

	//加速度运动
	void	ShiftMove();
	// 有地图障碍物的加速度运动
	void	ShiftMove(GamePhysics* ph);
	void	ShiftMove(vector<GamePhysics*> v_ph);
	
	//移动到目标点
	void	MoveToDes();

	//沿指定路径移动
	void	MoveAlongPath(POINTF * ptDesPath,int nPtCount,BOOL bCycle=FALSE);

	//向方向Direction移动
	void	MoveDirect(DIRECTION Direct);

	// 判断点pt是否在矩形范围r内
	BOOL  IsPointInBound(POINTF pt,RECT r);

	BOOL CheckErr(BOOL bRectify);
	BOOL CheckErr(GamePhysics* ph, BOOL bRectify);
	BOOL CheckErr(vector<GamePhysics*> v_ph, BOOL bRectify);

	// 实现物体因重力而下落的效果  20161002
	void Fall();

	BOOL TouchMapBricks();
	BOOL TouchMapBricks(vector<GamePhysics*> v_ph);

	/*新增用于碰撞检测的相关方法*/


	//设置碰撞检测矩形
	void SetCheckBox(RECT rObject)
	{
		int w=(int)((rObject.right-rObject.left)*0.1);
		int h=(int)((rObject.bottom-rObject.top)*0.1);
		// w=0;h=0;
		m_rCheckBox.left=rObject.left+w;
		m_rCheckBox.right=rObject.right-w;
		m_rCheckBox.top=rObject.top+h;
		m_rCheckBox.bottom=rObject.bottom-h;
		// m_rCheckBox = rObject;
	}

	//获取碰撞检测矩形
	RECT GetCheckBox()
	{
		return m_rCheckBox;
	}

	// 按速度m_ptVelo进行均速直线移动,并对边框碰撞进行检测,当发生碰撞时,按action指定的方式动作
	void	UniformMove2(BOUNDACTION action);

	// 当前物体按给定速度进行直线移动,另一物体ph也按其给定速度进行直线运动,对两个物体的碰撞进行检测,当发生碰撞时,按action指定的方式动作
	BOOL	Collision(GamePhysics  * ph, BOUNDACTION action,RECT * rCollision);

	// 重载Collision，输入vector
	BOOL Collision(vector<GamePhysics*> v_ph, BOUNDACTION action, RECT *rCollision);

};

#endif