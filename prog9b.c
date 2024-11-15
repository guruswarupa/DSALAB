#include <stdio.h>
struct sparse
{
int row;
int col;
int val;
} s[10];
void readsparsematrix(){
    int i,j,r,c,ele,pos=0;
    printf("Enter rows and cols:\n");
    scanf("%d%d", &r,&c);
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            scanf("%d", &ele);
            if (ele != 0){
                pos++;
                s[pos].row = i;
                s[pos].col = j;
                s[pos].val = ele;
            }
        }
    }
    s[0].row = r;
    s[0].col = c;
    s[0].val = pos;
}
void triplet(){
    int i;
    printf("\nTriplet representation:\n");
    printf("Row Col Value\n");
    for (i = 0; i <= s[0].val; i++){
        printf("%d%d%d\n", s[i].row, s[i].col, s[i].val);
    }
}
void search(){
    int found=0,key,i;
    printf("Enter key:\n");
    scanf("%d", &key);
    for (i = 1; i <= s[0].val; i++){
        if (s[i].val == key){
            printf("%d%d\n", s[i].row, s[i].col);
            found=1;
            break;
        }
    }
    if(found==0)
        printf("\n element not found:");
}

void transpose(){
    int i,j;
    struct sparse trans[10];
    trans[0].row = s[0].col;
    trans[0].col = s[0].row;
    trans[0].val = s[0].val;
    int k = 1;
    for (i = 0; i < s[0].col; i++){
        for (j = 1; j <= s[0].val; j++){
            if (s[j].col == i){
                trans[k].row = s[j].col;
                trans[k].col = s[j].row;
                trans[k].val = s[j].val;
                k++;
            }
        }
    }
    for (i = 0; i <= s[0].val; i++){
        s[i] = trans[i];
    }
    triplet();
}

int main(){
    readsparsematrix();
    triplet();
    search();
    transpose();
    return 0;
}