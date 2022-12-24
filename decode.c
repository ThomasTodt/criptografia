#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char morse[26][5] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
char novo_alfabeto[26];

void gen_new_alphabet(char* key)
{
  for (int i=0; i < (strlen(key) / 2); i++)
  {
    if(!strchr(novo_alfabeto, key[i]))
    {
      novo_alfabeto[strlen(novo_alfabeto)] = key[i];
      // printf("%c\n", key[i]);
    }
  }

  for (char i = 'a'; i <= 'z' && strlen(novo_alfabeto) < 26; i++)
  {
    if(!strchr(novo_alfabeto, i))
    {
      novo_alfabeto[strlen(novo_alfabeto)] = i;
    }
  }

  // printf("novo alfabeto\n");
  // for(int i=0; i<26; i++)
  //   printf("%c ", novo_alfabeto[i]);
  // printf("\n");
}

// Function to generate a random permutation of the alphabet
void generate_permutation(char permutation[]) {
  // Initialize the permutation with the alphabet
  for (int i = 0; i < 26; i++) {
    permutation[i] = 'a' + i;
  }

  // Shuffle the permutation using the Fisher-Yates algorithm
  for (int i = 25; i >= 1; i--) {
    int j = rand() % (i + 1);
    char temp = permutation[i];
    permutation[i] = permutation[j];
    permutation[j] = temp;
  }
}

// // Function to encode a string using a given permutation of the alphabet
// void encode(char* s, char permutation[]) {
//   int length = strlen(s);
//   for (int i = 0; i < length; i++) {
//     // Only encode alphabetical characters
//     if (s[i] >= 'a' && s[i] <= 'z') {
//       s[i] = permutation[s[i] - 'a'];
//     } else if (s[i] >= 'A' && s[i] <= 'Z') {
//       s[i] = permutation[s[i] - 'A'] - 32;
//     }
//   }
// }

// Function to decode a string using a given permutation of the alphabet
void decode(char* s, char permutation[]) {
  int length = strlen(s);
  for (int i = 0; i < length; i++) {
    // Only decode alphabetical characters
    if (s[i] >= 'a' && s[i] <= 'z') {
      for (int j = 0; j < 26; j++) {
        if (s[i] == permutation[j]) {
          s[i] = 'a' + j;
          break;
        }
      }
    } else if (s[i] >= 'A' && s[i] <= 'Z') {
      for (int j = 0; j < 26; j++) {
        if (s[i] == permutation[j] - 32) {
          s[i] = 'A' + j;
          break;
        }
      }
    }
  }
}

// void postencode(char* s, char* key, char* result)
// {
//   printf("\n  partially Encoded string: %s\n", s);

//   int lenght = strlen(s)-1;
//   for (int i=0; i < lenght; i++) 
//   {
//     printf("morse[%c]: %s\n", (s[i]), morse[s[i] - 'a']);
//     s[i] = novo_alfabeto[s[i] - 'a'];
//     printf("concatena: %s\n", morse[s[i] - 'a']);
//     strcat(result, morse[s[i] - 'a']);
//     strcat(result, "/");
//     printf("\n  partially Encoded string: %s\n", result);
//   }

//   int key_separator = ((strlen(key)-1) / 2)+1;
//   int tmp;

//   for (int i=0; i < strlen(result); i++) 
//   {
//     tmp = (((rand() % 13) + 1) * 2);
//     printf("numero: %d\n", tmp);
//     while(novo_alfabeto[tmp-2] == key[key_separator] || novo_alfabeto[tmp-1] == key[key_separator])
//       tmp = (((rand() % 13) + 1) * 2);

//     if (result[i] == '.')
//     {
//       result[i] = novo_alfabeto[tmp-2];
//       printf("letra: %c\n", novo_alfabeto[tmp-2]);
//     }
//     else if (result[i] == '-')
//     {
//       result[i] = novo_alfabeto[tmp-1];
//       printf("letra: %c\n", novo_alfabeto[tmp-1]);
//     }
//     else if (result[i] == '/')
//     {
//       result[i] = key[key_separator];
//       printf("separa: %c\n", key[key_separator]);
//       key_separator++;
//       if (key_separator == strlen(key)-1) key_separator = ((strlen(key)-1) / 2)+1;
//     }
//      printf("RESULT: %s\n---\n", result);
//   }

