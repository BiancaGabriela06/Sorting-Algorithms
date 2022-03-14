#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <time.h>
#define N 100000001


using namespace std;

vector <int> v(N), correct_v(N);
vector <int> vRadix(N), vShell(N), vHeap(N), vSTL(N), vMerge(N), vCounting(N);

int vmax, n, baza, T, mmin, mmax;
time_t timer1;

void ShellSort(vector <int> &v, int n)
{
    int interval, temp, i, j;
    for(interval = n/2; interval>0; interval/=2)
    {
        for(i = interval; i < n; i++)
        {
            temp = v[i];
            for(j = i; j>=interval && v[j-interval] > temp; j-=interval)
                v[j] = v[j-interval];
            v[j] = temp;
        }
    }
}

void CountSort(vector < int > &V, int b, int exponent)
{
    int n = V.size();
    vector < int > count(b, 0), new_sort(n, 0);

    for(int i = 0; i < n; ++i)
        ++count[(V[i] / exponent) % b];

    for(int i = 1; i < b; ++i)
        count[i] += count[i - 1];

    for(int i = n - 1; i >= 0; --i)
    {
        new_sort[count[(V[i] / exponent) % b] - 1] = V[i];
        --count[(V[i] / exponent) % b];
    }

    for(int i = 0; i < n; ++i)
        v[i] = new_sort[i];
    new_sort.clear();
}


void RadixSort(vector < int > &V, int n, int b)
{
    int maxim = -1, i;

    // calculam cel mai mare numar ca sa aflam numarul maxim de cifre
    for(int i = 0; i < n; ++i)
        maxim = max(V[i], maxim);

    //numarul maxim de cifra, in functie de baza
    int max_digits = int(log(maxim) / log(baza)) + 1;

    int pow = 1;

    for(i = 1; i <= max_digits; ++i)
    {
            CountSort(V, b, pow);
            pow *= b;

    }
}


void Interclasare( vector <int> &v, int st, int mij, int dr)
{
    vector <int> a;
    int i=st, j=mij+1;

    while( i <= mij && j <=dr)
        if(v[i] < v[j])
        {
            a.push_back(v[i]);
            i ++;
        }
        else
        {
            a.push_back(v[j]);
            j++;
        }

    while(i<=mij)
    {
        a.push_back(v[i]);
        i ++;
    }

    while(j<=dr)
    {
        a.push_back(v[j]);
        j++;
    }

    for(int index=st; index <=dr; index++)
        v[index]=a[index-st];

    a.clear();

}

void MergeSort(vector < int > &V, int st, int dr)
{
    if(st >= dr) return;
    int mij = (st + dr) / 2;
    MergeSort(V, st, mij);
    MergeSort(V, mij + 1, dr);
    Interclasare(V, st, mij, dr);
}

void max_heapify(vector<int>& v, int i, int n)
{
    int largest, l = (2*i) + 1, r = l + 1;

    if(l < n && v[l] > v[i])
        largest = l;
    else
        largest = i;

    if(r < n && v[r] > v[largest])
        largest = r;

    if(largest != i)
    {
        swap(v[i], v[largest]);
        max_heapify(v, largest, n);
    }
}

void build_max_heap(vector<int>& v, int n)
{
    for(int i = n / 2; i >= 0; i--)
        max_heapify(v, i, n);
}

void HeapSort(vector<int>& v, int n)
{
    build_max_heap(v, n);
    for(int i = n - 1; i > 0; i--)
    {
        swap(v[0], v[i]);
        n--;
        max_heapify(v, 0, n);
    }
}

void CountingSort(vector <int> &V, int min, int max)
{
    vector <int> count(max - min + 1);

    int size = V.size();

    for(int i = 0; i < size; ++i)
        ++count[V[i] - min];

    V.clear();

    for(int i = 0; i <= max - min; ++i)
        for(int j = 1; j <= count[i]; ++i)
            V.push_back(i + min);

}

