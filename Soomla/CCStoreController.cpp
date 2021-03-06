//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCStoreController.h"
#include "CCSoomla.h"
#include "CCStoreUtils.h"
#include "CCSoomlaNdkBridge.h"
#include "data/CCStoreInfo.h"
#include "CCSoomlaError.h"

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;
	
    static CCStoreController *s_SharedStoreController = NULL;

    CCStoreController *CCStoreController::sharedStoreController() {
        return s_SharedStoreController;
    }

    void CCStoreController::createShared(CCIStoreAssets *storeAssets, CCDictionary *storeParams) {
        CCStoreController *ret = new CCStoreController();
        if (ret->init(storeAssets, storeParams)) {
            s_SharedStoreController = ret;
        } else {
            delete ret;
        }
    }

    CCStoreController::CCStoreController() {

    }

    CCStoreController::~CCStoreController() {

    }

    bool CCStoreController::init(CCIStoreAssets *storeAssets, CCDictionary *storeParams) {
        CCString *customSecret = dynamic_cast<CCString *>(storeParams->objectForKey("customSecret"));
        CCString *soomSec = dynamic_cast<CCString *>(storeParams->objectForKey("soomSec"));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CCString *androidPublicKey = dynamic_cast<CCString *>(storeParams->objectForKey("androidPublicKey"));
        CCBool *androidTestMode = dynamic_cast<CCBool *>(storeParams->objectForKey("androidTestMode"));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCBool *SSV = dynamic_cast<CCBool *>(storeParams->objectForKey("SSV"));
#endif

        if (customSecret == NULL) customSecret = CCString::create("");
        if (soomSec      == NULL) soomSec      = CCString::create("");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (androidPublicKey == NULL) androidPublicKey = CCString::create("");
        if (androidTestMode  == NULL) androidTestMode  = CCBool::create(false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (SSV == NULL) SSV = CCBool::create(false);
#endif

        // Redundancy checking
        CCDictElement* el = NULL;
        CCDICT_FOREACH(storeParams, el) {
            std::string key = el->getStrKey();
            if (!(
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                  key.compare("androidPublicKey") == 0 ||
                  key.compare("androidTestMode")  == 0 ||
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                  key.compare("SSV") == 0 ||
#endif
                  key.compare("customSecret") == 0 ||
                  key.compare("soomSec")      == 0 )) {
                CCString *message =
                    CCString::createWithFormat("WARNING!! Possible typo in member of storeParams: %s", key.c_str());
                CCStoreUtils::logError(TAG, message->getCString());
            }
        }

        
        if (customSecret->length() == 0 || soomSec->length() == 0) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX MISSING customSecret or soomSec !!! Stopping here !!");
            return false;
        }

        if (customSecret->compare(SOOMLA_ONLY_ONCE_DEFAULT) == 0 ||
            soomSec->compare(SOOMLA_ONLY_ONCE_DEFAULT) == 0) {

            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX You have to change customSecret and soomSec !!! Stopping here !!");
            return false;
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (androidPublicKey->length() == 0) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX MISSING publickKey !!! Stopping here !!");
            return false;
        }

        if (androidPublicKey->compare(SOOMLA_AND_PUB_KEY_DEFAULT) == 0) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX You have to change android publicKey !!! Stopping here !!");
            return false;
        }

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setAndroidPublicKey"), "method");
            params->setObject(androidPublicKey, "androidPublicKey");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }
#endif

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setSoomSec"), "method");
            params->setObject(soomSec, "soomSec");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setSSV"), "method");
            params->setObject(SSV, "ssv");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }
#endif
        
        CCStoreInfo::createShared(storeAssets);

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::init"), "method");
            params->setObject(customSecret, "customSecret");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            params->setObject(androidPublicKey, "androidPublicKey");
#endif
            CCSoomlaNdkBridge::callNative(params, NULL);
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setAndroidTestMode"), "method");
            params->setObject(androidTestMode, "testMode");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }
#endif
        return true;
    }

    void CCStoreController::buyMarketItem(const char *productId, CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::buyMarketItem"), "method");
        params->setObject(CCString::create(productId), "productId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    void CCStoreController::storeOpening() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::storeOpening"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    void CCStoreController::storeClosing() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::storeClosing"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    void CCStoreController::restoreTransactions() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::restoreTransactions"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    bool CCStoreController::transactionsAlreadyRestored() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::transactionsAlreadyRestored"), "method");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        return retValue->getValue();
    }
}
