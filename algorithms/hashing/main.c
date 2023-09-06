#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct hashNode
{
    char id[10];
    int order;
    bool is_cached;
} hashNode;

typedef struct cacheNode
{
    char id[10];
    char name[10];
    char surname[10];
    char dateOfBirth[5];
    char address[10];
    struct cacheNode *next;
} cacheNode;

int hornerHash(char *id);
int doubleHash(hashNode *, char *, int, bool *);
bool isPrime(int n);
int nextPrime(int n);
cacheNode *createCache(int size);
hashNode *createHash(int size);

int main()
{
    //Load faktör
    double loadFactor = 0.60;
    //cacheSize cache listesinin toplam boyutunu tutar
    //cacheLen cache listesinin eleman sayısını tutar
    int cacheSize = 2, cacheLen = 0, i;
    // printf("Enter the size of the cache: ");
    // scanf("%d", &cacheSize);
    //Hash Tablosunun boyutu hesaplanır.
    int hashTableSize = nextPrime((int)(cacheSize / loadFactor));
    hashNode *hashTable = createHash(hashTableSize);
    cacheNode *cache = createCache(cacheSize);
    cacheNode *p, *q;
    bool exist, temp;
    char id[10], name[10], surname[10], dateOfBirth[5], address[10], filename[20] = "test.txt";
    FILE *fp;
    // printf("Enter the name of the file: ");
    // scanf("%s", filename);
    fp = fopen(filename, "r");
    /**
     * @brief Okunan dosyasnın sonuna kadar çalışır.
     *        Okunan girdini id'sine göre bir hash indisi hesaplanır.
     *        Eğer bu id cache var ise ekrana yazdırılır ve konumu cachein başına getirilir.
     *        Ondan önce olan elemanlar ise bir adım ileri taşınarak hash tablosundaki order değerleri bir arttırılır.
     *        
     *        Eğer girilen değer cachede yok ve cachede yer var ise cache'e eklenir.
     *        Eğer cache dolu ise sondaki elemana gidilir ve bu elemanın bilgileri hash tablosundan silinir.Ardından eklenecek olan
     *        eleman için tekrardan hash değeri hesaplanır ve bu değerle hash tablosuna eklenir. 
     *        Her cache'e eleman eklemesi yapıldığında eğer eleman en başta değilse, diğer elemanların hash tablosundaki
     *        order değerleri bir arttırılır ve bir adım taşınır.
     *        (Aslında birer adım taşınma işleminden kasıt, cache'in başına gidecek olan liste elemanının yerinden koparılıp başa taşınması işlemidir.)
     * 
     */
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s", id, name, surname, dateOfBirth, address);
        int doubleHashIndex = doubleHash(hashTable, id, hashTableSize, &exist);
        //Eğer hash tablosunda bu id varsa doubleHashIndex hash tablosu sınırlarında bir sayı dönecektir. Eğer id yok ise random bir sayı dönecektir.
        //Görsel amaçla yazdırılmıştır.
        printf("Hash Table Index: %d\n", doubleHashIndex);
        //Eğer hash tablosunda bu id varsa, order bir değer dönecektir. Aksi halde random bir sayı dönecektir.
        printf("Cache Order: %d\n", hashTable[doubleHashIndex].order);
        if (exist)
        {
            i = 0;
            p = cache;
            // id var ise, id'ye varana kadar gelecek olan tüm nodeların order değerlerini bir arttırır.
            while (i < hashTable[doubleHashIndex].order)
            {
                q = p;
                hashTable[doubleHash(hashTable, q->id, hashTableSize, &temp)].order++;
                p = p->next;
                i++;
            }
            printf("Information about %s is in cache\n", id);
            printf("%s %s %s %s %s\n", p->id, p->name, p->surname, p->dateOfBirth, p->address);
            // Eğer id cacde ilk eleman değilse başa getirilir. 
            if (p != cache)
            {
                q->next = p->next;
                p->next = cache;
                cache = p;
                hashTable[doubleHashIndex].order = 0;
            }
        }
        else
        {
            if (cacheLen < cacheSize)
            {
                p = cache;
                // Eğer cachede yer var ise boşta olan node id char dizisinin ilk elemanın kontrolü ile bulunur. Ona varana kadar gelecek
                // olan tüm nodeların order değerlerini bir arttırır.
                while (p->id[0] != '\0' || p->id[0] != '\000')
                {
                    q = p;
                    hashTable[doubleHash(hashTable, p->id, hashTableSize, &temp)].order++;
                    p = p->next;
                }
                strcpy(p->id, id);
                strcpy(p->name, name);
                strcpy(p->surname, surname);
                strcpy(p->dateOfBirth, dateOfBirth);
                strcpy(p->address, address);

                if (p != cache)
                {
                    q->next = p->next;
                    p->next = cache;
                    cache = p;
                }
                // id 'ye ait bilgiler hashtablosuna işlenir.
                hashTable[doubleHashIndex].order = 0;
                hashTable[doubleHashIndex].is_cached = true;
                strcpy(hashTable[doubleHashIndex].id, id);

                cacheLen++;
            }
            else
            {
                p = cache;
                // Eğer cache dolu ise sondaki elemana gidilir ve gidene kadar gelecek olan elemanların order değerlerini bir arttırır.
                while (p->next != NULL)
                {
                    q = p;
                    hashTable[doubleHash(hashTable, p->id, hashTableSize, &temp)].order++;
                    p = p->next;
                }
                // Sondaki elemanın bilgileri silinir. Ardından eklenecek olan eleman için tekrardan hash değeri hesaplanır ve bu değerle hash tablosuna eklenir.
                hashTable[doubleHash(hashTable, p->id, hashTableSize, &temp)].is_cached = false;
                int newHashIndex = doubleHash(hashTable, id, hashTableSize, &temp);
                strcpy(p->id, id);
                strcpy(p->name, name);
                strcpy(p->surname, surname);
                strcpy(p->dateOfBirth, dateOfBirth);
                strcpy(p->address, address);

                if (p != cache)
                {
                    q->next = NULL;
                    p->next = cache;
                    cache = p;
                }

                hashTable[newHashIndex].order = 0;
                hashTable[newHashIndex].is_cached = true;
                strcpy(hashTable[newHashIndex].id, id);
            }
        }
    }
    fclose(fp);
    
    // hash tablosu ve cache hafızadan silinir.
    free(hashTable);
    while (cache)
    {
        cacheNode *temp = cache;
        cache = cache->next;
        free(temp);
    }
    return 0;
}

