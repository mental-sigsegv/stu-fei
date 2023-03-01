import java.util.Scanner;  // Import the Scanner class

public class uloha_2_2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String numArrayString = input.nextLine();
        input.close();
        
        String[] numArray = numArrayString.split(" ");
        
        for (int i = 0; i < numArray.length; i++) {
            System.out.println(numArray[i]);
        }
    }
}
