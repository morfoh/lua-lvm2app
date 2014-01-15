package.cpath = "../../build/?.so"

--
-- helper functions
--

-- print an error message and exit with the provided exitcode 
function exit_error(exitcode, errmsg)
	print("  " .. errmsg)
	os.exit(exitcode)
end

-- print a status message
function status(msg)
	print("  " .. msg)
end
