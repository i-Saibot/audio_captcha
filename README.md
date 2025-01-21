# Audio Captcha
##### <https://www.youtube.com/watch?v=aGhHXSs0WHw>
---

> Show captcha for player:
```pawn
captcha_ShowPlayer(playerid, captchaid)
```
- `playerid` - player identifier  
- `captchaid` - constant identifier


> Callback for check
```pawn
OnPlayerInputCaptcha(playerid, captchaid, bool: correct_number)
```
- `playerid` - player identifier  
- `captchaid` - constant identifier  
- `result` - `true` if the player clicked the correct number, `false` if the player clicked the wrong number

---
> Example
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

public OnPlayerInputCaptcha(playerid, captchaid, bool:result)
{
    switch (captchaid)
    {
        case CAPTCHA_TEST:
        {
            if (result == true)
            {
                SendClientMessage(playerid, -1, !"Ok");
            }
            else
            {
                SendClientMessage(playerid, -1, !"Wrong");
            }
        }
    }
    return 1;
}
```
