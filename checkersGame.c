#include "checkersGame.h"



/*exe 1*/

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src) 
{
    SingleSourceMovesTreeNode *source = InitNewTreeNode(board, src);
    if (source == NULL)
    {
        return NULL;
    }
    if (!(RowToInt(src->row) >= 0 && RowToInt(src->row) < BOARD_SIZE && ColToInt(src->col) >= 0 && ColToInt(src->col) < BOARD_SIZE))
    {
        return NULL;
    }
    

    switch (board[RowToInt(src->row)][ColToInt(src->col)])
    {
        case 'T': //bottom to top movement
            FillTreeLeftSideT(source, board);
            FillTreeRightSideT(source, board);
            break;
        case 'B': //top to bottom movement
            FillTreeLeftSideB(source, board);
            FillTreeRightSideB(source, board);
            break;
    }

    if (source != NULL && source->next_move[LEFT] == NULL || source->next_move[RIGHT] == NULL)
    {
        DeleteTreeNodes(source);
        return NULL;
    }
    

    SingleSourceMovesTree *tree = (SingleSourceMovesTree *)malloc(sizeof(SingleSourceMovesTree));
    if (tree == NULL)
    {
        DeleteTreeNodes(source);  // Clean up the tree if memory allocation fails
        return NULL;
    }

    tree->source = source;
    return tree;
}

int RowToInt(char chr)
{
    return chr - 'A';
}

int ColToInt(char chr)
{
    return chr - '0';
}



