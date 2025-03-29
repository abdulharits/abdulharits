#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Fungsi untuk menentukan prioritas operator
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

// Fungsi untuk memeriksa apakah karakter adalah operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// a. Konversi Infix ke Postfix
void infixToPostfix(char* infix, char* postfix) {
    char stack[MAX];
    int top = -1;
    int j = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char c = infix[i];

        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--; // Pop '('
        } else if (isOperator(c)) {
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
}

// b. Konversi Postfix ke Infix
void postfixToInfix(char* postfix, char* infix) {
    char stack[MAX][MAX];
    int top = -1;

    for (int i = 0; i < strlen(postfix); i++) {
        char c = postfix[i];

        if (isalnum(c)) {
            stack[++top][0] = c;
            stack[top][1] = '\0';
        } else if (isOperator(c)) {
            char operand2[MAX], operand1[MAX];
            strcpy(operand2, stack[top--]);
            strcpy(operand1, stack[top--]);

            char temp[MAX];
            sprintf(temp, "(%s%c%s)", operand1, c, operand2);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(infix, stack[top]);
}

// c. Konversi Infix ke Prefix
void reverse(char* exp) {
    int n = strlen(exp);
    for (int i = 0; i < n / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[n - i - 1];
        exp[n - i - 1] = temp;
    }
}

void infixToPrefix(char* infix, char* prefix) {
    char infixReversed[MAX], stack[MAX];
    int top = -1, j = 0;

    reverse(infix);
    strcpy(infixReversed, infix);

    for (int i = 0; i < strlen(infixReversed); i++) {
        char c = infixReversed[i];

        if (isalnum(c)) {
            prefix[j++] = c;
        } else if (c == ')') {
            stack[++top] = c;
        } else if (c == '(') {
            while (top != -1 && stack[top] != ')') {
                prefix[j++] = stack[top--];
            }
            top--; // Pop ')'
        } else if (isOperator(c)) {
            while (top != -1 && precedence(stack[top]) > precedence(c)) {
                prefix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top != -1) {
        prefix[j++] = stack[top--];
    }
    prefix[j] = '\0';
    reverse(prefix);
}

// d. Konversi Prefix ke Infix
void prefixToInfix(char* prefix, char* infix) {
    char stack[MAX][MAX];
    int top = -1;

    for (int i = strlen(prefix) - 1; i >= 0; i--) {
        char c = prefix[i];

        if (isalnum(c)) {
            stack[++top][0] = c;
            stack[top][1] = '\0';
        } else if (isOperator(c)) {
            char operand1[MAX], operand2[MAX];
            strcpy(operand1, stack[top--]);
            strcpy(operand2, stack[top--]);

            char temp[MAX];
            sprintf(temp, "(%s%c%s)", operand1, c, operand2);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(infix, stack[top]);
}

// e. Konversi Prefix ke Postfix
void prefixToPostfix(char* prefix, char* postfix) {
    char stack[MAX][MAX];
    int top = -1;

    for (int i = strlen(prefix) - 1; i >= 0; i--) {
        char c = prefix[i];

        if (isalnum(c)) {
            stack[++top][0] = c;
            stack[top][1] = '\0';
        } else if (isOperator(c)) {
            char operand1[MAX], operand2[MAX];
            strcpy(operand1, stack[top--]);
            strcpy(operand2, stack[top--]);

            char temp[MAX];
            sprintf(temp, "%s%s%s", operand1, operand2, &c);
            strcpy(stack[++top], temp);
        }
    }
    strcpy(postfix, stack[top]);
}

int main() {
    int choice;
    char infix[MAX], postfix[MAX], prefix[MAX], infixResult[MAX];

    do {
        // Menu Pilihan
        printf("\nMenu Konversi Ekspresi Aritmatika\n");
        printf("1. Infix ke Postfix\n");
        printf("2. Postfix ke Infix\n");
        printf("3. Infix ke Prefix\n");
        printf("4. Prefix ke Infix\n");
        printf("5. Prefix ke Postfix\n");
        printf("6. Keluar\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan ekspresi infix: ");
                getchar(); // Untuk membersihkan newline setelah scanf
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = 0; // Menghapus newline
                infixToPostfix(infix, postfix);
                printf("Ekspresi postfix: %s\n", postfix);
                break;
            case 2:
                printf("Masukkan ekspresi postfix: ");
                getchar(); // Untuk membersihkan newline setelah scanf
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = 0; // Menghapus newline
                postfixToInfix(postfix, infixResult);
                printf("Ekspresi infix: %s\n", infixResult);
                break;
            case 3:
                printf("Masukkan ekspresi infix: ");
                getchar(); // Untuk membersihkan newline setelah scanf
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = 0; // Menghapus newline
                infixToPrefix(infix, prefix);
                printf("Ekspresi prefix: %s\n", prefix);
                break;
            case 4:
                printf("Masukkan ekspresi prefix: ");
                getchar(); // Untuk membersihkan newline setelah scanf
                fgets(prefix, MAX, stdin);
                prefix[strcspn(prefix, "\n")] = 0; // Menghapus newline
                prefixToInfix(prefix, infixResult);
                printf("Ekspresi infix: %s\n", infixResult);
                break;
            case 5:
                printf("Masukkan ekspresi prefix: ");
                getchar(); // Untuk membersihkan newline setelah scanf
                fgets(prefix, MAX, stdin);
                prefix[strcspn(prefix, "\n")] = 0; // Menghapus newline
                prefixToPostfix(prefix, postfix);
                printf("Ekspresi postfix: %s\n", postfix);
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid, silakan coba lagi.\n");
        }
    } while (choice != 6);

    return 0;
}
