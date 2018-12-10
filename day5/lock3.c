#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

const char *test_file = "/tmp/test_lock";
int main(){
    int file_desc;
    int byte_count;
    char *byte_to_write = "A";
    
}