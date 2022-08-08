/*

	Author: Saibot

	Script: Audio Captcha

*/

#if defined audio_captcha
	#endinput
#endif
#define audio_captcha


const
	MAX_TD_CAPTCHA = 11,
	MAX_LENGHT_LINKS = 90
;

static enum e_captcha
{
	captcha_number,
	captcha_links[MAX_LENGHT_LINKS]
}
static const links_for_captcha[][e_captcha] =
{
	{1, "https://download1083.mediafire.com/z3d6u2l9a5lg/5kou9m35wv2qc37/asdfcxzvasdaewq.mp3"},
	{2, "https://download1498.mediafire.com/tloqkqhuyqmg/3axdz5f017nj9c1/asdgghdfkjghergih.mp3"},
	{3, "https://download946.mediafire.com/cr40y43wzccg/a7rbyo1wq6fgvso/asdfertggvdf.mp3"},

	{1, "https://download1321.mediafire.com/cqp8ntsfj92g/wvitnmfti0sooe1/asdbverthbbnrhh.mp3"},
	{2, "https://download1515.mediafire.com/teabrkux38eg/qtrjzgm3pcdt25p/asdergbrtghgffn.mp3"},
	{3, "https://download1584.mediafire.com/fbrp5g6g24sg/7ue1xheifabo47n/asdbgegbnnfgjd.mp3"},

	{1, "https://download1580.mediafire.com/c7f0qpdce8yg/sc8eot9yaewfu3u/asderhgbnrtjert.mp3"},
	{2, "https://download848.mediafire.com/hgn08uzpqtog/zy43pqm2oj4hl7r/asdergbgfrjhrth.mp3"},
	{3, "https://download1647.mediafire.com/0tzb074cemlg/2iruarvw1np309t/asdergbrtjhgfjrjrjgn.mp3"},

	{1, "https://download1482.mediafire.com/4nq12c22pqug/ei3xnck9f6jdm1v/asdetwgbdfgdf.mp3"},
	{2, "https://download1502.mediafire.com/01dv9txr10gg/cg612jch6k593ly/asdewrgbvhn.mp3"},
	{3, "https://download1655.mediafire.com/vp5mmh7b4xjg/y1mhxvk8fb9uxqk/asdfvdsfgqdffad.mp3"}
};

static enum e_captcha_player_info
{
	captcha_id,
	bool: captcha_is_show,
	captcha_correct_answer,
	PlayerText: captcha_texdtraw[MAX_TD_CAPTCHA]
}
static
	captcha_PlayerInfo[MAX_PLAYERS][e_captcha_player_info],
	captcha_DefaultValue[e_captcha_player_info] =
	{
		0,
		false,
		0,
		PlayerText:0xFFFF
	}
;


///////////////////////////////////

forward OnPlayerInputCaptcha(playerid, captchaid, bool: resualt);

///////////////////////////////////



