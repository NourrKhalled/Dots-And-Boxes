////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int mode=0; //game mode
int choice=0;
playerinfo top[10];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mainmenuchoice()  //Main menu choice at startup
{

        printf("Choose:\n\t1:Start Game\n\t2:Load Game\n\t3:Top Ten Players\n\t4:Exit\n");
        scanf("%d" , &choice);
        if (choice < 1)
        {
            char charoffbuff;
            scanf("%c", &charoffbuff);  // eats a character off the buffer
        }
        switch (choice)
        {
            case 1: printf("Start\n");
                    do
                    {printf("Choose Mode:\n\t1:Expert Mode\n\t2:Beginners Mode\n");
                    scanf("%d" , &mode);
                    if (mode < 1)
                        {
                            char charoffbuff;
                            scanf("%c", &charoffbuff);  // eats a character off the buffer
                        }
                    switch (mode)
                    {
                    case 1: reset_grid_exp();
                    EXP();
                    mainmenuchoice();
                    break;
                    case 2:reset_grid();
                    BEG();
                    mainmenuchoice();
                    break;
                    default:SetColor(4);
                    printf("Enter A Valid Number!\n");
                    SetColor(15);
                    }
                    }while(mode!=1 && mode!=2);
                    break;

            case 2:printf("Choose Save File To Load:\n\t\t1)SAVE 1\n\t\t2)SAVE 2\n\t\t3)SAVE 3");
                int flag;

            do
            {
                scanf("%d" , &flag);
            }while(flag>3 && flag<1);
            loadGame(flag);
            mainmenuchoice();
            break;

            case 3: printf("Top10\n");
            loadtop10();
            top10(top, 20);
            mainmenuchoice();
            break;

            case 4: printf("Bye Bye :(");
                    exit(0);

            default:SetColor(4);
            printf("Enter A Valid Number!\n");
            SetColor(15);
            mainmenuchoice();
            return;
        }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int ingamemenu(int ingamechoice , int playermoves ,int player )//, int score
{
    switch (ingamechoice)
    {
        case 1111:
        if((round_moves)<=0){
        printf("Can't undo!!");
        break;
        }
        else{round_moves=undo(playermoves , player);
        return playermoves-1;}
        break;
        case 2222:
        round_moves=redo(&playermoves , player);
        break;
        case 3333: printf("Save Game\n");
        int flag;
        printf("Choose Save File:\n\t\t1)SAVE 1\n\t\t2)SAVE 2\n\t\t3)SAVE 3");
        do
        {
            scanf("%d" , &flag);
        }while(flag>3 && flag<1);
        saveGame(flag);
        break;
        case 4444:
        mainmenuchoice();
        break;

    }

    return playermoves;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ingamemenuEXP(int ingamechoice , int playermoves ,int player )//, int score
{
    SetColor(3);
    printf("\t\t\t\tP1's Score: %d" , playersarr[0].score);
    SetColor(5);
    printf("\t\tP2's Score: %d\n\n" , playersarr[1].score);
    SetColor(15);
    SetColor(3);
    printf("\t\t\t\tNumber of P1's Moves:%d\t\t" ,player1move);
    SetColor(5);
    printf("Number of P2's Moves:%d\n" ,player2move);
    SetColor(15);
    switch (ingamechoice)
    {
        case 1111:
        if((round_moves)<=0){
        printf("Can't undo!!");
        break;
        }
        else{round_moves=undoEXP(playermoves , player);
        return playermoves-1;}
        break;
        case 2222:
        round_moves=redoEXP(&playermoves , player);
        break;
        case 3333: printf("Save Game");
        int flag;
        printf("Choose Save File:\n\t\t1)SAVE 1\n\t\t2)SAVE 2\n\t\t3)SAVE 3");
        do
        {
            scanf("%d" , &flag);
        }while(flag>3 && flag<1);
        saveGame(flag);
        break;
        case 4444:
        mainmenuchoice();
        break;

    }

    return playermoves;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


