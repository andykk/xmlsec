/** 
 * XMLSec library
 *
 *
 * See Copyright for the status of this software.
 * 
 * Author: Aleksey Sanin <aleksey@aleksey.com>
 */
#include "globals.h"

#include <libxml/tree.h>

#include <xmlsec/xmlsec.h>

/*************************************************************************
 *
 * Global Namespaces
 *
 ************************************************************************/
const xmlChar xmlSecNs[] 			= "http://www.aleksey.com/xmlsec/2002";
const xmlChar xmlSecDSigNs[] 			= "http://www.w3.org/2000/09/xmldsig#";
const xmlChar xmlSecEncNs[] 			= "http://www.w3.org/2001/04/xmlenc#";
const xmlChar xmlSecXPathNs[] 			= "http://www.w3.org/TR/1999/REC-xpath-19991116";
const xmlChar xmlSecXPath2Ns[] 			= "http://www.w3.org/2002/06/xmldsig-filter2";
const xmlChar xmlSecXPointerNs[]		= "http://www.w3.org/2001/04/xmldsig-more/xptr";

/*************************************************************************
 *
 * DSig Nodes
 *
 ************************************************************************/
const xmlChar xmlSecNodeSignature[]		= "Signature";
const xmlChar xmlSecNodeSignedInfo[]		= "SignedInfo";
const xmlChar xmlSecNodeCanonicalizationMethod[]= "CanonicalizationMethod";
const xmlChar xmlSecNodeSignatureMethod[]	= "SignatureMethod";
const xmlChar xmlSecNodeSignatureValue[]	= "SignatureValue";
const xmlChar xmlSecNodeDigestMethod[]		= "DigestMethod";
const xmlChar xmlSecNodeDigestValue[]		= "DigestValue";
const xmlChar xmlSecNodeObject[]		= "Object";
const xmlChar xmlSecNodeManifest[]		= "Manifest";

/*************************************************************************
 *
 * Encryption Nodes
 *
 ************************************************************************/
const xmlChar xmlSecNodeCipherValue[]		= "CipherValue";
const xmlChar xmlSecNodeCipherData[]		= "CipherData";
const xmlChar xmlSecNodeCipherReference[]	= "CipherReference";

/*************************************************************************
 *
 * KeyInfo Nodes
 *
 ************************************************************************/
const xmlChar xmlSecNodeKeyInfo[]		= "KeyInfo";
const xmlChar xmlSecNodeReference[]		= "Reference";
const xmlChar xmlSecNodeTransforms[]		= "Transforms";
const xmlChar xmlSecNodeTransform[]		= "Transform";

/*************************************************************************
 *
 * Attributes
 *
 ************************************************************************/
const xmlChar xmlSecAttrId[]			= "Id";
const xmlChar xmlSecAttrURI[]			= "URI";
const xmlChar xmlSecAttrType[]			= "Type";
const xmlChar xmlSecAttrAlgorithm[]		= "Algorithm";
const xmlChar xmlSecAttrFilter[]		= "Filter";

/*************************************************************************
 *
 * AES strings
 *
 ************************************************************************/
const xmlChar xmlSecNameAESKeyValue[]		= "aes";
const xmlChar xmlSecNodeAESKeyValue[]		= "AESKeyValue";
const xmlChar xmlSecHrefAESKeyValue[]		= "http://www.aleksey.com/xmlsec/2002#AESKeyValue";

const xmlChar xmlSecNameAes128Cbc[]		= "aes128-cbc-transform";
const xmlChar xmlSecHrefAes128Cbc[]		= "http://www.w3.org/2001/04/xmlenc#aes128-cbc";

const xmlChar xmlSecNameAes192Cbc[]		= "aes192-cbc-transform";
const xmlChar xmlSecHrefAes192Cbc[]		= "http://www.w3.org/2001/04/xmlenc#aes192-cbc";

