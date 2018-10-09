
#include <stdio.h>
#include <string.h>
#include "Animal.h"

/**
* Print text menu to the console.
*/
void printTextMenu() {
  printf("Welcome to the Animals' World!\n");
  printf("Make your choice, summoners: \n");
  printf(" 0.To Quit\n");
  printf(" 1.Read one byte at a time\n");
  printf(" 2.Read four bytes at a time\n");
  printf(" 3.Give ID, and get your animal\n");
  printf(" 4.Give ID, and update your animal\n");
  printf(" 5.Overwrite your animal\n");
  printf("Enter your choice: ");
}

/**
* Read the binary file one byte at a time, and print it as
* a single character between the ASCII value of 32-127
* else print a space.
* @param fileName - file ptr of the binary file
*/
void readOneByte(FILE *fileName) {
    
    unsigned char character;
    unsigned int charCount = 0;
    while (fread(&character, sizeof(unsigned char), 1, fileName)) {
      if (charCount > 80) {
        printf("\n");
        charCount = 0;
      }
      if (character >= 32 && character <= 127) printf("%c", character);
      else printf(" ");
      charCount++;
    }
}

/**
* Read the binary file four bytes at a time, and print it as
* a signed integer to the console with space between.
* @param fileName - file ptr of the binary file
*/
void readFourBytes(FILE *fileName) {
    
    signed int num;
    unsigned int numCount = 0;
   
    while (fread(&num, sizeof(signed int), 1, fileName)) {
      numCount += countDigits(num) + 1;
      if (numCount > 80) {
        printf("\n");
        numCount = 0;
      }
      printf("%d ", num);
     
     
    }
}

/** 
* Display an animal's information with the given ID.
* @param fileName - file ptr of the binary file
*/
void displayAnimalInfo(FILE *fileName) {
  int id;
  char *unknown = "unknown";
  printf("Please enter the Animal's ID: ");
  scanf("%d", &id);
  if (id == 0) {
    printf("Animal doesn't exist.\n");
    return;
  }
  Animal a = {0, "", "", '0', 0};
  fseek(fileName, sizeof(a) * (id - 1), 0);
  int exist = fread(&a, sizeof(a), 1, fileName);
  printf("%s\n", a.name);
  if (!strcmp(unknown, a.name)) {
    printf("Animal has empty records.\n");
  } else if (!exist) {
    printf("Animal doesn't exist.\n");
  } else {
    printf("Animal's ID is %d \n", a.id);
    printf("Animal's name is %s \n", a.name);
    printf("Animal's Species is %s \n", a.species);
    printf("Animal's size is %c \n", a.size);
    printf("Animal's age is %d \n", a.age);
  }

}

/**
* Update an animal's information with a given ID.
* @param fileName - file ptr of the binary file
*/
void updateAnimalInfo(FILE *fileName) {
  
  fclose(fileName);
  fileName = fopen("animals.dat", "rb+");

  int id;
  printf("Please enter the Animal's ID: ");
  scanf("%d", &id);
  if (id == 0) {
    printf("Animal doesn't exist.\n");
    return;
  }

  Animal a = {0, "", "", '0', 0};
  fseek(fileName, -(sizeof(a) * (id - 1)), 0);
  int exist = fread(&a, sizeof(a), 1, fileName);
  char newName[20];
  char newSpecies[35];
  unsigned char newSize;
  int newAge;
  if (exist) {
    printf("Enter new size: ");
    scanf(" %c", &newSize);
    printf("Enter new age: ");
    scanf("%d", &newAge);
    printf("Enter new name: ");
    scanf(" %[a-zA-Z ]+", &newName);
    printf("Enter new species: ");
    scanf(" %[a-zA-Z ]+", &newSpecies);
   

    strcpy(a.name, newName);
    strcpy(a.species, newSpecies);
    a.size = newSize;
    a.age = newAge;
    a.id = id;
  }
  // printf("%s\n", a.name);
  fwrite(&a, sizeof(a), 1, fileName);
  fclose(fileName);

}


/**
* Delete an animal, and truncate the file.
* @param fileName - file ptr of the binary file
*/
void deleteAndTruncate(FILE *fileName) {
  int id;
  FILE *tempFile = fopen("temp.dat", "wb");
  printf("Please enter the Animal's ID: ");
  scanf("%d", &id);
  if (id == 0) {
    printf("Animal doesn't exist.\n");
    return;
  }

  Animal a = {0, "", "", '0', 0};
  int newID = id;
  while (fread(&a, sizeof(a), 1, fileName)) {
    if (a.id > id) {
      a.id = newID;
      // if the new id is the same to the deleted id,
      // write to the file.
      if (a.id == id) {
         fwrite(&a, sizeof(a), 1, tempFile);
      }
      newID++;
    }
    if(a.id != id) {

      fwrite(&a, sizeof(a), 1, tempFile);
    }
  }


  fclose(tempFile);
  remove("animals.dat");
  rename("temp.dat", "animals.dat");
}

/**
* Update CSV File.
* @param fileName - file ptr of the binary file
*/
void updateCSVFile(FILE *fileName) {
  FILE *test = fopen("test.csv", "w");
  char *unknown = "unknown";
  Animal a = {0, "", "", '0', 0};
  while (fread(&a, sizeof(a), 1, fileName)) {
    if (strcmp(unknown, a.name)) fprintf(test, "%d,%s,%s,%c,%d\n", a.id, a.name, a.species, a.size, a.age);
  }
  fclose(test);
}

// helper method
/** 
* Count digits in the number
* @param theNum- to count digits
* @return number of digits
*/
int countDigits(signed int theNum) {
  int count = 1;
  while(theNum / 10 != 0) {
    count++;
    theNum = theNum / 10;
  }
  return count;
}

/**
* Print animals' info to the console.
* @param fileName - file ptr of the binary file
*/
void printInfo(FILE *fileName) {
   Animal a = {0, "", "", '0', 0};
   while (fread(&a, sizeof(a), 1, fileName)) {
    printf("%d\n", a.id);
    printf("%s\n", a.name);
    printf("%s\n", a.species);
    printf("%d\n", a.age);
    printf("%c\n", a.size);
    printf("\n");
   }
}