

/*Sudoku is a logic-based, combinatorial number-placement puzzle.
 In classic sudoku, the objective is to fill a 9×9 grid with digits
 so that each column, each row, and each of the nine 3×3 subgrids
 that compose the grid contain all of the digits from 1 to 9.
*/


#include<stdio.h>
//Defining a Global 2-Dimensional array as the sudoku puzzle grid
//This 2-D array has a global scope
int puzzGrid[9][9];
/*                ={{0,0,5,3,0,0,0,0,0},
                   {8,0,0,0,0,0,2,0,0},
                   {0,7,0,0,1,0,5,0,0},
                   {4,0,0,0,0,5,3,0,0},
                   {0,1,0,0,7,0,0,0,6},
                   {0,0,3,2,0,0,0,8,0},
                   {0,6,0,5,0,0,0,0,9},
                   {0,0,4,0,0,0,0,3,0},
                   {0,0,0,0,0,9,7,0,0}};
*/
//Function prototypes :
int presentInRow(int,int);
int presentInColumn(int,int);
int presentInGrid(int,int,int);
int checkSolved();
int solve();
int validEntry(int,int,int);
void print();
int findVacant();
void getDetails();
//File pointer to read/write in files: "problem","sudoku"(d:)
FILE *file;
int main()
{   //To get the details from user :
    getDetails();
    system("cls");
    print();

    if(solve())
    {   printf("\nSolved !! :\n");
        print();
        return 0;
    }
    printf("\n\nPuzzle can't be solved");
    file=fopen("d://sudoku.txt","a");
    fprintf(file,"Can't Solve the problem : INVALID \n\n");
    fclose(file);
    return 0;
}

int solve()
{   int location,column,row;
    //To check if the grid has been successfully completed with all numbers inserted
    //function call to checksolved which checks for any vacant spaces

    if(checkSolved())                       //1.
    {    return 1;
    }

    //returns 1 if the puzzle has been solved completely
    //If this condition fails, there are still empty regions in the
    //grid where numbers have to be entered.
    // To store the location of the box in the grid which does
    //not have any number in it by using function findVacant()
    location=findVacant();
    //now to store the column and row value of the particular box separately
    row=location/10;
    column=location%10;



    //For loop to check whether numbers from 1-9 can be entered in the particular box
    for(int i=1;i<=9;i++)
    {     //To check whether the present number i can be inserted in the box of given column and row
          if(validEntry(row,column,i))
          {   //if condition satisfied then enter the number i in that location
              puzzGrid[row][column]=i;

              //Recursion statement to check until last number entered
              //This statement will check for numbers to enter in the next vacant box recursively
              // The same function is repeatedly added to the ACTIVATION RECORD
              //When the grid has been completely solved the if condition (1.) will return 1(true)
              //and the current Activation record will repeatedly get removed from the stack
              if(solve())
              {   return 1;
              }
              //In any one of the recursive function calls, none of the numbers 1-9 lead to the solution then 0 is returned after current for loop
              // And in the previous function call the value i is incremented till 9
              //If even after 9 the puzzle isn't solved then the 0 is returned to the previous activation record and current activation record is removed
          }
          puzzGrid[row][column]=0;
    }
    //If for a certain box, none of the numbers 1-9 lead to the solution the 0 is returned after all 9 numbers have been entered and checked
    //0 is returned to the previous activation record and the current activation record is removed from the stack
    //Importantly this statement is reached only if execution through for loop is completed without returning 1
    return 0;
   }

//That is the end of the Solve function . In an ideal case a particular values will lead to solving the puzzle through recursive functions which all return 1


//To check whether all the boxes of the grid has been entered i.e whether the puzzle has been completely solved

int checkSolved()
{    //for loop to check row by row
     for(int row=0;row<9;row++)
     {   //for loop to check each column of particular row
         for(int column=0;column<9;column++)
         {
             //If no number has been entered at particular row and column,0(false) is returned
             if(puzzGrid[row][column]==0)
             {     return 0;
             }

         }
     }

     //If all the numbers have been entered then execution comes out of the for loops and 1(true) is returned
     return 1;
}




//This function is to return the location in the grid where there is no number entered.
//Using for loop each box in the grid is check for a value, if 0 then the location of the box is returned
int findVacant()
{   //For loop to check row by row
    for(int i=0;i<9;i++)
    {
        //For loop to check each column of particular row
        for(int j=0;j<9;j++)
        {     //if the number in the particular row and column is 0 then the row and column are returned
              if(puzzGrid[i][j]==0)
              {
                 return i*10+j;
              }

        }

    }
    //This function will be invoked only if the puzzle hasn't been solved, hence surely a value will be returned before end of for loops
}


//Function to check whether a given number can be entered in a particular row and column
//functions are invoked to check whether the given number is already present in the row,column and grid

