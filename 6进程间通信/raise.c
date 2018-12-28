#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
    printf("raise before \n");
    //相当于_exit()
    raise(9);
    printf('raise after \n');
    return 0;
}
