/***************************************************************************
  tag: The SourceWorks  Tue Sep 7 00:55:18 CEST 2010  TaskContextI.cpp

                        TaskContextI.cpp -  description
                           -------------------
    begin                : Tue September 07 2010
    copyright            : (C) 2010 The SourceWorks
    email                : peter@thesourceworks.com

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU General Public                   *
 *   License as published by the Free Software Foundation;                 *
 *   version 2 of the License.                                             *
 *                                                                         *
 *   As a special exception, you may use this file as part of a free       *
 *   software library without restriction.  Specifically, if other files   *
 *   instantiate templates or use macros or inline functions from this     *
 *   file, or you compile this file and link it with other files to        *
 *   produce an executable, this file does not by itself cause the         *
 *   resulting executable to be covered by the GNU General Public          *
 *   License.  This exception does not however invalidate any other        *
 *   reasons why the executable file might be covered by the GNU General   *
 *   Public License.                                                       *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public             *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/


// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1196

#include "TaskContextI.h"
#include "TaskContextServer.hpp"
#include "TaskContextProxy.hpp"
#include "ServiceI.h"
#include "ServiceRequesterI.h"
#include "DataFlowI.h"
#include "../../OperationCaller.hpp"
#include "../../rtt-detail-fwd.hpp"


using namespace RTT;
using namespace RTT::detail;
using namespace RTT::corba;

// Implementation skeleton constructor
RTT_corba_CTaskContext_i::RTT_corba_CTaskContext_i (RTT::TaskContext* orig, PortableServer::POA_ptr the_poa)
    : mpoa( PortableServer::POA::_duplicate(the_poa) )
    , mtask( orig ), mRequest_i(0), mService_i(0)
{
    // Add the corba object to the interface:
    mtask->addOperation("shutdown", &RTT_corba_CTaskContext_i::shutdownCORBA, this).doc("Shutdown CORBA ORB. This function makes RunOrb() return.");
}

// Implementation skeleton destructor
RTT_corba_CTaskContext_i::~RTT_corba_CTaskContext_i (void)
{
    //CDataFlowInterface_i::deregisterServant(mtask->ports()); causes invalid read (freed already)
}

void RTT_corba_CTaskContext_i::shutdownCORBA() {
    TaskContextServer::ShutdownOrb(false);
}

char * RTT_corba_CTaskContext_i::getName (
    void)
{
    return CORBA::string_dup( mtask->getName().c_str() );
}

char * RTT_corba_CTaskContext_i::getDescription (
    void)
{
    return CORBA::string_dup( mtask->provides()->doc().c_str() );
}

::RTT::corba::CTaskState RTT_corba_CTaskContext_i::getTaskState (
    void)
{
    return ::RTT::corba::CTaskState(mtask->getTaskState());
}

::CORBA::Boolean RTT_corba_CTaskContext_i::configure (
    void)
{
    return mtask->configure();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::start (
    void)
{
    return mtask->start();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::activate (
    void)
{
    return mtask->activate();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::stop (
    void)
{
    return mtask->stop();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::cleanup (
    void)
{
    return mtask->cleanup();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::resetException (
    void)
{
    if (mtask->getTaskState() == RTT::TaskContext::Exception)
        return mtask->recover();
    return false;
}

::CORBA::Boolean RTT_corba_CTaskContext_i::isActive (
    void)
{
    return mtask->isActive();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::isRunning (
    void)
{
    return mtask->isRunning();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::isConfigured (
    void)
{
    return mtask->isConfigured();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::inFatalError (
    void)
{
    return mtask->inFatalError();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::inRunTimeError (
    void)
{
    return mtask->inRunTimeError();
}

::RTT::corba::CDataFlowInterface_ptr RTT_corba_CTaskContext_i::ports (
    void)
{
    return getProvider("this");
}

::RTT::corba::CService_ptr RTT_corba_CTaskContext_i::getProvider (
    const char * service_name)
{
    if ( mtask->provides()->hasService(service_name) == false)
        return CService::_nil();
    // Creates Service for "this"
    if ( CORBA::is_nil( mService ) ) {
        log(Debug) << "Creating CService for "<< mtask->getName()<<endlog();
        RTT_corba_CService_i* mserv;
        mService_i = mserv = new RTT_corba_CService_i( mtask->provides(), mpoa );
        mService = mserv->activate_this();
        CDataFlowInterface_i::registerServant(CDataFlowInterface::_narrow(mService), mserv);
    }
    // Now the this service is available, check for the service name:
    std::string svc(service_name);
    if ( svc == "this" )
        return ::RTT::corba::CService::_duplicate( mService.in() );
    return mService->getService( service_name );
}

::RTT::corba::CServiceRequester_ptr RTT_corba_CTaskContext_i::getRequester (
    const char * service_name)
{
    std::string svc(service_name);
    if ( mtask->requires()->requiresService(service_name) == false && svc != "this")
        return CServiceRequester::_nil();
    // Creates service requester for "this"
    if ( CORBA::is_nil( mRequest ) ) {
        log(Debug) << "Creating CServiceRequester for "<< mtask->getName()<<endlog();
        RTT_corba_CServiceRequester_i* mserv;
        mRequest_i = mserv = new RTT_corba_CServiceRequester_i( mtask->requires(), mpoa );
        mRequest = mserv->activate_this();
        //CServiceRequester_i::registerServant(mRequest, mtask->requires());
    }
    // Now the this service is available, check for the service name:
    if ( svc == "this" )
        return ::RTT::corba::CServiceRequester::_duplicate( mRequest.in() );
    return mRequest->getRequest( service_name );
}

::RTT::corba::CTaskContext::CPeerNames * RTT_corba_CTaskContext_i::getPeerList (
    void)
{
    TaskContext::PeerList peers = mtask->getPeerList();
    ::RTT::corba::CTaskContext::CPeerNames_var result = new ::RTT::corba::CTaskContext::CPeerNames();
    result->length( peers.size() );
    for (unsigned int i=0; i != peers.size(); ++i )
        result[i] = CORBA::string_dup( peers[i].c_str() );

    return result._retn();
}

::RTT::corba::CTaskContext_ptr RTT_corba_CTaskContext_i::getPeer (
    const char * name)
{
    std::string pname(name);
    TaskContext* task = mtask->getPeer( pname );
    if ( task ) {
        // create or lookup new server for this peer.
        // do not export it to the naming service.
        return TaskContextServer::CreateServer( task, false );
    }
    return RTT::corba::CTaskContext::_nil();
}

::CORBA::Boolean RTT_corba_CTaskContext_i::hasPeer (
    const char * name)
{
    std::string mname(name);
    return mtask->hasPeer(mname);
}

::CORBA::Boolean RTT_corba_CTaskContext_i::addPeer (
    ::RTT::corba::CTaskContext_ptr p,
    const char * alias)
{
    std::string malias(alias);
    if (mtask->hasPeer(alias) == false )
        return mtask->addPeer( TaskContextProxy::Create(p), alias );
    return false;
}

::CORBA::Boolean RTT_corba_CTaskContext_i::removePeer (
    const char * name)
{
    std::string mname(name);
    mtask->removePeer( mname );
    return true;
}

::CORBA::Boolean RTT_corba_CTaskContext_i::connectPeers (
    ::RTT::corba::CTaskContext_ptr p)
{
    TaskContext* t = TaskContextProxy::Create( p );
    return mtask->connectPeers( t );
}

::CORBA::Boolean RTT_corba_CTaskContext_i::disconnectPeers (
    const char * name)
{
    std::string pname(name);
    mtask->disconnectPeers( pname );
    return true;
}

::CORBA::Boolean RTT_corba_CTaskContext_i::connectPorts (
    ::RTT::corba::CTaskContext_ptr p)
{
    TaskContext* t = TaskContextProxy::Create( p );
    return mtask->connectPorts( t );
}

::CORBA::Boolean RTT_corba_CTaskContext_i::connectServices (
    ::RTT::corba::CTaskContext_ptr p)
{
    TaskContext* t = TaskContextProxy::Create( p );
    return mtask->connectServices( t );
}


