map = Map("tuya_main", "Tuya model")

section = map:section(NamedSection, "tuya_sct", "tuya_main", "Tuya device configuration")

flag = section:option(Flag, "enable", "Enable daemon", "Enable daemon program")
text = section:option( Value, "text_deviceid", "Device ID")
text.maxlength = 25
text = section:option( Value, "text_productid", "Product ID")
text.maxlength = 25
text = section:option( Value, "text_devicesecret", "Device secret")
text.maxlength = 25

return map
