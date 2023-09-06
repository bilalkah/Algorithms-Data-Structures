#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <stdbool.h>

// x, y ikililerinin tutulduğu struct veri tipi
typedef struct Point
{
    double x, y;
} Point;

// Diziyi left<right olduğu sürece ikiye böler ardından merge fonskiyonunu çağırır.
void mergeSort(Point *arr, int left, int right, bool is_x);

// 1 elemanlı diziden başlayarak sıralı dizileri birleştirir.
void merge(Point *arr, int left, int middle, int right, bool is_x);

// Brute Force ile points dizinin içerisindeki en yakın ikilileri bulan fonksiyon
double bruteForceClosest(Point *points, int n, Point *back1, Point *back2);

// x koordinat noktaları baz alınarak sıralanmış points dizisinin içerisindeki
// en yakın ikilileri bulan fonksiyon
double recursiveClosest_x(Point *points, int n, Point *back1, Point *back2);

// y koordinat noktaları baz alınarak sıralanmış points dizisinin içerisindeki
// en yakın ikilileri bulan fonksiyon
double recursiveClosest_y(Point *points, int n, Point *back1, Point *back2);

int main(void)
{
    Point *points = NULL; // sample.txt dosyasından okunan noktaların yerleştirileceği dizi
    int size = 0;         // points dizisinin uzunluğu

    FILE *ptr = fopen("sample.txt", "r"); // Noktaların içerisinde yer aldığı sample.txt dosyası okuma modunda açılır
    if (ptr == NULL)                      // Eğer dosya açılamaz ise çıkış yap
    {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("Dosya okumasi basarili\n");
    while (!feof(ptr)) // Dosyanın sonuna gelene kadar her satırı oku ve points dizisine yerleştir
    {
        size++;
        int temp_x, temp_y;
        fscanf(ptr, "%d %d", &temp_x, &temp_y);
        if (points == NULL) // points dizisinin dinamik olarak büyütüyoruz. Bu sayede gerektiği kadar yer kullanılıyor.
        {
            points = (Point *)malloc(sizeof(Point));
            if (points == NULL)
            {
                fprintf(stderr, "Error allocating memory!\n");
                exit(EXIT_FAILURE);
            }
            points[0].x = (double)temp_x; // x ve y ikilileri double tipinde listeye ekleniyor çünkü mesafe bulurken ondalıklı sayılar elde edilebiliyor.
            points[0].y = (double)temp_y;
        }
        else
        {
            points = realloc(points, sizeof(Point) * size);
            if (points == NULL)
            {
                fprintf(stderr, "Error allocating memory!\n");
                exit(EXIT_FAILURE);
            }
            points[size - 1].x = (double)temp_x; // x ve y ikilileri double tipinde listeye ekleniyor çünkü mesafe bulurken ondalıklı sayılar elde edilebiliyor.
            points[size - 1].y = (double)temp_y;
            //sortAndFill_x(points, size, (double)temp_x, (double)temp_y); // girilen noktaları uygun yerine yerleştiren fonksiyon çağrılıyor
        }
    }
    fclose(ptr); // Dosya okuma işlemi bitince FILE pointer kapatılır.
    printf("Dosya okuma islemi tamamlandi.\n");
    mergeSort(points, 0, size - 1, true); // points dizisini x koordinatları baz alarak sıralayan fonksiyon çağrılıyor
    Point p1, p2;                                                                                   // p1 ve p2 en yakın olan iki noktanın değerlerini alacak değişkenlerdir.
    double min = recursiveClosest_x(points, size, &p1, &p2);                                        // en kısa mesafeyi ve ikiliyi bulan fonksiyon çağrılır
    printf("P1: %d %d\nP2: %d %d\nDistance:%f\n", (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, min); // Ekrana sonuç yazılır

    free(points); // dinamik olarak ayrılan bellek boşaltılır.
    return 0;
}

/**
 * @brief points dizisinin içindeki noktaların en küçük uzaklığını brute force ile hesaplar ve minimum olan uzaklık bilgisi ile minimum uzaklığa sahip noktaların değerlerini döndürür.
 *        noktaların bilgisi p1 ve p2 değerlerine yazılmaktadır.
 * @param points 
 * @param n 
 * @param p1 
 * @param p2 
 * @return double 
 */
double bruteForceClosest(Point *points, int n, Point *back1, Point *back2)
{
    double min = DBL_MAX; // Minimum mesafeyi tutacak değer.
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double dist = sqrt(pow(abs(points[i].x - points[j].x), 2) + pow(abs(points[i].y - points[j].y), 2)); // Öklid mesafe hesabı
            if (dist < min)                                                                                      // Eğer mesafe min değerinden küçükse yeni min, dist olur. Ayrınca p1 ve p2 noktalarının değerlerini günceller.
            {
                min = dist;
                back1->x = points[i].x;
                back1->y = points[i].y;
                back2->x = points[j].x;
                back2->y = points[j].y;
                printf("back1:%d,%d\nback2:%d,%d\nDistance:%f\n", (int)back1->x, (int)back1->y, (int)back2->x, (int)back2->y, min);
            }
        }
    }
    return min;
}

