
package guessingmachine;

import java.util.Random;
import java.util.Scanner;

public class GuessingMachine {

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int numberDrawn = drawNumber();

        int right = drawNumber();
        int i = 0;
        int guess = 50;
        int upper = 100;
        int lower = 0;
        while (true) {
            i++;
            System.out.println("Guess a number: ");
            System.out.println(""+ guess);
            if (guess < right) {
                System.out.println("The number is greater, guesses made: " + i);
                lower = guess;
                guess = ((upper+lower)/2);
            } else if (guess > right) {
                System.out.println("The number is lesser, guesses made: " + i);
                upper = guess;
                guess = ((upper+lower)/2);
            } else if (guess == right) {
                break;
            }

        }
        System.out.println("Congratulations, your guess is correct!");
    }

    private static int drawNumber() {
        return new Random().nextInt(101);
    }
}

