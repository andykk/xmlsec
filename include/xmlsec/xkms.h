	/** 
 * XML Security Library (http://www.aleksey.com/xmlsec).
 *
 * "XML Key Management Specification v 2.0" implementation
 *  http://www.w3.org/TR/xkms2/
 * 
 * This is free software; see Copyright file in the source
 * distribution for preciese wording.
 * 
 * Copyright (C) 2002-2003 Aleksey Sanin <aleksey@aleksey.com>
 */
#ifndef __XMLSEC_XKMS_H__
#define __XMLSEC_XKMS_H__    

#ifndef XMLSEC_NO_XKMS
	
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */ 
#include <stdio.h>		

#include <libxml/tree.h>
#include <libxml/parser.h> 

#include <xmlsec/xmlsec.h>
#include <xmlsec/buffer.h>
#include <xmlsec/list.h>
#include <xmlsec/keys.h>
#include <xmlsec/keysmngr.h>
#include <xmlsec/keyinfo.h>
#include <xmlsec/transforms.h>

typedef struct _xmlSecXkmsRespondWithKlass	xmlSecXkmsRespondWithKlass, 
						*xmlSecXkmsRespondWithId;


/************************************************************************
 *
 * XKMS requests server side processing klass
 *
 ************************************************************************/ 
/**
 * XMLSEC_XKMS_NO_RESPONSE_LIMIT:
 *
 * The responseLimit value.
 */
#define XMLSEC_XKMS_NO_RESPONSE_LIMIT				-1


/**
 * xmlXkmsServerCtxMode:
 * @xmlXkmsServerCtxModeLocateRequest: 	the <xkms:LocateRequest/> node processing.
 * @xmlXkmsServerCtxModeValidateRequest:	the <xkms:ValidateRequest/> node processing.
 *
 * XKMS request processing mode.
 */
typedef enum {
    xmlXkmsServerCtxModeLocateRequest = 0,
    xmlXkmsServerCtxModeValidateRequest
} xmlXkmsServerCtxMode;

/** 
 * xmlSecXkmsServerCtx:
 * @userData:			the pointer to user data (xmlsec and xmlsec-crypto libraries
 *				never touches this).
 * @flags:			the XML Encryption processing flags.
 * @flags2:			the XML Encryption processing flags.
 * @keyInfoReadCtx:		the reading key context.
 * @keyInfoWriteCtx:		the writing key context (not used for signature verification).
 * @reserved0:			reserved for the future.
 * @reserved1:			reserved for the future.
 * 
 * XKMS context.
 */
struct _xmlSecXkmsServerCtx {
    /* these data user can set before performing the operation */
    void*			userData;
    unsigned int		flags;
    unsigned int		flags2;    
    xmlSecKeyInfoCtx		keyInfoReadCtx;
    xmlSecKeyInfoCtx		keyInfoWriteCtx;
    xmlSecPtrList		enabledRespondWith;
    
    /* these data are returned */
    xmlDocPtr			result;
    xmlSecPtrList		keys;
    int				majorError;
    int				minorError;
    xmlChar*			requestId;    
    xmlChar*			service;
    xmlChar*			nonce;
    xmlChar*			originalRequestId;
    xmlChar*                    pendingNotificationMechanism;
    xmlChar*                    pendingNotificationIdentifier;
    int 			responseLimit;
    unsigned int		responseMechanismMask;

    /* these are internal data, nobody should change that except us */
    xmlXkmsServerCtxMode	mode;
    xmlNodePtr			opaqueClientDataNode;
    xmlNodePtr 			firtsMsgExtNode;
    xmlNodePtr 			keyInfoNode;
    xmlSecPtrList		respWithList;
    
    /* reserved for future */
    void*			reserved0;
    void*			reserved1;
};

XMLSEC_EXPORT xmlSecXkmsServerCtxPtr	xmlSecXkmsServerCtxCreate(xmlSecKeysMngrPtr keysMngr);
XMLSEC_EXPORT void 		xmlSecXkmsServerCtxDestroy	(xmlSecXkmsServerCtxPtr ctx);
XMLSEC_EXPORT int		xmlSecXkmsServerCtxInitialize	(xmlSecXkmsServerCtxPtr ctx,
								 xmlSecKeysMngrPtr keysMngr);
XMLSEC_EXPORT void		xmlSecXkmsServerCtxFinalize	(xmlSecXkmsServerCtxPtr ctx);
XMLSEC_EXPORT int		xmlSecXkmsServerCtxCopyUserPref(xmlSecXkmsServerCtxPtr dst,
								 xmlSecXkmsServerCtxPtr src);
