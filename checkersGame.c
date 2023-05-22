#include "checkersGame.h"



/*exe 1*/

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src) 
{
    
    SingleSourceMovesTreeNode *source = InitNewTreeNode(board, src);
    if (source == NULL)
    {
        return NULL;
    }

    switch (board[src->row][src->col])
    {
    case 'B': //bottom to top movement
        FillTreeLeftSideB(source, board, src, 'T');
        FillTreeRightSideB(source, board, src, 'T');
        break;
    case 'T': //top to bottom movement
        FillTreeLeftSideT(source, board, src, 'B');
        FillTreeRightSideT(source, board, src, 'B');
        break;
    
    default:

        return NULL;
        break;
    }
    

    if (source == NULL)
    {
        return NULL;
    }
    
    SingleSourceMovesTree *tree = (SingleSourceMovesTree *)malloc(sizeof(SingleSourceMovesTree));
    if (tree == NULL)
    {
        DeleteTreeNodes(source);
        return NULL;
    }

    tree->source = source;
    return tree;
}

void FillTreeLeftSideB(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent)
{   
    //if tile is inside board
    if (pos->row + 1 < 8 && pos->col - 1 >= 0) 
    {

        //if jump tile is inside board AND you can jump over the opponent (eat/jump)
        if (pos->row + 2 < 8 && pos->col - 2 >= 0 && (borad[pos->row + 1][pos->col - 1] == oponnent && borad[pos->row + 2][pos->col - 2] == '\0')) 
        {
                //proceed to jump over and recursively call
                src->next_move[LEFT] = InitNewTreeNode(borad, pos);
                if (src->next_move[LEFT] == NULL)
                {
                    DeleteTreeNodes(src);
                }
                src->next_move[LEFT]->pos->col -= 2;
                src->next_move[LEFT]->pos->row += 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideB(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
                FillTreeRightSideB(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row + 1][pos->col-1] == '\0')
        {
            src->next_move[LEFT] = InitNewTreeNode(borad, pos);
            src->next_move[LEFT]->pos->col -= 1;
            src->next_move[LEFT]->pos->row += 1;
        }
    }
    
}

void FillTreeRightSideB(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent)
{
    //if tile is inside board
    if (pos->row + 1 < 8 && pos->col + 1 >= 0) // wrap in bool function
    {

        //if jump tile is inside board AND you can jump over the opponent (eat/jump)
        if (pos->row + 2 < 8 && pos->col + 2 >= 0 && (borad[pos->row + 1][pos->col + 1] == oponnent && borad[pos->row + 2][pos->col + 2] == '\0')) 
        {
                //proceed to jump over and recursively call
                src->next_move[RIGHT] = InitNewTreeNode(borad, pos);
                if (src->next_move[RIGHT] == NULL)
                {
                    DeleteTreeNodes(src);
                }
                src->next_move[RIGHT]->pos->col += 2;
                src->next_move[RIGHT]->pos->row += 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideB(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
                FillTreeRightSideB(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row + 1][pos->col+1] == '\0')
        {
            src->next_move[RIGHT] = InitNewTreeNode(borad, pos);
            src->next_move[RIGHT]->pos->col += 1;
            src->next_move[RIGHT]->pos->row += 1;
        }
    }
}

void FillTreeLeftSideT(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent)
{
    //if tile is inside board
    if (pos->row - 1 < 8 && pos->col - 1 >= 0) // wrap in bool function
    {

        //if jump tile is inside board AND you can jump over the opponent (eat/jump)
        if (pos->row - 2 < 8 && pos->col - 2 >= 0 && (borad[pos->row - 1][pos->col - 1] == oponnent && borad[pos->row - 2][pos->col - 2] == '\0')) 
        {
                //proceed to jump over and recursively call
                src->next_move[LEFT] = InitNewTreeNode(borad, pos);
                if (src->next_move[LEFT] == NULL)
                {
                    DeleteTreeNodes(src);
                }
                src->next_move[LEFT]->pos->col -= 2;
                src->next_move[LEFT]->pos->row -= 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideT(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
                FillTreeRightSideT(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row - 1][pos->col-1] == '\0')
        {
            src->next_move[LEFT] = InitNewTreeNode(borad, pos);
            src->next_move[LEFT]->pos->col -= 1;
            src->next_move[LEFT]->pos->row -= 1;
        }
    }
}

void FillTreeRightSideT(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent)
{
    //if tile is inside board
    if (pos->row - 1 < 8 && pos->col + 1 >= 0) // wrap in bool function
    {

        //if jump tile is inside board AND you can jump over the opponent (eat/jump)
        if (pos->row - 2 < 8 && pos->col + 2 >= 0 && (borad[pos->row - 1][pos->col + 1] == oponnent && borad[pos->row - 2][pos->col + 2] == '\0')) 
        {
                //proceed to jump over and recursively call
                src->next_move[RIGHT] = InitNewTreeNode(borad, pos);
                if (src->next_move[RIGHT] == NULL)
                {
                    DeleteTreeNodes(src);
                }
                
                src->next_move[RIGHT]->pos->col += 2;
                src->next_move[RIGHT]->pos->row -= 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideT(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
                FillTreeRightSideT(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row - 1][pos->col+1] == '\0')
        {
            src->next_move[RIGHT] = InitNewTreeNode(borad, pos);
            src->next_move[RIGHT]->pos->col += 1;
            src->next_move[RIGHT]->pos->row -= 1;
        }
    }
}


SingleSourceMovesTreeNode *InitNewTreeNode(Board board, checkersPos *pos)
{
    SingleSourceMovesTreeNode *node = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
    if (node == NULL)
    {
        return NULL;
    }

    node->pos = (checkersPos *)malloc(sizeof(checkersPos));
    if (node->pos == NULL)
    {
        free(node);
        return NULL;
    }
    
    node->pos->row = pos->row;
    node->pos->col = pos->col;

    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            node->board[i][j] = board[i][j];
        }
    }

    node->total_captures_so_far = 0;
    return node;
}

void DeleteTreeNodes(SingleSourceMovesTreeNode *node)
{
    if (node->next_move[LEFT] == NULL && node->next_move[RIGHT] == NULL)
    {
        free(node->pos);
        node->pos = NULL;
        free(node);
        node = NULL;
    }

    DeleteTreeNodes(node->next_move[LEFT]);
    DeleteTreeNodes(node->next_move[RIGHT]);
}



/***************exe 2***************/

SingleSourceMoveList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree) //TODO: fix seg fault
{
    SingleSourceMoveList *list = (SingleSourceMoveList *)malloc(sizeof(SingleSourceMoveList));
    if (list == NULL)
    {
        return NULL;
    }
    SingleSourceMoveListCell *cell = InitNewSingleSourceMoveList(moves_tree->source->pos, moves_tree->source->total_captures_so_far);

    list->head = cell;
    printf("fail in begin exe2\n");

    while (moves_tree->source != NULL)
    {   
        //check where is the most jumps and go to that direction and add it to the list
        if (moves_tree->source->next_move[LEFT]->total_captures_so_far >= 
            moves_tree->source->next_move[RIGHT]->total_captures_so_far) // if they are equal we go left
        {
            cell->next = InitNewSingleSourceMoveList(moves_tree->source->pos, moves_tree->source->next_move[LEFT]->total_captures_so_far);
            if (cell->next == NULL)
            {
                DeleteSingleSourceCell(cell);
                return NULL;
            }
            
            moves_tree->source = moves_tree->source->next_move[LEFT];
        }
        else
        {
            cell->next = InitNewSingleSourceMoveList(moves_tree->source->pos, moves_tree->source->next_move[RIGHT]->total_captures_so_far);
            if (cell->next == NULL)
            {
                DeleteSingleSourceCell(cell);
                return NULL;
            }
            moves_tree->source = moves_tree->source->next_move[RIGHT];
        }
        list->tail = cell;
        cell = cell->next;
    }

    printf("fail in end exe2\n");
    DeleteTreeNodes(moves_tree->source);
    free(moves_tree); //free tree
    return list;
}


SingleSourceMoveListCell *InitNewSingleSourceMoveList(checkersPos *pos, unsigned short captures)
{
    SingleSourceMoveListCell *cell = (SingleSourceMoveListCell *)malloc(sizeof(SingleSourceMoveListCell));
    if (cell == NULL)
    {
        return NULL;
    }

    cell->position = (checkersPos *)malloc(sizeof(checkersPos));
    if (cell->position == NULL)
    {
        free(cell);
        return NULL;
    }
    
    cell->position->row = pos->row;
    cell->position->col = pos->col;

    cell->captures = captures;
    cell->next = NULL;
    return cell;
}

void DeleteSingleSourceCell(SingleSourceMoveListCell * cell)
{
    SingleSourceMoveListCell *next;
    while (cell != NULL)
    {
        next = cell->next;
        free(cell->position);
        cell->position = NULL;
        free(cell);
        cell = next;
    }
    
}

/**************exe 3****************/

MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board borad, Player player)  //TODO free all cell if aloc fail
{
    checkersPos pos = {0,0};
    
    MultipleSourceMovesList *list = (MultipleSourceMovesList *)malloc(sizeof(MultipleSourceMovesList));
    if (list == NULL)
    {
        return NULL;
    }

    MultipleSourceMovesListCell *cell;
    
    //iterate the board to find a block wite player and edit the pos
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        pos.row = i;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            pos.col = j;
            if (borad[i][j] == player)
            {   
                //find for this block the best move and add this move to the list
                cell = InitNewMultipleSourceMovesListCell(FindSingleSourceOptimalMove(FindSingleSourceMoves(borad, &pos)));
                printf("fail in exe 3\n");
                if (list->head == NULL)
                {
                    list->head = cell;
                }

                if (cell == NULL)
                {
                    DeleteMultipleSourceMovesListCell(list->head);
                    free(list);
                    return NULL;
                }

                list->tail = cell;
                cell = cell->next;

            }
        }
    }

    return list;
}


