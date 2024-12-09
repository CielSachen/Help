package net.cielsachen.machineproject;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import net.cielsachen.machineproject.board.Tile;

/** A player of the game (presumable either A or B). */
public class Player {
    /** The set of this player's occupied board tiles. */
    public final Set<Tile> occupiedTiles = new HashSet<Tile>(36);
    /** The set of this player's winning conditions. */
    public final Set<Tile> winningConditions = new HashSet<Tile>(4);

    /** Constructs a new player object. */
    public Player() {
    }

    /**
     * Updates this player's occupied tiles to add the provided new tile.
     * 
     * @param newTile The newly occupied tile to add.
     */
    public void update(Tile newTile) {
        this.occupiedTiles.add(newTile);

        if (this.getTilePatternsAmount() > this.winningConditions.size()) {
            this.winningConditions.add(new Tile(
                    (int) Math.floor((newTile.column - 1) / 3) + 1,
                    (int) Math.floor((newTile.row - 1) / 3) + 1));
        }
    }

    /**
     * Gets the number of tile patterns that this player has completed.
     * 
     * @return The number of tile patterns this player has completed.
     */
    public int getTilePatternsAmount() {
        Set<Set<Tile>> tilePatterns = new HashSet<Set<Tile>>(Arrays.asList(
                new HashSet<Tile>(Arrays.asList(
                        new Tile(1, 1), new Tile(1, 3), new Tile(2, 2), new Tile(3, 1), new Tile(3, 3))),
                new HashSet<Tile>(Arrays.asList(
                        new Tile(4, 4), new Tile(4, 6), new Tile(5, 5), new Tile(6, 4), new Tile(6, 6))),
                new HashSet<Tile>(Arrays.asList(
                        new Tile(1, 5), new Tile(2, 4), new Tile(2, 5), new Tile(2, 6), new Tile(3, 5))),
                new HashSet<Tile>(Arrays.asList(
                        new Tile(4, 1), new Tile(4, 3), new Tile(5, 1), new Tile(5, 3), new Tile(6, 1),
                        new Tile(6, 3)))));
        int tilePatternsAmount = 0;

        for (Set<Tile> tilePattern : tilePatterns) {
            if (this.occupiedTiles.containsAll(tilePattern)) {
                tilePatternsAmount++;
            }
        }

        return tilePatternsAmount;
    }

    /**
     * Checks whether or not the player has all the winning conditions and has, therefore, won.
     * 
     * @return {@code true} if the player has won or {@code false} if not.
     */
    public boolean isWinner() {
        if (this.winningConditions.size() < 1) {
            return false;
        }

        Set<Set<Tile>> winningConditions = new HashSet<Set<Tile>>(Arrays.asList(
                new HashSet<Tile>(Arrays.asList(new Tile(1, 1), new Tile(2, 2))),
                new HashSet<Tile>(Arrays.asList(new Tile(1, 2), new Tile(2, 1)))));

        for (Set<Tile> winningCondition : winningConditions) {
            if (this.winningConditions.containsAll(winningCondition)) {
                return true;
            }
        }

        return false;
    }
}
