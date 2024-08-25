char gridEXP[11][21];
int inputEXP[2][50][2];
int boxesEXP[25][3]={{1,1,0},{1,5,0},{1,9,0},{1,13,0},{1,17,0},{3,1,0},{3,5,0},{3,9,0},{3,13,0},{3,17,0},{5,1,0},{5,5,0},{5,9,0},{5,13,0},{5,17,0},{7,1,0},{7,5,0},{7,9,0},{7,13,0},{7,17,0},{9,1,0},{9,5,0},{9,9,0},{9,13,0},{9,17,0}};
int redo_arrEXP[49][2];
///////////////////////////////////////////////////////////////////////////////////////////////
void input_reset_exp()
{
    player1move=player2move=0;
    for(int i=0 ; i<2 ; i++)
    {
        for(int j=0 ; j<50 ; j++)
            {
                for(int k=0 ; k<2 ; k++)
                    {
                        inputEXP[i][j][k]=0;
                    }
            }
    }


    for(int j=0 ; j<25; j++)
            {
                boxesEXP[j][2]=0;

            }



            playersarr[1].score=0;
            playersarr[0].score=0;

}
///////////////////////////////////////////////////////////////////////////////////////////////
void reset_grid_exp(){
    memset(gridEXP,' ', sizeof(gridEXP));
for(int i=0 ; i<11 ; i++)
    {
        for(int j=0 ; j<21 ; j++)
        {
            gridEXP[i][j]==' ';

            if(j%4==0 && i%2==0)
            {
                gridEXP[i][j]='*';
            }
        }
    }

}
////////////////////////////////////////////////////////////////////////////////////////////

