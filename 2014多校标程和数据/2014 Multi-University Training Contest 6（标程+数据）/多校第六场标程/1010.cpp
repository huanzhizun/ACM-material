#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
struct node{
    int sg[16];
    int cp[14];
    int tr[14][3];
    int bomb[14][2];
    int tot; 
}A,B;
char a[50],b[50];
void Pre_Work(node &x,char y[]){
    int i,j,k,len;
    memset(&x,0,sizeof(x));
    x.tot=len=strlen(y);
    for(i=0;i<len;i++){
        int t;
        if(y[i]>='3'&&y[i]<='9')t=y[i]-'2';
        else if(y[i]=='T')t=8;
        else if(y[i]=='J')t=9;
        else if(y[i]=='Q')t=10;
        else if(y[i]=='K')t=11;
        else if(y[i]=='A')t=12;
        else if(y[i]=='2')t=13;
        else if(y[i]=='X')t=14;
        else if(y[i]=='Y')t=15;
        x.sg[t]++;
        if(x.sg[0]<t)x.sg[0]=t;
    }
    for(i=1;i<=13;i++){
        if(x.sg[i]>1)x.cp[i]=1,x.cp[0]=i;
        if(x.sg[i]>2)x.tr[i][0]=1,x.tr[0][0]=i;
        if(x.sg[i]>3)x.bomb[i][0]=1,x.bomb[0][0]=i;
    }
    for(i=1;i<=13;i++){
        if(x.tr[i][0]==0)continue;
        for(j=1;j<=15;j++){
            if(j==i)continue;
            if(x.sg[j]){
                x.tr[i][1]=1;
                x.tr[0][1]=i;
                break;
            }
        }
        for(j=1;j<=13;j++){
            if(j==i)continue;
            if(x.cp[j]){
                x.tr[i][2]=1;
                x.tr[0][2]=i;
                break;
            }
        }
    }
    for(i=1;i<=13;i++){    //ŽŠÀíËÄŽø¶þ ËÄŽøÁœ¶Ô
        if(x.bomb[i][0]==0)continue;
        int cnt=0;
        for(j=1;j<=15;j++){
            if(j==i)continue;
            if(x.sg[j])cnt+=x.sg[j];
            if(cnt>=2){
                x.bomb[i][1]=1;
                x.bomb[0][1]=i;
                break;
            }
        }
    }
}
bool Check(){
    if(A.sg[14]&&A.sg[15])return true;//ÓÐÍõÕš±ØÓ® 
    if(A.tot==1||(A.tot==2&&A.cp[0]))return true;//Ò»ÊÖÅÆ±ØÓ® 
    if((A.tot==3&&A.tr[0][0])||(A.tot==4&&A.tr[0][1])||(A.tot==5&&A.tr[0][2]))return true;
    if((A.tot==4&&A.bomb[0][0])||(A.tot==6&&A.bomb[0][1]))return true;
    if(B.sg[14]&&B.sg[15])return false;//¶ÔÃæÍõÕšŸÍÊä 
    if(A.bomb[0][0]>=B.bomb[0][0]&&A.bomb[0][0]>0)return true;//ÓÐÕšÇÒŽó 
    if(A.bomb[0][0]<B.bomb[0][0])return false;
    if(A.sg[0]>=B.sg[0]&&A.sg[0])return true;
    if(A.cp[0]>=B.cp[0]&&A.cp[0])return true;
    if(A.tr[0][0]>=B.tr[0][0]&&A.tr[0][0])return true;
    if(A.tr[0][1]>=B.tr[0][1]&&A.tr[0][1])return true;
    if(A.tr[0][2]>=B.tr[0][2]&&A.tr[0][2])return true;
    return false;
}
int main(){
    int test;
    scanf("%d",&test);
    while(test--){
        scanf("%s%s",a,b);
        Pre_Work(A,a);
        Pre_Work(B,b);
        if(Check())printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