/**
 * @brief x koordinat noktasına göre recursive olarak points dizisinin içerisindeki en yakın ikilileri arayan fonksiyon
 *        Eğer points dizisinin uzunluğu, yani n, <=3 olursa brute force ile mesafe hesabı yapar. n<=3 olana kadar diziyi
 *        2'ye bölerek arama yapar ardından gelen iki min değerini kıyaslayarak en yakın ikili bilgisini günceller.
 *        her iki bölgede ayrı ayrı en yakın ikililer hesaplandıktan sonra, elde edilen minimum mesafe ç
 * 
 * @param points x,y ikililerinin tutulduğu dizi
 * @param n  x,y ikililerinin tutulduğu dizinin uzunluğu
 * @param back1 back1 ve back2 en yakın mesafeye sahip iki nokta
 * @param back2 
 * @return double 
 */
double recursiveClosest_x(Point *points, int n, Point *back1, Point *back2)
{
    if (n <= 3)
    {
        return bruteForceClosest(points, n, back1, back2);
    }
    else
    {
        int mid = n / 2;              // dizinin orta noktası
        Point midPoint = points[mid]; // dizinin orta noktasındaki değer
        Point l1, l2;                 // ikiye bölünen dizinin sol tarafındaki en kısa noktaların değerlerini tutacak değişkenler
        Point r1, r2;                 // ikiye bölünen dizinin sağ tarafındaki en kısa noktaların değerlerini tutacak değişkenler

        // p1 ve p2 ikiye bölünen dizilerin başlangıç noktasını temsil etmektedir.
        // dinamik olarak bellek ayrılmaktadır.
        Point *p1 = (Point *)malloc(mid * sizeof(Point));
        if (p1 == NULL)
        {
            fprintf(stderr, "Error allocating memory!\n");
            exit(EXIT_FAILURE);
        }
        Point *p2 = (Point *)malloc((n - mid) * sizeof(Point));
        if (p2 == NULL)
        {
            fprintf(stderr, "Error allocating memory!\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < mid; i++)
        {
            p1[i] = points[i];
        }
        for (int i = mid; i < n; i++)
        {
            p2[i - mid] = points[i];
        }

        // ardından l1 ve l2 noktalarının adres değerleri ile fonksiyon tekrar çağrılır.
        // d1 dizinin sol tarafından gelecek olan minimum değeri temsil etmektedir.
        double d1 = recursiveClosest_x(p1, mid, &l1, &l2);
        // ardından r1 ve r2 noktalarının adres değerleri ile fonksiyon tekrar çağrılır.
        // d2 dizinin sağ tarafından gelecek olan minimum değeri temsil etmektedir.
        double d2 = recursiveClosest_x(p2, n - mid, &r1, &r2);

        free(p1); // p1 ve p2 için ayrılan alan boşaltılır.
        free(p2);

        Point ans1, ans2; // sağ ve sol taraftan gelen noktaların en küçük mesafeye sahip olanlarının
                          //cevaplarının yerleştirileceği değişkenler

        double minimum_x; // d1 ve d2 değerlerinden en küçük olanının değerini tutan değişken
        if (d1 < d2)
        {
            ans1 = l1;
            ans2 = l2;
            minimum_x = d1;
        }
        else
        {
            ans1 = r1;
            ans2 = r2;
            minimum_x = d2;
        }

        // Burada sağ ve sol bölgelerin medyan değerinden +minimum_x ve -minimum_x aralığındaki noktalar kontrol edilir.
        // Burada y koordinat noktasına göre bir kıyaslama yapılacağı için eğer var ise noktalar y bilgisine göre
        // sıralanır. Ardından y noktasına göre yakınlık arayan recursiveClosest_y fonksiyonu çağrılır
        Point *p3 = NULL;
        int p3_size = 0;

        for (int i = 0; i < n; i++)
        {
            if (abs(points[i].y - midPoint.y) < minimum_x)
            {
                if (p3 == NULL)
                {
                    p3 = (Point *)malloc(++p3_size * sizeof(Point));
                    if (p3 == NULL)
                    {
                        fprintf(stderr, "Error allocating memory!\n");
                        exit(EXIT_FAILURE);
                    }
                    p3[0] = points[i];
                }
                else
                {
                    p3 = (Point *)realloc(p3, ++p3_size * sizeof(Point));
                    if (p3 == NULL)
                    {
                        fprintf(stderr, "Error allocating memory!\n");
                        exit(EXIT_FAILURE);
                    }
                    p3[p3_size - 1] = points[i];
                    //sortAndFill_y(p3, p3_size, points[i].x, points[i].y);
                }
            }
        }
        double minimum_y; // rescursiveClosest_y fonksiyonundan gelecek olan minimum mesafe bilgisi
        Point y1, y2;     // rescursiveClosest_y fonksiyonundan gelecek olan en yakın nokta ikilileri bilgisi
        // Eğer p3 NULL gelirse aranılan bölgede nokta mevcut olmadığı anlamına gelir ve
        // ans1 ve ans2 değerleri back1 ve back2 değerlerine yazılır ve fonksiyon en kısa mesafeyi döner.
        if (p3 == NULL)
        {
            back1->x = ans1.x;
            back1->y = ans1.y;
            back2->x = ans2.x;
            back2->y = ans2.y;
            return minimum_x;
        }
        else if (p3_size <= 3) // eğer nokta sayısı <=3 ise bruteforceClosest çağrılır
        {
            mergeSort(p3, 0, p3_size - 1, false);
            minimum_y = bruteForceClosest(p3, p3_size, &y1, &y2);
        }
        else
        { // diğer türlü recursive olarak parçalara bölünmek üzere recursiveClosest_y fonksiyonu çağrılır.
            mergeSort(p3, 0, p3_size - 1, false);
            minimum_y = recursiveClosest_y(p3, p3_size, &y1, &y2);
        }

        free(p3); // p3 için ayrılan alan boşaltılır.
        // Eğer minimum_x bilgisinden daha kısa bir mesafe hesaplanırsa back1 ve back2
        // recursiveClosest_y'den dönen noktalar ile güncellenir ve minimum_y değeri dönülür.
        if (minimum_y < minimum_x)
        {
            back1->x = y1.x;
            back1->y = y1.y;
            back2->x = y2.x;
            back2->y = y2.y;
            return minimum_y;
        }
        // Eğer minimum_x en kısa mesafe olursa ans1 ve ans2 değerleri back1 ve back2 ye yazılır. Ardından minimum_x döner.
        back1->x = ans1.x;
        back1->y = ans1.y;
        back2->x = ans2.x;
        back2->y = ans2.y;
        return minimum_x;
    }
}

/**
 * @brief recursiveClosest_x ile aynı işi yapmaktadır. Tek farkı medyanda ,elde edilen minimum mesafe değerinin
 *        + ve - aralığını kontrol etmez.
 * 
 * @param points 
 * @param n 
 * @param back1 
 * @param back2 
 * @return double 
 */
double recursiveClosest_y(Point *points, int n, Point *back1, Point *back2)
{
    if (n <= 3)
    {
        return bruteForceClosest(points, n, back1, back2);
    }
    else
    {
        int mid = n / 2;
        Point midPoint = points[mid];
        Point l1, l2;
        Point r1, r2;

        Point *p1 = (Point *)malloc(mid * sizeof(Point));
        if (p1 == NULL)
        {
            fprintf(stderr, "Error allocating memory!\n");
            exit(EXIT_FAILURE);
        }
        Point *p2 = (Point *)malloc((n - mid) * sizeof(Point));
        if (p2 == NULL)
        {
            fprintf(stderr, "Error allocating memory!\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < mid; i++)
        {
            p1[i] = points[i];
        }
        for (int i = mid; i < n; i++)
        {
            p2[i - mid] = points[i];
        }

        double d1 = recursiveClosest_y(p1, mid, &l1, &l2);
        double d2 = recursiveClosest_y(p2, n - mid, &r1, &r2);

        free(p1);
        free(p2);

        double minimum_x;
        if (d1 < d2)
        {
            back1->x = l1.x;
            back1->y = l1.y;
            back2->x = l2.x;
            back2->y = l2.y;
            return d1;
        }
        else
        {
            back1->x = r1.x;
            back1->y = r1.y;
            back2->x = r2.x;
            back2->y = r2.y;
            return d2;
        }
    }
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
void mergeSort(Point *arr, int left, int right, bool is_x)
{
    // Sağ ve sol yer değiştirmediği sürece diziyi ikiye böl ardından sıralanmış dizileri birleştir
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle, is_x);
        mergeSort(arr, middle + 1, right, is_x);

        merge(arr, left, middle, right, is_x);
    }
}

/**
 * @brief Sıralı iki diziyi birleştirir
 *        
 * @param arr 
 * @param left 
 * @param middle 
 * @param right 
 */
void merge(Point *arr, int left, int middle, int right, bool is_x)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int i, j, k;
    //Diziyi ortasından ikiye böl ve yeni dizi oluştur
    Point *L = (Point *)malloc(n1 * sizeof(Point));
    Point *M = (Point *)malloc(n2 * sizeof(Point));

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
        if (is_x)
        {
            if (L[i].x <= M[j].x)
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
        else
        {
            if (L[i].y <= M[j].y)
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