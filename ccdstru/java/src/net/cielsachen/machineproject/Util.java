package net.cielsachen.machineproject;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/** This class contains various methods for handling specialized set operations and CLI graphics printing. */
public final class Util {
    /** The size of set C and all of its subsets. */
    public static final int C_SET_SIZE = 4;
    /** The size of set F and all of its subsets. */
    public static final int F_SET_SIZE = 36;

    private Util() {
    }

    /**
     * Counts the number of sets in set S that are subsets of the passed set.
     * 
     * @param set The set to check against.
     * @return The number of sets that are subsets of {@code set}.
     */
    public static int countSetSSubsets(Set<OrderedPair> set) {
        final Set<Set<OrderedPair>> s = new HashSet<Set<OrderedPair>>(Arrays.asList(
                new HashSet<OrderedPair>(Arrays.asList(new OrderedPair(1, 1), new OrderedPair(1, 3),
                        new OrderedPair(2, 2), new OrderedPair(3, 1), new OrderedPair(3, 3))),
                new HashSet<OrderedPair>(Arrays.asList(new OrderedPair(4, 4), new OrderedPair(4, 6),
                        new OrderedPair(5, 5), new OrderedPair(6, 4), new OrderedPair(6, 6))),
                new HashSet<OrderedPair>(Arrays.asList(new OrderedPair(1, 5), new OrderedPair(2, 4),
                        new OrderedPair(2, 5), new OrderedPair(2, 6), new OrderedPair(3, 5))),
                new HashSet<OrderedPair>(Arrays.asList(new OrderedPair(4, 1), new OrderedPair(4, 3),
                        new OrderedPair(5, 1), new OrderedPair(5, 3), new OrderedPair(6, 1), new OrderedPair(6, 3)))));
        int subsetsCount = 0;

        for (Set<OrderedPair> sSet : s) {
            if (set.containsAll(sSet)) {
                subsetsCount++;
            }
        }

        return subsetsCount;
    }

    /**
     * Checks whether the passed set is a superset of a set in set P.
     * 
     * @param set The set to check.
     * @returns {@code true} if {@code set} is a superset or {@code false} if not.
     */
    public static boolean isSupersetOfSetPSet(Set<OrderedPair> set) {
        final Set<Set<OrderedPair>> p = new HashSet<Set<OrderedPair>>(
                Arrays.asList(new HashSet<OrderedPair>(Arrays.asList(new OrderedPair(1, 1), new OrderedPair(2, 2))),
                        new HashSet<OrderedPair>(Arrays.asList(new OrderedPair(1, 2), new OrderedPair(2, 1)))));

        for (Set<OrderedPair> pSet : p) {
            if (set.containsAll(pSet)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Prints the board with row and column legends to the console.
     * 
     * @param f1 The set F₁ value.
     * @param f2 The set F₂ value.
     */
    public static void printGameBoard(Set<OrderedPair> f1, Set<OrderedPair> f2) {
        final int maximumRows = 6;
        final int maximumColumns = 6;

        for (int rowNumber = 0; rowNumber <= maximumRows; rowNumber++) {
            for (int columnNumber = 0; columnNumber <= maximumColumns; columnNumber++) {
                if (rowNumber == 0) {
                    System.out.print("  ");

                    if (columnNumber > 0) {
                        System.out.print(columnNumber);

                        if (columnNumber == maximumColumns) {
                            System.out.println();
                        } else {
                            System.out.print(" ");
                        }
                    }
                } else if (columnNumber == 0) {
                    System.out.print(rowNumber + " ");
                } else {
                    OrderedPair coordinates = new OrderedPair(columnNumber, rowNumber);

                    if (f1.contains(coordinates)) {
                        System.out.print("| A ");
                    } else if (f2.contains(coordinates)) {
                        System.out.print("| B ");
                    } else {
                        System.out.print("|   ");
                    }

                    if (columnNumber == maximumColumns) {
                        System.out.println("|");
                    }
                }

            }

            System.out.print("  ");

            for (int columnNumber = 1; columnNumber <= maximumColumns; columnNumber++) {
                System.out.print("+---");

                if (columnNumber == maximumColumns) {
                    System.out.println("+");
                }
            }
        }

        System.out.println();
    }
}
