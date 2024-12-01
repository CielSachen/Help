package net.cielsachen.machineproject;

import java.util.HashSet;
import java.util.Set;

public class Utils {
    public static final int MAX_ROWS = 6;
    public static final int MAX_COLUMNS = 6;

    public static void displayGameBoard(HashSet<Coordinates> F1, HashSet<Coordinates> F2) {
        for (int rowCount = 0; rowCount <= MAX_ROWS; rowCount++) {
            for (int columnCount = 0; columnCount <= MAX_COLUMNS; columnCount++) {
                if (rowCount == 0) {
                    System.out.print("  ");

                    if (columnCount > 0) {
                        System.out.print(columnCount);

                        if (columnCount == MAX_COLUMNS) {
                            System.out.print("\n");
                        } else {
                            System.out.print(" ");
                        }
                    }
                } else {
                    if (columnCount == 0) {
                        System.out.print(rowCount + " ");
                    } else {
                        var coordinates = new Coordinates(rowCount, columnCount);

                        if (F1.contains(coordinates)) {
                            System.out.print("| A ");
                        } else if (F2.contains(coordinates)) {
                            System.out.print("| B ");
                        } else {
                            System.out.print("|   ");
                        }

                        if (columnCount == MAX_COLUMNS) {
                            System.out.println("|");
                        }
                    }
                }
            }

            System.out.print("  ");

            for (int columnCount = 1; columnCount <= MAX_COLUMNS; columnCount++) {
                System.out.print("+---");

                if (columnCount == MAX_COLUMNS) {
                    System.out.println("+");
                }
            }
        }
    }

    public static HashSet<Coordinates> createNewSetF3(HashSet<Coordinates> F1, HashSet<Coordinates> F2) {
        var F = Set.of(
                new Coordinates(1, 1), new Coordinates(1, 2), new Coordinates(1, 3), new Coordinates(1, 4),
                new Coordinates(1, 5), new Coordinates(1, 6), new Coordinates(2, 1), new Coordinates(2, 2),
                new Coordinates(2, 3), new Coordinates(2, 4), new Coordinates(2, 5), new Coordinates(2, 6),
                new Coordinates(3, 1), new Coordinates(3, 2), new Coordinates(3, 3), new Coordinates(3, 4),
                new Coordinates(3, 5), new Coordinates(3, 6), new Coordinates(4, 1), new Coordinates(4, 2),
                new Coordinates(4, 3), new Coordinates(4, 4), new Coordinates(4, 5), new Coordinates(4, 6),
                new Coordinates(5, 1), new Coordinates(5, 2), new Coordinates(5, 3), new Coordinates(5, 4),
                new Coordinates(5, 5), new Coordinates(5, 6), new Coordinates(6, 1), new Coordinates(6, 2),
                new Coordinates(6, 3), new Coordinates(6, 4), new Coordinates(6, 5), new Coordinates(6, 6));
        var F3 = new HashSet<Coordinates>(F);

        for (Coordinates FOrderedPair : F) {
            boolean isExistingElement = false;

            for (Coordinates F1OrderedPair : F1) {
                if (FOrderedPair.equals(F1OrderedPair)) {
                    isExistingElement = true;
                }
            }

            for (Coordinates F2OrderedPair : F2) {
                if (FOrderedPair.equals(F2OrderedPair)) {
                    isExistingElement = true;
                }
            }

            if (isExistingElement) {
                F3.remove(FOrderedPair);
            }
        }

        return F3;
    }

    public static int getElementsIntersectingSetSAmount(HashSet<Coordinates> set) {
        var S = Set.of(
                Set.of(new Coordinates(1, 1), new Coordinates(1, 3), new Coordinates(2, 2), new Coordinates(3, 1),
                        new Coordinates(3, 3)),
                Set.of(new Coordinates(4, 4), new Coordinates(4, 6), new Coordinates(5, 5), new Coordinates(6, 4),
                        new Coordinates(6, 6)),
                Set.of(new Coordinates(1, 5), new Coordinates(2, 4), new Coordinates(2, 5), new Coordinates(2, 6),
                        new Coordinates(3, 5)),
                Set.of(new Coordinates(4, 1), new Coordinates(4, 3), new Coordinates(5, 1), new Coordinates(5, 3),
                        new Coordinates(6, 1), new Coordinates(6, 3)));
        int intersecting_elements_amount = 0;

        for (Set<Coordinates> subset : S) {
            if (set.containsAll(subset)) {
                intersecting_elements_amount++;
            }
        }

        return intersecting_elements_amount;
    }

    public static boolean isContainingAnElementOfSetP(HashSet<Coordinates> set, Set<Set<Coordinates>> P) {
        for (Set<Coordinates> PSubset : P) {
            if (set.containsAll(PSubset)) {
                return true;
            }
        }

        return false;
    }
}
