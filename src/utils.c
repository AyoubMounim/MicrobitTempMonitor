
#include "utils.h"


int len_string(const char buff[]){
  int len = 0;
  while (buff[len] != 0){
    len++;
  }
  return len;
}


int cmp_string(const char string_1[], const char string_2[]){
  int len_string_1 = len_string(string_1);
  int len_string_2 = len_string(string_2);
  if (len_string_1 != len_string_2){
    return 0;
  }
  for (int i=0; i<len_string_1; i++){
    if (string_1[i] != string_2[i]){
      return 0;
    }
  }
  return 1;
}