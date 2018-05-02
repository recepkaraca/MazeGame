#include <stdio.h>
#include <stdlib.h>

struct kapi{
    int x;
    int y;
};
struct suan{
    int x;
    int y;
};

struct liste{
    struct suan deger;
    struct liste *sonraki;
};

struct liste *yigin;
struct liste *son;

int bosmu(){
    if(yigin==NULL){
        return 1;
    }else {
        return 0;
    }
}

void pop(){
    if(!bosmu()){
        yigin=yigin->sonraki;
    }else{
        printf("Yigin bos.");
    }

}
void push(int gelenx,int geleny){
    struct liste *yeni=(struct liste*)malloc(sizeof(struct liste));
    yeni->deger.x=gelenx;
    yeni->deger.y=geleny;
    yeni->sonraki=yigin;
    yigin=yeni;
}
void yigingoster(){
    while(yigin!=NULL){
        printf("x=%d y=%d ",yigin->deger.x,yigin->deger.y);
        yigin=yigin->sonraki;
    }
}

int main()
{
    srand(time(NULL));
    int n,i,j,durum=0;
    struct kapi giris;
    struct kapi cikis;

    printf("Labirentin boyutunu giriniz: ");
    scanf("%d",&n);
    //int matris[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            //matris[i][j]=rand()%2;
        }
    }


    int matris[7][7]={
        {0, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 1},
        {0, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 0},
        {1, 1, 0, 1, 1, 0, 1}
    };

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d ",matris[i][j]);
        }
        printf("\n");
    }

    do{
        printf("\nGiris kapisinin koordinatlarini giriniz.(Kapilarin kenarlar uzerinde olmasi gerekmektedir.)\n");
        printf("x=");
        scanf("%d",&giris.x);
        printf("y=");
        scanf("%d",&giris.y);
        durum=0;
        if(!((giris.x==0 && giris.y>=0 && giris.y<=n-1) || (giris.x==n-1 && giris.y>=0 && giris.y<=n-1) ||
             (giris.y==0 && giris.x>=0 && giris.y<=n-1) || (giris.y==n-1 && giris.x>=0 && giris.x<=n-1))){
            printf("\nLutfen girmis oldugunuz kapinin, kenar uzerinde olduguna emin olunuz.\n");
            durum=1;
        }else{
            if(matris[giris.x][giris.y]==0){
                printf("\nBelirlediginiz kapi kapali.\n");
                durum=1;
            }
        }
    }while(durum);
    do{
        printf("\nCikis kapisinin koordinatlarini giriniz.(Kapilarin kenarlar uzerinde olmasi gerekmektedir.)\n");
        printf("x=");
        scanf("%d",&cikis.x);
        printf("y=");
        scanf("%d",&cikis.y);
        durum=0;
        if(!((cikis.x==0 && cikis.y>=0 && cikis.y<=n-1) || (cikis.x==n-1 && cikis.y>=0 && cikis.y<=n-1) ||
             (cikis.y==0 && cikis.x>=0 && cikis.y<=n-1) || (cikis.y==n-1 && cikis.x>=0 && cikis.x<=n-1))){
            printf("\nLutfen girmis oldugunuz kapinin, kenar uzerinde olduguna emin olunuz.\n");
            durum=1;
        }else{
            if(matris[cikis.x][cikis.y]==0){
                printf("\nBelirlediginiz kapi kapali.\n");
                durum=1;
            }
        }
    }while(durum);
    int isaretlenen[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            isaretlenen[i][j]=0;
        }
    }
    struct suan suanki;
    suanki.x=giris.x;
    suanki.y=giris.y;

    yigin=(struct liste*)malloc(sizeof(struct liste));
    yigin=NULL;
    int isaret=0;
    isaretlenen[suanki.x][suanki.y]=2;
    push(suanki.x,suanki.y);

    while(suanki.x!=cikis.x || suanki.y!=cikis.y){

        if(suanki.y!=n-1 && matris[suanki.x][suanki.y+1]!=0 && isaretlenen[suanki.x][suanki.y+1]!=2){
            suanki.y++;
            isaretlenen[suanki.x][suanki.y]=2;

            isaret=1;
        }else if(suanki.x!=n-1 && matris[suanki.x+1][suanki.y]!=0 && isaretlenen[suanki.x+1][suanki.y]!=2){
            suanki.x++;
            isaretlenen[suanki.x][suanki.y]=2;

            isaret=1;
        }else if(suanki.y!=0 && matris[suanki.x][suanki.y-1] && isaretlenen[suanki.x][suanki.y-1]!=2){
            suanki.y--;
            isaretlenen[suanki.x][suanki.y]=2;

            isaret=1;
        }else if(suanki.x!=0 && matris[suanki.x-1][suanki.y] && isaretlenen[suanki.x-1][suanki.y]!=2){
            suanki.x--;
            isaretlenen[suanki.x][suanki.y]=2;

            isaret=1;
        }else{
            isaret=0;
            isaretlenen[suanki.x][suanki.y]=2;

            pop();
            if(bosmu()){
                printf("Yol yok.");
                break;
            }
            matris[suanki.x][suanki.y]=0;
            suanki.x=yigin->deger.x;
            suanki.y=yigin->deger.y;

        }
        if(isaret){
            push(suanki.x,suanki.y);
            isaretlenen[suanki.x][suanki.y]=2;
        }
        printf("Suan x=%d y=%d\n",suanki.x,suanki.y);
        printf("Kopya matris:\n");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                    printf("%d ",isaretlenen[i][j]);
            }
            printf("\n");
        }
        printf("Ilk matris:\n");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                    printf("%d ",matris[i][j]);
            }
            printf("\n");
        }

    }

    printf("Yol:\n");
    for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                    if(matris[i][j]==1 && isaretlenen[i][j]==2){
                        printf("%d ",1);
                    }else {
                        printf("%d ",0);
                    }
            }
            printf("\n");
        }

    return 0;
}
