# Czat Sieciowy (Windows Sockets)

## Opis projektu

Projekt implementuje prostą aplikację czatu sieciowego z architekturą klient-serwer przy użyciu Windows Sockets API. System umożliwia wielu użytkownikom komunikację w czasie rzeczywistym w ramach jednej grupy czatowej.

## Architektura systemu

System składa się z dwóch głównych komponentów:
- **Serwer czatu** - obsługuje połączenia klientów i przekazuje wiadomości
- **Klient czatu** - umożliwia użytkownikowi wysyłanie i odbieranie wiadomości

### Serwer czatu

Serwer implementuje następującą funkcjonalność:
- Nasłuchiwanie połączeń na porcie 1234
- Obsługę wielokrotnych jednoczesnych połączeń klientów
- Przekazywanie wiadomości do wszystkich podłączonych klientów (broadcast)
- Bezpieczne zarządzanie wątkami przy użyciu mutex

#### Kluczowe elementy implementacji

```cpp
mutex chat_mutex;
map<SOCKET, string> clients;

void handle_client(SOCKET client_socket) {
    // Obsługa pojedynczego klienta
    // Odczyt wiadomości i broadcast do innych klientów
}
```

### Klient czatu

Klient zapewnia:
- Łączenie z serwerem pod adresem 127.0.0.1 (localhost)
- Identyfikację użytkownika za pomocą nicku
- Wysyłanie i odbieranie wiadomości w czasie rzeczywistym
- Osobny wątek do obsługi przychodzących wiadomości

#### Kluczowe elementy implementacji

```cpp
void receive_messages(SOCKET client_socket) {
    // Odczyt wiadomości w osobnym wątku
}

// Główny wątek - wysyłanie wiadomości
string message = nick + ": " + message;
send(client_socket, message.c_str(), message.size(), 0);
```

## Wymagania systemowe

- System operacyjny: Windows
- Kompilator: Microsoft Visual C++ lub MinGW
- Biblioteka: ws2_32.lib (Windows Sockets)

## Kompilacja i uruchomienie

### Kompilacja
```bash
# Dla Microsoft Visual C++
cl Server.cpp -lws2_32
cl Client.cpp -lws2_32

# Dla MinGW
g++ Server.cpp -o Server.exe -lws2_32
g++ Client.cpp -o Client.exe -lws2_32
```

### Uruchomienie

1. **Uruchom serwer**:
```bash
./Server.exe
```
Serwer rozpocznie nasłuchiwanie na porcie 1234.

2. **Uruchom klienta**:
```bash
./Client.exe
```
Program poprosi o podanie nicku użytkownika.

3. **Rozpocznij czat**:
Po połączeniu możesz wpisywać wiadomości. Każda wiadomość zostanie przesłana do wszystkich innych podłączonych użytkowników.

## Funkcjonalność

### Serwer
- Automatyczne akceptowanie nowych połączeń
- Zarządzanie listą aktywnych klientów
- Przekazywanie wiadomości do wszystkich klientów (odbiorca nie otrzymuje własnej wiadomości)
- Usuwanie klientów po rozłączeniu
- Wielowątkowa obsługa klientów

### Klient
- Wprowadzanie nicku użytkownika
- Łączenie z serwerem lokalnym
- Wysyłanie wiadomości po naciśnięciu Enter
- Odbieranie i wyświetlanie wiadomości w czasie rzeczywistym
- Automatyczne rozłączanie przy zamknięciu aplikacji

## Format wiadomości

Wiadomości są formatowane jako:
```
[nick]: [treść wiadomości]
```

## Ograniczenia i uwagi

1. **Rozmiar wiadomości**: maksymalnie 512 bajtów
2. **Adres serwera**: serwer jest zatwierdzony na lokalnym komputerze (127.0.0.1)
3. **Port**: aplikacja używa portu 1234 (należy się upewnić, że port jest wolny)
4. **Brak uwierzytelniania**: system nie posiada mechanizmu uwierzytelniania użytkowników
5. **Format znaków**: aplikacja może mieć problemy z polskimi znakami w niektórych konsolach

## Bezpieczeństwo wątków

Program wykorzystuje mutex (`chat_mutex`) do synchronizacji dostępu do listy klientów, co zapewnia bezpieczeństwo w środowisku wielowątkowym.

## Możliwe rozszerzenia

- Dodanie historii wiadomości
- Implementacja prywatnych wiadomości
- System autoryzacji użytkowników
- Obsługa wielu kanałów czatu
- Interfejs graficzny
- Szyfrowanie komunikacji
- Przechowywanie wiadomości w bazie danych

## Autor

Copyright [2025] Alicja Fuks