XMLSEC_EXPORT void		xmlSecXkmsServerCtxReset	(xmlSecXkmsServerCtxPtr ctx);
XMLSEC_EXPORT void		xmlSecXkmsServerCtxSetError	(xmlSecXkmsServerCtxPtr ctx,
								 int majorError,
								 int minorError);
XMLSEC_EXPORT int		xmlSecXkmsServerCtxLocate	(xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);
XMLSEC_EXPORT int		xmlSecXkmsServerCtxValidate	(xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);
XMLSEC_EXPORT void		xmlSecXkmsServerCtxDebugDump	(xmlSecXkmsServerCtxPtr ctx,
								 FILE* output);
XMLSEC_EXPORT void		xmlSecXkmsServerCtxDebugXmlDump(xmlSecXkmsServerCtxPtr ctx,
								 FILE* output);


/************************************************************************
 *
 * XKMS ResultMajor attribute values.
 *
 ************************************************************************/ 
/**
 * XMLSEC_XKMS_ERROR_MAJOR_SUCCESS:
 *
 * XKMS ResultMajor attribute value. The operation succeeded.
 */
#define XMLSEC_XKMS_ERROR_MAJOR_SUCCESS			0		

/**
 * XMLSEC_XKMS_ERROR_MAJOR_VERSION_MISMATCH:
 *
 * XKMS ResultMajor attribute value. The service does not support 
 * the protocol version specified in the request.
 */
#define XMLSEC_XKMS_ERROR_MAJOR_VERSION_MISMATCH	1	

/**
 * XMLSEC_XKMS_ERROR_MAJOR_SENDER:
 *
 * XKMS ResultMajor attribute value. An error occurred that was due to 
 * the message sent by the sender.
 */
#define XMLSEC_XKMS_ERROR_MAJOR_SENDER			2			

/**
 * XMLSEC_XKMS_ERROR_MAJOR_RECEIVER:
 *
 * XKMS ResultMajor attribute value. An error occurred at the receiver.
 */
#define XMLSEC_XKMS_ERROR_MAJOR_RECEIVER		3			

/**
 * XMLSEC_XKMS_ERROR_MAJOR_REPRESENT:
 *
 * XKMS ResultMajor attribute value. The service has not acted on 
 * the request. In order for the request to be acted upon the request MUST 
 * be represented with the specified nonce in accordance with the two phase 
 * protocol.
 */
#define XMLSEC_XKMS_ERROR_MAJOR_REPRESENT		4			

/**
 * XMLSEC_XKMS_ERROR_MAJOR_PENDING:
 *
 * XKMS ResultMajor attribute value. The request has been accepted 
 * for processing and the service will return the result asynchronously.
 */
#define XMLSEC_XKMS_ERROR_MAJOR_PENDING			5			

/************************************************************************
 *
 * XKMS ResultMinor attribute values.
 *
 ************************************************************************/ 
/**
 * XMLSEC_XKMS_ERROR_MINOR_NONE:
 *
 * XKMS ResultMinor attribute value. Not specified.
 */
#define XMLSEC_XKMS_ERROR_MINOR_NONE			0		

/**
 * XMLSEC_XKMS_ERROR_MINOR_NO_MATCH:
 *
 * XKMS ResultMinor attribute value. No match was found for the search 
 * prototype provided.
 */
#define XMLSEC_XKMS_ERROR_MINOR_NO_MATCH		1		

/**
 * XMLSEC_XKMS_ERROR_MINOR_TOO_MANY_RESPONSES:
 *
 * XKMS ResultMinor attribute value. The request resulted in the number of 
 * responses that exceeded either  the ResponseLimit value specified in 
 * the request or some other limit determined by the service. 
 * The service MAY either return a subset of the possible 
 * responses or none at all.
 */
#define XMLSEC_XKMS_ERROR_MINOR_TOO_MANY_RESPONSES	2		

/**
 * XMLSEC_XKMS_ERROR_MINOR_INCOMPLETE:
 *
 * XKMS ResultMinor attribute value. Only part of the information requested 
 * could be provided.
 */
#define XMLSEC_XKMS_ERROR_MINOR_INCOMPLETE		3

/**
 * XMLSEC_XKMS_ERROR_MINOR_FAILURE:
 *
 * XKMS ResultMinor attribute value. The service attempted to perform 
 * the request but the operation failed for unspecified reasons.
 */
#define XMLSEC_XKMS_ERROR_MINOR_FAILURE			4		

/**
 * XMLSEC_XKMS_ERROR_MINOR_REFUSED:
 *
 * XKMS ResultMinor attribute value. The operation was refused. The service 
 * did not attempt to perform the request.
 */
#define XMLSEC_XKMS_ERROR_MINOR_REFUSED			5		