MultipleSourceMovesListCell *InitNewMultipleSourceMovesListCell(SingleSourceMoveList *single_source_move_list)
{
    MultipleSourceMovesListCell *cell = (MultipleSourceMovesListCell *)malloc(sizeof(MultipleSourceMovesListCell));
    if (cell == NULL)
    {
        return NULL;
    }
    cell->next = NULL;
    cell->single_source_moves_list = single_source_move_list;
    return cell;
    
}

void DeleteMultipleSourceMovesListCell(MultipleSourceMovesListCell *cell)
{
    MultipleSourceMovesListCell *next;
    while (cell != NULL)
    {
        next = cell->next;
        free(cell);
        cell = next;
    }
    
}

/**************exe 4****************/

void Turn(Board board, Player player) //TODO: delete all moves after the play
{
    MultipleSourceMovesList *list = FindAllPossiblePlayerMoves(board, player);
    printf("fail in exe 4\n");
    unsigned short current_captures = 0;
    unsigned short max_captures = 0;
    MultipleSourceMovesListCell *multiple_move_cell = list->head;
    SingleSourceMoveListCell *single_move_cell = NULL;
    SingleSourceMoveListCell *play = NULL;

    while (multiple_move_cell != NULL)
    {
        //finding the best play to do
        single_move_cell = multiple_move_cell->single_source_moves_list->head;
        while (single_move_cell != NULL)
        {
            current_captures = single_move_cell->captures;
            single_move_cell = single_move_cell->next;
        }
        
        if (current_captures >= max_captures)
        {
            max_captures = current_captures;
            play = multiple_move_cell->single_source_moves_list->head;
        }
        multiple_move_cell = multiple_move_cell->next;
    }

    //make the play

    printf("%c%d->",PosToChr(play->position), play->position->col);
    while (play->next != NULL)
    {
        board[play->position->row][play->position->col] = '\0'; // '\0' for empty block
        play = play->next;
    }
    board[play->position->row][play->position->col] = player;
    printf("%c%d\n",PosToChr(play->position), play->position->col);


}


