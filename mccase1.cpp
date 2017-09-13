/*Name:Navin Kumar Adhikari*/
/*Email:navinadhikari@nevada.unr.edu */
/*CS776 Assignment 0 case I(Boat Capacity 2)*/

#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;
//Number of possbile valid actions from left part of the river to the right part.
#define CCR 0 
#define MMR 1
#define CR  2
#define MR  3
#define MCR 4
#define NODE_LIMIT  51 //Total possible nodes with including nodes.
#define NUM_OF_MOVE 5

struct Node{
 int nodeNum;
 int mNum;
 int cNum;
 Node *next;
};  
/*
 A linked list fucntion that joins childs nodes to theier corresponding parent nodes.
*/
struct Node *addadjnode (Node *currentNode, int newNodeNum, int newcNum, int newmNum)
{
    Node *newNode = new Node();
    newNode->nodeNum = newNodeNum;
    newNode->mNum = newmNum;
    newNode->cNum = newcNum;
    newNode->next   = currentNode;
    return newNode;

}
/*
  This function checks if the Action is valid or not.   
*/
int IsValidMove(  int c, int m, int cOnboat, int mOnboat)
{
    int cL, mL, cR, mR;  
    cL = c - cOnboat;
    mL = m - mOnboat;
    cR = 3 - c + cOnboat;
    mR = 3 - m + mOnboat;
    
    if(((cL <= mL) || (cL == 0) || (mL == 0)) && ((cR <= mR) || (cR == 0) || (mR == 0)))
    {
        return (1);   
    }
    else
    {
        return (0);
    }
}
/*
  A function that returns node number
*/
int  assignnodenum (int c, int m)
{
    if((c == 3) && (m == 3)){
        return(50);
    }
    else if((c == 3) && (m == 2)){
        return(20); // 
    }
    else if((c == 3) && (m == 1)){
        return(18);
    }
    else if((c == 3) && (m == 0)){
        return(41);
    }
    else if((c == 2) && (m == 3)){
        return(36);
    }
    else if((c == 2) && (m == 2)){
        return(33);
    }
    else if((c == 2) && (m == 1)){
        return(42);
    }
    else if((c == 2) && (m == 0)){
        return(25);
    }
    else if((c == 1) && (m == 3)){
        return(30);
    }
    else if((c == 1) && (m == 2)){
        return(17);
    }
    else if((c == 1) && (m == 1)){
        return(10);
    }
    else if((c == 1) && (m == 0)){
        return(5);
    }
    else if((c == 0) && (m == 3)){
        return(7);
    }
    else if((c == 0) && (m == 2)){
        return(13);
    }
    else if((c == 0) && (m == 1)){
        return(16);
    }
    else if((c == 0) && (m == 0)){
        return(0);
    }
    else{
        return(255);
    }
}

/*
  This function takes the # cannibals (c) and mercenaries (m) along with the action.
  Based on the value of (c, m) and move next state ID is generated. 
*/
int GenState(int *c, int *m, int action)
{
    int can, mer;
    can = *c;
    mer = *m;
    switch(action){
        case 0: //CCR 
                if(IsValidMove(can, mer, 2, 0)){
                    can = *c - 2;
                    mer = *m;
                    *c = can;
                    *m = mer;
                    return(assignnodenum(can, mer));
                }
                else{
                    return (255);
                }  
                break;
        case 1: //MMR
                if(IsValidMove(can, mer, 0, 2)){
                    can = *c;
                    mer = *m - 2;
                    *c = can;
                    *m = mer;
                    return(assignnodenum(can, mer));
                }
                else{
                    return (255);
                }
                break;
        case 2: //CR
                if(IsValidMove(can, mer, 1, 0)){
                    can = *c - 1;
                    mer = *m;
                    *c = can;
                    *m = mer;
                    return(assignnodenum(can, mer));
                }
                else{
                    return (255);
                }
                break;
        case 3: //MR
                if(IsValidMove(can, mer, 0, 1)){
                    can = *c;
                    mer = *m - 1;
                    *c = can;
                    *m = mer;
                    return(assignnodenum(can, mer));
                }
                else{
                    return (255);
                }
                break;
        case 4: //MCR
                if(IsValidMove(can, mer, 1, 1)){
                    can = *c - 1;
                    mer = *m - 1;
                    *c = can;
                    *m = mer;
                    return(assignnodenum(can, mer));
                }
                else{
                    return (255);
                }
                break;
        default:
                return (255);
                break;
    }    
}

/*
  This function removes the repeated nodes in the currentPool
  to avoid the multiple execution of same node during the 
  state space generation algorithm.
  
*/
void FilterCurrentPool(int currentPool[])
{
    int i, j, k;
    //check for the repeated one in the currentPool
    for(j = 0; currentPool[j] != -1; j++)
    {
     for(i = j+1; currentPool[i] != -1; i++)       
     {
      if(currentPool[j] == currentPool[i])
      {
       for(k = j; k < NODE_LIMIT-1; k++)
       {
        currentPool[k] = currentPool[k+1];
       }
       currentPool[NODE_LIMIT-1] = -1;
      } 
     }
    }   
}

