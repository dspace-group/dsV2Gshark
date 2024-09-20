/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    GnuTLSHelper.cpp
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!-------------------------------------------------------------------------->*/
#include <gnutls/gnutls.h>
#include <gnutls/x509.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <iomanip>

#include "CertHelper.h"
#include "Utils.h"

constexpr int MAX_STRING_LEN = 512;

std::string get_error_description(int error_code)
{
    return std::string(gnutls_strerror(error_code));
}

X509CertInfos get_cert_info(std::string x509_content)
{
    X509CertInfos cert_info{};

    gnutls_x509_crt_t cert;

    cert_info.result = gnutls_x509_crt_init(&cert);
    if (cert_info.result < 0)
    {
        fprintf(stderr, "dsV2G CertInfo error in initialization\n");
        return cert_info;
    }

    char buffer[MAX_STRING_LEN];
    size_t size = sizeof(buffer);

    gnutls_datum_t cert_in;
    cert_in.data = new unsigned char[x509_content.length()];
    strncpy((char *)cert_in.data, x509_content.c_str(), x509_content.length());
    cert_in.size = x509_content.length();
    cert_info.result = gnutls_x509_crt_import(cert, &cert_in, GNUTLS_X509_FMT_PEM);
    if (cert_info.result < 0)
    {
        fprintf(stderr, "dsV2G CertInfo error parsing certificate\n");
        delete[] cert_in.data;
        gnutls_x509_crt_deinit(cert);
        return cert_info;
    }

    size = sizeof(buffer);
    int errn = gnutls_x509_crt_get_serial(cert, buffer, &size);
    if (errn != GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_serial\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = errn;
        }
        cert_info.serial_number = "ERROR";
    }
    else
    {
        cert_info.serial_number = "0x" + uint8_to_hex_string((uint8_t *)buffer, size);
    }

    time_t expiration_time, activation_time;
    expiration_time = gnutls_x509_crt_get_expiration_time(cert);
    if (expiration_time == -1)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_expiration_time\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = expiration_time;
        }
        cert_info.time_not_after = "ERROR";
    }
    else
    {
        cert_info.time_not_after = ctime(&expiration_time);
        cert_info.time_not_after.pop_back();  // remove linebreak
    }
    activation_time = gnutls_x509_crt_get_activation_time(cert);
    if (activation_time == -1)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_activation_time\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = activation_time;
        }
        cert_info.time_not_before = "ERROR";
    }
    else
    {
        cert_info.time_not_before = ctime(&activation_time);
        cert_info.time_not_before.pop_back();  // remove linebreak
    }

    int sig_algorithm = gnutls_x509_crt_get_signature_algorithm(cert);
    cert_info.sig_algorithm = gnutls_sign_algorithm_get_name((gnutls_sign_algorithm_t)sig_algorithm);

    cert_info.version = gnutls_x509_crt_get_version(cert) - 1;
    if (cert_info.version < 0)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_version\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = cert_info.version;
        }
    }

    size = sizeof(buffer);
    errn = gnutls_x509_crt_get_dn(cert, buffer, &size);
    if (errn != GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_dn\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = errn;
        }
        cert_info.subject = "ERROR";
    }
    else
    {
        cert_info.subject = buffer;
    }

    size = sizeof(buffer);
    errn = gnutls_x509_crt_get_issuer_dn(cert, buffer, &size);
    if (errn != GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_issuer_dn\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = errn;
        }
        cert_info.issuer = "ERROR";
    }
    else
    {
        cert_info.issuer = buffer;
    }

    size = sizeof(buffer);
    errn = gnutls_x509_crt_get_signature(cert, buffer, &size);
    if (errn != GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_signature\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = errn;
        }
        cert_info.sig_value = "ERROR";
    }
    else
    {
        cert_info.sig_value = uint8_to_hex_string((uint8_t *)buffer, size);
    }

    unsigned int pk_algo, bits;
    pk_algo = gnutls_x509_crt_get_pk_algorithm(cert, &bits);
    if (pk_algo < 0)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_pk_algorithm\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = pk_algo;
        }
        cert_info.pubkey_algorithm = "ERROR";
    }
    else
    {
        cert_info.pubkey_algorithm = gnutls_pk_algorithm_get_name((gnutls_pk_algorithm_t)pk_algo);
    }

    unsigned int ext_crit, ext_ca;
    int ext_pathlen;
    int basic_constraints_ret = gnutls_x509_crt_get_basic_constraints(cert, &ext_crit, &ext_ca, &ext_pathlen);
    if (basic_constraints_ret == GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE)
    {
        cert_info.v3ext_basic_constraint = "N/A";
        cert_info.v3ext_basic_constraint_CA = "N/A";
    }
    else if (basic_constraints_ret < GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_basic_constraints %d\n", basic_constraints_ret);
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = basic_constraints_ret;
        }
        cert_info.v3ext_basic_constraint = "ERROR";
        cert_info.v3ext_basic_constraint_CA = "ERROR";
    }
    else
    {
        switch (ext_crit)
        {
        case 0:
            cert_info.v3ext_basic_constraint = "not critical";
            break;
        case 1:
            cert_info.v3ext_basic_constraint = "critical";
            break;
        default:
            cert_info.v3ext_basic_constraint = "unknown error";
            fprintf(stderr, "crit     : %ud\n", ext_crit);
            break;
        }
        switch (ext_ca)
        {
        case 0:
            cert_info.v3ext_basic_constraint_CA = "not set";
            break;
        case 1:
            cert_info.v3ext_basic_constraint_CA = "set";
            break;
        default:
            cert_info.v3ext_basic_constraint_CA = "unknown error";
            fprintf(stderr, "bc ca     : %ud\n", ext_ca);
            break;
        }
    }

    unsigned int key_usage;
    int key_usage_ret = gnutls_x509_crt_get_key_usage(cert, &key_usage, &ext_crit);
    if (key_usage_ret == GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE)
    {
        cert_info.v3ext_key_usage = "N/A";
        cert_info.v3ext_key_usage_critical = "N/A";
    }
    else if (key_usage_ret != GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_key_usage\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = key_usage_ret;
        }
        cert_info.v3ext_key_usage = "ERROR";
        cert_info.v3ext_key_usage_critical = "ERROR";
    }
    else
    {
        switch (ext_crit)
        {
        case 0:
            cert_info.v3ext_key_usage_critical = "not critical";
            break;
        case 1:
            cert_info.v3ext_key_usage_critical = "critical";
            break;
        default:
            cert_info.v3ext_key_usage_critical = "unknown error";
            break;
        }

        cert_info.v3ext_key_usage = "";
        if (key_usage & GNUTLS_KEY_DIGITAL_SIGNATURE)
            cert_info.v3ext_key_usage += "Digital Signature, ";
        if (key_usage & GNUTLS_KEY_NON_REPUDIATION)
            cert_info.v3ext_key_usage += "Non Repudiation, ";
        if (key_usage & GNUTLS_KEY_KEY_ENCIPHERMENT)
            cert_info.v3ext_key_usage += "Key Encipherment, ";
        if (key_usage & GNUTLS_KEY_DATA_ENCIPHERMENT)
            cert_info.v3ext_key_usage += "Data Encipherment, ";
        if (key_usage & GNUTLS_KEY_KEY_AGREEMENT)
            cert_info.v3ext_key_usage += "Key Agreement, ";
        if (key_usage & GNUTLS_KEY_KEY_CERT_SIGN)
            cert_info.v3ext_key_usage += "Cert Sign, ";
        if (key_usage & GNUTLS_KEY_CRL_SIGN)
            cert_info.v3ext_key_usage += "Crl Sign, ";
        if (key_usage & GNUTLS_KEY_ENCIPHER_ONLY)
            cert_info.v3ext_key_usage += "Encipher only, ";
        if (key_usage & GNUTLS_KEY_ENCIPHER_ONLY)
            cert_info.v3ext_key_usage += "Decipher only, ";

        if (cert_info.v3ext_key_usage.length() > 1)
            cert_info.v3ext_key_usage.pop_back();
        if (cert_info.v3ext_key_usage.length() > 1)
            cert_info.v3ext_key_usage.pop_back();
    }

    size = sizeof(buffer);
    int keyIdRet = gnutls_x509_crt_get_subject_key_id(cert, buffer, &size, &ext_crit);
    if (keyIdRet == GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE)
    {
        cert_info.v3ext_subjkey_id = "N/A";
        cert_info.v3ext_subjkey_id_critical = "N/A";
    }
    else if (keyIdRet != GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_subject_key_id\n");
        if (cert_info.result == GNUTLS_E_SUCCESS)
        {
            cert_info.result = keyIdRet;
        }
        cert_info.v3ext_subjkey_id = "ERROR";
        cert_info.v3ext_subjkey_id_critical = "ERROR";
    }
    else
    {
        switch (ext_crit)
        {
        case 0:
            cert_info.v3ext_subjkey_id_critical = "not critical";
            break;
        case 1:
            cert_info.v3ext_subjkey_id_critical = "critical";
            break;
        default:
            cert_info.v3ext_subjkey_id_critical = "unknown error";
            break;
        }
        cert_info.v3ext_subjkey_id = uint8_to_hex_string((uint8_t *)buffer, size);
    }

    gnutls_ecc_curve_t curve;
    gnutls_datum_t coord_x, coord_y;
    if (gnutls_x509_crt_get_pk_ecc_raw(cert, &curve, &coord_x, &coord_y) != GNUTLS_E_SUCCESS)
    {
        fprintf(stderr, "dsV2G CertInfo error gnutls_x509_crt_get_pk_ecc_raw\n");
        // cert_info.result - keep previous result in case this is not ecc pk
        cert_info.spk_NIST_curve = "ERROR";
        cert_info.spk_pub = "ERROR";
    }
    else
    {
        cert_info.spk_NIST_curve = gnutls_ecc_curve_get_name(curve);
        cert_info.spk_pub = uint8_to_hex_string(coord_x.data, coord_x.size);
        cert_info.spk_pub += uint8_to_hex_string(coord_y.data, coord_y.size);
    }

    delete[] cert_in.data;
    gnutls_x509_crt_deinit(cert);

    return cert_info;
}
