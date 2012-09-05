-- Copyright (c) 2012 by Christian Wiese <chris@opensde.org>
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
-- Physical Volume handling
--

object "PV" {
	userdata_type = 'simple',
	c_source [[
typedef pv_t PV;
]],
	constructor "from_name" {
		c_call "PV" "lvm_pv_from_name" {
			"VG", "vg",
			"const char *", "name"
		},
	},
	constructor "from_uuid" {
		c_call "PV" "lvm_pv_from_uuid" {
			"VG", "vg",
			"const char *", "uuid"
		},
	},
	method "get_uuid" {
		c_method_call "const char *" "lvm_pv_get_uuid" {}
	},
	method "get_name" {
		c_method_call "const char *" "lvm_pv_get_name" {}
	},
	method "get_mda_count" {
		c_method_call "uint64_t" "lvm_pv_get_mda_count" {}
	},
	method "get_dev_size" {
		c_method_call "uint64_t" "lvm_pv_get_dev_size" {}
	},
	method "get_size" {
		c_method_call "uint64_t" "lvm_pv_get_size" {}
	},
	method "get_free" {
		c_method_call "uint64_t" "lvm_pv_get_free" {}
	},

	--
	-- TODO: struct lvm_property_value lvm_pv_get_property(const pv_t pv, const char *name);
	--

	--
	-- TODO: struct lvm_property_value lvm_pvseg_get_property(const pvseg_t pvseg,
        --                                         const char *name);

	--
	-- TODO: struct dm_list *lvm_pv_list_pvsegs(pv_t pv);
	--
}
