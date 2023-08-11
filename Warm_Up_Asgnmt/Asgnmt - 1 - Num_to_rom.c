#include<stdio.h>


void num_to_rom(int n);
int main()
{
    printf("Enter a number between 1 and 3999 which you wanna convert to Roman numeral: ");
    int n;
    scanf("%d", &n);
    
    num_to_rom(n);
    
    return 0;
}

void num_to_rom(int n)
{
    int val[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    char *pr[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    int i = 12;
    
    while(n)
    {
        int q = n / val[i];
        n = n % val[i];
        
        while(q)
        {
            printf("%s", pr[i]);
            q--;
        }
        i--;
    }
    printf("\n");
}
