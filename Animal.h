#include <stdio.h>
#pragma pack(1)
#ifndef ANIMAL_H
#define ANIMAL_H

/**
* A structure to store animals' information.
*/
struct Animal {
  short int id;
  char name[20];
  char species[35];
  char size;
  short int age;
};

/** Animal's Class pointer.*/
typedef struct Animal Animal;


/** Print Text Menu.*/
void printTextMenu();
/** Read byte's file one byte at a time.*/
void readOneByte(FILE *fileName);
/** Read byte's file four bytes at a time.*/
void readFourBytes(FILE *fileName);
/** Display an animal's information with a given ID.*/
void displayAnimalInfo(FILE *fileName);
/** Update an animal's information with a given ID.*/
void updateAnimalInfo(FILE *fileName);
/** Delete an animal's information with a given ID, and truncate the file.*/
void deleteAndTruncate(FILE *fileName);
/** Write updated byte file to csv file.*/
void updateCSVFile(FILE *fileName);

// helper methods
/** Count digits in the number.*/
int countDigits(signed int);
/** Print Animals' information.*/
void printInfo(FILE *fileName);
#endif