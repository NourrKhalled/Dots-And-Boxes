////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void SetColor(int ForgC);


void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void reset_grid()
{

    memset(grid,' ', sizeof(grid));
    for(int i=0 ; i<ROW ; i++)
    {
        for(int j=0 ; j<COLM ; j++)
        {
            grid[i][j]==' ';

            if(j%4==0 && i%2==0)
            {
                grid[i][j]='*';
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void print_grid(int boxesarray[4][3])
{





    int belong=0;
    int r=0;
    printf("\n\t\t\t\t1111:Undo\t\t2222:Redo\n\t\t\t\t<--\t\t\t\t-->\n\t\t\t\t3333:Save Game\t\t4444:Exit To Main Menu\n");
    SetColor(3);
    printf("\t\t\t\tNumber of P1's Moves:%d " ,player1move);
    SetColor(5);
    printf("Number of P2's Moves:%d\n" ,player2move);
    SetColor(3);
    printf("\t\t\t\tP1's Score: %d" , playersarr[0].score);
    SetColor(5);
    printf("\t\tP2's Score: %d\n\n" , playersarr[1].score);
    SetColor(15);
    printf("\t\t\t\tSpaces Left:%d\n" , empty_spaces());
    printf("\t\t\t\t   1 2 3 4 5\n\n");
    for(int i=0 ; i<ROW ; i++)
    {
        if(i<5)printf("\t\t\t\t%d  " , i+1);

        for(int j=0 ; j<COLM ; j++)
        {


            belong=0;

                    for(int a=0 ; a<12 ; a++)  //column inputs
                        {
                            if(i==inputarr[0][a][0] && j==inputarr[0][a][1] && (i!=0 || j!=0))   //print in player one color
                            {
                                belong=1;
                                if(inputarr[0][a][0]==0 || inputarr[0][a][0]==2 || inputarr[0][a][0]==4)   //even row ---
                                {
                                    SetColor(3);        //Cyan
                                    for(int k=0 ; k<3 ; k++)   // loop for ---
                                    {

                                        printf("%c" , grid[i][j+k]);

                                    }
                                    j+=2;         //already printed
                                    SetColor(15);
                                    break;
                                }
                                else{                                            //odd row |
                                    SetColor(3);        //Cyan
                                    printf("%c" , grid[i][j]);
                                    SetColor(15);
                                }
                                //break;
                            }

                            else if(i==inputarr[1][a][0] && j==inputarr[1][a][1] && (i!=0 || j!=0))  //print in player two color
                            {
                                belong=1;
                                if(inputarr[1][a][0]==0 || inputarr[1][a][0]==2 || inputarr[1][a][0]==4)   //even row ---
                                {
                                    SetColor(5);        //Magenta
                                    for(int k=0 ; k<3 ; k++)    // loop for ---
                                    {

                                        printf("%c" , grid[i][j+k]);

                                    }
                                    SetColor(15);
                                    j+=2;          //already printed
                                    break;
                                }
                                else{                                            //odd row |
                                    SetColor(5);        //Magenta
                                    printf("%c" , grid[i][j]);
                                    SetColor(15);
                                }

                                break;
                            }

                        if(i==boxesarray[a][0] && j==boxesarray[a][1]+1 &&  a<4)
                        {

                            belong=1;
                            if(boxesarray[a][2]==1)
                            {
                                grid[i][j]='1';
                                SetColor(3);        //Cyan
                                printf("%c" , grid[i][j]);
                                SetColor(15);
                            }

                            else if(boxesarray[a][2]==2)
                            {
                                grid[i][j]='2';
                                SetColor(5);        //Magenta
                                printf("%c" , grid[i][j]);
                                SetColor(15);
                            }
                            else
                            {
                                grid[i][j]=' ';
                                printf("%c" , grid[i][j]);

                            }
                        }



                        }

                        if(belong==0)      // for dots and spaces
                        {
                            printf("%c" , grid[i][j]);
                        }
                        }

        printf("\n");
    }

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


