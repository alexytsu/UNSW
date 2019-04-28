import numpy as np

from board import Board

MAX_HEURISTIC = 10000
MIN_HEURISTIC = -MAX_HEURISTIC


def MOVE_TO_INDEX(move):
    return move - 1


def INDEX_TO_MOVE(index):
    return index + 1


class Position:

    def __init__(self, board, currGridN):
        self.board = board
        self.currGridN = 0

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

    def minimax(self, maximise, depth):

        if depth == 0:
            evaluation = self.board.evaluate_board()
            return evaluation

        if self.board.won_game(1):
            return MAX_HEURISTIC
        elif self.board.won_game(2):
            return MIN_HEURISTIC

        possibleMoves = self.get_valid_moves()

        if maximise:
            maxResult = MIN_HEURISTIC
            for move in possibleMoves:
                newGrid = np.copy(self.board.grid)
                newGrid[self.currGridN][move] = 1
                newBoard = Board(newGrid)
                newPosition = Position(newBoard, move)
                maxResult = max(maxResult, newPosition.minimax(False, depth-1))
            return maxResult

        else:
            minResult = MAX_HEURISTIC
            for move in possibleMoves:
                newGrid = np.copy(self.board.grid)
                newGrid[self.currGridN][move] = 2
                newBoard = Board(newGrid)
                newPosition = Position(newBoard, move)
                minResult = min(minResult, newPosition.minimax(True, depth-1))
            return minResult
