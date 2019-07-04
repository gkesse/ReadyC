/* soapServer.c
   Generated by gSOAP 2.8.14 from srv/service.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"
#ifdef __cplusplus
extern "C" {
#endif

SOAP_SOURCE_STAMP("@(#) soapServer.c ver 2.8.14 2019-07-03 20:43:58 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	unsigned int k = soap->max_keep_alive;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (soap->max_keep_alive > 0 && !--k)
			soap->keep_alive = 0;
#endif
		if (soap_begin_serve(soap))
		{	if (soap->error >= SOAP_STOP)
				continue;
			return soap->error;
		}
		if (soap_serve_request(soap) || (soap->fserveloop && soap->fserveloop(soap)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(soap);
#else
			return soap_send_fault(soap);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(soap);
		soap_end(soap);
	} while (1);
#else
	} while (soap->keep_alive);
#endif
	return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:add"))
		return soap_serve_ns__add(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:subtract"))
		return soap_serve_ns__subtract(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:multiply"))
		return soap_serve_ns__multiply(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:divide"))
		return soap_serve_ns__divide(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__add(struct soap *soap)
{	struct ns__add soap_tmp_ns__add;
	struct ns__addResponse soap_tmp_ns__addResponse;
	int soap_tmp_int;
	soap_default_ns__addResponse(soap, &soap_tmp_ns__addResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__addResponse.result = &soap_tmp_int;
	soap_default_ns__add(soap, &soap_tmp_ns__add);
	soap->encodingStyle = NULL;
	if (!soap_get_ns__add(soap, &soap_tmp_ns__add, "ns:add", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__add(soap, soap_tmp_ns__add.a, soap_tmp_ns__add.b, soap_tmp_ns__addResponse.result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__addResponse(soap, &soap_tmp_ns__addResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__addResponse(soap, &soap_tmp_ns__addResponse, "ns:addResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__addResponse(soap, &soap_tmp_ns__addResponse, "ns:addResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__subtract(struct soap *soap)
{	struct ns__subtract soap_tmp_ns__subtract;
	struct ns__subtractResponse soap_tmp_ns__subtractResponse;
	int soap_tmp_int;
	soap_default_ns__subtractResponse(soap, &soap_tmp_ns__subtractResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__subtractResponse.result = &soap_tmp_int;
	soap_default_ns__subtract(soap, &soap_tmp_ns__subtract);
	soap->encodingStyle = NULL;
	if (!soap_get_ns__subtract(soap, &soap_tmp_ns__subtract, "ns:subtract", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__subtract(soap, soap_tmp_ns__subtract.a, soap_tmp_ns__subtract.b, soap_tmp_ns__subtractResponse.result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__subtractResponse(soap, &soap_tmp_ns__subtractResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__subtractResponse(soap, &soap_tmp_ns__subtractResponse, "ns:subtractResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__subtractResponse(soap, &soap_tmp_ns__subtractResponse, "ns:subtractResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__multiply(struct soap *soap)
{	struct ns__multiply soap_tmp_ns__multiply;
	struct ns__multiplyResponse soap_tmp_ns__multiplyResponse;
	int soap_tmp_int;
	soap_default_ns__multiplyResponse(soap, &soap_tmp_ns__multiplyResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__multiplyResponse.result = &soap_tmp_int;
	soap_default_ns__multiply(soap, &soap_tmp_ns__multiply);
	soap->encodingStyle = NULL;
	if (!soap_get_ns__multiply(soap, &soap_tmp_ns__multiply, "ns:multiply", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__multiply(soap, soap_tmp_ns__multiply.a, soap_tmp_ns__multiply.b, soap_tmp_ns__multiplyResponse.result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__multiplyResponse(soap, &soap_tmp_ns__multiplyResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__multiplyResponse(soap, &soap_tmp_ns__multiplyResponse, "ns:multiplyResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__multiplyResponse(soap, &soap_tmp_ns__multiplyResponse, "ns:multiplyResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__divide(struct soap *soap)
{	struct ns__divide soap_tmp_ns__divide;
	struct ns__divideResponse soap_tmp_ns__divideResponse;
	int soap_tmp_int;
	soap_default_ns__divideResponse(soap, &soap_tmp_ns__divideResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__divideResponse.result = &soap_tmp_int;
	soap_default_ns__divide(soap, &soap_tmp_ns__divide);
	soap->encodingStyle = NULL;
	if (!soap_get_ns__divide(soap, &soap_tmp_ns__divide, "ns:divide", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__divide(soap, soap_tmp_ns__divide.a, soap_tmp_ns__divide.b, soap_tmp_ns__divideResponse.result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__divideResponse(soap, &soap_tmp_ns__divideResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__divideResponse(soap, &soap_tmp_ns__divideResponse, "ns:divideResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__divideResponse(soap, &soap_tmp_ns__divideResponse, "ns:divideResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

#ifdef __cplusplus
}
#endif

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapServer.c */
