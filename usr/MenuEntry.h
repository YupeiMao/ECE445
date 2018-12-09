/******************************************************************************
 * MenuEntry.H - 菜单初始化入口及菜单主循环
 ******************************************************************************/

//
//the menu node 
//        Prev
//         |
//--Down--Node--Up
//         |
//        Next
//
//esample the menunode list:NodeId rule:the fathernodeid+thisnodelistorder
//--------------------------------------Node2----------------------------------------Node1
//                                        |                                            |
//             Node202-----------------Node201               Node102----------------Node101
//                |                       |                     |                      |
// Node20202---Node20201  Node20102---Node20101  Node10102---Node10201  Node10102---Node10101
//

//--------当前菜单信息
MenuNode MenuNode1 ={1,"Set Clock     \0",numberfunc,(void*)0,(void*)0,(void*)0,(void*)0,Func_Set_Clock};
MenuNode MenuNode2 ={2,"Set Date      \0",numberfunc,(void*)0,(void*)0,(void*)0,(void*)0,Func_Set_Date};
MenuNode MenuNode3 ={3,"Set Temper    \0",numberfunc,(void*)0,(void*)0,(void*)0,(void*)0,Func_Set_Temper};
MenuNode MenuNode4 ={4,"Set Rhum      \0",numberfunc,(void*)0,(void*)0,(void*)0,(void*)0,Func_Set_Rhum};
MenuNode MenuNode5 ={5,"Set o3_Tim    \0",numberfunc,(void*)0,(void*)0,(void*)0,(void*)0,Func_Set_o3_tim};
MenuNode MenuNode9 ={2,"              \0",numberfunc,(void*)0,(void*)0,(void*)0,(void*)0,MenuActionNULL};

//MenuNode MenuNode101={101,"  ID", numberfunc,(void*)0,(void*)0,(void*)0,(void*)0,MenuActionNULL};

//--------菜单初始化
void MenuListInit(void)
{
   u8 i,index = 0;
   MenuNode *InitMenuNode;
   CurrentMenuNode=&MenuNode1;
   MenuTotalList.Point_Node[index++]=&MenuNode1;
   MenuTotalList.Point_Node[index++]=&MenuNode2;
   MenuTotalList.Point_Node[index++]=&MenuNode3;
	 MenuTotalList.Point_Node[index++]=&MenuNode4;
	 MenuTotalList.Point_Node[index++]=&MenuNode5;
//   MenuTotalList.Point_Node[index++]=&MenuNode101;
//   MenuTotalList.Point_Node[index++]=&MenuNode102;
   for(i=0;i<MenuTotalNode;i++)		  
   {
      InitMenuNode=MenuTotalList.Point_Node[i];
      (*InitMenuNode).First_Node=SearchMenuNode((*InitMenuNode).MenuNodeID,firstnode);
      (*InitMenuNode).Last_Node =SearchMenuNode((*InitMenuNode).MenuNodeID,lastnode);
      (*InitMenuNode).Prev_Node =SearchMenuNode((*InitMenuNode).MenuNodeID,prevnode);
      (*InitMenuNode).Next_Node =SearchMenuNode((*InitMenuNode).MenuNodeID,nextnode);
   }
}

//--------菜单主操作
u16 MenuLoop(u8 key)
{
	if(key==KEY_DEC)
	{
		key = Key_Down;
	}
	else if(key==KEY_ESC)
	{
		key = Key_Back;
	}
	else if(key==KEY_OK)
	{
		key = Key_Enter;
	}
	switch(key)
	{
		case Key_Back:		
		case Key_Up:
		case Key_Down:
			 MenuFunctionKey(key);MenuShow();break;
		case Key_Enter:
			 if((*CurrentMenuNode).MenuStatus == numberfunc)
			 {
				 MenuNumberKey(key);
			 }
			 else
			 {
				 MenuFunctionKey(key);
			 }
			 MenuShow();break; 
		default:
			break;
	}
	return (*CurrentMenuNode).MenuNodeID; 
}

u16 GetCurMenuID(void)
{
	return (*CurrentMenuNode).MenuNodeID;	
}


