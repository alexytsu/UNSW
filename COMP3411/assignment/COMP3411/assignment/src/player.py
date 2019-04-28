import random
import pdb

import numpy as np

from position import Position, MIN_HEURISTIC, MAX_HEURISTIC, MOVE_TO_INDEX, INDEX_TO_MOVE
from board import Board

DEBUG = False
SEARCH_DEPTH = 4


class Player:

    def __init__(self, currPosition):
        self.currPosition = currPosition
        self.moves_played = 0

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
        self.moves_played += 1
        print("play_minimax_move(): playing a new move")

        valid_moves = self.currPosition.get_valid_moves()
        candidates = []

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
                    False, SEARCH_DEPTH, MIN_HEURISTIC, MAX_HEURISTIC)
                if candidate["value"] > best_score:
                    best_move = [(candidate["move"])]
                    best_score = candidate["value"]
                elif candidate["value"] == best_score:
                    best_move.append(candidate["move"])

            chosen_move = random.choice(best_move)
            external_move = INDEX_TO_MOVE(chosen_move)

            if DEBUG:
                print("===== CANDIDATES =====")
                for x in candidates:
                    print(x)
                print("==== BEST MOVES ====")
                print(best_move)
                print("CHOSEN:", chosen_move)

            self.currPosition.place(external_move, self.player)
            return external_move

        if self.player == 2:
            best_move = []
            best_score = MAX_HEURISTIC
            for candidate in candidates:

                """
                make the candidate move
                """
                candidate["value"] = candidate["position"].minimax(
                    True, SEARCH_DEPTH, MIN_HEURISTIC, MAX_HEURISTIC)

                """
                evaluate it compared to previous moves
                """
                if candidate["value"] < best_score:
                    best_move = [(candidate["move"])]
                    best_score = candidate["value"]
                elif candidate["value"] == best_score:
                    best_move.append(candidate["move"])

            chosen_move = random.choice(best_move)

            if DEBUG:
                print("\n\n\nCURRPOSITON")
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

            return external_move


if __name__ == "__main__":

    # FAILED TO CHOOSE CORRECT MOVE (first noticed in commit 686c2e7)
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
