#include <stdio.h>
#include <stdlib.h>

int main()
{
    double x;
    float u;
    int q;
    FILE *fp;
    printf("Please input your seed(between 0 and 1)\n");
    scanf("%lf", &x);
    printf("Please input the u parameter(between 0 and 4)\n");
    scanf("%f", &u);
    printf("Please input the quantity\n");
    scanf("%d", &q);

    fp = fopen("LogisticIn.txt", "w");

    for(int i = 0; i < q; i++)
    {
        x = u * x * (1.0 - x);
        printf("%.10f\n", x);
        fprintf(fp, "%.10f\n", x);
    }

    fclose(fp);
    return 0;
}
