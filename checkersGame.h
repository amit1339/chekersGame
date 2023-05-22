#ifndef __CHECKERSGAME_H__
#define __CHECKERSGAME_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define LEFT 0
#define RIGHT 1

/***************exe 1***************/

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

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src);
void FillTreeLeftSideB(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent);
void FillTreeRightSideB(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent);
void FillTreeLeftSideT(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent);
void FillTreeRightSideT(SingleSourceMovesTreeNode *src, Board borad, checkersPos *pos, Player oponnent);
SingleSourceMovesTreeNode *InitNewTreeNode(Board board, checkersPos *pos);
void DeleteTreeNodes(SingleSourceMovesTreeNode *node);

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

SingleSourceMoveList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);
SingleSourceMoveListCell *InitNewSingleSourceMoveList(checkersPos *pos, unsigned short captures);
void DeleteSingleSourceCell(SingleSourceMoveListCell * cell);

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


MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board borad, Player player);
MultipleSourceMovesListCell *InitNewMultipleSourceMovesListCell(SingleSourceMoveList *single_source_move_list);
void DeleteMultipleSourceMovesListCell(MultipleSourceMovesListCell *cell);

/**************exe 4****************/

void Turn(Board board, Player player);

/**************exe 5****************/

void PlayGame(Board board, Player starting_player);

/**************utils****************/
char PosToChr(checkersPos *pos);
void InitializeBoard(Board board);
void PrintBoard(Board board);

#endif // __CHECKERSGAME_H__