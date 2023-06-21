# Audio Captcha
##### <https://www.youtube.com/watch?v=aGhHXSs0WHw>
---

Подключаем после всех ```include```
 ```pawn
 #include <audio_captcha>
 ```
 Функция для показа капчи игроку:
```pawn
captcha_ShowPlayer(playerid, captchaid)
```
- ```playerid``` - передаем идентификатор игрока
- ```captchaid``` - передаем идентификатор константы

Callback для проверки ввода капчи
```pawn
OnPlayerInputCaptcha(playerid, captchaid, bool: correct_number)
```
- ```playerid``` - идентификатор игрока
- ```captchaid``` - идентификатор константы
- ```resualt``` - ```true```, игрок нажал на правильную цифру, если ```false```, игрок нажал на неправильную цифру

---
### Пример
```pawn
enum
{
    CAPTCHA_TEST
}

CMD:test(playerid)
{
    captcha_ShowPlayer(playerid, CAPTCHA_TEST);
    return 1;

}

public OnPlayerInputCaptcha(playerid, captchaid, bool: resualt)
{
    switch (captchaid)
    {
        case CAPTCHA_TEST:
        {
            if (resualt == true)
            {
                SendClientMessage(playerid, -1, !"Игрок нажал на правильную цифру");
            }
            else
            {
                SendClientMessage(playerid, -1, !"Игрок нажал на неправильную цифру");
            }
        }
    }
    return 1;
}
```