void print_grid_exp(){


    int belong=0;
    printf("\n\t\t\t\t1111:Undo\t\t2222:Redo\n\t\t\t\t<--\t\t\t\t-->\n\t\t\t\t3333:Save Game\t\t4444:Exit To Main Menu\n");
    SetColor(3);
    printf("\t\t\t\tNumber of P1's Moves:%d\t\t" ,player1move);
    SetColor(5);
    printf("Number of P2's Moves:%d\n" ,player2move);
    SetColor(15);
    SetColor(3);
    printf("\t\t\t\tP1's Score: %d" , playersarr[0].score);
    SetColor(5);
    printf("\t\tP2's Score: %d\n\n" , playersarr[1].score);
    SetColor(15);
    printf("\t\t\t\tSpaces Left:%d\n" , empty_spaces_exp());
    printf("\t\t\t\t    1 2 3 4 5 6 7 8 9 1011\n\n");
    for(int i=0 ; i<11 ; i++)
    {
        if(i+1<10)printf("\t\t\t\t%d   " , i+1);
        else{printf("\t\t\t\t%d  " , i+1);}
         for(int j=0 ; j<21 ; j++)
        {
            belong=0;

                    for(int a=0 ; a<50 ; a++)  //column inputs
                        {
                            if(i==inputEXP[0][a][0] && j==inputEXP[0][a][1] && (i!=0 || j!=0))   //print in player one color
                            {
                                belong=1;
                                if(inputEXP[0][a][0]%2==0)   //even row ---
                                {
                                    SetColor(3);        //Cyan
                                    for(int k=0 ; k<3 ; k++)   // loop for ---
                                    {

                                        printf("%c" , gridEXP[i][j+k]);

                                    }
                                    j+=2;         //already printed
                                    SetColor(15);
                                    break;
                                }
                                else{                                            //odd row |
                                    SetColor(3);        //Cyan
                                    printf("%c" , gridEXP[i][j]);
                                    SetColor(15);
                                }
                                break;
                            }

                            else if(i==inputEXP[1][a][0] && j==inputEXP[1][a][1] && (i!=0 || j!=0))  //print in player two color
                            {
                                belong=1;
                                if(inputEXP[1][a][0]%2==0)   //even row ---
                                {
                                    SetColor(5);        //Magenta
                                    for(int k=0 ; k<3 ; k++)    // loop for ---
                                    {

                                        printf("%c" , gridEXP[i][j+k]);

                                    }
                                    SetColor(15);
                                    j+=2;          //already printed
                                    break;
                                }
                                else{                                            //odd row |
                                    SetColor(5);        //Magenta
                                    printf("%c" , gridEXP[i][j]);
                                    SetColor(15);
                                }

                                break;
                            }
                            if(i==boxesEXP[a][0] && j==boxesEXP[a][1]+1 &&  a<25 )
                        {

                            belong=1;
                            if(boxesEXP[a][2]==1)
                            {
                                gridEXP[i][j]='1';
                                SetColor(3);        //Cyan
                                printf("%c" , gridEXP[i][j]);
                                SetColor(15);
                            }

                            else if(boxesEXP[a][2]==2)
                            {
                                gridEXP[i][j]='2';
                                SetColor(5);        //Magenta
                                printf("%c" , gridEXP[i][j]);
                                SetColor(15);
                            }
                            else
                            {
                                gridEXP[i][j]=' ';
                                printf("%c" , gridEXP[i][j]);

                            }
                        }


                        }
                        if(belong==0)      // for dots
                        {
                            printf("%c" , gridEXP[i][j]);
                        }
        }
        printf("\n");
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int empty_spaces_exp()
{
    int emptyspaces=60;
    for(int i=0 ; i<11 ; i++)
    {
        for(int j=0 ; j<21 ; j++)
        {
            if(gridEXP[i][j]=='-')
            {
                emptyspaces--;
                j+=3;
            }
            else if (gridEXP[i][j]=='|' )
            {
                emptyspaces--;
            }
        }
    }
    return emptyspaces;
}
///////////////////////////////////////////////////////////////////////////////////////////////
void storeinputEXP(int playermove , int player , int r, int c )
{
    inputEXP[player][playermove][0]=r;
    inputEXP[player][playermove][1]=c;
    return ;
}
//////////////////////////////////////////////////////////////////////////////////////////////
int boxclosedEXP(int* closedbox , int* score , int player)   //checks when a box is closed or reopened
{
    int r=0 , c=0;
    for(int r=0 ; r<25 ; r++)  //loop for each box
    {
        if(boxesEXP[r][c+2]==0 && (gridEXP[boxesEXP[r][c]-1][boxesEXP[r][c+1]]=='-' && gridEXP[boxesEXP[r][c]+1][boxesEXP[r][c+1]]=='-') )
        {
            if((gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]-1]=='|' && gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]+3]=='|'))
            {
                *closedbox=1;
                if(player==0)boxesEXP[r][c+2]=1;
                else if(player==1)boxesEXP[r][c+2]=2;
                (*score)++;
            }
        }
        else if(boxesEXP[r][c+2]==1 || boxesEXP[r][c+2]==2 )
            {
                if(gridEXP[boxesEXP[r][c]-1][boxesEXP[r][c+1]]!='-' || gridEXP[boxesEXP[r][c]+1][boxesEXP[r][c+1]]!='-'  || gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]-1]!='|' || gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]+3]!='|')
                {
                    boxesEXP[r][c+2]=0;
                    (*score)--;
                }
            }
    }

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void player1_exp(){
    SetColor(3);
    printf("\t\t\t\t");
    printf("Player 1\n");
    SetColor(15);
    //closedbox=0;
    print_grid_exp();
    while(empty_spaces_exp())
    {

        printf("\t\t\t\tEnter A Valid Row(1-11)");
        scanf("%d" , &r1);


    if (r1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }

        while(r1%1111==0 && r1>=1111)
        {

            player1move=ingamemenuEXP(r1 , player1move , 0);                //undo or save or exit is done
            boxclosedEXP(&closedbox,&playersarr[0].score ,0);
            printf("\t\t\t\tEnter A Valid Row(1-11)");
            scanf("%d" , &r1);
            if (r1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }

        }
  if(r1<12 && r1>0)
    {

        ////////////////////////////////////////////////////////////


        if(r1%2!=0) //odd row ---
        {
        printf("\t\t\t\tEnter A Valid Column(Even Number)"  );
        scanf("%d" , &c1);

        while(c1%1111==0 && c1>=1111)
        {

            player1move=ingamemenuEXP(c1 , player1move , 0);
            boxclosedEXP(&closedbox,&playersarr[0].score, 0);
            scanf("%d" , &c1);

        if (c1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }

            //break;
        }

          if (c1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }


        player1move=ingamemenuEXP(c1 , player1move , 0);
        boxclosedEXP(&closedbox,&playersarr[0].score, 0);



        if(c1<=0 || c1>11 || c1%2!=0 && c1%1111!=0 )  //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player1_exp();
            break;
        }

        if(c1==2)c1=1;
        else if(c1==4)c1=5;
        else if(c1==6)c1=9;
        else if(c1==8)c1=13;
        else if(c1==10)c1=17;
        r1--;

         if(gridEXP[r1][c1]=='-') //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player1_exp();
            break;
        } else{    //the move
            round_moves++;

            for(int i=0 ; i<3 ; i++)
                {
                    gridEXP[r1][c1+i]='-';      //inerts the line

                }

        storeinputEXP(player1move++, 0 , r1 ,c1);  //input stored
        boxclosedEXP(&closedbox,&playersarr[0].score, 0);


            if(closedbox==1)
            {
            chainofboxesEXP(&playersarr[0].score , &player1move,0 , round_moves);
            closedbox=0;
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player1_exp();
            }
        break;               //end of turn####################################################
        }
        }

        ///////////////////////////////////////
         else if(r1%2==0) //even row |
        {
        printf("\t\t\t\tEnter A Valid Column(Odd Number)");
        scanf("%d" , &c1);
        while(c1%1111==0 && c1>=1111)
        {

            player1move=ingamemenuEXP(c1 , player1move , 0);
            boxclosedEXP(&closedbox,&playersarr[0].score, 0);
            printf("\t\t\t\tEnter A Valid Column(Odd Number)");
            scanf("%d" , &c1);
            if (c1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }
        }


        if (c1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }


        player1move=ingamemenuEXP(c1 , player1move , 0);
        boxclosedEXP(&closedbox,&playersarr[0].score, 0);





        if(c1<=0 || c1>11 || c1%2==0 && c1%1111!=0)   //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player1_exp();
            break;
        }


        if(c1==1)c1=0;                    //conversion
        else if(c1==3)c1=4;
        else if(c1==5)c1=8;
        else if(c1==7)c1=12;
        else if(c1==9)c1=16;
        else if(c1==11)c1=20;

        r1--;


        if(gridEXP[r1][c1]=='|')   //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player1_exp();
            break;
        } else{                              //the move
            round_moves++;
            gridEXP[r1][c1]='|';
            storeinputEXP(player1move++,0 , r1 ,c1);
            boxclosedEXP(&closedbox,&playersarr[0].score, 0);


            if(closedbox==1)
            {
            closedbox=0;
            chainofboxesEXP(&playersarr[players-2].score , &player1move,0 , round_moves);
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player1_exp();
            }
        break;              //end of turn####################################################
        }
    }
    }




    ////////////////////////////////////////////////////////////


    else  //invalid row
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player1_exp();
            break;
        }

    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void player2_exp()
{

    SetColor(5);
    printf("\t\t\t\t");
    printf("Player 2\n");
    SetColor(15);
    print_grid_exp();
    empty_spaces_exp();





    while(empty_spaces_exp())
    {
         printf("\t\t\t\tEnter A Valid Row(1-11)");
         scanf("%d" , &r2);


    if (r2 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }

        while(r2%1111==0 && r2>=1111)
        {
            player2move=ingamemenuEXP(r2 , player2move , 1);
            boxclosedEXP(&closedbox , &playersarr[1].score , 1);
            printf("\t\t\t\tEnter A Valid Row(1-11)");
            scanf("%d" , &r2);
            if (r2 < 1)
                {
                    char charoffbuff;
                    scanf("%c", &charoffbuff);  // takes a character off the buffer
                }
        }




    if(r2<12 && r2>0)
    {
        ////////////////////////////////////////////////////////////


        if(r2%2!=0) //odd row ---
        {
        printf("\t\t\t\tEnter A Valid Column(Even Number)");
        scanf("%d" , &c2);
        while(c2%1111==0 && c2>=1111)
        {
            player2move=ingamemenuEXP(c2 , player2move , 1);
            boxclosedEXP(&closedbox , &playersarr[1].score , 1);
            printf("\t\t\t\tEnter A Valid Column(Even Number)");
            scanf("%d" , &c2);
            if (c2 < 1)
                {
                    char charoffbuff;
                    scanf("%c", &charoffbuff);  // takes a character off the buffer
                }
        }


        if (c2 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }


        player2move=ingamemenuEXP(c2 , player2move , 1);
        boxclosedEXP(&closedbox , &playersarr[1].score , 1);




        if((c2<=0 || c2>11) || c2%2!=0 && c2%1111!=0)  //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player2_exp();
            break;
        }


        if(c2==2)c2=1;
        else if(c2==4)c2=5;
        else if(c2==6)c2=9;
        else if(c2==8)c2=13;
        else if(c2==10)c2=17;
        r2--;



        if(gridEXP[r2][c2]=='-') //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player2_exp();
            break;
        }



        else{    //the move
                round_moves++;

            for(int i=0 ; i<3 ; i++)
                {
                    gridEXP[r2][c2+i]='-';
                }


        storeinputEXP(player2move++,1, r2 ,c2);
        boxclosedEXP(&closedbox,&playersarr[1].score , 1);


            if(closedbox==1)
            {
            closedbox=0;
            chainofboxesEXP(&playersarr[1].score , &player2move,1 , round_moves);
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player2_exp();
            }

        break;                                     //end of turn####################################################
        }

        }

        ////////////////////////////////////////////////////////////


        else if(r2%2==0) //even row '|'
        {
        printf("\t\t\t\tEnter A Valid Column(Odd Number)");
        scanf("%d" , &c2);
        while(c2%1111==0 && c2>=1111)
        {
            player2move=ingamemenuEXP(c2 , player2move , 1);
            boxclosedEXP(&closedbox , &playersarr[1].score , 1);
            printf("\t\t\t\tEnter A Valid Column(Odd Number)");
            scanf("%d" , &c2);
            if (c2 < 1)
                {
                    char charoffbuff;
                    scanf("%c", &charoffbuff);  // takes a character off the buffer
                }
        }


        player2move=ingamemenuEXP(c2 , player2move , 1);
        boxclosedEXP(&closedbox,&playersarr[1].score , 1);




        if(c2<=0 || c2>11 || c2%2==0 && c2%1111!=0 )   //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player2_exp();
            break;
        }


         if(c2==1)c2=0;                    //conversion
        else if(c2==3)c2=4;
        else if(c2==5)c2=8;
        else if(c2==7)c2=12;
        else if(c2==9)c2=16;
        else if(c2==11)c2=20;

        r2--;



        if(gridEXP[r2][c2]=='|')   //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player2_exp();
            break;
        }



        else{    //the move
            gridEXP[r2][c2]='|';
            storeinputEXP(player2move++,1, r2 ,c2);
            boxclosedEXP(&closedbox,&playersarr[1].score , 1);
            round_moves++;

            if(closedbox==1)
            {
            closedbox=0;
            chainofboxesEXP(&playersarr[1].score ,&player2move,1 , round_moves);
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player2_exp();
            }
        break;                            //end of turn####################################################
        }


    }


    ////////////////////////////////////////////////////////////



    }




    else  //invalid row
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player2_exp();
            break;
        }


    }


}