int validEntry(int row,int column,int number)
{   //If not present in row,column and box then return 0
    if(!presentInRow(row,number) && !presentInColumn(column,number) && !presentInGrid(row-row%3,column-column%3,number))
    {
        return 1;
    }
    //Else if the number already exists in row,column or box then return 0
    //This indicates that the given number can't be entered in this row,column
    return 0;
}



//Function to check whether the given number already exists in the row
int presentInRow(int row,int number)
{     //To check each column from 1-9 of the given row
      for(int column=0;column<9;column++)
      {
          //If any column of the column conatains the number, then 1(true) is returned
          //This indicates that number already exists in row
          if(puzzGrid[row][column]==number)
          {   return 1;
          }
      }
      return 0;
      //the end of for loop is reached if the number isn't there in the entire row
      //0(false) is returned indicating number isn't present in row
}


//Function to check whether the given number already exists in the column
int presentInColumn(int column,int number)
{     //To check each row from 1-9 of the given column
      for(int row=0;row<9;row++)
      {
          //If any column of the row contains the number, then 1(true) is returned
          //This indicates that number already exists in column
          if(puzzGrid[row][column]==number)
          {   return 1;
          }
      }
      return 0;
      //the end of for loop is reached if the number isn't there in the entire column
      //0(false) is returned indicating number isn't present in column
}


//Function to check whether the given number already exists in the 3*3 grid
int presentInGrid(int row,int column,int number)
{     //Given the starting row/column values of 3*3 grid
      //To check each of the 3 rows of the 3*3 grid
      for(int r=0;r<3;r++)
      {
         //In a particular row to check all the 3 columns if number  already exists
         for(int c=0;c<3;c++)
            //If number exists at particular row column in 3*3 grid, then return 1(true)
            if(puzzGrid[row+r][column+c]==number)
            {   return 1;
            }
      }
      return 0;
      //the end of for loop is reached if the number isn't there in the entire 3*3 grid
}
//Function to print entire puzzle-grid to create a visual representation
 void print()
{     file=fopen("d://sudoku.txt","a");
      (checkSolved())?fprintf(file,"Solution :\n\n"):fprintf(file,"Problem :\n\n");

      for(int row=0;row<9;row++)
      {
           //ffile(&puzzGrid[row],4,36,f);
           for(int column=0;column<9;column++)
           {    if(!column)
                {   (puzzGrid[row][column]==0)?printf("|   "):printf("| %d ",puzzGrid[row][column]);
                    (puzzGrid[row][column]==0)?fprintf(file,"|   "):fprintf(file,"| %d ",puzzGrid[row][column]);;
                }else if(column==8)
                {
                    (puzzGrid[row][column]==0)?printf("  |"):printf(" %d |",puzzGrid[row][column]);
                    (puzzGrid[row][column]==0)?fprintf(file,"  |"):fprintf(file,"%d |",puzzGrid[row][column]);;
                }else
                {   (puzzGrid[row][column]==0)?printf("  "):printf(" %d",puzzGrid[row][column]);
                    (puzzGrid[row][column]==0)?fprintf(file,"  "):fprintf(file,"%d ",puzzGrid[row][column]);;

                }
               //fprintf(write,"%d ",puzzGrid[row][column]);
               printf(" ");
               if(column==2 || column==5)
               {    printf("| ");
                    fprintf(file,"| ");
               }


           }
           fprintf(file,"\n");
           printf("\n");
           if(row==2 || row==5)
           {   printf(" __ __ __  __ __ __  __ __ __\n\n");
               fprintf(file,"  _ _ _   _ _ _   _ _ _\n\n");
           }
      }

      fprintf(file,"\n\n");
      fclose(file);

 }



 //Function to get numbers form the user which already exist in the 9*9 grid
void getDetails()
{   //printf("Enter digits separated by blank space, enter 0 if no number exists \n");
    int choice,i,j;
    //To accept values row by row
    printf("Input data (1)manually or (2)from file : \n1.Manual\n2.From File - problem.txt\n");
    scanf("%d",&choice);
    if(choice==1){
        printf("Enter digits separated by blank space, enter 0 if no number exists \n");
        for(int row=0;row<9;row++)
        {   printf("Enter the 9 digits of row : %d \n",row+1);

            for(int column=0;column<9;column++)
            {    scanf(" %d",&puzzGrid[row][column]);
            }

        }
    }else
    {   //To get input from a file
        i=0,j=0;
        file=fopen("d://problem.txt","r");
        fseek(file,0,SEEK_SET);
        while(!feof(file))
        {   fscanf(file,"%d ",&puzzGrid[i][j]);
            j++;
            if(j>8)
            {   j=0;
                i++;
            }
        }

    }
}
/*
data in d://problem.txt
0 0 0 1 0 6 0 0 8
0 0 9 0 0 0 2 4 0
0 3 0 0 0 9 0 0 6
0 9 0 0 3 0 4 0 0
0 7 0 0 0 0 0 2 0
0 0 5 0 2 0 0 7 0
8 0 0 9 0 0 0 6 0
0 2 6 0 0 0 8 0 0
9 0 0 8 0 5 0 0 0
*/




