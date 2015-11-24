/* Utils.h
 *
 * Copyright (C) 2012  Belledonne Comunications, Grenoble, France
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#import "LinphoneManager.h"

@interface LinphoneLogger : NSObject {

}

+ (void)log:(OrtpLogLevel)severity file:(const char *)file line:(int)line format:(NSString *)format, ...;
void linphone_iphone_log_handler(int lev, const char *fmt, va_list args);
@end

@interface LinphoneUtils : NSObject

+ (BOOL)findAndResignFirstResponder:(UIView*)view;
+ (void)adjustFontSize:(UIView*)view mult:(float)mult;
+ (void)buttonFixStates:(UIButton*)button;
+ (void)buttonMultiViewAddAttributes:(NSMutableDictionary*)attributes button:(UIButton*)button;
+ (void)buttonMultiViewApplyAttributes:(NSDictionary*)attributes button:(UIButton*)button;
+ (NSString *)deviceName;

typedef enum {
	LinphoneDateHistoryList,
	LinphoneDateHistoryDetails,
	LinphoneDateChatList,
	LinphoneDateChatBubble,
} LinphoneDateFormat;

+ (NSString *)timeToString:(time_t)time withFormat:(LinphoneDateFormat)format;

+ (BOOL)hasSelfAvatar;
+ (UIImage *)selfAvatar;

+ (NSString *)durationToString:(int)duration;

@end

@interface NSNumber (HumanReadableSize)

- (NSString*)toHumanReadableSize;

@end

#define LOGV(level, ...) [LinphoneLogger log:level file:__FILE__ line:__LINE__ format:__VA_ARGS__]
#define LOGD(...) LOGV(ORTP_DEBUG, __VA_ARGS__)
#define LOGI(...) LOGV(ORTP_MESSAGE, __VA_ARGS__)
#define LOGW(...) LOGV(ORTP_WARNING, __VA_ARGS__)
#define LOGE(...) LOGV(ORTP_ERROR, __VA_ARGS__)
#define LOGF(...) LOGV(ORTP_FATAL, __VA_ARGS__)

@interface NSString(md5)

- (NSString *)md5;

@end

@interface UIImage (squareCrop)

- (UIImage *)squareCrop;

@end

@interface ContactDisplay : NSObject
+ (void)setDisplayNameLabel:(UILabel *)label forContact:(ABRecordRef)contact;
+ (void)setDisplayNameLabel:(UILabel *)label forAddress:(const LinphoneAddress *)addr;
@end

#import <UIKit/UIColor.h>
#import <UIKit/UIKit.h>

#define LINPHONE_MAIN_COLOR [UIColor colorWithRed:207.0f / 255.0f green:76.0f / 255.0f blue:41.0f / 255.0f alpha:1.0f]
#define LINPHONE_SETTINGS_BG_IOS7 [UIColor colorWithRed:164 / 255. green:175 / 255. blue:183 / 255. alpha:1.0]

@interface UIColor (LightAndDark)

- (UIColor *)adjustHue:(float)hm saturation:(float)sm brightness:(float)bm alpha:(float)am;

- (UIColor *)lumColor:(float)mult;

- (UIColor *)lighterColor;

- (UIColor *)darkerColor;

@end

@interface UIImage (ForceDecode)

+ (UIImage *)decodedImageWithImage:(UIImage *)image;

@end

/* Use that macro when you want to invoke a custom initialisation method on your class,
 whatever is using it (xib, source code, etc., tableview cell) */
#define INIT_WITH_COMMON                                                                                               \
	-(instancetype)init {                                                                                              \
		self = [super init];                                                                                           \
		[self commonInit];                                                                                             \
		return self;                                                                                                   \
	}                                                                                                                  \
	-(instancetype)initWithCoder : (NSCoder *)aDecoder {                                                               \
		self = [super initWithCoder:aDecoder];                                                                         \
		[self commonInit];                                                                                             \
		return self;                                                                                                   \
	}                                                                                                                  \
	-(instancetype)initWithFrame : (CGRect)frame {                                                                     \
		self = [super initWithFrame:frame];                                                                            \
		[self commonInit];                                                                                             \
		return self;                                                                                                   \
	}                                                                                                                  \
	-(void)commonInit