//   printf("RESULT: %s\n---\n", result);

// }


void predecode(char* s, char* key, char* result)
{
  // printf("oii\n");
  int lenght = strlen(s);
//   for (int i=0; i < lenght; i++) 
//   {
//     for (int j=0; j < 26; j++)
//     {
//       if (s[i] == novo_alfabeto[j])
//       {
//         s[i] = 'a' + j;
//         break;
//       }
//     }
//   }

  // printf("%s\n", s);

  int key_separator = (strlen(key) / 2) - ((strlen(key)-1) % 2);

  for (int i=0; i < strlen(s)-1; i++) 
  {
    if (s[i] == key[key_separator])
    {
      s[i] = '/';
      key_separator++;
      if (key_separator == strlen(key)-1) key_separator = (strlen(key) / 2  - ((strlen(key)-1) % 2));
      continue;
    }
    else if (s[i] % 2)
    {
      s[i] = '.';
    }
    else if ( !(s[i] % 2) )
    {
      s[i] = '-';
    }
  }

  // printf("%s\n", s);

  // decodifica o morse
  char tmp[5] = "\0\0\0\0\0";
  int tam_letra = 0;
  int iguais;
  for (int i=0; i < strlen(s); i++)
  {
    if (s[i] != '/')
    {
      tmp[tam_letra] = s[i];
      tam_letra++;
    }
    else
    {
    //   printf("%d, %s\n", tam_letra, tmp);  
    
      for (int j=0; j < 26; j++)
      {
        if(strlen(morse[j]) != tam_letra)
            continue;

        iguais = 1;
        for (int k=0; k<tam_letra; k++)
        {
            if(tmp[k] != morse[j][k])
            {
                // printf("%c, %c\n", tmp[k], morse[j][k]);
                iguais = 0;
                break;
            }
        }
        // printf("iguais: %d, j: %d\n", iguais, j);
        if ( iguais )
        {
          result[strlen(result)] = 'a' + j;
          tmp[0] = '\0';
          tmp[1] = '\0';
          tmp[2] = '\0';
          tmp[3] = '\0';
          tmp[4] = '\0';
          tam_letra = 0;
          break;
        }
      }
    }
  }

  // printf("RESULT: %s\n", result);

//   printf("oii\n");

  // mais uma desconversao do novo alfabeto
  lenght = strlen(result);
  for (int i=0; i < lenght; i++) 
  {
    for (int j=0; j < 26; j++)
    {
      if (result[i] == novo_alfabeto[j])
      {
        result[i] = 'a' + j;
        break;
      }
    }
  }
}


int main(int argc, char** argv) {
  // Seed the random number generator with the current time
//   srand(time(NULL));

//   // Get the string to encode from the user
//   char s[1024*10];
//   printf("Enter a string to encode: ");
//   fgets(s, 1024*10, stdin);

//   // Generate a random permutation of the alphabet
//   char permutation[26];
//   generate_permutation(permutation);

//   // Encode the string
//   encode(s, permutation);

  char key[1024*10];
  printf("Enter the key to encode: ");
  fgets(key, 1024*10, stdin);
  gen_new_alphabet(key);
//   // cut the key in half. half to the separators, half to change alphabet order

//   char result[1024*10];
//   postencode(s, key, result);

//   // Print the encoded string
//   printf("Encoded string: %s\n", result);

  // get permutation
  char permutation[27];
  printf("Enter permutation to decode: ");
  fgets(permutation, 30, stdin);

  // Get the encoded string from the user
  char encoded[1024*10], encoded2[1024*10];
  printf("Enter an encoded string to decode: ");
  fgets(encoded, 1024*10, stdin);

  // Decode the string
  predecode(encoded, key, encoded2);
  decode(encoded2, permutation);

  // Print the decoded string
  printf("Decoded string: %s\n", encoded2);

  return 0;
}

