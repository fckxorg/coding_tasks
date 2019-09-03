#include <stdio.h>
#include <assert.h>

int custom_puts(char *str) {
    assert(str);
    int i = 0;
    while(str[i]){
        if (putc(str[i], stdout) == EOF){
            return EOF;
        }
        i++;
    }
    if(putc('\n', stdout) == EOF){
        return EOF;
    }
    return 0;
}

char *custom_fgets(char *str, int count, FILE *stream){
    assert(str);
    assert(count);
    assert(stream);
    if (count < 1){
        return NULL;
    }
    int i = 0;
    char cursor = 0;
    cursor = getc(stream);
    while (cursor && i < count){
        str[i] = cursor;
        cursor = getc(stream);
    }
    return str;

}

char *custom_itoa(int number, char *buffer, int base = 10) {
    /*! Interprets number to string. You must provide string buffer with enough space in it.
     * @param number number to interpretate
     * @param buffer string buffer for output
     * @param base base specifier, default is 10
     * @return buffer pointer to buffer start
     * */
    assert(buffer);
    assert(number);

    int str_length = 0;
    const int FIRST_DIGIT_ASCII_POSITION = 48;
    while (number != 0) {
        buffer[str_length] = char(number % 10 + FIRST_DIGIT_ASCII_POSITION);
        str_length++;
        number /= 10;
    }
    char tmp = 0;
    for (int j = 0; j < str_length / 2; j++) {
        tmp = buffer[j];
        buffer[j] = buffer[str_length - j - 1];
        buffer[str_length - j - 1] = tmp;
    }
    return buffer;
}

int custom_atoi(const char *str) {
    /*! Interprets an integer value in a byte string pointed to by str
     * @param str pointer to a byte string
     * @return Integer value corresponding to the contents of str on success. If no conversion can be performed returns 0. If the converted value is out of range of integer type, the return value is undefined
     * */
    assert(str);
    int number = (int) NULL;
    int i = 0;
    int digit = 0;
    const int FIRST_DIGIT_ASCII_POSITION = 48;
    while (str[i]) {
        digit = (int) str[i] - FIRST_DIGIT_ASCII_POSITION;
        if (digit < 10 && digit > -1) {
            number *= 10;
            number += digit;
        }
        i++;
    }
    if (!number) {
        return 0;
    }
    return number;
}

int main() {
    char str[] = "Linus Torvalds";
    int status_code = custom_puts(str);
    const int ITOA_TEST_VALUE = 42;
    char buffer[10] = {};
    printf("Status code: %d\n", status_code);
    printf("atoi output: %d\n", custom_atoi("junk123"));
    printf("itoa output: %s\n", custom_itoa(ITOA_TEST_VALUE, buffer));

    return 0;
}