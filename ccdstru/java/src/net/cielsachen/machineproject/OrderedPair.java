package net.cielsachen.machineproject;

import java.util.Objects;

/** A pair of two integer values with fixed order. */
public class OrderedPair {
    /** This pair's first integer value. */
    public final int a;
    /** This pair's second integer value. */
    public final int b;

    /**
     * Constructs a new ordered pair object using the two passed integer values.
     * 
     * @param a The pair's first integer value.
     * @param b The pair's second integer value.
     */
    public OrderedPair(int a, int b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public boolean equals(Object object) {
        if (object == this) {
            return true;
        } else if (object == null || object.getClass() != this.getClass()) {
            return false;
        }

        final OrderedPair point = (OrderedPair) object;

        return this.a == point.a && this.b == point.b;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.a, this.b);
    }

    @Override
    public String toString() {
        return '(' + this.a + ", " + this.b + ')';
    }
}
