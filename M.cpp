#include<bits/stdc++.h>
#define TAM 100100
#define pb push_back
#define p push
#define ii pair<long long,long long>
#define vi vector<long long>
#define vvi vector<vi>
#define vii vector<ii>
#define vvii vector<vii>
#define mp make_pair
#define x first
#define y second

using namespace std;


int n, k, t,acc;

//vi vetor;
int vetor[TAM];
long long binarySearch(long long s){

    while(true){
        
        //cout << mid << " " << r << endl;
            long long pipocas=s*t;
            acc=0;
            int pessoas=1;
            for(int i=0;i<n;i++){
                
                if(vetor[i]>pipocas){
                    pessoas=k+1;
                    break;
                }
                    
                if(acc+vetor[i]>pipocas){
                    acc=0;
                    i--;
                    pessoas++;
                }
                else
                {
                    acc+=vetor[i];
                }
                //cout<<pessoas<<" "<<acc<<" "<<segundos<<endl;
                if(pessoas>k)
                    break;
                
            }
            if(pessoas>k)
                s++;
            else
            {
                return s;
            }
    }
            
    
}

int main(){
    ios::sync_with_stdio(false);
    //cin.tie(NULL);

    cin >> n >> k >> t;

    //vetor.resize(n);
    acc=0;
    int maior=0;
    for(int i=0; i<n; i++){
         cin >> vetor[i];
         acc+=vetor[i];
         maior=max(maior,vetor[i]);
    }
    long long s=acc/(k*t);
    s=max(s,(long long)maior/t);
    cout<<binarySearch(s)<<"\n";
    
    


    return 0;
}