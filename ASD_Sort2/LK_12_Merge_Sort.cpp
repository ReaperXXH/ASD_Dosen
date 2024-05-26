#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

int *generate_random_int(int n)
{
    int *data = new int[n];

    for (int i = 0; i < n; i++)
    {
        data[i] = rand();
    }

    return data;
}
bool is_sorted(int *data, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (data[i - 1] > data[i])
        {
            return false;
        }
    }
    return true;
}

void merge(int *data, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = data[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        data[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void merge_sort(int *data, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort(data, left, mid);
        merge_sort(data, mid + 1, right);

        merge(data, left, mid, right);
    }
}

void sort(int *data, int n)
{
    merge_sort(data, 0, n - 1);     
}

int main()
{
    int num_of_experiments = 100;
    int *data;
    int n;
    // DEBUG
    // The program will stop if the sorting is incorrect
    n = 100;
    data = generate_random_int(n);
    sort(data, n);
    if (!is_sorted(data, n))
    {
        throw runtime_error("Sorting function ERROR.");
    }
    // EXPERIMENTS
    cout << "data, time (ms)\n";
    cout << " \n";
    for (int i = 1; i <= num_of_experiments; i++)
    {
        n = i * 1000;
        data = generate_random_int(n);
        auto start = chrono::high_resolution_clock::now();
        sort(data, n);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

        cout << n << ", " << duration.count() << "\n";

        delete data;
    }
    return 0;
}