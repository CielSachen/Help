package net.cielsachen.machineproject;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

class Main {
    private static boolean nextPlayerMove(Coordinates pos, boolean over, boolean next, HashSet<Coordinates> F3,
            boolean good, HashSet<Coordinates> F1, HashSet<Coordinates> F2, HashSet<Coordinates> C1,
            HashSet<Coordinates> C2) {
        int a = pos.x();
        int b = pos.y();
        int c = (int) Math.floor((a - 1) / 3) + 1;
        int d = (int) Math.floor((b - 1) / 3) + 1;
        var cdCoordinates = new Coordinates(c, d);

        if (!over && next && F3.contains(pos)) {
            good = !good;

            F1.add(pos);
        } else if (!over && !next && F3.contains(pos)) {
            good = !good;

            F2.add(pos);
        }

        if (!over && good && next && Utils.getElementsIntersectingSetSAmount(F1) > C1.size()) {
            C1.add(cdCoordinates);
        } else if (!over && good && !next && Utils.getElementsIntersectingSetSAmount(F2) > C2.size()) {
            C2.add(cdCoordinates);
        }

        if (!over && good) {
            good = !good;
        }

        return good;
    }

    private static String gameOver(boolean over, boolean next, HashSet<Coordinates> C1, HashSet<Coordinates> C2,
            Set<Set<Coordinates>> P, String result) {
        if (over && next && C1.size() > 0 && Utils.isContainingAnElementOfSetP(C1, P)) {
            return "A wins";
        } else if (over && !next && C2.size() > 0 && Utils.isContainingAnElementOfSetP(C2, P)) {
            return "B wins";
        }

        return result;
    }

    public static void main(String[] args) {
        var F1 = new HashSet<Coordinates>(36);
        var F2 = new HashSet<Coordinates>(36);
        var F3 = Utils.createNewSetF3(F1, F2);
        boolean over = false;
        boolean next = false;
        var scanner = new Scanner(System.in);
        boolean good = false;
        var C1 = new HashSet<Coordinates>(4);
        var C2 = new HashSet<Coordinates>(4);
        var P = Set.of(
                Set.of(new Coordinates(1, 1), new Coordinates(2, 2)),
                Set.of(new Coordinates(1, 2), new Coordinates(2, 1)));
        String result = "A and B are tied";

        while (!over) {
            Utils.displayGameBoard(F1, F2);

            System.out.print("\n");

            if (next) {
                System.out.println("Player A's Turn,");
            } else {
                System.out.println("Player B's Turn,");
            }

            int givenCoordinates;
            Coordinates pos;

            do {
                System.out.print("Input the coordinates (XY): ");

                givenCoordinates = scanner.nextInt();

                if (givenCoordinates < 11 || givenCoordinates > 66) {
                    System.out.println("Those are not valid coordinates.");
                }

                pos = new Coordinates(givenCoordinates / 10, givenCoordinates % 10);

                if (!F3.contains(pos)) {
                    System.out.println("Those coordinates coordinate is no longer available.");
                }
            } while (givenCoordinates < 11 || givenCoordinates > 66 || !F3.contains(pos));

            good = nextPlayerMove(pos, over, next, F3, good, F1, F2, C1, C2);
            F3 = Utils.createNewSetF3(F1, F2);

            if (F3.size() == 0 ||
                    (C1.size() > 0 && Utils.isContainingAnElementOfSetP(C1, P)) ||
                    (C2.size() > 0 && Utils.isContainingAnElementOfSetP(C2, P))) {
                over = true;
            }

            if (!over) {
                next = !next;
            }

            result = gameOver(over, next, C1, C2, P, result);

            System.out.print("\n");
        }

        scanner.close();

        Utils.displayGameBoard(F1, F2);

        System.out.print("\n");

        System.out.println("Player " + result + "!");

    }
}
