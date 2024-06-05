/* COP 3503C Assignment 2
This program is written by: Your Full Name */

import java.util.Scanner;

public class Main {

    // Directions for moving in 8 possible directions
    private static final int[] ROW_DIRECTIONS = {-1, -1, -1, 0, 1, 1, 1, 0};
    private static final int[] COL_DIRECTIONS = {-1, 0, 1, 1, 1, 0, -1, -1};

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Read the dimensions and number of words
        int M = sc.nextInt();
        int N = sc.nextInt();
        int S = sc.nextInt();
        sc.nextLine();  // Consume the remaining newline

        // Read the matrix
        char[][] board = new char[M][N];
        for (int i = 0; i < M; i++) {
            String[] row = sc.nextLine().split(" ");
            for (int j = 0; j < N; j++) {
                board[i][j] = row[j].charAt(0);
            }
        }

        // Read the words
        String[] words = new String[S];
        for (int i = 0; i < S; i++) {
            words[i] = sc.nextLine();
        }

        // Process each word
        for (String word : words) {
            boolean found = false;
            boolean[][] visited = new boolean[M][N];

            System.out.println("Looking for " + word);
            outerLoop:
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (board[i][j] == word.charAt(0) && searchWord(board, word, 0, i, j, visited)) {
                        found = true;
                        break outerLoop;
                    }
                }
            }

            if (!found) {
                System.out.println(word + " not found!");
            }
        }

        sc.close();
    }

    private static boolean searchWord(char[][] board, String word, int index, int row, int col, boolean[][] visited) {
        if (index == word.length()) {
            printBoard(board, word);
            return true;
        }

        if (!isValid(row, col, board.length, board[0].length, visited) || board[row][col] != word.charAt(index)) {
            return false;
        }

        visited[row][col] = true;

        for (int direction = 0; direction < 8; direction++) {
            int newRow = row + ROW_DIRECTIONS[direction];
            int newCol = col + COL_DIRECTIONS[direction];

            if (searchWord(board, word, index + 1, newRow, newCol, visited)) {
                visited[row][col] = false;
                return true;
            }
        }

        visited[row][col] = false;
        return false;
    }

    private static boolean isValid(int row, int col, int maxRow, int maxCol, boolean[][] visited) {
        return row >= 0 && row < maxRow && col >= 0 && col < maxCol && !visited[row][col];
    }

    private static void printBoard(char[][] board, String word) {
        for (char[] row : board) {
            for (char c : row) {
                System.out.print(c + " ");
            }
            System.out.println();
        }
    }
}