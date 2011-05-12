//
//  HTNotifier.h
//  HoptoadNotifier
//
//  Created by Caleb Davenport on 10/2/10.
//  Copyright 2010 GUI Cocoa, LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>

#import "HTNotifierDelegate.h"

// notifier version
extern NSString *HTNotifierVersion;

// internal
extern NSString *HTNotifierAlwaysSendKey;

/*
 
 use these variables in your alert title, alert body, and
 environment name to have their values replaced at runtime
 
 */
// bundle name of the app
extern NSString *HTNotifierBundleName;
// bundle version of the app
extern NSString *HTNotifierBundleVersion;

/*
 
 use these standard environment names to have default
 values provided to hoptoad
 
 */
extern NSString *HTNotifierDevelopmentEnvironment;
extern NSString *HTNotifierAdHocEnvironment;
extern NSString *HTNotifierAppStoreEnvironment;
extern NSString *HTNotifierReleaseEnvironment;

/*
 
 HTNotifier is the primary class of the notifer library
 
 start the notifier by calling
	startNotifierWithAPIKey:environmentName:
 
 access the shared instance by calling sharedNotifier
 
 */
@interface HTNotifier : NSObject {
@private
    NSMutableDictionary *_environmentInfo;
    NSString *_environmentName;
    NSString *_apiKey;
	id<HTNotifierDelegate> _delegate;
    BOOL _useSSL;
    
	SCNetworkReachabilityRef reachability;
}

// properties
@property (nonatomic, readonly) NSDictionary *environmentInfo;
@property (nonatomic, readonly) NSString *apiKey;
@property (nonatomic, readonly) NSString *environmentName;
@property (nonatomic, assign) id<HTNotifierDelegate> delegate;

/*
 
 control whether notices are posted using SSL. your account
 must support this feature
 
 default:NO
 
 */
@property (nonatomic, assign) BOOL useSSL;

/*
 
 this method is the entry point for the library. any code
 executed after this method call is monitored for crashes
 and signals
 
 the values for key and environment name must not be nil
 and must have a length greater than 0
 
 include any of the above constant strings in the
 enviromnent name to have the value replaced by the library
 
 */
+ (void)startNotifierWithAPIKey:(NSString *)key environmentName:(NSString *)name;

/*
 
 access the shared notifier object.
 
 if this is called before `startNotifierWithAPIKey:environmentName:`
 nil will be returned.
 
 */
+ (HTNotifier *)sharedNotifier;

/*
 
 writes a test notice to disk if one does not exist already
 
 */
- (void)writeTestNotice;

/*
 
 set environment info key/value pair
 
 passing nil as value will remove the value for the given key
 
 */
- (void)setEnvironmentValue:(NSString *)valueOrNil forKey:(NSString *)key;

/*
 
 get environment info value given a key
 
 */
- (NSString *)environmentValueForKey:(NSString *)key;

@end
