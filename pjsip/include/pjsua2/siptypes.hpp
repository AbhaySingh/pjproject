/* $Id$ */
/*
 * Copyright (C) 2032 Teluu Inc. (http://www.teluu.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __PJSUA2_SIPTYPES_HPP__
#define __PJSUA2_SIPTYPES_HPP__

/**
 * @file pjsua2/types.hpp
 * @brief PJSUA2 Base Types
 */
#include <pjsua2/types.hpp>
#include <pjsua2/persistent.hpp>

#include <string>
#include <vector>

/**
 * @defgroup PJSUA2_TYPES Data structure
 * @ingroup PJSUA2_Ref
 * @{
 */

/** PJSUA2 API is inside pj namespace */
namespace pj
{

/**
 * Credential information. Credential contains information to authenticate
 * against a service.
 */
struct AuthCredInfo : public PersistentObject
{
    /**
     * The authentication scheme (e.g. "digest").
     */
    string	scheme;

    /**
     * Realm on which this credential is to be used. Use "*" to make
     * a credential that can be used to authenticate against any challenges.
     */
    string	realm;

    /**
     * Authentication user name.
     */
    string	username;

    /**
     * Type of data that is contained in the "data" field. Use 0 if the data
     * contains plain text password.
     */
    int		dataType;

    /**
     * The data, which can be a plain text password or a hashed digest.
     */
    string	data;

    /*
     * Digest AKA credential information. Note that when AKA credential
     * is being used, the \a data field of this #pjsip_cred_info is
     * not used, but it still must be initialized to an empty string.
     * Please see \ref PJSIP_AUTH_AKA_API for more information.
     */

    /** Permanent subscriber key. */
    string	akaK;

    /** Operator variant key. */
    string	akaOp;

    /** Authentication Management Field	*/
    string	akaAmf;

public:
    /** Default constructor */
    AuthCredInfo();

    /** Construct a credential with the specified parameters */
    AuthCredInfo(const string &scheme,
                 const string &realm,
                 const string &user_name,
                 const int data_type,
                 const string data);

    /**
     * Read this object from a container node.
     *
     * @param node		Container to read values from.
     */
    virtual void readObject(const ContainerNode &node) throw(Error);

    /**
     * Write this object to a container node.
     *
     * @param node		Container to write values to.
     */
    virtual void writeObject(ContainerNode &node) const throw(Error);
};


//////////////////////////////////////////////////////////////////////////////

/**
 * TLS transport settings, to be specified in TransportConfig.
 */
struct TlsConfig : public PersistentObject
{
    /**
     * Certificate of Authority (CA) list file.
     */
    string		CaListFile;

    /**
     * Public endpoint certificate file, which will be used as client-
     * side  certificate for outgoing TLS connection, and server-side
     * certificate for incoming TLS connection.
     */
    string		certFile;

    /**
     * Optional private key of the endpoint certificate to be used.
     */
    string		privKeyFile;

    /**
     * Password to open private key.
     */
    string		password;

    /**
     * TLS protocol method from #pjsip_ssl_method.
     *
     * Default is PJSIP_SSL_UNSPECIFIED_METHOD (0), which in turn will
     * use PJSIP_SSL_DEFAULT_METHOD, which default value is
     * PJSIP_TLSV1_METHOD.
     */
    pjsip_ssl_method	method;

    /**
     * Ciphers and order preference. The Endpoint::utilSslGetAvailableCiphers()
     * can be used to check the available ciphers supported by backend.
     * If the array is empty, then default cipher list of the backend
     * will be used.
     */
    IntVector		ciphers;

