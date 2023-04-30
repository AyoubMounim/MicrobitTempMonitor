
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

/*
void blink(int n_times){
    int i, k;
    static const unsigned ssod[] = {
        _ROW(ROW1, 0, 1, 0, 1, 0),
        _ROW(ROW3, 1, 0, 1, 0, 1),
        _ROW(ROW5, 0, 1, 0, 1, 0),
    };

    GPIO0_DIR = LED_MASK0;
    GPIO1_DIR = LED_MASK1;

    for (int n = 0; n < n_times; n++){
        for (k = 33; k > 0; k--){
            for (i = 0; i < 6; i += 2){
                GPIO0_OUT = ssod[i];
                GPIO1_OUT = ssod[i+1];
                delay_loop(5000);
            }
        }
        GPIO0_OUT = 0;
        GPIO1_OUT = 0;
        delay_loop(100000);
    }
    return;
}
*/
