// Copyright © 2016 ABBI Ltd. <https://abbi.io> All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>
#import "WMCampaignInfo.h"

/**
 * Enum to Support Hybrid iOS apps (i.e. webview based apps)
 * Use - (void) start: (NSString*) appId withSecretKey: (NSString*) appSecretKey andApplicationType:(ABBIAppType) type;
 *
 */
typedef enum {ABBI_APP_NATIVE = 10, ABBI_APP_HYBRID = 11, ABBI_APP_COCOS2D = 12, ABBI_APP_UNITY = 13, ABBI_APP_MAX = 14} ABBIAppType;
typedef enum {GOAL = 1} EventType;

extern NSString *SDK_VERSION;

/**
 * Interface definition for a callback to be invoked in Campaign actions.
 */
@protocol WMCampaignInfoDelegate <NSObject>

/**
 * Called after campaign was dismissed.
 *
 * @param campaignInfo The dismissed campaign info.
 */
- (void)campaignDidDismiss:(WMCampaignInfo *)campaignInfo;

@end

/**
* ABBI class manages the execution of ABBI SDK.
* Navigate to https://console.mobile.walkme.com to Register/Login and Manage Your Promotions
* For support, drop us an email at support@walkme.com
*/
@interface ABBI : NSObject

@property (nonatomic,weak) id<WMCampaignInfoDelegate> campaignInfoDelegate;

/** 
 * Starts ABBI SDK.
 *
 * @param appId The Application Id provided by WalkMe
 * @param appSecretKey The Application Secret key provided by WalkMe
 * 
 * To get your Application Id and Application Secret key, login to WalkMe console at https://console.mobile.walkme.com
 * and click the settings icon near your Application Name. You can find more info here - https://walkme-mobile.zendesk.com/hc
 */
+ (void)start:(NSString *)appId withSecretKey:(NSString *)appSecretKey;

/**
 * Restarts a new SDK session
 *
 */
+ (void)restart;

/** 
 * Starts ABBI SDK - FOR HYBRID APPS ONLY!
 *
 * @param appId The Application Id provided by ABBI
 * @param appSecretKey The Application Secret key provided by ABBI
 * @param type The Application Type (i.e. ABBI_APP_HYBRID)
 *
 */
+ (void)start:(NSString *)appId withSecretKey:(NSString *)appSecretKey andApplicationType:(ABBIAppType)type;

/**
 * Sends a Goal to ABBI's Backend.
 * A Goal is a user action that can be used to target your users.
 *
 * Usage Example :@
 *
 * [ABBI sendGoal:@"Bought a blue sword" withProperites:nil]
 * [ABBI sendGoal:@"Bought a blue sword" withProperites:@{@"item_name", @"unlimited_calls"}]
 *
 * @param goalName the Goal name.
 * @param properties the Goal properties, key-value structured (if any).
 */
+ (void)sendGoal:(NSString *)goalName withProperites:(NSDictionary *)properties;

/**
 * Sets a user attribute
 *
 * @param key the attribute key
 * @param value the attribute value
 * 
 * @code
 * Usage Examples:
 * [ABBI setUserAttributeWithKey:@"isProUser" andValue:@YES];
 * [ABBI setUserAttributeWithKey:@"isLoggedIn" andValue:@(0)];
 */
+ (void)setUserAttributeWithKey:(NSString *)key andValue:(id)value;

/**
 * Sets multiple user attributes
 *
 * @param attributes the user attributes
 * 
 * @code
 * Usage Example:
 * [ABBI setUserAttributes:@{@"isProUser": @YES, @"isLoggedIn": @(0)}];
 */
+ (void)setUserAttributes:(NSDictionary<NSString*,id> *)attributes;

/**
 * Sets a private user attribute
 *
 * @param key the attribute key
 * @param value the attribute value
 *
 * @code
 * Usage Examples:
 * [ABBI setPrivateUserAttributeWithKey:@"gender" andValue:@"female"];
 * [ABBI setPrivateUserAttributeWithKey:@"balance" andValue:@(1000)];
 */
+ (void)setPrivateUserAttributeWithKey:(NSString *)key andValue:(id)value;

/**
 * Sets multiple private user attributes
 *
 * @param attributes the private user attributes
 *
 * @code
 * Usage Example:
 * [ABBI setPrivateUserAttributes:@{@"gender": @"female", @"balance": @(1000)}];
 */
+ (void)setPrivateUserAttributes:(NSDictionary<NSString*,id> *)attributes;

/**
 * Clears all private user attributes
 */
+ (void)clearPrivateUserAttributes;

/** 
 * Utility function for remote sessions with ABBI support team.
 *
 * @param n Will be given by ABBI support team when needed
 */
+ (void)setFlag:(int)n;

/**
 * Launches a campaign by trigger key
 * Once invoked, the method will show the campaign WITHOUT any of its segments (if defined)
 *
 * @code
 * Usage Example :
 * [ABBI trigger:@"Show How To Order Credit Card"];
 */
+ (void)trigger:(NSString *)trigger;

/**
 * Launches a campaign by trigger key after redirecting the user to the given deep link
 * Once invoked, the method will show the campaign WITHOUT any of its segments (if defined)
 *
 * @code
 * Usage Example :
 * [ABBI trigger:@"Show How To Order Credit Card" withDeepLink:@"myapp://main_screen"];
 */
+ (void)trigger:(NSString*)trigger withDeepLink:(NSString*)deepLink;

/**
 * Sets user id
 *
 * @param userId the user id as NSString
 *
 * @code
 * Usage Example:
 * [ABBI setUserID:@"myuserid"];
 */
+ (void)setUserID:(NSString*)userId;

/**
 * Register a delegate to campaign events
 *
 *@param delegate The delegate
 *
 */
+ (void)setCampaignInfoDelegate:(id<WMCampaignInfoDelegate>)delegate;

/**
 * Opens a URL
 *
 *@param url the URL that should be handled by the SDK
 *@param options the options received from the app delegate "application:openURL:options:" method
 *@return true if the SDK handled the openURL request successfully
 *
 */
+ (BOOL)openURL:(NSURL*)url options:(NSDictionary*)options;

@end
