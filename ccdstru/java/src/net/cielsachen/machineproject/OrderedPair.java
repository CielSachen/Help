package net.cielsachen.machineproject;

/** A pair of two integer values with a fixed order. */
public record OrderedPair(
        /** The pair's first integer value. */
        int a,
        /** The pair's second integer value. */
        int b) {
}
