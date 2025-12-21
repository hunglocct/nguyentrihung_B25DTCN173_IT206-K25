#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// 1. Data Structures
typedef struct {
    char question[256];
    char options[4][100];
    char correct_option; // 'A', 'B', 'C', or 'D'
} Question;

void display_leaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        printf("\n--- Leaderboard is empty or missing ---\n");
        return;
    }

    printf("\n--- B?NG X?P H?NG ---\n");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    printf("---------------------\n");
}

void save_score(const char *name, int score) {
    FILE *file = fopen("leaderboard.txt", "a");
    if (file == NULL) {
        printf("Error: Could not save score.\n");
        return;
    }
    fprintf(file, "Player: %-15s | Score: %d/5\n", name, score);
    fclose(file);
}

int main() {
    srand(time(NULL));

    // 2. Initialize 10 Questions
    Question bank[10] = {
        {"Thu do cua Vietnam la gi?", {"A. Ha Noi", "B. Ho Chi Minh", "C. Da Nang", "D. Hue"}, 'A'},
        {"1 + 1 = ?", {"A. 1", "B. 2", "C. 3", "D. 4"}, 'B'},
        {"Ngon ngu lap trinh C ra doi nam nao?", {"A. 1969", "B. 1972", "C. 1980", "D. 1990"}, 'B'},
        {"Ai la tac gia cua C?", {"A. Dennis Ritchie", "B. Bjarne Stroustrup", "C. James Gosling", "D. Guido van Rossum"}, 'A'},
        {"Tu khoa nao dung de khai bao so nguyen?", {"A. float", "B. char", "C. int", "D. double"}, 'C'},
        {"Ham nao dung de in ra man hinh?", {"A. scan()", "B. print()", "C. printf()", "D. echo()"}, 'C'},
        {"Ky tu xuong dong la gi?", {"A. \\t", "B. \\n", "C. \\r", "D. \\b"}, 'B'},
        {"Dau cham dong trong C la?", {"A. .", "B. ,", "C. ;", "D. :"}, 'C'},
        {"Mang trong C bat dau tu index may?", {"A. 1", "B. 0", "C. -1", "D. 2"}, 'B'},
        {"Lenh nao de thoat vong lap?", {"A. stop", "B. exit", "C. break", "D. continue"}, 'C'}
    };

    // 3. Game Setup
    char playerName[50];
    printf("Chao mung den voi Quiz Game!\n");
    printf("Nhap ten cua ban: ");
    fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = 0; // Remove newline

    // Random selection logic (Shuffle indices)
    int indices[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++) {
        int r = rand() % 10;
        int temp = indices[i];
        indices[i] = indices[r];
        indices[r] = temp;
    }

    int score = 0;
    int questions_to_ask = 5;

    // 4. Game Loop
    printf("\nBat dau choi! Tra loi 5 cau hoi ngau nhien.\n");
    for (int i = 0; i < questions_to_ask; i++) {
        int q_idx = indices[i];
        Question q = bank[q_idx];

        printf("\nCau %d: %s\n", i + 1, q.question);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", q.options[j]);
        }

        char answer;
        printf("Dap an cua ban (A/B/C/D): ");
        scanf(" %c", &answer);
        
        if (toupper(answer) == q.correct_option) {
            printf(">> Chinh xac! (+1 diem)\n");
            score++;
        } else {
            printf(">> Sai roi! Dap an dung la %c.\n", q.correct_option);
        }
    }

    // 5. Scoring & Leaderboard
    printf("\n--- KET QUA ---\n");
    printf("Nguoi choi: %s\n", playerName);
    printf("Tong diem: %d/%d\n", score, questions_to_ask);

    save_score(playerName, score);
    display_leaderboard();

    printf("\nCam on ban da choi!\n");

    return 0;
}


