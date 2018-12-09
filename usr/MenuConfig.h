/******************************************************************************
 * MenuConfig.H - �˵���������
 ******************************************************************************/

#ifndef __MENUCONFIG_H
#define __MENUCONFIG_H

//���尴������

#define Key_Enter      1
#define Key_Up         2
#define Key_Down       3
#define Key_Back       4

//--------�˵��ں˰�������
//#define Key_First      Key_Up
#define Key_Last       Key_Down
#define Key_Prev       Key_Back 
#define Key_Next       Key_Enter

//----------------------------------------------lcdconfig
//��Ļ�����ʾ��
#define MaxScreenSize      2
//--------�˵������ж�
//#define MenuIntDisable()                IntMasterDisable()
//#define MenuIntEnable()                 IntMasterEnable()

//--------�˵��ڵ�����
#define MenuTotalNode     5//7+5

//--------�˵���ջ���
#define MenuStackDeep      5

//----------------------------------------------�˵��ں�
//--------�˵�״̬����
#define menufunc           0
#define numberfunc         1

//--------�˵���������
#define firstnode          1
#define lastnode           2
#define prevnode           3
#define nextnode           4

//--------�˵��ڵ�ṹ��
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

//--------�˵�����
typedef struct _MenuList
{
   struct _MenuNode *Point_Node[MenuTotalNode];
}MenuList;

//--------�˵��ں˱���
extern u8 MenuDeep;
extern u8 CurrentMenuStatus;

//--------�˵��ڵ���
extern MenuList MenuTotalList;
extern MenuNode *CurrentMenuNode;

//--------menuinit
extern void MenuListInit(void);
extern u16 MenuLoop(u8 key);
extern u16 GetCurMenuID(void);

//--------�˵��ں�
extern MenuNode *SearchMenuNode(u16 nodeid,u8 searchtype);
extern MenuNode *SearchSomeOneMenuNode(u16 nodeid);
extern void MenuShow(void);
extern void MenuFunctionKey(u8 key);
extern void MenuNumberKey(u8 key);

//--------�˵���չ
void (*MenuNodeAction)(u8 key);

/**************************** �˵�Ŀ¼ʹ�õĿպ��� ************************/
void MenuActionNULL(u8 key);

#endif
