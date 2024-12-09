package net.cielsachen.machineproject;

import java.util.Scanner;

import net.cielsachen.machineproject.board.Board;
import net.cielsachen.machineproject.board.Tile;

class Main {
    public static void main(String[] args) {
        Board board = new Board();
        Player[] players = { new Player(), new Player() };
        Player player = players[0];
        int turn = 1;
        Scanner scanner = new Scanner(System.in);
        String result = "A and Player B are tied";

        while (true) {
            board.print(players[0], players[1]);

            if (player.isWinner()) {
                result = (((turn & 1) == 1) ? 'A' : 'B') + " wins";

                break;
            } else if (board.getRemainingTiles().size() == 0) {
                break;
            }

            player = players[((turn & 1) == 1) ? 0 : 1];

            System.out.println("Player " + (((turn & 1) == 1) ? 'A' : 'B') + "'s Turn,");

            int givenLocation;
            Tile tile;

            while (true) {
                System.out.print("Input the tile's location {XY | X = Column, Y = Row}: ");

                givenLocation = scanner.nextInt();

                if (givenLocation < 11 || givenLocation > 66) {
                    System.out.println("Please input a location within the board.");

                    continue;
                }

                tile = new Tile(givenLocation / 10, givenLocation % 10);

                if (!board.getRemainingTiles().contains(tile)) {
                    System.out.println("Please input the location of an unoccupied tile.");

                    continue;
                }

                break;
            }

            player.update(tile);

            board.update(players[0], players[1]);

            System.out.print("\n");

            turn++;
        }

        scanner.close();

        System.out.println("Player " + result + "!");
    }
}
