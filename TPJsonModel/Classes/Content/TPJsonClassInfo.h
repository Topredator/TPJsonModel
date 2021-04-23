//
//  TPJsonClassInfo.h
//  TPJsonModel
//
//  Created by Topredator on 2021/4/23.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Type encoding's type.
 */
typedef NS_OPTIONS(NSUInteger, TPJsonEncodingType) {
    TPJsonEncodingTypeMask       = 0xFF, ///< mask of type value
    TPJsonEncodingTypeUnknown    = 0, ///< unknown
    TPJsonEncodingTypeVoid       = 1, ///< void
    TPJsonEncodingTypeBool       = 2, ///< bool
    TPJsonEncodingTypeInt8       = 3, ///< char / BOOL
    TPJsonEncodingTypeUInt8      = 4, ///< unsigned char
    TPJsonEncodingTypeInt16      = 5, ///< short
    TPJsonEncodingTypeUInt16     = 6, ///< unsigned short
    TPJsonEncodingTypeInt32      = 7, ///< int
    TPJsonEncodingTypeUInt32     = 8, ///< unsigned int
    TPJsonEncodingTypeInt64      = 9, ///< long long
    TPJsonEncodingTypeUInt64     = 10, ///< unsigned long long
    TPJsonEncodingTypeFloat      = 11, ///< float
    TPJsonEncodingTypeDouble     = 12, ///< double
    TPJsonEncodingTypeLongDouble = 13, ///< long double
    TPJsonEncodingTypeObject     = 14, ///< id
    TPJsonEncodingTypeClass      = 15, ///< Class
    TPJsonEncodingTypeSEL        = 16, ///< SEL
    TPJsonEncodingTypeBlock      = 17, ///< block
    TPJsonEncodingTypePointer    = 18, ///< void*
    TPJsonEncodingTypeStruct     = 19, ///< struct
    TPJsonEncodingTypeUnion      = 20, ///< union
    TPJsonEncodingTypeCString    = 21, ///< char*
    TPJsonEncodingTypeCArray     = 22, ///< char[10] (for example)
    
    TPJsonEncodingTypeQualifierMask   = 0xFF00,   ///< mask of qualifier
    TPJsonEncodingTypeQualifierConst  = 1 << 8,  ///< const
    TPJsonEncodingTypeQualifierIn     = 1 << 9,  ///< in
    TPJsonEncodingTypeQualifierInout  = 1 << 10, ///< inout
    TPJsonEncodingTypeQualifierOut    = 1 << 11, ///< out
    TPJsonEncodingTypeQualifierBycopy = 1 << 12, ///< bycopy
    TPJsonEncodingTypeQualifierByref  = 1 << 13, ///< byref
    TPJsonEncodingTypeQualifierOneway = 1 << 14, ///< oneway
    
    TPJsonEncodingTypePropertyMask         = 0xFF0000, ///< mask of property
    TPJsonEncodingTypePropertyReadonly     = 1 << 16, ///< readonly
    TPJsonEncodingTypePropertyCopy         = 1 << 17, ///< copy
    TPJsonEncodingTypePropertyRetain       = 1 << 18, ///< retain
    TPJsonEncodingTypePropertyNonatomic    = 1 << 19, ///< nonatomic
    TPJsonEncodingTypePropertyWeak         = 1 << 20, ///< weak
    TPJsonEncodingTypePropertyCustomGetter = 1 << 21, ///< getter=
    TPJsonEncodingTypePropertyCustomSetter = 1 << 22, ///< setter=
    TPJsonEncodingTypePropertyDynamic      = 1 << 23, ///< @dynamic
};

/**
 Get the type from a Type-Encoding string.
 @param typeEncoding  A Type-Encoding string.
 @return The encoding type.
 */
TPJsonEncodingType TPJsonEncodingGetType(const char *typeEncoding);


/**
 Instance variable information.
 */
