#include <bits/stdc++.h>
#define TAM 2020
using namespace std;
int pais[TAM],niveis[TAM];
struct No{
    int x,y,s; 
};
double dist(No a, No b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}
int find(int v){
    if(pais[v]==v)
        return v;
    return pais[v]=find(pais[v]);
}
void uniao(int v1,int v2){
    v1=find(v1);
    v2=find(v2);
    if(v1!=v2){
        if(niveis[v1]>niveis[v2]){
            pais[v2]=v1;
        }
        else{
            pais[v1]=v2;
            if(niveis[v2]==niveis[v1])
                niveis[v2]++;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    
    int m,n,k,x,y,s;
    No nos[TAM];
    cin>>m>>n>>k;
    for(int i=0;i<k+4;i++){
        pais[i]=i;
        niveis[i]=0;
    }
    for(int i=0;i<k;i++)
        cin>>nos[i].x>>nos[i].y>>nos[i].s;
    if(-nos[0].s+nos[0].x<=0)
        uniao(0,k);
    if(nos[0].s+nos[0].x>=m)
        uniao(0,k+1);
    if(-nos[0].s+nos[0].y<=0)
        uniao(0,k+2);
    if(nos[0].s+nos[0].y>=n)
        uniao(0,k+3);
        
    for(int i=1;i<k;i++){
        for(int j=0;j<i;j++){
            //cout<<dist(nos[i],nos[j])<<endl;
            if(dist(nos[i],nos[j])<=nos[i].s+nos[j].s){
                //cout<<i<<" "<<j<<endl;
                uniao(i,j);
            }
        }
        if(-nos[i].s+nos[i].x<=0)
            uniao(i,k);
        if(nos[i].s+nos[i].x>=m)
            uniao(i,k+1);
        if(-nos[i].s+nos[i].y<=0)
            uniao(i,k+2);
        if(nos[i].s+nos[i].y>=n)
            uniao(i,k+3);
    }
    /*for(int i=0;i<k+4;i++)
        cout<<pais[i]<<endl;*/
    int ve=find(k),vd=find(k+1),vc=find(k+2),vb=find(k+3);
    //cout<<ve<<" "<<vc<<" "<<vd<<" "<<vb<<endl;
    if(ve==vc||ve==vd||vd==vb||vc==vb)
        cout<<"N\n";
    else
        cout<<"S\n";
}