#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/modify/CCMenu.hpp>
#include <Geode/modify/CCLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/binding/PauseLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

#include <eclipse.ffmpeg-api/include/export.hpp>
#include <eclipse.ffmpeg-api/include/recorder.hpp>
#include <eclipse.ffmpeg-api/include/audio_mixer.hpp>
#include <eclipse.ffmpeg-api/include/render_settings.hpp>

using namespace geode::prelude;

class x {
public:
	void d(CCObject* sender) {
		log::info("{}", sender);
	}
};

/*
	My mod settings menu
	11/17/2024 - 11/20/2024
	Rest in peace

// Make menu
namespace modmenu {
	class infoPopup {
	public:
		void show(CCMenuItemSpriteExtra* sender) {
			FLAlertLayer::create(
				"RenderMod",    // title
				((CCString*) sender->getUserObject())->getCString(),  // content
				"OK"        // button
			)->show();
		}
	};

	#define getYPos(LINE) -200 + ((7 - LINE) * 25)

	static CCLabelBMFont* addText(CCMenu* menu, const char* texto, int line) {
		auto text = CCLabelBMFont::create(texto, "bigFont.fnt");
		text->setAnchorPoint(CCPoint(0, 0.5));
		text->setScale(0.6);
		text->setID("rendermod-text");
		menu->addChildAtPosition(text, Anchor::TopLeft, CCPoint(5, getYPos(line)), true);

		return text;
	}

	static CCMenuItemToggler* addCheckbox(CCMenu* menu, int xpos, int line) {
		auto checkbox = CCMenuItemToggler::create(
			CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"),
			CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
			nullptr,
			menu_selector(x::d)
		);
		checkbox->setID("rendermod-checkbox");
		checkbox->setScale(0.7);
		menu->addChildAtPosition(checkbox, Anchor::TopLeft, CCPoint(xpos + 25, getYPos(line) - 1));

		return checkbox;
	}

	static TextInput* addTextbox(CCMenu* menu, int xpos, int line, const char* filter, const char* placeholder) { // 356 is x size
		TextInput* textInput = TextInput::create((-20 + 356 - 2 - xpos) / 0.7, placeholder);
		textInput->setAnchorPoint(CCPoint(1, 0.5));
		textInput->ignoreAnchorPointForPosition(false);
		textInput->setID("rendermod-textbox");
		textInput->setScale(0.7);
		textInput->setFilter(filter);

		menu->addChildAtPosition(textInput, Anchor::TopRight, CCPoint(-10, getYPos(line) - 2), true);

		return textInput;
	}

	static CCMenuItemSpriteExtra* addInfoButton(CCMenu* menu, int xpos, int line, const char* popup) {
		auto info = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
		info->setScale(0.5);

		CCMenuItemSpriteExtra* btn = CCMenuItemSpriteExtra::create(
			info,
			menu,
			menu_selector(infoPopup::show)
		);

		btn->setID("rendermod-info-btn");

		btn->setUserObject(CCString::create(popup));
		menu->addChildAtPosition(btn, Anchor::TopLeft, CCPoint(xpos + 7, getYPos(line) + 14));

		return btn;
	}

	static void addMySettingsLayer() {
		// Make new layer
		GJDropDownLayer* settings = GJDropDownLayer::create("RenderMod");
		settings->setID("rendermod-dropdown");
		settings->setZOrder(15);

		// Get inner frame
		CCNode* innerFrame = settings->getChildByID("main-layer");
		GJListLayer* bg = (GJListLayer*)innerFrame->getChildByID("background");
		bg->setColor(ccColor3B(37, 107, 143));
		bg->setOpacity(0xff);

		// Add a menu so I can click this button
		auto menu = CCMenu::create();
		menu->setID("rendermod-menu");
		menu->setContentSize(CCSize(356, 220));
		menu->setPosition(CCPoint(62, 65));
		menu->setAnchorPoint(CCPoint(0, 0));
		innerFrame->addChild(menu);

		// SIZE: 356 x 220
		// BUTTON SIZE Y: 30
		// Add buttons

		/*
						 [ RENDER ]
			INCLUDE PROGRESS BAR             [x]
			RECORD GAME AUDIO                [x]
			VIDEO FPS ________
			FFMPEG ARGS ______
			RESOLUTION ______
			CODEC ______________________________

		!/

		auto renderbtn = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Render!", 1),
			innerFrame,
			menu_selector(x::d)
		);
		renderbtn->setID("rendermod-render-button");
		menu->addChildAtPosition(renderbtn, Anchor::Top, CCPoint(0, -20), true);

		auto t1 = addText(menu, "Include UI", 1); // Record gameplay or screen
		auto t2 = addText(menu, "Record game audio", 2); // Record live audio or put it in after
		auto t3 = addText(menu, "FPS", 3); // Game and video
		auto t4 = addText(menu, "Resolution", 4); // width x height
		auto t5 = addText(menu, "Extra args", 5); // all the other stuff

		auto c1 = addCheckbox(menu, t1->getScaledContentWidth(), 1);
		auto c2 = addCheckbox(menu, t2->getScaledContentWidth(), 2);

		addTextbox(menu, t3->getScaledContentWidth(), 3, "0.123456789", "60");
		addTextbox(menu, t4->getScaledContentWidth(), 4, "0x123456789", "width x height");
		addTextbox(menu, t5->getScaledContentWidth(), 5, "0.123456789-qwertyuiopasdfghjklzxcvbnm,./;'[]\\=|+-_)(*&^%$#@!~`}{\":?><", "Confused? Leave blank. (These are NOT FFmpeg args)");

		addInfoButton(menu, t1->getScaledContentWidth(), 1, "Records the percentage bar, pause button, and other UI elements.");
		addInfoButton(menu, t2->getScaledContentWidth(), 2, "Records the live game audio instead of adding the song after recording.");
		addInfoButton(menu, t5->getScaledContentWidth(), 5, "Read the mod description for documentation. These aren't FFmpeg args!");

		c1->toggle(Mod::get()->getSettingValue<bool>("includeUi"));
		c2->toggle(Mod::get()->getSettingValue<bool>("liveAudio"));

		CCScene::get()->addChild(settings);
		settings->enterLayer();
	}
}

*/

// Make and place the buttons
namespace funnyButtons {

	class onSettingsButtonPressed {
	public:
		void _(CCObject* sender) {
			openSettingsPopup(Mod::get());
			// modmenu::addMySettingsLayer();
		}
	};

	static CCMenuItemSpriteExtra* makeSettingsButton(cocos2d::CCNode* target) {
		auto btn = CCMenuItemSpriteExtra::create(
			CircleButtonSprite::createWithSpriteFrameName("edit_eeFABtn_001.png"),
			target,
			menu_selector(onSettingsButtonPressed::_)
		);

		btn->setID("rendermod-settings-btn");
		target->addChild(btn);
		target->updateLayout();

		return btn;
	}

	// Put settings button in places
	class $modify(MyPauseLayer, PauseLayer) {
		void customSetup() {

			PauseLayer::customSetup();

			auto leftButtons = this->getChildByID("left-button-menu");

			auto btn = makeSettingsButton(leftButtons);
		};
	};

	class $modify(MyMenuLayer, MenuLayer) {
		bool init() {

			if (!MenuLayer::init()) {
				return false;
			}

			auto sidebar = this->getChildByID("side-menu");

			makeSettingsButton(sidebar);

			return true;
		};
	};
}