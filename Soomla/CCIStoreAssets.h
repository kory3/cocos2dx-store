//
// Created by Fedor Shubin on 5/20/13.
//



#include "cocoa/CCArray.h"

#ifndef __CCIStoreAssets_H_
#define __CCIStoreAssets_H_

namespace soomla {
	/** \class CCIStoreAssets
		\brief An abstract class that defines the store assets.

		Implement this class to define your store's assets. See the wiki for
		information about the various VirtualGoods and how to define them.
	 */
    class CCIStoreAssets: public cocos2d::CCObject {
    public:
        virtual int getVersion() = 0;

		/**
		   This function should return a CCArray containing all of your game's
		   currencies.
		 */
        virtual cocos2d::CCArray *getCurrencies() = 0;

		/**
		   This function should return a CCArray containing all of your game's
		   goods.
		*/
        virtual cocos2d::CCArray *getGoods() = 0;

		/**
		   This function should return a CCArray containing all of your game's
		   currency packs.
		*/
        virtual cocos2d::CCArray *getCurrencyPacks() = 0;

		/**
		   This function should return a CCArray containing all of your game's
		   virtual categories.
		*/
        virtual cocos2d::CCArray *getCategories() = 0;

		/**
		   This function should return a CCArray containing all of your game's
		   non consumable items.
		*/
        virtual cocos2d::CCArray *getNonConsumableItems() = 0;
    };
};

#endif //__CCIStoreAssets_H_
