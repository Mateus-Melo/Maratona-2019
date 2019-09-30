#include<bits/stdc++.h>
#define TAM 100100
#define pb push_back
#define p push
#define ii pair<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<ii>
#define vvii vecotr<vii>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vi vetor(n);
    int maxi = 0;
    for(int i=0; i<n; i++){
        cin >> vetor[i];
        maxi = max(maxi,vetor[i]);
    }
    
    if(maxi==vetor[0]) cout << "S" << endl;
    else cout << "N" << endl;
    
    return 0;
}