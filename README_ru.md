# TroykaHatCpp

## Установка библиотеки

Установка библиотеки `libGpioExpanderPi` в систему:

```bash
make
sudo make install
```

## Использование библиотеки

Для использования бибилиотеки добавьте флаг `-lGpioExpanderPi` при компиляции.

## Примеры

Для компиляции примеров:

```bash
make examples
```

## Запуск примеров

Традиционный Blink:

```bash
./examples/digitalWrite
```

Чтение состояния кнопки:

```bash
./examples/digitalRead
```

Управлем потенциометром яркостью светодиода:

```bash
./examples/analogReadWrite
```