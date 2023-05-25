/*
 * Some examples to think about condition codes
 */
#include <stdio.h>

int main(int argc, char **argv) {

    unsigned int a, b, res1;
    int x, y, res2;


    printf("\n");
    printf("ADD\n");
    printf("---\n");
    a = 0x7fffffff;
    x = 0x7fffffff;
    res1 = a + 4;
    res2 = x + 4;
    printf("unsigned %u + 4 is %14u (0x%x)\n", a, res1, res1);
    printf("  signed %d + 4 is %14d (0x%x)\n", x, res2, res2);

    printf("\n");
    printf("SUB\n");
    printf("---\n");
    a = 3;
    x = 3;
    res1 = a - 5;
    res2 = x - 5;
    printf("unsigned 3 - 5 is %14u (0x%x)\n", res1, res1);
    printf("  signed 3 - 5 is %14d (0x%x)\n", res2, res2);

    printf("\n");
    printf("OR and AND\n");
    printf("----------\n");
    a = 0x08;
    b = 0x08;
    printf("a:    0x%x\n", a);
    printf("b:    0x%x\n", b);
    res1 = a & b;
    printf("a & b 0x%8x  signed %14d  unsigned %u\n", res1, res1, res1);
    res1 = a | b;
    printf("a | b 0x%8x  signed %14d  unsigned %u\n", res1, res1, res1);

    printf("\n");
    x = 0x30000000;
    y = 0x80000001;
    printf("x:    0x%x\n", x);
    printf("y:    0x%x\n", y);
    res1 = x & y;
    printf("x & y 0x%8x  signed %14d  unsigned %u\n", res1, res1, res1);
    res1 = x | y;
    printf("x | y 0x%8x  signed %14d  unsigned %u\n", res1, res1, res1);

    printf("\n");

    return 0;
}
