#include<bits/stdc++.h>
#define TAM 100100
#define pb push_back
#define p push
#define ii pair<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<ii>
#define vvii vecotr<vii>
#define TAM 100100
#define s size
#define f front
#define pp pop_back
#define qi queue<int>
#define si stack<int>
#define mp make_pair
using namespace std;
int niveis_ini[TAM],niveis_fim[TAM];
vi folhas;
vi maxi;
int fila[TAM],ini,fim;
void bfs(vvi &grafo){
    //qi fila;
    //fila.p(1);
    fila[0]=1;
    ini=0;
    fim=1;
    niveis_ini[1]=1;
    int v;
    while(ini<fim){
        v=fila[ini];
        ini++;
        bool c=true;
        for(auto i:grafo[v]){
            if(!niveis_ini[i]){
                //cout<<v<<" "<<i<<endl;
                fila[fim++]=i;
                niveis_ini[i]=niveis_ini[v]+1;
                //cout<<niveis_ini[i]<<endl;;
                c=false;
            }
        }
        if(c)
            folhas.pb(v);
    }

}
int dfs(vvi &grafo, int v){
    if(!niveis_ini[v])
        return 0;
    //niveis_ini[v]=0;
    //cout<<v<<endl;
    for(auto i:grafo[v]){
        //cout<<i<<" "<<v<<endl;
        if(niveis_ini[v]>niveis_ini[i]){
            int aux = dfs(grafo,i)+1;
            niveis_ini[v]=0;
            return aux;
            
        }
    }
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    int n,k,pai;
    cin>>n>>k;
    vvi grafo(n+1);
    for(int i=2;i<=n;i++){
        cin>>pai;
        grafo[pai].pb(i);
        grafo[i].pb(pai);
    }
    
    bfs(grafo);
    //sort(folhas.rbegin(),folhas.rend());
    grafo[1].pb(0);
    //cout<<folhas.size()<<endl;
    for(auto i=folhas.rbegin();i!=folhas.rend();i++){
        //cout<<i.second<<endl;;
        maxi.pb(dfs(grafo,*(i)));
        //cout<<"a"<<maxi.back()<<endl;
    }
    sort(maxi.rbegin(),maxi.rend());
    int acc=0;
    for(int i=0;i<k;i++)
        acc+=maxi[i];
    cout<<acc<<"\n";
    
}