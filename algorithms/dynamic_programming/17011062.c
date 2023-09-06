#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

// Reklam veri yapisi
typedef struct commercial
{
    int start;
    int duration;
    int end;
    int value;
    int order;
} com;

void mergeSort(com *arr, int left, int right);
void merge(com *arr, int left, int middle, int right);
int *maxProfit(com *arr, int n);

int main()
{

    char filename[20];
    FILE *fp;
    com *com_arr = NULL;
    int size = 0;
    int j;
    printf("Enter the name of the file: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    while (fp == NULL)
    {
        fprintf(stderr, "File not found.\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(fp))
    {
        if (com_arr == NULL)
        {
            com_arr = (com *)malloc(sizeof(com));
            size++;
        }
        else
        {
            com_arr = (com *)realloc(com_arr, sizeof(com) * (++size));
        }
        fscanf(fp, "%d %d %d", &com_arr[size - 1].start, &com_arr[size - 1].duration, &com_arr[size - 1].value);
        com_arr[size - 1].end = com_arr[size - 1].start + com_arr[size - 1].duration;
        com_arr[size - 1].order = size - 1;
    }
    fclose(fp);

    mergeSort(com_arr, 0, size - 1);
    
    printf("start\tduration\tend\tvalue\n");
    for (j = 0; j < size; j++)
    {
        printf("%d\t%d\t\t%d\t%d\n", com_arr[j].start, com_arr[j].duration, com_arr[j].end, com_arr[j].value);
    }
    printf("\n\n");
    int *profit = maxProfit(com_arr, size);

    printf("Maximum profit: %d\n", profit[size - 1]);
    printf("Selected commercials: ");

    //Burada toplam kazançttan çıkarma yapılarak seçilen noktalar tespit edilmektedir.
    //Kazanç aynı olduğu sürece j'yi 1 azaltırız ve ardından j. indisteki reklam değerini kontrol ederiz.
    int total_profit = profit[size - 1];
    j = size - 1;

    while (j >= 0 && total_profit > 0)
    {
        while (j >= 0 && total_profit == profit[j - 1])
        {
            j--;
        }

        int commercial_index = com_arr[j].order;
        printf("%d ", commercial_index);
        total_profit -= com_arr[j].value;
        j--;
    }

    free(profit);
    free(com_arr);
    return 0;
}

/**
 * @brief Reklam verilerinden maksimum kazancı bulacak şekilde reklamları arar.
 *
 * @param arr
 * @param n
 */
int *maxProfit(com *arr, int n)
{
    // Kazanç değerlerinin tutan dizi
    int *profit = (int *)calloc(n, sizeof(int));
    // indisler
    int i, j, k;

    // ilk değerleri ata
    profit[0] = arr[0].value;

    for (k = 0; k < n; k++)
    {
        printf("%d ", profit[k]);
    }
    printf("\n");
    // i = 1 den başlayarak diziyi dön
    for (i = 1; i < n; i++)
    {
        // profit dizisinde bir önceki indisten başlayarak başlangıcı bitişinden küçük olduğu sürece
        // ve j 0'dan büyük olduğu sürece j'yi bir azalt
        j = i - 1;
        while (j >= 0 && arr[i].start <= arr[j].end)
        {
            j--;
        }
        // Eğer j'nin değeri 0'dan büyükse ve çakışmayan bir önceki kazanç ile şimdiki reklam
        // hali hazırda bulunan kazançtan büyükse bu reklamın kazançını ata
        if (j >= 0 && arr[i].value + profit[j] > profit[i - 1])
        {
            profit[i] = arr[i].value + profit[j];
        }
        // Eğer j'nin değeri 0'dan küçükse ve gelen reklam ile kazancı kıyasla ve eğer
        // gelen reklam toplam kazançtan büyükse bu reklamın kazançını ata
        else if (arr[i].value > profit[i - 1])
        {
            profit[i] = arr[i].value;
        }
        // Eğer büyük değilse önceki kazancı ata
        else
        {
            profit[i] = profit[i - 1];
        }

        for (k = 0; k < n; k++)
        {
            printf("%d ", profit[k]);
        }
        printf("\n");
    }
    printf("\n\n");
    return profit;
}

/**
 * @brief Sıralı iki diziyi birleştirir
 *
 * @param arr
 * @param left
 * @param middle
 * @param right
 */
void merge(com *arr, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int i, j, k;
    // Diziyi ortasından ikiye böl ve yeni dizi oluştur
    com *L = (com *)malloc(n1 * sizeof(com));
    com *M = (com *)malloc(n2 * sizeof(com));

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }

    for (j = 0; j < n2; j++)
    {
        M[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    // Bu kısımda diziler karşılaştırılarak birleştirilir.
    while (i < n1 && j < n2)
    {

        if (L[i].end <= M[j].end)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }

    free(L);
    free(M);
}

/**
 * @brief diziyi merge sort algoritması ile sıralar
 *        çalışma mantığı dizinin boyutu 1 kalana kadar böl ardından sıralayarak birleştir.
 *        karmaşıklık O(nlogn)
 *
 * @param arr
 * @param left
 * @param right
 */
void mergeSort(com *arr, int left, int right)
{
    // Sağ ve sol yer değiştirmediği sürece diziyi ikiye böl ardından sıralanmış dizileri birleştir
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}