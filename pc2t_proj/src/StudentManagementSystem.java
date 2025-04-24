import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.List;
import java.util.Scanner;

class StudentManagementSystem {
    private StudentDatabase database;
    private Scanner scanner;
    private Connection dbConnection;

    public StudentManagementSystem() {
        database = new StudentDatabase();
        scanner = new Scanner(System.in);

        // Inicializace pripojeni k databazi
        try {
            // Pro SQLite
            Class.forName("org.sqlite.JDBC");
            dbConnection = DriverManager.getConnection("jdbc:sqlite:students.db");
            Statement stmt = dbConnection.createStatement();

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

            // Nacteni dat pri spusteni
            database.loadFromDatabase(dbConnection);
        } catch (Exception e) {
            System.err.println("Chyba pri pripojeni k databazi: " + e.getMessage());
        }
    }

    public void run() {
        boolean running = true;

        while (running) {
            displayMenu();
            int choice = getIntInput("Vyberte akci: ");

            switch (choice) {
                case 1:
                    addNewStudent();
                    break;
                case 2:
                    addGradeToStudent();
                    break;
                case 3:
                    removeStudent();
                    break;
                case 4:
                    findAndDisplayStudent();
                    break;
                case 5:
                    executeStudentSkill();
                    break;
                case 6:
                    displaySortedStudents();
                    break;
                case 7:
                    displayAverageGradesByType();
                    break;
                case 8:
                    displayStudentCountByType();
                    break;
                case 9:
                    saveStudentToFile();
                    break;
                case 10:
                    loadStudentFromFile();
                    break;
                case 0:
                    // Ulozeni a ukonceni
                    database.saveToDatabase(dbConnection);
                    running = false;
                    break;
                default:
                    System.out.println("Neplatna volba. Prosim, zkuste to znovu.");
            }
        }

        // Uzavreni zdroju
        try {
            scanner.close();
            if (dbConnection != null) {
                dbConnection.close();
            }
        } catch (SQLException e) {
            System.err.println("Chyba pri uzavirani pripojeni k databazi: " + e.getMessage());
        }
    }

    private void displayMenu() {
        System.out.println("\n--- System spravy studentu ---");
        System.out.println("1. Pridat noveho studenta");
        System.out.println("2. Pridat znamku studentovi");
        System.out.println("3. Propustit studenta");
        System.out.println("4. Najit a zobrazit informace o studentovi");
        System.out.println("5. Spustit dovednost studenta");
        System.out.println("6. Zobrazit serazeny seznam studentu");
        System.out.println("7. Zobrazit studijni prumer podle skupin");
        System.out.println("8. Zobrazit pocet studentu podle skupin");
        System.out.println("9. Ulozit studenta do souboru");
        System.out.println("10. Nacist studenta ze souboru");
        System.out.println("0. Konec");
    }

    private int getIntInput(String prompt) {
        System.out.print(prompt);
        while (!scanner.hasNextInt()) {
            System.out.println("Neplatny vstup. Prosim, zadejte cislo.");
            System.out.print(prompt);
            scanner.next();
        }
        return scanner.nextInt();
    }

    private String getStringInput(String prompt) {
        System.out.print(prompt);
        scanner.nextLine(); // Vycisteni bufferu
        return scanner.nextLine();
    }

    private void addNewStudent() {
        System.out.println("\n--- Pridani noveho studenta ---");
        System.out.println("1. Student telekomunikaci");
        System.out.println("2. Student kyberneticke bezpecnosti");

        int type = getIntInput("Vyberte typ studenta: ");

        if (type != 1 && type != 2) {
            System.out.println("Neplatny typ studenta.");
            return;
        }

        System.out.print("Zadejte jmeno: ");
        String firstName = scanner.next();

        System.out.print("Zadejte prijmeni: ");
        String lastName = scanner.next();

        int birthYear = getIntInput("Zadejte rok narozeni: ");

        int id;
        if (type == 1) {
            id = database.addTelecommunicationsStudent(firstName, lastName, birthYear);
            System.out.println("Student telekomunikaci pridan. ID: " + id);
        } else {
            id = database.addCybersecurityStudent(firstName, lastName, birthYear);
            System.out.println("Student kyberneticke bezpecnosti pridan. ID: " + id);
        }
    }

