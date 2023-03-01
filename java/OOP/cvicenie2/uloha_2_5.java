public class uloha_2_5 {
    public static void main(String[] args) {
        int ARRAY_SIZE = 15;
        int[][] numArray = new int[ARRAY_SIZE][ARRAY_SIZE];
        
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                numArray[i][j] = (i+1)*(j+1);
            }
        }

        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                System.out.print(" " + String.format("%3d", numArray[i][j]));
            }
            System.out.println();
        }
    }
}