public OnPlayerDisconnect(playerid, reason)
{
	captcha_DestroyTextdraw(playerid);

#if defined captcha_OnPlayerDisconnect
	return captcha_OnPlayerDisconnect(playerid, reason);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect captcha_OnPlayerDisconnect
#if defined    captcha_OnPlayerDisconnect
	forward captcha_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerSpawn(playerid)
{
	captcha_DestroyTextdraw(playerid);

#if defined captcha_OnPlayerSpawn
		return captcha_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn captcha_OnPlayerSpawn
#if defined captcha_OnPlayerSpawn
	forward captcha_OnPlayerSpawn(playerid);
#endif

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (captcha_PlayerInfo[playerid][captcha_is_show] == true)
	{
		for (new i = 4; i < 7; i++)
		{
			if (playertextid == captcha_PlayerInfo[playerid][captcha_texdtraw][i])
			{
				new answer = captcha_PlayerInfo[playerid][captcha_correct_answer];

				CallRemoteFunction(
					"OnPlayerInputCaptcha",
					"ddd",
					playerid,
					captcha_PlayerInfo[playerid][captcha_id],
					answer == i - 3 ? true : false
				);
				captcha_DestroyTextdraw(playerid);
				return 1;
			}
		}
	}
#if defined captcha_OnPlayerClickPlayerTD
	return captcha_OnPlayerClickPlayerTD(playerid, playertextid);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw captcha_OnPlayerClickPlayerTD
#if defined    captcha_OnPlayerClickPlayerTD
	forward captcha_OnPlayerClickPlayerTD(playerid, PlayerText:playertextid);
#endif


public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == Text: INVALID_TEXT_DRAW)
	{
		captcha_DestroyTextdraw(playerid);
	}
#if defined captcha_OnPlayerClickTextDraw
	return captcha_OnPlayerClickTextDraw(playerid, Text:clickedid);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw captcha_OnPlayerClickTextDraw
#if defined    captcha_OnPlayerClickTextDraw
	forward captcha_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif


stock captcha_ShowPlayer(const playerid, captchaid)
{
	if (captcha_PlayerInfo[playerid][captcha_is_show] == false)
	{
		captcha_CreateTextdraw(playerid);

		new question = random(sizeof(links_for_captcha));

		captcha_PlayerInfo[playerid][captcha_correct_answer] = links_for_captcha[question][captcha_number];

		PlayAudioStreamForPlayer(
			playerid,
			links_for_captcha[question][captcha_links]
		);
		captcha_PlayerInfo[playerid][captcha_id] = captchaid;
		captcha_PlayerInfo[playerid][captcha_is_show] = true;

		for (new i; i < MAX_TD_CAPTCHA; i++)
		{
			PlayerTextDrawShow(
				playerid,
				captcha_PlayerInfo[playerid][captcha_texdtraw][i]
			);
		}
		SelectTextDraw(playerid, 0xFFFFFF);
	}
}

static captcha_DestroyTextdraw(playerid)
{
	if (captcha_PlayerInfo[playerid][captcha_is_show] == true)
	{
		for (new i; i < MAX_TD_CAPTCHA; i++)
		{
			PlayerTextDrawDestroy(
				playerid,
				captcha_PlayerInfo[playerid][captcha_texdtraw][i]
			);
		}
		CancelSelectTextDraw(playerid);
		StopAudioStreamForPlayer(playerid);
	}
	captcha_PlayerInfo[playerid] = captcha_DefaultValue;
}

static stock captcha_CreateTextdraw(playerid)
{
	captcha_PlayerInfo[playerid][captcha_texdtraw][0] = CreatePlayerTextDraw(playerid, 268.3334, 173.9517, "LD_SPAC:white"); // пусто
	PlayerTextDrawTextSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][0], 104.0000, 66.0000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][0], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][0], 370480895);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][0], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][0], 4);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][0], 0);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][0], 0);

	captcha_PlayerInfo[playerid][captcha_texdtraw][1] = CreatePlayerTextDraw(playerid, 268.4333, 173.8074, "LD_SPAC:white"); // пусто
	PlayerTextDrawTextSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][1], 103.7899, 2.0000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][1], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][1], 791621631);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][1], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][1], 4);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][1], 0);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][1], 0);

	captcha_PlayerInfo[playerid][captcha_texdtraw][2] = CreatePlayerTextDraw(playerid, 268.3999, 238.0438, "LD_SPAC:white"); // пусто
	PlayerTextDrawTextSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][2], 103.7699, 2.0000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][2], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][2], 791621631);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][2], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][2], 4);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][2], 0);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][2], 0);

	captcha_PlayerInfo[playerid][captcha_texdtraw][3] = CreatePlayerTextDraw(playerid, 321.5668, 175.4224, "Audio_Captcha"); // пусто
	PlayerTextDrawLetterSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][3], 0.1896, 1.3137);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][3], 2);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][3], -1061109505);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][3], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][3], 2);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][3], 1);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][3], 0);

	captcha_PlayerInfo[playerid][captcha_texdtraw][4] = CreatePlayerTextDraw(playerid, 273.4668, 198.1780, "LD_SPAC:white"); // пусто
	PlayerTextDrawTextSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], 23.0000, 16.0000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], 791621631);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], 4);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], 0);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], 0);
	PlayerTextDrawSetSelectable(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][4], true);

	captcha_PlayerInfo[playerid][captcha_texdtraw][5] = CreatePlayerTextDraw(playerid, 308.7343, 198.0780, "LD_SPAC:white"); // пусто
	PlayerTextDrawTextSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], 23.0000, 16.0000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], 791621631);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], 4);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], 0);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], 0);
	PlayerTextDrawSetSelectable(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][5], true);

	captcha_PlayerInfo[playerid][captcha_texdtraw][6] = CreatePlayerTextDraw(playerid, 343.3364, 198.0780, "LD_SPAC:white"); // пусто
	PlayerTextDrawTextSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], 23.0000, 16.0000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], 791621631);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], 4);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], 0);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], 0);
	PlayerTextDrawSetSelectable(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][6], true);

	captcha_PlayerInfo[playerid][captcha_texdtraw][7] = CreatePlayerTextDraw(playerid, 281.1332, 198.8928, "1"); // пусто
	PlayerTextDrawLetterSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][7], 0.4000, 1.6000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][7], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][7], -1);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][7], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][7], 3);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][7], 1);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][7], 0);

	captcha_PlayerInfo[playerid][captcha_texdtraw][8] = CreatePlayerTextDraw(playerid, 316.4332, 198.4075, "2"); // пусто
	PlayerTextDrawLetterSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][8], 0.4000, 1.6000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][8], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][8], -1);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][8], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][8], 3);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][8], 1);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][8], 0);

	captcha_PlayerInfo[playerid][captcha_texdtraw][9] = CreatePlayerTextDraw(playerid, 351.5332, 198.3075, "3"); // пусто
	PlayerTextDrawLetterSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], 0.4000, 1.6000);
	PlayerTextDrawTextSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], 3.0000, 0.0000);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], 1);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], -1);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], 3);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], 1);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][9], 0);

	captcha_PlayerInfo[playerid][captcha_texdtraw][10] = CreatePlayerTextDraw(playerid, 321.4666, 223.3113, "select_the_desired_number"); // пусто
	PlayerTextDrawLetterSize(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][10], 0.1463, 1.1810);
	PlayerTextDrawAlignment(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][10], 2);
	PlayerTextDrawColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][10], -2139062017);
	PlayerTextDrawBackgroundColor(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][10], 255);
	PlayerTextDrawFont(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][10], 2);
	PlayerTextDrawSetProportional(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][10], 1);
	PlayerTextDrawSetShadow(playerid, captcha_PlayerInfo[playerid][captcha_texdtraw][10], 0);
}