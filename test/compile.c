#include "jkweb/common.h"

int main(int argc, char *argv[])
{
    struct slInt *list = NULL;
    struct slInt *one = newSlInt(1);
    slAddHead(&list, one);
    slFreeList(&list);
    return(0);
}
