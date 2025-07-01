# otomatik-sulama-sistemi
Bu proje, STM32F4 mikrodenetleyicisi kullanılarak geliştirilen, **YL-69 nem sensörü** yardımıyla toprağın nem seviyesine göre **otomatik olarak sulama yapan bir sistemdir**.

## Donanım Gereksinimleri

- STM32F4 Geliştirme Kartı
- YL-69 Nem Sensörü
- Röle Modülü
- Su pompası (motor)
- 5V Güç Kaynağı
- UART haberleşme için USB-TTL dönüştürücü (isteğe bağlı ve debug için faydalı)

## Yazılım Modülleri

### 1. `config.c`
Bu dosya donanımsal ayarları içerir:

#### `systemClockConfig()`
Sistem saatini HSE  + PLL kullanarak 84 MHz’e çıkarır. Bu işlem Flash, AHB, APB1, APB2 saat bölücüleri ile birlikte ayarlanır. Saat ayarları doğru yapılmazsa zamanlama bozuk olur.

#### `gpioConfig()`
- `GPIOC->MODER`: PC4 çıkış olarak ayarlanır (röle kontrolü)
- `PC1`: Nem sensörü dijital çıkışı için giriş modunda ayarlanır.
- `PA2/PA3`: UART2 için alternatif fonksiyon modunda ayarlanır.

#### `uartConfig()`
- USART2 (PA2: TX, PA3: RX) yapılandırılır.
- Baudrate: 115200
- UART üzerinden bilgisayara log gönderimi için kullanılabilir.

### 2. `functionality.c`
Bu dosya, sistemin sulama mantığını içerir.

## ⏱️ Parametreler

- **WATERING_DURATION**: Sulama süresi (varsayılan 10 saniye)
- **CHECK_INTERVAL**: Nem kontrol aralığı (varsayılan 60 saniye)


##  Çalışma Mantığı

1. YL-69 sensörü toprağın nem durumunu okur.
2. Eğer nem düşükse (kuruysa=0) ve son sulamadan itibaren 60 saniye geçtiyse;
   - Röle tetiklenir, motor çalıştırılır.
   - 10 saniye boyunca sulama yapılır.
3. Eğer  nem düşükse yüksekse (ıslaksa=1), sistem motoru çalıştırmaz.
4. Tüm bu işlemler `SysTick_Handler` zamanlayıcısı ile periyodik olarak kontrol edilir.

## 🔧 Derleme Talimatları

Proje STM32CubeIDE, Keil, PlatformIO gibi ARM destekli IDE’lerde derlenebilir.
(Bu proje Keilde yapılmıştır)



