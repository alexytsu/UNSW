import numpy as np
from board import Board


class Position:
    def minimax(position, maximising, depth, lim):
        # get all the possible moves for this position

        if depth == lim:
            return position.board.evaluate_board()

        currGrid = position.board.board[position.currGridN]
        possibleMoves = np.where(currGrid == 0)[0]

        for i in range(9):
            if position.board.won_grid(position.board.board[i], 1):
                return (lim-depth+1)*100

            if position.board.won_grid(position.board.board[i], 2):
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
                newBoard = Board(newBoard)
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
