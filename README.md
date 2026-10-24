# Arduino–Raspberry Pi Distance Monitor

HC-SR04 ultrasonik mesafe sensörünün Arduino Uno ile okunması ve ölçümlerin USB seri haberleşme üzerinden Raspberry Pi'de izlenmesi.

## Mevcut durum

- Arduino Uno üzerinde mesafe ölçümü laptopta test edildi.
- Arduino, USB ile Raspberry Pi'ye bağlandı ve seri porttan ölçümler okundu.
- Tarayıcı paneli, veri kaydı ve eşik tabanlı uyarılar henüz uygulanmadı; sonraki geliştirmelerdir.

## Donanım

- Arduino Uno R3
- HC-SR04 mesafe sensörü
- Raspberry Pi 4 Model B (4 GB), Raspberry Pi OS (64-bit), microSD ve uygun güç adaptörü
- Veri aktarabilen Arduino USB kablosu
- Jumper kablolar, gerekirse breadboard
- Kodu yüklemek ve Pi'ye SSH ile erişmek için laptop

## Bağlantılar

Bağlantıları Arduino'nun enerjisi kesilmişken yapın.

| HC-SR04 | Arduino Uno |
| --- | --- |
| VCC | 5V |
| Trig | D9 |
| Echo | D10 |
| GND | GND |

Sensör Arduino'ya bağlıdır. Arduino ile Pi arasındaki bağlantı USB üzerinden yapılır; Uno'nun 5 V sinyalleri Pi'nin GPIO pinlerine doğrudan bağlanmaz.

## Arduino kodunu yükleme

1. `arduino/distance_sensor/distance_sensor.ino` dosyasını Arduino IDE'de açın.
2. Arduino'yu USB ile laptopa bağlayın.
3. Kart olarak **Arduino Uno**, port olarak kartın bağlı olduğu COM portunu seçin.
4. Kodu yükleyin. Harici Arduino kütüphanesi gerekmez.
5. Seri Port Ekranı'nı **9600 baud** ile açın.
6. Sensörün önüne 10–50 cm uzaklıkta düz bir kitap veya kutu tutup hareket ettirin.

Örnek çıktı (gerçek deney kaydı değildir):

```text
Mesafe: 25.4 cm
Mesafe: 18.2 cm
Mesafe: 10.7 cm
```

Kod yankı gelmediğinde `Olcum alinamadi`, hesaplanan mesafe 2–400 cm dışında olduğunda `Olcum aralik disinda` yazar. Bu aralık kontrolü tek başına ölçüm doğruluğunu garanti etmez. Ölçülen süre, sesin yaklaşık 0.0343 cm/µs hızıyla çarpılır ve gidiş-dönüş yolunu hesaba katmak için ikiye bölünür.

## Raspberry Pi'den okuma

1. Laptopta Arduino Seri Port Ekranı'nı kapatın.
2. Arduino USB kablosunu laptoptan çıkarıp kendi adaptörüyle çalışan Pi'ye takın.
3. Laptop ve Pi aynı yerel ağdayken Pi'ye SSH ile bağlanın:

```bash
ssh KULLANICI_ADI@PI_ADI.local
```

4. PySerial kurulu değilse kurun:

```bash
sudo apt update
sudo apt install python3-serial
```

5. Seri portları listeleyin:

```bash
python3 -m serial.tools.list_ports
```

Bu kurulumda Arduino `/dev/ttyUSB0` olarak bulundu. Farklı kartlarda `/dev/ttyACM0` veya başka bir port adı görülebilir; aşağıdaki komutta kendi çıktınızı kullanın.

```bash
python3 -m serial.tools.miniterm /dev/ttyUSB0 9600
```

Port açıldığında Uno yeniden başlayabilir. Birkaç saniye sonra ölçümler görünmelidir. Çıkmak için **Ctrl + ]** kullanın. Şu aşamada Pi'de özel bir Python uygulaması yerine PySerial'ın hazır terminal aracı kullanılıyor.

## Sorun giderme

- **Boş seri ekran:** 9600 baud, doğru port ve yüklemenin tamamlandığını kontrol edin; Uno'nun RESET düğmesine bir kez basın.
- **Ölçüm alınamıyor:** VCC/GND ve Trig/Echo bağlantılarını kontrol edin; sensörün önünde düz bir hedef kullanın.
- **No module named serial:** `sudo apt install python3-serial` çalıştırın.
- **Permission denied:** `groups` çıktısında `dialout` grubunu kontrol edin. Gerekiyorsa `sudo usermod -aG dialout "$USER"` komutundan sonra SSH oturumunu kapatıp yeniden bağlanın.
- **SSH adı bulunamıyor:** Pi'nin açık olduğunu ve laptopla aynı ağda bulunduğunu kontrol edin. Gerekirse Pi'nin güncel IP adresiyle bağlanın.
- **Connection reset:** SSH bağlantısı kesilmiştir. Wi-Fi/hotspot ve Pi'nin güç bağlantısını kontrol edip yeniden bağlanın; bu mesaj tek başına sensör arızası göstermez.

## Sonraki geliştirmeler

- [ ] Tarayıcıda canlı mesafe göstergesi
- [ ] Zaman bilgisiyle ölçüm kaydı
- [ ] Ayarlanabilir yakınlık eşiği ve LED uyarısı
- [ ] Arduino'ya Pi üzerinden komut gönderme

## Öğrenilen konular

Sensör okuma, ultrasonik uçuş süresinden mesafe hesaplama, USB seri haberleşme, baud hızı, Linux seri portları ve SSH üzerinden Raspberry Pi kullanımı.
