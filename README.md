# IRC

Internet Relay Chat или IRC — это текстовый протокол связи в Интернете.
Он предлагает обмен сообщениями в режиме реального времени, который может быть как публичным, так и частным. Пользователи могут обмениваться
прямые сообщения и присоединяйтесь к групповым каналам.
Клиенты IRC подключаются к серверам IRC, чтобы присоединиться к каналам. IRC-сервера подключены
вместе, чтобы сформировать сеть.


**Подключение**

1) Запуск сервера:

    `make`

   `./ircserv <port> <password>`
- где port - это порт на котором будет подключен сервер, а password - пароль для подключения к серверу.

2) Подключение клиента к сереверу(через терминал):

    `nc <localhost/ip> <port>`
- nc - это утилита командной строки, которая считывает и записывает данные через сетевые соединения с использованием протоколов TCP или UDP; 
localhost - для запуска клиента на том же компьютере, где запущен сервер, или ip - если компьютер находится в той же локальной сетке что и сервер;
и port - это порт на котором подключен сервер.

3) Авторизация клиента:

    `NICK <nick>`
- NICK используется для установки пользовательского никнейма или изменения предыдущего, где nick - никнейм.

    `PASS <password>`
- PASS используется для установки 'парольного соединения', где password - сам пароль.

    `USER <username> <hostname> <servername> <realname>`
- USER используется для указания: username - имени пользователя, hostname - названия хоста, servername - названия сервера и realname - реального имени нового 
пользователя.


*После успешного подключения, клиента встречает приветственное сообщение:*

<img width="683" alt="Welcome message" src="https://github.com/Kirillznkv/ft_irc/blob/main/info/images/welcome%20message.png">