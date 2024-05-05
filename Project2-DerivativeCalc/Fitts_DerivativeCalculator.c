#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

double *PrimeCalc(char term[10], int size, FILE *inFile, int COUNT) { // "size" counts null terminator
    size -= 1;
    char prime[20];
    int k;
    int i;
    int coCount=0;
    int powCount=0;
    char coBuffer[10] = {'1'};
    double coefficent=0;
    char powBuffer[4] = {};
    int power = 0;
    int coSign = 1;
    static double derivList[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int j;

    if (term[0] == '+') {
        memmove(term, term+1, strlen(term));
    }

    for (i=0; i<=size; ++i) {
        if ((term[i] >= 48 && term[i] <= 57) || term[i] == '.') {
            coBuffer[coCount] = term[i];
            coCount+=1;
        }
        else if (term[i] == 'x') {
            coefficent = 1.0;
            power = 1;
            if (term[i+1] == '^') {
                i+=2;
                for (i=i; term[i] != '\0'; ++i) {
                    if (term[i] >= 48 && term[i] <= 57) {
                        powBuffer[powCount] = term[i];
                        powCount += 1;
                    }
                }
                coefficent = atof(coBuffer);
                power = atoi(powBuffer);
                break;
            }
            else {
                break;
            }
        }
    }

    if (power == 0) {
        return derivList;
    }

    //old co and power HERE
    if (term[0] == '-') {
        coefficent *= -1.0;
    }
    printf("\nOriginal Eq. calulations for term %d\n", (COUNT+1));
    for (j=0; j<=9; ++j) {
        derivList[j] = pow((j+1), power);
        derivList[j] *= coefficent;
        printf("Integer %d = %f\n", j+1,derivList[j]);
    }

    coefficent = coefficent * power;
    power -= 1;

    //NEW HERE
    printf("\nDerivative Eq. calulations for term %d\n", (COUNT+1));
    for (j=1; j<=10; ++j) {
        derivList[j+9] = pow((j), power);
        derivList[j+9] *= coefficent;
        printf("Integer %d = %f\n", j, derivList[j+9]);
    }


    if (COUNT == 0 || coefficent < 0){
        if (power >= 2) {
            sprintf(prime, "%.1fx^%d",coefficent, power);
        }
        else if (power == 1) {
            sprintf(prime, "%.1fx",coefficent);
        }
        else {
            sprintf(prime, "%.1f",coefficent);
        }

    }
    else {
        if (power >= 2) {
            sprintf(prime, "+%.1fx^%d",coefficent, power);
        }
        else if (power == 1) {
            sprintf(prime, "+%.1fx",coefficent);
        }
        else {
            sprintf(prime, "+%.1f",coefficent);
        }

    }

    fprintf(inFile, "%s", prime);

    return derivList;
}

int main() {
    FILE* inFile = NULL;
    int size;
    int i;
    int j=0;
    int k;
    char fileRead[100];
    double *finish;
    char term[20];
    char derivative[100];
    int power;
    double coefficent;
    double derivTotals[21];
    int COUNT = 0;
    double derivMin;
    double derivMax;
    double origMin;
    double origMax;

    inFile = fopen("equation.txt", "a+");

    if (inFile == NULL) {
        printf("Ensure your .txt file is named \"equation.txt\" !\n");
        return -1;
    }
    
    for (i=0; !feof(inFile); ++i) {
        fscanf(inFile, " %c", fileRead + i);
        size = i;
    }
    printf("%s %d\n", fileRead, size);

    fprintf(inFile, "\n");

    for (i=0;i<=size;++i) { //made this part before I knew we could seperate with whitespace, more universal anyways.
        term[j] = fileRead[i];
        j+=1;
        if (fileRead[i+1] == '+' || fileRead[i+1] == '-' || fileRead[i+1] == '=') {
            
            finish = PrimeCalc(term, j, inFile, COUNT);
            COUNT += 1;
            for (k=0; k<=19; ++k) { //FIRST 10 are old (0-9), LAST 10 are prime (10-19)
                derivTotals[k] += finish[k];
            }

            memset(term, 0, sizeof(term));
            j=0;
        }
    }

    fprintf(inFile, "=0\n   Original Eq. | Derivative\n");
    printf("\nFinal Values|Original Eq. | Derivative\n");
    for (i=0; i<=9; ++i) {
        fprintf(inFile, "%d   |   %.2f   |   %.2f\n", i+1, derivTotals[i], derivTotals[i+10]);
        printf("Integer %d     =  %.2f   |   %.2f\n", i+1, derivTotals[i], derivTotals[i+10]);
    }

    derivMin = derivTotals[10];
    derivMax = derivTotals[10];
    origMin = derivTotals[0];
    origMax = derivTotals[0];
    for (i=11; i<=19; ++i) {
        if (derivMin > derivTotals[i]) {
            derivMin = derivTotals[i];
        }
        if (derivMax < derivTotals[i]) {
            derivMax = derivTotals[i];
        }
    }
    for (i=1; i<=9; ++i) {
        if (origMin > derivTotals[i]) {
            origMin = derivTotals[i];
        }
        if (origMax < derivTotals[i]) {
            origMax = derivTotals[i];
        }
    }


    printf("Original Min: %.2f\nOriginal Max: %.2f\n", origMin, origMax);
    printf("Derivative Min: %.2f\nDerivative Max: %.2f\n", derivMin, derivMax);
    fclose(inFile);









    return 0;
}