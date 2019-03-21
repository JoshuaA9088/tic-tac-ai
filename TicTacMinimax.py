from math import inf as infinity
import random
import os
import time
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
    # os.system("cls")
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
    display_time = 0.5
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

def evaluate(board):
    """
    Return heuristic evaluation of state.
    """
    if check_win(board, COMP):
        score = 1
    elif check_win(board, HUMAN):
        score = -1
    else:
        score = 0

    return score

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

def human_move(board):
    valid = False

    while not valid:
        row = int(input("Row: "))
        column = int(input("Column: "))
        if valid_move([row, column]):
            move(HUMAN, [row, column])
            valid = True
        else:
            print("Invalid move, retry\n")
            valid = False
    print_board(board)

def random_move(board, player):
    my_move = random.choice(calc_moves(board))
    move(board, player, my_move)
    print_board(board)
    return my_move

def random_game(board):
    comp_turn = True
    while not game_over(board):
        if comp_turn:
            random_move(board, COMP)
            comp_turn = False
        else:
            random_move(board, HUMAN)
            comp_turn = True
        time.sleep(0.1)

def minimax(board, depth, player):
    print(id(board), "MINIMAX")
    # COMP is Maximizer
    # HUMAN is Minimizer

    # Start with worst possible score
    if player == COMP:
        best = [1, 1, -infinity]
    else:
        best = [1, 1, infinity]

    if depth == 0 or game_over(board):
        score = evaluate(board)
        return [1, 1, score]

    for move in calc_moves(board):
        row, column = move[0], move[1]
        board[row][column] = player
        if player == COMP:
            player = HUMAN
        else:
            player =  COMP

        score = minimax(board, depth - 1, player)

        # Maximizer
        if player == COMP:
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
        random_move(board, HUMAN)
        # print(id(board), "MAIN")
        time.sleep(0.1)

        # AI
        depth = len(calc_moves(board))
        my_move = minimax(board.copy(), depth, COMP)
        print("foo")
        print(my_move)
        move(board, COMP, [my_move[0], my_move[1]])
        time.sleep(0.5)

if __name__ == "__main__":
    board = new_game()
    # random_game(board)
    random_V_ai(board)
