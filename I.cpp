#include<bits/stdc++.h>
#define TAM 410
#define pb push_back
#define s size
#define ii pair<int,int>
#define vii vector<ii>
#define vvii vector<vii>
#define peso first
#define no second
#define mp make_pair
#define INF 1000000000
#define vi vector<int>
#define vvi vector<vi>
using namespace std;
struct Consulta{
    int origem,destino,k,pos,resposta;
    bool c;
    Consulta(){}
    Consulta(int o,int d,int k,bool c, int p){
        origem=o;
        destino=d;
        this->k=k;
        this->c=c;
        pos=p;
    }
};
bool comp(Consulta c1, Consulta c2){
    return c1.k<c2.k;
}
bool comp2(Consulta c1, Consulta c2){
    return c1.pos<c2.pos;
}
int main(){
    ios::sync_with_stdio(false);
    int n,m,o,d,p,grafo[TAM][TAM],grafo2[TAM][TAM],q,temps[TAM];
    ii temperaturas[TAM];
    Consulta consultas[100100];
    vvi nos(TAM);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>o;
        temperaturas[i]=mp(o,i+1);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            grafo[i][j]=INF;
    sort(temperaturas,temperaturas+n);
    nos[1].pb(temperaturas[0].second);
    int pos=1,ant=temperaturas[0].first;
    temps[1]=1;
    for(int i=1;i<n;i++){
        if(temperaturas[i].first!=temperaturas[i-1].first)
            pos++;
        nos[pos].pb(temperaturas[i].second);
        temps[i+1]=pos;
    }
    /*for(int i=1;i<=n;i++)
        cout<<temps[i]<<" ";
    cout<<endl;
    cout<<nos[1].size()<<" "<<nos[2].size()<<endl;*/
    //cout<<nos[2][0]<<" "<<nos[2][1]<<endl;
    while(m--){
        cin>>o>>d>>p;
        grafo[o][d]=p;
        grafo[d][o]=p;
    }
    for(int i=1;i<=n;i++)
        grafo[i][i]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            grafo2[i][j]=grafo[i][j];
       
    
    bool c;
    int ka;
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>o>>d>>ka>>c;
        //ka=temps[ka];
        //cout<<k<<endl;
        consultas[i]=Consulta(o,d,ka,c,i);
        
    }
    sort(consultas,consultas+q,comp);
    int kM=0,km=0;
    for(int z=0;z<q;z++){
        int aux;
        if(consultas[z].c){
            while(kM<consultas[z].k){
                //cout<<"a"<<kM<<endl;
                kM++;
                //cout<<"a"<<kM<<endl;
                //cout<<pos-kM+1<<endl;
                for(int l=0;l<nos[pos-kM+1].size();l++){
                    for(int i=1;i<=n;i++){
                        for(int j=1;j<=n;j++){                            
                            grafo2[i][j]=min(grafo2[i][j],grafo2[i][nos[pos-kM+1][l]]+grafo2[nos[pos-kM+1][l]][j]);
                            //cout<<grafo2[i][j]<<" ";    
                        }
                        
                    }
                    //cout<<endl;
                }
                //cout<<endl;
                
            }
            //cout<<consultas[z].origem<<" b "<<consultas[z].destino<<endl;
            aux=grafo2[consultas[z].origem][consultas[z].destino];
        }
        else{
            while(km<consultas[z].k){
                km++;
                //cout<<km<<endl;
                for(int l=0;l<nos[km].size();l++){
                    for(int i=1;i<=n;i++){
                        for(int j=1;j<=n;j++){                            
                                grafo[i][j]=min(grafo[i][j],grafo[i][nos[km][l]]+grafo[nos[km][l]][j]);
                            }
                        }
                    }
            }
            aux=grafo[consultas[z].origem][consultas[z].destino];
        }
        if(aux==INF)
            consultas[z].resposta=-1;
        else
            consultas[z].resposta=aux;
    }
    sort(consultas,consultas+q,comp2);
    for(int i=0;i<q;i++)
        cout<<consultas[i].resposta<<"\n";
    return 0;
}