/**************exe 5****************/

void PlayGame(Board board, Player starting_player)
{
    // print board, who`s turn, make the turn and print it, print the board again
    PrintBoard(board);
    printf("its %c turn\n", starting_player);
    Turn(board, starting_player);
    PrintBoard(board);
    //TODO: insert this logic into a loop
}

char PosToChr(checkersPos *pos)
{
    char LUT[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        LUT[i] = 'A' + i;
    }
    return LUT[pos->row];
}

void InitializeBoard(Board board) 
{
    // Initialize empty squares
    for (int row = 0; row < BOARD_SIZE; row++) 
    {
        for (int col = 0; col < BOARD_SIZE; col++) 
        {
            board[row][col] = '\0';
        }
    }

    // Add T pieces
    for (int row = 0; row < 3; row++) 
    {
        for (int col = 0; col < BOARD_SIZE; col += 2) 
        {
            if (row % 2 == 0)
            {
                board[row][col + 1] = 'T';
            }
            else
            {
                board[row][col] = 'T';
            }
        }
    }

    // Add B pieces
    for (int row = BOARD_SIZE - 1; row >= BOARD_SIZE - 3; row--) 
    {
        for (int col = 0; col < BOARD_SIZE; col += 2) 
        {
            if (row % 2 == 0)
            {
                board[row][col + 1] = 'B';
            }
            else
            {
                board[row][col] = 'B';
            }
        }
    }
}

void PrintBoard(Board board) 
{
    printf("\n   0  1  2  3  4  5  6  7\n");
    printf(" +--+--+--+--+--+--+--+--+\n");
    for (int row = 0; row < BOARD_SIZE; row++) 
    {
        printf("%d|", row);
        for (int col = 0; col < BOARD_SIZE; col++) 
        {
            if (board[row][col] == '\0') 
            {
                printf("  |");
            } 
            else 
            {
                if (board[row][col] == 'T')
                {
                    printf("T |");
                }
                else
                {
                    printf("B |");
                }
            }
        }
        printf("\n +--+--+--+--+--+--+--+--+\n");
    }
}


int main()
{
    Board board;
    InitializeBoard(board);
    PlayGame(board, 'T');

    return 0;
}

