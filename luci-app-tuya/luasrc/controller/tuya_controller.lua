module("luci.controller.tuya_controller", package.seeall)

function index()
	entry({"admin", "services", "tuya_model"}, cbi("tuya_model"), _("Tuya model"),105)
end
