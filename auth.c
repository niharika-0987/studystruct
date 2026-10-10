
#include <string.h>
#define HSIZE 10
char users[HSIZE][20];
int passHash[HSIZE];
int used[HSIZE];

int hashKey(char s[]) {
    int sum = 0, i;
    for (i = 0; s[i] != '\0'; i++)
        sum = sum + s[i];
    return sum % HSIZE;
}

int hashPass(char s[]) {
    int h = 0, i;
    for (i = 0; s[i] != '\0'; i++)
        h = h * 31 + s[i];
    return h;
}

void signup(char name[], char pass[]) {
    int i = hashKey(name), count = 0;
    while (used[i] && count < HSIZE) 
    {     
        i = (i + 1) % HSIZE;
        count++;
    }
    if (count == HSIZE) {
        printf("User table full\n");
        return;
    }
    strcpy(users[i], name);
    passHash[i] = hashPass(pass);
    used[i] = 1;
    printf("Signup done\n");
}

int login(char name[], char pass[]) {
    int i = hashKey(name), count = 0;
    while (used[i] && count < HSIZE) {
        if (strcmp(users[i], name) == 0 && passHash[i] == hashPass(pass))
            return 1;
        i = (i + 1) % HSIZE;
        count++;
    }
    return 0;
}

