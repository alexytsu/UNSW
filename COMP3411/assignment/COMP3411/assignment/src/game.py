import pdb
import random

import numpy as np

from position import Position
from board import Board

MAX = True
MIN = False

nodes_explored = 0


class Game:
    """
    Each game has a "board" which consists of 9 3x3 grids.
    Each grid is a traditional tic-tac-toe board.
    """

    # Class helper functions
    def index_to_move(index):
        """
        converts between our internal representation of the board
        and the server's indexing of the board
        """
        return index + 1

    def move_to_index(move):
        """
        converts an index from the server's format to our internal 
        0-indexed representation (arrays start from 0!)
        """
        return move - 1

    def __init__(self, board=None):
        """
        creates an initially empty board
        """
        self.moves_played = 0
        if board is None:
            self.board = np.zeros((9, 9), dtype="int8")
        else:
            self.board = board

    def print_board_row(board, a, b, c, i, j, k):
        a = a - 1
        b = b - 1
        c = c - 1
        i = i - 1
        j = j - 1
        k = k - 1
        s = ["*", "X", "O"]
        print(
            " "
            + s[board[a][i]]
            + " "
            + s[board[a][j]]
            + " "
            + s[board[a][k]]
            + " | "
            + s[board[b][i]]
            + " "
            + s[board[b][j]]
            + " "
            + s[board[b][k]]
            + " | "
            + s[board[c][i]]
            + " "
            + s[board[c][j]]
            + " "
            + s[board[c][k]]
        )

    def print_board(self):
        Game.print_board_row(self.board, 1, 2, 3, 1, 2, 3)
        Game.print_board_row(self.board, 1, 2, 3, 4, 5, 6)
        Game.print_board_row(self.board, 1, 2, 3, 7, 8, 9)
        print(" ------+-------+------")
        Game.print_board_row(self.board, 4, 5, 6, 1, 2, 3)
        Game.print_board_row(self.board, 4, 5, 6, 4, 5, 6)
        Game.print_board_row(self.board, 4, 5, 6, 7, 8, 9)
        print(" ------+-------+------")
        Game.print_board_row(self.board, 7, 8, 9, 1, 2, 3)
        Game.print_board_row(self.board, 7, 8, 9, 4, 5, 6)
        Game.print_board_row(self.board, 7, 8, 9, 7, 8, 9)
        print()

    def evaluate_grid(self, grid_n):
        """
        returns a heuristic for the grid
        """
        pass

    def set_player(self, player):
        if player == "o":
            self.player = 2
            self.opposition = 1
        elif player == "x":
            self.player = 1
            self.opposition = 2
        print("We are player", player, "with index:", self.player)

    def set_curr_grid(self, grid_n):
        grid_n = Game.move_to_index(grid_n)
        self.currGrid = grid_n

    def place(self, pos, player):
        """
        grid_n & pos passed in from the server perspective
        """
        pos = Game.move_to_index(pos)
        self.board[self.currGrid][pos] = player
        self.currGrid = pos

    def play_random_move(self):
        # choose a random move from the curr grid
        grid = self.board[self.currGrid]
        valid_places = np.where(grid == 0)[0]
        index = valid_places[0]
        external_move = Game.index_to_move(index)
        self.place(external_move, self.player)
        return external_move

    def play_minimax_move(self):

        self.moves_played += 1

        grid = self.board[self.currGrid]
        valid_places = np.where(grid == 0)[0]

        candidates = []
        for move in valid_places:
            new_board = np.copy(self.board)
            new_board[self.currGrid][move] = self.player
            new_board = Board(new_board)
            new_position = Position(new_board, move)
            candidates.append({"move": move, "position": new_position})

        if self.player == 1:
            best_move = []
            best_score = -100000
            for x in candidates:
                x["value"] = Position.minimax(x["position"], False, 0, 2)
                if x["value"] >= best_score:
                    if(x["value"] == best_score):
                        try:
                            best_move.append(x["move"])
                        except:
                            print(best_move)
                        continue
                    best_score = x["value"]
                    best_move = [x["move"]]

            chosen_move = random.choice(best_move)
            external_move = Game.index_to_move(chosen_move)
            self.place(external_move, self.player)

            print("candidates", candidates)
            return external_move

        if self.player == 2:
            best_move = []
            best_score = 100000
            for x in candidates:
                x["value"] = Position.minimax(x["position"], True, 0, 2)
                if x["value"] <= best_score:
                    if(x["value"] == best_score):
                        try:
                            best_move.append(x["move"])
                        except:
                            print("Error:", best_move)
                        continue
                    best_score = x["value"]
                    best_move = [x["move"]]

            chosen_move = random.choice(best_move)
            external_move = Game.index_to_move(chosen_move)
            self.place(external_move, self.player)
            print("candidates", candidates)

            return external_move
