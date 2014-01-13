-- Copyright (c) 2012-2014 by Christian Wiese <chris@opensde.org>
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

--
-- Logical Volume handling
--

object "LV" {
	userdata_type = 'simple',

	constructor "create_linear" {
		c_call "LV" "lvm_vg_create_lv_linear" {
			"VG", "vg",
			"const char *", "name",
			"uint64_t", "size"
		},
	},
	constructor "from_name" {
		c_call "LV" "lvm_lv_from_name" {
			"VG", "vg",
			"const char *", "name"
		},
	},
	constructor "from_uuid" {
		c_call "LV" "lvm_lv_from_uuid" {
			"VG", "vg",
			"const char *", "uuid"
		},
	},
	method "activate" {
		c_method_call "int" "lvm_lv_activate" {}
	},
	method "deactivate" {
		c_method_call "int" "lvm_lv_deactivate" {}
	},
	method "remove" {
		c_method_call "int" "lvm_vg_remove_lv" {}
	},
	method "get_uuid" {
		c_method_call "const char *" "lvm_lv_get_uuid" {}
	},
	method "get_name" {
		c_method_call "const char *" "lvm_lv_get_name" {}
	},
	method "get_size" {
		c_method_call "uint64_t" "lvm_lv_get_size" {}
	},

	--
	-- TODO: lvm_lv_get_property
	--

	--
	-- TODO: lvm_lvseg_get_property
	--

	method "is_active" {
		c_method_call "uint64_t" "lvm_lv_is_active" {}
	},
	method "is_suspended" {
		c_method_call "uint64_t" "lvm_lv_is_suspended" {}
	},
	method "add_tag" {
		c_method_call "int" "lvm_lv_add_tag" { "const char *", "tag" }
	},
	method "remove_tag" {
		c_method_call "int" "lvm_lv_remove_tag" { "const char *", "tag" }
	},

	--
	-- TODO: lvm_lv_get_tags
	--

	method "resize" {
		c_method_call "int" "lvm_lv_resize" { "uint64_t", "size" }
	},
}

