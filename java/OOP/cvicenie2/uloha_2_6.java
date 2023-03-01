public class uloha_2_6 {
    public static void main(String[] args) {
        int MATRIX_SIZE = 3;
        int k = 4;
        int[][] numArray = new int[MATRIX_SIZE][MATRIX_SIZE];
        
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                numArray[i][j] = (i+k*j)*(j-k*i);
            }
        }

        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                System.out.print(" " + String.format("%3d", numArray[i][j]));
            }
            System.out.println();
        }

        System.out.println("Determinant: " + determinant3x3(numArray));
    }

    public static int determinant3x3(int[][] matrix) {
        int det = 0;
    
        // Calculate the determinant using the formula for a 3x3 matrix
        det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
            - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
            + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    
        return det;
    }
} 
