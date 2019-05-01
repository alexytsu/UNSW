import numpy as np

from board import Board

MAX_HEURISTIC = 10000
MIN_HEURISTIC = -MAX_HEURISTIC

DEBUG = False
PRUNE = True


def MOVE_TO_INDEX(move):
    return move - 1


def INDEX_TO_MOVE(index):
    return index + 1


class Position:

    def __init__(self, board, currGridN):
        self.board = board
        self.currGridN = currGridN
        self.oldGridN = 0
        self.killer_max_moves = {}
        self.killer_min_moves = {}

    def set_curr_grid(self, gridN):
        gridN = MOVE_TO_INDEX(gridN)
        self.currGridN = gridN

    def place(self, move, player):
        move = MOVE_TO_INDEX(move)
        self.board.grid[self.currGridN][move] = player
        self.oldGridN = self.currGridN
        self.currGridN = move
        print(f"From board {self.oldGridN} played {move}")

    def get_valid_moves(self):
        subGrid = self.board.grid[self.currGridN]
        possibleMoves = np.where(subGrid == 0)[0]
        return possibleMoves

    def minimax(self, maximise, depth, alpha, beta):

        if depth == 0:
            evaluation = self.board.evaluate_board(self.currGridN)
            return evaluation

        # to check if we are a terminal node we only need to check the subgrid
        # that was last played in when returning the heuristic, we also weight
        # earlier victories in the search tree more than later ones by adding
        # or subtracting the current depth as necessary
        if self.board.won_subgrid(self.oldGridN, 1):
            return MAX_HEURISTIC + depth
        elif self.board.won_subgrid(self.oldGridN, -1):
            return MIN_HEURISTIC - depth

        possibleMoves = self.get_valid_moves()

        subgrid = self.board.grid[self.currGridN]
        grid_hash = subgrid.tobytes()

        if maximise:
            maxResult = MIN_HEURISTIC

            best_move = None
            
            # play the killer move first
            if grid_hash in self.killer_max_moves:
                best_move = self.killer_max_moves[grid_hash]["move"]

            if best_move is not None:
                location = np.where(possibleMoves == best_move)[0][0]
                possibleMoves = np.roll(possibleMoves, location+1)

            for move in possibleMoves:

                # make the move
                self.board.grid[self.currGridN][move] = 1
                memOldGridN = self.oldGridN
                self.oldGridN = self.currGridN
                self.currGridN = move

                # minimax evaluation
                curr_eval = self.minimax(False, depth-1, alpha, beta)

                if curr_eval > maxResult:
                    maxResult = curr_eval

                # update our killer move if necessary
                if grid_hash in self.killer_max_moves:
                    if curr_eval > self.killer_max_moves[grid_hash]["val"]:
                        self.killer_max_moves[grid_hash] = {"move": move, "val": curr_eval}
                else:
                    self.killer_max_moves[grid_hash] = {"move": move, "val": curr_eval}

                # undo the move
                self.currGridN = self.oldGridN
                self.board.grid[self.currGridN][move] = 0

                self.oldGridN = memOldGridN

                if PRUNE:
                    alpha = max(alpha, maxResult)
                    if alpha >= beta:
                        break
            return maxResult

        else:
            minResult = MAX_HEURISTIC

            best_move = None
            # play the killer move first
            if grid_hash in self.killer_min_moves:
                best_move = self.killer_min_moves[grid_hash]["move"]

            if best_move is not None:
                location = np.where(possibleMoves == best_move)[0][0]
                possibleMoves = np.roll(possibleMoves, location+1)

            for move in possibleMoves:

                # make the move
                self.board.grid[self.currGridN][move] = -1
                memOldGridN = self.oldGridN
                self.oldGridN = self.currGridN
                self.currGridN = move

                # minimax evaluation
                curr_eval = self.minimax(True, depth-1, alpha, beta)

                if curr_eval < minResult:
                    minResult = curr_eval

                # update our killer move if necessary
                if grid_hash in self.killer_min_moves:
                    if curr_eval < self.killer_min_moves[grid_hash]["val"]:
                        self.killer_min_moves[grid_hash] = {"move": move, "val": curr_eval}
                else:
                    self.killer_min_moves[grid_hash] = {"move": move, "val": curr_eval}

                # undo the move
                self.currGridN = self.oldGridN
                self.board.grid[self.currGridN][move] = 0

                self.oldGridN = memOldGridN

                if PRUNE:
                    beta = min(beta, minResult)
                    if alpha >= beta:
                        break
            return minResult