/**
 * XMLSEC_XKMS_ERROR_MINOR_NO_AUTHENTICATION:
 *
 * XKMS ResultMinor attribute value. The operation was refused because 
 * the necessary authentication information was incorrect or missing.
 */
#define XMLSEC_XKMS_ERROR_MINOR_NO_AUTHENTICATION	6		

/**
 * XMLSEC_XKMS_ERROR_MINOR_MESSAGE_NOT_SUPPORTED:
 *	
 * XKMS ResultMinor attribute value. The receiver does not implement 
 * the specified operation.
 */
#define XMLSEC_XKMS_ERROR_MINOR_MESSAGE_NOT_SUPPORTED	7		

/**
 * XMLSEC_XKMS_ERROR_MINOR_UNKNOWN_RESPONSE_ID:
 *
 * XKMS ResultMinor attribute value. The ResponseId for which pending 
 * status was requested is unknown to the service.
 */
#define XMLSEC_XKMS_ERROR_MINOR_UNKNOWN_RESPONSE_ID	8		

/**
 * XMLSEC_XKMS_ERROR_MINOR_NOT_SYNCHRONOUS:
 *
 * XKMS ResultMinor attribute value. The receiver does not support 
 * synchronous processing of this type of request
 */
#define XMLSEC_XKMS_ERROR_MINOR_NOT_SYNCHRONOUS		9		


/************************************************************************
 *
 * XKMS ResponseMechanism element values.
 *
 ************************************************************************/ 
/**
 * XMLSEC_XKMS_RESPONSE_MECHANISM_MASK_REPRESENT:
 *
 * XKMS ResponseMechanism element value. The requestor is prepared to 
 * accept a response that uses asynchronous processing, i.e. the service 
 * MAY return the MajorResult code Pending.
 */
#define XMLSEC_XKMS_RESPONSE_MECHANISM_MASK_PENDING			0x00000001	

/**
 * XMLSEC_XKMS_RESPONSE_MECHANISM_MASK_REPRESENT:
 *
 * XKMS ResponseMechanism element value. The requestor is prepared to 
 * accept a response that uses the two phase protocol, i.e. the service 
 * MAY return the MajorResult code Represent.
 */
#define XMLSEC_XKMS_RESPONSE_MECHANISM_MASK_REPRESENT			0x00000002

/**
 * XMLSEC_XKMS_RESPONSE_MECHANISM_MASK_REQUEST_SIGNATURE_VALUE:
 *
 * XKMS ResponseMechanism element value. The requestor is prepared to 
 * accept a response that carries a <RequestSignatureValue> element.
 */
#define XMLSEC_XKMS_RESPONSE_MECHANISM_MASK_REQUEST_SIGNATURE_VALUE	0x00000004

/************************************************************************
 *
 * XKMS ResponseLimit element values
 *
 ************************************************************************/ 
/**
 * XMLSEC_XKMS_NO_RESPONSE_LIMIT:
 *
 * The ResponseLimit is not specified.
 */
#define XMLSEC_XKMS_NO_RESPONSE_LIMIT			-1

/************************************************************************
 *
 * XKMS RespondWith Klass
 *
 ************************************************************************/ 
XMLSEC_EXPORT xmlSecPtrListPtr	xmlSecXkmsRespondWithIdsGet	(void);
XMLSEC_EXPORT int 		xmlSecXkmsRespondWithIdsInit	(void);
XMLSEC_EXPORT void 		xmlSecXkmsRespondWithIdsShutdown(void);
XMLSEC_EXPORT int 		xmlSecXkmsRespondWithIdsRegisterDefault(void);
XMLSEC_EXPORT int		xmlSecXkmsRespondWithIdsRegister(xmlSecXkmsRespondWithId id);

XMLSEC_EXPORT int  		xmlSecXkmsRespondWithReadNode	(xmlSecXkmsRespondWithId id,
								 xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);
XMLSEC_EXPORT int  		xmlSecXkmsRespondWithWriteNode	(xmlSecXkmsRespondWithId id,
								 xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);
XMLSEC_EXPORT void		xmlSecXkmsRespondWithDebugDump	(xmlSecXkmsRespondWithId id,
								 FILE* output);
XMLSEC_EXPORT void		xmlSecXkmsRespondWithDebugXmlDump(xmlSecXkmsRespondWithId id,
								 FILE* output);
XMLSEC_EXPORT int  		xmlSecXkmsRespondWithDefaultReadNode(xmlSecXkmsRespondWithId id,
								 xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);
XMLSEC_EXPORT int  		xmlSecXkmsRespondWithDefaultWriteNode(xmlSecXkmsRespondWithId id,
								 xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);

typedef int  		(*xmlSecXkmsRespondWithReadNodeMethod)	(xmlSecXkmsRespondWithId id,
								 xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);
