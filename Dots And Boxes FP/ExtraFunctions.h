
int no_of_players=0;
time_t t1;
int inputEXP[2][50][2];
int boxesEXP[25][3];
char gridEXP[11][21];
playerinfo top[10];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct{
    int r;
    int c;
}moveinfo;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void boxclosed(int* closedbox , int* score , int player )   //checks when a box is closed or reopened
{
    int r=0 , c=0;
    for(r=0 ; r<4 ; r++)

        {if(boxesarray[r][c+2]==0 && (grid[boxesarray[r][c]-1][boxesarray[r][c+1]]=='-' && grid[boxesarray[r][c]+1][boxesarray[r][c+1]]=='-') )
        {
            if((grid[boxesarray[r][c]][boxesarray[r][c+1]-1]=='|' && grid[boxesarray[r][c]][boxesarray[r][c+1]+3]=='|'))
            {
                *closedbox=1;
                if(player==0)boxesarray[r][c+2]=1;
                else if(player==1)boxesarray[r][c+2]=2;
                (*score)++;
            }
        }
        else if(boxesarray[r][c+2]==1 ||  boxesarray[r][c+2]==2)
            {
                if(grid[boxesarray[r][c]-1][boxesarray[r][c+1]]!='-' || grid[boxesarray[r][c]+1][boxesarray[r][c+1]]!='-'  || grid[boxesarray[r][c]][boxesarray[r][c+1]-1]!='|' || grid[boxesarray[r][c]][boxesarray[r][c+1]+3]!='|')
                {
                    boxesarray[r][c+2]=0;
                    (*score)--;
                }
            }
        }



    return (*closedbox);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void inputreset()
{
    player1move=player2move=0;
    for(int i=0 ; i<2 ; i++)
    {
        for(int j=0 ; j<12 ; j++)
            {
                for(int k=0 ; k<2 ; k++)
                    {
                        inputarr[i][j][k]=0;
                    }
            }
    }


    for(int j=0 ; j<4; j++)
            {
                boxesarray[j][2]=0;

            }

            playersarr[1].score=0;
            playersarr[0].score=0;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void storeinput(int playermove , int player , int r, int c )
{
    inputarr[player][playermove][0]=r;
    inputarr[player][playermove][1]=c;
    return ;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BEG()
{
    inputreset();
    printf("Choose Mode:\n\t1:One Player\n\t2:Two Players\n");
    scanf("%d" , &no_of_players);
    if (no_of_players < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // eats a character off the buffer
            printf("Invalid Input");
            BEG();
        }

        if(no_of_players==2)
        {
            SetColor(3);
            printf("Enter Player One's Name:");fgets(playersarr[0].name ,30 , stdin);
            scanf("%s", playersarr[0].name);
            SetColor(5);
            printf("\nEnter Player Two's Name:");fgets(playersarr[1].name ,30 , stdin);
            scanf("%s", playersarr[1].name);
            SetColor(15);
            HvsH();
            savetop10();
        }
        if(no_of_players==1)
        {
            srand(time(NULL));
            SetColor(3);
            printf("\nEnter Player's Name:");fgets(playersarr[0].name ,30 , stdin);
            scanf("%s", playersarr[0].name);
            SetColor(15);
            HvsC();
            savetop10();

        }


}

void timer(time_t* t0)
{
    int mint,sec;
    t1=time(NULL)-*t0;
    mint=t1/60;
    sec=t1%60;
    printf("time:\n%d : %d\n",mint,sec);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int chainofboxes(int* score , int* playermove , int* player)
{
    int bordersarr[4];         //each element represents a border for the box
    int noOfborders=0,r=0,c=0 , l=0 ;
        for(int i=0 ; i<4 ; i++)  //loop for each box
    {
        for(int k=0 ; k<4 ;k++)
            {
                bordersarr[k]=0;
            }
            noOfborders=0;
        if(boxesarray[r][c+2]==0)
    {

        if(grid[boxesarray[r][c]-1][boxesarray[r][c+1]]=='-')
            {
                bordersarr[0]+=1;
            }
        if(grid[boxesarray[r][c]][boxesarray[r][c+1]-1]=='|')
            {
                bordersarr[1]+=1;
            }
        if(grid[boxesarray[r][c]+1][boxesarray[r][c+1]]=='-')
            {
                bordersarr[2]+=1;
            }
        if(grid[boxesarray[r][c]][boxesarray[r][c+1]+3]=='|')
            {
                bordersarr[3]+=1;
            }
        for(int k=0 ; k<4 ;k++)
            {
                noOfborders+=bordersarr[k];
            }
        if(noOfborders%3==0 && noOfborders!=0 )
        {

            if(bordersarr[1]==0)
                {
                    grid[boxesarray[r][c]][boxesarray[r][c+1]-1]='|';
                    storeinput(*playermove , player ,boxesarray[r][c] ,boxesarray[r][c+1]-1 );
                }
            else if(bordersarr[3]==0)
                {
                    grid[boxesarray[r][c]][boxesarray[r][c+1]+3]='|';
                    storeinput(*playermove , player ,boxesarray[r][c] ,boxesarray[r][c+1]+3 );
                }
            else if(bordersarr[0]==0)
            {
                storeinput(*playermove , player ,boxesarray[r][c]-1 ,boxesarray[r][c+1] );
                for(int j=0 ; j<3 ; j++)
            {
                grid[boxesarray[r][c]-1][boxesarray[r][c+1]+j]='-';

            }


            }
            else if(bordersarr[2]==0)
              {
                storeinput(*playermove , player ,boxesarray[r][c]+1 ,boxesarray[r][c+1] );
            {
                for(int j=0 ;j<3 ;j++)
                {
                grid[boxesarray[r][c]+1][boxesarray[r][c+1]+j]='-';
                }

            }
            }
            (*playermove)++;
            round_moves++;
            boxclosed(&l,score , player);
        }


    }
     r++;
    }
    return round_moves;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void saveGame(int flag){
     int i;
     FILE* fp;                              //3 files to save 3 games
      if (flag==1){                         // use some features from GITHUP
        fp = fopen("game1.txt","w");
    }
    else if (flag==2){
        fp = fopen("game2.txt","w");
    }
    else if (flag==3){
        fp = fopen("game3.txt","w");
    }

      if (fp == NULL) {
         printf("Error\n");
         exit(1);
      }

    else{
/* ################ DIFFICULTY #################### */
        fprintf(fp,"%d\n",mode);






        if(mode==1)           //to save expert mode
        {
            /* ################ MODE #################### */
        fprintf(fp,"%d\n",no_of_players);
        /* ################ PLAYER INFO ################## */
        for(i=0;i<2;i++){
                int j=0;
                for(j=0 ; j<30 ; j++)
                {
                    fprintf(fp,"%c",playersarr[i].name[j]);
                }
           fprintf(fp,"%d\n",playersarr[i].score);
           }
/* ############### INPUT INFO ################## */
        for(int i=0 ; i<2 ; i++)
    {
        for(int j=0 ; j<50 ; j++)
            {
                for(int k=0 ; k<2 ; k++)
                    {
                        fprintf(fp,"%d\n" , inputEXP[i][j][k]);
                    }
            }
    }
/* ############### BOXES ARRAY ####################### */
        for(int j=0 ; j<25 ; j++)
            {
                for(int k=0 ; k<3 ; k++)
                    {
                        fprintf(fp,"%d\n" , boxesEXP[j][k]);
                    }
            }
/* ############### GRID ####################### */
    for(int i=0 ; i<11 ; i++)
    {
        for(int j=0 ; j<21; j++)
        {
            fprintf(fp,"%c" , gridEXP[i][j]);
        }
    }
/* ############### TIME ####################### */
        //fprintf(fp,"%d",t1);

    fprintf(fp,"%d\n" , player1move);
    fprintf(fp,"%d\n" , player2move);
    }



/////////////////////////////////////////////////////////////////////////////////////////////////


    else if(mode==2)   //to save beginner mode
    {
/* ################ MODE #################### */
        fprintf(fp,"%d\n",no_of_players);
/* ################ PLAYER INFO ################## */
        for(i=0;i<2;i++){
                int j=0;
           for(j=0 ; j<30 ; j++)
                {
                    fprintf(fp,"%c",playersarr[i].name[j]);
                }
           fprintf(fp,"%d\n",playersarr[i].score);
           }
/* ############### INPUT INFO ################## */
        for(int i=0 ; i<2 ; i++)
            {
        for(int j=0 ; j<12 ; j++)
            {
                for(int k=0 ; k<2 ; k++)
                    {
                        fprintf(fp,"%d\n" , inputarr[i][j][k]);
                    }
            }
    }
/* ############### BOXES ARRAY ####################### */
        for(int j=0 ; j<4 ; j++)
            {
                for(int k=0 ; k<3 ; k++)
                    {
                        fprintf(fp,"%d\n" , boxesarray[j][k]);
                    }
            }
/* ############### GRID ####################### */
    for(int i=0 ; i<ROW ; i++)
    {
        for(int j=0 ; j<COLM ; j++)
        {
            fprintf(fp,"%c" , grid[i][j]);
        }
    }

/* ############### TIME ####################### */
        //fprintf(fp,"%d",t1);

    fprintf(fp,"%d\n" , player1move);
    fprintf(fp,"%d\n" , player2move);
    }



        }
fclose(fp);
printf("\nSaved Successfully!:D\n");
for(int i=0 ; i<4 ; i++)
    {
        for(int j=0 ; j<3 ; j++)
        {
            printf("%d" , boxesarray[i][j]);
        }
        printf("\n");
    }

for(int i=0 ; i<2 ; i++)
            {
        for(int j=0 ; j<12 ; j++)
            {
                for(int k=0 ; k<2 ; k++)
                    {
                        printf("%d" , inputarr[i][j][k]);
                    }printf("\t");
            }printf("\n");
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loadGame (int flag){
     int i;
     FILE* fp;                                //3 files to load 3 games
     if (flag==1){                           // use some features from GITHUP
        fp = fopen("game1.txt","r");
    }
    else if (flag==2){
        fp = fopen("game2.txt","r");
    }
    else if (flag==3){
        fp = fopen("game3.txt","r");
    }

    if (fp == NULL) {
         printf("Error\n");
         exit(1);
      }


    else{
/* ################ DIFFICULTY #################### */
        fscanf(fp,"%d\n",&mode);



////////////////////////////////////////////////////////////////////////////////////////////


    if(mode==1)              //to load expert mode
    {
        /* ################ MODE #################### */
        fscanf(fp,"%d\n",&no_of_players);
/* ################ PLAYER INFO ################## */
        for(i=0;i<2;i++){
                int j=0;
                for(j=0 ; j<30 ; j++)
                {
                    fscanf(fp,"%c",&playersarr[i].name[j]);
                }
           fscanf(fp,"%d\n",&playersarr[i].score);
           }
/* ############### GRID INFO ################## */
       for(int i=0 ; i<2 ; i++)
       {
        for(int j=0 ; j<50 ; j++)
            {
                for(int k=0 ; k<2 ; k++)
                    {
                        fscanf(fp,"%d\n" ,&inputEXP[i][j][k]);
                    }
            }
       }
/* ############### BOXES ARRAY ####################### */
        for(int j=0 ; j<25 ; j++)
            {
                for(int k=0 ; k<3 ; k++)
                    {
                        fscanf(fp,"%d\n" , &boxesEXP[j][k]);
                    }
            }
/* ############### GRID ####################### */
    for(int i=0 ; i<11 ; i++)
    {
        for(int j=0 ; j<21 ; j++)
        {
            fscanf(fp,"%c" , &gridEXP[i][j]);
        }
    }
/* ############### TIME ####################### */
        //fscanf(fp,"%d",&time);

    fscanf(fp,"%d\n" , &player1move);
    fscanf(fp,"%d\n" , &player2move);
    if(no_of_players==2)HvsHEXP();
    else{HvsCEXP();}
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    else if(mode==2)         //to load beginners mode
    {
/* ################ MODE #################### */
        fscanf(fp,"%d\n",&no_of_players);
/* ################ PLAYER INFO ################## */
        for(i=0;i<2;i++){
                int j=0;
           for(j=0 ; j<30 ; j++)
                {
                    fscanf(fp,"%c",&playersarr[i].name[j]);
                }
                j=0;
           fscanf(fp,"%d\n",&playersarr[i].score);
           }
/* ############### INPUT INFO ################## */
        for(int i=0 ; i<2 ; i++)
            {
        for(int j=0 ; j<12 ; j++)
            {
                for(int k=0 ; k<2 ; k++)
                    {
                        fscanf(fp,"%d\n" ,&inputarr[i][j][k]);
                    }
            }
    }
/* ############### BOXES ARRAY ####################### */
        for(int j=0 ; j<4 ; j++)
            {
                for(int k=0 ; k<3 ; k++)
                    {
                        fscanf(fp,"%d\n" , &boxesarray[j][k]);
                    }
            }
/* ############### GRID ####################### */
    for(int i=0 ; i<6 ; i++)
    {
        for(int j=0 ; j<10 ; j++)
        {
            fscanf(fp,"%c" , &grid[i][j]);
        }
    }

/* ############### TIME ####################### */
        //fprintf(fp,"%d",t1);

    fscanf(fp,"%d\n" , &player1move);
    fscanf(fp,"%d\n" , &player2move);
    }

    if(no_of_players==2)HvsH();
    else{HvsC();}
    }
    fclose(fp);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int redo_arr[6][2];

int undo(int playermove , int player){
    int l=0;
    round_moves--;
    (playermove)--;
    redo_arr[round_moves][0]=inputarr[player][playermove][0];
    redo_arr[round_moves][1]=inputarr[player][playermove][1];
    inputarr[player][playermove][0]=0;
    inputarr[player][playermove][1]=0;
    if(redo_arr[round_moves][0]%2==0)
    {
        for(int i=0 ; i<3 ; i++)
        {
            grid[redo_arr[round_moves][0]][redo_arr[round_moves][1]+i]=' ';
        }
    }
    else{
        grid[redo_arr[round_moves][0]][redo_arr[round_moves][1]]=' ';
    }
 boxclosed(&l , &playersarr[player].score ,player );


print_grid(boxesarray);
return round_moves;
}



int redo(int* playermove , int player)
{
    int l;
    if(redo_arr[round_moves][1]==0 && redo_arr[round_moves][0]==0 )
    {
        printf("Can't redo!!");
        return round_moves;
    }


    inputarr[player][*playermove][0]=redo_arr[round_moves][0];
    inputarr[player][*playermove][1]=redo_arr[round_moves][1];
    if(redo_arr[round_moves][0]%2==0)
    {
        for(int i=0 ; i<3 ; i++)
        {
            grid[redo_arr[round_moves][0]][redo_arr[round_moves][1]+i]='-';
        }
    }
    else{
        grid[redo_arr[round_moves][0]][redo_arr[round_moves][1]]='|';
    }
     boxclosed(&l , &playersarr[player].score ,player );
    redo_arr[round_moves][0]=0;
    redo_arr[round_moves][1]=0;
(*playermove)++;
round_moves++;
print_grid(boxesarray);
return round_moves;
}

void HvsH()
{
                time_t *t0=time(NULL);
                if(player2move<player1move)
                {
                    while(emptyspaces=empty_spaces())
                {
                    round_moves=0;
                    player_2();
                    timer(&t0);
                    round_moves=0;
                    player_1();
                    timer(&t0);
                }
                }

                else{
                    while(emptyspaces=empty_spaces())
                {
                    SetColor(3);
                    round_moves=0;
                    player_1();
                    timer(&t0);
                    round_moves=0;
                    player_2();
                    timer(&t0);
                }
                }

            SetColor(3);
            printf("\t\t\t\tP1's Score: %d" , playersarr[0].score);
            SetColor(5);
            printf("\t\tP2's Score: %d\n\n" , playersarr[1].score);
            SetColor(15);
            print_grid(boxesarray);
            if(playersarr[1].score==playersarr[0].score){printf("\nIt's A TIE!!!!\n");}
            else if(playersarr[1].score>playersarr[0].score){SetColor(5);printf("\nPlayer TWO Have WON!!\n");SetColor(15);}
            else{SetColor(3);printf("\nPlayer ONE Have WON!!\n");SetColor(15);}

}

void HvsC()
{
    time_t *t0=time(NULL);
            while(emptyspaces=empty_spaces())
                {
                    round_moves=0;
                    player_1();
                    timer(&t0);
                    round_moves=0;
                    computer();
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

void top10(playerinfo arr[], int n)
{
void swapp(playerinfo *x, playerinfo *y)
{
    playerinfo temp = *x;
    *x = *y;
    *y = temp;
}
    int i, j;
    int swapped;           //use bubble sort because we have small data
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].score < arr[j + 1].score) {
                swapp(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
    if(n<=10){
    for(i=0;i<n;i++){
        int k=0;
           printf("%d)" , i+1);
            for(k=0;k<30;k++)
            {
                if(playersarr[i].name[j]==' '){break;}
                printf("%c",arr[i].name[k]);
            }
        printf("\tscore: %d\n",arr[i].score);
        printf("\n");
    }
    }else{
       for(i=0;i<10;i++){
           int k=0;
           printf("%d)" , i+1);
            for(k=0;k<30;k++)
            {
                printf("%c",arr[i].name[k]);

            }
                printf("\tscore: %d\n",arr[i].score);
            }
       printf("\n");
    }
}


void savetop10()
{
    loadtop10();
    for(int j=0;j<10;j++)
        {
            for(int k=0;k<2;k++)
                {
                    int f=1;
                    for(int i=0;i<30;i++)
                    {
                    if(playersarr[k].name[i]!=top[j].name[i])
                    {f=0;continue;
                    printf("HERE1");

                    }

                    }
                    if(f==1 && playersarr[k].score>top[j].score){
                        top[j].score=playersarr[k].score;
                        printf("HERE2");
                    }
                }

        }
    FILE* fp;
    fp = fopen("TOP10.txt","a");
    if (fp == NULL) {
         printf("Error\n");
         exit(1);
      }
      else{
        /* ################ PLAYER INFO ################## */
        for(i=0;i<2;i++){
                int j=0;
                for(j=0 ; j<30 ; j++)
                {

                    fprintf(fp,"%c",playersarr[i].name[j]);
                }
           fprintf(fp,"%d\n",playersarr[i].score);
           }
      }
      fclose(fp);
}

void loadtop10()
{

    for(int j=0 ; j<20 ;j++)
    {
        for(int u=0 ; u<30 ; u++)
        {
            top[j].name[u]=' ';
        }
        top[j].score=0;
    }
    FILE* fp;
    fp = fopen("TOP10.txt","r");
    if (fp == NULL) {
         printf("Error\n");
         exit(1);
      }
      else{
        /* ################ PLAYER INFO ################## */
        for(i=0;i<20;i++){
                int j=0;
                for(j=0 ; j<30 ; j++)
                {
                    fscanf(fp,"%c",&top[i].name[j]);
                }
           fscanf(fp,"%d\n",&top[i].score);
           }

      }
      fclose(fp);


}
