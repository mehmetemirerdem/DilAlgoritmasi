#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};

const char languages[2][8]={"english", "german"};

//Ýngilizce dilinin frekans deðerleri
 const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//Almanca dilinin frekans deðerleri
 const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };


float gecme_sayisi[20]; // Bigram ve trigramlarin metinde gecme sayilarini tutan dizi.

float calculated_frequencies[20];
float distances [2]={0,0};


void filter_str(char str[]);
void calculate_frequencies_bi(char str[]);
void calculate_frequencies_tri(char str[]);
void calculate_distances();
void detect_lang();

int main()
{
    char metin[1000000]; /*Alınan metnin boyutuyla ilgili herhangi bir problem olmaması için boyut mümkün olduğunca yüksek tutulmaya çalışılmıştır.*/

    printf("\n************************************************************************************************************** \n\n");

    printf(" Hangi dilde yazildigini ogrenmek istediginiz metni giriniz: \n\n"); /*Kullanıcıdan metin alınır.*/
    gets(metin);

    filter_str(metin);

    printf(" Metindeki bigramlarin gecme sayisi ve frekansi: \n\n");

    calculate_frequencies_bi(metin);

    printf("\n************************************************************************************************************** \n\n");

    printf(" Metindeki trigramlarin gecme sayisi ve frekansi: \n\n");

    calculate_frequencies_tri(metin);

    printf("\n************************************************************************************************************** \n\n");

    calculate_distances();

    detect_lang();

    printf("\n************************************************************************************************************** \n\n"); /*Yıldızların yazdırılmasının amacı, kod bölümlerinin gözle ayrılmasını sağlayarak komut satırındaki kodların daha anlaşılabilir olmasını sağlamaktır.*/

	return 0;
}

void filter_str(char str[])
{
    for(int j=0;j<strlen(str);j++) /*strlen() fonksiyonu kullanılarak girilen metnin toplam harf sayısına kadar döngü devam etmektedir.*/
    {
        str[j]=tolower(str[j]); /*tolower() fonksiyonu kullanılarak (kodun ilerleyen kısımlarında kolaylık olması için) metindeki bütün harfler küçültülmüştür.*/
    }

    printf("\n\n************************************************************************************************************** \n\n");

    printf(" Metindeki butun harfler kucultulmustur: \n\n"); /*Büyük harf varsa küçültülür.*/
    puts(str);

    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]>=97 && str[i]<=122 || str[i]==32) /*Metindeki girdilerin sadece harf ve boşluktan oluşmasını sağlamak için ASCII kodları kullanılmıştır.*/
            continue;
        else
            str[i]=32; /*Harf ve boşluk harici bütün girdiler boşlukla değiştirilmiştir.*/
    }
    printf("\n\n************************************************************************************************************** \n\n");
    printf(" Metin yabanci karakterlerden temizlenmistir: \n\n"); /*Yabancı karakter varsa temizlenir*/
    puts(str);

    printf("\n\n************************************************************************************************************** \n\n");
}

void calculate_frequencies_bi(char str[]) /*Bigram frekans hesaplaması yapılır ve kullanıcıya sunulur.*/
{
    int i,j; /*Döngü dışında başka işlemlerde kullanıldıkları için döngü dışında tanımlanmışlardır.*/

    for(int a=0;a<strlen(str);a++) /*Metin döngüsü*/
    {
        for(i=0;i<10;i++) /*Bigramlarin ilk harfinin döngüsü*/
        {
            for(j=0;j<2;j++) /*Bigramların ikinci harfinin döngüsü*/
            {
                if(str[a]==matrix_bigram_strings[i][j] && str[a+1]==matrix_bigram_strings[i][j+1]) /*Metinde bigramların geçip geçmediği kontrol edilir.*/
                {
                    gecme_sayisi[i]++; /*Eğer geçiyorsa gecme_sayisi adlı dizinin gerekli indisi 1 artırılır.*/
                }
            }
        }
    }

    for(int b=0;b<10;b++) /*Her bir bigramın frekansı hesaplanır.*/
    {
        calculated_frequencies[b]=gecme_sayisi[b]*100/strlen(str);
        printf("'%c%c' bigrami metinde %.f kere gecmektedir ve frekansi : %f \n",matrix_bigram_strings[b][0],matrix_bigram_strings[b][1],gecme_sayisi[b],calculated_frequencies[b]);
    }
}

void calculate_frequencies_tri(char str[]) /*Trigram hesaplamaları yapılır ve kullanıcıya sunulur*/
{
    int i,j;

    for(int a=0;a<strlen(str);a++) /*Metin döngüsü*/
    {
        for(i=0;i<10;i++) /*Trigramların ilk harfinin döngüsü*/
        {
            for(j=0;j<3;j++) /*Trigramlar matrix şeklinde tanımlı oldukları için 2. ve 3. harflerinin döngüsü böyle tanımlanabilir. */
            {
                if(str[a]==matrix_trigram_strings[i][j] && str[a+1]==matrix_trigram_strings[i][j+1]) /*Metinde trigramların geçip geçmediği kontrol edilir.*/
                {
                    gecme_sayisi[i+10]++; /*Eğer geçiyorsa gecme_sayisi dizisindeki gerekli indis 1 artırılır. Bigramlar ilk 10 indisi kullandığından sonraki 10 indise geçebilmek için +10 eklenmiştir.*/
                }
            }
        }
    }

    for(int c=0;c<10;c++) /*Her bir trigramın frekansı hesaplanır.*/
    {
        calculated_frequencies[c+10]=gecme_sayisi[c+10]*100/strlen(str);
        printf("'%c%c%c' trigrami metinde %.f kere gecmektedir ve frekansi : %f \n",matrix_trigram_strings[c][0],matrix_trigram_strings[c][1],matrix_trigram_strings[c][2],gecme_sayisi[c+10],calculated_frequencies[c+10]);
    }
}

void calculate_distances() /*Öklid bağıntısı kullanılarak Ingilizce ve Almanca dizilerin uzaklıkları hesaplanmıştır.*/
{
    float eng_dis,ger_dis;

    for(int i=0;i<20;i++)
    {
        eng_dis+=pow(frequency_eng[i]-calculated_frequencies[i],2);
    }
        distances[0]=sqrt(eng_dis);

    for(int j=0;j<20;j++)
    {
        ger_dis+=pow(frequency_germ[j]-calculated_frequencies[j],2);
    }
        distances[1]=sqrt(ger_dis);
}

void detect_lang() /*Metnin dilinin Ingilizce mi yoksa Almanca mı olduğu belirlenir ve kullanıcıya gösterilir.*/
{
    if(distances[0]>distances[1])
    {
        printf(" Metin Almanca yazilmistir.\n");
    }
    else if(distances[0]<distances[1])
    {
        printf(" Metin Ingilizce yazilmistir. \n");
    }
    else
        printf(" Metnin hangi dilde yazildigi bulunamadi. \n"); /*Küçük bir ihtimal de olsa uzaklıkların eşit çıkma ihtimalinden dolayı else bloğu eklenmiştir.*/
}
