import java.util.Random;
import java.util.Arrays;
import java.util.Comparator;

public class uloha_3_2 {
    public static void main(String[] args) {
        Student[] students = new Student[10];
        String[] names = {"John", "Mary", "David", "Sarah", "Michael", "Emma", "James", "Olivia", "Robert", "Ava"};
        String[] surnames = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Grey", "Moore", "Taylor"};
        Random rand = new Random();

        // Fill array with random students
        for (int i = 0; i < students.length; i++) {
            int studentAge = rand.nextInt(33) + 18;
            int studentID = i;
            String studentName = names[rand.nextInt(names.length)];
            String studentSurname = surnames[rand.nextInt(surnames.length)];
            students[i] = new Student(studentID, studentAge, studentName, studentSurname);
        }

        // Print the array of students
        printfStudents(students);

        Arrays.sort(students, new NameComparator());
        printfStudents(students);

        Arrays.sort(students, new AgeComparator());
        printfStudents(students);

        Arrays.sort(students, new IdComparator());
        printfStudents(students);
    }

    public static void printfStudents(Student[] students) {
        for (Student student : students) {
            System.out.printf("%8s %7s, age: %d, ID: %d\n", student.getSurname(), student.getName(), student.getAge(), student.getID());
        }
        System.out.println();
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

class NameComparator implements Comparator<Student> {
    private final boolean ascending;

    public NameComparator() {
        this.ascending = true;
    }


    public NameComparator(boolean ascending) {
        this.ascending = ascending;
    }

    @Override
    public int compare(Student student1, Student student2) {
        int result = student1.getSurname().compareTo(student2.getSurname());
        if (result == 0) {
            result = student1.getName().compareTo(student2.getName());
        }
        return ascending ? result : -result;
    }
}

class AgeComparator implements Comparator<Student> {
    private final boolean ascending;

    public AgeComparator() {
        this.ascending = true;
    }


    public AgeComparator(boolean ascending) {
        this.ascending = ascending;
    }

    @Override
    public int compare(Student student1, Student student2) {
        int result = Integer.compare(student1.getAge(), student2.getAge());
        return ascending ? result : -result;
    }
}

class IdComparator implements Comparator<Student> {
    private final boolean ascending;

    public IdComparator() {
        this.ascending = true;
    }


    public IdComparator(boolean ascending) {
        this.ascending = ascending;
    }

    @Override
    public int compare(Student student1, Student student2) {
        int result = Integer.compare(student1.getID(), student2.getID());
        return ascending ? result : -result;
    }
}