    /**
     * Specifies TLS transport behavior on the server TLS certificate
     * verification result:
     * - If \a verifyServer is disabled, TLS transport will just notify
     *   the application via #pjsip_tp_state_callback with state
     *   PJSIP_TP_STATE_CONNECTED regardless TLS verification result.
     * - If \a verifyServer is enabled, TLS transport will be shutdown
     *   and application will be notified with state
     *   PJSIP_TP_STATE_DISCONNECTED whenever there is any TLS verification
     *   error, otherwise PJSIP_TP_STATE_CONNECTED will be notified.
     *
     * In any cases, application can inspect #pjsip_tls_state_info in the
     * callback to see the verification detail.
     *
     * Default value is false.
     */
    bool		verifyServer;

    /**
     * Specifies TLS transport behavior on the client TLS certificate
     * verification result:
     * - If \a verifyClient is disabled, TLS transport will just notify
     *   the application via #pjsip_tp_state_callback with state
     *   PJSIP_TP_STATE_CONNECTED regardless TLS verification result.
     * - If \a verifyClient is enabled, TLS transport will be shutdown
     *   and application will be notified with state
     *   PJSIP_TP_STATE_DISCONNECTED whenever there is any TLS verification
     *   error, otherwise PJSIP_TP_STATE_CONNECTED will be notified.
     *
     * In any cases, application can inspect #pjsip_tls_state_info in the
     * callback to see the verification detail.
     *
     * Default value is PJ_FALSE.
     */
    bool		verifyClient;

    /**
     * When acting as server (incoming TLS connections), reject incoming
     * connection if client doesn't supply a TLS certificate.
     *
     * This setting corresponds to SSL_VERIFY_FAIL_IF_NO_PEER_CERT flag.
     * Default value is PJ_FALSE.
     */
    bool		requireClientCert;

    /**
     * TLS negotiation timeout to be applied for both outgoing and incoming
     * connection, in milliseconds. If zero, the SSL negotiation doesn't
     * have a timeout.
     *
     * Default: zero
     */
    unsigned		msecTimeout;

    /**
     * QoS traffic type to be set on this transport. When application wants
     * to apply QoS tagging to the transport, it's preferable to set this
     * field rather than \a qosParam fields since this is more portable.
     *
     * Default value is PJ_QOS_TYPE_BEST_EFFORT.
     */
    pj_qos_type 	qosType;

    /**
     * Set the low level QoS parameters to the transport. This is a lower
     * level operation than setting the \a qosType field and may not be
     * supported on all platforms.
     *
     * By default all settings in this structure are disabled.
     */
    pj_qos_params 	qosParams;

    /**
     * Specify if the transport should ignore any errors when setting the QoS
     * traffic type/parameters.
     *
     * Default: PJ_TRUE
     */
    bool		qosIgnoreError;

public:
    /** Default constructor initialises with default values */
    TlsConfig();

    /** Convert to pjsip */
    pjsip_tls_setting toPj() const;

    /** Convert from pjsip */
    void fromPj(const pjsip_tls_setting &prm);

    /**
     * Read this object from a container node.
     *
     * @param node		Container to read values from.
     */
    virtual void readObject(const ContainerNode &node) throw(Error);

    /**
     * Write this object to a container node.
     *
     * @param node		Container to write values to.
     */
    virtual void writeObject(ContainerNode &node) const throw(Error);
};


/**
 * Parameters to create a transport instance.
 */
struct TransportConfig : public PersistentObject
{
    /**
     * UDP port number to bind locally. This setting MUST be specified
     * even when default port is desired. If the value is zero, the
     * transport will be bound to any available port, and application
     * can query the port by querying the transport info.
     */
    unsigned		port;

    /**
     * Specify the port range for socket binding, relative to the start
     * port number specified in \a port. Note that this setting is only
     * applicable when the start port number is non zero.
     *
     * Default value is zero.
     */
    unsigned		portRange;

    /**
     * Optional address to advertise as the address of this transport.
     * Application can specify any address or hostname for this field,
     * for example it can point to one of the interface address in the
     * system, or it can point to the public address of a NAT router
     * where port mappings have been configured for the application.
     *
     * Note: this option can be used for both UDP and TCP as well!
     */
    string		publicAddress;