typedef int  		(*xmlSecXkmsRespondWithWriteNodeMethod)	(xmlSecXkmsRespondWithId id,
								 xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);
struct _xmlSecXkmsRespondWithKlass {
    const xmlChar*				name;
    const xmlChar*				nodeName;
    const xmlChar*				nodeNs;
    
    xmlSecXkmsRespondWithReadNodeMethod		readNode;
    xmlSecXkmsRespondWithWriteNodeMethod	writeNode;
};

#define xmlSecXkmsRespondWithKlassGetName(id) \
	((((id) != NULL) && ((id)->name != NULL)) ? (id)->name : NULL)

/************************************************************************
 *
 * XKMS RespondWith Klass List
 *
 ************************************************************************/ 
/**
 * xmlSecXkmsRespondWithIdListId:
 *
 * XKMS RespondWith  klasses list klass.
 */
#define xmlSecXkmsRespondWithIdListId	xmlSecXkmsRespondWithIdListGetKlass()
XMLSEC_EXPORT xmlSecPtrListId	xmlSecXkmsRespondWithIdListGetKlass(void);
XMLSEC_EXPORT int		xmlSecXkmsRespondWithIdListFind	(xmlSecPtrListPtr list,
								 xmlSecXkmsRespondWithId id);
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithIdListFindByName
								(xmlSecPtrListPtr list,
								 const xmlChar* name);
XMLSEC_EXPORT int		xmlSecXkmsRespondWithIdListWrite(xmlSecPtrListPtr list,
								 xmlSecXkmsServerCtxPtr ctx,
								 xmlNodePtr node);

/******************************************************************** 
 *
 * XML Sec Library RespondWith Ids
 *
 *******************************************************************/
/**
 * xmlSecXkmsRespondWithIdUnknown:
 *
 * The "unknown" RespondWith id (NULL).
 */
#define xmlSecXkmsRespondWithIdUnknown			NULL

/**
 * xmlSecXkmsRespondWithKeyNameId:
 *
 * The respond with KeyName klass.
 */ 
#define xmlSecXkmsRespondWithKeyNameId \
	xmlSecXkmsRespondWithKeyNameGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithKeyNameGetKlass(void);

/**
 * xmlSecXkmsRespondWithKeyValueId:
 *
 * The respond with KeyValue klass.
 */ 
#define xmlSecXkmsRespondWithKeyValueId \
	xmlSecXkmsRespondWithKeyValueGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithKeyValueGetKlass(void);

/**
 * xmlSecXkmsRespondWithPrivateKeyId:
 *
 * The respond with PrivateKey klass.
 */ 
#define xmlSecXkmsRespondWithPrivateKeyId \
	xmlSecXkmsRespondWithPrivateKeyGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithPrivateKeyGetKlass(void);

/**
 * xmlSecXkmsRespondWithRetrievalMethodId:
 *
 * The respond with RetrievalMethod klass.
 */ 
#define xmlSecXkmsRespondWithRetrievalMethodId \
	xmlSecXkmsRespondWithRetrievalMethodGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithRetrievalMethodGetKlass(void);

/**
 * xmlSecXkmsRespondWithX509CertId:
 *
 * The respond with X509Cert klass.
 */ 
#define xmlSecXkmsRespondWithX509CertId \
	xmlSecXkmsRespondWithX509CertGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithX509CertGetKlass(void);

/**
 * xmlSecXkmsRespondWithX509ChainId:
 *
 * The respond with X509Chain klass.
 */ 
#define xmlSecXkmsRespondWithX509ChainId \
	xmlSecXkmsRespondWithX509ChainGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithX509ChainGetKlass(void);

/**
 * xmlSecXkmsRespondWithX509CRLId:
 *
 * The respond with X509CRL klass.
 */ 
#define xmlSecXkmsRespondWithX509CRLId \
	xmlSecXkmsRespondWithX509CRLGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithX509CRLGetKlass(void);


/**
 * xmlSecXkmsRespondWithPGPId:
 *
 * The respond with PGP klass.
 */ 
#define xmlSecXkmsRespondWithPGPId \
	xmlSecXkmsRespondWithPGPGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithPGPGetKlass(void);

/**
 * xmlSecXkmsRespondWithSPKIId:
 *
 * The respond with SPKI klass.
 */ 
#define xmlSecXkmsRespondWithSPKIId \
	xmlSecXkmsRespondWithSPKIGetKlass()
XMLSEC_EXPORT xmlSecXkmsRespondWithId	xmlSecXkmsRespondWithSPKIGetKlass(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XMLSEC_NO_XKMS */

#endif /* __XMLSEC_XKMS_H__ */

