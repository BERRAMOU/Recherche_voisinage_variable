#include <bits/stdc++.h>
using namespace std;
int emp[] ;
int sal[] ;

ifstream ifs("test.txt",ios::in);
struct result{
    string bit;
    int bit_count;
    long long z;
};

void afficher(result &res){
    cout<<res.bit<<endl;
    cout<<"Avec une difference totale de points : "<<res.z<<" , "<<" nombre de clauses prises : "<<res.bit_count<<"\n";
    cout<<endl<<endl;
}

 //range : [min, max)
int random(int mn, int mx){
   //cout<<mn<<" "<<mx<<"\n";
   static bool first = true;
   if ( first ) {
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return mn + rand() % (mx - mn);
}

string reverse(string s){
    return string(s.rbegin(), s.rend());
}

string dec_to_bin(int number){
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return dec_to_bin(number / 2) + "0";
    else
        return dec_to_bin(number / 2) + "1";
}

int eff(int k, int n, int start, vector<int> &v){
    long long ret = 0;
    for(int i = 0; i<n; i++){
        if( (1<<i) & k){
            ret += v[i];
        }
    }
    return ret;
}

int eff(string res, vector<int> &v){
    long long ret = 0;
     for(int i = 0; i<res.size(); i++){
        if(res[i]=='1')
            ret += v[i];
    }
    return ret;
}

int nombreDe1(int k){
    int ret = 0;
    while(k){
        ret += k & 1;
        k /= 2;
    }
    return ret;
}

int nombreDe1(string res){
    int ret = 0;
    for(int i = 0; i<res.size(); i++){
        if(res[i]=='1') ret++;
    }
    return ret;
}

string solutionInitiale(vector<int> &emp, vector<int> &sal){
    int N = emp.size();
    string res0;
    cout<<"division du vecteur initial en "<<(N-1)/20 + 1<<" parties pour generer une solution initiale"<<endl<<endl;
    for(int i = 0; i<(N-1)/20 + 1; i++){
        int n = min(20, N - i*20);
        result res;
        res.z = 9223372036854775807;
        res.bit_count = 1;
        for(int j = 1; j<(1<<n); j++){
            long long z = eff(j, n, i*20, emp) - eff(j, n, i*20, sal);
            z = abs(z);
            int bit_count = nombreDe1(j);
            if(bit_count * 2 < n) continue;
            if( (z * res.bit_count < res.z * bit_count) ||
                (z * res.bit_count == res.z * bit_count && bit_count > res.bit_count)
               ){
                string res1 = dec_to_bin(j);
                res.bit = reverse(string(n - res1.size(), '0') + res1);
                res.bit_count = bit_count;
                res.z = z;
                //cout<<res.n<<" "<<string(n - res1.size(), '0') + res1<<" "<<res.z<<" "<<res.bit_count<<endl;
            }
        }
        cout<<"La partie "<<i+1<<" contient "<<n<<" elements "<<"une difference de points de  "<<res.z<<" un nombre de clauses prises : "<<res.bit_count<<" la solution est : "<<res.bit<<endl;
        cout<<endl;
        res0 += res.bit;
    }
    return res0;
}

result voisin(string res0, vector<int> &emp, vector<int> &sal, int mod){
    vector<int> v;
    v.push_back( random( 0, emp.size()-(mod-1) ) );
    for(int i = 2; i <= mod; i++){
        v.push_back( random( *v.rbegin()+1, emp.size()-(mod-i) ) );
    }
    for(int i = 0; i<v.size(); i++){
        //cout<<v[i]<<" ";
        res0[v[i]] = ((res0[v[i]] - '0' + 1) % 2) + '0';
    }
    //cout<<"\n";
    result res;
    res.bit = res0;
    res.bit_count = nombreDe1(res.bit);
    res.z = abs(eff(res0, emp) - eff(res0, sal));

    //cout<<res.bit<<" "<<res.z<<" "<<res.bit_count<<"\n";

    return res;
}

int MAX_ITER = 10000;

result RVV(result res_prev, vector<int> &emp, vector<int> &sal){
    result res0 = res_prev;
    for(int i = 1; i <= emp.size(); i++){
        bool improve = false;
        for(int k = 0; k<MAX_ITER/i; k++){
             result res = voisin(res0.bit, emp, sal, i);
             if(res.bit_count * 2 < emp.size()) continue;
             if( (res.z * res0.bit_count < res0.z * res.bit_count) ||
                (res.z * res0.bit_count == res0.z * res.bit_count && res.bit_count > res0.bit_count)
               ){
                improve = true;
                res0 = res;
            }
        }
        cout<< "fin du voisinage qui comporte  " << i <<" changements\n";
        if(improve) {
            cout<< "amelioration trouvee dans ce voisinage !!!!! "<<endl;
            cout<< "La solution est :  "<<endl;afficher(res0);
            return RVV(res0, emp, sal);
        }
    }
    cout<<endl<<endl;
    cout<< "fin d execution ,";
    return res_prev;
}


void Inserer(){

    int nbre;
    ifs>>nbre;
    for(int i=0 ; i < nbre ; i++ ){
        ifs>>emp[i]>>sal[i];
    }
   // sort(difference.begin(),difference.begin()+nbre);
   // return nbre;
}

//test Pour 60 clauses

/*int emp[] = { 4, 10, 9, 7, 10, 5, 9, 9, 4, 10, 9, 7,4, 10, 9,7, 10, 5, 9, 9, 4, 10, 9, 7, 10, 5, 2, 2, 4, 10, 2, 7,4, 10, 2 ,7, 10, 5, 2, 2, 4, 10, 2, 7, 10, 5, 2, 2, 7, 5 ,5, 6, 9, 5, 6, 4, 10, 5, 5, 6 };
int sal[] = { 5, 6, 9, 5, 6, 4,7, 10, 5, 2, 2, 4, 10, 2, 7, 10, 5, 2, 2, 4, 10, 2, 7,4, 10, 2 ,10, 5, 5, 6 ,5, 5, 6, 9, 5, 6, 4, 10, 5, 5, 6, 9,5, 6, 4, 10, 5, 5, 6, 9, 5, 6, 4, 10, 5, 5, 6, 9, 5, 7 , 8 };
*/
int main(){






    cout<<"                                                          ******Negociation des contrats de travail******"<<endl<<endl;
    vector<int> empv(emp, emp+60), salv(sal, sal+60);
    string bits =  solutionInitiale(empv, salv);
    result res0, res;
    res0.bit = bits;
    res0.bit_count = nombreDe1(res0.bit);
    res0.z = abs(eff(res0.bit, empv) - eff(res0.bit, salv));

    res = RVV(res0, empv, salv);
    cout<< " le resultat final est  : "<<endl;
    afficher(res);

    return 0;
}
