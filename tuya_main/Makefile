include $(TOPDIR)/rules.mk

PKG_NAME:=tuya_main
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/tuya_main
	CATEGORY:=Base system
	TITLE:=tuya_main
	DEPENDS:=+tuya_sdk +libubus +libubox +libblobmsg-json 
endef

define Package/tuya_main/description
	Tuya sdk example program
endef

define Package/tuya_main/install
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tuya_main $(1)/usr/bin
	$(INSTALL_BIN) ./files/tuya_main.init $(1)/etc/init.d/tuya_main
	$(INSTALL_CONF) ./files/tuya_main.config $(1)/etc/config/tuya_main
endef

$(eval $(call BuildPackage,tuya_main))
