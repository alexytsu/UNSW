import random
import pdb
import time

import numpy as np

from position import (
    Position,
    MIN_HEURISTIC,
    MAX_HEURISTIC,
    MOVE_TO_INDEX,
    INDEX_TO_MOVE,
)
from board import Board

DEBUG = False

BASE_SEARCH_DEPTH = 2 # never evaluate worse than this depth even under time pressure


class Player:
    def __init__(self, currPosition: Position):
        self.currPosition = currPosition
        self.moves_played = 0
        self.search_depth = 0
        self.clock_available = (
            28
        )  # give us some leeway for initialisation + error overhead
        self.previous_time = 0

    def set_player(self, playerToken):
        if playerToken == "x":
            self.player = 1
            self.opposition = -1
            self.moves_played += 1
        elif playerToken == "o":
            self.player = -1
            self.opposition = 1

    def play_minimax_move(self):
        """ 
        Choose the best move for the player find all possible moves to make. Choose the move
        that leads to the worst response from the opponent assuming perfect play
        """

        start = time.clock()
        self.moves_played += 1 # store for debugging

        valid_moves = self.currPosition.get_valid_moves()

        candidates = []
        # Generate a new "Position" for each possible move to evaluate it
        for move in valid_moves:
            newGrid = np.copy(self.currPosition.board.grid)
            newGrid[self.currPosition.currGridN][move] = self.player
            newBoard = Board(newGrid)
            newPosition = Position(newBoard, move)
            candidates.append({"move": move, "position": newPosition})

        if self.player == 1:  # we are player x
            best_move = []
            best_score = MIN_HEURISTIC

            # examine all cnadidate moves
            for candidate in candidates:

                # play it out to the dynamic depth
                candidate["value"] = candidate["position"].minimax(
                    False,
                    BASE_SEARCH_DEPTH + self.search_depth,  # dynamic depth
                    2 * MIN_HEURISTIC,
                    2 * MAX_HEURISTIC,
                )
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

            self.currPosition.place(external_move, self.player)

        if self.player == -1:  # we are player o
            best_move = []
            best_score = MAX_HEURISTIC
            for candidate in candidates:

                # evaluate the candidate move
                candidate["value"] = candidate["position"].minimax(
                    True,
                    BASE_SEARCH_DEPTH + self.search_depth,
                    2 * MIN_HEURISTIC,
                    2 * MAX_HEURISTIC,
                )

                # evaluate it compared to previous moves
                if candidate["value"] < best_score:
                    best_move = [(candidate["move"])]
                    best_score = candidate["value"]
                elif candidate["value"] == best_score:
                    best_move.append(candidate["move"])

            try:
                chosen_move = random.choice(best_move)
            except:
                chosen_move = random.choice(valid_moves)

            external_move = INDEX_TO_MOVE(chosen_move)

            self.currPosition.place(external_move, self.player)

        # Let's prepare for the next move and update some bookkeeping
        time_taken = time.clock() - start

        # store
        self.previous_time = time_taken

        # update our time keeping
        self.clock_available += 2  # we gain 2 seconds for every move made 
        self.clock_available -= time_taken  # we used some time

        # update our depth for the next move
        if self.clock_available - self.previous_time * 90 > 0:
            # in early stages we might need a more aggressive deepening of the search depth
            self.search_depth += 2

        elif self.clock_available - self.previous_time * 10 > 0:
            # if we will not timeout by increasing the search depth, do it
            self.search_depth += 1

        if self.clock_available - self.previous_time * 1.4 < 0:
            # if maintaining the current search depth may timeout, decrease it for safety
            self.search_depth -= 1

        print("Search depth", self.search_depth)

        return external_move
