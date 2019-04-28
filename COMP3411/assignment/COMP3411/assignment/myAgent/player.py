import random

import numpy as np

from position import Position, MIN_HEURISTIC, MAX_HEURISTIC, MOVE_TO_INDEX, INDEX_TO_MOVE
from board import Board

DEBUG = False


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
                    False, 2, MIN_HEURISTIC, MAX_HEURISTIC)
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
                candidate["value"] = candidate["position"].minimax(
                    True, 5, MIN_HEURISTIC, MAX_HEURISTIC)
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
