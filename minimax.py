from math import inf as infinity
from random import choice
import platform
import time
from os import system
from TicTacToe import *

game = Tic()
HUMAN = game.HUMAN
COMP = game.COMP

def minimax(board, player):
    possible_moves = game.calc_moves()
    # Maximizer
    if player == game.COMP:
        best = [1, 1, -infinity]
    # Minimizer
    else:
        best = [1, 1, infinity]
    # Iterate through possible
    for move in possible_moves:
        row, column = move[0], move[1]
        board[row][column] = player
        score = minimax(board, game.HUMAN if player == game.COMP else game.COMP)
        score[0], score[1] = row, column

        if player == game.COMP:
            if score[2] > best[2]:
                best = score
        else:
            if score[2] < best[2]:
                best = score
    return best

def randomVai():
    while not game.game_over():
        game.random_move(game.HUMAN)
        board = game.get_board()
        best = minimax(board, game.COMP)
        # print(best)
        game.move(game.COMP, best)
        time.sleep(1)
        # print('foo')
def main():
    game.randomVai()
    # best = minimax(board, game.COMP)
    # for i in range(1000):
    #     game.random_game()
    #     time.sleep(0.1)

if __name__ == "__main__":
    main()
