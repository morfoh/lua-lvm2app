--
-- Example: pvcreate [[PhysicalVolume] [PhysicalVolume]]
--

-- load common helper functions module
require("cmdcommon")

local lvm2app = require("lvm2app")

-- check if there is at least one argument or exit with
-- the same exit code like the real 'pvcreate' command
if #arg < 1 then
	exit_error(3, "Please enter a physical volume path")
end

-- creating LVM object handle
local LVM = lvm2app.LVM()

-- error state
local error = false

-- iterate through the devices in the argument table 
for _, device in ipairs(arg) do
	local success, errmsg = LVM:pv_create(device)
	if not success then
		-- just continue with the next device but change error state
		error = true
		status(errmsg)
	else
		status("Physical volume" .. " \"" .. device .. "\" " .. "successfully created")
	end
end

-- release LVM object handle
LVM:quit()

-- on error exit with the same code like the real 'pvcreate' command
if error then
	os.exit(5)
end
