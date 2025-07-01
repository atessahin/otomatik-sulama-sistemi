# otomatik-sulama-sistemi
Bu proje, STM32F4 mikrodenetleyicisi kullanılarak geliştirilen, **YL-69 nem sensörü** yardımıyla toprağın nem seviyesine göre **otomatik olarak sulama yapan bir sistemdir**.


## Kullanılan Teknolojiler
- **Mikrodenetleyici**: STM32F407 
- **Programlama Dili**: C (STM32 HAL/LL kütüphanesi kullanılmadan, doğrudan register bazlı)
- **IDE**: STM32CubeIDE / Keil / PlatformIO uyumlu
- **Donanım Katmanı**: GPIO, SysTick, RCC, UART

## Kullanılan Teknolojiler
- **config.c**:  Sistem saat ayarları, GPIO konfigürasyonu, UART kurulumları ve delay fonksiyonu 
- **functionality.c**: Sensör verisinin okunması, sulama kararlarının verilmesi, motorun kontrol edilmesi 
- **config.h**: Fonksiyon prototipleri ve tanımlar 

## Donanım Gereksinimleri
- STM32F4 Geliştirme Kartı
- YL-69 Nem Sensörü
- Röle Modülü
- Su pompası (motor)
- 5V Güç Kaynağı
- UART haberleşme için USB-TTL dönüştürücü (isteğe bağlı ve debug için faydalı)

## Sistem Çalışma Prensibi

1. **YL-69 nem sensörü**, dijital çıkışı ile toprağın ıslak ya da kuru olduğunu belirler.
2. Eğer toprak kuruysa ve bir önceki kontrol üzerinden **60 saniye** geçtiyse, sistem su pompasını **10 saniye** boyunca çalıştırır.
3. Eğer toprak ıslaksa, sistem beklemeye geçer, motor çalışmaz.
4. Bu mantık **sürekli çalışan bir zamanlayıcı (SysTick)** ile kontrol edilir.
5. UART üzerinden bilgisayara log mesajları göndermek de mümkündür (isteğe bağlı geliştirme)


##  Fonksiyon Açıklamaları

### `systemClockConfig()`
- HSE  + PLL kullanılarak sistem saat frekansını 84 MHz'e çıkarır.
- FLASH latency ayarları yapılır.
- AHB, APB1 ve APB2 bus'ları uygun şekilde bölünür.

### `gpioConfig()`
- `PC4`: Röle kontrol pini 
- `PC1`: Nem sensörü dijital çıkış pini 
- `PA2/PA3`: UART2 iletişimi için alternatif fonksiyon olarak yapılandırılır.

###  `uartConfig()`
- UART2 aktif hale getirilir.
- Baudrate: 115200
- TX ve RX pinleri yapılandırılır.
- UART kullanılarak dış dünyaya bilgi iletmek mümkündür.

###  `wetLevel()`
- PC1 pininden nem sensörü durumu okunur.
- Giriş 0 ise → Toprak kuru, 1 ise → Islak olarak değerlendirilir.

###  `startWatering()` & `stopWatering()`
- Röleyi tetikleyerek motoru çalıştırır veya durdurur.

###  `sulama()`
Sistemin ana karar alma fonksiyonudur:
- Sistemin o anki zamanı `systemTick` ile takip edilir.
- Önce toprak durumu okunur.
- Uygun koşullarda motor başlatılır.
- 10 saniye sonunda motor durdurulur.

###  `SysTick_Handler()`
- Her 1 ms'de bir tetiklenir.
- `systemTick` sayaç değişkeni artırılır.

##  Parametreler

- **WATERING_DURATION**: Sulama süresi (varsayılan 10 saniye)
- **CHECK_INTERVAL**: Nem kontrol aralığı (varsayılan 60 saniye)


## Derleme Talimatları

Proje STM32CubeIDE, Keil, PlatformIO gibi ARM destekli IDE’lerde derlenebilir.
(Bu proje Keilde yapılmıştır)



