/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    LuaLib_V2G.cpp
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!--------------------------------------------------------------------------->*/
#include <string>
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <exi_error_codes.h>

#include "XmlValidator.h"
#include "Utils.h"
#include "Decoder.h"
#include "CertHelper.h"

static int l_getGnuTlsErrorDescription(lua_State *L)
{
    int error_code = luaL_checkinteger(L, 0);

    lua_pushstring(L, get_error_description(error_code).c_str());

    return 1;
}

static int l_getX509Infos(lua_State *L)
{
    size_t certSize;
    const char *cert = luaL_checklstring(L, 1, &certSize);

    std::string fullcert = "-----BEGIN CERTIFICATE-----\n";
    fullcert.append(cert);
    fullcert.append("\n-----END CERTIFICATE-----");

    X509CertInfos cInfo = get_cert_info(fullcert);

    lua_pushinteger(L, cInfo.result);
    lua_pushstring(L, cInfo.subject.c_str());
    lua_pushstring(L, cInfo.issuer.c_str());
    lua_pushinteger(L, cInfo.version);
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

    return 18;  // Note: the lua stack has only (at least) 20 free slots!
}

Decoder v2g_message_decoder;
XmlValidator v2g_message_validator;

static int l_decodeV2GExiAuto(lua_State *L)
{
    std::string exiIn = luaL_checkstring(L, 1);

    result_decode result = v2g_message_decoder.decode_message_auto_schema(exiIn);
    if (result.errn != EXI_ERROR__NO_ERROR)
    {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
        return 3;
    }
    else
    {
        lua_pushstring(L, result.decoded_xml.c_str());
        lua_pushstring(L, result.used_schema.c_str());
        lua_pushinteger(L, result.errn);
        return 3;
    }
}

static int l_validate(lua_State *L)
{
    try
    {
        std::string xmlIn = luaL_checkstring(L, 1);
        std::string nsIn = luaL_checkstring(L, 2);

        char error[512] = {0};

        if (v2g_message_validator.validate_xml(xmlIn.c_str(), nsIn.c_str(), error, sizeof(error) / sizeof(error[0])))
        {
            lua_pushboolean(L, 1);
            return 1;
        }
        else
        {
            // remove namespaces in error messages
            std::string errorStr = std::string(error);
            size_t start_pos = errorStr.find('{');
            size_t end_pos = errorStr.find('}');
            if (start_pos != std::string::npos && end_pos != std::string::npos && start_pos < end_pos)
            {
                errorStr.erase(start_pos, end_pos - start_pos + 1);
            }

            lua_pushboolean(L, 0);
            lua_pushstring(L, errorStr.c_str());
            return 2;
        }
    }
    catch (...)
    {
        lua_pushboolean(L, 0);
        lua_pushstring(L, "internal validation error");
        return 2;
    }
    return 0;
}

static int l_validate_init(lua_State *L)
{
    v2g_message_validator.init_validators();
    return 0;
}

static int l_validate_cleanup(lua_State *L)
{
    v2g_message_validator.cleanup_validators();
    return 0;
}

static int l_decodeV2GExi(lua_State *L)
{
    std::string schemaIn = luaL_checkstring(L, 1);
    std::string exiIn = luaL_checkstring(L, 2);

    result_decode result_decode = v2g_message_decoder.decode_message(exiIn, schemaIn);

    if (result_decode.errn)
    {
        std::string last_errorneos_xml = result_decode.decoded_xml;
        int last_errn = result_decode.errn;

        // use SAP as fallback
        result_decode = v2g_message_decoder.decode_message(exiIn, NAMESPACE_SAP);
        if (result_decode.errn == EXI_ERROR__NO_ERROR)
        {
            lua_pushstring(L, result_decode.decoded_xml.c_str());
            lua_pushstring(L, NAMESPACE_SAP);
            lua_pushinteger(L, result_decode.errn);
        }
        else
        {
            lua_pushstring(L, last_errorneos_xml.c_str());
            lua_pushstring(L, schemaIn.c_str());
            lua_pushinteger(L, last_errn);
        }
    }
    else
    {
        lua_pushstring(L, result_decode.decoded_xml.c_str());
        lua_pushstring(L, schemaIn.c_str());
        lua_pushinteger(L, result_decode.errn);
    }

    return 3;
}

extern "C"
{
    int luaopen_v2gLib(lua_State *L)
    {
        static const struct luaL_Reg LuaDecoderLib[] =
            {
                // function name, function reference
                {"decodeV2GExi", l_decodeV2GExi},
                {"decodeV2GAuto", l_decodeV2GExiAuto},
                {"validateXml", l_validate},
                {"initValidator", l_validate_init},
                {"cleanupValidator", l_validate_cleanup},
                {"getX509Infos", l_getX509Infos},
                {"getGnuTLSErrorDescr", l_getGnuTlsErrorDescription},
                {NULL, NULL}};
#if LUA_VERSION_NUM > 501
        luaL_newlib(L, LuaDecoderLib);
#else
        luaL_register(L, "LuaDecoder", LuaDecoderLib);
#endif
        return 1;
    }
}
