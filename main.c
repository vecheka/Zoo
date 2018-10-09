#include <stdio.h>
#include "Animal.h"

int main(void) {

  

  char choice;
  FILE *byteFile;
  
  
 

  do {
    printTextMenu();
    scanf(" %c", &choice);
   
    byteFile = fopen("animals.dat", "rb");
    //  printInfo(byteFile);
    switch (choice) {
      case '1':  
        readOneByte(byteFile);
        printf("\n");
        break;
      case '2':
        readFourBytes(byteFile);
        printf("\n");
        break;
      case '3':
        displayAnimalInfo(byteFile);
        printf("\n");
        break;
      case '4':
        updateAnimalInfo(byteFile);
        printf("\n");
        break;
      case '5':
        deleteAndTruncate(byteFile);
        break;
      default:
        break; 
    }
  
  } while (choice != '0');

  updateCSVFile(byteFile);
  fclose(byteFile);
}