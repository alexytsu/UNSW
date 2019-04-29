import random
import pdb
import time

import numpy as np

from position import Position, MIN_HEURISTIC, MAX_HEURISTIC, MOVE_TO_INDEX, INDEX_TO_MOVE
from board import Board

DEBUG = False
SEARCH_DEPTH = 2


class Player:

    def __init__(self, currPosition):
        self.currPosition = currPosition
        self.moves_played = 0
        self.search_depth = 0
        self.clock_available = 25  # give us some leeway
        self.previous_time = 0

    def set_player(self, playerToken):
        if playerToken == 'x':
            self.player = 1
            self.opposition = 2
            self.moves_played += 1
        elif playerToken == 'o':
            self.player = 2
            self.opposition = 1

        print("We are player:", playerToken, "\n\tindex:", self.player)

    def play_minimax_move(self):
        start = time.clock()
        self.moves_played += 1

        valid_moves = self.currPosition.get_valid_moves()
        candidates = []

        external_move = 0

        for move in valid_moves:
            newGrid = np.copy(self.currPosition.board.grid)
            newGrid[self.currPosition.currGridN][move] = self.player
            newBoard = Board(newGrid)
            newPosition = Position(newBoard, move)
            candidates.append({"move": move, "position": newPosition})

        if self.player == 1:
            best_move = []
            best_score = MIN_HEURISTIC
            for candidate in candidates:
                candidate["value"] = candidate["position"].minimax(
                    False, 2 + self.search_depth, 2*MIN_HEURISTIC, 2*MAX_HEURISTIC)
                if candidate["value"] > best_score:
                    best_move = [(candidate["move"])]
                    best_score = candidate["value"]
                elif candidate["value"] == best_score:
                    best_move.append(candidate["move"])

            try:
                chosen_move = random.choice(best_move)
            except:
                chosen_move = random.choice(valid_moves)

            external_move = INDEX_TO_MOVE(chosen_move)

            if DEBUG:
                print("===== CANDIDATES =====")
                for x in candidates:
                    print(x)
                print("==== BEST MOVES ====")
                print(best_move)
                print("CHOSEN:", chosen_move)

            self.currPosition.place(external_move, self.player)

        if self.player == 2:
            best_move = []
            best_score = MAX_HEURISTIC
            for candidate in candidates:

                """
                make the candidate move
                """
                candidate["value"] = candidate["position"].minimax(
                    True, 2 + self.search_depth, 2*MIN_HEURISTIC, 2*MAX_HEURISTIC)

                """
                evaluate it compared to previous moves
                """
                if candidate["value"] < best_score:
                    best_move = [(candidate["move"])]
                    best_score = candidate["value"]
                elif candidate["value"] == best_score:
                    best_move.append(candidate["move"])

            try:
                chosen_move = random.choice(best_move)
            except:
                chosen_move = random.choice(valid_moves)

            if DEBUG:
                print("\n\n\nCURRPOSITON about to play O")
                print("Curr Grid: ", self.currPosition.currGridN)
                self.currPosition.board.print_board()
                print("===== CANDIDATES =====")
                for x in candidates:
                    print(x)
                print("==== BEST MOVES ====")
                print(best_move)
                print("CHOSEN:", chosen_move)

            external_move = INDEX_TO_MOVE(chosen_move)

            self.currPosition.place(external_move, self.player)

        time_taken = time.clock() - start
        print("TimeTaken:", time_taken)

        # store
        self.previous_time = time_taken

        # update our time keeping
        self.clock_available += 2
        self.clock_available -= time_taken

        # update our depth
        if self.clock_available - self.previous_time * 90 > 0:
            print(
                f"DOUBLE Increasing search depth to {self.search_depth + 2 } with {self.clock_available} on the clock and previous move {self.previous_time}")
            self.search_depth += 2

        elif self.clock_available - self.previous_time * 10 > 0:
            print(
                f"Increasing search depth to {self.search_depth +1 } with {self.clock_available} on the clock and previous move {self.previous_time}")
            self.search_depth += 1

        if self.clock_available - self.previous_time * 1.5 < 0:
            print(
                f"Decreasing search depth to {self.search_depth - 1 } with {self.clock_available} on the clock and previous move {self.previous_time}")
            self.search_depth -= 1

        return external_move


if __name__ == "__main__":

    # FAILED TO CHOOSE CORRECT MOVE (first noticed in commit 686c2e7)
    """
    # Fix: reverse the depth for winning moves on X and O
    b1 = Board()
    b1.grid[0][np.array([1, 2, 7])] = 1
    b1.grid[0][np.array([6])] = 2
    b1.grid[1][np.array([3, 5])] = 1
    b1.grid[1][0] = 2
    b1.grid[2][0] = 2
    b1.grid[3][np.array([5, 8])] = 2
    b1.grid[5][6] = 1
    b1.grid[5][0] = 2
    b1.grid[6][6] = 1
    b1.grid[6][np.array([0, 8])] = 2
    b1.grid[7][1] = 2
    b1.grid[8][np.array([0, 3])] = 1
    b1.print_board()

    p1 = Position(b1, 0)

    pl1 = Player(p1)
    pl1.set_player('x')

    pl1.play_minimax_move()

    pl1.currPosition.board.print_board()
    """

    # Chose a losing move
    """
    CURRPOSITON
    Curr Grid:  3
    * X X | X * * | * * *
    * * * | * * * | X O *
    * O * | O * O | X * *
    ------+-------+------
    * * * | O * * | * * O
    * * * | * X * | * * *
    * * O | * X * | * * *
    ------+-------+------
    * * * | * O * | O X *
    * O X | * * * | X * *
    * * X | * * X | O * *

    == == = CANDIDATES == == =
    {'move': 0, 'position': < position.Position object at 0x7f1354b21f60 > , 'value': 1}
    {'move': 1, 'position': < position.Position object at 0x7f1354b219e8 > , 'value': 2}
    {'move': 2, 'position': < position.Position object at 0x7f1354b21b70 > , 'value': 1}
    {'move': 3, 'position': < position.Position object at 0x7f1354b21c18 > , 'value': 2}
    {'move': 4, 'position': < position.Position object at 0x7f1354b21da0 > , 'value': 1}
    {'move': 5, 'position': < position.Position object at 0x7f1354b21e10 > , 'value': 2}
    {'move': 6, 'position': < position.Position object at 0x7f1354b21e80 > , 'value': 1}
    {'move': 7, 'position': < position.Position object at 0x7f1354b21940 > , 'value': 2}
    == == BEST MOVES == ==
    [0, 2, 4, 6]
    CHOSEN: 2
    """

    b2 = Board()
    g2 = b2.grid
    g2[0][1] = 1
    g2[0][2] = 1
    g2[0][7] = 2

    g2[1][0] = 1
    g2[1][6] = 2
    g2[1][8] = 2

    g2[2][3] = 1
    g2[2][6] = 1
    g2[2][4] = 2

    g2[3][8] = 2

    g2[4][4] = 1
    g2[4][7] = 1
    g2[4][0] = 2

    g2[5][2] = 2

    g2[6][5] = 1
    g2[6][8] = 1
    g2[6][4] = 2

    g2[7][8] = 1
    g2[7][1] = 2

    g2[8][1] = 1
    g2[8][3] = 1
    g2[8][0] = 2
    g2[8][6] = 2

    b2.print_board()

    pos2 = Position(b2, 3)
    pl2 = Player(pos2)
    pl2.set_player('o')

    pl2.play_minimax_move()
