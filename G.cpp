#include <bits/stdc++.h>
#define TAM 210

#define ii pair<int,int>
#define mp make_pair
#define menor_capacidade first
#define vertice second
#define INF INT_MAX
using namespace std;
int pu[TAM],pv[TAM],way[TAM],pairV[TAM];

void hungarian(int matriz[TAM][TAM],int n ) {
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
    cin>>t;
    for(int i=1;i<=t;i++){
        for(int j=1;j<=t;j++){
            cin>>matriz[i][j];
            matriz[i][j]=round(10000*log(matriz[i][j]));
        }
        
    }
    negates(matriz,t);
    hungarian(matriz,t);
    cout<<pairV[1];
    for(int i=2;i<=t;i++){
        cout<<" "<<pairV[i];
    }
    cout<<"\n";
}