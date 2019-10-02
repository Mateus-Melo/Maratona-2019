#include <bits/stdc++.h>
#define TAM 210

#define ii pair<int,int>
#define mp make_pair
#define menor_capacidade first
#define vertice second
#define INF INT_MAX
using namespace std;
struct Arco{
    int capacidade,fluxo;
    Arco(int c,int f){
        capacidade=c;
        f=fluxo;
    }
    Arco(){
        capacidade=fluxo=0;
    }
    Arco(int c){
        capacidade=c;
        fluxo=0;
    }
};
void satura(Arco grafo[TAM][TAM],vector<int>&precede, int t, int menor){
    while(precede[t]!=-1){        
        grafo[precede[t]][t].fluxo+=menor;
        grafo[t][precede[t]].capacidade+=menor;
        t=precede[t];
    }
}
bool bfs_satura(Arco grafo[TAM][TAM],int s, int t){
    ii fila[TAM];
    int ini,fim;
    ini=0;
    fim=1;
    vector<int>precede(TAM,-1);    
    fila[ini]=mp(INF,s);
    while(ini<fim){
        ii davez=fila[ini++];
        if(davez.vertice==t){
            satura(grafo, precede, t, davez.menor_capacidade);
            return true;
        }
            
        for(int i=0;i<TAM;i++){
            if(grafo[davez.vertice][i].capacidade-grafo[davez.vertice][i].fluxo&&precede[i]==-1&&i!=s){
                precede[i]=davez.vertice;
                fila[fim++]=mp(min(davez.menor_capacidade,grafo[davez.vertice][i].capacidade-grafo[davez.vertice][i].fluxo),i);

            }
        }
    }
    return false;
}

int edmond_karp(Arco grafo[TAM][TAM],int s,int t){
    int fluxo_max=0;
    while(bfs_satura(grafo,s,t));
    for(int i=1;i<t;i++)
        fluxo_max+=grafo[i][t].fluxo;
    return fluxo_max;
}

void inicia_fluxo(Arco grafo[TAM][TAM],int s,int t){
    for(int i=1;i<t;i++){
        for(int j=1;j<t;j++){
            if((grafo[0][i].capacidade-grafo[0][i].fluxo)&&(grafo[i][j].capacidade-grafo[i][j].fluxo)&&(grafo[j][t].capacidade-grafo[j][t].fluxo)){
                grafo[0][i].fluxo++;
                grafo[i][0].capacidade++;
                grafo[i][j].fluxo++;
                grafo[j][i].capacidade++;
                grafo[j][t].fluxo++;
                grafo[t][j].capacidade++;
                break;
            }
        }
    }
    
    
}
void menor_linha(int matriz[TAM][TAM], int t){
    for(int i=0;i<t;i++){
        int menor=INF;
        for(int j=0;j<t;j++)
            menor=min(menor,matriz[i][j]);
        for(int j=0;j<t;j++){
            matriz[i][j]-=menor;
        }
    }
}
void menor_coluna(int matriz[TAM][TAM], int t){
    for(int i=0;i<t;i++){
        int menor=INF;
        for(int j=0;j<t;j++)
            menor=min(menor,matriz[j][i]);
        for(int j=0;j<t;j++){
            matriz[j][i]-=menor;
        }
    }
}
int direcao(int matriz[TAM][TAM],int linha,int col,int t){
    int ret=0;
    for(int i=0;i<t;i++){
        ret-=(matriz[linha][i]==0);
        ret+=(matriz[i][col]==0);
    }
    cout<<" afds"<<ret<<endl;
    return ret;
}

bool colore(int matriz[TAM][TAM],int linha,int col, int dir,int cores[TAM][TAM], int t){
    cout<<linha<<" "<<col<<" "<<cores[linha][col]<<" "<<dir<<endl;
    if(cores[linha][col]==2)
        return 0;
    if(dir>0 && cores[linha][col]==1)
        return 0;
    if(dir<=0 && cores[linha][col]==-1)
        return 0;
    for(int i=0;i<t;i++){
        if(dir>0){
            if(cores[i][col])
                cores[i][col]=2;
            else
                cores[i][col]=1;
        }
        else{
            if(cores[linha][i])
                cores[linha][i]=2;
            else
                cores[linha][i]=-1;
        }
    }
    cout<<"aqui"<<endl;
    return 1;
}

int num_linhas(int matriz[TAM][TAM],int t, int cores[TAM][TAM]){
    int ret=0;
    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            if(!matriz[i][j])
                ret+=colore(matriz,i,j,direcao(matriz,i,j,t),cores,t);
        }
    }
    cout<<"aaaa"<<ret<<endl;
    return ret;
}

void novos_zeros(int matriz[TAM][TAM],int t,int cores[TAM][TAM]){
    int menor=INF;
    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            if(!cores[i][j])
                menor=min(menor,matriz[i][j]);
        }
    }
    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            if(!cores[i][j])
                matriz[i][j]-=menor;
            else if(cores[i][j]==2)
                matriz[i][j]+=menor;

        }
    }
    
}

void hungarian(int matriz[TAM][TAM], int t){
    menor_linha(matriz,t);
    menor_coluna(matriz,t);
    int cores[TAM][TAM]={0};
    int aut;
    while((aut=num_linhas(matriz,t,cores))<t){
        cout<<"kjngfsdjgf"<<aut<<endl;
        cin>>aut;
        novos_zeros(matriz,t,cores);
        memset(cores,0,sizeof(cores));
    }
    return;

}
int main() {
    ios::sync_with_stdio(false);
    int t;
    int matriz[TAM][TAM];
    Arco grafo[TAM][TAM];
    cin>>t;
    for(int i=0;i<t;i++)
        for(int j=0;j<t;j++)
            cin>>matriz[i][j];
    hungarian(matriz, t);
    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            cout<<matriz[i][j]<<" ";
            if(!matriz[i][j])
                grafo[i+1][j+t+1].capacidade=1;
        }
        cout<<endl;
    }
    for(int i=1;i<=t;i++){
        grafo[0][i].capacidade=1;
        grafo[i+t][2*t+1].capacidade=1;
    }
    inicia_fluxo(grafo,0,2*t+1);
    cout<<edmond_karp(grafo,0,2*t+1)<<endl;
    for(int i=0;i<=2*t+1;i++){
        for(int j=0;j<=2*t+1;j++)
            cout<<grafo[i][j].fluxo<<" ";
        cout<<endl;
    }
    cout<<endl;
    //cin>>t;
    for(int i=0;i<=2*t+1;i++){
        for(int j=0;j<=2*t+1;j++)
            cout<<grafo[i][j].capacidade<<" ";
        cout<<endl;
    }
    for(int i=1;i<=t;i++){
        for(int j=1;j<=t;j++){
            if(grafo[i][j+t].fluxo&&grafo[i][j+t].fluxo==grafo[i][j+t].capacidade){
                cout<<j<<endl;
                break;
            }
        }
    }
}