/*
  This function is used in state space (or graph) generation algorithm.
  This function checks if the nextPool of the graph nodes is empty or not.   
  If the nextPool is empty, then the state space generation is completed.
*/
int IsEmpty(int nextPool[])
{
 int i;
 for(i = 0; i < NODE_LIMIT; i++)
 {
  if(nextPool[i] > 0)
  {
   return (0);
  }
 }
 return (1);
}
void BreadthFirstSearch( Node * adjacencyList[],int parent[],int level[])
{
    Node * traverse;
    int i, par, lev, flag = 1;
    // 'lev' represents the level to be assigned
    // 'par' represents the parent to be assigned
    // 'flag' used to indicate if graph is exhausted
    lev = 0;
    level[NODE_LIMIT-1] = lev;
    // We start at startVertex
  
    while (flag) {
        flag = 0;
        for (i = 0; i < NODE_LIMIT; ++i) {
            if (level[i] == lev) {
                flag = 1;
                traverse = adjacencyList[i];
                par = i;
  
                while (traverse != NULL) {
                    if (level[traverse->nodeNum] != -1) {
                        traverse = traverse->next;
                        continue;
                    }
                    level[traverse->nodeNum] = lev + 1;
                    parent[traverse->nodeNum] = par;
                    traverse = traverse->next;				
                }
           }		
        }
        ++lev;	 
    }
}

int main(void)
{
    int  i  = 0, j  = 0,k  = 0, v1 = 0, v2 = 0,c=3,m=3,tempC=0,tempM=0;
    int  flag = 0,currentPool[NODE_LIMIT],nextPool[NODE_LIMIT],path[6];
    int  move[7] = {CCR, MMR, CR, MR, MCR}; 
    int cValue[NODE_LIMIT], mValue[NODE_LIMIT],ath[NODE_LIMIT];
    int p, levelCount,parent[NODE_LIMIT], level[NODE_LIMIT];
    Node *adjList[NODE_LIMIT];
    Node *traverse;
    //Initialization
    for(i = 0; i < NODE_LIMIT; i++){
        adjList[i]= NULL, currentPool[i] = -1;
        nextPool[i]= -1,parent[i]= 50,level[i]= -1;
    }
     //set up thethe first parent Node
     v1 = assignnodenum(c, m);
     for(i = 0; i < NUM_OF_MOVE; i++){
         tempC = c;
         tempM = m;
         v2 = GenState(&tempC, &tempM, move[i]);
         if(v2 != 0b11111111)
         {      
            adjList[v1] = addadjnode(adjList[v1], v2, tempC, tempM); 
         }
     } 
     currentPool[0] = v1;
     while(1)
     {
      k = 0;
      for(j = 0; currentPool[j] != -1; j++)
      {
       v1 = currentPool[j];
       traverse = adjList[v1];
       while(traverse != NULL)
       {
        v1 = traverse->nodeNum;     
         //check for whether the node is already build.
        for(i = 0; i < NODE_LIMIT; i++)
        {
         if((v1 == currentPool[i]) || (v1 == nextPool[i]))
         {
          flag = 1;
          break;
         }
         else
         {
          flag = 0;
         }
        }  
        if(flag == 1)
        {
         traverse = traverse->next;
         continue;
        }
        
        nextPool[k++] = v1;
        
        c = traverse->cNum;
        m = traverse->mNum;
        for(i = 0; i < NUM_OF_MOVE; i++)
         {
            tempC = c;
            tempM = m;
            v2 = GenState(&tempC, &tempM, move[i]);
            if(v2 != 0b11111111)
            { 
                adjList[v1] = addadjnode(adjList[v1], v2, tempC, tempM);
            }
        }
        traverse = traverse->next;
       } //while(traverse)   
      } //for(j)
      //is nextPool empty
      if(IsEmpty(nextPool))
      {
       break;
      }
      //copy nextPool into currentPool
      for(i = 0; i < NODE_LIMIT; i++ )
      {
       if(i<k)
       {
        currentPool[i] = nextPool[i];
        nextPool[i]    = -1;
       }
       else
       {
        currentPool[i] = -1;
        nextPool[i]    = -1;
       }
      }
      FilterCurrentPool(currentPool);
      
     } //while
     
     flag = 1;
     //Printing adjancency list
     for(i = 50; i >= 0; i--){
         traverse = adjList[i];
         if(traverse != NULL)
         {
             cout<<"Node"<<i<<"--->";            
         }
         flag = 0;
         while(traverse != NULL){
             cout<<"Node"<<"["<<traverse->nodeNum<<"]"<<"c="<<traverse->cNum<<","<<"m="<< traverse->mNum<<" ---> ";
             traverse = traverse->next;
             flag = 1;
         }
         if(flag == 1)
         {
             cout<<"NULL\n\n";
         }
     } 
    BreadthFirstSearch(adjList, parent, level);  
    levelCount = level[0];
    path[0] = 0;
    for(i = 1; i <= levelCount; i++)
    {
        path[i] = parent[path[i-1]];    
    }
    int cn[5],me[5];
    cout<<"\nThe States Forming Optimal Path in State Space Diagram  -\n";
    for (i = 0; i <= levelCount; i++) {
         switch(path[i])
         { 
         case 0:
                  cn[i]=0; 
                  me[i]=0;
                 
                  break;
         case 10:
                 cn[i]=1; 
                 me[i]=1;
                 break;
         case 15:
                 cn[i]=1;
                 me[i]=3;
                 break;
         case 50:
                 cn[i]=3;
                 me[i]=3;
                 break;
         }
        cout<<"stateID= "<<path[i]<<" and (c,m)= "<<cn[i]<<","<<me[i]<<"\t"; 
        
    }
       cout<<"\n\n";
       cout<<"\n~~~~~~~~~The optimal solution for missionary and cannibals problem is~~~~~~~~~\n";
       cout<<"\nState(c="<<cn[levelCount]<<","<<" m="<<me[levelCount]<<")";
       for (int k = levelCount; k > 0; k--) {
        c = abs(cn[k] - cn[k-1]);
        m = abs(me[k] - me[k-1]);
        cout<<"-->Action(c="<<c<<","<<"m="<<m<<")"<<"-->State(c="<<cn[k-1]<<","<<"m="<<me[k-1]<<")";    
    }    
    return 0;
 }
