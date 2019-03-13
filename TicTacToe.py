import random
import os
import time

class Tic:
    """
    Tic Tac Toe!
    """
    def __init__(self):
        self.new_game()
        self.print_board()
        self.HUMAN = 1
        self.COMP = 2

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
        os.system("cls")
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
        # Check win condition
        if self.check_win(self.COMP):
            print("Computer Wins!!")
            time.sleep(display_time)
            self.new_game()
            return True
        elif self.check_win(self.HUMAN):
            print("Human Wins!!")
            time.sleep(display_time)
            self.new_game()
            return True
        elif 0 not in self.board[0]:
            if 0 not in self.board[1]:
                if 0 not in self.board[2]:
                    print("Stalemate!!")
                    time.sleep(display_time)
                    self.new_game()
                    return True

    def calc_moves(self):
        """
        Determine which moves are still possible
        """
        possible_moves = []
        # i = row
        # j = column
        for i in range(len(self.board)):
            for j in range(len(self.board[i])):
                if self.board[i][j] == 0:
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

    def getBoard(self):
        """
        Return the current board
        """
        return self.board

    def human_move(self):
        valid = False

        while not valid:
            row = int(input("Row: "))
            column = int(input("Column: "))
            if self.valid_move([row, column]):
                self.move(HUMAN, [row, column])
                valid = True
            else:
                print("Invalid move, retry\n")
                valid = False
        self.print_board()

    def random_move(self, player):
        my_move = random.choice(self.calc_moves())
        self.move(player, my_move)
        self.print_board()

    def random_game(self):
        comp_turn = True
        while not self.game_over():
            if comp_turn:
                self.random_move(self.COMP)
                comp_turn = False
            else:
                self.random_move(self.HUMAN)
                comp_turn = True
            time.sleep(0.5)
