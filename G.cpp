#include <bits/stdc++.h>
#define TAM 3
#define INF INT_MAX
using namespace std;
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
bool marc[TAM][TAM];

void hungarian(int matriz[TAM][TAM], int t, vector<int>&pessoas){
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
    int matriz[3][3]={{1500,4000,4500},
                      {2000,6000,3500},
                      {2000,4000,2500}};
    /*1500  4000  4500
 2000  6000  3500
 2000  4000  2500*/
    vector<int>pessoas(TAM,-1);
    menor_linha(matriz, 3);
    menor_coluna(matriz, 3);
    hungarian(matriz, 3,pessoas);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            cout<<matriz[i][j]<<" ";
        cout<<endl;
    }
}