void computerEXP()
{

    int ran_r,ran_c;
    empty_spaces_exp();



    while(empty_spaces_exp())
    {

        do
        {
            ran_r=rand();
            ran_r%=12;
        }while(ran_r<=0);


        if(ran_r%2!=0) //odd row ---
        {


        do
        {
            ran_c=rand()%11;

        }while(ran_c<=0  || ran_c%2!=0);  //checks invalid number


        if(ran_c==2)ran_c=1;
        else if(ran_c==4)ran_c=5;
        else if(ran_c==6)ran_c=9;
        else if(ran_c==8)ran_c=13;
        else if(ran_c==10)ran_c=17;
        ran_r--;


        if(gridEXP[ran_r][ran_c]=='-') //checks move validity
        {
            computerEXP();
            break;
        }
        else{    //the move
                for(int i=0 ; i<3 ; i++)
                {
                    gridEXP[ran_r][ran_c+i]='-';  //inserts the line
                }
        storeinputEXP(player2move++ , 1 , ran_r ,ran_c);  //input stored
        boxclosedEXP(&closedbox , &playersarr[1].score , 1);


        if(closedbox==1)
            {
            closedbox=0;
            chainofboxesEXP(&playersarr[1].score, &player2move , 1 ,round_moves);
            computerEXP();
            }
        break;                            //end of turn####################################################
        }


        }

        else if(ran_r%2==0 && ran_r!=0) //even row |
        {
       do{
         ran_c=rand()%12;
       }while(ran_c<=0 || ran_c%2==0);   //valid col


        if(ran_c==1)ran_c=0;

        else if(ran_c==3)ran_c=4;

        else if(ran_c==5)ran_c=8;
        else if(ran_c==7)ran_c=12;
        else if(ran_c==9)ran_c=16;
        else if(ran_c==11)ran_c=20;

        ran_r--;

        if(gridEXP[ran_r][ran_c]=='|')   //checks move validity
        {
            computerEXP();
            break;
        }

        else{    //the move
            round_moves++;
            gridEXP[ran_r][ran_c]='|';
            storeinputEXP(player2move++ , 1 , ran_r ,ran_c);  //input stored
            boxclosedEXP(&closedbox ,&playersarr[1].score , 1);
            round_moves++;

            if(closedbox==1)
            {
            closedbox=0;
            chainofboxesEXP(&playersarr[1].score, &player2move , 1 );
            computerEXP();
            }


        break;                            //end of turn####################################################
        }
    }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void EXP(){
    input_reset_exp();
    printf("Choose Mode:\n\t1:One Player\n\t2:Two Players\n");
    scanf("%d" , &no_of_players);
    if (no_of_players < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // eats a character off the buffer
            printf("Invalid Input");
            EXP();
        }
    if(no_of_players==2)
        {
            SetColor(3);
            printf("Enter Player One's Name:");fgets(playersarr[0].name ,30 , stdin);
            scanf("%s", playersarr[0].name);players++;
            SetColor(5);
            printf("\nEnter Player Two's Name:");fgets(playersarr[1].name ,30 , stdin);//players++;
            scanf("%s", playersarr[1].name);
            SetColor(15);
            HvsHEXP();
            savetop10();
        }
     if(no_of_players==1)
        {
            srand(time(NULL));
            SetColor(3);
            printf("\nEnter Player's Name:");fgets(playersarr[0].name ,30 , stdin);
            scanf("%s", playersarr[0].name);
            SetColor(15);
            HvsCEXP();
            savetop10();

        }

}


/////////////////////////////////////////////////////////////////////////////////////////



int chainofboxesEXP(int* score , int* playermove , int* player)
{
    int bordersarr[4]={0,0,0,0};         //each element represents a border for the box
    int noOfborders=0,r=0,c=0 , l=0 ;
        for(int i=0 ; i<25 ; i++)  //loop for each box
    {
;        for(int k=0 ; k<4 ;k++)
            {
                bordersarr[k]=0;
            }
            noOfborders=0;
        if(boxesEXP[r][c+2]==0)
        {
        if(gridEXP[boxesEXP[r][c]-1][boxesEXP[r][c+1]]=='-')
            {
                bordersarr[0]+=1;
            }
        if(gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]-1]=='|')
            {
                bordersarr[1]+=1;
            }
        if(gridEXP[boxesEXP[r][c]+1][boxesEXP[r][c+1]]=='-')
            {
                bordersarr[2]+=1;
            }
        if(gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]+3]=='|')
            {
                bordersarr[3]+=1;
            }
        for(int k=0 ; k<4 ;k++)
            {
                noOfborders+=bordersarr[k];
            }
        if(noOfborders==3 )
        {

            if(bordersarr[1]==0)
                {
                    gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]-1]='|';
                    storeinputEXP(*playermove , player ,boxesEXP[r][c] ,boxesEXP[r][c+1]-1 );
                }
            else if(bordersarr[3]==0)
                {
                    gridEXP[boxesEXP[r][c]][boxesEXP[r][c+1]+3]='|';
                    storeinputEXP(*playermove , player ,boxesEXP[r][c] ,boxesEXP[r][c+1]+3 );
                }
            else if(bordersarr[0]==0)
            {
                storeinputEXP(*playermove , player ,boxesEXP[r][c]-1 ,boxesEXP[r][c+1] );
                for(int j=0 ; j<3 ; j++)
            {
                gridEXP[boxesEXP[r][c]-1][boxesEXP[r][c+1]+j]='-';

            }


            }
            else if(bordersarr[2]==0)
              {
                storeinputEXP(*playermove , player ,boxesEXP[r][c]+1 ,boxesEXP[r][c+1] );
            {
                for(int j=0 ;j<3 ;j++)
                {
                    gridEXP[boxesEXP[r][c]+1][boxesEXP[r][c+1]+j]='-';
                }


            }
            }
            (*playermove)++;
            round_moves++;
            boxclosedEXP(&l,score , player);
            chainofboxesEXP(score ,playermove , player);
        }


    }
     r++;
    }
    return round_moves;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int undoEXP(int playermove , int player){
    int l=0;
    round_moves--;
    (playermove)--;
    redo_arrEXP[round_moves][0]=inputEXP[player][playermove][0];
    redo_arrEXP[round_moves][1]=inputEXP[player][playermove][1];
    inputEXP[player][playermove][0]=0;
    inputEXP[player][playermove][1]=0;
    if(redo_arrEXP[round_moves][0]%2==0)
    {
        for(int i=0 ; i<3 ; i++)
        {
            gridEXP[redo_arrEXP[round_moves][0]][redo_arrEXP[round_moves][1]+i]=' ';
        }
    }
    else{
        gridEXP[redo_arrEXP[round_moves][0]][redo_arrEXP[round_moves][1]]=' ';
    }
    boxclosedEXP(&l,&playersarr[player].score ,player);

print_grid_exp();
return round_moves;
}





