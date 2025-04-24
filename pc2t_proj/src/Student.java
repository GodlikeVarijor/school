import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

abstract class Student implements Serializable {
    private static final long serialVersionUID = 1L;

    private int id;
    private String firstName;
    private String lastName;
    private int birthYear;
    private List<Integer> grades; // Seznam znamkek

    public Student(int id, String firstName, String lastName, int birthYear) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.birthYear = birthYear;
        this.grades = new ArrayList<>();
    }

    // Gettery a settery
    public int getId() { return id; }
    public String getFirstName() { return firstName; }
    public String getLastName() { return lastName; }
    public int getBirthYear() { return birthYear; }

    // Metody pro spravu znamkek
    public void addGrade(int grade) {
        if (grade >= 1 && grade <= 5) {
            grades.add(grade);
        }
    }

    public List<Integer> getGrades() {
        return new ArrayList<>(grades);
    }

    public double getAverageGrade() {
        if (grades.isEmpty()) {
            return 0.0;
        }

        int sum = 0;
        for (int grade : grades) {
            sum += grade;
        }

        return (double) sum / grades.size();
    }

    // Abstraktni metoda pro dovednost studenta
    public abstract String executeSkill();

    @Override
    public String toString() {
        return String.format("ID: %d, %s %s, rok narozeni: %d, studijni prumer: %.2f",
                id, firstName, lastName, birthYear, getAverageGrade());
    }
}
