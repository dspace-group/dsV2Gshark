"""
File:           zip_xsd.py

Description:    With this script it is possible to compress the content of XSD files.
                This content is used in the V2G message decoder to validate V2G messages.
                A file 'Schemas.h' is created in which the compressed content is stored.
                The XSD files should be copied to a directory 'XSDs' so that this script can
                find the files. For each charging standard (ISO 15118-2, ISO 15118-20, DIN 70121) there
                is a subdirectory. The structure should be as follows:
                    XSDs/DIN_70121
                    XSDs/ISO_15118_2
                    XSDs/ISO_15118_20
                    XSDs/V2G_SAP
                Call `python zip_xsd.py` to generate the header file with the compressed content
                of the XSD files.
                
Preconditions:  python >= 3.9

Version:        1.0
"""

import typing
import os
import glob
import zlib
from collections import OrderedDict
import lxml.etree

SOURCE_PATH = "../src/"
FILE_NAME = "Schemas.h"


def create_key_from_file_path(file_path: str) -> str:
    """
    Create a string from the file path that is used as name of the variable in the generated file.
    """

    key_value = os.path.basename(file_path).replace(".xsd", "").replace("-", "_")
    if key_value == "xmldsig_core_schema":
        key_value = "XSD_XMLDSIG_CORE"

    if "ISO_15118_20\\" in file_path:
        key_value = key_value.replace("V2G_CI_", "XSD_ISO20_")
        if "CommonMessages" in key_value:
            key_value = key_value.replace("CommonMessages", "CM")
    elif "ISO_15118_2\\" in file_path:
        key_value = key_value.replace("V2G_CI_", "XSD_ISO2_")
    elif "DIN_70121\\" in file_path:
        key_value = key_value.replace("V2G_CI_", "XSD_DIN_")

    if "V2G_CI_AppProtocol" in key_value:
        key_value = key_value.replace("V2G_CI_AppProtocol", "XSD_SAP")

    return key_value


def import_data_from_xsd(file_path: str) -> typing.Tuple[str, bytes]:
    """
    Read the content of a XSD file using XMLParser. Comments and newlines are removed.
    This function returns the name of the file and the content as byte array in an tuple.
    """
    parser = lxml.etree.XMLParser(remove_comments=True, remove_blank_text=True)
    tree = lxml.etree.parse(file_path, parser)
    name = create_key_from_file_path(file_path)
    return (name, lxml.etree.tostring(tree))


def import_data_from_all_xsds(
    file_paths: typing.List[str],
) -> typing.OrderedDict[str, bytes]:
    """
    Returns a list of tuples with the file name and the content of the given XSD files.
    """
    xcd_content = OrderedDict()
    for file_path in file_paths:
        file_name, content_bytes = import_data_from_xsd(file_path)
        xcd_content[file_name] = content_bytes

    return xcd_content


def find_xsd_files(dir_name: str) -> typing.List[str]:
    """
    Returns a list of all XSD files in the given directory
    """
    xsd_file_paths = []
    if not os.path.isdir(dir_name):
        print(f"Directory '{dir_name}' does not exist.")
    else:
        xsd_file_paths = glob.glob(dir_name + "/*.xsd")
    return xsd_file_paths


def find_all_xsd_files() -> typing.List[str]:
    """
    Returns a list of all XSD files. The files are searched for in the
    following directories relative to the script:
        XSDs/DIN_70121
        XSDs/ISO_15118_2
        XSDs/ISO_15118_20
        XSDs/V2G_SAP
    """
    xsd_file_paths = []
    # find DIN 70121 schemas
    dir_name = "XSDs\\DIN_70121"
    xsd_file_paths += find_xsd_files(dir_name)

    # find ISO 15118-2 schemas
    dir_name = "XSDs\\ISO_15118_2"
    xsd_file_paths += find_xsd_files(dir_name)

    # find ISO 15118-20 schemas
    dir_name = "XSDs\\ISO_15118_20"
    xsd_file_paths += find_xsd_files(dir_name)

    # SupportedAppProtocol
    dir_name = "XSDs\\V2G_SAP"
    xsd_file_paths += find_xsd_files(dir_name)

    return xsd_file_paths


def create_header_info() -> str:
    """
    Header of the output file
    """
    header_info = "/** <!------------------------------------------------------------------------->\n"
    header_info += "*\n"
    header_info += "*  @file\n"
    header_info += "*    " + FILE_NAME + "\n"
    header_info += "*\n"
    header_info += "*  @note\n"
    header_info += "*    This file has been generated with zip_xsd.py\n"
    header_info += "*\n"
    header_info += "*<!-------------------------------------------------------------------------->*/\n\n"

    return header_info


def create_header_zipped_data(xsd_content: typing.OrderedDict[str, bytes]) -> None:
    """
    Create a file 'schema.h' with the content of XSD files. The content is zipped using
    'zlib'.
    """
    with open(SOURCE_PATH + FILE_NAME, "w", encoding="utf-8") as schemas_file:
        schemas_file.write(create_header_info())
        schemas_file.write("#include <cstdint>\n\n")

        max_unzipped_len = 0
        for file_name, xsd_byte_array in xsd_content.items():
            print(file_name)
            string_value_zipped = zlib.compress(xsd_byte_array, level=6)
            xsd_zipped_hex_array = "{"
            xsd_zipped_hex_array += ", ".join(
                "0x{:02x}".format(x) for x in string_value_zipped
            )
            xsd_zipped_hex_array += "}"
            schemas_file.write(f"uint8_t {file_name}[] = {xsd_zipped_hex_array};\n")
            schemas_file.write(
                f"uint16_t {file_name}_zipped_len = {str(len(string_value_zipped))};\n\n"
            )
            if len(xsd_byte_array) > max_unzipped_len:
                max_unzipped_len = len(xsd_byte_array)
        schemas_file.write(
            f"constexpr uint16_t MAX_UNZIPPED_LEN = {max_unzipped_len};\n"
        )


if __name__ == "__main__":
    xsd_files = find_all_xsd_files()
    xsd_data = import_data_from_all_xsds(xsd_files)
    create_header_zipped_data(xsd_data)
