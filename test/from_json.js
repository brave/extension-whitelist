/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
/* global describe, it, before */

const assert = require('assert')
const CEWParser = require('../build/Release/ew_node_addon').CEWParser

describe('Client populated from whitelist.json', function() {
    before(function() {
        this.addon = new CEWParser()
        fs = require('fs')
        data = fs.readFileSync('data/whitelist.json', 'utf8')
        blacklist = JSON.parse(String(data))['blacklist']
        for (var i in blacklist) {
            this.addon.addToBlacklist(blacklist[i]['id'])
        }
        whitelist = JSON.parse(String(data))['whitelist']
        for (var i in whitelist) {
            this.addon.addToWhitelist(whitelist[i]['id'])
        }
    })
    it('should match whitelisted ID mhjfbmdgcfjbbpaeojofohoefgiehjai', function() {
        assert(this.addon.isWhitelisted('mhjfbmdgcfjbbpaeojofohoefgiehjai'))
    })
    it('should match blacklisted ID mlklomjnahgiddgfdgjhibinlfibfffc', function() {
        assert(this.addon.isBlacklisted('mlklomjnahgiddgfdgjhibinlfibfffc'))
    })
    it('should match whitelisted ID ngicbhhaldfdgmjhilmnleppfpmkgbbk', function() {
        assert(this.addon.isWhitelisted('ngicbhhaldfdgmjhilmnleppfpmkgbbk'))
    })
    it('should not match unknown blacklisted ID', function() {
        assert.equal(this.addon.isBlacklisted('a'), false)
    })
    it('should not match unknown whitelisted ID', function() {
        assert.equal(this.addon.isWhitelisted('b'), false)
    })
})
