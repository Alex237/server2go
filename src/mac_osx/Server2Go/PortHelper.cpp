/*
 *  PortHelper.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "PortHelper.h"
#include <wx/wx.h>
#include "wx/socket.h"

long PortHelper::getFreeWebserverPort(wxString hostname, long configValue)
{
	//--- if the default value is already used check an array
	//--- with possible values
	int apachePorts[] = {configValue, 80, 81, 8080, 8081, 82, 8282, 8082, 8083};
	
	for (int i = 0; i < sizeof(apachePorts); i++)
	{
		if (true == PortHelper::checkPort(hostname, apachePorts[i]))
		{
			return apachePorts[i];
		}
	}
	
	return -1;
}

long PortHelper::getFreeMySqlPort(wxString hostname, long configValue)
{
	//--- if the default value is already used check an array
	//--- with possible values
	int mysqlPorts[] = {configValue, 3306, 7188, 7189, 7190, 7191, 7192, 7193, 7194};
	
	for (int i = 0; i < sizeof(mysqlPorts); i++)
	{
		if (true == PortHelper::checkPort(hostname, mysqlPorts[i]))
		{
			return mysqlPorts[i];
		}
	}
	
	return -1;
}

bool PortHelper::checkPort(wxString hostname, long port)
{
	wxIPV4address server;
	server.AnyAddress();
	server.Service(port);
	
	/*wxSocketClient* socket = new wxSocketClient();
	return socket->Connect(server, true);*/
	wxSocketClient* client = new wxSocketClient();
	client->Connect(server, false);
	
	// Wait until the request completes or until we decide to give up
	bool waitmore = true; 
	while ( !client->WaitOnConnect(2, 0) && waitmore )
	{
		// possibly give some feedback to the user,
		// and update waitmore as needed.
	}
	bool success = client->IsConnected();
	
	free (client);
	
	return !success;
}