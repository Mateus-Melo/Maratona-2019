#include <bits/stdc++.h>
#define TAM 210

#define ii pair<int,int>
#define mp make_pair
#define menor_capacidade first
#define vertice second
#define INF INT_MAX
using namespace std;
int pu[TAM],pv[TAM],way[TAM],pairV[TAM];
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
int column_scan(int matriz[TAM][TAM], int t, int covered[TAM][TAM]){
    int assignments=0;
    for(int i=0;i<t;i++){
        int cont=0;
        int pos;
        for(int j=0;j<t;j++){
            if(!matriz[j][i]&&!covered[j][i]){
                cont++;
                pos=j;
            }
        }
        if(cont==1){
            assignments++;
            for(int j=0;j<t;j++)
                covered[pos][j]++;
        }
    }
    return assignments;
}
int row_scan(int matriz[TAM][TAM],int t, int covered[TAM][TAM]){
    int assignments=0;
    for(int i=0;i<t;i++){
        int cont=0;
        int pos;
        for(int j=0;j<t;j++){
            if(!matriz[i][j]&&!covered[i][j]){
                cont++;
                pos=j;
            }
        }
        if(cont==1){
            assignments++;
            for(int j=0;j<t;j++)
                covered[j][pos]++;
        }
    }
    return assignments;
}
void novos_zeros(int matriz[TAM][TAM],int t, int covered[TAM][TAM]){
    int menor=INF;
    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            if(!covered[i][j])
                menor=min(menor,matriz[i][j]);
        }
    }
    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            if(!covered[i][j])
                matriz[i][j]-=menor;
            if(covered[i][j]==2)
                matriz[i][j]+=menor;
        }
    }
    return;
}
/*void hungarian(int matriz[TAM][TAM],int t){
    menor_linha(matriz,t);
    menor_coluna(matriz,t);
    int covered[TAM][TAM]={0};
    int assigments;
    while(true){
        for(int i=0;i<t;i++){
            for(int j=0;j<t;j++)
                cout<<matriz[i][j]<<" ";
            cout<<endl;
        }
        assigments=row_scan(matriz,t,covered);
        assigments+=column_scan(matriz,t,covered);
        if(assigments==t)
            return;
        novos_zeros(matriz,t,covered);
        cout<<endl;
        for(int i=0;i<t;i++){
            for(int j=0;j<t;j++){
                cout<<covered[i][j]<<" ";
                covered[i][j]=0;
            }
            cout<<endl;
        }
        cout<<endl;
        cin>>t;
    }
}*/

void hungarian(int matriz[TAM][TAM],int n) {
    int minv[TAM];
    bool used[TAM];

	memset(&pairV, 0, sizeof pairV);
	for(int i = 1, j0 = 0; i <= n; i++) {
		pairV[0] = i;
		memset(&minv, INF, sizeof(minv));
		memset(&used, false, sizeof(used));
		do {
			used[j0] = true;
			int i0 = pairV[j0], delta = INF, j1;
			for(int j = 1; j <= n; j++) {
				if (used[j]) continue;
				int cur = matriz[i0][j] - pu[i0] - pv[j];
				if (cur < minv[j])
					minv[j] = cur, way[j] = j0;
				if (minv[j] < delta)
					delta = minv[j], j1 = j;
			}
			for(int j = 0; j <= n; j++) {
				if (used[j])
					pu[pairV[j]] += delta, pv[j] -= delta;
				else minv[j] -= delta;
			}
			j0 = j1;
		} while(pairV[j0] != 0);
		do {
			int j1 = way[j0];
			pairV[j0] = pairV[j1];
			j0 = j1;
		} while(j0);
	}
}
void negates(int matriz[TAM][TAM],int t){
    for(int i=1;i<=t;i++){
        for(int j=1;j<=t;j++)
            matriz[i][j]=-matriz[i][j];
    }

}
int main() {
    ios::sync_with_stdio(false);
    int t;
    int matriz[TAM][TAM];
    Arco grafo[TAM][TAM];
    cin>>t;
    for(int i=1;i<=t;i++){
        for(int j=1;j<=t;j++){
            cin>>matriz[i][j];
            matriz[i][j]=round(100*log(matriz[i][j]));
        }
    }
    negates(matriz,t);
    hungarian(matriz,t);        
    /*for(int i=0;i<t;i++){
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
    int saida[TAM];
    for(int i=1;i<=t;i++){
        for(int j=1;j<=t;j++){
            if(grafo[i][j+t].fluxo&&grafo[i][j+t].fluxo==grafo[i][j+t].capacidade){
                //cout<<i<<" "<<j<<endl;
                saida[j]=i;
                break;
            }
        }
    }

    cout<<saida[1];
    for(int i=2;i<=t;i++)
        cout<<" "<<saida[i];
    cout<<"\n";*/
    cout<<pairV[1];
    for(int i=2;i<=t;i++){
        cout<<" "<<pairV[i];
    }
    cout<<"\n";
}