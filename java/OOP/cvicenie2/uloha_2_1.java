public class uloha_2_1 {
    private static final String[] ZODIAC_SIGNS = { "Aquarius", "Pisces", "Aries", "Taurus", "Gemini", "Cancer", "Leo",
            "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricorn" };

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Invalid arguments. Usage: java uloha_2_1 <day> <month>");
            return;
        }

        int day = Integer.parseInt(args[0]);
        int month = Integer.parseInt(args[1]);

        int index = getZodiacIndex(day, month);
        System.out.println(ZODIAC_SIGNS[index]);
    }

    private static int getZodiacIndex(int day, int month) {
        int zodiacIndex = 0;
        switch (month) {
            case 1:
                if (day < 20)
                    zodiacIndex = 12;
                else
                    zodiacIndex = 1;
                break;
            case 2:
                if (day < 19)
                    zodiacIndex = 1;
                else
                    zodiacIndex = 2;
                break;
            case 3:
                if (day < 21)
                    zodiacIndex = 2;
                else
                    zodiacIndex = 3;
                break;
            case 4:
                if (day < 20)
                    zodiacIndex = 3;
                else
                    zodiacIndex = 4;
                break;
            case 5:
                if (day < 21)
                    zodiacIndex = 4;
                else
                    zodiacIndex = 5;
                break;
            case 6:
                if (day < 21)
                    zodiacIndex = 5;
                else
                    zodiacIndex = 6;
                break;
            case 7:
                if (day < 23)
                    zodiacIndex = 6;
                else
                    zodiacIndex = 7;
                break;
            case 8:
                if (day < 23)
                    zodiacIndex = 7;
                else
                    zodiacIndex = 8;
                break;
            case 9:
                if (day < 23)
                    zodiacIndex = 8;
                else
                    zodiacIndex = 9;
                break;
            case 10:
                if (day < 23)
                    zodiacIndex = 9;
                else
                    zodiacIndex = 10;
                break;
            case 11:
                if (day < 22)
                    zodiacIndex = 10;
                else
                    zodiacIndex = 11;
                break;
            case 12:

                if (day < 22)
                    zodiacIndex = 11;
                else
                    zodiacIndex = 12;
                break;
        }
        return zodiacIndex - 1;

    }

}