void FillTreeLeftSideT(SingleSourceMovesTreeNode *src, Board board) 
{
    if (RowToInt(src->pos->row) + 1 < BOARD_SIZE && ColToInt(src->pos->col) - 1 >= 0)
    {
        if (RowToInt(src->pos->row) + 2 < BOARD_SIZE && ColToInt(src->pos->col) - 2 >= 0 && (board[RowToInt(src->pos->row) + 1][ColToInt(src->pos->col) - 1] == 'B' && board[RowToInt(src->pos->row) + 2][ColToInt(src->pos->col) - 2] == '\0'))
        {   
            checkersPos pos = {src->pos->row + 2, src->pos->col -2};
            src->next_move[LEFT] = InitNewTreeNode(board, &pos);
            if (src->next_move[LEFT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
            src->total_captures_so_far += 1;

            FillTreeLeftSideT(src->next_move[LEFT], board);
            FillTreeRightSideT(src->next_move[RIGHT], board);
            if (src->next_move[LEFT] == NULL)
            {
                src->total_captures_so_far += src->next_move[RIGHT]->total_captures_so_far;
            }

            else if (src->next_move[RIGHT] == NULL)
            {
                src->total_captures_so_far += src->next_move[LEFT]->total_captures_so_far;
            }
            
            else
            {
               src->total_captures_so_far += Max(src->next_move[LEFT]->total_captures_so_far, src->next_move[RIGHT]->total_captures_so_far);
            }
        }
        else if (board[RowToInt(src->pos->row)+ 1][ColToInt(src->pos->col) - 1] == '\0' && src->total_captures_so_far == 0)
        {
            checkersPos pos = {src->pos->row + 1, src->pos->col -1};
            
            src->next_move[LEFT] = InitNewTreeNode(board, &pos);
            if (src->next_move[LEFT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
        }
    }
}

void FillTreeRightSideT(SingleSourceMovesTreeNode *src, Board board) 
{
    if (RowToInt(src->pos->row) + 1 < BOARD_SIZE && ColToInt(src->pos->col) + 1 < BOARD_SIZE)
    {
        if (RowToInt(src->pos->row) + 2 < BOARD_SIZE && ColToInt(src->pos->col) + 2 < BOARD_SIZE && (board[RowToInt(src->pos->row) + 1][ColToInt(src->pos->col) + 1] == 'B' && board[RowToInt(src->pos->row) + 2][ColToInt(src->pos->col) + 2] == '\0'))
        {   
            checkersPos pos = {src->pos->row + 2, src->pos->col + 2};
            src->next_move[RIGHT] = InitNewTreeNode(board, &pos);
            if (src->next_move[RIGHT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
            src->total_captures_so_far += 1;

            FillTreeLeftSideT(src->next_move[LEFT], board);
            FillTreeRightSideT(src->next_move[RIGHT], board);
            if (src->next_move[LEFT] == NULL)
            {
                src->total_captures_so_far += src->next_move[RIGHT]->total_captures_so_far;
            }

            else if (src->next_move[RIGHT] == NULL)
            {
                src->total_captures_so_far += src->next_move[LEFT]->total_captures_so_far;
            }
            
            else
            {
               src->total_captures_so_far += Max(src->next_move[LEFT]->total_captures_so_far, src->next_move[RIGHT]->total_captures_so_far);
            }
        }
        else if (board[RowToInt(src->pos->row)+ 1][ColToInt(src->pos->col) + 1] == '\0' && src->total_captures_so_far == 0)
        {
            checkersPos pos = {src->pos->row + 1, src->pos->col + 1};
            
            src->next_move[RIGHT] = InitNewTreeNode(board, &pos);
            if (src->next_move[RIGHT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
        }
    }
}

void FillTreeLeftSideB(SingleSourceMovesTreeNode *src, Board board) 
{
    if (RowToInt(src->pos->row) - 1 >= 0 && ColToInt(src->pos->col) - 1 >= 0)
    {
        if (RowToInt(src->pos->row) - 2 < BOARD_SIZE && ColToInt(src->pos->col) - 2 >= 0 && (board[RowToInt(src->pos->row) - 1][ColToInt(src->pos->col) - 1] == 'T' && board[RowToInt(src->pos->row) - 2][ColToInt(src->pos->col) - 2] == '\0'))
        {   
            checkersPos pos = {src->pos->row - 2, src->pos->col - 2};
            src->next_move[LEFT] = InitNewTreeNode(board, &pos);
            if (src->next_move[LEFT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
            src->total_captures_so_far += 1;

            FillTreeLeftSideB(src->next_move[LEFT], board);
            FillTreeRightSideB(src->next_move[RIGHT], board);
            if (src->next_move[LEFT] == NULL)
            {
                src->total_captures_so_far += src->next_move[RIGHT]->total_captures_so_far;
            }

            else if (src->next_move[RIGHT] == NULL)
            {
                src->total_captures_so_far += src->next_move[LEFT]->total_captures_so_far;
            }
            
            else
            {
               src->total_captures_so_far += Max(src->next_move[LEFT]->total_captures_so_far, src->next_move[RIGHT]->total_captures_so_far);
            }
            
        }
        else if (board[RowToInt(src->pos->row) - 1][ColToInt(src->pos->col) - 1] == '\0' && src->total_captures_so_far == 0)
        {
            checkersPos pos = {src->pos->row - 1, src->pos->col - 1};
            
            src->next_move[LEFT] = InitNewTreeNode(board, &pos);
            if (src->next_move[LEFT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
        }
    }
}

void FillTreeRightSideB(SingleSourceMovesTreeNode *src, Board board) 
{
    if (src != NULL && RowToInt(src->pos->row) - 1 >= 0 && ColToInt(src->pos->col) + 1 < BOARD_SIZE)
    {
        if (RowToInt(src->pos->row) - 2 < BOARD_SIZE && ColToInt(src->pos->col) + 2 < BOARD_SIZE && (board[RowToInt(src->pos->row) - 1][ColToInt(src->pos->col) + 1] == 'T' && board[RowToInt(src->pos->row) - 2][ColToInt(src->pos->col) + 2] == '\0'))
        {   
            checkersPos pos = {src->pos->row - 2, src->pos->col + 2};
            src->next_move[RIGHT] = InitNewTreeNode(board, &pos);
            if (src->next_move[RIGHT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
            src->total_captures_so_far += 1;

            FillTreeLeftSideB(src->next_move[LEFT], board);
            FillTreeRightSideB(src->next_move[RIGHT], board);
            if (src->next_move[LEFT] == NULL)
            {
                src->total_captures_so_far += src->next_move[RIGHT]->total_captures_so_far;
            }

            else if (src->next_move[RIGHT] == NULL)
            {
                src->total_captures_so_far += src->next_move[LEFT]->total_captures_so_far;
            }
            
            else
            {
               src->total_captures_so_far += Max(src->next_move[LEFT]->total_captures_so_far, src->next_move[RIGHT]->total_captures_so_far);
            }
        }
        else if (board[RowToInt(src->pos->row) - 1][ColToInt(src->pos->col) + 1] == '\0' && src->total_captures_so_far == 0)
        {
            checkersPos pos = {src->pos->row - 1, src->pos->col + 1};
            
            src->next_move[RIGHT] = InitNewTreeNode(board, &pos);
            if (src->next_move[RIGHT] == NULL)
            {
                DeleteTreeNodes(src);
                return;
            }
        }
    }
}

SingleSourceMovesTreeNode *InitNewTreeNode(Board board, checkersPos *pos)
{
    SingleSourceMovesTreeNode *node = (SingleSourceMovesTreeNode *)malloc(sizeof(SingleSourceMovesTreeNode));
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
    if (node == NULL)
    {
        return;
    }

    DeleteTreeNodes(node->next_move[LEFT]);
    DeleteTreeNodes(node->next_move[RIGHT]);

    free(node->pos);
    node->pos = NULL;
    //free(node); //TODO: memory prob
}




/***************exe 2***************/

SingleSourceMoveList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree)
{
    SingleSourceMoveList *list = (SingleSourceMoveList *)malloc(sizeof(SingleSourceMoveList));
    if (list == NULL)
    {
        return NULL;
    }

    SingleSourceMoveListCell *cell = InitNewSingleSourceMoveList(moves_tree->source->pos, moves_tree->source->total_captures_so_far);
    list->head = cell;

    while (moves_tree->source != NULL)
    {
        if (moves_tree->source->next_move[RIGHT] == NULL && moves_tree->source->next_move[LEFT] == NULL)
        {
            break;
        }

        if (moves_tree->source->next_move[RIGHT] == NULL)
        {
            cell->next = Move(moves_tree->source->next_move[LEFT], list);
            moves_tree->source = moves_tree->source->next_move[LEFT];
        }
        else if (moves_tree->source->next_move[LEFT] == NULL)
        {
            cell->next = Move(moves_tree->source->next_move[RIGHT], list);
            moves_tree->source = moves_tree->source->next_move[RIGHT];
        }
        else
        {
            if (moves_tree->source->next_move[LEFT]->total_captures_so_far >
                moves_tree->source->next_move[RIGHT]->total_captures_so_far)
            {
                cell->next = Move(moves_tree->source->next_move[LEFT], list);
                moves_tree->source = moves_tree->source->next_move[LEFT];
            }
            else if(moves_tree->source->next_move[LEFT]->total_captures_so_far <
                moves_tree->source->next_move[RIGHT]->total_captures_so_far)
            {
                cell->next = Move(moves_tree->source->next_move[RIGHT], list);
                moves_tree->source = moves_tree->source->next_move[RIGHT];
            }
            else
            {
                if (moves_tree->source->board[RowToInt(moves_tree->source->pos->row)][ColToInt(moves_tree->source->pos->col)] == 'T')
                {
                    cell->next = Move(moves_tree->source->next_move[RIGHT], list);
                    moves_tree->source = moves_tree->source->next_move[RIGHT];
                }
                else
                {
                    cell->next = Move(moves_tree->source->next_move[LEFT], list);
                    moves_tree->source = moves_tree->source->next_move[LEFT];
                }
                
            }
        }

        cell = cell->next;
    }

    list->tail = cell;
    DeleteTreeNodes(moves_tree->source);
    free(moves_tree);
    return list;
}

SingleSourceMoveListCell *Move(SingleSourceMovesTreeNode *node, SingleSourceMoveList *list)
{
    SingleSourceMoveListCell *cell = InitNewSingleSourceMoveList(node->pos, node->total_captures_so_far);
    if (cell == NULL)
    {
        DeleteSingleSourceCell(list->head);
        free(list);
        return NULL;
    }
    return cell;
}


int Max(int a, int b)
{
    return (a > b) ? a : b;
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

void DeleteSingleSourceCell(SingleSourceMoveListCell *cell)
{
    SingleSourceMoveListCell *next;
    while (cell != NULL)
    {
        next = cell->next;
        free(cell->position);
        free(cell);
        cell = next;
    }
}


/**************exe 3****************/

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
    checkersPos pos = {0, 0};
    
    MultipleSourceMovesList* list_multi = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
    if (list_multi == NULL)
    {
        return NULL;
    }

    list_multi->head = NULL;
    list_multi->tail = NULL;

    MultipleSourceMovesListCell* cell;
    
    // Iterate the board to find a block with the player and update the position
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        pos.row = i + 'A';
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            pos.col = j + '0';
            if (board[i][j] == player)
            {   
                // Find the best move for this block and add it to the list
                SingleSourceMovesTree* tree = FindSingleSourceMoves(board, &pos);
                if (tree == NULL)
                {
                    continue;
                }

                SingleSourceMoveList* list_single = FindSingleSourceOptimalMove(tree);
                if (list_single == NULL)
                {
                    continue;
                }

                cell = InitNewMultipleSourceMovesListCell(list_single);
                if (cell == NULL)
                {
                    DeleteMultipleSourceMovesListCell(list_multi->head);
                    free(list_multi);
                    return NULL;
                }

                if (list_multi->head == NULL)
                {
                    list_multi->head = cell;
                    list_multi->tail = cell;
                }
                else
                {
                    list_multi->tail->next = cell;
                    list_multi->tail = cell;
                }
                
            }
        }
    }

    return list_multi;
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

    printf("%c%c->",play->position->row, play->position->col);
    while (play->next != NULL)
    {
        board[RowToInt(play->position->row)][ColToInt(play->position->col)] = '\0'; // '\0' for empty block
        play = play->next;
    }
    board[RowToInt(play->position->row)][ColToInt(play->position->col)] = player;
    printf("%c%c\n",play->position->row, play->position->col);


}


/**************exe 5****************/

void PlayGame(Board board, Player starting_player)
{
    char winner = 0;
    while ((winner = CheckWin(board)) == 0)
    {
    // print board, who`s turn, make the turn and print it, print the board again
        PrintBoard(board);
        printf("its %c turn\n", starting_player);
        Turn(board, starting_player);
        PrintBoard(board);
        printf(" END OF TURN\n");
        if (starting_player == 'T')
        {
            starting_player = 'B';
        }
        else
        {
            starting_player = 'T';
        }
        
    }

    printf("player %c won the match\n", winner);
}


char CheckWin(Board board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[0][i] == 'B')
        {
            return 'B';
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[BOARD_SIZE - 1][i] == 'T')
        {
            return 'T';
        }
    }
//TODO: check win is not finish... need to check if there is pieces left on board
    
    return 0;
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
        printf("%c|", row + 'A');
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

