void swap(int * x, int * y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main(int argc, char const *argv[])
{
    int x = 1;
    int y = 5;
    swap(&x,&y);
    printf("%i %i", x,y);
    return 0;
}
