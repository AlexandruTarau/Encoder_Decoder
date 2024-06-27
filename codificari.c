#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swapch (char *a, char *b) { //Face interschimbarea intre 2 caractere
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void CodificareA (char arg[], char s[], char m[][50]) {
    int i, j = 1, k = 0, n, c, l;

    strcpy(m[0], arg);
    n = strlen(arg);

    //Copiez s in matrice
    while (k < strlen(s)) {
        for (i = 0; i < n; i++) {
            if (k < strlen(s)) {
                m[j][i] = s[k++];
            } else {
                m[j][i] = ' ';
            }
        }
        j++;
    }

    //Fac interschimbarea intre coloane cu "sequential sort"
    for (c = 0; c < n; c++) {
        for (i = c + 1; i < n; i++) {
            if (m[0][c] > m[0][i]) {
                for (l = 0; l < j; l++) {
                    swapch(&m[l][c], &m[l][i]);
                }
            }
        }   
    }
    //Copiez in s, in ordine, coloanele matricii
    int q = 0;
    for (c = 0; c < n; c++) {
        for (l = 1; l < j; l++) {
            if (q <= strlen(s)) {
                s[q++] = m[l][c];
            }
        }     
    }

    s[q] = '\0';
    puts(s);
}

void CodificareB (char arg[], char s[]) {
    int nr = 0, i = 0, k = strlen(arg), p = 1;
    char aux[500];

    //Formez nr
    for (i = 1; i < k; i++) {
        p *= 10;
    }
    for (i = 0; i < k; i++) {
        nr += (arg[i] - '0') * p;
        p /= 10;
    }

    int n, swt;
    /*
    swt (switch) = {0,1} face transferul de la "abc..." la "ABC..." si invers
    n = numarul pe care lucram pentru a gasi caracterul aux[i]
    */
    strcpy(aux, s + strlen(s) - nr);
    for (i = 0; i < nr; i++) {
        if (aux[i] >= 'A' && aux[i] <= 'Z') {
            n = aux[i] + nr;
            swt = 0;
            while (n > 'Z' + 32 * swt) {
                n = ('a' - 32 * swt) + n - ('Z' + 32 * swt) - 1; 
                if (swt == 0) {
                    swt = 1;
                } else {
                    swt = 0;
                }   
            }
            aux[i] = n;  
        } else if (aux[i] >= 'a' && aux[i] <= 'z') {
            n = aux[i] + nr;
            swt = 1;
            while (n > 'Z' + 32 * swt) {
                n = ('a' - 32 * swt) + n - ('Z' + 32 * swt) - 1; 
                if (swt == 0) {
                    swt = 1;
                } else {
                    swt = 0;
                }   
            }
            aux[i] = n;
        } else {
            aux[i] = ' ';
        }
        
    }
    s[strlen(s) - nr] = '\0';
    strcpy(aux + nr, s);
    strcpy(s, aux);
    puts(s);
}

void DecodificareB(char arg[], char s[]) {
    int nr = 0, i, k = strlen(arg), p = 1;
    char aux[500], aux2[500];
    strcpy(aux, s);
    //aux[] = subsirul pentru decodificare
    //aux2[] = pt ca strcpy(s, s + nr) suprascrie gresit...in vmchecker

    //Formez nr
    for (i = 1; i < k; i++) {
        p *= 10;
    }
    for (i = 0; i < k; i++) {
        nr += (arg[i] - '0') * p;
        p /= 10;
    }
    aux[nr] = '\0';

    int n, swt;
    /*
    swt (switch) = {0,1} face transferul de la "abc..." la "ABC..." si invers
    n = numarul pe care lucram pentru a gasi caracterul aux[i]
    */
    for (i = 0; i < nr; i++) {
        if (aux[i] >= 'A' && aux[i] <= 'Z') {
            n = aux[i] - nr;
            swt = 0;
            while (n < 'A' + 32 * swt) {
                n = ('z' - 32 * swt) + n - ('A' + 32 * swt) + 1;
                if (swt == 0) {
                    swt = 1;
                } else {
                    swt = 0;
                }   
            }
            aux[i] = n;
        } else if (aux[i] >= 'a' && aux[i] <= 'z') {
            n = aux[i] - nr;
            swt = 1;
            while (n < 'A' + 32 * swt) {
                n = ('z' - 32 * swt) + n - ('A' + 32 * swt) + 1;
                if (swt == 0) {
                    swt = 1;
                } else {
                    swt = 0;
                }   
            }
            aux[i] = n;
        } else {
            aux[i] = ' ';
        }
    }

    strcpy(aux2, s + nr);
    strcat(aux2, aux);
    strcpy(s, aux2);
    puts(s);
}

void DecodificareA(char arg[], char s[], char m[][50]) {
    int i, n, j = 1, k = 0, l, c, a[500][10], q = 0; 
    n = strlen(arg);
    strcpy(m[0], arg);

    for (c = 0; c < n; c++) {
        for (i = c + 1; i < n; i++) {
            if (m[0][c] > m[0][i]) {
                swapch(&m[0][c], &m[0][i]);
                a[q][0] = c; //in a memoram indicii interschimbarilor
                a[q][1] = i;
                q++;
            }
        }
    }

    //Aflu nr de linii: j-1
    while (k < strlen(s)) {
        for (i = 0; i < n; i++) {
            if (k < strlen(s)) {
                k++;
            }
        }
        j++;
    }

    //Umplu matricea cu s in forma codificata
    k = 0;
    for (c = 0; c < n; c++) {
        for (l = 1; l < j; l++) {
            if (k < strlen(s)) {
                m[l][c] = s[k++];
            } else {
                m[l][c] = ' ';
            }
        }     
    }

    //Decodific matricea
    while (strcmp(arg, m[0])) {
        q--;
        for (l = 0; l < j; l++) {
            swapch(&m[l][a[q][0]], &m[l][a[q][1]]);
        }
    }

    //Completez s cu elementele din matricea decodificata.
    k = 0;
    for (l = 1; l < j; l++) {
        for (c = 0; c < n; c++) {
            s[k++] = m[l][c];
        }
    }
    s[k] = '\0';
    puts(s);
}

int main()
{
    char s[500], op[20], arg[50], m[500][50];

    fgets(s, 500, stdin);
    s[strlen(s) - 1] = '\0';

    for (;;) {
        fflush(stdin);
        scanf("%s", op);
        if (strcmp(op, "STOP") == 0) {
            break;
        }
        fflush(stdin);
        fgets(arg, 50, stdin);
        //elimin '\n' citit de fgets...
        arg[strlen(arg) - 1] = '\0';
        //elimin ' ' citit de fgets...
        if (arg[0] == ' ') {
            for (int i = 0; i < strlen(arg); i++) {
                arg[i] = arg[i + 1];
            }
            //strcpy(arg, arg + 1); nu merge mereu...
        }
        
        if (strcmp(op, "CodificareA") == 0) {
            CodificareA(arg, s, m);
        } else if (strcmp(op, "CodificareB") == 0){
            CodificareB(arg, s);
        } else if (strcmp(op, "DecodificareB") == 0){
            DecodificareB(arg, s);
        } else if (strcmp(op, "DecodificareA") == 0){
           DecodificareA(arg, s, m);
        }
    }

    return 0;
}