const xmlChar xmlSecNameAes256Cbc[]		= "aes256-cbc-transform";
const xmlChar xmlSecHrefAes256Cbc[]		= "http://www.w3.org/2001/04/xmlenc#aes256-cbc";

const xmlChar xmlSecNameKWAes128[]		= "kw-aes128-transform";
const xmlChar xmlSecHrefKWAes128[]		= "http://www.w3.org/2001/04/xmlenc#kw-aes128";

const xmlChar xmlSecNameKWAes192[]		= "kw-aes192-transform";
const xmlChar xmlSecHrefKWAes192[]		= "http://www.w3.org/2001/04/xmlenc#kw-aes192";

const xmlChar xmlSecNameKWAes256[]		= "kw-aes256-transform";
const xmlChar xmlSecHrefKWAes256[]		= "http://www.w3.org/2001/04/xmlenc#kw-aes256";

/*************************************************************************
 *
 * BASE64 strings
 *
 ************************************************************************/
const xmlChar xmlSecNameBase64[]		= "base64-transform";
const xmlChar xmlSecHrefBase64[]		= "http://www.w3.org/2000/09/xmldsig#base64";

/*************************************************************************
 *
 * C14N strings
 *
 ************************************************************************/
const xmlChar xmlSecNameC14N[]			= "c14n-transform";
const xmlChar xmlSecHrefC14N[]			= "http://www.w3.org/TR/2001/REC-xml-c14n-20010315";

const xmlChar xmlSecNameC14NWithComments[]	= "c14n-with-comments-transform";
const xmlChar xmlSecHrefC14NWithComments[]	= "http://www.w3.org/TR/2001/REC-xml-c14n-20010315#WithComments";

const xmlChar xmlSecNameExcC14N[]		= "exc-c14n-transform";
const xmlChar xmlSecHrefExcC14N[]		= "http://www.w3.org/2001/10/xml-exc-c14n#";

const xmlChar xmlSecNameExcC14NWithComments[]	= "exc-c14n-with-comments-transform";
const xmlChar xmlSecHrefExcC14NWithComments[]	= "http://www.w3.org/2001/10/xml-exc-c14n#WithComments";

const xmlChar xmlSecNsExcC14N[]			= "http://www.w3.org/2001/10/xml-exc-c14n#";
const xmlChar xmlSecNsExcC14NWithComments[]	= "http://www.w3.org/2001/10/xml-exc-c14n#WithComments";

const xmlChar xmlSecNodeInclusiveNamespaces[]	= "InclusiveNamespaces";
const xmlChar xmlSecAttrPrefixList[]		= "PrefixList";
/*************************************************************************
 *
 * DES strings
 *
 ************************************************************************/
const xmlChar xmlSecNameDESKeyValue[]		= "des";
const xmlChar xmlSecNodeDESKeyValue[]		= "DESKeyValue";
const xmlChar xmlSecHrefDESKeyValue[]		= "http://www.aleksey.com/xmlsec/2002#DESKeyValue";

const xmlChar xmlSecNameDes3Cbc[]		= "tripledes-cbc-transform";
const xmlChar xmlSecHrefDes3Cbc[]		= "http://www.w3.org/2001/04/xmlenc#tripledes-cbc";

const xmlChar xmlSecNameKWDes3[]		= "kw-tripledes-transform";
const xmlChar xmlSecHrefKWDes3[]		= "http://www.w3.org/2001/04/xmlenc#kw-tripledes";

/*************************************************************************
 *
 * DSA strings
 *
 ************************************************************************/
const xmlChar xmlSecNameDSAKeyValue[]		= "dsa";
const xmlChar xmlSecNodeDSAKeyValue[]		= "DSAKeyValue";
const xmlChar xmlSecHrefDSAKeyValue[]		= "http://www.w3.org/2000/09/xmldsig#DSAKeyValue";
const xmlChar xmlSecNodeDSAP[]			= "P";
const xmlChar xmlSecNodeDSAQ[]			= "Q";
const xmlChar xmlSecNodeDSAG[]			= "G";
const xmlChar xmlSecNodeDSAX[]			= "X";
const xmlChar xmlSecNodeDSAY[]			= "Y";
const xmlChar xmlSecNodeDSASeed[]		= "Seed";
const xmlChar xmlSecNodeDSAPgenCounter[]	= "PgenCounter";

