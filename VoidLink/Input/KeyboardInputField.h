//
//  KeyboardInputField.h
//  Moonlight
//
//  Created by Cameron Gutman on 12/2/22.
//  Copyright © 2022 Moonlight Game Streaming Project. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface KeyboardInputField : UITextField

@property (nonatomic, copy, nullable) void (^backspaceHandler)(void);
// Backspace pressed while the field is empty: UIKit reports no change for it.
@property (nonatomic, copy, nullable) void (^emptyBackspaceHandler)(void);

@end

NS_ASSUME_NONNULL_END
