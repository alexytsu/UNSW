import numpy as np

DEBUG = True


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

        self.lookup = {}
        self.won_subgrids = {}

    def evaluate_board(self, biased):
        heuristic = 0
        for i in range(9):
            subgrid_h = self.evaluate_subgrid(i)
            if i == biased:
                heuristic += subgrid_h
            heuristic += subgrid_h

        return heuristic

    # this function needs to be blazing quick
    def evaluate_subgrid(self, subGridN):

        subgrid = self.grid[subGridN]
        lookup_key = subgrid.tobytes()
        if lookup_key in self.lookup:
            return self.lookup[lookup_key]

        heuristic = 0

        for triplet in self.winning_combinations:
            mini_heuristic = 0
            for index in triplet:
                if subgrid[index] == 1:
                    mini_heuristic += 1
                    if mini_heuristic == 0:
                        break
                if subgrid[index] == -1:
                    mini_heuristic -= 1
                    if mini_heuristic == 0:
                        break
            if abs(mini_heuristic) >= 2:
                heuristic += 3*mini_heuristic
            else:
                heuristic += mini_heuristic

        reverse_key = (-subgrid).tobytes()
        self.lookup[lookup_key] = heuristic
        self.lookup[reverse_key] = -heuristic

        return heuristic

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

        key = playerPos.tobytes()
        if key in self.won_subgrids:
            return self.won_subgrids[key]

        for winning_combination in Board.winning_combinations:
            mask = np.isin(winning_combination, playerPos)
            won = not (False in mask)
            if won:
                self.won_subgrids[key] = True
                return True

        self.won_subgrids[key] = False
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


if __name__ == "__main__":
    board = Board()
    subGrid = board.grid[7]

    subGrid[np.array([2, 5, 8])] = 2
    subGrid[np.array([3, 6])] = 1

    print(board.won_game(1))
    print(board.won_game(2))
