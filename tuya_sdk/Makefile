include $(TOPDIR)/rules.mk

PKG_NAME:=tuya_sdk
PKG_RELEASE:=1
PKG_VERSION:=1.0.1
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tuya/tuya-iot-core-sdk.git
PKG_SOURCE_VERSION:=0208badefb2003d30e70b5b875395e3187c850d9

PKG_BUILD_DEPENDS:=USE_UCLIBC:argp-standalone USE_MUSL:argp-standalone

CMAKE_BINARY_SUBDIR:=build

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/tuya_sdk
	CATEGORY:=Base system
	TITLE:=tuya_sdk
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include $(1)/usr/lib 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/liblink_core.so $(1)/usr/lib 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/libmiddleware_implementation.so $(1)/usr/lib 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/libplatform_port.so $(1)/usr/lib 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/libutils_modules.so $(1)/usr/lib 
	$(CP) $(PKG_BUILD_DIR)/utils/*.h $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/interface/*.h $(1)/usr/include/
	$(CP) $(PKG_BUILD_DIR)/include/tuyalink_core.h $(1)/usr/include/
endef

define Package/tuya_sdk/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/liblink_core.so $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/libmiddleware_implementation.so $(1)/usr/lib 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/libplatform_port.so $(1)/usr/lib 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/libutils_modules.so $(1)/usr/lib 
endef

$(eval $(call BuildPackage,tuya_sdk))
