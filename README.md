# Sosyal Ağ Ağacı ve Grafik Analizi

Bu proje, sosyal ağları hem **ağaç** hem de **graf** veri yapıları kullanarak modellemektedir. Kullanıcılar arasındaki ilişkileri analiz etmeyi, toplulukları keşfetmeyi ve kullanıcı etkisini hesaplamayı mümkün kılmaktadır. Aşağıda, projenin yapısı ve işlevleri ayrıntılı olarak açıklanmaktadır.

---

## **Özellikler**

1. **Kullanıcı ve İlişki Modelleme:**
   - Kullanıcılar düğümler olarak temsil edilir.
   - Kullanıcılar arasındaki ilişkiler yönlü bir graf olarak temsil edilir.

2. **Hiyerarşik Veri Yönetimi:**
   - Kullanıcı verilerini düzenlemek için kırmızı-siyah ağaç kullanılmıştır; bu, verimli arama, ekleme ve yönetim sağlar.

3. **Grafik Analizi:**
   - İlişkileri ve topluluk yapısını analiz etmek için grafik tabanlı algoritmalar uygulanmıştır.

4. **Temel İşlevler:**
   - Sosyal ağa kullanıcı ekleme.
   - Kullanıcılar arasında ilişki kurma.
   - Belirli bir derinlikteki arkadaşları Bulma (DFS kullanarak).
   - Bağlı bileşenlerin (toplulukların) tespiti.
   - Kullanıcı etkisini hesaplama (ağ üzerindeki erişimi).

---

## **Kod Yapısı**

### **Temel Veri Yapıları**

1. **Ağaç Düğümü (`AgacDugum`):**
   - Bir ağaç yapısında kullanıcıyı temsil eder.
   - `kullanici_id`, `cocuklar` ve `renk` (kırmızı-siyah ağaç özellikleri için) gibi özellikler içerir.

2. **Sosyal Ağ Ağacı (`SosyalAgAgaci`):**
   - Kırmızı-siyah ağaç kullanılarak kullanıcı verilerini depolar.
   - Grafik işlemleri için tüm düğümlerin bir listesini tutar.

---

### **Gerçekleştirilen Fonksiyonlar**

#### **Ağaç İşlemleri**
- `yeniDugum(int kullanici_id)`: Bir kullanıcı için yeni bir ağaç düğümü oluşturur.
- `yeniSosyalAg()`: Sosyal ağ ağacını başlatır.
- `kullaniciEkle(SosyalAgAgaci* ag, int kullanici_id)`: Ağaca yeni bir kullanıcı ekler.

#### **Grafik İşlemleri**
- `iliskiEkleAgac(SosyalAgAgaci* ag, int kullanici_id1, int kullanici_id2)`: İki kullanıcı arasında yönlü bir ilişki kurar.
- `derinlikIlkArama(SosyalAgAgaci* ag, int baslangic_id, int hedef_derinlik)`: Belirli bir derinlikteki arkadaşları bulur.

#### **Topluluk Tespiti**
- `toplulukTespit(SosyalAgAgaci* ag)`: Grafikte bağlı bileşenleri (toplulukları) tespit eder.

#### **Etki Hesaplama**
- `kullaniciEtkisi(SosyalAgAgaci* ag, int kullanici_id)`: Bir kullanıcının ağ üzerindeki etkisini, erişilebilir kullanıcı sayısına göre hesaplar.

---

## **Kullanım**

1. **Kullanıcı Ekleme:**
   `kullaniciEkle` fonksiyonu kullanılarak ağa kullanıcı eklenir. Örnek:
   ```c
   kullaniciEkle(sosyalAg, 101);
   kullaniciEkle(sosyalAg, 102);
   ```

2. **İlişki Kurma:**
   `iliskiEkleAgac` fonksiyonu ile kullanıcılar arasında ilişki tanımlanır. Örnek:
   ```c
   iliskiEkleAgac(sosyalAg, 101, 102);
   iliskiEkleAgac(sosyalAg, 101, 103);
   ```

3. **Derinlikteki Arkadaşları Bulma:**
   `derinlikIlkArama` fonksiyonu ile belirli bir derinlikteki arkadaşlar bulunur. Örnek:
   ```c
   derinlikIlkArama(sosyalAg, 101, 2);
   ```

4. **Topluluk Tespiti:**
   `toplulukTespit` fonksiyonu ile bağlı bileşenler belirlenir. Örnek:
   ```c
   toplulukTespit(sosyalAg);
   ```

5. **Etki Hesaplama:**
   `kullaniciEtkisi` fonksiyonu ile bir kullanıcının etkisi hesaplanır. Örnek:
   ```c
   int etkisi = kullaniciEtkisi(sosyalAg, 101);
   printf("Kullanici 101 etkisi: %d\n", etkisi);
   ```

---

## **Örnek Çıktı**

### **Girdi:**
- Kullanıcı ekleme: `101, 102, 103, 104, 105`
- İlişkiler:
  - `101 -> 102`
  - `101 -> 103`
  - `102 -> 104`
  - `103 -> 104`
  - `104 -> 105`

### **Çıktı:**
1. **Belirli Derinlikteki Arkadaşlar:**
   ```
   Derinlikteki arkadaslar:
   104 104
   ```

2. **Topluluklar:**
   ```
   Topluluklar:
   Topluluk: 101 102 103 104 105
   ```

3. **Kullanıcı Etkisi:**
   ```
   Kullanici 101 etkisi: 5
   ```

---

## **Uygulama Alanları**

Bu uygulama aşağıdaki alanlarda kullanılabilir:

1. **Sosyal Medya Platformları:**
   - Kullanıcı ilişkilerini modellemek ve analiz etmek.
   - Ağ analizi ile önerilerde bulunmak.

2. **Pazarlama ve Etki Analizi:**
   - Ağdaki kilit etkileyicileri belirlemek.

3. **Topluluk Tespiti:**
   - Hedefli pazarlama veya içerik dağıtımı için toplulukları analiz etmek.

4. **Veritabanı Yönetimi:**
   - Hiyerarşik ilişkileri verimli bir şekilde düzenlemek.

---

## **Bağımlılıklar**

- C standart kütüphaneleri: `<stdio.h>` ve `<stdlib.h>`

---

## **Gelecekteki Geliştirmeler**

1. Karşılıklı ilişkileri ele almak için yönsüz graf desteği.
2. Daha iyi ölçeklenebilirlik için dinamik kırmızı-siyah ağaç dengelemesi.
3. İlişki gücü için ağırlıklı kenarların uygulanması.
4. Daha büyük ağlar için DFS optimizasyonu.

---

Bu proje, sosyal ağları modellemek, düzenlemek ve analiz etmek için kapsamlı bir yaklaşım sunmaktadır.

