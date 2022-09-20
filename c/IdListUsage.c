/*
This file goes over a log file provided as input where every string is of type
	Action ID
	Action: 0 - remove, 1 - add
	ID: any nummber from 0 to SIZE

It checks usage of each of the IDs and returns which are free in the end
Assuming each ID is free at first, and each addition is followed by removal etc (no double add/remove) 
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

typedef struct {
    int used;
    int add_c;
    int del_c;
} ENTRY;

int add(ENTRY* pE)
{
    int ret = 0;
    if (pE->used)
        ret = 1;
    pE->used = 1;
    pE->add_c++;

    return ret;
}


int remove(ENTRY* pE)
{
    int ret = 0;
    if (!pE->used)
        ret = 1;
    pE->used = 0;
    pE->del_c++;

    return ret;
}

int main(int argc, char* argv[])
{
    ENTRY entries[SIZE] = { 0 };
    
    printf("\n Input File name is %s \n", argv[1]);

    FILE* fp;
    char line[10] = {0};
    size_t len = 0;
    int index = 0;
    int action = 0; // 0 - rmeove, 1 - add
    int id = 0;
    int ret; 
    char* next_token1 = NULL;
    fopen_s(&fp, argv[1], "r");
    while (( fgets(line, 11, fp))) {
        index++;

        action = atoi(strtok_s(line, " ", &next_token1));
        char* id_str = strtok_s(NULL, " ", &next_token1);

        id = (int)strtol(id_str, NULL, 0);

        if (action) // add
        {
            ret = add(&entries[id]);
            if(ret)
                printf("ERROR in entry %d - already used. Line %d \n", id, index);
        }
        else // remove
        {
            ret = remove(&entries[id]);
            if (ret)
                printf("ERROR in entry %d - already freed. Line %d \n", id, index);
        }
    }

    // print state
    for (int i = 0; i < SIZE; i++)
    {
        ENTRY e = entries[i];
        if (!e.used)
        {
            printf("FREE ENTRY. %d, delta is %d \n", i, e.add_c - e.del_c);
        }
        else
        {       
            if(e.add_c - e.del_c != 1)
                printf("USED ENTRY with bad delta. %d, delta is %d \n", i, e.add_c - e.del_c);
        }
    }
    return 0;
}