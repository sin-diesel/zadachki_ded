# zadachki_ded
## Установка
### Установка как библиотеки
Добавьте `equation.cpp` и `equation.h` в код. Подключайте `equation.h` когда надо решить уравнение
### Установка как программы
Скачайте `equation.cpp`, `equation.h`, `test.cpp`, `test.h`, `Source.cpp` и скомпилируйте в любом компиляторе c / c++
## Использование как библиотеку
Функция которая решает квадратное уравнение.
```c
solveEquations(double a, double b, double c, RootsPair * pair)
```
Принимает числа a, b, c - коэффициенты уравнения, а также массив res, куда будет записан результат. Массив должен быть как минимум размера 2.
Возвращаемое значение `EquationResult` равно `EQUATION_RESULT_OVERFLOW_ERROR`, если произошла ошибка переполнения, `EQUATION_RESULT_NO_ROOTS`, если корней нет,
`EQUATION_RESULT_INFINITE_ROOTS`, если корни - вся числовая прямая, или число, соответствующее количеству корней.

Корни можно вывести в консоль функцией `outResult()`, принимающей `EquationResult` и `RootsPair` и выводящей подходящее сообщение.

`RootsPair` - структура, хранящая корни. По умолчанию инициализирована как `{nan(""), nan("")}`. Если уравнение находит один корень, то он будет записан в `RootsPair::r1`, а `RootsPair::r2` остается без изменения. Если уравнение не находит корней или их бесконечность, то объект остается без изменения.

## Использование как программу
Программа выполняет несколько тестов, после чего запрашивает пользователя ввести коэффициенты уравнения и решает это уравнения, выводя пользователю ответ
