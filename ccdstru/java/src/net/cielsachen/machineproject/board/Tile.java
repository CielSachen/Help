package net.cielsachen.machineproject.board;

import java.util.Objects;

/** A tile within the game's board. */
public class Tile {
    /** This tile's column number. */
    public final int column;
    /** This tile's row number. */
    public final int row;

    /**
     * Constructs a new tile object using the passed column and row numbers.
     * 
     * @param column The tile's column number.
     * @param row    The tile's row number.
     */
    public Tile(int column, int row) {
        this.column = column;
        this.row = row;
    }

    @Override
    public boolean equals(Object object) {
        if (object == this)
            return true;
        else if (object == null || object.getClass() != this.getClass())
            return false;

        Tile tile = (Tile) object;

        return this.column == tile.column && this.row == tile.row;
    }

    @Override
    public int hashCode() {
        return Objects.hash(column, row);
    }

    @Override
    public String toString() {
        return '[' + column + ", " + row + ']';
    }
}
