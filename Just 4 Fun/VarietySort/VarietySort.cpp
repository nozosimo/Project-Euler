/**
        VARIETY SORT
        Based on CodeChef Post (http://bit.ly/2JFlhuU)
        
        Author: Leonardo H. Añez Vladimirovna
        Compiler: GNU CCC Compiler - C++11
        Date: 06/05/2018
**/


#include <bits/stdc++.h>
#define IOS                 ios::sync_with_stdio(0);
#define ll                  long long
#define pb                  push_back
#define par(a,b)            make_pair(a,b)
#define fst                 first
#define scd                 second
#define pfor(a,b,name)      for(int i=a;i<=b;++i){cout<<name[i]<<" ";}cout<<'\n';
#define ifor(a,b,name)      for(int i=a;i<=b;++i){cin>>name[i];}
#define euclid(x1,y1,x2,y2) sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))
#define lcm(a,b)            (a*b)/(__gcd(a,b))
#define gcd(a,b)            __gcd(a,b)
#define dbg                 cout<<"umu"<<endl;

using namespace std;

const double pi = 3.14159265;
const int INF = 1<<30;
const int maxn = (1e5)+50;
const int mod = (1e9)+7;
const int lim = (1e5);

const char filename_in[] = "input.txt";
const char filename_ou[] = "output.txt";

/// FUNCIONES BOGOSORT
bool estaOrdenado(vector<int> &arr,int l,int r)
{
    int n = arr.size();
    for(int i=0;i<n-1;++i)
    {
        if(arr[i]>arr[i+1])
        {
            return false;
        }
    }
    return true;
}
void bogoSort(vector<int> &arr)
{
    int n = arr.size();
    bool srt;
    do{}while(prev_permutation(arr.begin(),arr.end()) && !estaOrdenado(arr,0,n));
}
/// FUNCIONES QUICKSORT
int indicePartes(vector<int> &arr, int l, int r)
{
    int posIndex,pivote;
    posIndex = l;
    pivote = arr[r];
    for(int i=l;i<r;i++)
    {
        if(arr[i] <= pivote)
        {
            swap(arr[posIndex], arr[i]);
            posIndex++;
        }
    }
    swap(arr[posIndex], arr[r]);
    return posIndex;
}
void quickSort(vector<int> &arr, int l, int r)
{
    if(l<r)
    {
        int ind = indicePartes(arr,l,r);
        quickSort(arr, l, ind-1);
        quickSort(arr, ind+1, r);
    }
}
/// FUNCIONES BUBBLESORT
void mayorFinal(vector<int> &arr,int n)
{
    if(n>1)
    {
        mayorFinal(arr,n-1);
        if(arr[n-2]>arr[n-1])
        {
            swap(arr[n-2],arr[n-1]);
        }
    }
}
void bubbleSort(vector<int> &arr,int n)
{
    if(n>1 && !estaOrdenado(arr,n/2,n))
    {
        mayorFinal(arr,n);
        bubbleSort(arr,n-1);
    }
}
/// FUNCIONES INSERTION SORT
void insertionSort(vector<int> &arr, int n)
{
    if(n>1)
    {
        insertionSort(arr,n-1);
        int ultimo = arr[n-1];
        int j = n-2;

        while (j>=0 && arr[j]>ultimo)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = ultimo;
    }
}


void varietySort(vector<int> &arr)
{
    int n = arr.size();

    ///PRIMERA MITAD
    vector<int> a(arr.begin(),arr.begin()+n/2);
    int asize = a.size();
    bubbleSort(a,asize);
    vector<int> a1(a.begin(),a.begin()+(asize/2));
    vector<int> a2(a.begin()+(asize/2),a.begin()+asize);
    insertionSort(a1,a1.size());
    //pfor(0,asize-1,a); //Imprime la Primera Mitad Ordenada parcialmente
    //pfor(0,a1.size()-1,a1); //Imprime la Primera Mitad Ordenada parcialmente
    //pfor(0,a2.size()-1,a2); //Imprime la Primera Mitad Ordenada parcialmente
    /// UNIMOS AMBAS MITADES
    vector<int> c1; c1.reserve(a1.size()+a2.size());
    c1.insert( c1.end(), a1.begin(), a1.end() );
    c1.insert( c1.end(), a2.begin(), a2.end() );



    ///SEGUNDA MITAD
    vector<int> b(arr.begin()+(n/2),arr.begin()+n);
    int bsize = b.size();
    // 2 CUARTOS, SEGUNDA MITAD
    vector<int> b1(b.begin(),b.begin()+(bsize/2));
    vector<int> b2(b.begin()+(bsize/2),b.begin()+bsize);
    int b1size = b1.size();
    int b2size = b2.size();
    ///ORDENAMIENTO DE LOS CUARTOS (3,4)
    bogoSort(b1);
    quickSort(b2,0,b2size-1);
    //pfor(0,b1.size()-1,b1); //Imprime el Tercer Cuarto
    //pfor(0,b2.size()-1,b2); //Imprime el Cuarto Cuarto
    vector<int> c2(b1size+b2size);
    merge(b1.begin(),b1.end(),b2.begin(),b2.end(),c2.begin());
    //pfor(0,c2.size()-1,c2); //Imprime la Mitad Derecha

    vector<int> FINAL(arr.size());
    merge(c1.begin(),c1.end(),c2.begin(),c2.end(),FINAL.begin());

    arr = FINAL;

}

int main()
{
    IOS
    cin.tie(0);
    ///freopen(filename_in,"r",stdin);
    ///freopen(filename_ou,"w",stdout);

    vector<int> v{1,10,12,3,8,11,4,9,13,16,6,2,7,15,14,5};
    int n = v.size();

    varietySort(v);

    pfor(0,n-1,v);
}
/// This code is less virgin than me
