//
//  MRDLNA.h
//  MRDLNA
//
//  Created by MccRee on 2018/5/4.
//

#import <Foundation/Foundation.h>
#import "CLUPnP.h"
#import "CLUPnPDevice.h"

typedef NS_ENUM(NSUInteger, DLNAStatus) {
    DLNAStatusPlay = 1,
    DLNAStatusPause,
    DLNAStatusStop,
    DLNAStatusBuffer,
    DLNAStatusError,
};

@protocol DLNADelegate <NSObject>

@optional
/**
 DLNA局域网搜索设备结果
 @param devicesArray <CLUPnPDevice *> 搜索到的设备
 */
- (void)searchDLNAResult:(NSArray *)devicesArray;


/**
 投屏成功开始播放
 */
- (void)dlnaStartPlay;


- (void)dlnaStatusChange:(DLNAStatus)status;

- (void)dlnaSeekResponse;

- (void)dlnaPreviousResponse;

- (void)dlnaNextResponse;

- (void)dlnaSetVolumeResponse;

- (void)dlnaSetNextAVTransportURIResponse;

- (void)dlnaGetVolumeResponse:(NSString *)volume;

- (void)dlnaGetPositionInfoResponse:(CLUPnPAVPositionInfo *)info;

- (void)dlnaGetTransportInfoResponse:(CLUPnPTransportInfo *)info;

@end

@interface MRDLNA : NSObject

@property(nonatomic,weak)id<DLNADelegate> delegate;

@property(nonatomic, strong) CLUPnPDevice *device;

@property(nonatomic,copy) NSString *playUrl;

@property(nonatomic,assign) NSInteger searchTime;

/**
 单例
 */
+(instancetype)sharedMRDLNAManager;

/**
 搜设备
 */
- (void)startSearch;

- (void)stopSearch;

/**
 DLNA投屏
 */
- (void)startDLNA;
/**
 DLNA投屏(首先停止)---投屏不了可以使用这个方法
 ** 【流程: 停止 ->设置代理 ->设置Url -> 播放】
 */
- (void)startDLNAAfterStop;

/**
 退出DLNA
 */
- (void)endDLNA;

/**
 播放
 */
- (void)dlnaPlay;

/**
 暂停
 */
- (void)dlnaPause;

/**
 设置音量 volume建议传0-100之间字符串
 */
- (void)volumeChanged:(NSString *)volume;

/**
 设置播放进度 seek单位是秒
 */
- (void)seekChanged:(NSInteger)seek;

/**
 播放切集
 */
- (void)playTheURL:(NSString *)url;

/**
 获取播放进度,可通过协议回调使用
 */
- (void)getPositionInfo;

/**
 获取播放状态,可通过协议回调使用
 */
- (void)getTransportInfo;

/**
 获取音频,可通过协议回调使用
 */
- (void)getVolume;

@end
