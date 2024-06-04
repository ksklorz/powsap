# Projekt POWSAP

Projekt składa się z 5 płytek. 1 Arduino jako panel sterowania jest podłączone do esp32c3 które odpowiada za komunikację z resztą systemu. Pozostałe 3 płytki wykonują poszczególne zadania. Jako, że projekt na esp32 pisany z wykorzystaniem FreeRTOS, płytki można w miarę swobodnie dzielić lub łączyć, swobodnie modyfikująć system.

## Podział projektu

Cały software na wszystkie płytki znajduje się w jednym projekcie PlatformIO. Podział kodu na podprojekty skonfigurowany w pliku platformio.ini. 

Uniwersalne klasy, nadające się do wielu projektów zostały dodane w katalogu lib. CZasem z tych samych klas korzysta wiele płytek, czasem tylko jedna, ale można je swobodnie dołączać do każdego projektu.

W głównym katalogu src znajduje się trochę wspólnego kodu, z którego korzysta kilka płytek (ale nie jest na tyle uniwersalny by nadawał się do innych projektów).

W poszczególnych podfolderach znajdują się kody stricte pod konkretne płytki (przy komilacji na płytkę reszta podfolderów jest pomijana). W każdym z tych folderów jest plik main.cpp - główny plik wykonawczy dla danej płytki, plik config.h - plik z konfiguracją pinoutu itp., oraz wszelkie inne pliki z dedykowanymi wątkami i narzędziami. 

## Bibliotek klas

Wszystkie z tych klas zostały stworzone pod projekt, ale są w miarę uniwersalne i mogą się przydać do czegoś innego. Opis w miarę losowej kolejności. Prawie wszystkie są do przerobienia/rozbudowy.

### button
Klasa obsługująca przycisk pod odpowiednim pinem. Musi byc regularnie odświeżana. Zabezpieczona debouncingiem. Posiada wskaźnik do wykonywanej funkcji, przez co znaczenie przycisku można łatwo zmieniać dynamicznie.

### display
Wyświetlacz oled po i2c. NArzędzia do konfiguracji i podstawowe narzedzia do wyświetlania.

### lightbulb
Wbrew nazwie, to obsługa diody (ze ściemnianiem)

### mySerial 
Szablon do obsługi seriala. Niestety SoftwareSerial i HardwareSerial to inne klasy, więc dodałem szablon żeby tymi samymi narzędziami obsłużyć oba, zależnie tylko od konfiguracji (W arduio ciężko z HardwareSerialem)

### potentiometer
Potejncjometr. Zwraca przeliczenia sygnału analogowego.

### relay
Obsługa przekaźnika. Wysterowanie "wolnym" pwm. Na tyle wolnym, że użycie sprzętowego nie jest potrzebne (a nawet uciążliwe). Musi być regularnie odświeżana rozdzielczość 1e-3.

### termometer
obsługa DB18B20

### tools 
Przestrzeń nazw z róznymi narzeziami wspólnymi. Obecnie tylko CRC do komunikacji.

### PID
Klasa regulatora PID. Dodatkowo saturacja, filtracja D i anty-windup. DZiałąnie wymaga odświeżenia wartoscią zadana i wartoscią zmierzoną (różnica jest liczona wewnątrz klasy). Zwraca wysterowanie.

### encoder
Obsługa enkodera przyrostowego. Impulsy zliczane na jednym przerwaniu (dałoby sie wykorzystać 2 zwiększając rozdzielczość nawet 4 razy, ale nie zauważyłem by było to niezbędne). Odświeżenie powoduje wyliczenie prędkości kątowej. Zwraca też pozycje w radianach (stały przelicznik z impulsów)

### motor
Obsługa silnika DC. Skorzystano ze sterownika w którym 2 piny sterują mostkiem H, a trzeci wysterowywuje wypełnienie PWM. Odpowiednia metoda pozwala na wysterowanie napięcia na silniku w zakresie [-1;1]

### feedbackMotor
Klasa silnika DC ze sprzężeniem zwrotnym. DZiedziczy z klas motor i encoder, przez co można używać jej w tamten sposób. Dodatkowo posiada regulator PID z hardkodowanymi nastawami. Umożliwia to zadanie prędkości. DZiałąnie regulatora wymaga regularnego odświeżania.

### positionControler
Klasa dziedziczy z feedbackMotor. Zewnętrzna pętla regulacji umożliwia wysterowanie zadanego kąta silnika (wieloobrotowe).

### linearServo
Dziedziczy z positionControler. Jedynie dodaje narzędzia do zadawania pozycji liniowej (przeliczenie obrótów na przemieszczenie liniowe).

## SRC

W folderze src znajduje się reszta plików dedykowanych do projektu. W głównym folderze znajdują się źródła z których koszysta wiele płytek

### struct
Definicje wspólnych struktur. W szczególności znajduje się tu struktura sPacket, która jest wykorzystywana do rozsyłania informacji po systemie (zawiera docelową płytkę oraz odpowiednią daną). 

### MACdata
Dane MAC płytek do rozsyłania bezprzewodowego. Tutaj jest definicja która płytka co robi

### taskEspNow
Wątek FreeRTOS odpowiadający za komunikację po esp-now. posiada dwie kolejki - do jedne wrzuca otrzymane pakiety, z drugiej rozsyłą gdy tylko coś na niej się pojawi.

### arduino