    private void addGradeToStudent() {
        int studentId = getIntInput("Zadejte ID studenta: ");
        Student student = database.findStudentById(studentId);

        if (student == null) {
            System.out.println("Student s ID " + studentId + " nebyl nalezen.");
            return;
        }

        int grade = getIntInput("Zadejte znamku (1-5): ");
        if (grade < 1 || grade > 5) {
            System.out.println("Neplatna znamka. Znamka musi byt od 1 do 5.");
            return;
        }

        database.addGradeToStudent(studentId, grade);
        System.out.println("Znamka pridana.");
    }

    private void removeStudent() {
        int studentId = getIntInput("Zadejte ID studenta k propusteni: ");

        if (database.removeStudent(studentId)) {
            System.out.println("Student propusten.");
        } else {
            System.out.println("Student s ID " + studentId + " nebyl nalezen.");
        }
    }

    private void findAndDisplayStudent() {
        int studentId = getIntInput("Zadejte ID studenta: ");
        Student student = database.findStudentById(studentId);

        if (student == null) {
            System.out.println("Student s ID " + studentId + " nebyl nalezen.");
            return;
        }

        System.out.println("\n--- Informace o studentovi ---");
        System.out.println(student);

        System.out.println("Znamky: " + student.getGrades());
    }

    private void executeStudentSkill() {
        int studentId = getIntInput("Zadejte ID studenta: ");
        Student student = database.findStudentById(studentId);

        if (student == null) {
            System.out.println("Student s ID " + studentId + " nebyl nalezen.");
            return;
        }

        System.out.println("\n--- Provedeni dovednosti ---");
        System.out.println("Vysledek: " + student.executeSkill());
    }

    private void displaySortedStudents() {
        List<Student> sortedStudents = database.getSortedStudentsByLastName();

        System.out.println("\n--- Serazeny seznam studentu ---");

        System.out.println("Studenti telekomunikaci:");
        for (Student student : sortedStudents) {
            if (student instanceof TelecommunicationsStudent) {
                System.out.println(student);
            }
        }

        System.out.println("\nStudenti kyberneticke bezpecnosti:");
        for (Student student : sortedStudents) {
            if (student instanceof CybersecurityStudent) {
                System.out.println(student);
            }
        }
    }

    private void displayAverageGradesByType() {
        double telecomAvg = database.getAverageGradeByType(TelecommunicationsStudent.class);
        double cyberAvg = database.getAverageGradeByType(CybersecurityStudent.class);

        System.out.println("\n--- Studijni prumer podle skupin ---");
        System.out.printf("Studenti telekomunikaci: %.2f\n", telecomAvg);
        System.out.printf("Studenti kyberneticke bezpecnosti: %.2f\n", cyberAvg);
    }

    private void displayStudentCountByType() {
        int telecomCount = database.getStudentsByType(TelecommunicationsStudent.class).size();
        int cyberCount = database.getStudentsByType(CybersecurityStudent.class).size();

        System.out.println("\n--- Pocet studentu podle skupin ---");
        System.out.println("Studenti telekomunikaci: " + telecomCount);
        System.out.println("Studenti kyberneticke bezpecnosti: " + cyberCount);
        System.out.println("Celkova pocet studentu: " + (telecomCount + cyberCount));
    }

    private void saveStudentToFile() {
        int studentId = getIntInput("Zadejte ID studenta: ");
        Student student = database.findStudentById(studentId);

        if (student == null) {
            System.out.println("Student s ID " + studentId + " nebyl nalezen.");
            return;
        }

        System.out.print("Zadejte nazev souboru: ");
        String fileName = scanner.next();

        if (database.saveStudentToFile(studentId, fileName)) {
            System.out.println("Student ulozen do souboru: " + fileName);
        } else {
            System.out.println("Chyba pri ukladani studenta do souboru.");
        }
    }

    private void loadStudentFromFile() {
        System.out.print("Zadejte nazev souboru: ");
        String fileName = scanner.next();

        Student student = database.loadStudentFromFile(fileName);

        if (student != null) {
            System.out.println("Student naceten ze souboru:");
            System.out.println(student);
        } else {
            System.out.println("Chyba pri nacitani studenta ze souboru.");
        }
    }
}