import java.util.Scanner;

class BooleanAlgebra {
    static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int n = scanner.nextInt();

        while (n > 0) {
            boolean[] values = new boolean[n];

            for (int i = 0; i < n; i++) {
                values[i] = scanner.next("[0-9]").charAt(0) != '0';
            }

            String line = scanner.nextLine();
            String expression = parseExpression(line, values);

            for (int i = expression.length() - 1; i > 0; i--) {
                if (expression.charAt(i) == '(') {
                    String operator = extractOperator(expression, i);
                    boolean[] params = extractParams(expression, i);

                    i -= operator.length();

                    expression = updateExpression(expression, i, resolveExpression(operator, params) ? "1" : "0");
                }
            }

            System.out.println(expression);

            n = scanner.nextInt();
        }
    }

    static String parseExpression(String line, boolean[] values) {
        StringBuilder stringBuilder = new StringBuilder();

        for (int i = 0; i < line.length(); i++) {
            if (line.charAt(i) != ' ') {
                if (line.charAt(i) > 64 && line.charAt(i) < 91) {
                    stringBuilder.append(values[line.charAt(i) - 65] ? '1' : '0');
                } else {
                    stringBuilder.append(line.charAt(i));
                }
            }
        }

        return stringBuilder.toString();
    }

    static String extractOperator(String expression, int index) {
        StringBuilder stringBuilder = new StringBuilder();

        do {
            index--;

            stringBuilder.append(expression.charAt(index));
        } while (index > 0 && expression.charAt(index - 1) > 96 && expression.charAt(index - 1) < 123);

        return stringBuilder.reverse().toString();
    }

    static boolean[] extractParams(String expression, int index) {
        StringBuilder stringBuilder = new StringBuilder();

        while (index < expression.length() - 1 && expression.charAt(index + 1) != ')') {
            index++;

            if(expression.charAt(index) == '0' || expression.charAt(index) == '1') {
                stringBuilder.append(expression.charAt(index));
            }
        }

        String values = stringBuilder.toString();

        boolean[] params = new boolean[values.length()];

        for (int i = 0; i < values.length(); i++) {
            params[i] = values.charAt(i) == '1';
        }

        return params;
    }

    static String updateExpression(String expression, int endIndex, String patch) {
        StringBuilder stringBuilder = new StringBuilder();

        for (int i = 0; i < endIndex; i++) {
            stringBuilder.append(expression.charAt(i));
        }

        for (int i = endIndex; i < expression.length(); i++) {
            if (expression.charAt(i) == ')') {
                stringBuilder.append(patch);
                i++;

                while (i < expression.length()) {
                    stringBuilder.append(expression.charAt(i));
                    i++;
                }
            }
        }

        return stringBuilder.toString();
    }

    static boolean resolveExpression(String operator, boolean[] params) {
        boolean result = false;

        switch (operator) {
            case "not":
                result = !params[0];

                break;
            case "or":
                for (int i = 0; i < params.length; i++) {
                    if (params[i]) {
                        result = true;
                        i = params.length;
                    }
                }

                break;
            case "and":
                result = true;

                for (int i = 0; i < params.length; i++) {
                    if (!params[i]) {
                        result = false;
                        i = params.length;
                    }
                }

                break;
        }

        return result;
    }
}
