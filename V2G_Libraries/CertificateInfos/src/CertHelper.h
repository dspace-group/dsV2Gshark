/** <!------------------------------------------------------------------------->
 *
 *  @file
 *    CertHelper.h
 *
 *  @author
 *    ThorenG
 *
 *  @copyright
 *    Copyright 2024, dSPACE GmbH. All rights reserved.
 *    See LICENSE file
 *
 *<!-------------------------------------------------------------------------->*/
#pragma once

#include <string>

struct X509CertInfos
{
    bool valid = false;
    std::string subject = "ERROR";
    std::string issuer = "ERROR";
    int version = -1; // Note: this is defined by standards to be one less than
                      // the certificate version. E.g., version 3 certificate will return 2
    std::string serial_number = "ERROR"; // hex-string
    std::string sig_algorithm = "ERROR";
    std::string sig_value = "ERROR";
    std::string time_not_after = "ERROR";
    std::string time_not_before = "ERROR";
    std::string pubkey_algorithm = "ERROR";
    std::string spk_pub = "ERROR";
    std::string spk_NIST_curve = "ERROR";

    std::string v3ext_basic_constraint = "ERROR";
    std::string v3ext_basic_constraint_CA = "ERROR";
    std::string v3ext_key_usage = "ERROR";
    std::string v3ext_key_usage_critical = "ERROR";
    std::string v3ext_subjkey_id = "ERROR";
    std::string v3ext_subjkey_id_critical = "ERROR";
};

X509CertInfos get_cert_info(std::string x509_content);
