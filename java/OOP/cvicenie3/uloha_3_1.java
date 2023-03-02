public class uloha_3_1 {
    public static void main(String[] args) {
        Student student = new Student(12, 20, "Martin", "Klacik");
        student.setID(20);
    }
}

class Student {
    private int ID;
    private int age;
    private String name;
    private String surname;

    // Constructor 1: Default constructor
    public Student() {
        this.ID = 0;
        this.age = 0;
        this.name = "";
        this.surname = "";
    }

    // Constructor 2: Constructor with all attributes
    public Student(int ID, int age, String name, String surname) {
        this.ID = ID;
        this.age = age;
        this.name = name;
        this.surname = surname;
    }

    // Constructor 3: Constructor without ID attribute
    public Student(int age, String name, String surname) {
        this.ID = 0;
        this.age = age;
        this.name = name;
        this.surname = surname;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public int getID() {
        return this.ID;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public int getAge() {
        return this.age;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getSurname() {
        return this.surname;
    }
}
