%module(directors="1") pjsua2

//
// Suppress few warnings
//
#pragma SWIG nowarn=312		// 312: nested struct (in types.h, sip_auth.h)

//
// Header section
//
%{
#include "pjsua2.hpp"
using namespace std;
using namespace pj;
%}

#ifdef SWIGPYTHON
  %feature("director:except") {
    if( $error != NULL ) {
      PyObject *ptype, *pvalue, *ptraceback;
      PyErr_Fetch( &ptype, &pvalue, &ptraceback );
      PyErr_Restore( ptype, pvalue, ptraceback );
      PyErr_Print();
      //Py_Exit(1);
    }
  }
#endif

// Constants from PJSIP libraries
%include "symbols.i"


//
// Classes that can be extended in the target language
//
%feature("director") LogWriter;
%feature("director") Endpoint; 
%feature("director") Account;
%feature("director") Buddy;
%feature("director") FindBuddyMatch;


//
// STL stuff.
//
%include "std_string.i"
%include "std_vector.i"


%template(StringVector)			std::vector<std::string>;
%template(IntVector) 			std::vector<int>;

//
// Ignore stuffs in pjsua2
//
%ignore fromPj;
%ignore toPj;

//
// Now include the API itself.
//
%include "pjsua2/types.hpp"

%ignore pj::ContainerNode::op;
%ignore pj::ContainerNode::data;
%ignore container_node_op;
%ignore container_node_internal_data;
%include "pjsua2/persistent.hpp"

%ignore pj::TransportInfo::TransportInfo(const pjsua_transport_info &info);
%include "pjsua2/siptypes.hpp"

%template(SipHeaderVector)		std::vector<pj::SipHeader>;
%template(AuthCredInfoVector)		std::vector<pj::AuthCredInfo>;
%template(SipMultipartPartVector)	std::vector<pj::SipMultipartPart>;
%template(BuddyVector)			std::vector<pj::Buddy*>;

%include "pjsua2/endpoint.hpp"
%include "pjsua2/presence.hpp"
%include "pjsua2/account.hpp"

%ignore pj::JsonDocument::allocElement;
%ignore pj::JsonDocument::getPool;
%include "pjsua2/json.hpp"
