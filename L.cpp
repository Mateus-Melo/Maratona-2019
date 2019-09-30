#include<bits/stdc++.h>
#define TAM 100100
#define pb push_back
#define p push
#define ull unsigned long long
#define ii pair<int,int>
#define vi vector<ull>
#define vvi vector<vi>
#define vii vector<ii>
#define vvii vector<vii>
#define mp make_pair
#define x first

#define y second

using namespace std;
vi pot;
ull base[6]={1,2,2,4,2,4};
ull func(ull pos){
    //cout<<pos<<endl;
    if(pos<=5)
        return base[pos];
    auto it=lower_bound(pot.begin(),pot.end(),pos);
    if(it==pot.end())
        return 0;
    if(*it==pos)
        return 2;
    //cout<<*it<<endl;
    ull pot1=*(it-1),pot2=pot1*2;
    ull pot_a=*(it-2);
    ull mid=(pot1+pot2)/2;
    if(pos<mid)
        return func(pos-pot1+pot_a);
    return 2*func(pos-pot1+pot_a);
}

int main(){
    ios::sync_with_stdio(false);
    
    pot.pb(1);
    while(pot.back()<(ull)1e18){
        pot.pb(2*pot.back());
    }
    //cout<<pot.back()<<endl;
    ull n;
    cin>>n;
    //COUT<<
    cout<<func(n)<<endl;

    
    



    return 0;
}