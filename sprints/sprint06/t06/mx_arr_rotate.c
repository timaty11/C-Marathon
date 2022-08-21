void mx_arr_rotate(int *arr, int size, int shift);

void mx_arr_rotate(int *arr, int size, int shift) {
    int tmp[size];
    for (int i = 0; i < size; i++) {
        tmp[i] = arr[i];
    }
    while (shift >= size) {
        shift -= size;
    }
    if (shift > 0) {
        for (int i = 0; i < shift; i++) {
            arr[i] = tmp[size - shift + i];
        }
        for (int i = shift; i < size; i++) {
            arr[i] = tmp[i - shift];
        }
    } else if (shift < 0) {
        for (int i = 0; i < (shift * (-1)); i++) {
            arr[size + shift + i] = tmp[i];
        }
        for (int i = 0; i < (size + shift); i++) {
            arr[i] = tmp[i - shift];
        }
    } else return;
}

1 2 3 4 5
      1 2
