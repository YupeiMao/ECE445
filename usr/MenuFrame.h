/******************************************************************************
 * MenuFrame.H - �˵��ں�
 ******************************************************************************/  

//--------�˵��ں˶�ջ
u8 CurrentMenuStatus   =0;
u8 CurrentMenuCur      =0;
u8 MenuDeep            =0;		//�˵�����
u8 MenuCurStack[MenuStackDeep];	//��סÿһ��˵�����λ��

//--------�˵�����
MenuList MenuTotalList;
MenuNode *CurrentMenuNode;

MenuNode *SearchMenuNode(u16 nodeid,u8 searchtype)
{
   u8 i;
   u16  fathernodeid;
   MenuNode *SearchMenuNode;
   MenuNode *ReturnMenuNode=NULL;
   u16 searchnodeid=0; 

   fathernodeid=nodeid/100;   
   switch(searchtype)
   {
      case firstnode:
           searchnodeid=nodeid-1;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      case lastnode:
           searchnodeid=nodeid+1;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      case prevnode:
           searchnodeid=fathernodeid;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      case nextnode:
           searchnodeid=nodeid*100+1;
           for(i=0;i<MenuTotalNode;i++)
           {
              SearchMenuNode=MenuTotalList.Point_Node[i];
              if((*SearchMenuNode).MenuNodeID==searchnodeid)
              {
                 ReturnMenuNode=SearchMenuNode;
                 break;
              }
           }
           break;
      default:break;
   }
   return ReturnMenuNode;
}

//--------������һ�˵��ڵ�
MenuNode *SearchSomeOneMenuNode(u16 nodeid)
{
   u8 i;
   MenuNode *SearchMenuNode;
   MenuNode *ReturnMenuNode=NULL;
   
   for(i=0;i<MenuTotalNode;i++)
   {
      SearchMenuNode=MenuTotalList.Point_Node[i];
      if((*SearchMenuNode).MenuNodeID==nodeid)
      {
         ReturnMenuNode=SearchMenuNode;
         break;
      }
   }
   return ReturnMenuNode;
}

//--------�˵���ʾ
void MenuShow(void)
{
   int8 i;
   static MenuNode *ShowMenuNode;
   switch(CurrentMenuStatus)
   {
      case menufunc:
       Func_LCD_WriteString16(1,1,"           [ESC]\0");
		   Func_LCD_WriteString16(2,1,"            [OK]\0");
       ShowMenuNode=SearchSomeOneMenuNode((*CurrentMenuNode).MenuNodeID-CurrentMenuCur);
		   Func_LCD_WriteString16(CurrentMenuCur+1,1,"->");
			 for(i=0;i<MaxScreenSize;i++)
			 {
					Func_LCD_WriteString16(i+1,3,(*ShowMenuNode).MenuString);
					if((*ShowMenuNode).Last_Node!=NULL)
					{
						ShowMenuNode=(*ShowMenuNode).Last_Node;
					}
					else
						break;
        }
        break;
      case numberfunc:
        break;
      default:break;
   }
}

//--------�˵���������
void MenuFunctionKey(int8 key)
{
//   MenuIntDisable();
   switch(key)
   {
//      case Key_First:
//           if((*CurrentMenuNode).First_Node!=NULL)
//           {
//             CurrentMenuNode=(*CurrentMenuNode).First_Node;
//             if(CurrentMenuCur>0)
//                CurrentMenuCur--;
//           }
//           break;
      case Key_Last:
           if((*CurrentMenuNode).Last_Node!=NULL)
           {
             CurrentMenuNode=(*CurrentMenuNode).Last_Node;
             if(CurrentMenuCur<(MaxScreenSize-1))
                CurrentMenuCur++;
           }
					 else
					 {
						 for(;;)
						 {
							 if((*CurrentMenuNode).First_Node!=NULL)
							 {
									CurrentMenuNode=(*CurrentMenuNode).First_Node;
									if(CurrentMenuCur>0)
										CurrentMenuCur--;
							 }
							 else
							 {
									break;
							 }
						 }
						 
					 }
           break;
      case Key_Prev:
           if((*CurrentMenuNode).Prev_Node!=NULL)
           {
             CurrentMenuNode=(*CurrentMenuNode).Prev_Node;
             MenuDeep--;
             CurrentMenuCur=MenuCurStack[MenuDeep];
           }
           break;
      case Key_Next:
           if((*CurrentMenuNode).Next_Node!=NULL)
           {
             CurrentMenuNode=(*CurrentMenuNode).Next_Node;
             MenuCurStack[MenuDeep]=CurrentMenuCur;
             CurrentMenuCur=0;
             MenuDeep++;
           }
           break;
      default:break;
   }
//   MenuIntEnable();
}

//--------�˵���չ��������
void (*MenuNodeAction)(int8 key);

//--------�˵���������, ��չ����
void MenuNumberKey(int8 key)
{
//   MenuIntDisable();
   MenuNodeAction=(*CurrentMenuNode).Action;
//   MenuIntEnable();
   (*MenuNodeAction)(key);
}