    /**
     * Optional address where the socket should be bound to. This option
     * SHOULD only be used to selectively bind the socket to particular
     * interface (instead of 0.0.0.0), and SHOULD NOT be used to set the
     * published address of a transport (the public_addr field should be
     * used for that purpose).
     *
     * Note that unlike public_addr field, the address (or hostname) here
     * MUST correspond to the actual interface address in the host, since
     * this address will be specified as bind() argument.
     */
    string		boundAddress;

    /**
     * This specifies TLS settings for TLS transport. It is only be used
     * when this transport config is being used to create a SIP TLS
     * transport.
     */
    TlsConfig		tlsConfig;

    /**
     * QoS traffic type to be set on this transport. When application wants
     * to apply QoS tagging to the transport, it's preferable to set this
     * field rather than \a qosParam fields since this is more portable.
     *
     * Default is QoS not set.
     */
    pj_qos_type		qosType;

    /**
     * Set the low level QoS parameters to the transport. This is a lower
     * level operation than setting the \a qosType field and may not be
     * supported on all platforms.
     *
     * Default is QoS not set.
     */
    pj_qos_params	qosParams;

public:
    /** Default constructor initialises with default values */
    TransportConfig();

    /** Convert from pjsip */
    void fromPj(const pjsua_transport_config &prm);

    /** Convert to pjsip */
    pjsua_transport_config toPj() const;

    /**
     * Read this object from a container node.
     *
     * @param node		Container to read values from.
     */
    virtual void readObject(const ContainerNode &node) throw(Error);

    /**
     * Write this object to a container node.
     *
     * @param node		Container to write values to.
     */
    virtual void writeObject(ContainerNode &node) const throw(Error);
};

/**
 * This structure describes transport information returned by
 * Endpoint::transportGetInfo() function.
 */
struct TransportInfo
{
    /** PJSUA transport identification. */
    TransportId	    	    id;

    /** Transport type. */
    pjsip_transport_type_e  type;

    /** Transport type name. */
    string		    typeName;

    /** Transport string info/description. */
    string		    info;

    /** Transport flags (see #pjsip_transport_flags_e). */
    unsigned		    flags;

    /** Local/bound address. */
    SocketAddress	    localAddress;

    /** Published address (or transport address name). */
    SocketAddress	    localName;

    /** Current number of objects currently referencing this transport. */
    unsigned		    usageCount;

    /** Construct from pjsip */
    TransportInfo(const pjsua_transport_info &info);

};

//////////////////////////////////////////////////////////////////////////////

/**
 * This structure describes an incoming SIP message. It corresponds to the
 * pjsip_rx_data structure in PJSIP library.
 */
struct SipRxData
{
    /**
     * A short info string describing the request, which normally contains
     * the request method and its CSeq.
     */
    string		info;

    /**
     * The whole message data as a string, containing both the header section
     * and message body section.
     */
    string		wholeMsg;

    /**
     * Source IP address of the message.
     */
    string		srcIp;

    /**
     * Source port number of the message.
     */
    unsigned		srcPort;

    /**
     * Construct from PJSIP's pjsip_rx_data
     */
    void fromPj(pjsip_rx_data &rdata);
};


//////////////////////////////////////////////////////////////////////////////

/**
 * SIP media type containing type and subtype. For example, for
 * "application/sdp", the type is "application" and the subtype is "sdp".
 */
struct SipMediaType
{
    /** Media type. */
    string		type;

    /** Media subtype. */
    string		subType;

    /**
     * Construct from PJSIP's pjsip_media_type
     */
    void fromPj(const pjsip_media_type &prm);

    /**
     * Convert to PJSIP's pjsip_media_type.
     */
    pjsip_media_type toPj() const;
};

/**
 * Simple SIP header.
 */
struct SipHeader
{
    /**
     * Header name.
     */
    string		hName;

