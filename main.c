#include <stdio.h>
#include <stdlib.h>
#include "fun.h"

int main(void) {
    link RBT = Initialize();
    int answer,element;
    do {
        printf("Menou\n");
        printf("-------------------\n");
        printf("1|Eisagogi stixeiou\n");
        printf("2|Diagrafi stixeiou\n");
        printf("3|Elenxos gia to an uparxei kapio stixeio\n");
        printf("4|Ektiposi ton stixeion se aujousa seira\n");
        printf("5|Telos programatos\n");
        printf("-------------------\n");
        printf("\nDose apantisi :");
        scanf("%d",&answer);
        printf("\n");
        switch(answer) {
            case 1:
                printf("Dose stixeio gia eisagogi :");
                scanf("%d",&element);
                if(Search(RBT,element) == falsh)//αν το στιχειο δεν υπαρχει
                    RBT = InsertKey(RBT,element);//κανο εκχορισι του στιχειου και ενιμερονο την ριζα για αλλαγες
                else
                    printf("To stixeio %d uparxei eidi\n", element);
                printf("\n");
                break;
            case 2:
                printf("Dose stixeio gia diagrafh :");
                scanf("%d",&element);
                if(Search(RBT,element) == true)//αν το στιχειο υπαρχει
                    RBT = RemoveKey(RBT,element);//το διαγραφο και ενυμερονο την ριζα για αλλαγες
                else
                    printf("To stixeio %d den uparxei\n", element);
                printf("\n");
                break;
            case 3:
                printf("Dose stixeio gia anazitisi :");
                scanf("%d",&element);
                if(Search(RBT,element) == true)//αν το στιχειο υπαρχει
                    printf("To stixeio %d uparxei\n", element);
                else
                    printf("To stixeio %d den uparxei\n", element);
                printf("\n");
                break;
            case 4:
                InOrder(RBT);//εκτιποση σε αυξουσα σειρα
                printf("\n");
                printf("\n");
                break;   
        }
    }while(answer != 5);
}