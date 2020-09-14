//
//  ATCocosGDPRListener.h
//  CocosDemo
//
//  Created by Topon on 2020/1/3.
//

#ifndef ATCocosGDPRListener_h
#define ATCocosGDPRListener_h
class ATCocosGDPRListener {
public:
    
    virtual void onGDPRDataConsentSet(int dataConsent) {};
    virtual void onPageLoadFail() {};
};

#endif /* ATCocosGDPRListener_h */
