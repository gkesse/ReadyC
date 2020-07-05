/* soapStub.h
   Generated by gSOAP 2.7.13 from srv/service.h
   Copyright(C) 2000-2009, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not redeclare here */

#endif

#ifndef SOAP_TYPE_ns__addResponse
#define SOAP_TYPE_ns__addResponse (10)
/* ns:addResponse */
struct ns__addResponse
{
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__add
#define SOAP_TYPE_ns__add (11)
/* ns:add */
struct ns__add
{
	double a;	/* required element of type xsd:double */
	double b;	/* required element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__subResponse
#define SOAP_TYPE_ns__subResponse (13)
/* ns:subResponse */
struct ns__subResponse
{
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__sub
#define SOAP_TYPE_ns__sub (14)
/* ns:sub */
struct ns__sub
{
	double a;	/* required element of type xsd:double */
	double b;	/* required element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__mulResponse
#define SOAP_TYPE_ns__mulResponse (16)
/* ns:mulResponse */
struct ns__mulResponse
{
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__mul
#define SOAP_TYPE_ns__mul (17)
/* ns:mul */
struct ns__mul
{
	double a;	/* required element of type xsd:double */
	double b;	/* required element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__divResponse
#define SOAP_TYPE_ns__divResponse (19)
/* ns:divResponse */
struct ns__divResponse
{
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__div
#define SOAP_TYPE_ns__div (20)
/* ns:div */
struct ns__div
{
	double a;	/* required element of type xsd:double */
	double b;	/* required element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__powResponse
#define SOAP_TYPE_ns__powResponse (22)
/* ns:powResponse */
struct ns__powResponse
{
	double *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_ns__pow
#define SOAP_TYPE_ns__pow (23)
/* ns:pow */
struct ns__pow
{
	double a;	/* required element of type xsd:double */
	double b;	/* required element of type xsd:double */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (24)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (25)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (27)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
	char *__any;
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (30)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (31)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operations                                                         *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 ns__add(struct soap*, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__sub(struct soap*, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__mul(struct soap*, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__div(struct soap*, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__pow(struct soap*, double a, double b, double *result);

/******************************************************************************\
 *                                                                            *
 * Stubs                                                                      *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__add(struct soap *soap, const char *soap_endpoint, const char *soap_action, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__sub(struct soap *soap, const char *soap_endpoint, const char *soap_action, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__mul(struct soap *soap, const char *soap_endpoint, const char *soap_action, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__div(struct soap *soap, const char *soap_endpoint, const char *soap_action, double a, double b, double *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__pow(struct soap *soap, const char *soap_endpoint, const char *soap_action, double a, double b, double *result);

/******************************************************************************\
 *                                                                            *
 * Skeletons                                                                  *
 *                                                                            *
\******************************************************************************/

SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__add(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__sub(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__mul(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__div(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__pow(struct soap*);

#ifdef __cplusplus
}
#endif

#endif

/* End of soapStub.h */
