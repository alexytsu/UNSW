#!/usr/bin/python3
import socket
import sys
import pdb

import numpy as np
from player import Player
from position import Position
from board import Board

"""
Briefly describe how your program works, including any algorithms and data
structures employed, and explain any design decisions you made along the way.

*Note*: This section will provide a brief summary only. For implementation 
details and further explanation, see each module's inline docstrings.

===== Data structures =====

Class<Board>: represents a 9Board TicTacToe game. It contains within it a "grid"
which is a numpy (9,9) array. Each subgrid (a single TTT game) is encoded within 
a one-dimensional 9 length array. Empty spaces within subgrids are encoded as 0's,
X's as 1's and O's as 2's.
    - The Board class is responsible for checking whether subgrids/grids are considered
    winning as well as performing static evaluation on individual grids etc. for the 
    purposes of heuristic calculation.

Class<Position>: represents a game state. Game state is not only defined by what
the board looks like. Rather the "current grid" where the next player is required
make their move must also be encoded. Therefore the Position class encapsulates
this state along with a Board class.
    - The Position class is reponsible for calculating the minimax evaluation of the game
    state since moves are played with the "current grid" taken into account.

Class<Player>: represents an agent who is playing the game. It contains the 
current position, manages the state of the current position by receiving and playing moves.
It also is aware and keeps an internal state tracking the available time for the agent 
before a loss by timeout. This allows it to control the depth to which the Position class
calculates the minimax evaluation. 
    - The Player class is reponsible for calculating the best move to play at any 
    given position for a given player, keeping track of timing etc. and generally maximising
    the "real game" performance of the agent.

===== Algorithms =====

minimax(): A standard minimax algorithm set up on the 9Board game. The game has been
parameterised such that player X always seeks to maximise the heuristic evaluation of the board
and player O always seeks to minimise the heurisitc evaluation of the board. 
    - For more details on how the heuristic function works see the inline documentation
    in the Board class. 
Minimax works by considering all possible game states to a certain depth from a given position.
It seeks to maximise the outcomes for the player whilst accounting for perfect/best-case play
by the opponent. When we are often cutting our search short of terminal ("decisively won or lost")
positions, it is important that we have an accurate/performant heuristic function. 

heuristic function: See documentation in the Board class.

===== Optimisations =====

We will detail some of the most significant and crucial optimisations in terms of algorithm complexity
and data-structure efficiency here. Other optimisations are detailed in-line with where they are written. 

In general, any improvement to any step of minimax lead to significant performance improvements overall since
minimax evaluation is extremely expensive. More efficeincy leads to deeper allowable search depths leads to 
better game performance. 

- Deepening search
As the game progresses, more positions will lead to terminal states meaning early cutoff of minimax evaluation. 
In order to maximise the the search depth the player dynamically adjusts the search depth throughout the game.
In practice this leads to later game states being examined in significantly larger depth. 

The logic governing this deepening search goes as follows:
    - Assume that a move played at the same depth as the previous one will take roughly the same amount of time
    - Assume that a move played at one level deeper will take longer by one branching factor
    - Increase the search depth if based on the previous move, we can afford to go deeper
    - Decrease the search depth if based on the previous move, another move at the same depth would cause us to timeout
    eg. Previous move took 1.5 seconds and we have 20 seconds left. We assume deepening the search will lead to a 
    search time of ~15 seconds. Since we have 20 seconds left, lets increase the search depth for the next move. 

- Alpha-Beta pruning
Standard alpha-beta pruning allows us to cut-off and skip evaluation of branches that we know will lead to bad outcomes.
Specifically if a single move by the opponent can refute the current line of examination and that move leads to a
worse outcome for the player than one previously fully examined then that entire line of evaluation is pruned. This
is a strict improvement on standard minimax search with no pruning.

- Caching
Heuristic evaluation and terminal state evaluation are cached. A hash of the
position is taken and the result of a board is stored in a hashmap. This 
allows us to simply look up if we have previously already calculated the
heuristic of a particular board state. This leads to great savings in time
as many positions (of a subgrid) are repeated across the board and in 
different game paths.

For heuristic evaluation we can "double cache" any position by reversing
the board (swapping X's and O's) and storing the negative heuristic of that
since we have set our heuristic as a zero-sum between X and O and a position
that is evaluated as a 1 will be -1 if the X's are swapped with O's.

- Evaluation of terminal states
When a game is considered "won or lost", minimax search terminates leading to great performance optimisations.
In general, the game is considered "won" or "lost" when any one of the subboards is considered won or lost in the 
TTT sense. Since each and every position evaluated by each level/recurrence of the minimax search must
be evaluated as either won or lost, improvements in this function's efficiency are refelcted almost directly to
minimax performance overall. 

We can save time by checking whether only the grid that was last played in was won or lost. No other subgrid has changed
since the last move so we can assume that if it was not lost at that point in time, it will not be won or lost now. This
leads to a 9x efficiency boost (almost an order of magnitude). 

"""


def parse(string, player=None):
    string = string.strip()
    if "init" in string:
        return 0

    if "end" in string:
        return -1

    if "(" in string:
        command, args = string.split("(")
        args = args.split(")")[0]
        args = args.split(",")
    else:
        command, args = string, []

    # Handle cases for game start
    if command == "start":
        player.set_player(args[0])
        return 0

    if command == "second_move":
        player.currPosition.set_curr_grid(int(args[0]))
        player.currPosition.place(int(args[1]), player.opposition)
        return player.play_minimax_move()
    elif command == "third_move":
        player.currPosition.set_curr_grid(int(args[0]))
        player.currPosition.place(int(args[1]), player.player)
        player.currPosition.place(int(args[2]), player.opposition)
        return player.play_minimax_move()

    # Calculate the best next move
    elif command == "next_move":
        player.currPosition.place(int(args[0]), player.opposition)
        return player.play_minimax_move()

    elif command == "last_move":
        player.currPosition.place(int(args[0]), player.opposition)
        print("We played:", player.moves_played, "moves.")
        return 0

    # Handle cases for game ending
    elif command == "win":
        print("Yay!! We win!! :)")
        return -1

    elif command == "loss":
        print("We lost :(")
        player.currPosition.board.print_board()

        # pdb.set_trace()
        return -1

    else:
        return 0


def serverConnect(port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("localhost", port))
    return s


if __name__ == "__main__":

    # connect to the socket
    s = serverConnect(int(sys.argv[2]))
    board = Board()
    position = Position(board, 0)
    player = Player(position)

    while True:
        text = s.recv(1024).decode()
        if not text:
            continue

        for line in text.split("\n"):
            if not (line):
                break
            response = parse(line, player)
            if response == -1:
                s.close()
                exit()
            elif response > 0:
                s.sendall((str(response) + "\n").encode())
