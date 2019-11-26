from math import inf as infinity
import random
import os
import time


class Tic:
    """
    Tic Tac Toe!
    """

    def __init__(self, print_game=True):
        self.print = print_game
        self.HUMAN = 1
        self.COMP = 2
        self.new_game()
        self.print_board()

    def new_game(self):
        """
        Reset the game
        """
        self.board = [[0, 0, 0],
                      [0, 0, 0],
                      [0, 0, 0]]

    def print_board(self):
        """
        Print formatted tic tac toe board
        """
        if self.print:
            # os.system("cls")
            print("\n")
            for i in self.board:
                print("\t", end="")
                print(i)
            print("")

    def check_win(self, player):
        """
        Tests if a specific player wins. Possibilities:
        * Three rows
        * Three cols
        * Two diagonals
        """
        state = self.board
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

    def game_over(self):
        """
        Check and see if a player wins,
        If so display a message and reset the game.
        """
        display_time = 0.5
        self.winner = None
        # Check win condition
        if self.check_win(self.COMP):
            if self.print:
                print("Computer Wins!!")
                time.sleep(display_time)
            self.new_game()
            self.winner = self.COMP
            return True
        elif self.check_win(self.HUMAN):
            if self.print:
                print("Human Wins!!")
                time.sleep(display_time)
            self.new_game()
            self.winner = self.HUMAN
            return True
        elif 0 not in self.board[0]:
            if 0 not in self.board[1]:
                if 0 not in self.board[2]:
                    if self.print:
                        print("Stalemate!!")
                        time.sleep(display_time)
                    self.new_game()
                    self.winner = 0
                    return True

    def evaluate(self):
        """
        Return heuristic evaluation of state.
        """
        if self.check_win(self.COMP):
            score = +1
        elif self.check_win(self.HUMAN):
            score = -1
        else:
            score = 0

        return score

    def calc_moves(self, opt_board=None):
        """
        Determine which moves are still possible on default board
        or specified board
        """
        possible_moves = []
        # i = row
        # j = column
        if opt_board is None:
            for i in range(len(self.board)):
                for j in range(len(self.board[i])):
                    if self.board[i][j] == 0:
                        possible_moves.append([i, j])
            return possible_moves

        else:
            for i in range(len(opt_board)):
                for j in range(len(opt_board[i])):
                    if opt_board[i][j] == 0:
                        possible_moves.append([i, j])
            return possible_moves

    def valid_move(self, move):
        """
        Test to ensure a move by is not a repeat
        """
        row = move[0]
        column = move[1]
        if self.board[row][column] == 1 or self.board[row][column] == 2:
            return False
        else:
            return True

    def move(self, player, position):
        """
        Update board with a move
        """
        row = position[0]
        column = position[1]

        self.board[row][column] = player
        self.print_board()

    def get_board(self):
        """
        Return A COPY of the current board
        """
        return self.board.copy()

    def human_move(self):
        valid = False

        while not valid:
            row = int(input("Row: "))
            column = int(input("Column: "))
            if self.valid_move([row, column]):
                self.move(self.HUMAN, [row, column])
                valid = True
            else:
                print("Invalid move, retry\n")
                valid = False
        self.print_board()

    def random_move(self, player):
        my_move = random.choice(self.calc_moves())
        self.move(player, my_move)
        self.print_board()
        return my_move

    def random_game(self):
        human_moves = []
        comp_moves = []
        comp_turn = True
        while not self.game_over():
            if comp_turn:
                comp_moves.append(self.random_move(self.COMP))
                comp_turn = False
            else:
                human_moves.append(self.random_move(self.HUMAN))
                comp_turn = True
            if self.print:
                time.sleep(0.1)
        return human_moves, comp_moves, self.winner, self.board
