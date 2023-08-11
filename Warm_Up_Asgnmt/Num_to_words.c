#include<stdio.h>

void twoDigit(int n, char *ones[], char *tens[], char *doubleTen[])
{
    if (n < 10)
        {
            printf(ones[n]);
        }
        else if (n < 20)
        {
            printf(doubleTen[n - 10]);
        }
        else if (n < 100)
        {
            printf("%s %s", tens[n / 10 - 2], ones[n % 10]);
        }
}

void words(int n, int type)
{
    char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *tens[] = {"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char *doubleTen[] = {"Ten", "Eleven", "Tweleve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    
    if ( n == 0 ) { printf("Zero"); return; }
    else if ( n < 0 ) { printf(" Negative "); }
    else if ( n < 100 ) { twoDigit(n, ones, tens, doubleTen); }
    else if ( n < 1000 ) { printf("%s Hundred ", ones[ n / 100 ] ); n %= 100; if( n != 0 ) { words(n,type); } }
    else if ( n < 100000 && type == 1)    // type 1 is indian type 2 is international
    {
        words(n/1000, type);
        printf(" Thousand ");
        n %= 1000;
        if ( n != 0 ) { words(n,type); }
    }
    else if ( n < 10000000 && type == 1)
    {
        words( n/100000, type );
        printf(" Lakhs ");
        n %= 100000;
        if ( n != 0 ) { words(n, type); }
    }
    else if ( n < 1000000000 && type == 1 )
    {
        words( n / 10000000, type);
        printf(" Crores ");
        n %= 10000000;
        if ( n!= 0 ) { words(n, type); }
    }
    else if ( n >= 1000000000 && type == 1 )
    {
        words( n / 1000000000 , type);
        printf(" Arab ");
        n %= 1000000000;
        if ( n!= 0 ) { words(n, type); }
    }
    else if ( n < 1000000 && type == 2)
    {
        words(n/1000, type);
        printf(" Thousand ");
        n %= 1000;
        if ( n != 0 ) { words(n, type); }
    }
    else if (n < 1000000000 && type == 2 )
        {
            words(n / 1000000, type);
            printf(" Millions ");
            n %= 1000000;
            if ( n!= 0 ) { words(n, type); }
        }
    else if ( n >= 1000000000 && type == 2 )
    {
        words( n / 1000000000 , type);
        printf(" Billions ");
        n %= 1000000000;
        if ( n!= 0 ) { words(n, type); }
    }
}


//Driver Code
int main()
{
    printf("Enter the number: ");
    int n;
    scanf("%d", &n);
    
    printf("\nThe number is: %d\n", n);
    printf("\nIndian Representation: ");
    words(n, 1);
    printf("\n");
    printf("\nInternational Representation: ");
    words(n, 2);
    printf("\n");
   
    return 0;
}
