import pdb
import random

import numpy as np

MAX = True
MIN = False

nodes_explored = 0

class Position:
    def minimax(position, maximising, depth, lim):
        # get all the possible moves for this position
        global nodes_explored
        nodes_explored += 1

        if depth == lim:
            return 0

        currGrid = position.board[position.currGridN]
        possibleMoves = np.where(currGrid == 0)[0]

        for i in range(9):
            if Board.won_grid(position.board[i], 1):
                return (lim-depth+1)*100

            if Board.won_grid(position.board[i], 2):
                return (lim-depth+1)*(-100)

        if maximising:
            maxResult = -1000
            for move in possibleMoves:
                newBoard = np.copy(position.board)
                newBoard[position.currGridN][move] = 1
                newCurrGrid = move
                newPosition = Position(newBoard, newCurrGrid)
                maxResult = max(
                    maxResult,
                    Position.minimax(newPosition, False, depth + 1, lim),
                )
            return maxResult
        else:
            minResult = 1000
            for move in possibleMoves:
                newBoard = np.copy(position.board)
                newBoard[position.currGridN][move] = 2
                newCurrGrid = move
                newPosition = Position(newBoard, newCurrGrid)
                minResult = min(
                    minResult,
                    Position.minimax(newPosition, True, depth + 1, lim),
                )
            return minResult

    def __init__(self, board, currGridN):
        self.board = board
        self.currGridN = currGridN


class Board:

    def evaluate_grid(grid):
        """
        A static heuristic for a single grid of the 9x9 board.
        - Higher positive score favours player X more
        - More negative means favours player O more 

        The board's favourability for a particular player can be the sum 
        of the evaluation of the grids for most cases.
        """


    def won_grid(grid, player):

        # These indicies 'mask' combinations that are considered winning
        col1_win = np.array([0, 3, 6])
        col2_win = np.array([1, 4, 7])
        col3_win = np.array([2, 5, 8])
        row1_win = np.array([0, 1, 2])
        row2_win = np.array([3, 4, 5])
        row3_win = np.array([6, 7, 8])
        diag1_win = np.array([0, 4, 8])
        diag2_win = np.array([2, 4, 6])

        winning_positions = np.array(
            [
                col1_win,
                col2_win,
                col3_win,
                row1_win,
                row2_win,
                row3_win,
                diag1_win,
                diag2_win,
            ]
        )

        player_arrangement = np.where(grid == player)

        for winning_combination in winning_positions:
            mask = np.isin(winning_combination, player_arrangement)
            won = not (False in mask)
            if won:
                return True

        return False


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

        grid = self.board[self.currGrid]
        valid_places = np.where(grid == 0)[0]

        candidates = []
        for move in valid_places:
            new_board = np.copy(self.board)
            new_board[self.currGrid][move] = self.player
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

            print(nodes_explored)

            return external_move

        if self.player == 2:
            best_move = []
            best_score = 100000
            for x in candidates:
                x["value"] = Position.minimax(x["position"], True, 0, 3)
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
            print(nodes_explored)
            return external_move



