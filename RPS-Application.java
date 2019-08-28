import java.util.Scanner;

public class Application {

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        Player comp = new Player("R");
        int yourScore = 0;
        int compScore = 0;
        
         while(yourScore != 3 && compScore != 3){
            System.out.println("Enter your move (R, P, S): ");
            String yourMove = reader.nextLine();
        
            String compMove = comp.getMove();
            System.out.println("Computer move: " + compMove);
       
            int val = beat(compMove, yourMove);
            if (val == 1){
                compScore++;
                comp.changeMove(compMove);
            }
            else if (val == 2){
                yourScore++;
                comp.changeMove(yourMove);
            }
            else if (val == 3){
                String betterMove;
                if (yourMove.equals("R"))
                    betterMove = "P";
                else if (yourMove.equals("S"))
                    betterMove = "R";
                else
                    betterMove = "S";
                comp.changeMove(betterMove);
            }
            System.out.println("Your Score: " + yourScore + " Computer Score: " + compScore);
        }
    }
    
    public static int beat(String compMove, String playerMove){ //1 comp wins, 2 player wins, 3 tie
        if (compMove.equals("P")){
            if (playerMove.equals("P"))
                return 3;
            if (playerMove.equals("S"))
                return 2;
            if (playerMove.equals("R"))
                return 1;
        }
        else if (compMove.equals("R")){
            if (playerMove.equals("P"))
                return 2;
            if (playerMove.equals("S"))
                return 1;
            if (playerMove.equals("R"))
                return 3;
        }
        else if (compMove.equals("S")){
            if (playerMove.equals("P"))
                return 1;
            if (playerMove.equals("S"))
                return 3;
            if (playerMove.equals("R"))
                return 2;
        }
        return 0;
    }
}
