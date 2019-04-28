import numpy as np


class Board:

    # These class variables define winning combinations by the "mask" of
    # indices that a players move must cover in order to win a tic-tac-toe
    col1_win = np.array([0, 3, 6])
    col2_win = np.array([1, 4, 7])
    col3_win = np.array([2, 5, 8])
    row1_win = np.array([0, 1, 2])
    row2_win = np.array([3, 4, 5])
    row3_win = np.array([6, 7, 8])
    diag1_win = np.array([0, 4, 8])
    diag2_win = np.array([2, 4, 6])

    winning_combinations = np.array(
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

    def __init__(self, grid=None):
        if grid is None:
            self.grid = np.zeros((9, 9), dtype="int8")
        else:
            self.grid = grid

    def evaluate_board(self):
        heuristic = 0
        for i in range(9):
            subgrid_h = self.evaluate_subgrid(i)
            heuristic += subgrid_h

        return heuristic

    # this function needs to be blazing quick
    def evaluate_subgrid(self, subGridN):

        subgrid = self.grid[subGridN]
        tic_tac_toe = np.reshape(subgrid, (3, 3))

        x_heuristic = 0
        o_heuristic = 0

        for row in tic_tac_toe:
            if (row == 1).sum() == 1:
                x_heuristic += 1
            if (row == 1).sum() == 2:
                x_heuristic += 3

            if (row == 2).sum() == 1:
                o_heuristic += 1
            if (row == 2).sum() == 2:
                o_heuristic += 3

        for col in np.transpose(tic_tac_toe):
            if (col == 1).sum() == 1:
                x_heuristic += 1
            if (col == 1).sum() == 2:
                x_heuristic += 3

            if (col == 2).sum() == 1:
                o_heuristic += 1
            if (col == 2).sum() == 2:
                o_heuristic += 3

        return x_heuristic - o_heuristic

    def won_game(self, player):
        for i in range(9):
            if self.won_subgrid(i, player):
                return True

        return False

    def won_subgrid(self, subGridN, player):
        """
        Is a particular subgrid (tic-tac-toe) board considered winning?
        """
        subGrid = self.grid[subGridN]
        playerPos = np.where(subGrid == player)[0]

        for winning_combination in Board.winning_combinations:
            mask = np.isin(winning_combination, playerPos)
            won = not (False in mask)
            if won:
                return True

        return False

    # Utility Functions (Useful for debugging but do not offer useful logic
    # for the AI)
    def print_board_row(self, a, b, c, i, j, k):
        a = a - 1
        b = b - 1
        c = c - 1
        i = i - 1
        j = j - 1
        k = k - 1
        s = ["*", "X", "O"]
        print(
            " "
            + s[self.grid[a][i]]
            + " "
            + s[self.grid[a][j]]
            + " "
            + s[self.grid[a][k]]
            + " | "
            + s[self.grid[b][i]]
            + " "
            + s[self.grid[b][j]]
            + " "
            + s[self.grid[b][k]]
            + " | "
            + s[self.grid[c][i]]
            + " "
            + s[self.grid[c][j]]
            + " "
            + s[self.grid[c][k]]
        )

    def print_board(self):
        self.print_board_row(1, 2, 3, 1, 2, 3)
        self.print_board_row(1, 2, 3, 4, 5, 6)
        self.print_board_row(1, 2, 3, 7, 8, 9)
        print(" ------+-------+------")
        self.print_board_row(4, 5, 6, 1, 2, 3)
        self.print_board_row(4, 5, 6, 4, 5, 6)
        self.print_board_row(4, 5, 6, 7, 8, 9)
        print(" ------+-------+------")
        self.print_board_row(7, 8, 9, 1, 2, 3)
        self.print_board_row(7, 8, 9, 4, 5, 6)
        self.print_board_row(7, 8, 9, 7, 8, 9)
        print()
