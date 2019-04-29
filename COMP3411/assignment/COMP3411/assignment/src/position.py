import numpy as np

from board import Board

MAX_HEURISTIC = 10000
MIN_HEURISTIC = -MAX_HEURISTIC

DEBUG = False
PRUNE = True


def MOVE_TO_INDEX(move):
    return move - 1


def INDEX_TO_MOVE(index):
    return index + 1


class Position:

    def __init__(self, board, currGridN):
        self.board = board
        self.currGridN = currGridN

    def set_curr_grid(self, gridN):
        gridN = MOVE_TO_INDEX(gridN)
        self.currGridN = gridN

    def place(self, move, player):
        move = MOVE_TO_INDEX(move)
        self.board.grid[self.currGridN][move] = player
        self.currGridN = move

    def get_valid_moves(self):
        subGrid = self.board.grid[self.currGridN]
        possibleMoves = np.where(subGrid == 0)[0]
        return possibleMoves

    def minimax(self, maximise, depth, alpha, beta):

        evaluation = self.board.evaluate_board()

        if depth == 0:
            return evaluation

        if self.board.won_game(1):
            if DEBUG:
                print("CLAIMING VICTORY for X???")
                self.board.print_board()
            return MAX_HEURISTIC + depth
        elif self.board.won_game(2):
            if DEBUG:
                print("CLAIMING VICTORY for O???")
                self.board.print_board()
            return MIN_HEURISTIC - depth

        possibleMoves = self.get_valid_moves()

        if maximise:
            maxResult = MIN_HEURISTIC
            for move in possibleMoves:

                # make the move
                self.board.grid[self.currGridN][move] = 1
                oldGridN = self.currGridN
                self.currGridN = move

                maxResult = max(maxResult,
                                self.minimax(False, depth-1, alpha, beta))
                # undo the move
                self.currGridN = oldGridN
                self.board.grid[self.currGridN][move] = 0

                if PRUNE:
                    alpha = max(alpha, maxResult)
                    if alpha >= beta:
                        break
            return maxResult

        else:
            minResult = MAX_HEURISTIC
            for move in possibleMoves:

                # make the move
                self.board.grid[self.currGridN][move] = 2
                oldGridN = self.currGridN
                self.currGridN = move

                minResult = min(minResult,
                                self.minimax(True, depth-1, alpha, beta))

                # undo the move
                self.currGridN = oldGridN
                self.board.grid[self.currGridN][move] = 0

                if PRUNE:
                    beta = min(beta, minResult)
                    if alpha >= beta:
                        break
            return minResult
