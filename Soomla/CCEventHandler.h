/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CCEventHandler__
#define __CCEventHandler__

#include "./domain/virtualCurrencies/CCVirtualCurrency.h"
#include "./domain/virtualGoods/CCVirtualGood.h"
#include "./domain/virtualGoods/CCEquippableVG.h"
#include "./domain/virtualGoods/CCUpgradeVG.h"

namespace soomla {
	/** \class CCEventHandler
		\brief An abstract class that defines the event handler.

		Create your own implementation of this class and pass it to
		CCSoomla::addEventHandler() to work with the events. Functions are
		called when their corresponding events are fired in the SOOMLA SDK.
	 */
    class CCEventHandler : public cocos2d::CCObject {
    public:
        virtual void onBillingNotSupported() = 0;
        virtual void onBillingSupported() = 0;
        virtual void onOpeningStore() = 0;
        virtual void onClosingStore() = 0;
        virtual void onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded)  = 0;
        virtual void onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded) = 0;
        virtual void onGoodEquipped(CCEquippableVG *equippableVG) = 0;
        virtual void onGoodUnEquipped(CCEquippableVG *equippableVG) = 0;
        virtual void onGoodUpgrade(CCVirtualGood *virtualGood, CCUpgradeVG *upgradeVG) = 0;
        virtual void onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        virtual void onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        virtual void onMarketPurchaseCancelled(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        virtual void onMarketPurchase(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        virtual void onMarketPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        virtual void onMarketRefund(CCPurchasableVirtualItem *purchasableVirtualItem) = 0;
        virtual void onRestoreTransactions(bool success) = 0;
        virtual void onRestoreTransactionsStarted() = 0;
        virtual void onUnexpectedErrorInStore() = 0;
	virtual void onStoreControllerInitialized() = 0;
    };
};

#endif /* defined(__CCEventHandler__) */
