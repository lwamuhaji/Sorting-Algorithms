#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct heap
{
    int S[100000];
    int heapsize;
};

struct queue
{
    int *S;
    int size;
    int front;
    int rear;
    int count;
};

void print_data(int data[], int size);
int *generate_random(int size);
//정렬 알고리즘
void Exchange_Sort(int data[], int size);
void Merge_Sort(int *S, int data[], int start, int end, int size);
void merge(int S[], int data[], int start, int mid, int end);
void Quick_Sort(int data[], int left, int right, int size);
void Radix_Sort(int data[], int size);
void Heap_Sort(int n, heap &H);
// heap
int root(heap &H);
void removekeys(int n, heap &H, int S[]);
void makeheap(int n, heap &H);
void siftdown(heap &H, int i);
// queue
void InitQueue(queue *q, int size);
int IsEmpty(queue *q);
void Enqueue(queue *q, int data);
int Dequeue(queue *q);

int main()
{
    clock_t start, end;
    int size = 20000;
    int *data;
    int *D[5];

    // Exchange
    for (int i = 0; i < 5; i++)
    {
        D[i] = generate_random(size);
    }
    start = clock();
    for (int i = 0; i < 5; i++)
    {
        Exchange_Sort(D[i], size);
    }
    end = clock();
    printf("Exchange sort execution time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Merge
    for (int i = 0; i < 5; i++)
    {
        D[i] = generate_random(size);
    }
    int *S = (int *)malloc(sizeof(int) * size);
    start = clock();
    for (int i = 0; i < 5; i++)
    {
        Merge_Sort(S, D[i], 0, size - 1, size);
    }
    end = clock();
    printf("Merge sort execution time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Quick
    for (int i = 0; i < 5; i++)
    {
        D[i] = generate_random(size);
    }
    start = clock();
    for (int i = 0; i < 5; i++)
    {
        Quick_Sort(D[i], 0, size - 1, size);
    }
    end = clock();
    printf("Quick sort execution time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Heap
    heap H;
    start = clock();
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < size; i++)
        {
            H.S[i] = rand();
        }
        Heap_Sort(size, H);
    }
    end = clock();
    printf("Heap sort execution time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Radix
    for (int i = 0; i < 5; i++)
    {
        D[i] = generate_random(size);
    }
    start = clock();
    for (int i = 0; i < 5; i++)
    {
        Radix_Sort(D[i], size);
    }
    end = clock();
    printf("Radix sort execution time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void print_data(int data[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int *generate_random(int size)
{
    srand((int)time(NULL));
    int *data = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        data[i] = rand();
    }
    return data;
}

void Exchange_Sort(int data[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (data[i] > data[j])
            {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

void Merge_Sort(int *S, int data[], int start, int end, int size)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        Merge_Sort(S, data, start, mid, size);
        Merge_Sort(S, data, mid + 1, end, size);
        merge(S, data, start, mid, end);
    }
}

void merge(int S[], int data[], int start, int mid, int end)
{
    int i = start;
    int j = mid + 1;
    int k = start;

    while (i <= mid && j <= end)
    {
        if (data[i] <= data[j])
        {
            S[k] = data[i];
            i++;
        }
        else
        {
            S[k] = data[j];
            j++;
        }
        k++;
    }
    if (i > mid)
    {
        for (int t = j; t <= end; t++)
        {
            S[k] = data[t];
            k++;
        }
    }
    else
    {
        for (int t = i; t <= mid; t++)
        {
            S[k] = data[t];
            k++;
        }
    }

    for (int t = start; t <= end; t++)
    {
        data[t] = S[t];
    }
}

int Partition(int data[], int left, int right)
{
    int pivot = data[right];
    int n = left - 1;
    int temp;
    for (int k = left; k < right; k++)
    {
        if (data[k] < pivot)
        {
            n++;
            temp = data[n];
            data[n] = data[k];
            data[k] = temp;
        }
    }
    temp = data[n];
    data[n] = data[right];
    data[right] = temp;
    return (n + 1);
}

void Quick_Sort(int data[], int left, int right, int size)
{
    if (left < right)
    {
        int pivot_index = Partition(data, left, right);
        Quick_Sort(data, left, pivot_index - 1, size);
        Quick_Sort(data, pivot_index + 1, right, size);
    }
}

void Radix_Sort(int data[], int size)
{
    queue *q[10];
    for (int i = 0; i < 10; i++)
    {
        q[i] = (queue *)malloc(sizeof(queue));
        InitQueue(q[i], size);
    }

    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (max < data[i])
            max = data[i];
    }

    int r = 1;
    while (1)
    {
        if (r >= max)
            break;
        r = r * 10;
    }

    for (int i = 1; i < r; i = i * 10)
    {
        for (int j = 0; j < size; j++)
        {
            int k;
            if (data[j] < i)
                k = 0;
            else
                k = (data[j] / i) % 10;
            Enqueue(q[k], data[j]);
        }

        int k = 0;
        for (int j = 0; j < 10; j++)
        {
            while (!IsEmpty(q[j]))
            {
                data[k] = Dequeue(q[j]);
                k++;
            }
        }
    }
}

int root(heap &H)
{
    int keyout;
    keyout = H.S[1];
    H.S[1] = H.S[H.heapsize];
    H.heapsize = H.heapsize - 1;
    siftdown(H, 1);
    return keyout;
}

void removekeys(int n, heap &H, int S[])
{
    for (int i = n; i >= 1; i--)
    {
        S[i] = root(H);
    }
}

void makeheap(int n, heap &H)
{
    H.heapsize = n;
    for (int i = n / 2; i >= 1; i--)
    {
        siftdown(H, i);
    }
}

void Heap_Sort(int n, heap &H)
{
    makeheap(n, H);
    removekeys(n, H, H.S);
}

void siftdown(heap &H, int i)
{
    int parent, largerchild;
    int siftkey;
    int spotfound;

    siftkey = H.S[i];
    parent = i;
    spotfound = 0;
    while (2 * parent <= H.heapsize && !spotfound)
    {
        if (2 * parent < H.heapsize && H.S[2 * parent] < H.S[2 * parent + 1])
        {
            largerchild = 2 * parent + 1;
        }
        else
        {
            largerchild = 2 * parent;
        }
        if (siftkey < H.S[largerchild])
        {
            H.S[parent] = H.S[largerchild];
            parent = largerchild;
        }
        else
        {
            spotfound = 1;
        }
        H.S[parent] = siftkey;
    }
}

void InitQueue(queue *q, int size)
{
    q->S = (int *)malloc(sizeof(int) * size);
    q->size = size;
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

int IsEmpty(queue *q)
{
    return q->count == 0;
}

void Enqueue(queue *q, int data)
{
    q->S[q->rear] = data;
    q->rear = ((q->rear + 1) % q->size);
    q->count++;
}

int Dequeue(queue *q)
{
    int re = 0;
    if (IsEmpty(q))
    {
        return re;
    }
    re = q->S[q->front];
    q->front = ((q->front + 1) % q->size);
    q->count--;
    return re;
}