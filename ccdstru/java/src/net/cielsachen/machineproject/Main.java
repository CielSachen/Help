package net.cielsachen.machineproject;

import java.util.Arrays;
import java.util.HashSet;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Set;

class Main {
    /**
     * Implements the {@code NextPlayerMove(pos ∈ F)} function.
     * 
     * @param pos  The pos element value.
     * @param over The over element value.
     * @param next The next element value.
     * @param f3   The set F₃ value.
     * @param f1   The set F₁ value.
     * @param f2   The set F₂ value.
     * @param c1   The set C₁ value.
     * @param c2   The set C₂ value.
     */
    public static void nextPlayerMove(OrderedPair pos, boolean over, boolean next, Set<OrderedPair> f3,
            Set<OrderedPair> f1, Set<OrderedPair> f2, Set<OrderedPair> c1, Set<OrderedPair> c2) {
        final int c = (int) Math.floor((pos.a() - 1) / 3) + 1;
        final int d = (int) Math.floor((pos.b() - 1) / 3) + 1;

        if (!over && next && f3.contains(pos)) {
            f1.add(pos);

            if (Util.countSetSSubsets(f1) > c1.size()) {
                c1.add(new OrderedPair(c, d));
            }
        } else if (!over && !next && f3.contains(pos)) {
            f2.add(pos);

            if (Util.countSetSSubsets(f2) > c2.size()) {
                c2.add(new OrderedPair(c, d));
            }
        }
    }

    /**
     * Implements the {@code GameOver(over)} function.
     * 
     * @param over   The over element value.
     * @param next   The next element value.
     * @param c1     The set C₁ value.
     * @param c2     The set C₂ value.
     * @param result The result element value.
     * @return The updated result element value.
     */
    public static String gameOver(boolean over, boolean next, Set<OrderedPair> c1, Set<OrderedPair> c2, String result) {
        if (over && next && c1.size() > 0 && Util.isSupersetOfSetPSet(c1)) {
            return "A wins";
        } else if (over && !next && c2.size() > 0 && Util.isSupersetOfSetPSet(c2)) {
            return "B wins";
        }

        return result;
    }

    public static void main(String[] args) {
        final Set<OrderedPair> f1 = new HashSet<OrderedPair>(Util.F_SET_SIZE);
        final Set<OrderedPair> f2 = new HashSet<OrderedPair>(Util.F_SET_SIZE);
        final Set<OrderedPair> f3 = new HashSet<OrderedPair>(
                Arrays.asList(new OrderedPair(1, 1), new OrderedPair(1, 2), new OrderedPair(1, 3),
                        new OrderedPair(1, 4), new OrderedPair(1, 5), new OrderedPair(1, 6), new OrderedPair(2, 1),
                        new OrderedPair(2, 2), new OrderedPair(2, 3),
                        new OrderedPair(2, 4), new OrderedPair(2, 5), new OrderedPair(2, 6), new OrderedPair(3, 1),
                        new OrderedPair(3, 2), new OrderedPair(3, 3),
                        new OrderedPair(3, 4), new OrderedPair(3, 5), new OrderedPair(3, 6), new OrderedPair(4, 1),
                        new OrderedPair(4, 2), new OrderedPair(4, 3),
                        new OrderedPair(4, 4), new OrderedPair(4, 5), new OrderedPair(4, 6), new OrderedPair(5, 1),
                        new OrderedPair(5, 2), new OrderedPair(5, 3),
                        new OrderedPair(5, 4), new OrderedPair(5, 5), new OrderedPair(5, 6), new OrderedPair(6, 1),
                        new OrderedPair(6, 2), new OrderedPair(6, 3),
                        new OrderedPair(6, 4), new OrderedPair(6, 5), new OrderedPair(6, 6)));
        boolean over = false;
        boolean next = false;
        // boolean good = false;
        final Set<OrderedPair> c1 = new HashSet<OrderedPair>(Util.C_SET_SIZE);
        final Set<OrderedPair> c2 = new HashSet<OrderedPair>(Util.C_SET_SIZE);
        final Scanner scanner = new Scanner(System.in);
        String result = "A and Player B are tied";

        while (!over) {
            Util.printGameBoard(f1, f2);

            System.out.println("Player " + (next ? "A" : "B") + "'s Turn,");

            OrderedPair pos;

            while (true) {
                System.out.print("Input the tile's location {XY | X = Column, Y = Row}: ");

                int givenCoordinates;

                try {
                    givenCoordinates = scanner.nextInt();
                } catch (InputMismatchException exception) {
                    scanner.nextLine();

                    givenCoordinates = 0;
                }

                if (givenCoordinates < 11 || givenCoordinates > 66) {
                    System.out.println("Please input a location within the board.");

                    continue;
                }

                pos = new OrderedPair(givenCoordinates / 10, givenCoordinates % 10);

                if (!f3.contains(pos)) {
                    System.out.println("Please input the location of an unoccupied tile.");

                    continue;
                }

                break;
            }

            nextPlayerMove(pos, over, next, f3, f1, f2, c1, c2);

            f3.remove(pos);

            over = f3.size() == 0 || (c1.size() > 0 && Util.isSupersetOfSetPSet(c1))
                    || (c2.size() > 0 && Util.isSupersetOfSetPSet(c2));
            result = gameOver(over, next, c1, c2, result);

            if (!over) {
                next = !next;
            }

            System.out.println();
        }

        scanner.close();

        Util.printGameBoard(f1, f2);

        System.out.println("Player " + result + "!");
    }
}