/**
 * @brief çift hash ile hash tablosunun indisini bulmaya yarayan fonksiyon. 
 *        Eğer girilen id'ye ait bir kayıt varsa, exist değişkeni true olur ve indis döner
 *        Eğer boş bir alan bulunursa, exist değişkeni false olur ve bu kayıtın indisi döndürür. 
 *        Eğer kayıt yoksa, exist false olur ve  -1 döndürür.
 * 
 * @param hashTable 
 * @param id 
 * @param hashTableSize 
 * @param exist 
 * @return int 
 */
int doubleHash(hashNode *hashTable, char *id, int hashTableSize, bool *exist)
{
    int i = 0;
    int hash = hornerHash(id);
    int index = ((hash % hashTableSize) + i * (1 + (hash % (hashTableSize - 1)))) % hashTableSize;
    while (strcmp(hashTable[index].id, id) != 0 && hashTable[index].is_cached == true && i < hashTableSize)
    {
        i++;
        index = ((hash % hashTableSize) + i * (1 + (hash % (hashTableSize - 1)))) % hashTableSize;
    }
    if (hashTable[index].is_cached == false)
    {
        *exist = false;
        return index;
    }
    else if (strcmp(hashTable[index].id, id) == 0)
    {
        *exist = true;
        return index;
    }
    else
    {
        *exist = false;
        return -1;
    }
}

/**
 * @brief hornerHash fonksiyonu
 * 
 * @param id 
 * @return int 
 */
int hornerHash(char *id)
{
    int hash = 0;
    int i = 0;
    while (id[i] != '\0')
    {
        hash = (hash * 37) + id[i];
        i++;
    }
    return hash;
}

/**
 * @brief Girilen integer sayısının asal olup olmadığının kontrolü yapılır.
 * 
 * @param n 
 * @return true 
 * @return false 
 */
bool isPrime(int n)
{
    int i = 2;
    while (i < n && n % i != 0)
    {
        i++;
    }
    if (i == n)
    {
        return true;
    }
    return false;
}

/**
 * @brief Girilen bir integer değerinden daha büyük en küçük asal sayıyı bulur.
 * 
 * @param n 
 * @return int 
 */
int nextPrime(int n)
{
    while (!isPrime(n))
    {
        n++;
    }
    return n;
}

/**
 * @brief Cache listesini oluşturur. Listede sırradaki elemanın boş olup olmadığının kontrolü için
 *        id char dizisinin ilk karakterine \0 ataması yapılır.
 * 
 * @param size 
 * @return cacheNode* 
 */
cacheNode *createCache(int size)
{
    cacheNode *cache = (cacheNode *)malloc(sizeof(cacheNode));
    cacheNode *head = cache;
    int i = 0;
    for (i = 0; i < size - 1; i++)
    {
        cache->id[0] = '\0';
        cache->next = (cacheNode *)malloc(sizeof(cacheNode));
        cache = cache->next;
    }
    cache->next = NULL;
    cache->id[0] = '\0';
    printf("##Cache created\n");
    return head;
}

/**
 * @brief Hash tablosunu oluşturur. Girilen boyutta bir dizi oluşturur.
 * 
 * @param size 
 * @return hashNode* 
 */
hashNode *createHash(int size)
{
    hashNode *hashTable = (hashNode *)malloc(sizeof(hashNode) * size);
    int i = 0;
    for (i = 0; i < size; i++)
    {
        hashTable[i].is_cached = false;
    }
    printf("##Hash table created\n");
    return hashTable;
}
