import numpy as np


class Board:

    def __init__(self, board=None):
        """
        creates an initially empty board
        """
        if board is None:
            self.board = np.zeros((9, 9), dtype="int8")
        else:
            self.board = board

        # These indicies 'mask' combinations that are considered winning
        col1_win = np.array([0, 3, 6])
        col2_win = np.array([1, 4, 7])
        col3_win = np.array([2, 5, 8])
        row1_win = np.array([0, 1, 2])
        row2_win = np.array([3, 4, 5])
        row3_win = np.array([6, 7, 8])
        diag1_win = np.array([0, 4, 8])
        diag2_win = np.array([2, 4, 6])

        self.winning_combinations = np.array(
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

    def evaluate_board(self):
        board_heuristic = 0
        for grid in self.board:
            board_heuristic += Board.evaluate_grid(grid)

        return board_heuristic

    def evaluate_grid(grid):
        """
        A static heuristic for a single grid of the 9x9 board.
        - Higher positive score favours player X more
        - More negative means favours player O more 

        The board's favourability for a particular player can be the sum 
        of the evaluation of the grids for most cases.
        """

        available_moves = np.where(grid == 0)[0]

        heuristic = 0

        for move in available_moves:
            potential_grid = np.copy(grid)
            potential_grid[move] = 1
            if Board.won_grid(potential_grid, 1):
                heuristic += 1

            potential_grid[move] = 2
            if Board.won_grid(potential_grid, 1):
                heuristic -= 1

        return heuristic

    def won_grid(self, grid, player):

        player_arrangement = np.where(grid == player)

        for winning_combination in self.winning_combinations:
            mask = np.isin(winning_combination, player_arrangement)
            won = not (False in mask)
            if won:
                return True

        return False
