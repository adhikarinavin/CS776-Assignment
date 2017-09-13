/*Name:Navin Kumar Adhikari*/
/*Email:navinadhikari@nevada.unr.edu */
/*CS776 Assignment 1 My eval */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
//declaration of eval function
double eval(int *vec)
{ 
    int i,flag=0;
    double returnValue;
	for (i = 5; i < 100; i++)
	{
		if (vec[i] == 0)
		{
			flag = 1;
		}
		else
		{
			flag = 0;
			goto stage;
		}
        }
            if(flag==1)
            {  
            if (vec[0] == 1 && vec[1] == 0 && vec[2] == 0 &&vec[3] == 0 && vec[4] == 0)
	      {
		returnValue = 55;
	      }
	     else if (vec[0] == 0 && vec[1] == 1 && vec[2] == 0 &&vec[3] == 0 &&vec[4] == 0 )
              {
	         returnValue = 50;
	      }
	     else if (vec[0] == 0 && vec[1] == 0 && vec[2] == 1&&vec[3] == 0 && vec[4] == 0)
	     {
	         returnValue = 90;
	     }
             else
              {
                 goto stage;
              } 
           }

           if (flag==0)
	    {
	      stage: returnValue = 10;
            }
	   
    }

// A function that copies the values of array1 into array2.
void copyvector(int arr1[], int arr2[])
{
    for(int i = 0; i < 100; i++)
    {
        arr2[i] = arr1[i];
    }
}
//A function initilizes the start point for hill climbing.
void candidatesol( int arr[],int size)
{ 

    int randnum;
    for(int i = 0; i < size; i++)
    {
      arr[i] = 0;
    }
}
// A function that randomizes bit of candidate soution to find the next-
//candidate solution.
void nextcanditatesol( int arr[], int size)
{
   for( int i=0;i<1;i++)
   {
       int k1=rand()%100;
       int k2=rand()%100;
       arr[k1]=arr[k1]^1;
       arr[k2]=arr[k2]^1;
       
   }
}
//Main
int main()
{ 
  double maxitr=10000;
  const int bitsize=100;
  int vec1[bitsize];
  int vec2[bitsize];
  double fitness=0.0, bestfitness=0.0;
  candidatesol(vec1,bitsize);
  candidatesol(vec2,bitsize);
  fitness = eval(vec1);
  bestfitness=fitness;
  for (int i=0;i<maxitr;i++)
  {
   nextcanditatesol(vec1,bitsize);
   fitness = eval(vec1);
   if(fitness>bestfitness)
   {
    bestfitness=fitness;
    copyvector(vec1,vec2);//copies the max value point so far.
    cout << "Fitness Value = " << bestfitness << endl;
   }
  else
   { 

    copyvector(vec2,vec1);//Retrun to previous max value point to find new random start point-
                          //if the value halts to certain point making local maxima.
   }
 }
 cout<<" The maxmium Fitness Value is:"<<bestfitness<<" at the the point v1= ";
  for (int k=0;k<bitsize;k++)
 { 
    cout<<vec1[k];
 }
 cout<<endl;
}

