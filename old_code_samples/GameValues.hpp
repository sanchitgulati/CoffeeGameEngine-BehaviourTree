#pragma once
#include <string>

namespace GameValues {
	using str = std::string;

	static str sfxBLOP = "sfx/blop.wav";
	static str sfxCLICK = "sfx/click.wav";
	static str MUSIC = "sfx/music.wav";
	static str sfxPLOB = "sfx/polb.wav";
	static str sfxSLIDE = "sfx/slide.wav";
	static str BG = "images/bg_ipad_landscape.png";
	static str BTN = "images/button.png";
	static str BTN_PRESSED = "images/button_pressed.png";
	static str FONT = "fonts/Roboto-Bold.ttf";
	static str TILE_BG = "images/GameTileBG_01.png";
	static str GAME_OVER_OVERLAY = "images/overlay_gameover_ipad.png";
	static  std::vector<std::string> GEMS_FILE_PATH = std::vector <std::string>{
		"images/pastry_cookie01_320.png",
			"images/pastry_cookie02_320.png",
			"images/pastry_croissant_320.png",
			"images/pastry_cupcake_320.png",
			"images/pastry_donut_320.png",
			"images/pastry_eclair_320.png",
			"images/pastry_macaroon_320.png",
			"images/pastry_pie_320.png",
			"images/pastry_poptart01_320.png",
			"images/pastry_poptart02_320.png",
			"images/pastry_starcookie01_320.png",
			"images/pastry_starcookie02_320.png"
	};
}
