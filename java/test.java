import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Main {
    public static void main(String[] args) {
        ArrayList<Person> people = new ArrayList<>();
        people.add(new Person("John", 25));
        people.add(new Person("Mary", 32));
        people.add(new Person("David", 18));
        people.add(new Person("Sarah", 28));

        // Sort by name
        Collections.sort(people, new NameComparator());
        System.out.println("Sorted by name:");
        for (Person person : people) {
            System.out.println(person.getName() + " (" + person.getAge() + ")");
        }

        // Sort by age
        Collections.sort(people, new AgeComparator());
        System.out.println("\nSorted by age:");
        for (Person person : people) {
            System.out.println(person.getName() + " (" + person.getAge() + ")");
        }
    }
}

class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}

class NameComparator implements Comparator<Person> {
    @Override
    public int compare(Person p1, Person p2) {
        return p1.getName().compareTo(p2.getName());
    }
}

class AgeComparator implements Comparator<Person> {
    @Override
    public int compare(Person p1, Person p2) {
        return Integer.compare(p1.getAge(), p2.getAge());
    }
}
