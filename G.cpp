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
        //cout<<davez.vertice<<endl;
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
                //cout<<i<<" "<<j<<endl;
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
void menor_linha(int matriz[3][3], int t){
    for(int i=0;i<t;i++){
        int menor=INF;
        for(int j=0;j<t;j++)
            menor=min(menor,matriz[i][j]);
        for(int j=0;j<t;j++){
            matriz[i][j]-=menor;
        }
    }
}
void menor_coluna(int matriz[3][3], int t){
    for(int i=0;i<t;i++){
        int menor=INF;
        for(int j=0;j<t;j++)
            menor=min(menor,matriz[j][i]);
        for(int j=0;j<t;j++){
            matriz[j][i]-=menor;
        }
    }
}
bool marc[TAM][TAM];

void hungarian(int matriz[3][3], int t){
    while(true){
        vector<bool>mark_l(TAM,true);
        for(int i=0;i<t;i++){
            for(int j=0;j<t;j++){
                marc[i][j]=!matriz[i][j];
            }
        }
        for(int i=0;i<t;i++){
            for(int j=0;j<t;j++){
                if(marc[i][j]){
                    mark_l[i]=false;
                    for(int k=i+1;k<t;k++){
                        marc[k][j]=false;
                    }
                }
            }
        }
        vector<bool>mark_c(TAM,false);
        queue<int>linhas,colunas;
        for(int i=0;i<t;i++){
            if(mark_l[i]){
                linhas.push(i);
            }
        }
        while(!linhas.empty()||!colunas.empty()){
            while(!linhas.empty()){
                int l=linhas.front();
                linhas.pop();
                for(int i=0;i<t;i++){
                    if(!matriz[l][i]&&!mark_c[i]){
                        mark_c[i]=true;
                        colunas.push(i);
                    }
                }
            }
            while(!colunas.empty()){
                int c=colunas.front();
                colunas.pop();
                for(int i=0;i<t;i++){
                    if(!matriz[i][c]&&!mark_l[i]&&marc[i][c]){
                        mark_l[i]=true;
                        linhas.push(i);
                    }
                }
            }
            
        }
        int cont=0;
        for(int i=0;i<t;i++){
                cont+=!mark_l[i];
        }
            for(int i=0;i<t;i++){
                cont+=mark_c[i];
            }

            if(cont==t){
                
                return;
            }
            int menor=INF;
            for(int i=0;i<t;i++){
                if(mark_l[i]){
                    for(int j=0;j<t;j++){
                        if(!mark_c[j])
                            menor=min(menor,matriz[i][j]);
                    }
                }
            }
            for(int i=0;i<t;i++){
                for(int j=0;j<t;j++){
                    if(!mark_l[i]&&mark_c[j])
                        matriz[i][j]+=menor;
                    if(mark_l[i]&&!mark_c[j])
                        matriz[i][j]-=menor;
                }
            }
            //return;
    } 

}
int main() {
    int t=3;
    int matriz[3][3]={{2500,4000,3500},
                      {4000,6000,3500},
                      {2000,4000,2500}};
    Arco grafo[TAM][TAM];
    /*1500  4000  4500
 2000  6000  3500
 2000  4000  2500*/
    menor_linha(matriz, 3);
    menor_coluna(matriz, 3);
    hungarian(matriz, 3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
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