//
//  PredictIO.h
//  predict.io-sdk
//
//  Created by Zee on 28/02/2013.
//  Copyright (c) 2016 predict.io by ParkTAG GmbH. All rights reserved.
//  Version 3.0

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/*
 * PredictIOStatus
 * Discussion: Represents the current predict.io state.
 */
typedef NS_ENUM(int, PredictIOStatus) {
    // predict.io is in a working/active state
    PredictIOStatusActive = 0,

    // predict.io not in a working state as the location services are disabled
    PredictIOStatusLocationServicesDisabled,

    // predict.io has not been authorized by user to use location services at any time (kCLAuthorizationStatusAuthorizedAlways)
    PredictIOStatusInsufficientPermission,

    // predict.io has not been started. It is in inactive state.
    PredictIOStatusInActive
};

/*
 * TransportationMode
 * Discussion: Represents the vehicle transportation mode, determined by the predict.io
 */
typedef NS_ENUM(int, TransportationMode) {
    // current transportation mode is Undetermined
    TransportationModeUndetermined = 0,

    // current transportation mode is Car
    TransportationModeCar,

    // current transportation mode is other than Car
    TransportationModeOther
};

/*
 * LogLevel
 * Discussion: Represents the current predict.io logger state.
 */
typedef NS_ENUM(int, LogLevel)  {
    LogLevelNone = 0, LogLevelDebug
};

@protocol PredictIODelegate;

@interface PredictIO : NSObject

@property (nonatomic, weak) id <PredictIODelegate> delegate;
@property (nonatomic, strong) NSString *apiKey;
@property (nonatomic, strong) NSString *version;

+ (PredictIO *)sharedInstance;

/* This starts predict.io if delegate and API-Key are set, otherwise it returns an Error
 * @param handler: The argument to the completion handler block is an error object that contains
 * the description of the error. If predict.io is started successfully, then error object is nil
 */
- (void)startWithCompletionHandler:(void(^)(NSError *error))handler;

/*
 * Stop predict.io
 */
- (void)stop;

/*
 * Manually activate GPS for short period of time
 */
- (void)kickStartGPS;

/* This method returns the status of predict.io, PredictIOStatus i.e. if it is active or not
 * Discussion: PredictIOStatus represents the current predict.io state
 * PredictIOStatusActive: predict.io is in a working, active state
 * PredictIOStatusLocationServicesDisabled: predict.io is not in a working state as the location services are disabled
 * PredictIOStatusInsufficientPermission: predict.io is not in a working state as the permissions to use location services are not provided by the user
 * PredictIOStatusInActive: predict.io has not been started. It is in inactive state
 */
- (PredictIOStatus)status;

/*
 * An alphanumeric string that uniquely identifies a device to the predict.io
 */
- (NSString *)deviceIdentifier;

@end

@protocol PredictIODelegate <NSObject>

@optional

/* This method is invoked when predict.io detects that the user is about to depart
 * from his location and is approaching to his vehicle
 * @param departureLocation: The Location from where the user departed
 * @param transportationMode: Mode of transportation
 */
- (void)departingFromLocation:(CLLocation *)departureLocation
           transportationMode:(TransportationMode)transportationMode;

/* This method is invoked when predict.io detects that the user has just departed
 * from his location and have started a new trip
 * @param departureLocation: The Location from where the user departed
 * @param departureTime: Start time of the trip
 * @param transportationMode: Mode of transportation
 */
- (void)departedLocation:(CLLocation *)departureLocation
           departureTime:(NSDate *)departureTime
      transportationMode:(TransportationMode)transportationMode;

/* This method is invoked when predict.io is unable to validate the last departure event.
 * This can be due to invalid data received from sensors or the trip amplitude.
 * i.e. If the trip takes less than 5 minutes or the distance travelled is less than 3km
 */
- (void)departureCanceled;

/* This method is invoked when predict.io suspects that the user has just arrived
 * at his location and have ended a trip
 * Most of the time it is followed by a confirmed arrivedAtLocation event
 * If you need only confirmed arrival events, use arrivedAtLocation method (below) instead
 * @param departureLocation: The Location from where the user departed
 * @param arrivalLocation: The Location where the user arrived and ended the trip
 * @param departureTime: Start time of trip
 * @param arrivalTime: Stop time of trip
 * @param transportationMode: Mode of transportation
 */
- (void)arrivalSuspectedFromLocation:(CLLocation *)departureLocation
                     arrivalLocation:(CLLocation *)arrivalLocation
                       departureTime:(NSDate *)departureTime
                         arrivalTime:(NSDate *)arrivalTime
                  transportationMode:(TransportationMode)transportationMode;

/* This method is invoked when predict.io detects that the user has just arrived at destination
 * @param arrivalLocation: The Location where the user arrived and ended a trip
 * @param departureLocation: The Location from where the user departed
 * @param departureTime: Start time of trip
 * @param arrivalTime: Stop time of trip
 * @param transportationMode: Mode of transportation
 */
- (void)arrivedAtLocation:(CLLocation *)arrivalLocation
        departureLocation:(CLLocation *)departureLocation
              arrivalTime:(NSDate *)arrivalTime
            departureTime:(NSDate *)departureTime
       transportationMode:(TransportationMode)transportationMode;

/* This method is invoked when predict.io detects that the user is searching for a
 * parking space at a specific location
 * @param location: The Location where predict.io identifies that user is searching for a parking space
 */
- (void)searchingInPerimeter:(CLLocation *)searchingLocation;

/* This is invoked when new location information is received from location services
 * Implemented this method if you need raw GPS data, instead of creating new location manager
 * Since, it is not recommended to use multiple location managers in a single app
 * @param location: New location
 */
- (void)didUpdateLocation:(CLLocation *)location;

@end

/*
 * These notifications are sent out after the equivalent delegate message is called
 */
FOUNDATION_EXPORT NSString *const PIODepartingNotification;
FOUNDATION_EXPORT NSString *const PIODepartedNotification;
FOUNDATION_EXPORT NSString *const PIODepartureCanceledNotification;
FOUNDATION_EXPORT NSString *const PIOArrivalSuspectedNotification;
FOUNDATION_EXPORT NSString *const PIOArrivedNotification;
FOUNDATION_EXPORT NSString *const PIOSearchingParkingNotification;
