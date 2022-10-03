from math import inf as infinity
import random
import os
from os import system
import time
import platform
"""
Tic Tac Toe!
"""

HUMAN = 1
COMP = 2


def new_game():
    board = [[0, 0, 0],
             [0, 0, 0],
             [0, 0, 0]]

    return board


def print_board(board):
    """
    Print formatted tic tac toe board
    """
    # Correct clear commands for unix and windows
    os_name = platform.system().lower()
    if "windows" in os_name:
        os.system("cls")
    else:
        os.system("clear")
    print("\n")
    for i in board:
        print("\t", end="")
        print(i)
    print("")


def check_win(board, player):
    """
    Tests if a specific player wins. Possibilities:
    * Three rows
    * Three cols
    * Two diagonals
    """
    state = board
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


def game_over(board):
    """
    Check and see if a player wins,
    If so display a message and reset the game.
    """
    display_time = 0.2
    # Check win condition
    if check_win(board, COMP):
        print("Computer Wins!!")
        time.sleep(display_time)
        return True
    elif check_win(board, HUMAN):
        print("Human Wins!!")
        time.sleep(display_time)
        return True
    elif 0 not in board[0]:
        if 0 not in board[1]:
            if 0 not in board[2]:
                print("Stalemate!!")
                time.sleep(display_time)
                return True


def calc_moves(board):
    """
    Determine which moves are still possible board
    """
    possible_moves = []
    # i = row
    # j = column
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == 0:
                possible_moves.append([i, j])
    return possible_moves


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


def move(board, player, position):
    """
    Update board with a move
    """
    row = position[0]
    column = position[1]

    board[row][column] = player
    print_board(board)
    return board


def human_move(board):
    valid = False

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
    return board


def random_move(board, player):
    my_move = random.choice(calc_moves(board))
    board = move(board, player, my_move)
    print_board(board)
    return board


def random_game(board):
    comp_turn = True
    while not game_over(board):
        if comp_turn:
            board = random_move(board, COMP)
            comp_turn = False
        else:
            board = random_move(board, HUMAN)
            comp_turn = True
        time.sleep(0.1)


"""
PSUEDOCODE

Algorithms in a Nutshell (adapted)

minimax(state, depth, player)

    if (player = max) then
        best = [null, -infinity]
    else
        best = [null, +infinity]

    if (depth = 0 or gameover) then
        score = evalulate this player, aka check win
        return [null, score]

    for each valid move m for player in state s do
        execute move m on s
        [move, score] = minimax(s, depth - 1, -player) (-player = other player)
        undo move m on s

        if (player = max (comp)) then
            if score > best.score then best = [move, score]
        else
            if score < best.score then best = [move, score]
    return best
end
"""


def minimax_COMP(b, depth, player):
    # COMP is Maximizer
    # HUMAN is Minimizer
    # Start with worst possible score
    if player == COMP:
        best = [-1, -1, -infinity]
    else:
        best = [-1, -1, +infinity]

    if depth == 0:
        if check_win(b, COMP):
            score = +1
        elif check_win(b, HUMAN):
            score = -1
        else:
            score = 0
        return [-1, -1, score]

    for cell in calc_moves(b):
        row, column = cell[0], cell[1]
        b[row][column] = player

        score = minimax_COMP(b, depth - 1, -player)
        # Undo
        b[row][column] = 0
        score[0], score[1] = row, column

        # Maximizer
        if player == COMP:
            if score[2] > best[2]:
                best = score
        # Minimizer
        else:
            if score[2] < best[2]:
                best = score

    return best


def minimax_HUMAN(b, depth, player):
    # COMP is Maximizer
    # HUMAN is Minimizer
    # Start with worst possible score
    if player == HUMAN:
        best = [-1, -1, -infinity]
    else:
        best = [-1, -1, +infinity]

    if depth == 0:
        if check_win(b, HUMAN):
            score = +1
        elif check_win(b, COMP):
            score = -1
        else:
            score = 0
        return [-1, -1, score]

    for cell in calc_moves(b):
        row, column = cell[0], cell[1]
        b[row][column] = player

        score = minimax_HUMAN(b, depth - 1, -player)
        # Undo
        b[row][column] = 0
        score[0], score[1] = row, column

        # Maximizer
        if player == HUMAN:
            if score[2] > best[2]:
                best = score
        # Minimizer
        else:
            if score[2] < best[2]:
                best = score

    return best


def random_V_ai(board):
    while not game_over(board):
        # Random Player
        board = random_move(board, HUMAN)
        time.sleep(0.5)

        if game_over(board):
            return

        # AI
        depth = len(calc_moves(board))
        my_move = minimax_COMP(board, depth, COMP)
        board = move(board, COMP, [my_move[0], my_move[1]])
        time.sleep(0.5)


def human_V_ai(board):
    while not game_over(board):
        # Human
        print_board(board)
        board = human_move(board)
        time.sleep(0.1)

        if game_over(board):
            return

        # AI
        depth = len(calc_moves(board))
        my_move = minimax(board, depth, COMP)
        board = move(board, COMP, [my_move[0], my_move[1]])
        time.sleep(0.1)


def ai_V_ai(board):
    while not game_over(board):

        # Ai 1 - COMP
        depth = len(calc_moves(board))
        comp_move = minimax_COMP(board, depth, COMP)
        move(board, COMP, [comp_move[0], comp_move[1]])
        time.sleep(0.1)
        # if depth == 9:
        #     board = random_move(board, COMP)
        # else:
        # comp_move = minimax_COMP(board, depth, COMP)
        # move(board, COMP, [comp_move[0], comp_move[1]])
        # move(board, COMP, [1, 1])
        time.sleep(0.1)

        if game_over(board):
            return

        # Ai 2 - HUMAN
        depth = len(calc_moves(board))
        human_move = minimax_HUMAN(board, depth, HUMAN)
        move(board, HUMAN, [human_move[0], human_move[1]])
        time.sleep(0.1)


board = [[0, 0, 0],
         [0, 0, 0],
         [0, 0, 0]]

# random_V_ai(board)
# human_V_ai(board)
for i in range(200):
    ai_V_ai(board)
    board = new_game()
