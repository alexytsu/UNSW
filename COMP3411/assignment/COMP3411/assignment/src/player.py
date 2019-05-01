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
            24
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
        self.moves_played += 1  # store for debugging

        valid_moves = self.currPosition.get_valid_moves()
        chosen_move = valid_moves[0]  # a default failback in weird cases?

        if self.player == 1:  # set defaults that will undoubtedly be overidden
            best_score = MIN_HEURISTIC
            maximise = True
        elif self.player == -1:
            best_score = MAX_HEURISTIC
            maximise = False

        for move in valid_moves:

            # make the move 
            """
            playing and then undoing the move is far more performant than making a deep copy in memory
            """
            self.currPosition.board.grid[self.currPosition.currGridN][move] = self.player
            memOldGridN = self.currPosition.oldGridN
            self.currPosition.oldGridN = self.currPosition.currGridN
            self.currPosition.currGridN = move

            # play it out to the dynamic depth
            current_score = self.currPosition.minimax(
                not maximise,  # the maximiser takes the MAX of all the minimizer's choices
                BASE_SEARCH_DEPTH + self.search_depth,  # dynamic depth
                2 * MIN_HEURISTIC,
                2 * MAX_HEURISTIC,
            )

            self.currPosition.currGridN = self.currPosition.oldGridN
            self.currPosition.board.grid[self.currPosition.currGridN][move] = 0
            self.currPosition.oldGridN = memOldGridN

            if maximise: #track the running max score
                if current_score > best_score:
                    chosen_move = move
                    best_score = current_score
            else: # track the running min score and the move to achieve it
                if current_score < best_score:
                    chosen_move = move
                    best_score = current_score

        # update the currPosition by playing the chosen move
        external_move = INDEX_TO_MOVE(chosen_move)
        self.currPosition.place(external_move, self.player)

        # Let's prepare for the next move and update some bookkeeping
        time_taken = time.clock() - start

        # store
        self.previous_time = time_taken

        # update our time keeping
        self.clock_available += 1.5  # we gain 2 seconds for every move made 
        self.clock_available -= time_taken  # we used some time

        # update our depth for the next move
        if self.clock_available - self.previous_time * 90 > 0:
            # in early stages we might need a more aggressive deepening of the search depth
            self.search_depth += 2

        elif self.clock_available - self.previous_time * 10 > 0:
            # if we will not timeout by increasing the search depth, do it
            self.search_depth += 1

        if self.clock_available - self.previous_time * 2 < 0:
            # if maintaining the current search depth may timeout, decrease it for safety
            self.search_depth -= 1

        print("Search depth", self.search_depth)

        return external_move
