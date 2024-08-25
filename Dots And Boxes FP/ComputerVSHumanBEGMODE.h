char grid[6][10];
int i,j;
int row=6, colm=10;
void computer()
{

    int ran_r,ran_c;
    empty_spaces(grid);



    while(empty_spaces(grid))
    {

        do
        {
            ran_r=rand();
            ran_r%=6;
        }while(ran_r<=0);


        if(ran_r%2!=0) //odd row ---
        {


        do
        {
            ran_c=rand()%5;

        }while(ran_c<=0 || ran_c>5 || ran_c%2!=0);  //checks invalid number


        if(ran_c==2)ran_c--;


        else if(ran_c==4)ran_c=5;


        ran_r--;


        if(grid[ran_r][ran_c]=='-') //checks move validity
        {
            computer();
            break;
        }
        else{    //the move
                round_moves++;
                for(int i=0 ; i<3 ; i++)
                {
                    grid[ran_r][ran_c+i]='-';  //inserts the line
                }
        storeinput(player2move++ , 1 , ran_r ,ran_c);  //input stored
        boxclosed(&closedbox , &playersarr[1].score ,1);


        if(closedbox==1)
            {
            closedbox=0;
            chainofboxes(&playersarr[1].score, &player2move , 1 );
            computer();
            }
        break;                            //end of turn####################################################
        }


        }

        else if(ran_r%2==0 && ran_r!=0) //even row |
        {
       do{
         ran_c=rand()%6;
       }while(ran_c<=0 || ran_c%2==0);   //valid col


        if(ran_c==1)ran_c=0;

        else if(ran_c==3)ran_c=4;

        else if(ran_c==5)ran_c=8;

        ran_r--;


        if(grid[ran_r][ran_c]=='|')   //checks move validity
        {
            computer();
            break;
        }

        else{    //the move
            round_moves++;
            grid[ran_r][ran_c]='|';
            storeinput(player2move++ , 1 , ran_r ,ran_c);  //input stored
            boxclosed(&closedbox ,&playersarr[1].score,1);
            round_moves++;

            if(closedbox==1)
            {
            closedbox=0;
            chainofboxes(&playersarr[1].score, &player2move , 1 );
            computer();
            }


        break;                            //end of turn####################################################
        }
    }

    }
}
