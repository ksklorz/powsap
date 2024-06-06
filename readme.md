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
W folderze znajdują się dedykowane klasy tylko pod arduino. Klasa taskThread jest klasą czysto wirtualną. DAje narzędzia do periodycznego wywoływania określonego zadania. Jest to tylko pseudowątek, bo algorytmy muszą i tak ise wykonywać sekwencyjnie (arduino beznadziejnie radzi sobie z FreeRTOSem). W aktualnej werjsi z tej klasy dziedziczą wątki odpowiedzialne za komunikację i panel użytkownika. 

Wątek od komunikacji periodycznie sprawdza czy nie pojawiły się nowe dane na porcie. Dodatkowo są tam narzędzia do wysyłania danych.

Wątek panelu jest bardziej rozbudowany. Korzysta z klas PanelButton i PanelDisplay, które dziedziczą z wcześniej wspomnianeych klas, ale posiadają pewne dedykowane narzędzia wykorzystujące konkretne struktury w projekcie. 

W klasie zaimplmentowana jest maszyna stanów. Wciśnięcie odpowiedniego przycisku może zmienić aktualny stan. Po wejściu do satnu wywoływana jest funkcja, która w szczególności ustawia nowe znaczenie przycisków. W każdym ze stanów cyklicznie wywoływana jest funkcja np. odświeżająca wyświetlacz.

W aktualnym działaniu:
Na ekranie wyświetlają się jakieś różne informacje zebrane z systemu. 3 przyciski przechodzą odpowiednio do ustawień temperatury, światła i rolety. Potencjometrem możena w tym momencie wybrać odpowiedni poziom. JEden z przycisków wraca, drugi zatwierdza i wysyła. PRzynajmniej takie jest założenie, aktualnie wysyłane są na bieżąco, żeby można był owszystko szybko płynnie zmieniąc, bo tak testowałem, ale jeszcze nie wiem jak się skończy. 

### espMaster

Płytka podpięta serialem do arduino. Dużej filozofii nie ma. Jeden wątek czyta serial, drugi wysyła na serial, trzeci obsługuje espNow (odbieranie i wysyłanie). Jak coś przyjdzie na serial to przechodzi przez kolejkę FreeRTOS, i watek espNow wysyła to do konkretnego slava. Jak cos przyjdzie na espNow od slava, to trafia do kolejki i po uarcie do arduino.

### espLight
Odbiera wartosć zadaną. Wysterowuje światło na odpowiedni poziom (funkcja nieliniowa bo ludzkei oko nieliniowo odbiera natężenie światła).

### espHeater
Kila wątków. Osobne do wysterowania przekaźnika, do odczytu temperatury, do regulatora, do komunikacji. W ząłożeniu odbiera po espNow zadaną temperaturę. Regulator cyklicznie liczy wysterowania PID i odpowiednio ustawia szerokość impulsu PWM przekaźnika.

Nastawy losowe, jak będzie obiekt to się będę martwił.

### espWindow
Regulacja aktualnie w jednym wątku (w lib jest to rozbudowane). Przyjmuje wartosć zadaną i wysterowuje kaskadę regulatorów. Do dorobienia dopiero obsługa fotorezystora




