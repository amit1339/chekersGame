#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define LEFT 0
#define RIGHT 1

/*exe 1*/

typedef struct _checkersPos
{
    char row;
    char col;
} checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode
{
    Board board;
    checkersPos *pos;
    unsigned short total_captures_so_far; // num of skips
    struct _SingleSourceMovesTreeNode *next_move[2];
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
    SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src) //TODO free all cell if aloc fail
{
    
    SingleSourceMovesTree *tree = (SingleSourceMovesTree *)malloc(sizeof(SingleSourceMovesTree));
    if (tree == NULL)
    {
        return NULL;
    }

    tree->source = InitNewTreeNode(board, src);
    if (tree->source == NULL)
    {
        free (tree);
        return NULL;
    }

    switch (board[src->row][src->col])
    {
    case 'B': //bottom to top movement
        FillTreeLeftSideB(tree->source, board, src, 'T');
        FillTreeRightSideB(tree->source, board, src, 'T');
        break;
    case 'T': //top to bottom movement
        FillTreeLeftSideT(tree->source, board, src, 'B');
        FillTreeRightSideT(tree->source, board, src, 'B');
        break;
    
    default:

        return NULL;
        break;
    }
    

    return tree;
}

void FillTreeLeftSideB(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent)
{
    //if tile is inside board
    if (pos->row + 1 < 8 && pos->col - 1 >= 0) // wrap in bool function
    {

        //if jump tile is inside board AND you can jump over the opponent (eat/jump)
        if (pos->row + 2 < 8 && pos->col - 2 >= 0 && (borad[pos->row + 1][pos->col - 1] == oponnent && borad[pos->row + 2][pos->col - 2] == NULL)) 
        {
                //proceed to jump over and recursively call
                src->next_move[LEFT] = InitNewTreeNode(borad, pos);
                src->next_move[LEFT]->pos->col -= 2;
                src->next_move[LEFT]->pos->row += 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideB(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
                FillTreeRightSideB(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row + 1][pos->col-1] == NULL)
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
        if (pos->row + 2 < 8 && pos->col + 2 >= 0 && (borad[pos->row + 1][pos->col + 1] == oponnent && borad[pos->row + 2][pos->col + 2] == NULL)) 
        {
                //proceed to jump over and recursively call
                src->next_move[RIGHT] = InitNewTreeNode(borad, pos);
                src->next_move[RIGHT]->pos->col += 2;
                src->next_move[RIGHT]->pos->row += 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideB(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
                FillTreeRightSideB(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row + 1][pos->col+1] == NULL)
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
        if (pos->row - 2 < 8 && pos->col - 2 >= 0 && (borad[pos->row - 1][pos->col - 1] == oponnent && borad[pos->row - 2][pos->col - 2] == NULL)) 
        {
                //proceed to jump over and recursively call
                src->next_move[LEFT] = InitNewTreeNode(borad, pos);
                src->next_move[LEFT]->pos->col -= 2;
                src->next_move[LEFT]->pos->row -= 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideT(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
                FillTreeRightSideT(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row - 1][pos->col-1] == NULL)
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
        if (pos->row - 2 < 8 && pos->col + 2 >= 0 && (borad[pos->row - 1][pos->col + 1] == oponnent && borad[pos->row - 2][pos->col + 2] == NULL)) 
        {
                //proceed to jump over and recursively call
                src->next_move[RIGHT] = InitNewTreeNode(borad, pos);
                src->next_move[RIGHT]->pos->col += 2;
                src->next_move[RIGHT]->pos->row -= 2;
                src->total_captures_so_far += 1;
                FillTreeLeftSideT(src->next_move[RIGHT], borad, src->next_move[RIGHT]->pos, oponnent);
                FillTreeRightSideT(src->next_move[LEFT], borad, src->next_move[LEFT]->pos, oponnent);
        }

        //you cant jump or there is no opponent, next move is just a regular move
        else if (borad[pos->row - 1][pos->col+1] == NULL)
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

//TODO free TREE


/***************exe 2***************/

typedef struct _SingleSourceMoveListCell
{
    checkersPos *position;
    unsigned short captures;
    struct _SingleSourceMoveListCell *next;
} SingleSourceMoveListCell;

typedef struct _SingleSourceMoveList
{
    SingleSourceMoveListCell *head;
    SingleSourceMoveListCell *tail;
} SingleSourceMoveList;

SingleSourceMoveList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree) //TODO free all cell if aloc fail
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
        //check where is the most jumps and go to that direction and add it to the list
        if (moves_tree->source->next_move[LEFT]->total_captures_so_far >= 
            moves_tree->source->next_move[RIGHT]->total_captures_so_far) // if they are equal we go left
        {
            cell->next = InitNewSingleSourceMoveList(moves_tree->source->pos, moves_tree->source->next_move[LEFT]->total_captures_so_far);
            moves_tree->source = moves_tree->source->next_move[LEFT];
        }
        else
        {
            cell->next = InitNewSingleSourceMoveList(moves_tree->source->pos, moves_tree->source->next_move[RIGHT]->total_captures_so_far);
            moves_tree->source = moves_tree->source->next_move[RIGHT];
        }
        list->tail = cell;
        cell = cell->next;
    }
    //TODO delete tree
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

//TODO free list

/**************exe 3****************/

typedef struct _multipleSourceMovesListCell
{
    SingleSourceMoveList *single_source_moves_list;
    struct _multipleSourceMovesListCell *next;
} MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList
{
    MultipleSourceMovesListCell *head;
    MultipleSourceMovesListCell *tail;
} MultipleSourceMovesList;

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

                if (list->head == NULL)
                {
                    list->head = cell;
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

/**************exe 4****************/

void Turn(Board board, Player player)
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

    printf("%c%d->",PosToChr(play->position), play->position->col);
    while (play->next != NULL)
    {
        board[play->position->row][play->position->col] = NULL; // NULL for empty block
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
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) 
        {
            board[row][col] = NULL;
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
            board[row][col] = 'B';
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
                board[row][col] = 'B';;
            }
        }
    }
}

void PrintBoard(Board board) 
{
    printf("\n   0  1  2  3  4   5  6  7\n");
    printf(" +---+---+---+---+---+---+---+---+\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        printf("%d|", row);
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == NULL) {
                printf("   |");
            } else {
                if (board[row][col] == 'T')
                    printf(" T |");
                else
                    printf(" B |");
            }
        }
        printf("\n +---+---+---+---+---+---+---+---+\n");
    }
}


int main()
{
    Board board;
    InitializeBoard(board);
    PlayGame(board, 'T');

    return 0;
}
