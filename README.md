# Game of Life
Интерактивная консольная игра "Жизнь" для Linux, написанная на языке С.
## Описание
Этоа программа - классическая игра-клеточный автомат "Жизнь" со стандартными правилами для Linux-подобных ОС. Описание и правила игры: [Wikipedia](https://ru.wikipedia.org/wiki/Игра_«Жизнь»).
## Технологии в проекте
Игра написана с использованием языка С и библиотеки [ncurses](https://ru.wikipedia.org/wiki/Ncurses). Программу можно собрать с помощью утилиты Make и файла Makefile.
## Техническое описание проекта
### Сборка и запуск игры
Для того, чтобы собрать игру, откройте игру в папке с проектом и выполните команду в терминале:

make all

Команда создаст файл game.out в том же каталоге. Выполнив в терминале команду:

./game.out

можно запустить игру.
## Использование программы
После запуска игра предложит выбрать начальную конфигурацию игры:

![image](https://github.com/futurewillbeours/game_of_life/assets/134860207/7d4161a3-2d1c-4a65-b492-1db9cf9a072c)

Описание режимов:
1. Cycle - цикл. Игра повторяет с течением времени свои прежние состояния.
2. Extinction 1 - вымирание. С течением времени все клетки на поле умирают и игра завершается.
3. Doesn't change - состояние игры не меняется в течение времени.
4. Extinction 2 - вымирание. То же, что и п.2, но с другой конфигурацией.
5. Planner - клетки имитируют летящий самолет и движутся в одном направлении.

После ввода номера конфигурации и нажатия кнопки Enter игра начинается. Открывается цикличное игровое поле и можно наблюдать изменение поля.

Чтобы ускорить игру, можно нажимать кнопку A. Чтобы замедлить игру - кнопку Z. Выйти из игры можно нажав кнопку Q.

Начальные конфигурации поля можно менять в файлах conf1.txt - conf5.txt. В этих файлах конфигурация задана как часть поля в виде матрицы из 0 и 1. Цифры 0 означают пустую клетку,  означает наличие жизни в клетке.
