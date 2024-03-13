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
    int luaopen_v2gLuaDecoder(lua_State *L)
    {
        static const struct luaL_Reg LuaDecoderLib[] =
            {
                // function name, function reference
                {"decodeV2GExi", l_decodeV2GExi},
                {"decodeV2GAuto", l_decodeV2GExiAuto},
                {"validateXml", l_validate},
                {"initValidator", l_validate_init},
                {"cleanupValidator", l_validate_cleanup},
                {NULL, NULL}};
        luaL_newlib(L, LuaDecoderLib);
        return 1;
    }
}