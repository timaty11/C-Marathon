#include "../inc/header.h"

int main(int argc, char * argv[]) {
    // Wrong usage handling //
    if (argc != 5) {
        mx_printerr("usage: ./part_of_the_matrix [operand1] [operation] [operand2] [result]\n");
        exit(1);
    }

    // Отбрасываем пробелы и прочие лишние отступы
    for (int i = 1; i < 5; i++) {
        argv[i] = mx_strdup(mx_strtrim(argv[i]));
    }

    // СМОТРИМ, СКОЛЬКО ПЕРЕМЕННЫХ НАМ НЕИЗВЕСТНО И НА КАКИХ ПОЗИЦИЯХ В ARGV ОНИ НАХОДЯТСЯ
    int obscurity_stage = 0;
    for (int i = 1; i < 5; i++) {
        if (mx_count_qmarks(argv[i])) {
            obscurity_stage++;
        }
    }
    int *obscurity_vars_pos = (int*)malloc(sizeof(int) * obscurity_stage);
    int j = 0;
    for (int i = 0; i < 5; i++) {
        if (mx_count_qmarks(argv[i])) {
            obscurity_vars_pos[j] = i;
            j++;
        }
    }

    // ПРОВЕРКИ
    for (int i = 1; i < argc; i++) {
        if (i == 2) {
            if (mx_strcmp(argv[2], "-") && mx_strcmp(argv[2], "+") && mx_strcmp(argv[2], "*") && mx_strcmp(argv[2], "/") && mx_strcmp(argv[2], "?")) {
                mx_printerr("Invalid operation: ");
                mx_printerr(argv[2]);
                mx_printerr("\n");
                exit(1);
            }
        } else if (!mx_check_correct_inp(argv[i], mx_strlen(argv[i]))) {
            if (i == 1 || i == 3) {
                mx_printerr("Invalid operand: ");
                mx_printerr(argv[i]);
                mx_printerr("\n");
                exit(1);
            }
            else {
                mx_printerr("Invalid result: ");
                mx_printerr(argv[i]);
                mx_printerr("\n");
                exit(1);
            }
        }
    }

    // Подсчет количества возможных вариантов на основании количества вопросительных знаков
    int operand1_poss_vars_count = mx_pow(10, mx_count_qmarks(argv[1]));
    int operand2_poss_vars_count = mx_pow(10, mx_count_qmarks(argv[3]));
    int result_poss_vars_count = mx_pow(10, mx_count_qmarks(argv[4]));

    // Создание и заполнение массива с возможными вариантами для operand1
    // Если переменная не содержит ? то существует только один варик - тот, что ввел пользователь
    // Следовательно в массиве будет только 1 элемент
    char *operand1_poss_vars[operand1_poss_vars_count];
    int *operand1_counter = (int*)malloc(sizeof(int) * mx_count_qmarks(argv[1]));

    if (operand1_poss_vars_count == 1) {
        operand1_poss_vars[0] = argv[1];
    } else {
        for (int i = 0; i < operand1_poss_vars_count; i++) {
            char *operand1_poss_value = (char*)malloc(sizeof(char) * (mx_strlen(argv[1]) + 1));
            int pos = 0;
            for (int j = 0; j < mx_strlen(argv[1]); j++) {
                if (argv[1][j] != '?') {
                    operand1_poss_value[j] = argv[1][j];
                } else {
                    operand1_poss_value[j] = operand1_counter[pos] + 48;
                    if (pos == mx_count_qmarks(argv[1]) - 1) {
                        operand1_counter[pos]++;
                    } else if (operand1_counter[pos + 1] == 10) {
                        operand1_poss_value[j] = operand1_counter[pos] + 49;
                        operand1_counter[pos]++;
                        operand1_counter[pos + 1] = 0;
                    }
                    pos++;
                }
            }
            operand1_poss_vars[i] = operand1_poss_value;
        }
    }

    // Создание и заполнение массива с возможными вариантами для operand2
    char *operand2_poss_vars[operand2_poss_vars_count];
    int *operand2_counter = (int*)malloc(sizeof(int) * mx_count_qmarks(argv[3]));

    if (operand2_poss_vars_count == 1) {
        operand2_poss_vars[0] = argv[3];
    } else {
        for (int i = 0; i < operand2_poss_vars_count; i++) {
            char *operand2_poss_value = (char*)malloc(sizeof(char) * (mx_strlen(argv[3]) + 1));
            int pos = 0;
            for (int j = 0; j < mx_strlen(argv[3]); j++) {
                if (argv[3][j] != '?') {
                    operand2_poss_value[j] = argv[3][j];
                } else {
                    operand2_poss_value[j] = operand2_counter[pos] + 48;
                    if (pos == mx_count_qmarks(argv[3]) - 1) {
                        operand2_counter[pos]++;
                    } else if (operand2_counter[pos + 1] == 10) {
                        operand2_poss_value[j] = operand2_counter[pos] + 49;
                        operand2_counter[pos]++;
                        operand2_counter[pos + 1] = 0;
                    }
                    pos++;
                }
            }
            operand2_poss_vars[i] = operand2_poss_value;
        }
    }

    // Создание и заполнение массива с возможными вариантами для result
    char *result_poss_vars[result_poss_vars_count];
    int *result_counter = (int*)malloc(sizeof(int) * mx_count_qmarks(argv[4]));

    if (result_poss_vars_count == 1) {
        result_poss_vars[0] = argv[4];
    } else {
        for (int i = 0; i < result_poss_vars_count; i++) {
            char *result_poss_value = (char*)malloc(sizeof(char) * (mx_strlen(argv[4]) + 1));
            int pos = 0;
            for (int j = 0; j < mx_strlen(argv[4]); j++) {
                if (argv[4][j] != '?') {
                    result_poss_value[j] = argv[4][j];
                } else {
                    result_poss_value[j] = result_counter[pos] + 48;
                    if (pos == mx_count_qmarks(argv[4]) - 1) {
                        result_counter[pos]++;
                    } else if (result_counter[pos + 1] == 10) {
                        result_poss_value[j] = result_counter[pos] + 49;
                        result_counter[pos]++;
                        result_counter[pos + 1] = 0;
                    }
                    pos++;
                }
            }
            result_poss_vars[i] = result_poss_value;
        }
    }

    switch (*argv[2]) {
        case '+':
            for (int a = 0; a < operand1_poss_vars_count; a++) {
                for (int b = 0; b < operand2_poss_vars_count; b++) {
                    for (int c = 0; c < result_poss_vars_count; c++) {
                        if (mx_atoi(operand1_poss_vars[a]) + mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" + ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                    }
                }
            }
            break;
        case '-':
            for (int a = 0; a < operand1_poss_vars_count; a++) {
                for (int b = 0; b < operand2_poss_vars_count; b++) {
                    for (int c = 0; c < result_poss_vars_count; c++) {
                        if (mx_atoi(operand1_poss_vars[a]) - mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" - ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                    }
                }
            }
            break;
        case '*':
            for (int a = 0; a < operand1_poss_vars_count; a++) {
                for (int b = 0; b < operand2_poss_vars_count; b++) {
                    for (int c = 0; c < result_poss_vars_count; c++) {
                        if (mx_atoi(operand1_poss_vars[a]) * mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" * ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                    }
                }
            }
            break;
        case '/':
            if (mx_atoi(argv[2]) == 0) {
                break;
            }
            for (int a = 0; a < operand1_poss_vars_count; a++) {
                for (int b = 0; b < operand2_poss_vars_count; b++) {
                    for (int c = 0; c < result_poss_vars_count; c++) {
                        printf("== %i ==\n", mx_atoi(operand1_poss_vars[a]) / mx_atoi(operand2_poss_vars[b]));
                        if (mx_atoi(operand1_poss_vars[a]) / mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" / ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                    }
                }
            }
            break;
        case '?':
            for (int a = 0; a < operand1_poss_vars_count; a++) {
                for (int b = 0; b < operand2_poss_vars_count; b++) {
                    for (int c = 0; c < result_poss_vars_count; c++) {
                        if (mx_atoi(operand1_poss_vars[a]) + mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" + ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                        if (mx_atoi(operand1_poss_vars[a]) - mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" - ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                        if (mx_atoi(operand1_poss_vars[a]) * mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" * ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                        if (mx_atoi(operand1_poss_vars[a]) / mx_atoi(operand2_poss_vars[b]) == mx_atoi(result_poss_vars[c])) {
                            mx_printint(mx_atoi(operand1_poss_vars[a]));
                            mx_printstr(" / ");
                            mx_printint(mx_atoi(operand2_poss_vars[b]));
                            mx_printstr(" = ");
                            mx_printint(mx_atoi(result_poss_vars[c]));
                            mx_printchar('\n');
                        }
                    }
                }
            }
            break;
    }

    // Очистка памяти
    for (int i = 0; i < operand1_poss_vars_count; i++) {
        mx_strdel(&operand1_poss_vars[i]);
    }
    for (int i = 0; i < operand2_poss_vars_count; i++) {
        mx_strdel(&operand2_poss_vars[i]);
    }
    for (int i = 0; i < result_poss_vars_count; i++) {
        mx_strdel(&result_poss_vars[i]);
    }

    return 0;
}

