package net.cielsachen.machineproject;

/** A coordinate in a six by six Cartesian (XY) plane. */
public record Coordinates(int x, int y) {
    /**
     * Creates new coordinates from the provided X and Y values.
     * 
     * @param x The Coordinate on the X axis, or simply the X value.
     * @param y The Coordinate on the Y axis, or simply the Y value.
     */
    public Coordinates {
        assert x >= 1;
        assert x <= 6;

        assert y >= 1;
        assert y <= 6;
    }
}