@interface TPJsonClassIvarInfo : NSObject
@property (nonatomic, assign, readonly) Ivar ivar;              ///< ivar opaque struct
@property (nonatomic, strong, readonly) NSString *name;         ///< Ivar's name
@property (nonatomic, assign, readonly) ptrdiff_t offset;       ///< Ivar's offset
@property (nonatomic, strong, readonly) NSString *typeEncoding; ///< Ivar's type encoding
@property (nonatomic, assign, readonly) TPJsonEncodingType type;    ///< Ivar's type

/**
 Creates and returns an ivar info object.
 
 @param ivar ivar opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithIvar:(Ivar)ivar;
@end


/**
 Method information.
 */
@interface TPJsonClassMethodInfo : NSObject
@property (nonatomic, assign, readonly) Method method;                  ///< method opaque struct
@property (nonatomic, strong, readonly) NSString *name;                 ///< method name
@property (nonatomic, assign, readonly) SEL sel;                        ///< method's selector
@property (nonatomic, assign, readonly) IMP imp;                        ///< method's implementation
@property (nonatomic, strong, readonly) NSString *typeEncoding;         ///< method's parameter and return types
@property (nonatomic, strong, readonly) NSString *returnTypeEncoding;   ///< return value's type
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *argumentTypeEncodings; ///< array of arguments' type

/**
 Creates and returns a method info object.
 
 @param method method opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithMethod:(Method)method;
@end


/**
 Property information.
 */
@interface TPJsonClassPropertyInfo : NSObject
@property (nonatomic, assign, readonly) objc_property_t property; ///< property's opaque struct
@property (nonatomic, strong, readonly) NSString *name;           ///< property's name
@property (nonatomic, assign, readonly) TPJsonEncodingType type;      ///< property's type
@property (nonatomic, strong, readonly) NSString *typeEncoding;   ///< property's encoding value
@property (nonatomic, strong, readonly) NSString *ivarName;       ///< property's ivar name
@property (nullable, nonatomic, assign, readonly) Class cls;      ///< may be nil
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *protocols; ///< may nil
@property (nonatomic, assign, readonly) SEL getter;               ///< getter (nonnull)
@property (nonatomic, assign, readonly) SEL setter;               ///< setter (nonnull)

/**
 Creates and returns a property info object.
 
 @param property property opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithProperty:(objc_property_t)property;
@end


/**
 Class information for a class.
 */
@interface TPJsonClassInfo : NSObject
@property (nonatomic, assign, readonly) Class cls; ///< class object
@property (nullable, nonatomic, assign, readonly) Class superCls; ///< super class object
@property (nullable, nonatomic, assign, readonly) Class metaCls;  ///< class's meta class object
@property (nonatomic, readonly) BOOL isMeta; ///< whether this class is meta class
@property (nonatomic, strong, readonly) NSString *name; ///< class name
@property (nullable, nonatomic, strong, readonly) TPJsonClassInfo *superClassInfo; ///< super class's class info
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, TPJsonClassIvarInfo *> *ivarInfos; ///< ivars
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, TPJsonClassMethodInfo *> *methodInfos; ///< methods
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, TPJsonClassPropertyInfo *> *propertyInfos; ///< properties

/**
 If the class is changed (for example: you add a method to this class with
 'class_addMethod()'), you should call this method to refresh the class info cache.
 
 After called this method, `needUpdate` will returns `YES`, and you should call
 'classInfoWithClass' or 'classInfoWithClassName' to get the updated class info.
 */
- (void)setNeedUpdate;

/**
 If this method returns `YES`, you should stop using this instance and call
 `classInfoWithClass` or `classInfoWithClassName` to get the updated class info.
 
 @return Whether this class info need update.
 */
- (BOOL)needUpdate;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param cls A class.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClass:(Class)cls;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param className A class name.
 @return A class info, or nil if an error occurs.
 */
+ (nullable instancetype)classInfoWithClassName:(NSString *)className;

@end

NS_ASSUME_NONNULL_END
