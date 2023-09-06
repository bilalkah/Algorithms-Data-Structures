#include<stdio.h>
#include<stdlib.h>

typedef struct link{
    struct link *right;
    struct link *down;
    int value;
}node;

static node *head;

node *createNode(int val){
    node *p=(node*)malloc(sizeof(node));
    if(p==NULL){
        fprintf(stderr,"*createNode malloc error\n");
    }
    p->down=NULL;
    p->right=NULL;
    p->value=val;
    return p;
}

void createMatrix(int x,int y, int val){

    node *rp,*dp,*track=NULL,*chain;
    int i,j;
    chain=head;
    for(i=0, dp=head ; i<=x ; i++, chain=dp, dp=dp->down){
        if(dp->down==NULL && i<x){
            dp->down=createNode(0);
        }
        for(j=0, rp=dp ; j<=y ; j++, track=rp, rp=rp->right, chain=chain->right){
            if(rp->right==NULL && j<y){
                rp->right=createNode(0);
            }
            if(chain->down==NULL && i>0 && j>0){
                chain->down=rp;
            }
        }
    }

    track->value=val;
    
}

void printMatrix(){
    node *rp,*dp;
    for(dp=head;dp!=NULL;dp=dp->down){
        for(rp=dp;rp!=NULL;rp=rp->right){
            printf("%d",rp->value);
            if(rp->right!=NULL){
                printf(" -> ");
            }
        }
        printf("\n");
        for(rp=dp;rp!=NULL;rp=rp->right){
            if(rp->down!=NULL){
                printf("|    ");
            }
        }
        printf("\n");
        for(rp=dp;rp!=NULL;rp=rp->right){
            if(rp->down!=NULL){
                printf("V    ");
            }
        }
        printf("\n");
    }
}

void deleteMatrix(){
    node *dp,*rp,*del,*temp;
    if(head->down!=NULL){
        dp=head->down;
        rp=head;

        for(;dp!=NULL;dp=dp->down){
            while(rp){
                temp=rp;
                rp=rp->right;
                free(temp);
            }
            rp=dp;
        }

    }else{
        rp=head;
    }

    while(rp){
        temp=rp;
        rp=rp->right;
        free(temp);
    }

    

}

int main(){

    int x=1,y=1,val=10;

    head=createNode(0);
    
    
    while(x!=-1 && y!=-1 && val!=-1){
        printf("x: ");
        scanf("%d",&x);
        printf("y: ");
        scanf("%d",&y);
        printf("val: ");
        scanf("%d",&val);

        createMatrix(x,y,val);
        printMatrix();
    }
    

    /*
    createMatrix(0,0,15);
    printMatrix();
    
    createMatrix(3,0,15);
    printMatrix();
    
    createMatrix(0,3,15);
    printMatrix();

    
    createMatrix(3,3,15);
    printMatrix();
    */
    deleteMatrix();

    return 0;
}
