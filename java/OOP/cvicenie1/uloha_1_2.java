public class uloha_1_2 {
    public static void main(String[] args) {
        System.out.println(compare(1, 0));
        System.out.println(compare(0, 1));
        System.out.println(compare(0, 0));
    }

    private static int compare(int a, int b) {
        if (a > b) {
            return 1;
        } else if (a < b) {
            return -1;
        } else {
            return 0;
        }
    }
}