int redoEXP(int* playermove , int player)
{
    int l=0;
    if(redo_arrEXP[round_moves][1]==0 && redo_arrEXP[round_moves][0]==0 )
    {
        printf("Can't redo!!");
        return round_moves;
    }

    inputEXP[player][*playermove][0]=redo_arrEXP[round_moves][0];
    inputEXP[player][*playermove][1]=redo_arrEXP[round_moves][1];
    if(redo_arrEXP[round_moves][0]%2==0)
    {
        for(int i=0 ; i<3 ; i++)
        {
            gridEXP[redo_arrEXP[round_moves][0]][redo_arrEXP[round_moves][1]+i]='-';
        }
    }
    else{
        gridEXP[redo_arrEXP[round_moves][0]][redo_arrEXP[round_moves][1]]='|';
    }
    redo_arrEXP[round_moves][0]=0;
    redo_arrEXP[round_moves][1]=0;
    boxclosedEXP(&l,&playersarr[player].score ,player);
(*playermove)++;
round_moves++;
print_grid_exp();
return round_moves;
}




void HvsHEXP()
{

            time_t *t0=time(NULL);
             while(empty_spaces_exp())
                {

                   round_moves=0;
                   for(int i=0 ; i<49 ; i++)
                   {
                        for(int j=0 ; j<2 ; j++)
                        {
                            redo_arrEXP[i][j]==0;
                        }
                    }
                    player1_exp();
                    timer(&t0);
                   round_moves=0;
                   for(int i=0 ; i<49 ; i++)
                {
                    for(int j=0 ; j<2 ; j++)
                    {

                            redo_arrEXP[i][j]==0;
                    }
                }
                    player2_exp();
                    timer(&t0);
                }
            SetColor(3);
            printf("\t\t\t\tP1's Score: %d" , playersarr[0].score);
            SetColor(5);
            printf("\t\tP2's Score: %d\n\n" , playersarr[1].score);
            SetColor(15);
            print_grid_exp();
            if(playersarr[1].score==playersarr[0].score){printf("\nIt's A TIE!!!!\n");}
            else if(playersarr[1].score>playersarr[0].score){SetColor(5);printf("\nPlayer TWO Have WON!!\n");SetColor(15);}
            else{SetColor(3);printf("\nPlayer ONE Have WON!!\n");SetColor(15);}

}


void HvsCEXP()
{
    time_t *t0=time(NULL);
            while(empty_spaces_exp())
                {
                    for(int i=0 ; i<49 ; i++)
                        {
                            for(int j=0 ; j<2 ; j++)
                            {
                                redo_arrEXP[i][j]==0;
                            }
                        }
                    round_moves=0;
                    player1_exp();
                    timer(&t0);
                    round_moves=0;
                    computerEXP();
                }
            SetColor(3);
            printf("\t\t\t\tP1's Score: %d" , playersarr[0].score);
            SetColor(5);
            printf("\t\tP2's Score: %d\n\n" , playersarr[1].score);
            SetColor(15);
            print_grid(boxesarray);
            if(playersarr[0].score==playersarr[1].score){printf("\nIt's A TIE!!!!\n");}
            else if(playersarr[0].score>playersarr[1].score){SetColor(3);printf("\nYou Have WON!!\n");SetColor(15);}
            else{SetColor(4);printf("\nYou Have LOST!!\n");SetColor(15);}

}
