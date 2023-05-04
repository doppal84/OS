char *strrev(char *str, int length) {
    char *left, *right;
    left = str;
    right = str + (length - 1);
    while (left < right) {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
    return str;
}
