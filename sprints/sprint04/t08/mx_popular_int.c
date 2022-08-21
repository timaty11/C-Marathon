int mx_popular_int(const int *arr, int size) {
    int counter = 0;
    int num[size];
    for (int i = 0; i < size; i++)
    {
        num[i] = 0;
        int tmp = arr[i];
        for (int j = 0; j < size; j++)
        {
            if (tmp == arr[j])
            {
                num[i]++;
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if(num[0] == num[i])
        {
            num[0] = num[i];
            counter = i;
        }
    }
    return arr[counter];
}