const xmlChar xmlSecNameDsaSha1[]		= "dsa-sha1-transform";
const xmlChar xmlSecHrefDsaSha1[]		= "http://www.w3.org/2000/09/xmldsig#dsa-sha1";

/*************************************************************************
 *
 * EncryptedKey
 *
 ************************************************************************/
const xmlChar xmlSecNameEncryptedKey[]		= "enc-key-transform";
const xmlChar xmlSecNodeEncryptedKey[]		= "EncryptedKey";
const xmlChar xmlSecHrefEncryptedKey[]		= "http://www.w3.org/2001/04/xmlenc#EncryptedKey";

/*************************************************************************
 *
 * Enveloped transform strings
 *
 ************************************************************************/
const xmlChar xmlSecNameEnveloped[]		= "enveloped-transform";
const xmlChar xmlSecHrefEnveloped[]		= "http://www.w3.org/2000/09/xmldsig#enveloped-signature";

/*************************************************************************
 *
 * HMAC strings
 *
 ************************************************************************/
const xmlChar xmlSecNameHMACKeyValue[]		= "hmac";
const xmlChar xmlSecNodeHMACKeyValue[]		= "HMACKeyValue";
const xmlChar xmlSecHrefHMACKeyValue[]		= "http://www.aleksey.com/xmlsec/2002#HMACKeyValue";

const xmlChar xmlSecNodeHMACOutputLength[] 	= "HMACOutputLength";

const xmlChar xmlSecNameHmacSha1[]		= "hmac-sha1-transform";
const xmlChar xmlSecHrefHmacSha1[]		= "http://www.w3.org/2000/09/xmldsig#hmac-sha1";

const xmlChar xmlSecNameHmacRipemd160[]		= "hmac-ripemd160-transform";
const xmlChar xmlSecHrefHmacRipemd160[]		= "http://www.w3.org/2001/04/xmldsig-more#hmac-ripemd160";

const xmlChar xmlSecNameHmacMd5[]		= "hmac-md5-transform";
const xmlChar xmlSecHrefHmacMd5[]		= "http://www.w3.org/2001/04/xmldsig-more#hmac-md5";

/*************************************************************************
 *
 * KeyName strings
 *
 ************************************************************************/
const xmlChar xmlSecNameKeyName[]		= "key-name";
const xmlChar xmlSecNodeKeyName[]		= "KeyName";

/*************************************************************************
 *
 * KeyValue strings
 *
 ************************************************************************/
const xmlChar xmlSecNameKeyValue[]		= "key-value";
const xmlChar xmlSecNodeKeyValue[]		= "KeyValue";

/*************************************************************************
 *
 * Memory Buffer strings
 *
 ************************************************************************/
const xmlChar xmlSecNameMemBuf[]		= "membuf-transform";

/*************************************************************************
 *
 * RetrievalMethod
 *
 ************************************************************************/
const xmlChar xmlSecNameRetrievalMethod[] 	= "retrieval-method";
const xmlChar xmlSecNodeRetrievalMethod[] 	= "RetrievalMethod";

/*************************************************************************
 *
 * RIPEMD160 strings
 *
 ************************************************************************/
const xmlChar xmlSecNameRipemd160[]		= "ripemd160-transform";
const xmlChar xmlSecHrefRipemd160[]		= "http://www.w3.org/2001/04/xmlenc#ripemd160";

/*************************************************************************
 *
 * RSA strings
 *
 ************************************************************************/
