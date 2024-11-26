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

static bool rendering = false;

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