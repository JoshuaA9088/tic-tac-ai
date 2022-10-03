from math import inf as infinity
from random import choice
import platform
import time
from os import system
from TicTacToe import *

game = Tic()
HUMAN = game.HUMAN
COMP = game.COMP

board = [[0, 0, 0],
         [0, 0, 0],
         [0, 0, 0]]


def minimax(board, depth, player):
    if player == COMP:
        best = [1, 1, -infinity]
    else:
        best = [1, 1, infinity]

    if depth == 0 or game.game_over():
        score = game.evaluate()
        return [1, 1, score]

    for move in game.calc_moves(opt_board=board):
        row, column = move[0], move[1]
        board[row][column] = player
        if player == COMP:
            player = HUMAN
        else:
            player = COMP

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


def random_V_ai():
    board = game.get_board()

    while not game.game_over():
        # Random Player
        game.random_move(HUMAN)
        time.sleep(0.5)

        # AI
        depth = len(game.calc_moves())
        move = minimax(board, depth, COMP)
        if not game.valid_move(move):
            print("INVALID")
            return
        game.move(COMP, move)
        time.sleep(0.5)


if __name__ == "__main__":
    random_V_ai()

# def minimax(board, player):
#     possible_moves = game.calc_moves()
#     # Maximizer
#     if player == game.COMP:
#         best = [1, 1, -infinity]
#     # Minimizer
#     else:
#         best = [1, 1, infinity]
#     # Iterate through possible
#     for move in possible_moves:
#         row, column = move[0], move[1]
#         board[row][column] = player
#         score = minimax(board, game.HUMAN if player == game.COMP else game.COMP)
#         score[0], score[1] = row, column
#
#         if player == game.COMP:
#             if score[2] > best[2]:
#                 best = score
#         else:
#             if score[2] < best[2]:
#                 best = score
#     return best
#
# def randomVai():
#     while not game.game_over():
#         game.random_move(game.HUMAN)
#         board = game.get_board()
#         best = minimax(board, game.COMP)
#         # print(best)
#         game.move(game.COMP, best)
#         time.sleep(1)
#         # print('foo')
# def main():
#     game.randomVai()
#     # best = minimax(board, game.COMP)
#     # for i in range(1000):
#     #     game.random_game()
#     #     time.sleep(0.1)
#
# if __name__ == "__main__":
#     main()
