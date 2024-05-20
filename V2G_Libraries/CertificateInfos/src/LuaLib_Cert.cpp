/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    LuaLib_Cert.cpp
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!-------------------------------------------------------------------------->*/
#include <iostream>
#include <string>
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
}
#include "CertHelper.h"

static int l_getX509Infos(lua_State *L)
{
    size_t certSize;
    const char *cert = luaL_checklstring(L, 1, &certSize);

    std::string fullcert = "-----BEGIN CERTIFICATE-----\n";
    fullcert.append(cert);
    fullcert.append("\n-----END CERTIFICATE-----");

    X509CertInfos cInfo = get_cert_info(fullcert);

    lua_pushboolean(L, cInfo.valid);
    lua_pushstring(L, cInfo.subject.c_str());
    lua_pushstring(L, cInfo.issuer.c_str());
    lua_pushnumber(L, cInfo.version);
    lua_pushstring(L, cInfo.serial_number.c_str());
    lua_pushstring(L, cInfo.time_not_before.c_str());
    lua_pushstring(L, cInfo.time_not_after.c_str());
    lua_pushstring(L, cInfo.sig_algorithm.c_str());
    lua_pushstring(L, cInfo.sig_value.c_str());
    lua_pushstring(L, cInfo.pubkey_algorithm.c_str());
    lua_pushstring(L, cInfo.spk_NIST_curve.c_str());
    lua_pushstring(L, cInfo.spk_pub.c_str());
    lua_pushstring(L, cInfo.v3ext_basic_constraint.c_str());
    lua_pushstring(L, cInfo.v3ext_basic_constraint_CA.c_str());
    lua_pushstring(L, cInfo.v3ext_key_usage.c_str());
    lua_pushstring(L, cInfo.v3ext_key_usage_critical.c_str());
    lua_pushstring(L, cInfo.v3ext_subjkey_id.c_str());
    lua_pushstring(L, cInfo.v3ext_subjkey_id_critical.c_str());

    return 18; // Note: the lua stack has only (at least) 20 free slots!
}

extern "C"
{
    int luaopen_v2gX509CertInfos(lua_State *L)
    {
        static const struct luaL_Reg X509CertInfos[] =
            {
                // function name, function reference
                {"getX509Infos", l_getX509Infos},
                {NULL, NULL}};
#if LUA_VERSION_NUM > 501
        luaL_newlib(L, X509CertInfos);
#else
        luaL_register(L, "X509CertInfos", X509CertInfos);
#endif
        return 1;
    }
}
