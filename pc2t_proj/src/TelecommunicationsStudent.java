import java.util.HashMap;
import java.util.Map;

class TelecommunicationsStudent extends Student {
    private static final long serialVersionUID = 2L;

    public TelecommunicationsStudent(int id, String firstName, String lastName, int birthYear) {
        super(id, firstName, lastName, birthYear);
    }

    @Override
    public String executeSkill() {
        String fullName = getFirstName() + " " + getLastName();
        return convertToMorseCode(fullName);
    }

    private String convertToMorseCode(String text) {
        // Implementace prevodu textu do Morseovy abecedy
        Map<Character, String> morseMap = new HashMap<>();

        // Naplneni mapy znaku a jejich kodu v Morseove abecede
        morseMap.put('A', ".-");
        morseMap.put('B', "-...");
        morseMap.put('C', "-.-.");
        morseMap.put('D', "-..");
        morseMap.put('E', ".");
        morseMap.put('F', "..-.");
        morseMap.put('G', "--.");
        morseMap.put('H', "....");
        morseMap.put('I', "..");
        morseMap.put('J', ".---");
        morseMap.put('K', "-.-");
        morseMap.put('L', ".-..");
        morseMap.put('M', "--");
        morseMap.put('N', "-.");
        morseMap.put('O', "---");
        morseMap.put('P', ".--.");
        morseMap.put('Q', "--.-");
        morseMap.put('R', ".-.");
        morseMap.put('S', "...");
        morseMap.put('T', "-");
        morseMap.put('U', "..-");
        morseMap.put('V', "...-");
        morseMap.put('W', ".--");
        morseMap.put('X', "-..-");
        morseMap.put('Y', "-.--");
        morseMap.put('Z', "--..");
        morseMap.put('0', "-----");
        morseMap.put('1', ".----");
        morseMap.put('2', "..---");
        morseMap.put('3', "...--");
        morseMap.put('4', "....-");
        morseMap.put('5', ".....");
        morseMap.put('6', "-....");
        morseMap.put('7', "--...");
        morseMap.put('8', "---..");
        morseMap.put('9', "----.");
        morseMap.put(' ', " ");

        StringBuilder result = new StringBuilder();

        for (char c : text.toUpperCase().toCharArray()) {
            if (c == ' ') {
                result.append("  "); // Dve mezery mezi slovy
            } else if (morseMap.containsKey(c)) {
                result.append(morseMap.get(c)).append(" ");
            }
        }

        return result.toString().trim();
    }
}