const xmlChar xmlSecNameRSAKeyValue[]		= "rsa";
const xmlChar xmlSecNodeRSAKeyValue[]		= "RSAKeyValue";
const xmlChar xmlSecHrefRSAKeyValue[]		= "http://www.w3.org/2000/09/xmldsig#RSAKeyValue";
const xmlChar xmlSecNodeRSAModulus[]		= "Modulus";
const xmlChar xmlSecNodeRSAExponent[]		= "Exponent";
const xmlChar xmlSecNodeRSAPrivateExponent[] 	= "PrivateExponent";

const xmlChar xmlSecNameRsaSha1[]		= "rsa-sha1-transform";
const xmlChar xmlSecHrefRsaSha1[]		= "http://www.w3.org/2000/09/xmldsig#rsa-sha1";

const xmlChar xmlSecNameRsaPkcs1[]		= "rsa-pkcs1-transform";
const xmlChar xmlSecHrefRsaPkcs1[]		= "http://www.w3.org/2001/04/xmlenc#rsa-1_5";

const xmlChar xmlSecNameRsaOaep[]		= "rsa-oaep-transform";
const xmlChar xmlSecHrefRsaOaep[]		= "http://www.w3.org/2001/04/xmlenc#rsa-oaep-mgf1p";
const xmlChar xmlSecNodeRsaOAEPparams[]		= "OAEPparams";

/*************************************************************************
 *
 * SHA1 strings
 *
 ************************************************************************/
const xmlChar xmlSecNameSha1[]			= "sha1-transform";
const xmlChar xmlSecHrefSha1[]			= "http://www.w3.org/2000/09/xmldsig#sha1";

/*************************************************************************
 *
 * X509 strings
 *
 ************************************************************************/
const xmlChar xmlSecNameX509Data[]		= "x509-data";
const xmlChar xmlSecNodeX509Data[]		= "X509Data";
const xmlChar xmlSecHrefX509Data[]		= "http://www.w3.org/2000/09/xmldsig#X509Data";

const xmlChar xmlSecNodeX509Certificate[]	= "X509Certificate";
const xmlChar xmlSecNodeX509CRL[]		= "X509CRL";
const xmlChar xmlSecNodeX509SubjectName[]	= "X509SubjectName";
const xmlChar xmlSecNodeX509IssuerSerial[]	= "X509IssuerSerial";
const xmlChar xmlSecNodeX509IssuerName[]	= "X509IssuerName";
const xmlChar xmlSecNodeX509SerialNumber[]	= "X509SerialNumber";
const xmlChar xmlSecNodeX509SKI[]		= "X509SKI";

const xmlChar xmlSecNameRawX509Cert[]		= "raw-x509-cert";
const xmlChar xmlSecHrefRawX509Cert[]		= "http://www.w3.org/2000/09/xmldsig#rawX509Certificate";

const xmlChar xmlSecNameX509Store[]		= "x509-store";

/*************************************************************************
 *
 * XPath/XPointer strings
 *
 ************************************************************************/
const xmlChar xmlSecNameXPath[]			= "xpath-transform";
const xmlChar xmlSecNodeXPath[]			= "XPath";

const xmlChar xmlSecNameXPath2[]		= "xpath2-transform";
const xmlChar xmlSecNodeXPath2[]		= "XPath";
const xmlChar xmlSecXPath2FilterIntersect[]	= "intersect";
const xmlChar xmlSecXPath2FilterSubtract[]	= "subtract";
const xmlChar xmlSecXPath2FilterUnion[]		= "union";

const xmlChar xmlSecNameXPointer[]		= "xpointer-transform";
const xmlChar xmlSecNodeXPointer[]		= "XPointer";

/*************************************************************************
 *
 * Xslt strings
 *
 ************************************************************************/
const xmlChar xmlSecNameXslt[]			= "xslt-transform";
const xmlChar xmlSecHrefXslt[]			= "http://www.w3.org/TR/1999/REC-xslt-19991116";

/*************************************************************************
 *
 * Utility strings
 *
 ************************************************************************/
const xmlChar xmlSecStringEmpty[]		= "";
const xmlChar xmlSecStringCR[]			= "\n";





