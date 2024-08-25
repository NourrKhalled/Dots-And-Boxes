#define ROW 6
#define COLM 10

int player1move=0 , player1=0 , player2move=0 ,closedbox=0;
int boxesarray[4][3]={{1,1,0},{1,5,0},{3,1,0},{3,5,0}};  //index of each box | zero-->not closed | 1-->closed box by p1 | 2-->closed box by p2
int emptyspaces=24;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int r1 ,r2;int c1,c2; //players inputs
char grid[ROW][COLM];  //grid
int inputarr[2][12][2];
int round_moves;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



typedef struct{
    char name[30];
    int score;  //0 in case of losing //1 in case of winning
}playerinfo;

playerinfo playersarr[2];int players; //array to store players info and its counter

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



typedef struct{
    int row[12];
    int col[12];
    int color[12];
}progress;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void player_1()
{

    SetColor(3);
    printf("\t\t\t\t");
    printf("Player 1\n");
    SetColor(15);
    //closedbox=0;
    print_grid(boxesarray);
    emptyspaces=empty_spaces();



    while(emptyspaces=empty_spaces())
    {

        printf("\t\t\t\tEnter A Valid Row(1-5)");
        scanf("%d" , &r1);


    if (r1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }

        while(r1%1111==0 && r1>=1111)
        {

            player1move=ingamemenu(r1 , player1move , 0);
            boxclosed(&closedbox,&playersarr[0].score,0);
            printf("\t\t\t\t2)Enter A Valid Row(1-5)");
            scanf("%d" , &r1);
            if (r1 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }
        }





    if(r1<6 && r1>0  )
    {

        ////////////////////////////////////////////////////////////

        if(r1%2!=0) //odd row ---
        {
        printf("\t\t\t\tEnter A Valid Column(Even Number)"  );
        scanf("%d" , &c1);

        while(c1%1111==0 && c1>=1111)
        {

            player1move=ingamemenu(c1 , player1move , 0);
            boxclosed(&closedbox,&playersarr[0].score,0);
            printf("\t\t\t\t2)Enter A Valid Column(Even Number)");
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


        player1move=ingamemenu(c1 , player1move , 0);
        boxclosed(&closedbox,&playersarr[0].score,0);





        if(c1<=0 || c1>5 || c1%2!=0 && c1%1111!=0 )  //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player_1();
            break;
        }


        if(c1==2)c1--;


        else if(c1==4)c1=5;


        r1--;


        if(grid[r1][c1]=='-') //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player_1();
            break;
        }
        else{    //the move
            round_moves++;

            for(int i=0 ; i<3 ; i++)
                {
                    grid[r1][c1+i]='-';      //inerts the line

                }

        storeinput(player1move++, 0 , r1 ,c1);  //input stored

        //
        boxclosed(&closedbox,&playersarr[0].score,0);


            if(closedbox==1)
            {
            chainofboxes(&playersarr[0].score , &player1move,0 );
            closedbox=0;
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player_1();
            }
        return player1move;               //end of turn####################################################
        }


        }

        ////////////////////////////////////////////////////////////


        else if(r1%2==0) //even row |
        {
        printf("\t\t\t\tEnter A Valid Column(Odd Number)");
        scanf("%d" , &c1);
        while(c1%1111==0 && c1>=1111)
        {

            player1move=ingamemenu(c1 , player1move , 0);
            boxclosed(&closedbox,&playersarr[0].score , 0);
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


        player1move=ingamemenu(c1 , player1move , 0);
        boxclosed(&closedbox,&playersarr[0].score,0);





        if(c1<=0 || c1>8 || c1%2==0 && c1%1111!=0)   //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player_1();
            break;
        }


        if(c1==1)c1=0;


        else if(c1==3)c1=4;


        else if(c1==5)c1=8;


        r1--;


        if(grid[r1][c1]=='|')   //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player_1();
            break;
        }

        else{    //the move
            round_moves++;
            grid[r1][c1]='|';
            storeinput(player1move++,0 , r1 ,c1);

            boxclosed(&closedbox,&playersarr[0].score , 0);

            if(closedbox==1)
            {
            closedbox=0;
            chainofboxes(&playersarr[0].score , &player1move,0 );
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player_1();
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
            player_1();
            break;
        }


    }


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void player_2()
{

    SetColor(5);
    printf("\t\t\t\t");
    printf("Player 2\n");
    SetColor(15);
    print_grid(boxesarray);
    emptyspaces=empty_spaces();





    while(emptyspaces=empty_spaces())
    {
         printf("\t\t\t\tEnter A Valid Row(1-5)");
         scanf("%d" , &r2);


    if (r2 < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // takes a character off the buffer
        }

        while(r2%1111==0 && r2>=1111)
        {
            player2move=ingamemenu(r2 , player2move , 1);
            boxclosed(&closedbox , &playersarr[1].score , 1);
            printf("\t\t\t\tEnter A Valid Row(1-5)");
            scanf("%d" , &r2);
            if (r2 < 1)
                {
                    char charoffbuff;
                    scanf("%c", &charoffbuff);  // takes a character off the buffer
                }
        }




    if(r2<6 && r2>0)
    {
        ////////////////////////////////////////////////////////////


        if(r2%2!=0) //odd row ---
        {
        printf("\t\t\t\tEnter A Valid Column(Even Number)");
        scanf("%d" , &c2);
        while(c2%1111==0 && c2>=1111)
        {
            player2move=ingamemenu(c2 , player2move , 1);
            boxclosed(&closedbox , &playersarr[1].score , 1);
            printf("\t\t\t\tEnter A Valid Column(Even Number)");
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


        player2move=ingamemenu(c2 , player2move , 1);
        boxclosed(&closedbox , &playersarr[1].score , 1);




        if((c2<=0 || c2>5) || c2%2!=0 && c2%1111!=0)  //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player_2();
            break;
        }


        if(c2==2)c2=1;


        else if(c2==4)c2=5;


        r2--;


        if(grid[r2][c2]=='-') //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player_2();
            break;
        }

        else{    //the move
                round_moves++;

            for(int i=0 ; i<3 ; i++)
                {
                    grid[r2][c2+i]='-';
                }


        storeinput(player2move++,1, r2 ,c2);;
        boxclosed(&closedbox,&playersarr[1].score , 1);


            if(closedbox==1)
            {
            closedbox=0;
            chainofboxes(&playersarr[1].score , &player2move,1 );
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player_2();
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
            player2move=ingamemenu(c2 , player2move , 1);
            boxclosed(&closedbox , &playersarr[1].score , 1);
            printf("\t\t\t\tEnter A Valid Column(Odd Number)");
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


        player2move=ingamemenu(c2 , player2move , 1);
        boxclosed(&closedbox,&playersarr[1].score , 1);




        if(c2<=0 || c2>8 || c2%2==0 && c2%1111!=0 )   //invalid move
        {
            SetColor(4);
            printf("\t\t\t\tEnter A Valid Number!\n");
            SetColor(15);
            player_2();
            break;
        }


        if(c2==1)c2=0;


        else if(c2==3)c2=4;


        else if(c2==5)c2=8;


        r2--;


        if(grid[r2][c2]=='|')   //checks move validity
        {
            SetColor(4);
            printf("\t\t\t\tInvalid Move!!\n");
            SetColor(15);
            player_2();
            break;
        }

        else{    //the move
            grid[r2][c2]='|';
            storeinput(player2move++,1, r2 ,c2);
            boxclosed(&closedbox,&playersarr[1].score , 1);
            round_moves++;

            if(closedbox==1)
            {
            closedbox=0;
            chainofboxes(&playersarr[1].score ,&player2move,1 );
            SetColor(10);
            printf("\n\t\t\t\tNice!Play Again\n");
            SetColor(15);
            player_2();
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
            player_2();
            break;
        }


    }


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int empty_spaces()
{
    emptyspaces=12;
    if(emptyspaces!=0)
    {for(int i=0 ; i<ROW ; i++)
    {
        for(int j=0 ; j<COLM ; j++)
        {
            if(grid[i][j]=='-')
            {
                emptyspaces--;
                j+=3;
            }
            else if (grid[i][j]=='|' )
            {
                emptyspaces--;
            }

        }
    }}
    return emptyspaces;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