    /**
     * Header value.
     */
    string		hValue;

    /**
     * Initiaize from PJSIP header.
     */
    void fromPj(const pjsip_hdr *) throw(Error);

    /**
     * Convert to PJSIP header.
     */
    pjsip_generic_string_hdr &toPj() const;

private:
    /** Interal buffer for conversion to PJSIP header */
    mutable pjsip_generic_string_hdr	pjHdr;
};


/** Array of strings */
typedef std::vector<SipHeader> SipHeaderVector;

/**
 * This describes each multipart part.
 */
struct SipMultipartPart
{
    /**
     * Optional headers to be put in this multipart part.
     */
    SipHeaderVector	headers;

    /**
     * The MIME type of the body part of this multipart part.
     */
    SipMediaType	contentType;

    /**
     * The body part of tthis multipart part.
     */
    string		body;

    /**
     * Initiaize from PJSIP's pjsip_multipart_part.
     */
    void fromPj(const pjsip_multipart_part &prm) throw(Error);

    /**
     * Convert to PJSIP's pjsip_multipart_part.
     */
    pjsip_multipart_part& toPj() const;

private:
    /** Interal buffer for conversion to PJSIP pjsip_multipart_part */
    mutable pjsip_multipart_part	pjMpp;
    mutable pjsip_msg_body		pjMsgBody;
};

/** Array of multipart parts */
typedef std::vector<SipMultipartPart> SipMultipartPartVector;

/**
 * Additional options when sending outgoing SIP message. This corresponds to
 * pjsua_msg_data structure in PJSIP library.
 */
struct SipTxOption
{
    /**
     * Optional remote target URI (i.e. Target header). If NULL, the target
     * will be set to the remote URI (To header). At the moment this field
     * is only used when sending initial INVITE and MESSAGE requests.
     */
    string		targetUri;

    /**
     * Additional message headers to be included in the outgoing message.
     */
    SipHeaderVector	headers;

    /**
     * MIME type of the message body, if application specifies the messageBody
     * in this structure.
     */
    string		contentType;

    /**
     * Optional message body to be added to the message, only when the
     * message doesn't have a body.
     */
    string		msgBody;

    /**
     * Content type of the multipart body. If application wants to send
     * multipart message bodies, it puts the parts in multipartParts and set
     * the content type in multipartContentType. If the message already
     * contains a body, the body will be added to the multipart bodies.
     */
    SipMediaType	multipartContentType;

    /**
     * Array of multipart parts. If application wants to send multipart
     * message bodies, it puts the parts in \a parts and set the content
     * type in \a multipart_ctype. If the message already contains a body,
     * the body will be added to the multipart bodies.
     */
    SipMultipartPartVector	multipartParts;

    /**
     * Initiaize from PJSUA's pjsua_msg_data.
     */
    void fromPj(const pjsua_msg_data &prm) throw(Error);

    /**
     * Convert to PJSUA's pjsua_msg_data.
     */
    void toPj(pjsua_msg_data &msg_data) const;
};


/* Utilities */
#ifndef SWIG
void readIntVector( ContainerNode &node,
                    const string &array_name,
                    IntVector &v) throw(Error);
void writeIntVector(ContainerNode &node,
                    const string &array_name,
                    const IntVector &v) throw(Error);
void readQosParams( ContainerNode &node,
                    pj_qos_params &qos) throw(Error);
void writeQosParams( ContainerNode &node,
                     const pj_qos_params &qos) throw(Error);
void readSipHeaders( const ContainerNode &node,
                     const string &array_name,
                     SipHeaderVector &headers) throw(Error);
void writeSipHeaders(ContainerNode &node,
                     const string &array_name,
                     const SipHeaderVector &headers) throw(Error);
#endif // SWIG

} // namespace pj

/**
 * @}  PJSUA2
 */



#endif	/* __PJSUA2_SIPTYPES_HPP__ */
