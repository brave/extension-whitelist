/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
/* global describe, it, before */

const assert = require('assert')
const CEWParser = require('../build/Release/ew_node_addon').CEWParser

describe('Client populated from deserialized data', function() {
    before(function() {
        this.addon = new CEWParser()
        this.addon.addToBlacklist('mhjfbmdgcfjbbpaeojofohoefgiehjai')
        this.addon.addToBlacklist('mlklomjnahgiddgfdgjhibinlfibfffc')
        this.addon.addToWhitelist('ngicbhhaldfdgmjhilmnleppfpmkgbbk')
        this.data = this.addon.serialize()
        this.addon2 = new CEWParser()
        this.addon2.deserialize(this.data)
    })
    it('should match blacklisted ID mhjfbmdgcfjbbpaeojofohoefgiehjai', function() {
        assert(this.addon2.isBlacklisted('mhjfbmdgcfjbbpaeojofohoefgiehjai'))
    })
    it('should match blacklisted ID mlklomjnahgiddgfdgjhibinlfibfffc', function() {
        assert(this.addon2.isBlacklisted('mlklomjnahgiddgfdgjhibinlfibfffc'))
    })
    it('should match whitelisted ID ngicbhhaldfdgmjhilmnleppfpmkgbbk', function() {
        assert(this.addon2.isWhitelisted('ngicbhhaldfdgmjhilmnleppfpmkgbbk'))
    })
    it('should not match unknown blacklisted ID', function() {
        assert.equal(this.addon2.isBlacklisted('a'), false)
    })
    it('should not match unknown whitelisted ID', function() {
        assert.equal(this.addon2.isWhitelisted('b'), false)
    })
})
