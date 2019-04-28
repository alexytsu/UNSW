#!/usr/bin/python3
import socket
import sys

import numpy as np
from player import Player
from position import Position
from board import Board

# read what the server sent us and
# only parses the strings that are necessary


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
        return -1

    else:
        return 0


def serverConnect(port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('localhost', port))
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
            if not(line):
                break
            response = parse(line, player)
            if response == -1:
                s.close()
                exit()
            elif response > 0:
                s.sendall((str(response) + "\n").encode())
