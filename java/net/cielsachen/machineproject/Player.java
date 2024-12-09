package net.cielsachen.machineproject;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import net.cielsachen.machineproject.board.Tile;

/** */
public class Player {
    /** */
    public final Set<Tile> occupiedTiles = new HashSet<Tile>(36);
    /** */
    public final Set<Tile> winningConditions = new HashSet<Tile>(4);

    /** */
    public Player() {
    }

    /**
     * 
     * @param newTile
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
     * 
     * @return The number of tile patterns the player has completed.
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
     * 
     * @return Whether or not the player has won.
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
