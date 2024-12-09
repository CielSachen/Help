package net.cielsachen.machineproject.board;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import net.cielsachen.machineproject.Player;

/** The game's board. */
public class Board {
    private final int maxColumns = 6;
    private final int maxRows = 6;
    private final Set<Tile> remainingTiles = new HashSet<Tile>(Arrays.asList(
            new Tile(1, 1), new Tile(1, 2), new Tile(1, 3), new Tile(1, 4), new Tile(1, 5), new Tile(1, 6),
            new Tile(2, 1), new Tile(2, 2), new Tile(2, 3), new Tile(2, 4), new Tile(2, 5), new Tile(2, 6),
            new Tile(3, 1), new Tile(3, 2), new Tile(3, 3), new Tile(3, 4), new Tile(3, 5), new Tile(3, 6),
            new Tile(4, 1), new Tile(4, 2), new Tile(4, 3), new Tile(4, 4), new Tile(4, 5), new Tile(4, 6),
            new Tile(5, 1), new Tile(5, 2), new Tile(5, 3), new Tile(5, 4), new Tile(5, 5), new Tile(5, 6),
            new Tile(6, 1), new Tile(6, 2), new Tile(6, 3), new Tile(6, 4), new Tile(6, 5), new Tile(6, 6)));

    /** Constructs a new board object. */
    public Board() {
    }

    /**
     * Prints this board with row and column legends to the output stream.
     * 
     * @param playerA Player A's data.
     * @param playerB Player B's data.
     */
    public void print(Player playerA, Player playerB) {
        for (int rowNumber = 0; rowNumber <= this.maxRows; rowNumber++) {
            for (int columnNumber = 0; columnNumber <= this.maxColumns; columnNumber++) {
                if (rowNumber == 0) {
                    System.out.print("  ");

                    if (columnNumber > 0) {
                        System.out.print(columnNumber);

                        if (columnNumber == this.maxColumns) {
                            System.out.print("\n");
                        } else {
                            System.out.print(" ");
                        }
                    }
                } else {
                    if (columnNumber == 0) {
                        System.out.print(rowNumber + " ");
                    } else {
                        Tile coordinates = new Tile(rowNumber, columnNumber);

                        if (playerA.occupiedTiles.contains(coordinates)) {
                            System.out.print("| A ");
                        } else if (playerB.occupiedTiles.contains(coordinates)) {
                            System.out.print("| B ");
                        } else {
                            System.out.print("|   ");
                        }

                        if (columnNumber == this.maxColumns) {
                            System.out.println("|");
                        }
                    }
                }
            }

            System.out.print("  ");

            for (int columnNumber = 1; columnNumber <= this.maxColumns; columnNumber++) {
                System.out.print("+---");

                if (columnNumber == this.maxColumns) {
                    System.out.println("+");
                }
            }
        }

        System.out.print("\n");
    }

    /**
     * Updates this board using the provided data of players A and B.
     * 
     * @param playerA Player A's data.
     * @param playerB Player B's data.
     */
    public void update(Player playerA, Player playerB) {
        Set<Tile> tiles = new HashSet<Tile>(this.remainingTiles);

        for (Tile tile : tiles) {
            boolean isOccupied = false;

            for (Tile occupiedTile : playerA.occupiedTiles) {
                if (tile.equals(occupiedTile)) {
                    isOccupied = true;

                    break;
                }
            }

            if (!isOccupied) {
                for (Tile occupiedTile : playerB.occupiedTiles) {
                    if (tile.equals(occupiedTile)) {
                        isOccupied = true;

                        break;
                    }
                }
            }

            if (isOccupied) {
                this.remainingTiles.remove(tile);
            }
        }
    }

    /**
     * Gets the remaining tiles unoccupied by either player A or player B.
     * 
     * @return The set of the remaining unoccupied tiles.
     */
    public Set<Tile> getRemainingTiles() {
        return Collections.unmodifiableSet(this.remainingTiles);
    }
}
