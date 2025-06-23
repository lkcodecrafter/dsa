public class QueenDirectionChecks {

    public static void main(String[] args) {
        int row = 3, col = 2;
        int size = 8; // 8x8 board
        char[][] board = new char[size][size];

        System.out.println("🔹 Same Column ⬆:");
        for (int i = 0; i < row; i++) {
            System.out.println("(" + i + ", " + col + ")");
        }

        System.out.println("\n🔹 Upper Left Diagonal ↖:");
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            System.out.println("(" + i + ", " + j + ")");
        }

        System.out.println("\n🔹 Upper Right Diagonal ↗:");
        for (int i = row - 1, j = col + 1; i >= 0 && j < size; i--, j++) {
            System.out.println("(" + i + ", " + j + ")");
        }
    }
}
