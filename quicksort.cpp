#include <iostream>
#include <pthread.h>
using namespace std;
struct Array
{
    int size;
    int *arr;
    bool order;
};
int **a1;
int sum = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partitionasc(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++)
    {
        if (A[j] <= x)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return (i + 1);
}
int partitiondesc(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++)
    {
        if (A[j] > x)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return (i + 1);
}
void quickSortasc(int A[], int p, int r)
{
    if (p < r)
    {
        int q = partitionasc(A, p, r);
        quickSortasc(A, p, q - 1);
        quickSortasc(A, q + 1, r);
    }
}
void quickSortdesc(int A[], int p, int r)
{
    if (p < r)
    {
        int q = partitiondesc(A, p, r);
        quickSortdesc(A, p, q - 1);
        quickSortdesc(A, q + 1, r);
    }
}
void *quicksort(void *arg)
{
    Array *temp = (Array *)arg;
    if (temp->order == true)
        quickSortasc(temp->arr, 0, temp->size - 1);
    else
        quickSortdesc(temp->arr, 0, temp->size - 1);
    int i;
    // cout<<"temp-arr\n";
    for (i = 0; i < temp->size; i++)
    {
        // cout<<temp->arr[i]<<" ";
        sum += temp->arr[i];
    }
    cout << endl;

    pthread_exit((void *)temp->arr);
}

int main()
{
    int row = 0;
    int col = 0;
    cout << "Enter number of rows\n";
    cin >> row;
    cout << "Enter number of column\n";
    cin >> col;
    a1 = new int *[row];
    for (int i = 0; i < row; i++)
    {
        a1[i] = new int[col];
    }
    cout << "Enter elememnts for the matrix\n";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> a1[i][j];
        }
    }
    cout << "Matrix\n";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << a1[i][j] << " ";
        }
        cout << endl;
    }
    int stid = 0;
    cout << "Enter Student ID:\n";
    cin >> stid;
    int id = stid % 10;
    int *result = 0;
    if (id == 0 || id == 1 || id == 2)
    {
        int no_of_threads = row;
        pthread_t threads[no_of_threads];
        for (int j = 0; j < no_of_threads; j++)
        {
            Array *object = new Array();
            object->arr = new int[row];
            object->order = true;
            object->size = row;

            for (int i = 0; i < row; i++)
            {
                object->arr[i] = a1[i][j];
            }
            pthread_create(&threads[j], NULL, &quicksort, (void *)object);
            pthread_join(threads[j], (void **)&result);
            // cout<<"a1[k][j]"<<endl;
            for (int k = 0; k < row; k++)
            {
                a1[k][j] = result[k];
                // cout<<a1[k][j]<<" ";
            }
            if (object)
            {
                if (object->arr)
                    free(object->arr);
                free(object);
            }
        }
    }
    else if (id == 3 || id == 4 || id == 5)
    {
        int no_of_threads = col;
        pthread_t threads[no_of_threads];
        for (int j = 0; j < no_of_threads; j++)
        {
            Array *object = new Array();
            object->arr = new int[col];
            object->order = false;
            object->size = row;

            for (int i = 0; i < row; i++)
            {
                object->arr[i] = a1[i][j];
            }
            pthread_create(&threads[j], NULL, &quicksort, (void *)object);
            pthread_join(threads[j], (void **)&result);
            for (int k = 0; k < row; k++)
            {
                a1[k][j] = result[k];
            }
            if (object)
            {
                if (object->arr)
                    free(object->arr);
                free(object);
            }
        }
    }
    else if (id == 6 || id == 7)
    {
        int no_of_threads = row;
        pthread_t threads[no_of_threads];
        for (int j = 0; j < no_of_threads; j++)
        {
            Array *object = new Array();
            object->arr = new int[row];
            object->order = true;
            object->size = col;

            for (int i = 0; i < col; i++)
            {
                object->arr[i] = a1[j][i];
            }
            pthread_create(&threads[j], NULL, &quicksort, (void *)object);
            pthread_join(threads[j], (void **)&result);
            // cout<<"a1[j][k]"<<endl;
            for (int k = 0; k < col; k++)
            {
                //  cout<<result[k]<<" ";
                a1[j][k] = result[k];
            }
            if (object)
            {
                if (object->arr)
                    free(object->arr);
                free(object);
            }
        }
    }
    else if (id == 8 || id == 9)
    {
        int no_of_threads = row;
        pthread_t threads[no_of_threads];
        for (int j = 0; j < no_of_threads; j++)
        {
            Array *object = new Array();
            object->arr = new int[col];
            object->order = false;
            object->size = col;

            for (int i = 0; i < col; i++)
            {
                object->arr[i] = a1[j][i];
            }
            pthread_create(&threads[j], NULL, &quicksort, (void *)object);
            pthread_join(threads[j], (void **)&result);
            // cout<<"a1[j][k]"<<endl;
            for (int k = 0; k < col; k++)
            {
                // cout<<result[k]<<" ";
                a1[j][k] = result[k];
            }
            if (object)
            {
                if (object->arr)
                    free(object->arr);
                free(object);
            }
        }
    }
    cout << "Resultant Matrix\n";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << a1[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Matrix Sum: " << sum << endl;
    if (a1)
    {
        for (int i = 0; i < row; i++)
            if (a1[i])
                free(a1[i]);
        free(a1);
    }
    return 0;
}