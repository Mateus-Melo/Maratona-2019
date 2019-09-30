#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    int n,k,venceu=-1;
    string cartas[20];
    map<char,int>valor;
    valor['C']=0;    
    valor['A']=1;
    valor['2']=2;
    valor['3']=3;
    valor['4']=4;
    valor['5']=5;
    valor['6']=6;
    valor['7']=7;
    valor['8']=8;
    valor['9']=9;
    valor['D']=10;
    valor['Q']=11;
    valor['J']=12;
    valor['K']=13;
    cin>>n>>k;
    k--;
    for(int i=0;i<n;i++){
        cin>>cartas[i];
        cartas[i][0]=toupper(cartas[i][0]);
        cartas[i][1]=toupper(cartas[i][1]);
        cartas[i][2]=toupper(cartas[i][2]);
        cartas[i][3]=toupper(cartas[i][3]);
        if(i!=k&&cartas[i][0]==cartas[i][1]&&cartas[i][1]==cartas[i][2]&&cartas[i][2]==cartas[i][3]){
            cout<<i+1<<"\n";
            return 0;
        }
    }
    
    char carta='C';
    int o=k;
    int indice=20;
    bool c=false;
    while(true){
        
        map<char,int>cont;
        //cin>>k;
        if(carta!='C')
            cartas[k].push_back(carta);
        //cout<<cartas[k]<<endl;
        for(auto i:cartas[k]){
            cont[i]++;
            if(cont[i]==4&&c){
                cout<<k+1<<"\n";
                return 0;
                
                
            }
        }
        c=true;
        char aux='K';
        int menor=5;
        for(auto i:cont){
            //cout<<i.first<<" "<<i.second<<" "<<aux<<" "<<valor[aux]<<endl;
            if(i.second<menor||(i.second==menor&&valor[i.first]<valor[aux])){
                menor=i.second;
                aux=i.first;
            }
        }
        if(carta=='C')
            cartas[k].push_back('C');
        
        cartas[k].erase(cartas[k].find(aux),1);
        //cout<<cartas[k]<<endl;
        carta=aux;
        k++;
        k=k%n; 
    }
}