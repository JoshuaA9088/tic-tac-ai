import numpy as np
import os
import random
import time
from math import inf as infinity

# Unplayed = 0
HUMAN = 1
COMP = 2

def new_game():
    board = [[0, 0, 0],
            [0, 0, 0],
            [0, 0, 0]]
    return board

def check_win(state, player):
    """
    This function tests if a specific player wins. Possibilities:
    * Three rows
    * Three cols
    * Two diagonals
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

def game_over(board, i):
    display_time = 0.5
    # Check win condition after comp move
    if check_win(board, COMP):
        print("Computer Wins!!")
        time.sleep(display_time)
        return True
    elif check_win(board, HUMAN):
        print("Human Wins!!")
        time.sleep(display_time)
        return True
    elif i == 8:
        print("Stalemate!!")
        time.sleep(display_time)
        return True

# Test calc_moves
def random_game(board):
    """
    Randomly select moves and play them.
    Test for calc_moves() and move()
    """
    comp_turn = True

    for i in range(9):

        if comp_turn:
            possible_moves = calc_moves(board)
            my_move = random.choice(possible_moves)
            board = move(board, COMP, my_move)
            print_board(board)
            comp_turn = False
        else:
            possible_moves = calc_moves(board)
            my_move = random.choice(possible_moves)
            board = move(board, HUMAN, my_move)
            print_board(board)
            comp_turn = True

        if game_over(board, i):
            return 0

        time.sleep(0.5)

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
        if game_over(board, i):
            return 0

        # Comp
        my_move = random.choice(calc_moves(board))
        move(board, COMP, my_move)
        print_board(board)

        # Check win condition after comp move
        if game_over(board, i):
            return 0

def play_many_random(board, num_games):
    for _ in range(num_games):
        random_game(board)

        # Reset the game
        board = new_game()


def minimax(board, depth, player):
    if player == COMP:
        best = [1, 1, -infinity]
    else:
        best = [1, 1, +infinity]

    for m in calc_moves(board):
        x, y = m[0], m[1]
        board[x][y] = player
        score = minimax(board, depth - 1, HUMAN)
        board[x][y] = 0
        score[0], score[1] = x, y

        if player == COMP:
            if score[2] > best[2]:
                best = score
        else:
            if score[2] < best[2]:
                best = score
    return best

# play_many_random(board, 100)
def play_smart_game(board):
    for i in range(9):

        valid = False

        # Human
        print_board(board)
        print("Humans Turn")

        while not valid:
            row = int(input("Row: "))
            column = int(input("Column: "))
            if valid_move(board, [row, column]):
                board = move(board, HUMAN, [row, column])
                valid = True
            else:
                print("Invalid move, retry\n")
                valid = False

        print_board(board)

        # Check win condition after human move
        if game_over(board, i):
            return 0

        print_board(board)

        depth = len(calc_moves(board))
        print("DEPTH: ", depth)
        my_move = minimax(board, depth, COMP)
        print(my_move)
        board = move(board, COMP, [my_move[0], my_move[1]])


        if game_over(board, i):
            return 0

    time.sleep(0.5)

def play_smart_game_against_self(board):
    for i in range(9):

        # Comp 1 Uses minimax
        depth = len(calc_moves(board))
        my_move = minimax(board, depth, COMP)
        board = move(board, COMP, [my_move[0], my_move[1]])
        print_board(board)

        if game_over(board, i):
            return 0

        # Comp 2 Randomly picks
        possible_moves = calc_moves(board)
        my_move = random.choice(possible_moves)
        board = move(board, HUMAN, my_move)
        print_board(board)

        if game_over(board, i):
            return 0

        time.sleep(0.5)


for i in range(100):
    board = new_game()
    play_smart_game_against_self(board)
