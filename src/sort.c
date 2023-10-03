
#include "../../hw2/include/gradedb.h"
#include "../../hw2/include/sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Sort the Class and Section Rosters
 */

void warning(const char *fmt, ...);

Student *getnext(s)
Student *s;
{
        if (s != NULL) {
        return s->next;
    } else {    
        return NULL;
    }
}

Student *getcnext(s)
Student *s;
{
        if (s != NULL && s->cnext != NULL ) {
        return s->cnext;
    } else {    
        return NULL;
    }
}

void setnext(s, n)
Student *s, *n;
{
        s->next = n;
}

void setcnext(s, n)
Student *s, *n;
{
        s->cnext = n;
}

void sortrosters(c, compare)
Course *c;
int compare();
{
        Section *s;

        if(c->roster != NULL)c->roster = sortroster(c->roster, getcnext, setcnext, compare);
        if(c->sections != NULL){
        for(s = c->sections; s != NULL && s->roster != NULL; s = s->next)
        if (s->roster != NULL) {
                s->roster = sortroster(s->roster, getnext, setnext, compare);
        }
        }
}

Student *sortroster(s, gtnxt, stnxt, compare)
Student *s;
Student *gtnxt();
void stnxt();
int compare();
{
        int count, i;
        Student *sp, **stab;

        sp = s;
        count = 0;
        while(sp != NULL) {     /* Count students */
                count++;
                sp = gtnxt(sp);
        }
        if(count == 0) return(NULL);
        if((stab = (Student **)malloc(count*sizeof(Student))) == NULL)
                warning("Not enough memory to perform sorting.");
        sp = s;
        i = count;
        while(i--) {            /* Put students in table */
                stab[i] = sp;
                sp = gtnxt(sp);
        }
        sorttable(stab, 0, count, compare);
        sp = stab[0];
        for(i = 1; i < count; i++) {    /* Relink students in order */
                stnxt(sp, stab[i]);
                sp = stab[i];
        }
        stnxt(sp, NULL);
        free(stab);
        return(stab[0]);
}

/*
 * Quicksort algorithm for sorting table of students.
 */

void sorttable(stab, low, high, compare)
Student **stab;
int low, high;
int compare();
{
        int middle;
        if(low == high) return;
        middle = partition(stab, low, high, compare);
        if(low+1 == high) return;
        sorttable(stab, low, middle, compare);
        sorttable(stab, middle, high, compare);
}

int partition(stab, low, high, compare)
Student **stab;
int low, high;
int compare();
{
        int l, h, c, alt;
        Student *temp, *pivot;
        pivot = stab[(low+high)/2];
        l = low;
        h = high;
        alt = 1;
        while(l < h) {
                c = compare(stab[l], pivot);
                if(c == 0) {
                        c = alt;
                        alt = -alt;
                }
                if(c > 0) { /* put on high end */
                        temp = stab[h-1];
                        stab[h-1] = stab[l];
                        stab[l] = temp;
                        h--;
                } else {        /* put on low end */
                        l++;
                }
        }
        return(l);
}

int comparename(s1, s2)
Student *s1, *s2;
{
        if (s1 == NULL || s2 == NULL) {
        // Handle the case where either pointer is NULL
        // You can decide what to return in this case
        return 0; // For example, return 0 for consistency with strcmp
    }

    int surnameComparison = strcmp(s1->surname, s2->surname);
    
    if (surnameComparison != 0) {
        // Surnames are different, return the result of comparing surnames
        return surnameComparison;
    } else {
        // Surnames are the same, compare names
        return strcmp(s1->name, s2->name);
    }
}

int compareid(s1, s2)
Student *s1, *s2;
{
        return(strcmp(s1->id, s2->id));
}

int comparescore(s1, s2)
Student *s1, *s2;
{
        if(s1->composite > s2->composite) return(-1);
        else if(s1->composite < s2->composite) return(1);
        else return(0);
}

void checkfordups(sp)
Student *sp;
{
        // printf("fafdad");
        // printf("%d\n",sp==NULL);
        // printf("%s\n",sp->name);
        // printf("111Calculating statistics...\n");
        // printf("%d\n",sp->cnext==NULL);
        // printf("111Calculating statistics...\n");

        // printf("%s\n", sp->name);
        
        if(sp != NULL && sp->cnext != NULL)
        while(sp != NULL && sp->cnext != NULL) {
                // printf("%s\n",sp->name);
                // printf("%s\n",sp->cnext->name);
                if(!comparename(sp, sp->cnext))
                        warning("Duplicate entry for student: %s, %s.",
                                sp->surname, sp->name);
                if(sp != NULL && sp->cnext != NULL)sp = sp->cnext;
        }
        
        
        
}
