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
-- Volume Group handling
--

object "VG" {
	userdata_type = 'simple',

	constructor "open" {
		c_call "VG" "lvm_vg_open" {
			"LVM", "lvm_handle",
			"const char *", "vgname",
			"const char *", "mode",
			"uint32_t", "flags"
		},
	},
	constructor "create" {
		c_call "VG" "lvm_vg_create" {
			"LVM", "lvm_handle",
			"const char *", "vgname",
		},
	},
	destructor "close" {
		c_method_call "int" "lvm_vg_close" {},
	},

	--
	-- TODO: struct dm_list *lvm_vg_list_lvs(vg_t vg);
	--

	--
	-- TODO: struct dm_list *lvm_vg_list_pvs(vg_t vg);
	--

	method "write" {
		c_method_call "int" "lvm_vg_write" {}
	},
	method "remove" {
		c_method_call "int" "lvm_vg_remove" {}
	},
	method "extend" {
		c_method_call "int" "lvm_vg_extend" { "const char *", "device" }
	},
	method "reduce" {
		c_method_call "int" "lvm_vg_reduce" { "const char *", "device" }
	},
	method "add_tag" {
		c_method_call "int" "lvm_vg_add_tag" { "const char *", "tag" }
	},
	method "remove_tag" {
		c_method_call "int" "lvm_vg_remove_tag" { "const char *", "tag" }
	},
	method "set_extent_size" {
		c_method_call "int" "lvm_vg_set_extent_size" { "uint32_t", "new_size" }
	},
	method "is_clustered" {
		c_method_call "uint64_t" "lvm_vg_is_clustered" {}
	},
	method "is_exported" {
		c_method_call "uint64_t" "lvm_vg_is_exported" {}
	},
	method "is_partial" {
		c_method_call "uint64_t" "lvm_vg_is_partial" {}
	},
	method "get_seqno" {
		c_method_call "uint64_t" "lvm_vg_get_seqno" {}
	},
	method "get_uuid" {
		c_method_call "const char *" "lvm_vg_get_uuid" {}
	},
	method "get_name" {
		c_method_call "const char *" "lvm_vg_get_name" {}
	},
	method "get_size" {
		c_method_call "uint64_t" "lvm_vg_get_size" {}
	},
	method "get_free_size" {
		c_method_call "uint64_t" "lvm_vg_get_free_size" {}
	},
	method "get_extent_size" {
		c_method_call "uint64_t" "lvm_vg_get_extent_size" {}
	},
	method "get_extent_count" {
		c_method_call "uint64_t" "lvm_vg_get_extent_count" {}
	},
	method "get_free_extent_count" {
		c_method_call "uint64_t" "lvm_vg_get_free_extent_count" {}
	},
	method "get_pv_count" {
		c_method_call "uint64_t" "lvm_vg_get_pv_count" {}
	},
	method "get_max_pv" {
		c_method_call "uint64_t" "lvm_vg_get_max_pv" {}
	},
	method "get_max_lv" {
		c_method_call "uint64_t" "lvm_vg_get_max_lv" {}
	},

	--
	-- struct dm_list *lvm_vg_get_tags(const vg_t vg);
	--

	--
	-- struct lvm_property_value lvm_vg_get_property(const vg_t vg, const char *name);
	--

	--
	-- int lvm_vg_set_property(const vg_t vg, const char *name,
        --                struct lvm_property_value *value);
	--
}