vector <int> Numbers_generator(int size, int vmax)
{
    int x;
    vector <int> V;
    mmin = vmax + 1;
    mmax = -1;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for(int i = 0; i < size; ++i)
    {
        x = uniform_int_distribution<int>(0, vmax)(rng);
        mmin = min(x, mmin);
        mmax = max(x, mmax);
        v.push_back(x);
    }

    return  V;
}

vector <int> correct_sort(vector <int> V)
{
    sort(V.begin(), V.end());
    return V;
}

bool Test(vector <int> V1, vector <int> V2)
{
    if(V1.size() != V2.size()) return 0;
    for(int i = 0; i < V1.size(); ++i)
        if(V1[i] != V2[i])
            return 0;

    return 1;
}

void Print(vector <int> v, int n)
{
    int i;
    for(i=0; i<n; i++)
        cout<<v[i] <<" ";

}

void Sortare(int n, int vmax, int baza)
{
        v = Numbers_generator(n, vmax);
        vRadix = v;
        vShell = v;
        vCounting = v;
        vHeap = v;
        vSTL = v;
        vMerge = v;
        correct_v = correct_sort(v);

        ///RADIXSORT
        time(&timer1);
        auto start = chrono::high_resolution_clock::now();
        RadixSort(vRadix,n,baza);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout <<"RadixSort: ";
        if( Test(vRadix, correct_v) == 1 ) cout << "Sortare corecta" << " " << (double)duration.count()/1000  << " milisecunde";
        else cout << "Sortare incorecta";
        cout <<"\n";



        if( baza == 10)
        {
            ///SHELLSORT

            time(&timer1);
            start = chrono::high_resolution_clock::now();
            ShellSort(vShell,n);
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout <<"ShellSort: ";
            if( Test(vShell, correct_v) == 1 ) cout << "Sortare corecta" << " " << (double)duration.count()/1000 << " milisecunde";
            else cout << "Sortare incorecta";
            cout<<"\n";

            ///MERGESORT
            time(&timer1);
            start = chrono::high_resolution_clock::now();
            MergeSort(vMerge,0,n-1);
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout <<"MergeSort: ";
            if( Test(vMerge, correct_v) == 1 ) cout << "Sortare corecta" << " " << (double)duration.count()/1000 << " milisecunde";
            else cout << "Sortare incorecta";
            cout<<"\n";

            ///HEAPSORT
            time(&timer1);
            start = chrono::high_resolution_clock::now();
            HeapSort(vHeap,n);
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout <<"HeapSort: ";
            if( Test(vHeap, correct_v) == 1 ) cout << "Sortare corecta" << " " << (double)duration.count()/1000 << " milisecunde";
            else cout << "Sortare incorecta";
            cout<<"\n";

            ///COUNTINGSORT
            time(&timer1);
            start = chrono::high_resolution_clock::now();
            CountingSort(vCounting, mmin, mmax);
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout<<"CountingSort: ";
            if( Test(vCounting, correct_v) == 1 ) cout << "Sortare corecta" << " " << (double)duration.count()/1000  << " milisecunde";
            else cout << "Sortare incorecta";
            cout << "\n";

            /// STL NATIVE SORT
            time(&timer1);
            start = chrono::high_resolution_clock::now();
            sort(vSTL.begin(),vSTL.end());
            stop = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            cout << "STL Native Sort: " <<" "<< (double)duration.count()/1000 << " milisecunde";
            cout <<"\n";

        }


}

int main()
{

    int i;

    cout << "Numarul de teste este: ";
    cin >> T;
    for(i=1; i<=T; i++) {
        cout << "Scrieti marimea vectorului: ";
        cin >> n;
        if (n >= 536870911) {
            cout << "Prea multe valori";
            return 0;
        }

        cout <<"Scrieti valoarea maxima a numerelor din vector: ";
        cin >> vmax;
        cout << "Scrieti baza in care vor fi numere (RadixSort): ";
        cin >> baza;

        Sortare(n,vmax,baza);
    }


    return 0;
}
