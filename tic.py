import numpy as np
import os
import random
import time

board = [[0, 0, 0],
         [0, 0, 0],
         [0, 0, 0]]

# Unplayed = 0
HUMAN = 1
COMP = 2

def check_win(state, player):
    """
    This function tests if a specific player wins. Possibilities:
    * Three rows    [X X X] or [O O O]
    * Three cols    [X X X] or [O O O]
    * Two diagonals [X X X] or [O O O]
    """
    win_state = [
        [state[0][0], state[0][1], state[0][2]],
        [state[1][0], state[1][1], state[1][2]],
        [state[2][0], state[2][1], state[2][2]],
        [state[0][0], state[1][0], state[2][0]],
        [state[0][1], state[1][1], state[2][1]],
        [state[0][2], state[1][2], state[2][2]],
        [state[0][0], state[1][1], state[2][2]],
        [state[2][0], state[1][1], state[0][2]],
    ]
    if [player, player, player] in win_state:
        return True
    else:
        return False

def print_board(board):
    """
    Print formatted tic tac toe board
    """
    os.system("cls")
    print("\n")
    for i in board:
        print("\t", end="")
        print(i)
    print("\n")

def calc_moves(board):
    """
    Determine which moves are still possible
    """
    possible_moves = []
    # i = row
    # j = column
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == 0:
                possible_moves.append([i, j])
    return possible_moves

def move(board, player, position):
    """
    Update board with a move
    """
    row = position[0]
    column = position[1]

    board[row][column] = player
    return board

# Test calc_moves
def random_game(board):
    """
    Randomly select moves and play them.
    Test for calc_moves() and move()
    """
    for i in range(9):
        possible_moves = calc_moves(board)
        my_move = random.choice(possible_moves)
        board = move(board, COMP, my_move)
        print_board(board)
        # Check win condition after comp move
        if check_win(board, COMP):
            print("Computer Wins!!")
            return 0
        elif check_win(board, HUMAN):
            print("Human Wins!!")
            return 0
        time.sleep(.5)

def valid_move(board, move):
    """
    Test to ensure a move by is not a repeat
    """
    row = move[0]
    column = move[1]
    if board[row][column] == 1 or board[row][column] == 2:
        return False
    else:
        return True

def play_human_randomly(board):
    """
    Have comp play against a human randomly selecting moves
    """
    for i in range(9):
        valid = False 

        # Human
        print_board(board)
        print("Humans Turn")
        
        while not valid:
            row = int(input("Row: "))
            column = int(input("Column: "))
            if valid_move(board, [row, column]):
                move(board, HUMAN, [row, column])
                valid = True
            else:
                print("Invalid move, retry\n")
                valid = False
        
        print_board(board)
        
        # Check win condition after human move
        if check_win(board, COMP):
            print("Computer Wins!!")
            return 0
        elif check_win(board, HUMAN):
            print("Human Wins!!")
            return 0

        # Comp
        my_move = random.choice(calc_moves(board))
        move(board, COMP, my_move)
        print_board(board)
        
        # Check win condition after comp move
        if check_win(board, COMP):
            print("Computer Wins!!")
            return 0
        elif check_win(board, HUMAN):
            print("Human Wins!!")
            return 0

random_game(board)