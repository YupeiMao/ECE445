/******************************************************************************
 * MenuConfig.H - 菜单参数配置
 ******************************************************************************/

#ifndef __MENUCONFIG_H
#define __MENUCONFIG_H

//定义按键编码

#define Key_Enter      1
#define Key_Up         2
#define Key_Down       3
#define Key_Back       4

//--------菜单内核按键定义
//#define Key_First      Key_Up
#define Key_Last       Key_Down
#define Key_Prev       Key_Back 
#define Key_Next       Key_Enter

//----------------------------------------------lcdconfig
//屏幕最大显示项
#define MaxScreenSize      2
//--------菜单开关中断
//#define MenuIntDisable()                IntMasterDisable()
//#define MenuIntEnable()                 IntMasterEnable()

//--------菜单节点总数
#define MenuTotalNode     5//7+5

//--------菜单堆栈深度
#define MenuStackDeep      5

//----------------------------------------------菜单内核
//--------菜单状态类型
#define menufunc           0
#define numberfunc         1

//--------菜单索引类型
#define firstnode          1
#define lastnode           2
#define prevnode           3
#define nextnode           4

//--------菜单节点结构体
typedef struct _MenuNode
{
   u16  MenuNodeID;
   u8 *MenuString;
   u8 MenuStatus;
   struct _MenuNode *First_Node;
   struct _MenuNode *Last_Node;
   struct _MenuNode *Prev_Node;
   struct _MenuNode *Next_Node;
   void(*Action)(u8 in);
}MenuNode;

//--------菜单链表
typedef struct _MenuList
{
   struct _MenuNode *Point_Node[MenuTotalNode];
}MenuList;

//--------菜单内核变量
extern u8 MenuDeep;
extern u8 CurrentMenuStatus;

//--------菜单节点链
extern MenuList MenuTotalList;
extern MenuNode *CurrentMenuNode;

//--------menuinit
extern void MenuListInit(void);
extern u16 MenuLoop(u8 key);
extern u16 GetCurMenuID(void);

//--------菜单内核
extern MenuNode *SearchMenuNode(u16 nodeid,u8 searchtype);
extern MenuNode *SearchSomeOneMenuNode(u16 nodeid);
extern void MenuShow(void);
extern void MenuFunctionKey(u8 key);
extern void MenuNumberKey(u8 key);

//--------菜单扩展
void (*MenuNodeAction)(u8 key);

/**************************** 菜单目录使用的空函数 ************************/
void MenuActionNULL(u8 key);

#endif
