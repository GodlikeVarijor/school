import java.io.*;
import java.sql.*;
import java.util.*;

class StudentDatabase {
    private List<Student> students;
    private int nextId;

    public StudentDatabase() {
        students = new ArrayList<>();
        nextId = 1;
    }

    // Pridani noveho studenta
    public int addTelecommunicationsStudent(String firstName, String lastName, int birthYear) {
        int id = nextId++;
        students.add(new TelecommunicationsStudent(id, firstName, lastName, birthYear));
        return id;
    }

    public int addCybersecurityStudent(String firstName, String lastName, int birthYear) {
        int id = nextId++;
        students.add(new CybersecurityStudent(id, firstName, lastName, birthYear));
        return id;
    }

    // Vyhledani studenta podle ID
    public Student findStudentById(int id) {
        for (Student student : students) {
            if (student.getId() == id) {
                return student;
            }
        }
        return null;
    }

    // Pridani znamky studentovi
    public boolean addGradeToStudent(int studentId, int grade) {
        Student student = findStudentById(studentId);
        if (student != null) {
            student.addGrade(grade);
            return true;
        }
        return false;
    }

    // Odstraneni studenta
    public boolean removeStudent(int studentId) {
        Student student = findStudentById(studentId);
        if (student != null) {
            students.remove(student);
            return true;
        }
        return false;
    }

    // Ziskani seznamu vsech studentu
    public List<Student> getAllStudents() {
        return new ArrayList<>(students);
    }

    // Ziskani seznamu studentu podle typu
    public List<Student> getStudentsByType(Class<? extends Student> type) {
        List<Student> result = new ArrayList<>();
        for (Student student : students) {
            if (type.isInstance(student)) {
                result.add(student);
            }
        }
        return result;
    }

    // Razeni studentu podle prijmeni
    public List<Student> getSortedStudentsByLastName() {
        List<Student> sortedList = new ArrayList<>(students);
        Collections.sort(sortedList, new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                return s1.getLastName().compareTo(s2.getLastName());
            }
        });
        return sortedList;
    }

    // Vypocet prumerne znamky pro urcity typ studentu
    public double getAverageGradeByType(Class<? extends Student> type) {
        List<Student> filteredStudents = getStudentsByType(type);
        if (filteredStudents.isEmpty()) {
            return 0.0;
        }

        double sum = 0.0;
        int count = 0;
        for (Student student : filteredStudents) {
            if (!student.getGrades().isEmpty()) {
                sum += student.getAverageGrade();
                count++;
            }
        }

        return count > 0 ? sum / count : 0.0;
    }

    // Ulozeni studenta do souboru
    public boolean saveStudentToFile(int studentId, String fileName) {
        Student student = findStudentById(studentId);
        if (student == null) {
            return false;
        }

        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(fileName))) {
            out.writeObject(student);
            return true;
        } catch (IOException e) {
            System.err.println("Chyba pri ukladani studenta: " + e.getMessage());
            return false;
        }
    }

    // Nacteni studenta ze souboru
    public Student loadStudentFromFile(String fileName) {
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(fileName))) {
            return (Student) in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Chyba pri nacitani studenta: " + e.getMessage());
            return null;
        }
    }

    // Ulozeni vsech dat do SQL databaze
    public void saveToDatabase(Connection connection) {
        try {
            // Priprava tabulek
            createTablesIfNotExist(connection);

            // Vycisteni existujicich dat
            clearDatabase(connection);

            // Pridani studentu
            for (Student student : students) {
                saveStudentToDatabase(connection, student);
            }
        } catch (SQLException e) {
            System.err.println("Chyba pri ukladani do databaze: " + e.getMessage());
        }
    }

    // Nacteni vsech dat z SQL databaze
    public void loadFromDatabase(Connection connection) {
        try {
            students.clear();
            nextId = 1;

            // Nacteni studentu
            Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM students");

            while (rs.next()) {
                int id = rs.getInt("id");
                String firstName = rs.getString("first_name");
                String lastName = rs.getString("last_name");
                int birthYear = rs.getInt("birth_year");
                String type = rs.getString("student_type");

                Student student;
                if ("TELECOM".equals(type)) {
                    student = new TelecommunicationsStudent(id, firstName, lastName, birthYear);
                } else {
                    student = new CybersecurityStudent(id, firstName, lastName, birthYear);
                }

                students.add(student);

                if (id >= nextId) {
                    nextId = id + 1;
                }
            }
            rs.close();

            // Nacteni znamek
            for (Student student : students) {
                PreparedStatement pstmt = connection.prepareStatement(
                        "SELECT grade FROM grades WHERE student_id = ?");
                pstmt.setInt(1, student.getId());
                rs = pstmt.executeQuery();

                while (rs.next()) {
                    int grade = rs.getInt("grade");
                    student.addGrade(grade);
                }

                rs.close();
                pstmt.close();
            }
        } catch (SQLException e) {
            System.err.println("Chyba pri nacitani z databaze: " + e.getMessage());
        }
    }

    // Pomocne metody pro praci s databazi
    private void createTablesIfNotExist(Connection connection) throws SQLException {
        Statement stmt = connection.createStatement();

        // Vytvoreni tabulky studentu
        stmt.execute("CREATE TABLE IF NOT EXISTS students (" +
                "id INTEGER PRIMARY KEY, " +
                "first_name TEXT, " +
                "last_name TEXT, " +
                "birth_year INTEGER, " +
                "student_type TEXT)");

        // Vytvoreni tabulky znamek
        stmt.execute("CREATE TABLE IF NOT EXISTS grades (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                "student_id INTEGER, " +
                "grade INTEGER, " +
                "FOREIGN KEY (student_id) REFERENCES students(id))");

        stmt.close();
    }

    private void clearDatabase(Connection connection) throws SQLException {
        Statement stmt = connection.createStatement();
        stmt.execute("DELETE FROM grades");
        stmt.execute("DELETE FROM students");
        stmt.close();
    }

    private void saveStudentToDatabase(Connection connection, Student student) throws SQLException {
        // Ulozeni informaci o studentovi
        PreparedStatement pstmt = connection.prepareStatement(
                "INSERT INTO students (id, first_name, last_name, birth_year, student_type) VALUES (?, ?, ?, ?, ?)");

        pstmt.setInt(1, student.getId());
        pstmt.setString(2, student.getFirstName());
        pstmt.setString(3, student.getLastName());
        pstmt.setInt(4, student.getBirthYear());

        if (student instanceof TelecommunicationsStudent) {
            pstmt.setString(5, "TELECOM");
        } else {
            pstmt.setString(5, "CYBER");
        }

        pstmt.executeUpdate();
        pstmt.close();

        // Ulozeni znamek studenta
        pstmt = connection.prepareStatement("INSERT INTO grades (student_id, grade) VALUES (?, ?)");

        for (int grade : student.getGrades()) {
            pstmt.setInt(1, student.getId());
            pstmt.setInt(2, grade);
            pstmt.executeUpdate();
        }

        pstmt.close();
    }
}
